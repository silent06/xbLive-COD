#include "stdafx.h"
#include "gameInfoMenu.h"
#include "../visualMenu.h"

using namespace GameInfoMenuVars;

namespace GameInfoMenuVars {
	Vars vars;

	const char* GetReadableName(const char* name) {
		DWORD hash = pUtils.Joaat(name);
		switch (hash) {
			/*Game Modes*/
		case 0xdd6f4a20:
			return "Free-For-All";
		case 0xc38032bd:
			return "Team Deathmatch";
		case 0x1148a15e:
			return "Search and Destroy";
		case 0xfc0cca60:
			return "Sabotage";
		case 0xbbf2d511:
			return "Domination";
		case 0x81688a9e:
			return "Headquarters";
		case 0xc7391121:

			/*Maps*/
		case 0xdb8b5580:
			return "Airfield";
		case 0xe2f4a3a5:
			return "Asylum";
		case 0x1a75e95b:
			return "Castle";
		case 0x99f2824d:
			return "Cliffside";
		case 0x1ea61067:
			return "Courtyard";
		case 0x70626767:
			return "Dome";
		case 0x37390a8f:
			return "Downfall";
		case 0x75330191:
			return "Hangar";
		case 0xcd9d44ba:
			return "Makin";
		case 0x9f6c7899:
			return "Outskirts";
		case 0xa42be85b:
			return "Roundhouse";
		case 0x9260edac:
			return "Seelow";
		case 0x99b22f09:
			return "Upheaval";
		case 0xfd66ef50:
			return "Knee Deep";
		case 0xf1a40dbb:
			return "Nightfire";
		case 0xee4d9d2c:
			return "Station";
		case 0x8a34b4a:
			return "Banzai";
		case 0x703f1ebd:
			return "Corrosion";
		case 0x53e91070:
			return "Sub Pens";
		case 0x51c0fda4:
			return "Battery";
		case 0xa9402d85:
			return "Breach";
		case 0x91da4d15:
			return "Revolution";
		default:
			return name;
		}
	}
}

void GameInfoMenu::Init() {
	SetParentSubmenu<VisualMenu>();
	SetName("Game Info");

	addOption(ToggleOption("Engine Name")
		.addToggle(vars.bEngineName).canBeSaved("Game Info")
		.addTooltip("Shows the engine name."));

	addOption(ToggleOption("Target Details")
		.addToggle(vars.bTargetDetails).canBeSaved("Game Info")
		.addTooltip("Shows information on the aimbot target."));

	addOption(ToggleOption("FPS")
		.addToggle(vars.bFPS).canBeSaved("Game Info")
		.addTooltip("Shows your FPS."));

	addOption(ToggleOption("Ping")
		.addToggle(vars.bPing).canBeSaved("Game Info")
		.addTooltip("Shows your ping."));

	addOption(ToggleOption("Screen Resolution")
		.addToggle(vars.bScreenResolution).canBeSaved("Game Info")
		.addTooltip("Shows information about your screen."));

	addOption(ToggleOption("Map")
		.addToggle(vars.bMap).canBeSaved("Game Info")
		.addTooltip("Shows the map name."));

	addOption(ToggleOption("Game Mode")
		.addToggle(vars.bGameMode).canBeSaved("Game Info")
		.addTooltip("Shows the game mode name."));

	addOption(ToggleOption("Host")
		.addToggle(vars.bHost).canBeSaved("Game Info")
		.addTooltip("Shows the game host."));
}

/*Update once when submenu is opened*/
void GameInfoMenu::UpdateOnce() {}

/*Update while submenu is active*/
void GameInfoMenu::Update() {}

/*Background update*/
void GameInfoMenu::FeatureUpdate() {
	int displayIndex = 1;

	if (vars.bEngineName) {
		pRenderer.DrawTopRight("xbLive Engine v1.0a", displayIndex);
		displayIndex++;
	}

	if (vars.bScreenResolution) {
		if (Engine::GetCG()) {
			if (Engine::GetCG()->Refdef.vScale.X) {
				char buffer[75];
				_snprintf(buffer, 75, "Screen Resolution: %i x %i", Engine::GetCG()->Refdef.vScale.X, Engine::GetCG()->Refdef.vScale.Y);
				pRenderer.DrawTopRight(buffer, displayIndex);
				displayIndex++;
			}
		}
	}

	if (vars.bFPS) {
		static int delay = 0;
		static float fps = 0.0f;

		if (pGame.pContext) {
			if (pGame.pContext->fFramesPerSecond != 0.0f) {
				if (GetTickCount() - delay > 2000) {
					delay = GetTickCount();
					fps = pGame.pContext->fFramesPerSecond;
				}

				if (fps > 60.f) fps = 60.f;

				char buffer[20];
				_snprintf(buffer, 20, "FPS: %.0f", fps);
				pRenderer.DrawTopRight(buffer, displayIndex);
				displayIndex++;
			}
		}
	}

	if (vars.bPing) {
		if (Engine::GetCG()) {
			if (Engine::GetCG()->pNextSnap) {
				char buffer[20];
				_snprintf(buffer, 20, "Ping: %ims", Engine::GetCG()->pNextSnap->dwPing);
				pRenderer.DrawTopRight(buffer, displayIndex);
				displayIndex++;
			}
		}
	}

	if (vars.bMap) {
		if (Engine::GetDvar<const char*>(GetPatch(xbLive.pPatches->WAW.ui_mapname))) {
			char buffer[100];
			_snprintf(buffer, 100, "Map: %s", GetReadableName(Engine::GetDvar<const char*>(GetPatch(xbLive.pPatches->WAW.ui_mapname))));
			pRenderer.DrawTopRight(buffer, displayIndex);
			displayIndex++;
		}
	}

	if (vars.bGameMode) {
		if (Engine::GetDvar<const char*>(GetPatch(xbLive.pPatches->WAW.ui_gametype))) {
			char buffer[100];
			_snprintf(buffer, 100, "Game Mode: %s", GetReadableName(Engine::GetDvar<const char*>(GetPatch(xbLive.pPatches->WAW.ui_gametype))));
			pRenderer.DrawTopRight(buffer, displayIndex);
			displayIndex++;
		}
	}

	if (vars.bHost) {
		auto serverInfo = Engine::GetServerInfo();
		if (serverInfo) {
			char buffer[100];
			_snprintf(buffer, 100, "Host: %s", serverInfo->szHostName);
			pRenderer.DrawTopRight(buffer, displayIndex);
			displayIndex++;
		}
	}

	if (Engine::InGame()) {
		if (vars.bTargetDetails) {
			auto cg = Engine::GetCG();
			if (pGame.iAimbotTarget != -1) {
				displayIndex++;
				pRenderer.DrawTopRight("Target Details", displayIndex);
				displayIndex++;

				char nameBuffer[60];
				_snprintf(nameBuffer, 60, "Name: %s", cg->ClientInfo[pGame.iAimbotTarget].szName);
				pRenderer.DrawTopRight(nameBuffer, displayIndex);
				displayIndex++;

				char clientIDBuffer[30];
				_snprintf(clientIDBuffer, 30, "Client ID: %i", pGame.iAimbotTarget);
				pRenderer.DrawTopRight(clientIDBuffer, displayIndex);
				displayIndex++;

				char targetBoneBuffer[60];
				_snprintf(targetBoneBuffer, 60, "Target Bone: %s", pGame.Clients[pGame.iAimbotTarget].pBestTag);
				pRenderer.DrawTopRight(targetBoneBuffer, displayIndex);
				displayIndex++;

				char visibleBuffer[20];
				_snprintf(visibleBuffer, 20, "Visible: %s", pGame.Clients[pGame.iAimbotTarget].bVisible ? "YES" : "NO");
				pRenderer.DrawTopRight(visibleBuffer, displayIndex);
				displayIndex++;

				char distanceBuffer[20];
				_snprintf(distanceBuffer, 20, "Distance: %.2fm", Engine::GetDistance(Engine::GetEntity(pGame.iAimbotTarget).vOrigin, Engine::GetEntity(cg->iClientNumber).vOrigin) * 0.03048f);
				pRenderer.DrawTopRight(distanceBuffer, displayIndex);
				displayIndex++;

				char stanceBuffer[30];
				_snprintf(stanceBuffer, 30, "Stance: %s", Engine::GetEntity(pGame.iAimbotTarget).bStance & 0x08 ? "Prone" : Engine::GetEntity(pGame.iAimbotTarget).bStance & 0x04 ? "Crouched" : "Standing");
				pRenderer.DrawTopRight(stanceBuffer, displayIndex);
				displayIndex++;
			}
		}
	}
}

/*Singleton*/
GameInfoMenu* _instance;
GameInfoMenu* GameInfoMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new GameInfoMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
GameInfoMenu::~GameInfoMenu() { delete _instance; }