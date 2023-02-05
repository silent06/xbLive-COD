#include "stdafx.h"
#include "menu/submenus/aimbotMenu.h"
#include "menu/submenus/visual/compassMenu.h"

Title pTitle;

typedef void(*tMenu_PaintAll)(UIContext* pContext);
tMenu_PaintAll OriginalMenu_PaintAll;
void Menu_PaintAllHook(UIContext* pContext) {
	DWORD dwLR = 0;
	__asm mflr dwLR

	OriginalMenu_PaintAll(pContext);

	if (dwLR != GetPatch(xbLive.pPatches->MW2.Menu_PaintAllReturn)) return;

	pGame.pContext = pContext;
	static once_flag initFlag;
	call_once(&initFlag, [] {
		pRenderer.Initialize();
		pMenu.Initialize();
	});

	if (pContext) {
		if (pContext->iCurrentFrame > 0) {
			pController.Update();
			pSubmenuHandler.ASyncUpdate();
			pMenu.Render();
			pMenu.ASyncUpdate();
		}
	}
}

typedef int(*tCL_SendCmd)(int);
tCL_SendCmd OriginalCL_SendCmd;
int CL_SendCmdHook(int r3) {
	static int fakeLagCount = 0;

	if (Engine::InGame()) {
		if (pGame.bResetState) {
			pGame.bResetState = false;

			for (int i = 0; i < 18; i++) {
				pGame.Clients[i].bPrioritized = false;
			}
		}

		auto cg = Engine::GetCG();
		ClientActive* ca = Engine::GetClientActive();
		UserCommand* command = ca->GetCommand(ca->iCurCmd);
		UserCommand* oldCommand = ca->GetCommand(ca->iCurCmd - 1);
		UserCommand* nextCommand = ca->GetCommand(ca->iCurCmd + 1);
		
		*nextCommand = *command;
		command->iCommandTime--;
		ca->iCurCmd++;

		if (HvHMenuVars::vars.bCrouchEvent) {
			static int crouchCounter = 0;
			static bool crouching = false;

			switch (HvHMenuVars::vars.iCrouchEvent) {
			case 0: // On Damage
				if (Engine::GetCG()->iHealth < Engine::GetCG()->iMaxHealth) {
					crouchCounter++;

					if (crouchCounter >= 8 && !crouching) {
						Engine::CL_SetStance(0, 1);
						crouchCounter = 0;
						crouching = true;
					} else if (crouchCounter >= 8 && crouching) {
						Engine::CL_SetStance(0, 0);
						crouchCounter = 0;
						crouching = false;
					}
				}
				break;
			case 1: // On Target
				if (pGame.iAimbotTarget != -1) {
					crouchCounter++;

					if (crouchCounter >= 8 && !crouching) {
						Engine::CL_SetStance(0, 1);
						crouchCounter = 0;
						crouching = true;
					} else if (crouchCounter >= 8 && crouching) {
						Engine::CL_SetStance(0, 0);
						crouchCounter = 0;
						crouching = false;
					}
				}
				break;
			case 2: // Always
				crouchCounter++;

				if (crouchCounter >= 8 && !crouching) {
					Engine::CL_SetStance(0, 1);
					crouchCounter = 0;
					crouching = true;
				} else if (crouchCounter >= 8 && crouching) {
					Engine::CL_SetStance(0, 0);
					crouchCounter = 0;
					crouching = false;
				}
				break;
			}
		}

		if (AimbotMenuVars::vars.bAimbot) {
			if (AimbotMenuVars::vars.bAimingRequired && cg->fZoomState < 0.5f) return OriginalCL_SendCmd(r3);

			pGame.iAimbotTarget = AimbotMenuVars::CalculateBestClient();

			if (HvHMenuVars::vars.bXDirection) {
				if (HvHMenuVars::vars.iXDirection == 0) {
					// Verticle Jitter
					static float spin = 0.f; spin += 45.f;
					if (spin > 69.99f)
						spin = -69.99f;

					nextCommand->vViewAngles.X = ANGLE2SHORT(spin - ca->vBaseAngles.X);
				} else if (HvHMenuVars::vars.iXDirection == 1 || HvHMenuVars::vars.iXDirection == 2) {
					// Look Up/Look Down
					nextCommand->vViewAngles.X = ANGLE2SHORT((HvHMenuVars::vars.iXDirection == 2 ? -69.99f : 69.99f) - ca->vBaseAngles.X);
				}
			}

			if (HvHMenuVars::vars.bYDirection) {
				if (HvHMenuVars::vars.iYDirection == 0) {
					// Shield
					if (pGame.iAimbotTarget != -1 || pGame.iClosestAATarget != -1) {
						int target = pGame.iAimbotTarget == -1 ? pGame.iClosestAATarget : pGame.iAimbotTarget;

						Vector3<float> viewOrigin;
						Engine::CG_GetPlayerViewOrigin(0, Engine::GetCG(), &viewOrigin);

						Vector3<float> pos = Engine::GetEntity(target).vOrigin;
						Vector3<float> subtracted = pos - viewOrigin;

						Vector3<float> angle;
						Engine::VectorToAngle(&subtracted, &angle);

						nextCommand->vViewAngles.Y = ANGLE2SHORT((angle.Y - 160.f) - ca->vBaseAngles.Y);
					}
				} else if (HvHMenuVars::vars.iYDirection == 1) {
					// Random Jitter
					nextCommand->vViewAngles.Y = ANGLE2SHORT(pUtils.FloatMinMax(0.f, 360.f) - ca->vBaseAngles.Y);
				} else if (HvHMenuVars::vars.iYDirection == 2) {
					// Spin
					static float angle = 0.f;

					if (angle > 360.f)
						angle -= 360.f;

					angle += HvHMenuVars::vars.iYSpeed;
					nextCommand->vViewAngles.Y = ANGLE2SHORT(angle);
				} else if (HvHMenuVars::vars.iYDirection == 3) {
					// Fake
					static bool flip = false; flip ^= true;
					nextCommand->vViewAngles.Y = ANGLE2SHORT((flip ? 69.99f : -69.99f) - ca->vBaseAngles.Y);
				}
			}

			if (pGame.iAimbotTarget != -1) {
				Vector3<float> viewOrigin;
				Engine::CG_GetPlayerViewOrigin(0, cg, &viewOrigin);

				auto entity = Engine::GetEntity(pGame.iAimbotTarget);
				auto bonePosition = Engine::GetTagPosition(pGame.iAimbotTarget, pGame.Clients[pGame.iAimbotTarget].pBestTag);

				if (AimbotMenuVars::vars.bPositionPrediction) {
					auto oldPosition = entity.GetPreviousPredictedPosition();
					auto newPosition = entity.GetNextPredictedPosition();

					auto velocity = (newPosition - oldPosition).NormalizeInline();
					velocity *= AimbotMenuVars::vars.fPositionPrediction;
					bonePosition += velocity;
				}

				auto subtracted = bonePosition - viewOrigin;

				Vector3<float> angle;
				Engine::VectorToAngle(&subtracted, &angle);

				switch (AimbotMenuVars::vars.iAimType) {
				case 0: // snap
					AimbotMenuVars::SnapAim(angle);
					break;
				case 1: // silent
					AimbotMenuVars::SilentAim(command, angle);
					break;
				}

				if (MainMenuVars::vars.bNoSpread) {
					MainMenuVars::NoSpread(command);
				}

				if (AimbotMenuVars::vars.bAutoFire) {
					static int timer = 0;
					if (GetTickCount() - timer > AimbotMenuVars::vars.iAutoFireDelay) {
						timer = GetTickCount();
						command->dwButton |= 1;
					}
				}
			}
		}

		if (HvHMenuVars::vars.bFakeLag) {
			fakeLagCount++;
			if (fakeLagCount >= HvHMenuVars::vars.iFakeLag || (command->dwButton != 0) || (oldCommand->dwButton != 0) || (nextCommand->dwButton != 0)) {
				fakeLagCount = 0;
			}
		} else {
			fakeLagCount = 0;
		}
	} else {
		pGame.bResetState = true;
		fakeLagCount = 0;
	}

	if (fakeLagCount == 0)
		return OriginalCL_SendCmd(r3);
	else return 0;
}

typedef void(*tCG_Respawn)(int iLocalClient, bool bUnk);
tCG_Respawn OriginalCG_Respawn;
void CG_RespawnHook(int iLocalClient, bool bUnk) {
	OriginalCG_Respawn(iLocalClient, bUnk);

	Engine::CacheEquipmentIndexs();

	CompassMenuVars::DisableEngineCompass();
	MainMenuVars::DvarSetHearEveryone();
	MainMenuVars::DvarThirdPerson();
	MainMenuVars::DvarFOV();

	MainMenuVars::vars.bWasReloading = false;
	MainMenuVars::vars.bReloadYPressed = false;
	MainMenuVars::vars.iReloadCount = 0;
}

typedef void(*tR_AddCmdDrawStretchPic)(float x, float y, float width, float height, float xScale, float yScale, float xay, float yay, const float * color, Material * material);
tR_AddCmdDrawStretchPic OriginalR_AddCmdDrawStretchPic;
void R_AddCmdDrawStretchPicHook(float x, float y, float width, float height, float xScale, float yScale, float xay, float yay, const float * color, Material * material) {
	if (material) {
		if (material->pName) {
			if (!strcmp(material->pName, "mw2_main_cloud_overlay")
				|| !strcmp(material->pName, "mockup_bg_glow")) {
				return OriginalR_AddCmdDrawStretchPic(x, y, width, height, xScale, yScale, xay, yay, Color(160, 57, 64).GetFloatPtr(), material);
			}

			if ((!strcmp(material->pName, "minimap_scanlines") || !strcmp(material->pName, "scanlines_stencil"))) {
				if (CompassMenuVars::vars.bDisableEngineCompass) {
					return;
				}
			}
		}
	}

	OriginalR_AddCmdDrawStretchPic(x, y, width, height, xScale, yScale, xay, yay, color, material);
}

typedef DWORD(*tXamInputGetState)(int r3, int r4, XINPUT_STATE* state);
tXamInputGetState OriginalXamInputGetState;
DWORD XamInputGetStateHook(int dwUserIndex, int dwDeviceContext, XINPUT_STATE* pInputState) {
	DWORD ret = OriginalXamInputGetState(dwUserIndex, dwDeviceContext, pInputState);

	auto result = OriginalXamInputGetState(dwUserIndex, dwDeviceContext, pInputState);

	if (pInputState) {
		if (Engine::InGame()) {
			if (MainMenuVars::vars.bFastReload) {
				if (MainMenuVars::vars.bWasReloading) {
					if (!MainMenuVars::vars.bReloadYPressed) {
						if (!((pInputState->Gamepad.wButtons & XINPUT_GAMEPAD_Y) == XINPUT_GAMEPAD_Y)) {
							pInputState->Gamepad.wButtons |= XINPUT_GAMEPAD_Y;
						}

						MainMenuVars::vars.bReloadYPressed = true;
						MainMenuVars::vars.iReloadCount++;
					}

					if (MainMenuVars::vars.iReloadCount > 1) {
						MainMenuVars::vars.bWasReloading = false;
						MainMenuVars::vars.bReloadYPressed = false;
						MainMenuVars::vars.iReloadCount = 0;
					}
				}
			}
		}

		if (pMenu.IsOpen()) {
			pController.bABypass = (bool)(pInputState->Gamepad.wButtons & XINPUT_GAMEPAD_A);
			pController.bBBypass = (bool)(pInputState->Gamepad.wButtons & XINPUT_GAMEPAD_B);
			pController.bLeftBypass = (bool)(pInputState->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
			pController.bRightBypass = (bool)(pInputState->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
			pController.bLeftBumperBypass = (bool)(pInputState->Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER);
			pController.bRightBumperBypass = (bool)(pInputState->Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER);

			pInputState->Gamepad.wButtons &= ~(XINPUT_GAMEPAD_LEFT_SHOULDER | XINPUT_GAMEPAD_RIGHT_SHOULDER | XINPUT_GAMEPAD_DPAD_UP | XINPUT_GAMEPAD_DPAD_DOWN | XINPUT_GAMEPAD_DPAD_LEFT | XINPUT_GAMEPAD_DPAD_RIGHT | XINPUT_GAMEPAD_A | XINPUT_GAMEPAD_B);
		}
	}

	return ret;
}

typedef void(*tCG_EntityEvent)(int, int, int, int);
tCG_EntityEvent OriginalCG_EntityEvent;
void CG_EntityEventHook(int client, int entityState, int pevent, int eventParam) {
	if (MainMenuVars::vars.bFastReload) {
		if (pevent == 23) {
			auto reloadIndex = *(short*)(entityState + 0xD0);
			if (reloadIndex == (short)Engine::GetCG()->iClientNumber) {
				MainMenuVars::vars.bWasReloading = true;
			}
		} else if (pevent == 26) {
			auto clientSwitchIndex = *(short*)(entityState + 0xD0);
			if (MainMenuVars::vars.bWasReloading && MainMenuVars::vars.iReloadCount == 1) {
				MainMenuVars::vars.bReloadYPressed = false;
			}
		}
	}

	OriginalCG_EntityEvent(client, entityState, pevent, eventParam);
}

bool Title::ApplyHooks() {
	if (!bInitialized) {
		pHooking.HookFunction(GetPatch(xbLive.pPatches->MW2.CG_EntityEvent), &CG_EntityEventHook, (void**)&OriginalCG_EntityEvent);
		pHooking.HookFunction(GetPatch(xbLive.pPatches->MW2.CG_Respawn), &CG_RespawnHook, (void**)&OriginalCG_Respawn);
		pHooking.HookFunction(GetPatch(xbLive.pPatches->MW2.Menu_PaintAll), &Menu_PaintAllHook, (void**)&OriginalMenu_PaintAll);
		pHooking.HookFunction(GetPatch(xbLive.pPatches->MW2.R_AddCmdDrawStretchPic), &R_AddCmdDrawStretchPicHook, (void**)&OriginalR_AddCmdDrawStretchPic);
		pHooking.HookFunction(GetPatch(xbLive.pPatches->MW2.XamInputGetState), &XamInputGetStateHook, (void**)&OriginalXamInputGetState);
		pHooking.HookFunction(GetPatch(xbLive.pPatches->MW2.CL_SendCmd), &CL_SendCmdHook, (void**)&OriginalCL_SendCmd);

		*(DWORD*)GetPatch(xbLive.pPatches->MW2.CrashFix[0]) = 0x60000000;
		*(DWORD*)GetPatch(xbLive.pPatches->MW2.CrashFix[1]) = 0x60000000; // crash

		LOG_DEV("Applied detours!");
		bInitialized = true;
		return true;
	} else {
		LOG_DEV("TitleHooks already initialized!");
	}

	return false;
}

void Title::Remove(bool bOverride) {
	if (bInitialized || bOverride) {
		pHooking.UnhookAll();

		Sleep(1000);

		LOG_DEV("Removed detours!");
		bInitialized = false;
	} else {
		LOG_DEV("TitleHooks have not been initialized!");
	}
}