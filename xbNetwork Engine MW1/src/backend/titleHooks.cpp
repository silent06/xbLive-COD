#include "stdafx.h"
#include "menu/submenus/aimbotMenu.h"
#include "menu/submenus/hvhMenu.h"
#include "menu/submenus/visual/compassMenu.h"

Title pTitle;

typedef void(*tMenu_PaintAll)(UIContext* pContext);
tMenu_PaintAll OriginalMenu_PaintAll;
void Menu_PaintAllHook(UIContext* pContext) {
	OriginalMenu_PaintAll(pContext);

	pGame.pContext = (UIContext*)GetPatch(xbLive.pPatches->MW1.Menu_PaintAllPointer);

	static once_flag initFlag;
	call_once(&initFlag, [] {
		pRenderer.Initialize();
		pMenu.Initialize();
	});

	if (pContext) {
		pController.Update();
		pSubmenuHandler.ASyncUpdate();
		pMenu.Render();
		pMenu.ASyncUpdate();
	}
}

typedef int(*tCL_ReadyToSendPacket)(int);
tCL_ReadyToSendPacket OriginalCL_ReadyToSendPacket;
int CL_ReadyToSendPacketHook(int r3) {
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
				// Random Jitter
				nextCommand->vViewAngles.Y = ANGLE2SHORT(pUtils.FloatMinMax(0.f, 360.f) - ca->vBaseAngles.Y);
			} else if (HvHMenuVars::vars.iYDirection == 1) {
				// Spin
				static float angle = 0.f;

				if (angle > 360.f)
					angle -= 360.f;

				angle += HvHMenuVars::vars.iYSpeed;
				nextCommand->vViewAngles.Y = ANGLE2SHORT(angle);
			} else if (HvHMenuVars::vars.iYDirection == 2) {
				// Fake
				static bool flip = false; flip ^= true;
				nextCommand->vViewAngles.Y = ANGLE2SHORT((flip ? 69.99f : -69.99f) - ca->vBaseAngles.Y);
			}
		}

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
			if (AimbotMenuVars::vars.bAimingRequired && !pController.IsAiming()) return OriginalCL_ReadyToSendPacket(r3);

			pGame.iAimbotTarget = AimbotMenuVars::CalculateBestClient();
			if (pGame.iAimbotTarget != -1) {
				Vector3<float> viewOrigin;
				Engine::CG_GetPlayerViewOrigin(0, cg->GetPlayerState(), &viewOrigin);

				auto entity = Engine::GetEntity(pGame.iAimbotTarget);
				auto bonePosition = Engine::GetTagPosition(pGame.iAimbotTarget, pGame.Clients[pGame.iAimbotTarget].pBestTag);
				if (bonePosition.IsNull()) return OriginalCL_ReadyToSendPacket(r3);

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
					MainMenuVars::NoSpread(command, nextCommand);
				}

				if (AimbotMenuVars::vars.bAutoFire) {
					static int timer = 0;
					if (GetTickCount() - timer > AimbotMenuVars::vars.iAutoFireDelay) {
						timer = GetTickCount();

						nextCommand->dwButton |= 1;
						if (command->dwButton & 1) {
							command->dwButton &= 0xFFFFFFFEu;
						}
					}
				} else {
					if (pController.IsShooting()) {
						nextCommand->dwButton |= 1;
						if (command->dwButton & 1) {
							command->dwButton &= 0xFFFFFFFEu;
						}
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
		return OriginalCL_ReadyToSendPacket(r3);
	else return 0;
}

typedef void(*tCG_Respawn)(int iLocalClient);
tCG_Respawn OriginalCG_Respawn;
void CG_RespawnHook(int iLocalClient) {
	OriginalCG_Respawn(iLocalClient);

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
			if (!strcmp(material->pName, "animbg_blur_front")
				|| !strcmp(material->pName, "animbg_blur_back")
				|| !strcmp(material->pName, "animbg_blur_fogscroll")) {
				return OriginalR_AddCmdDrawStretchPic(x, y, width, height, xScale, yScale, xay, yay, Color(160, 57, 64).GetFloatPtr(), material);
			}
		}
	}

	OriginalR_AddCmdDrawStretchPic(x, y, width, height, xScale, yScale, xay, yay, color, material);
}

typedef DWORD(*tXamInputGetState)(int r3, int r4, XINPUT_STATE* state);
tXamInputGetState OriginalXamInputGetState;
DWORD XamInputGetStateHook(int dwUserIndex, int dwDeviceContext, XINPUT_STATE* pInputState) {
	DWORD ret = OriginalXamInputGetState(dwUserIndex, dwDeviceContext, pInputState);

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

typedef void(*tCG_EntityEvent)(int, int, int);
tCG_EntityEvent OriginalCG_EntityEvent;
void CG_EntityEventHook(int client, int entityState, int pevent) {
	if (MainMenuVars::vars.bFastReload) {
		if (pevent == 20) {
			auto reloadIndex = *(short*)(entityState + 0xC0);
			if (reloadIndex == (short)Engine::GetCG()->iClientNumber) {
				MainMenuVars::vars.bWasReloading = true;
			}
		} else if (pevent == 23) {
			auto clientSwitchIndex = *(short*)(entityState + 0xC0);
			if (MainMenuVars::vars.bWasReloading && MainMenuVars::vars.iReloadCount == 1) {
				MainMenuVars::vars.bReloadYPressed = false;
			}
		}
	}

	OriginalCG_EntityEvent(client, entityState, pevent);
}

bool Title::ApplyHooks() {
	if (!bInitialized) {

		pHooking.HookFunction(GetPatch(xbLive.pPatches->MW1.CL_ReadyToSendPacket), &CL_ReadyToSendPacketHook, (void**)&OriginalCL_ReadyToSendPacket);
		pHooking.HookFunction(GetPatch(xbLive.pPatches->MW1.CG_EntityEvent), &CG_EntityEventHook, (void**)&OriginalCG_EntityEvent);
		pHooking.HookFunction(GetPatch(xbLive.pPatches->MW1.CG_Respawn), &CG_RespawnHook, (void**)&OriginalCG_Respawn);
		pHooking.HookFunction(GetPatch(xbLive.pPatches->MW1.Menu_PaintAll), &Menu_PaintAllHook, (void**)&OriginalMenu_PaintAll);
		pHooking.HookFunction(GetPatch(xbLive.pPatches->MW1.R_AddCmdDrawStretchPic), &R_AddCmdDrawStretchPicHook, (void**)&OriginalR_AddCmdDrawStretchPic);
		pHooking.HookFunction(GetPatch(xbLive.pPatches->MW1.XamInputGetState), &XamInputGetStateHook, (void**)&OriginalXamInputGetState);

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