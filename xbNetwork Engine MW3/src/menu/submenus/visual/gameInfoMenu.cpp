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
		case 0xfa24b367:
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
			return "Capture the Flag";
		case 0x7688fc55:
			return "Demolition";
		case 0x450ba8b6:
			return "Kill Confirmed";
		case 0xa2198c58:
			return "Team Defender";
		case 0x25fe0213:
			return "Drop Zone";
		case 0x14e3dbb6:
			return "Team Juggernaut";
		case 0xa86abbdb:
			return "Juggernaut";
		case 0x439a2ae5:
			return "Gun Game";
		case 0x19a2cad5:
			return "Infected";
		case 0x71735b69:
			return "One in the Chamber";

			/*Maps*/
		case 0x84a165e7:
			return "Lockdown";
		case 0xd738122c:
			return "Bootleg";
		case 0xcaa6476:
			return "Mission";
		case 0x3bf2559:
			return "Carbon";
		case 0x70626767:
			return "Dome";
		case 0x896275f4:
			return "Downturn";
		case 0xc0330651:
			return "Hardhat";
		case 0x4240e6c9:
			return "Interchange";
		case 0x6da8a9c0:
			return "Fallen";
		case 0xd1a780c2:
			return "Bakaara";
		case 0x53bc0e83:
			return "Resistance";
		case 0xadce8f20:
			return "Arkaden";
		case 0x7cbdca36:
			return "Outpost";
		case 0x7556ddbb:
			return "Seatown";
		case 0x88895841:
			return "Underground";
		case 0x1085ab50:
			return "Village";
		case 0xdf58f9d1:
			return "Aground";
		case 0xf85e32d9:
			return "Aqueduct";
		case 0x8d9a6db1:
			return "Foundation";
		case 0x94be79ef:
			return "Getaway";
		case 0xa0283854:
			return "Piazza";
		case 0x656ca4d2:
			return "Sanctuary";
		case 0x7a68b8a2:
			return "Black Box";
		case 0xc12358b5:
			return "Overwatch";
		case 0x859018bf:
			return "Liberation";
		case 0xb29bb927:
			return "Oasis";
		case 0x4be89d05:
			return "Lookout";
		case 0xf88f4847:
			return "Terminal";
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
		char buffer[30];
		_snprintf(buffer, 30, "xbLive Engine v1.1b");
		pRenderer.DrawTopRight(buffer, displayIndex);
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

				float cachedFps = fps;
				if (Engine::InGame() && cachedFps != 0.f) cachedFps /= 2.f;
				if (cachedFps > 60.f) cachedFps = 60.f;

				char buffer[20];
				_snprintf(buffer, 20, "FPS: %.0f", cachedFps);
				pRenderer.DrawTopRight(buffer, displayIndex);
				displayIndex++;
			}
		}
	}

	if (vars.bPing) {
		if (Engine::GetCG()) {
			if (Engine::GetCG()->GetSnapshot()) {
				char buffer[20];
				_snprintf(buffer, 20, "Ping: %ims", Engine::GetCG()->GetSnapshot()->dwPing);
				pRenderer.DrawTopRight(buffer, displayIndex);
				displayIndex++;
			}
		}
	}

	if (vars.bMap) {
		if (Engine::GetDvar<const char*>(GetPatch(xbLive.pPatches->MW3.ui_mapname))) {
			char buffer[100];
			_snprintf(buffer, 100, "Map: %s", GetReadableName(Engine::GetDvar<const char*>(GetPatch(xbLive.pPatches->MW3.ui_mapname))));
			pRenderer.DrawTopRight(buffer, displayIndex);
			displayIndex++;
		}
	}

	if (vars.bGameMode) {
		auto serverInfo = Engine::GetServerInfo();
		if (serverInfo) {
			if (serverInfo->szGametype && strlen(serverInfo->szGametype) > 1) {
				char buffer[100];
				_snprintf(buffer, 100, "Game Mode: %s", GetReadableName(serverInfo->szGametype));
				pRenderer.DrawTopRight(buffer, displayIndex);
				displayIndex++;
			}
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
				_snprintf(stanceBuffer, 30, "Stance: %s", Engine::GetEntity(pGame.iAimbotTarget).iFlags & 0x08 ? "Prone" : Engine::GetEntity(pGame.iAimbotTarget).iFlags & 0x04 ? "Crouched" : "Standing");
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