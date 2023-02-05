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

			/*Maps*/
		case 0x7258b812:
			return "Vacant";
		case 0x946bb9fa:
			return "Trailer Park";
		case 0x9a01b754:
			return "Strike";
		case 0x4696f9de:
			return "Fuel";
		case 0x57b47e3e:
			return "Carnival";
		case 0xfa332518:
			return "Storm";
		case 0xdd9b0888:
			return "Overgrown";
		case 0x9ec299e6:
			return "Salvage";
		case 0xb3e38927:
			return "Crash";
		case 0x89481a25:
			return "Bailout";
		case 0x17d421a1:
			return "Wasteland";
		case 0xae4ce99e:
			return "Underpass";
		case 0xba5bacee:
			return "Terminal";
		case 0xd00ebdf6:
			return "Sub Base";
		case 0x571946fa:
			return "Skidrow";
		case 0xc3733e99:
			return "Scrapyard";
		case 0x43ed45ce:
			return "Rust";
		case 0x3bf87ff5:
			return "Rundown";
		case 0x34419d9f:
			return "Quarry";
		case 0x804a3946:
			return "Karachi";
		case 0xd3ff8b89:
			return "Invasion";
		case 0x8db241c5:
			return "Highrise";
		case 0x87482b4d:
			return "Favela";
		case 0xdbd51f0f:
			return "Estate";
		case 0x810c1771:
			return "Derail";
		case 0x3f028392:
			return "Afghan";
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
		pRenderer.DrawTopRight("xbLive Engine v1.1b", displayIndex);
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
			if (Engine::GetCG()->pSnap) {
				char buffer[20];
				_snprintf(buffer, 20, "Ping: %ims", Engine::GetCG()->pSnap->dwPing);
				pRenderer.DrawTopRight(buffer, displayIndex);
				displayIndex++;
			}
		}
	}

	if (vars.bMap) {
		if (Engine::GetDvar<const char*>(GetPatch(xbLive.pPatches->MW2.ui_mapname))) {
			char buffer[100];
			_snprintf(buffer, 100, "Map: %s", GetReadableName(Engine::GetDvar<const char*>(GetPatch(xbLive.pPatches->MW2.ui_mapname))));
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