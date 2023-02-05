#include "stdafx.h"
#include "aimbotMenu.h"

using namespace AimbotMenuVars;

namespace AimbotMenuVars {
	Vars vars;

	ScrollStruct<int> ScrollAimFilter[] = {
		"Visible", 0,
		"Logical", 1,
	};

	ScrollStruct<int> ScrollAimType[] = {
		"Snap", 0,
		"Silent", 1,
		// "Legit", 2
	};

	ScrollStruct<int> ScrollAutowallBoneTags[] = {
		"j_head", 100,
		"j_hip_le", 50,
		"j_hip_ri", 40,
		"j_mainroot", 90,
		"j_spineupper", 80,
		"j_shoulder_le", 70,
		"j_shoulder_ri", 60
	};

	ScrollStruct<int> ScrollAimTag[] = {
		"j_helmet", 100,
		"j_mainroot", 90,
		"j_neck", 100,
		"j_head", 100,
		"j_hip_le", 90,
		"j_hip_ri", 90,
		"j_knee_le", 90,
		"j_knee_ri", 90,
		"j_spineupper", 80,
		"j_ankle_le", 90,
		"j_ankle_ri", 90,
		"j_shoulder_le", 90,
		"j_shoulder_ri", 90,
		"j_elbow_le", 90,
		"j_elbow_ri", 90,
		"j_jaw", 100,
		"j_toeend_le", 80,
		"j_toeend_ri", 80,
		"j_thumb_le_1", 80,
		"j_thumb_ri_1", 80,
		"j_pinky_le_1", 80,
		"j_pinky_ri_1", 80
	};

	bool IsTargetVisible(float fraction) {
		return fraction >= (vars.bIncreasedPenetrationChecks ? 0.92f : 0.97f);
	}

	bool IsClientWallbangable(int client, const char* bone) {
		if (!Engine::GetCG()) return false;

		auto end = Engine::GetTagPosition(client, bone);

		Vector3<float> viewOrigin;
		Engine::CG_GetPlayerViewOrigin(0, Engine::GetCG(), &viewOrigin);

		BulletFireParams bulletFireParams;
		bulletFireParams.iMaxEntityNumber = 2046;
		bulletFireParams.iIgnoreEntIndex = Engine::GetCG()->iClientNumber;
		bulletFireParams.fDamageMultiplier = 1.0f;
		bulletFireParams.iMethodOfDeath = 2;
		bulletFireParams.iUnk = 0;
		bulletFireParams.vOriginalStart = viewOrigin;
		bulletFireParams.vStart = viewOrigin;
		bulletFireParams.vEnd = end;

		Vector3<float> endDirection = end - viewOrigin;

		Vector3<float> angle;
		Engine::VectorToAngle(&endDirection, &angle);

		Vector3<float> hax;
		pUtils.AngleVectors(angle, &hax, nullptr, nullptr);
		
		bulletFireParams.vDirection = hax;

		*(DWORD*)GetPatch(xbLive.pPatches->MW3.Autowall[0]) = 0x4E800020;
		*(DWORD*)GetPatch(xbLive.pPatches->MW3.Autowall[1]) = 0x38600001;
		*(QWORD*)GetPatch(xbLive.pPatches->MW3.Autowall[2]) = 0x386000004E800020;
		*(QWORD*)GetPatch(xbLive.pPatches->MW3.Autowall[3]) = 0x386000004E800020;

		Engine::FireBulletPenetrate(0, &bulletFireParams, Engine::GetEntity(Engine::GetCG()->iClientNumber).iWeaponIndex, -1, &Engine::GetEntity(Engine::GetCG()->iClientNumber), -1, &viewOrigin, false);

		*(DWORD*)GetPatch(xbLive.pPatches->MW3.Autowall[0]) = 0x7D8802A6;
		*(DWORD*)GetPatch(xbLive.pPatches->MW3.Autowall[1]) = 0x4bff994d;
		*(QWORD*)GetPatch(xbLive.pPatches->MW3.Autowall[2]) = 0x7D8802A64835A3A9;
		*(QWORD*)GetPatch(xbLive.pPatches->MW3.Autowall[3]) = 0x7D8802A69181FFF8;

		return (bulletFireParams.iIgnoreEntIndex == client);
	}

	void SnapAim(Vector3<float> toAngle) {
		auto ca = Engine::GetClientActive();
		if (ca) {
			ca->vViewAngles.X = toAngle.X - ca->vBaseAngles.X;
			ca->vViewAngles.Y = toAngle.Y - ca->vBaseAngles.Y;
		}
	}

	void FixMovement(UserCommand* pCmd, float CurAngle, float OldAngle, float fOldForward, float fOldSidemove) {
		float deltaView = CurAngle - OldAngle;
		int forward = (int)(cos(deltaView * (PI / 180.0f)) * fOldForward + cos((deltaView + 90.f) * (PI / 180.0f)) * fOldSidemove);
		int right = (int)(sin(deltaView * (PI / 180.0f)) * fOldForward + sin((deltaView + 90.f) * (PI / 180.0f)) * fOldSidemove);

		if (forward < -128) forward = -128;
		else if (forward > 127) forward = 127;
		if (right < -128) right = -128;
		else if (right > 127) right = 127;

		pCmd->bForwardmove = (char)forward;
		pCmd->bRightmove = (char)right;
	}

	void SilentAim(UserCommand* oldCommand, Vector3<float> toAngle) {
		auto ca = Engine::GetClientActive();
		if (ca) {
			float oldAngle = SHORT2ANGLE(oldCommand->vViewAngles.Y);
			oldCommand->vViewAngles.X = ANGLE2SHORT(toAngle.X - ca->vBaseAngles.X);
			oldCommand->vViewAngles.Y = ANGLE2SHORT(toAngle.Y - ca->vBaseAngles.Y);
			FixMovement(oldCommand, SHORT2ANGLE(oldCommand->vViewAngles.Y), oldAngle, oldCommand->bForwardmove, oldCommand->bRightmove);
			vars.vSilentAngles = oldCommand->vViewAngles;
		}
	}

	Vector3<float> AnglesToForward(Vector3<float> Angles, float Distance = 250.0f) {
		float angle, sp, sy, cp, cy, PiDiv = M_PI / 180.0f;

		angle = Angles.Y * PiDiv;

		sy = sinf(angle);
		cy = cosf(angle);

		angle = Angles.X * PiDiv;

		sp = sinf(angle);
		cp = cosf(angle);

		Vector3<float> Forward;
		Forward.X = (cp * cy * Distance);
		Forward.Y = (cp * sy * Distance);
		Forward.Z = (-sp * Distance);
		return Forward;
	}

	float WallDepth(Vector3<float> p1, Vector3<float> p2) {
		Vector3<float> v = p2 - p1;
		return sqrt(v.X * v.X + v.Y * v.Y + v.Z * v.Z);
	}

	float GetAimDegree(int t) {
		Vector3<float> clientAngles = Engine::GetEntity(t).vAngles;
		Vector3<float> EnemyPos = Engine::GetTagPosition(t, "j_head");
		return WallDepth((EnemyPos + AnglesToForward(clientAngles, WallDepth(Engine::GetCG()->Refdef.vOrigin, EnemyPos))), Engine::GetCG()->Refdef.vOrigin);
	}

	int CalculateBestClient() {
		if (Engine::InGame() && AimbotMenuVars::vars.bAimbot) {
			float closestDistance = FLT_MAX;
			int closestClient = -1;

			float smallestAimDregree = FLT_MAX;
			int smallestAimClient = -1;

			for (int i = 0; i < 18; i++) {
				pGame.Clients[i].dwPriority = 0;
				pGame.Clients[i].bVisible = false;
				pGame.Clients[i].bWallbangable = false;
				pGame.Clients[i].bValid = false;

				if (Engine::GetCG() == nullptr) continue;
				if (i == Engine::GetCG()->iClientNumber) continue;
				if (!Engine::IsAlive(i) || Engine::IsFriend(i)) continue;

				pGame.Clients[i].bValid = true;

				auto entity = Engine::GetEntity(i);
				auto clientInfo = Engine::GetClientInfo(i);

				auto status = entity.GetStatus();
				if (status == 128)
					pGame.Clients[i].dwPriority += PRIORITY_SHOOTING_NOT_AIMING;
				if (status == 8)
					pGame.Clients[i].dwPriority += PRIORITY_AIMING_NOT_SHOOTING;
				if (status == 136)
					pGame.Clients[i].dwPriority += PRIORITY_AIMING_AND_SHOOTING;

				float aimDegrees = GetAimDegree(i);
				bool secondaryShield = Engine::IsWeaponThis(entity.GetSecondaryWeaponID(), WEAPON_SHIELD);
				bool primaryShield = Engine::IsWeaponThis(entity.iWeaponIndex, WEAPON_SHIELD);

				if (aimDegrees < 50.f) {
					pGame.Clients[i].dwPriority += PRIORITY_AIMING_AT_ME;

					if (aimDegrees < smallestAimDregree) {
						smallestAimDregree = aimDegrees;
						smallestAimClient = i;
					}
				}

				if (Engine::GetCG() == nullptr) continue;
				float distance = Engine::GetDistance(Engine::GetEntity(Engine::GetCG()->iClientNumber).vOrigin, entity.vOrigin);
				if (distance < closestDistance) {
					closestDistance = distance;
					closestClient = i;
				}

				pGame.Clients[i].pBestTag = AimbotMenuVars::ScrollAimTag[AimbotMenuVars::vars.iAimTag].pName;

				if (AimbotMenuVars::vars.bAutowall) {
					bool runNormal = true;
					if (primaryShield) {
						if (aimDegrees < 70.f) {
							runNormal = false;
							auto tag = (rand() % 10) > 4 ? "j_ankle_le" : "j_ankle_ri";
							if ((pGame.Clients[i].bWallbangable = AimbotMenuVars::IsClientWallbangable(i, tag))) {
								pGame.Clients[i].pBestTag = tag;
								pGame.Clients[i].dwPriority += PRIORITY_WALLBANGABLE;
							}
						}
					} else if (secondaryShield) {
						if (aimDegrees < 70.f) {
							runNormal = false;
							if ((pGame.Clients[i].bWallbangable = AimbotMenuVars::IsClientWallbangable(i, "j_knee_ri"))) {
								pGame.Clients[i].pBestTag = "j_knee_ri";
								pGame.Clients[i].dwPriority += PRIORITY_WALLBANGABLE;
							}
						} else if (aimDegrees > 70.f && aimDegrees < 220.f) {
							runNormal = false;
							const char* tags[] = { "j_knee_le", "j_knee_ri" };
							auto attemptedTag = tags[rand() % 2];
							if ((pGame.Clients[i].bWallbangable = AimbotMenuVars::IsClientWallbangable(i, attemptedTag))) {
								pGame.Clients[i].pBestTag = attemptedTag;
								pGame.Clients[i].dwPriority += PRIORITY_WALLBANGABLE;
							}
						} else if (aimDegrees > 220.f) {
							runNormal = false;
							if ((entity.iFlags & 0x4) != 0) {
								if ((pGame.Clients[i].bWallbangable = AimbotMenuVars::IsClientWallbangable(i, "j_knee_ri"))) {
									pGame.Clients[i].pBestTag = "j_knee_ri";
									pGame.Clients[i].dwPriority += PRIORITY_WALLBANGABLE;
								}
							} else {
								const char* tags[] = { "j_knee_le", "j_knee_ri" };
								auto attemptedTag = tags[rand() % 2];
								if ((pGame.Clients[i].bWallbangable = AimbotMenuVars::IsClientWallbangable(i, attemptedTag))) {
									pGame.Clients[i].pBestTag = attemptedTag;
									pGame.Clients[i].dwPriority += PRIORITY_WALLBANGABLE;
								}
							}
						}
					}

					if (runNormal) {
						if (pGame.Clients[i].bPrioritized) {
							struct NiggerShit {
								bool bWallbangable;
								const char* strTag;
								int iPriority;
							}; NiggerShit wallbangableBones[7];
							memset(wallbangableBones, 0, sizeof(wallbangableBones));

							for (int hhh = 0; hhh < 7; hhh++) {
								if (AimbotMenuVars::IsClientWallbangable(i, AimbotMenuVars::ScrollAutowallBoneTags[hhh].pName)) {
									wallbangableBones[hhh].bWallbangable = true;
									wallbangableBones[hhh].strTag = AimbotMenuVars::ScrollAutowallBoneTags[hhh].pName;
									wallbangableBones[hhh].iPriority = AimbotMenuVars::ScrollAutowallBoneTags[hhh].Result;
								}
							}

							int cachedPriority = 0;
							int bestIndex = -1;

							for (int dddd = 0; dddd < 7; dddd++) {
								if (wallbangableBones[dddd].bWallbangable) {
									if (wallbangableBones[dddd].iPriority > cachedPriority) {
										cachedPriority = wallbangableBones[dddd].iPriority;
										bestIndex = dddd;
									}
								}
							}

							if (bestIndex != -1) {
								pGame.Clients[i].bWallbangable = true;
								pGame.Clients[i].pBestTag = wallbangableBones[bestIndex].strTag;
								pGame.Clients[i].dwPriority += PRIORITY_WALLBANGABLE;
							} else {
								pGame.Clients[i].bWallbangable = false;
							}

							if ((pGame.Clients[i].bVisible = IsTargetVisible(Engine::GetBoneFraction(i, "j_helmet")))) {
								pGame.Clients[i].dwPriority += PRIORITY_VISIBLE;
							}
						} else {
							if ((pGame.Clients[i].bWallbangable = AimbotMenuVars::IsClientWallbangable(i, pGame.Clients[i].pBestTag))) {
								pGame.Clients[i].dwPriority += PRIORITY_WALLBANGABLE;
							}
						}

						if ((pGame.Clients[i].bVisible = IsTargetVisible(Engine::GetBoneFraction(i, AimbotMenuVars::ScrollAimTag[AimbotMenuVars::vars.iAimTag].pName)))) {
							pGame.Clients[i].dwPriority += PRIORITY_VISIBLE;
						}
					}
				} else {
					if (pGame.Clients[i].bPrioritized) {
						struct MoreNiggerShit {
							const char* pTag;
							int iPriority;
							bool bVisible;
						}; MoreNiggerShit t[22];
						memset(t, 0, sizeof(t));

						for (int hhh = 0; hhh < 22; hhh++) {
							if ((Engine::GetBoneFraction(i, AimbotMenuVars::ScrollAimTag[hhh].pName) >= 0.97f)) {
								t[i].pTag = AimbotMenuVars::ScrollAimTag[hhh].pName;
								t[i].iPriority = AimbotMenuVars::ScrollAimTag[hhh].Result;
								t[i].bVisible = true;
							}
						}

						int cachedPriority = 0;
						int bestIndex = -1;

						for (int dddd = 0; dddd < 22; dddd++) {
							if (t[dddd].bVisible) {
								if (t[dddd].iPriority > cachedPriority) {
									cachedPriority = t[dddd].iPriority;
									bestIndex = dddd;
								}
							}
						}

						if (bestIndex != -1) {
							pGame.Clients[i].bVisible = true;
							pGame.Clients[i].pBestTag = t[bestIndex].pTag;
							pGame.Clients[i].dwPriority += PRIORITY_VISIBLE;
						}
					} else {
						if ((pGame.Clients[i].bVisible = IsTargetVisible(Engine::GetBoneFraction(i, AimbotMenuVars::ScrollAimTag[AimbotMenuVars::vars.iAimTag].pName)))) {
							pGame.Clients[i].dwPriority += PRIORITY_VISIBLE;
						}
					}
				}

				if (pGame.Clients[i].pBestTag == nullptr || !strcmp(pGame.Clients[i].pBestTag, "Auto")) {
					pGame.Clients[i].pBestTag = "j_helmet";
				}
			}

			pGame.iClosestAATarget = closestClient;

			if (closestClient != -1)
				pGame.Clients[closestClient].dwPriority += PRIORITY_CLOSEST_CLIENT;

			if (smallestAimClient != -1)
				pGame.Clients[smallestAimClient].dwPriority += PRIORITY_AIMING_AT_ME_THE_MOST;

			DWORD cachedPriority = 0;
			int bestClient = -1;

			if (Engine::GetCG() == nullptr) return -1;
			for (int i = 0; i < 18; i++) {
				if (i == Engine::GetCG()->iClientNumber || !pGame.Clients[i].bValid) continue;
				if ((AimbotMenuVars::vars.bAutowall && pGame.Clients[i].bWallbangable) || pGame.Clients[i].bVisible) {
					if (AimbotMenuVars::vars.iAimFilter == 0 && !pGame.Clients[i].bVisible) continue;
					if (pGame.Clients[i].dwPriority >= cachedPriority) {
						cachedPriority = pGame.Clients[i].dwPriority;
						bestClient = i;
					}
				}
			}

			for (int i = 0; i < 18; i++) {
				pGame.Clients[i].dwPriority = 0;
			}

			if (!Engine::IsAlive(bestClient) || bestClient == Engine::GetCG()->iClientNumber) {
				return -1;
			}

			return bestClient;
		}

		return -1;
	}

	void OnAimbot() {
		pGame.iAimbotTarget = -1;
	}
}

void AimbotMenu::Init() {
	SetName("Aimbot");

	addOption(ToggleOption("Enable Aimbot")
		.addToggle(vars.bAimbot)
		.addFunction(OnAimbot).canBeSaved("Aimbot")
		.addTooltip("Aimbot will only run if this is enabled."));

	addOption(ToggleOption("Aiming Required")
		.addToggle(vars.bAimingRequired).canBeSaved("Aimbot")
		.addTooltip("You'll be required to aim in your weapon to use the aimbot options."));

	addOption(ScrollOption<int>(SCROLL, "Aim Filter")
		.addScroll(vars.iAimFilter, 0, NUMOF(ScrollAimFilter) - 1, ScrollAimFilter).canBeSaved("Aimbot")
		.addTooltip("The filter that gets applied when scanning for a target.\nVisible: Only run when the target is visible\nLogical: Run when the target is visible or through walls"));

	addOption(ScrollOption<int>(SCROLL, "Aim Type")
		.addScroll(vars.iAimType, 0, NUMOF(ScrollAimType) - 1, ScrollAimType).canBeSaved("Aimbot")
		.addTooltip("The aim type that'll be used.\nSnap: Snaps your view onto the target\nSilent: Curves your bullets to hit the target"));

	addOption(ScrollOption<int>(SCROLL, "Aim Tag")
		.addScroll(vars.iAimTag, 0, NUMOF(ScrollAimTag) - 1, ScrollAimTag).canBeSaved("Aimbot")
		.addTooltip("The bone that the aimbot will target. To use multiple bones at once (autobone), prioritize the client in the Players menu."));

	addOption(NumberOption<float>(TOGGLE, "Position Prediction")
		.addToggle(vars.bPositionPrediction)
		.addNumber(vars.fPositionPrediction, "%.1f", 0.1f).addMin(0.01f).addMax(1.5f).canBeSaved("Aimbot")
		.addTooltip("Enables prediction the targets next position and sets the delta to use."));

	addOption(ToggleOption("Autowall")
		.addToggle(vars.bAutowall).canBeSaved("Aimbot")
		.addTooltip("Automatically checks to see if targets can be damaged through walls."));

	addOption(ToggleOption("Increased Penetration Checks")
		.addToggle(vars.bIncreasedPenetrationChecks).canBeSaved("Aimbot")
		.addTooltip("Enables extra checks for penetration when using the Logical filter."));

	addOption(NumberOption<int>(TOGGLE, "Auto Fire (with delay)")
		.addToggle(vars.bAutoFire)
		.addNumber(vars.iAutoFireDelay, "%ims", 50).addMin(0).addMax(5000).setScrollSpeed(10).canBeSaved("Aimbot")
		.addTooltip("Enables auto fire and sets the delay between shots."));

	addOption(ToggleOption("Auto ADS")
		.addToggle(vars.bAutoADS).canBeSaved("Aimbot")
		.addTooltip("Automatically aims in your weapon when you have a target."));

	addOption(ToggleOption("Show Aimbot Target")
		.addToggle(vars.bShowAimbotTarget).canBeSaved("Aimbot")
		.addTooltip("Singles out the target in visuals."));

	vars.fPositionPrediction = 0.2f;
}

/*Update once when submenu is opened*/
void AimbotMenu::UpdateOnce() {}

/*Update while submenu is active*/
void AimbotMenu::Update() {}

/*Background update*/
void AimbotMenu::FeatureUpdate() {}

/*Singleton*/
AimbotMenu* _instance;
AimbotMenu* AimbotMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new AimbotMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
AimbotMenu::~AimbotMenu() { delete _instance; }