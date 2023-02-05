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
		case 0xc38032bd: return "Team Deathmatch";
		case 0xdd6f4a20: return "Free-For-All";
		case 0xbbf2d511: return "Domination";
		case 0xf9fc3457: return "Demolition";
		case 0x450ba8b6: return "Kill Confirmed";
		case 0x81688a9e: return "Hardpoint";
		case 0x671558be: return "Headquarters";
		case 0xc7391121: return "Capture the Flag";
		case 0x1148a15e: return "Search and Destroy";
		case 0x91b8805: return "One Flag - Capture the Flag";
		case 0x439a2ae5: return "Gun Game";
		case 0x71735b69: return "One in the Chamber";
		case 0x58d19aee: return "Sharpshooter";
		case 0xf18eb598: return "Sticks and Stones";

			/*Maps*/
		case 0x16fdac16: return "Aftermath";
		case 0xfca88303: return "Drone";
		case 0xc566bbcb: return "NUKETOWN 2025";
		case 0x5d64fd4c: return "Carrier";
		case 0xafaeea40: return "Cargo";
		case 0xbccb9f75: return "Express";
		case 0x171c8345: return "Hijacked";
		case 0xdbf4118d: return "Meltdown";
		case 0x6e664194: return "Plaza";
		case 0xdf49f742: return "Overflow";
		case 0xff3f3dc9: return "Raid";
		case 0x55eeaa5: return "Slums";
		case 0xd050ef7b: return "Yemen";
		case 0x40affb51: return "Turbine";
		case 0x1366fa07: return "Standoff";
		case 0x2a39acf4: return "Downhill";
		case 0x5893165d: return "Hydro";
		case 0x526a7ab7: return "Mirage";
		case 0xbea87777: return "Skate";
		case 0x44243bf8: return "Core";
		case 0xcbc6597f: return "Magma";
		case 0xa824f57: return "Studio";
		case 0x896f0f4b: return "Vertigo";
		case 0x7f882613: return "Bridge";
		case 0xb2796183: return "Cove";
		case 0x26035e1b: return "Rush";
		case 0x633ef93e: return "Uplink";
		case 0xfd0e4632: return "Dig";
		case 0xd0b2566e: return "Frost";
		case 0xddc7d5d6: return "Pod";
		case 0x2f63fa7d: return "Takeoff";
		default: return name;
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
			if (Engine::GetCG()->pSnap) {
				char buffer[20];
				_snprintf(buffer, 20, "Ping: %ims", Engine::GetCG()->pSnap->iPing);
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
				_snprintf(buffer, 100, "Game Mode: %s", GetReadableName(serverInfo->szGametype));
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