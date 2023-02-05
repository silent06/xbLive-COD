#include "stdafx.h"
#include "espMenu.h"
#include "../visualMenu.h"

using namespace ESPMenuVars;

namespace ESPMenuVars {
	Vars vars;

	struct Positioning {
		Vector3<float> vFeet;
		Vector3<float> vHead;
		Vector3<float> vHelmet;
		Vector3<float> vOrigin;
	};

	ScrollStruct<int> Box[] = {
		"2D", 0,
		"3D", 1,
		"Filled", 2,
		"Corners", 3
	};

	ScrollStruct<int> Snaplines[] = {
		"Top", 0,
		"Center", 1,
		"Bottom", 2
	};

	Positioning GetPositioning(int client) {
		Positioning pos;
		pos.vHead = Engine::GetTagPosition(client, "j_head");
		pos.vFeet = Engine::GetTagPosition(client, "j_ankle_ri");
		pos.vHelmet = Engine::GetTagPosition(client, "j_helmet");
		pos.vOrigin = Engine::GetEntity(client).vOrigin;
		return pos;
	}

	void DrawESPLine(Vector3<float> center, float x1, float y1, float z1, float x2, float y2, float z2, Color color) {
		Vector3<float> pointPos1 = Vector3<float>(center.X + x1, center.Y + y1, center.Z + z1);
		Vector3<float> pointPos2 = Vector3<float>(center.X + x2, center.Y + y2, center.Z + z2);
		Vector3<float> xy1, xy2;

		if (Engine::WorldToScreen(pointPos1, &xy1) && Engine::WorldToScreen(pointPos2, &xy2)) {
			pRenderer.DrawLine(xy1.X, xy1.Y, xy2.X, xy2.Y, 1, color, pRenderer.Materials.white);
		}
	}

	void DrawBoneOnPlayer(int client, char*startBone, char*endBone, Color color) {
		Vector3<float> s, e;
		auto start = Engine::GetTagPosition(client, startBone);
		auto finish = Engine::GetTagPosition(client, endBone);
		if (Engine::WorldToScreen(start, &s) && Engine::WorldToScreen(finish, &e)) {
			pRenderer.DrawLine(s.X, s.Y, e.X, e.Y, 1, color, pRenderer.Materials.white);
		}
	}

	void PatchGameNames() {
		*(DWORD*)GetPatch(xbLive.pPatches->WAW.PatchGameNames) = (vars.bDrawNames || vars.bDrawDistance) ? 0x4e800020 : 0x7d8802a6;
	}

	void FixTextForDistance(const char* text, float* x, float* y, Font* font, float scale, Vector3<float> worldPos, float* outDist) {
		float distanceSq = Engine::GetDistance(Engine::GetCG()->Refdef.vOrigin, worldPos);
		float distance = sqrt(distanceSq);
		float distFrac = (float)(distance - 64) / 448;
		float distScale = (float)(distFrac * scale) + (float)(1 - distFrac);
		*outDist = distFrac;

		float x2 = (float)(floor(-((((float)Engine::R_TextWidth(text, font) * Engine::R_NormalizedTextScale(font, scale * distScale)) * 0.5) - *x) + 0.5));

		__asm {
			frsp x2, x2
		}

		*x = x2;
		*y = (float)(floor(*y + 0.5));
	}
}

void ESPMenu::Init() {
	SetParentSubmenu<VisualMenu>();
	SetName("ESP");

	addOption(ToggleOption("Draw Enemies")
		.addToggle(vars.bDrawEnemies).canBeSaved("ESP")
		.addTooltip("Draws the ESP options for enemies."));

	addOption(ToggleOption("Draw Friendlies")
		.addToggle(vars.bDrawFriendlies).canBeSaved("ESP")
		.addTooltip("Draws the ESP options for friendlies."));

	addOption(ScrollOption<int>(TOGGLE, "Draw Box")
		.addScroll(vars.iDrawBoxSelection, 0, NUMOF(Box) - 1, Box)
		.addToggle(vars.bDrawBox).canBeSaved("ESP")
		.addTooltip("Draws a box."));

	addOption(ToggleOption("Draw Name")
		.addToggle(vars.bDrawNames)
		.addFunction(PatchGameNames).canBeSaved("ESP")
		.addTooltip("Draws names."));

	addOption(ToggleOption("Draw Distance")
		.addToggle(vars.bDrawDistance)
		.addFunction(PatchGameNames).canBeSaved("ESP")
		.addTooltip("Draws the distance."));

	addOption(ToggleOption("Draw Bones")
		.addToggle(vars.bDrawBones).canBeSaved("ESP")
		.addTooltip("Draws bones."));

	addOption(ScrollOption<int>(TOGGLE, "Draw Snaplines")
		.addScroll(vars.iDrawSnaplinesSelection, 0, NUMOF(Snaplines) - 1, Snaplines)
		.addToggle(vars.bDrawSnaplines).canBeSaved("ESP")
		.addTooltip("Draws snaplines."));

	vars.DrawBoxFriendliesColor = Color(0x00d43fFF);
	vars.DrawBoxEnemiesColor = Color(0xa03940FF);
	vars.DrawBoxAimbotTargetColor = Color(0xa8a828FF);

	vars.DrawNameFriendliesColor = Color(0xFFFFFFFF);
	vars.DrawNameEnemiesColor = Color(0xFFFFFFFF);
	vars.DrawNameAimbotTargetColor = Color(0xFFFFFFFF);

	vars.DrawDistanceFriendliesColor = Color(0xFFFFFFFF);
	vars.DrawDistanceEnemiesColor = Color(0xFFFFFFFF);
	vars.DrawDistanceAimbotTargetColor = Color(0xFFFFFFFF);

	vars.DrawBonesFriendliesColor = Color(0x1ddbc2FF);
	vars.DrawBonesEnemiesColor = Color(0x1ddbc2FF);
	vars.DrawBonesAimbotTargetColor = Color(0xa8a828FF);

	vars.DrawSnaplinesFriendliesColor = Color(0x00d43fFF);
	vars.DrawSnaplinesEnemiesColor = Color(0xa03940FF);
	vars.DrawSnaplinesAimbotTargetColor = Color(0xa8a828FF);
}

/*Update once when submenu is opened*/
void ESPMenu::UpdateOnce() {}

/*Update while submenu is active*/
void ESPMenu::Update() {}

/*Background update*/
void ESPMenu::FeatureUpdate() {
	if (Engine::InGame()) {
		for (int i = 0; i < Engine::GetServerInfo()->iMaxClients; i++) {
			if (i == Engine::GetCG()->iClientNumber) continue;

			if (Engine::IsAlive(i, false)) {
				if ((vars.bDrawFriendlies && Engine::IsFriend(i)) || (vars.bDrawEnemies && !Engine::IsFriend(i))) {
					auto entity = Engine::GetEntityPtr();
					auto clientInfo = Engine::GetCG()->ClientInfo[i];
					auto isFriend = Engine::IsFriend(i);

					if (vars.bDrawBox) {
						if (vars.iDrawBoxSelection == 0) {
							// 2d
							auto position = GetPositioning(i);
							bool isFriend = Engine::IsFriend(i);

							Color color = Color(0xFFFFFFFF);
							if (vars.bDrawFriendlies && isFriend)
								color = vars.DrawBoxFriendliesColor;
							else if (vars.bDrawEnemies && !isFriend)
								color = vars.DrawBoxEnemiesColor;

							if (AimbotMenuVars::vars.bShowAimbotTarget && i == pGame.iAimbotTarget) {
								color = vars.DrawBoxAimbotTargetColor;
							}

							Vector3<float> helmet, origin;
							if (Engine::WorldToScreen(position.vHelmet, &helmet) && Engine::WorldToScreen(position.vOrigin, &origin)) {
								float width = fabs((helmet.Y - origin.Y) / 4);

								pRenderer.DrawLine(origin.X - width, origin.Y, origin.X + width, origin.Y, 1, color, pRenderer.Materials.white);
								pRenderer.DrawLine(origin.X - width, helmet.Y, origin.X + width, helmet.Y, 1, color, pRenderer.Materials.white);
								pRenderer.DrawLine(origin.X - width, origin.Y, origin.X - width, helmet.Y, 1, color, pRenderer.Materials.white);
								pRenderer.DrawLine(origin.X + width, helmet.Y, origin.X + width, origin.Y, 1, color, pRenderer.Materials.white);
							}
						}

						if (vars.iDrawBoxSelection == 1) {
							// 3d
							auto position = GetPositioning(i);
							bool isFriend = Engine::IsFriend(i);
							float height = 60.f;
							float gap = 15.f;

							Color color = Color(0xFFFFFFFF);
							if (vars.bDrawFriendlies && isFriend)
								color = vars.DrawBoxFriendliesColor;
							else if (vars.bDrawEnemies && !isFriend)
								color = vars.DrawBoxEnemiesColor;

							if (i == pGame.iAimbotTarget) {
								color = vars.DrawBoxAimbotTargetColor;
							}

							DrawESPLine(position.vOrigin, -gap, -gap, 0, gap, -gap, 0, color);
							DrawESPLine(position.vOrigin, -gap, -gap, 0, -gap, gap, 0, color);
							DrawESPLine(position.vOrigin, gap, gap, 0, gap, -gap, 0, color);
							DrawESPLine(position.vOrigin, gap, gap, 0, -gap, gap, 0, color);
							DrawESPLine(position.vOrigin, -gap, -gap, 0, -gap, -gap, height, color);
							DrawESPLine(position.vOrigin, -gap, gap, 0, -gap, gap, height, color);
							DrawESPLine(position.vOrigin, gap, -gap, 0, gap, -gap, height, color);
							DrawESPLine(position.vOrigin, gap, gap, 0, gap, gap, height, color);
							DrawESPLine(position.vOrigin, -gap, -gap, height, gap, -gap, height, color);
							DrawESPLine(position.vOrigin, -gap, -gap, height, -gap, gap, height, color);
							DrawESPLine(position.vOrigin, gap, gap, height, gap, -gap, height, color);
							DrawESPLine(position.vOrigin, gap, gap, height, -gap, gap, height, color);
						}

						if (vars.iDrawBoxSelection == 2) {
							// filled
							auto position = GetPositioning(i);
							bool isFriend = Engine::IsFriend(i);

							Color color = Color(0xFFFFFFFF);
							if (vars.bDrawFriendlies && isFriend)
								color = vars.DrawBoxFriendliesColor;
							else if (vars.bDrawEnemies && !isFriend)
								color = vars.DrawBoxEnemiesColor;

							if (i == pGame.iAimbotTarget) {
								color = vars.DrawBoxAimbotTargetColor;
							}

							Vector3<float> helmet, origin;
							if (Engine::WorldToScreen(position.vHelmet, &helmet) && Engine::WorldToScreen(position.vOrigin, &origin)) {
								float width = fabs((helmet.Y - origin.Y) / 4);

								pRenderer.DrawRect(origin.X - width, helmet.Y, width * 2 - 1, origin.Y - helmet.Y, JustifyLeft, color.WithOpacity(80));
								pRenderer.DrawLine(origin.X - width, origin.Y, origin.X + width, origin.Y, 1, color, pRenderer.Materials.white);
								pRenderer.DrawLine(origin.X - width, helmet.Y, origin.X + width, helmet.Y, 1, color, pRenderer.Materials.white);
								pRenderer.DrawLine(origin.X - width, origin.Y, origin.X - width, helmet.Y, 1, color, pRenderer.Materials.white);
								pRenderer.DrawLine(origin.X + width, helmet.Y, origin.X + width, origin.Y, 1, color, pRenderer.Materials.white);
							}
						}

						if (vars.iDrawBoxSelection == 3) {
							// corners
							auto position = GetPositioning(i);
							bool isFriend = Engine::IsFriend(i);

							Color color = Color(0xFFFFFFFF);
							if (vars.bDrawFriendlies && isFriend)
								color = vars.DrawBoxFriendliesColor;
							else if (vars.bDrawEnemies && !isFriend)
								color = vars.DrawBoxEnemiesColor;

							if (i == pGame.iAimbotTarget) {
								color = vars.DrawBoxAimbotTargetColor;
							}

							Vector3<float> origin, head;
							position.vOrigin.Z -= 5.f;
							if (Engine::WorldToScreen(position.vOrigin, &origin) && Engine::WorldToScreen(position.vHead, &head)) {
								float height = origin.Y - head.Y;
								float width = Engine::GetEntity(i).bStance & 8 ? height / 0.9f : height / 1.95f;

								pRenderer.DrawRect((origin.X - (width / 2)), (origin.Y - height), (width / 4), 1, JustifyLeft, color);
								pRenderer.DrawRect((origin.X - (width / 2)), origin.Y, (width / 4), 1, JustifyLeft, color);
								pRenderer.DrawRect((origin.X - (width / 2)), (origin.Y - height), 1, (width / 4), JustifyLeft, color);
								pRenderer.DrawRect((origin.X + (width / 2)), (origin.Y - height), 1, (width / 4), JustifyLeft, color);

								pRenderer.DrawRect((origin.X + ((width / 2) - (width / 4))), (origin.Y - height), (width / 4), 1, JustifyLeft, color);
								pRenderer.DrawRect((origin.X + ((width / 2) - (width / 4))), origin.Y, (width / 4) + 1, 1, JustifyLeft, color);
								pRenderer.DrawRect((origin.X - (width / 2)), (origin.Y - (width / 4)), 1, (width / 4), JustifyLeft, color);
								pRenderer.DrawRect((origin.X + (width / 2)), (origin.Y - (width / 4)), 1, (width / 4), JustifyLeft, color);
							}
						}
					}

					if (vars.bDrawBones) {
						bool isFriend = Engine::IsFriend(i);

						Color color = Color(0xFFFFFFFF);
						if (vars.bDrawFriendlies && isFriend)
							color = vars.DrawBonesFriendliesColor;
						else if (vars.bDrawEnemies && !isFriend)
							color = vars.DrawBonesEnemiesColor;

						if (AimbotMenuVars::vars.bShowAimbotTarget && i == pGame.iAimbotTarget) {
							color = vars.DrawBonesAimbotTargetColor;
						}

						DrawBoneOnPlayer(i, "j_knee_le", "pelvis", color);
						DrawBoneOnPlayer(i, "j_elbow_ri", "j_wrist_ri", color);
						DrawBoneOnPlayer(i, "j_neck", "j_elbow_ri", color);
						DrawBoneOnPlayer(i, "j_ankle_ri", "j_knee_ri", color);
						DrawBoneOnPlayer(i, "j_elbow_le", "j_wrist_le", color);
						DrawBoneOnPlayer(i, "j_ankle_le", "j_knee_le", color);
						DrawBoneOnPlayer(i, "j_knee_ri", "pelvis", color);
						DrawBoneOnPlayer(i, "pelvis", "j_neck", color);
						DrawBoneOnPlayer(i, "j_neck", "j_elbow_le", color);
						DrawBoneOnPlayer(i, "j_neck", "j_head", color);
						DrawBoneOnPlayer(i, "j_head", "j_helmet", color);
					}

					if (vars.bDrawSnaplines) {
						Vector3<float> screenPosition;
						bool isFriend = Engine::IsFriend(i);

						if (Engine::WorldToScreen(Engine::GetTagPosition(i, "j_head"), &screenPosition)) {
							Color color = Color(0xFFFFFFFF);
							if (vars.bDrawFriendlies && isFriend)
								color = vars.DrawSnaplinesFriendliesColor;
							else if (vars.bDrawEnemies && !isFriend)
								color = vars.DrawSnaplinesEnemiesColor;

							if (AimbotMenuVars::vars.bShowAimbotTarget && i == pGame.iAimbotTarget) {
								color = vars.DrawSnaplinesAimbotTargetColor;
							}

							float timesAmount = 0.0f;
							switch (vars.iDrawSnaplinesSelection) {
							case 0: timesAmount = 0.0f; break;
							case 1: timesAmount = 1.0f; break;
							case 2: timesAmount = 2.0f; break;
							}

							auto center = Engine::GetCenter();
							pRenderer.DrawLine(center.X, center.Y * timesAmount, screenPosition.X, screenPosition.Y, 1.25f, color, pRenderer.Materials.white);
						}
					}

					if (vars.bDrawNames) {
						auto headPos = Engine::GetTagPosition(i, "j_head");
						auto feetPos = entity[i].vOrigin;

						Vector3<float> headPosOut, feetPosOut;
						if (Engine::WorldToScreen(headPos, &headPosOut) && Engine::WorldToScreen(feetPos, &feetPosOut)) {
							auto headPosBackup = headPosOut;
							auto feetPosBackup = feetPosOut;
							float distanceOut = 0.f;

							Color color = Color(0xFFFFFFFF);
							if (vars.bDrawFriendlies && isFriend)
								color = vars.DrawNameFriendliesColor;
							else if (vars.bDrawEnemies && !isFriend)
								color = vars.DrawNameEnemiesColor;

							if (AimbotMenuVars::vars.bShowAimbotTarget && i == pGame.iAimbotTarget) {
								color = vars.DrawNameAimbotTargetColor;
							}

							FixTextForDistance(clientInfo.szName, &headPosOut.X, &headPosOut.Y, pRenderer.Fonts.smallFont, 1, feetPos, &distanceOut);
							auto x = pRenderer.CalculateXValueWithAlign(feetPosBackup.X, clientInfo.szName, pRenderer.Fonts.smallFont, 0.5f, JustifyCenter);

							if (vars.bDrawDistance) {
								pRenderer.DrawRect(x - 2, headPosOut.Y - 27, (Engine::R_TextWidth(clientInfo.szName, pRenderer.Fonts.smallFont) * 0.5f) + 2, 10, JustifyLeft, Color(0, 0, 0, 150));
								pRenderer.DrawString(clientInfo.szName, x - 1, headPosOut.Y - 16, pRenderer.Fonts.smallFont, 0.5f, color, false, false, JustifyLeft);
							} else {
								pRenderer.DrawRect(x - 2, headPosOut.Y - 16, (Engine::R_TextWidth(clientInfo.szName, pRenderer.Fonts.smallFont) * 0.5f) + 2, 10, JustifyLeft, Color(0, 0, 0, 150));
								pRenderer.DrawString(clientInfo.szName, x - 1, headPosOut.Y - 5, pRenderer.Fonts.smallFont, 0.5f, color, false, false, JustifyLeft);
							}
						}
					}

					if (vars.bDrawDistance) {
						auto headPos = Engine::GetTagPosition(i, "j_head");
						auto feetPos = entity[i].vOrigin;

						Vector3<float> headPosOut, feetPosOut;
						if (Engine::WorldToScreen(headPos, &headPosOut) && Engine::WorldToScreen(feetPos, &feetPosOut)) {
							auto headPosBackup = headPosOut;
							auto feetPosBackup = feetPosOut;
							float distanceOut = 0.f;

							Color color = Color(0xFFFFFFFF);
							if (vars.bDrawFriendlies && isFriend)
								color = vars.DrawDistanceFriendliesColor;
							else if (vars.bDrawEnemies && !isFriend)
								color = vars.DrawDistanceEnemiesColor;

							if (AimbotMenuVars::vars.bShowAimbotTarget && i == pGame.iAimbotTarget) {
								color = vars.DrawDistanceAimbotTargetColor;
							}

							char buffer[10];
							_snprintf(buffer, 10, "%.2fm", Engine::GetDistance(Engine::GetEntity(i).vOrigin, Engine::GetEntity(Engine::GetCG()->iClientNumber).vOrigin) * 0.03048f);

							FixTextForDistance(buffer, &headPosOut.X, &headPosOut.Y, pRenderer.Fonts.smallFont, 1, feetPos, &distanceOut);
							auto x = pRenderer.CalculateXValueWithAlign(feetPosBackup.X, buffer, pRenderer.Fonts.smallFont, 0.5f, JustifyCenter);

							pRenderer.DrawRect(x - 1, headPosOut.Y - 16, (Engine::R_TextWidth(buffer, pRenderer.Fonts.smallFont) * 0.5f) + 2, 10, JustifyLeft, Color(0, 0, 0, 150));
							pRenderer.DrawString(buffer, x, headPosOut.Y - 5, pRenderer.Fonts.smallFont, 0.5f, color, false, false, JustifyLeft);
						}
					}
				}
			}
		}
	}
}

/*Singleton*/
ESPMenu* _instance;
ESPMenu* ESPMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new ESPMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
ESPMenu::~ESPMenu() { delete _instance; }