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
			case 0xc38032bd:
				return "Team Deathmatch";
			case 0xdd6f4a20:
				return "Free-For-All";
			case 0xbbf2d511:
				return "Domination";
			case 0xf9fc3457:
				return "Demolition";
			case 0x450ba8b6:
				return "Kill Confirmed";
			case 0x81688a9e:
				return "Hardpoint";
			case 0x671558be:
				return "Headquarters";
			case 0xc7391121:
				return "Capture the Flag";
			case 0x1148a15e:
				return "Search and Destroy";
			case 0x91b8805:
				return "One Flag - Capture the Flag";
			case 0x439a2ae5:
				return "Gun Game";
			case 0x71735b69:
				return "One in the Chamber";
			case 0x58d19aee:
				return "Sharpshooter";
			case 0xf18eb598:
				return "Sticks and Stones";

				/*Maps*/
			case 0x6f95d497:
				return "Array";
			case 0x32d6e25c:
				return "Crisis";
			case 0x7a1661d8:
				return "Cracked";
			case 0x8acc9a08:
				return "Firing Range";
			case 0x6d95aba1:
				return "Grid";
			case 0xcfd0a56e:
				return "Hanoi";
			case 0x80987d5c:
				return "Havana";
			case 0xe4ed83f1:
				return "Jungle";
			case 0xe1e85fdb:
				return "Launch";
			case 0x1c5aa5b8:
				return "Nuketown";
			case 0xc57eac70:
				return "Radiation";
			case 0x4b70d9be:
				return "Summit";
			case 0xaf9f1788:
				return "Villa";
			case 0x331c719:
				return "WMD";
			case 0x4183734d:
				return "Berlin Wall";
			case 0x8e538828:
				return "Discovery";
			case 0xe99570f8:
				return "Stadium";
			case 0x1e5f085e:
				return "Hotel";
			case 0x4cb1955c:
				return "Hangar 18";
			case 0xe59a7449:
				return "Kowloon";
			case 0xe1d3296b:
				return "Stockpile";
			case 0x91358ca9:
				return "Convoy";
			case 0x501716cb:
				return "Zoo";
			case 0x766a40b5:
				return "Drive-In";

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
			if (Engine::GetCG()->pNextsnap) {
				char buffer[20];
				_snprintf(buffer, 20, "Ping: %ims", Engine::GetCG()->pNextsnap->iPing);
				pRenderer.DrawTopRight(buffer, displayIndex);
				displayIndex++;
			}
		}
	}

	if (vars.bMap) {
		auto serverInfo = Engine::GetServerInfo();
		if (serverInfo) {
			if (serverInfo->szMapname && strlen(serverInfo->szMapname) > 1) {
				char buffer[100];
				_snprintf(buffer, 100, "Map: %s", GetReadableName(serverInfo->szMapname));
				pRenderer.DrawTopRight(buffer, displayIndex);
				displayIndex++;
			}
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
				_snprintf(stanceBuffer, 30, "Stance: %s", Engine::GetEntity(pGame.iAimbotTarget).GetFlags() & 0x08 ? "Prone" : Engine::GetEntity(pGame.iAimbotTarget).GetFlags() & 0x04 ? "Crouched" : "Standing");
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