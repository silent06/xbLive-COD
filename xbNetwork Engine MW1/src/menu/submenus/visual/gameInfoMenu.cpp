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

			/*Maps*/
		case 0xba0c5735:
			return "Backlot";
		case 0x1c7a2bb5:
			return "Bloc";
		case 0x27977ca:
			return "Bog";
		case 0xdaa498c2:
			return "Wet Work";
		case 0xf15a990e:
			return "District";
		case 0x306bc795:
			return "Ambush";
		case 0xf1ae99c6:
			return "Countdown";
		case 0xb3e38927:
			return "Crash";
		case 0x1f575253:
			return "Winter Crash";
		case 0x32857117:
			return "Crossfire";
		case 0x82b4fb65:
			return "Downpour";
		case 0xdd9b0888:
			return "Overgrown";
		case 0x16e8e7e0:
			return "Pipeline";
		case 0x28a068e5:
			return "Shipment";
		case 0x5af4f341:
			return "Showdown";
		case 0x9a01b754:
			return "Strike";
		case 0x7258b812:
			return "Vacant";
		case 0x3abf2add:
			return "Broadcast";
		case 0x3f07b71f:
			return "Chinatown";
		case 0x73dad946:
			return "Creek";
		case 0x764eca42:
			return "Killhouse";

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
		if (Engine::GetDvar<const char*>(GetPatch(xbLive.pPatches->MW1.ui_mapname))) {
			char buffer[100];
			_snprintf(buffer, 100, "Map: %s", GetReadableName(Engine::GetDvar<const char*>(GetPatch(xbLive.pPatches->MW1.ui_mapname))));
			pRenderer.DrawTopRight(buffer, displayIndex);
			displayIndex++;
		}
	}

	if (vars.bGameMode) {
		auto serverInfo = Engine::GetServerInfo();
		if (serverInfo) {
			if (serverInfo->szGametype && strlen(serverInfo->szGametype) > 1) {
				char buffer[100];
				_snprintf(buffer, 100, "Game Mode: %s", GetReadableName(Engine::GetServerInfo()->szGametype));
				pRenderer.DrawTopRight(buffer, displayIndex);
				displayIndex++;
			}
		}
	}

	if (vars.bHost) {
		auto serverInfo = Engine::GetServerInfo();
		if (serverInfo) {
			if (serverInfo->szHostName && strlen(serverInfo->szHostName) > 1) {
				char buffer[100];
				_snprintf(buffer, 100, "Host: %s", serverInfo->szHostName);
				pRenderer.DrawTopRight(buffer, displayIndex);
				displayIndex++;
			}
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