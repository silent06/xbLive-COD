#include "stdafx.h"
#include "compassMenu.h"
#include "../visualMenu.h"

using namespace CompassMenuVars;

namespace CompassMenuVars {
	Vars vars;

	void DisableEngineCompass() {
		static DWORD lastHash = 0;

		if (!vars.bDisableEngineCompass) {
			*(DWORD*)GetPatch(xbLive.pPatches->MW2.Compass[0]) = 0x48143795; // Compass ownerdraw had width or height of 0
			*(DWORD*)GetPatch(xbLive.pPatches->MW2.Compass[1]) = 0x4BFF3A4D; // Scan line border
			*(DWORD*)GetPatch(xbLive.pPatches->MW2.Compass[2]) = 0x4BFDCCE9; // CG_CompassDrawTickertape
			*(DWORD*)GetPatch(xbLive.pPatches->MW2.Compass[3]) = 0x4BFDCCB1; // CG_CompassDrawTickertape
			*(DWORD*)GetPatch(xbLive.pPatches->MW2.Compass[4]) = 0x4BFDBE21; // CG_CompassDrawPlayerMap
			*(DWORD*)GetPatch(xbLive.pPatches->MW2.Compass[5]) = 0x4BFDC3F9; // CG_CompassDrawPlayer
			*(DWORD*)GetPatch(xbLive.pPatches->MW2.Compass[6]) = 0x4BFDD241; // CG_CompassDrawCrates
			*(DWORD*)GetPatch(xbLive.pPatches->MW2.Compass[7]) = 0x4BFDE5CD; // CG_CompassDrawFriendlies
			*(DWORD*)GetPatch(xbLive.pPatches->MW2.Compass[8]) = 0x4BFDEC21; // CG_CompassDrawEnemies
			*(DWORD*)GetPatch(xbLive.pPatches->MW2.Compass[9]) = 0x4BFDEFC1; // CG_CompassDrawTurrets
			*(DWORD*)GetPatch(xbLive.pPatches->MW2.Compass[10]) = 0x4BFDFAC5; // CG_CompassDrawMissiles
			*(DWORD*)GetPatch(xbLive.pPatches->MW2.Compass[11]) = 0x48205BD1; // CG_CompassDrawHelicopter
		} else {
			*(DWORD*)GetPatch(xbLive.pPatches->MW2.Compass[0]) = 0x60000000; // Compass ownerdraw had width or height of 0
			*(DWORD*)GetPatch(xbLive.pPatches->MW2.Compass[1]) = 0x60000000; // Scan line border
			*(DWORD*)GetPatch(xbLive.pPatches->MW2.Compass[2]) = 0x60000000; // CG_CompassDrawTickertape
			*(DWORD*)GetPatch(xbLive.pPatches->MW2.Compass[3]) = 0x60000000; // CG_CompassDrawTickertape
			*(DWORD*)GetPatch(xbLive.pPatches->MW2.Compass[4]) = 0x60000000; // CG_CompassDrawPlayerMap
			*(DWORD*)GetPatch(xbLive.pPatches->MW2.Compass[5]) = 0x60000000; // CG_CompassDrawPlayer
			*(DWORD*)GetPatch(xbLive.pPatches->MW2.Compass[6]) = 0x60000000; // CG_CompassDrawCrates
			*(DWORD*)GetPatch(xbLive.pPatches->MW2.Compass[7]) = 0x60000000; // CG_CompassDrawFriendlies
			*(DWORD*)GetPatch(xbLive.pPatches->MW2.Compass[8]) = 0x60000000; // CG_CompassDrawEnemies
			*(DWORD*)GetPatch(xbLive.pPatches->MW2.Compass[9]) = 0x60000000; // CG_CompassDrawTurrets
			*(DWORD*)GetPatch(xbLive.pPatches->MW2.Compass[10]) = 0x60000000; // CG_CompassDrawMissiles
			*(DWORD*)GetPatch(xbLive.pPatches->MW2.Compass[11]) = 0x60000000; // CG_CompassDrawHelicopter

			if (lastHash != pUtils.Joaat(Engine::GetDvar<const char*>(GetPatch(xbLive.pPatches->MW2.ui_mapname)))) {
				lastHash = pUtils.Joaat(Engine::GetDvar<const char*>(GetPatch(xbLive.pPatches->MW2.ui_mapname)));
				Engine::SetDvar(GetPatch(xbLive.pPatches->MW2.compassMaxRange), Engine::GetDvar<float>(GetPatch(xbLive.pPatches->MW2.compassMaxRange)) * 1.5f);
			}
		}
	}
}

void CompassMenu::Init() {
	SetParentSubmenu<VisualMenu>();
	SetName("Compass");

	addOption(ToggleOption("Disable Engine Compass")
		.addToggle(vars.bDisableEngineCompass)
		.addFunction(DisableEngineCompass).canBeSaved("Compass")
		.addTooltip("Disables the engines compass."));

	addOption(ToggleOption("Draw Custom Compass")
		.addToggle(vars.bDrawCustomCompass).canBeSaved("Compass")
		.addTooltip("Draws a custom compass."));

	addOption(ToggleOption("Custom Compass Draw Outline")
		.addToggle(vars.bCustomCompassDrawOutline).canBeSaved("Compass")
		.addTooltip("Draws an outline around the custom compass."));

	addOption(NumberOption<float>(SCROLL, "Custom Compass Scale")
		.addNumber(vars.fCustomCompassScale, "%.0f", 1.f).addMin(0.f).addMax(500.f).setScrollSpeed(20).canBeSaved("Compass")
		.addTooltip("Scales the custom compass."));

	vars.fCustomCompassScale = 175.f;
}

/*Update once when submenu is opened*/
void CompassMenu::UpdateOnce() {}

/*Update while submenu is active*/
void CompassMenu::Update() {}

/*Background update*/
void CompassMenu::FeatureUpdate() {
	if (Engine::InGame()) {
		if (vars.bDrawCustomCompass) {
			auto currentMenu = Invoke::Call<const char*>(GetPatch(xbLive.pPatches->MW2.UI_GetTopActiveMenuName), 0);
			if (!currentMenu || (strcmp(currentMenu, "scoreboard") && strcmp(currentMenu, "class"))) {
				auto center = Engine::GetCenter();

				RectDef parent, rect;
				parent.vPosition.X = 6.f;
				parent.vPosition.Y = 6.f;
				parent.vScale.X = vars.fCustomCompassScale;
				parent.vScale.Y = vars.fCustomCompassScale;
				parent.iHorzAlign = 0x08080000;

				rect.vPosition.X = 6.f;
				rect.vPosition.Y = 6.f;
				rect.vScale.X = vars.fCustomCompassScale;
				rect.vScale.Y = vars.fCustomCompassScale;
				rect.iHorzAlign = 0x0808c000;

				Engine::CG_CompassDrawPlayerMap(0, COMPASS_TYPE_PARTIAL, &parent, &rect, pRenderer.Materials.white, Color(0xFFFFFFFF).GetFloatPtr());

				if (vars.bCustomCompassDrawOutline) {
					float pos[4];
					Engine::CG_CompassCalcDimensions(COMPASS_TYPE_PARTIAL, Engine::GetCG(), &parent, &rect, &pos[0], &pos[1], &pos[2], &pos[3]);

					Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW2.Scr_ApplyRect), GetPatch(xbLive.pPatches->MW2.ScreenPlacement), &pos[0], &pos[1], &pos[2], &pos[3], 8, 8);
					pRenderer.DrawOutlinedRect(pos[0], pos[1], pos[2], pos[3], 2, Color(0, 0, 0, 0), Color(160, 57, 64), true);
				}

				Engine::CG_CompassDrawCrates(0, COMPASS_TYPE_PARTIAL, &parent, &rect, pRenderer.Materials.white, Color(0xFFFFFFFF).GetFloatPtr());
				Engine::CG_CompassDrawPlayer(0, COMPASS_TYPE_PARTIAL, &parent, &rect, pRenderer.Materials.compassping_player, Color(0x17c775FF).GetFloatPtr());
				Engine::CG_CompassDrawFriendlies(0, COMPASS_TYPE_PARTIAL, &parent, &rect, Color(0x3ce886FF).GetFloatPtr());
				Engine::CG_CompassDrawEnemies(0, COMPASS_TYPE_PARTIAL, &parent, &rect, Color(0xa03940FF).GetFloatPtr());
				Engine::CG_CompassDrawTurrets(0, COMPASS_TYPE_PARTIAL, &parent, &rect, Color(0xFFFFFFFF).GetFloatPtr());
				Engine::CG_CompassDrawMissiles(0, COMPASS_TYPE_PARTIAL, &parent, &rect, Color(0xFFFFFFFF).GetFloatPtr());
				Engine::CG_CompassDrawHelicopter(0, &parent, &rect, Color(0xFFFFFFFF).GetFloatPtr());
			}
		}
	}
}

/*Singleton*/
CompassMenu* _instance;
CompassMenu* CompassMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new CompassMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
CompassMenu::~CompassMenu() { delete _instance; }