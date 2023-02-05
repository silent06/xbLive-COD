#include "stdafx.h"
#include "compassMenu.h"
#include "../visualMenu.h"

using namespace CompassMenuVars;

namespace CompassMenuVars {
	Vars vars;

	void DisableEngineCompass() {
		static DWORD lastHash = 0;

		if (!vars.bDisableEngineCompass) {
			*(DWORD*)GetPatch(xbLive.pPatches->MW3.Compass[2]) = 0x48197925; // Compass ownerdraw had width or height of 0
			*(DWORD*)GetPatch(xbLive.pPatches->MW3.Compass[3]) = 0x4BFED0A5; // Scan line border
			*(DWORD*)GetPatch(xbLive.pPatches->MW3.Compass[4]) = 0x4BFD90A9; // CG_CompassDrawTickertape
			*(DWORD*)GetPatch(xbLive.pPatches->MW3.Compass[5]) = 0x4BFD9071; // CG_CompassDrawTickertape
			*(DWORD*)GetPatch(xbLive.pPatches->MW3.Compass[6]) = 0x4BFD7FA9; // CG_CompassDrawPlayerMap
			*(DWORD*)GetPatch(xbLive.pPatches->MW3.Compass[7]) = 0x4BFD8755; // CG_CompassDrawPlayer
			*(DWORD*)GetPatch(xbLive.pPatches->MW3.Compass[8]) = 0x4BFD9601; // CG_CompassDrawCrates
			*(DWORD*)GetPatch(xbLive.pPatches->MW3.Compass[9]) = 0x4BFDADB5; // CG_CompassDrawFriendlies
			*(DWORD*)GetPatch(xbLive.pPatches->MW3.Compass[10]) = 0x4BFDB611; // CG_CompassDrawEnemies
			*(DWORD*)GetPatch(xbLive.pPatches->MW3.Compass[11]) = 0x4BFDBB7D; // CG_CompassDrawTurrets
			*(DWORD*)GetPatch(xbLive.pPatches->MW3.Compass[12]) = 0x4BFDD001; // CG_CompassDrawMissiles
			*(DWORD*)GetPatch(xbLive.pPatches->MW3.Compass[13]) = 0x4827A339; // CG_CompassDrawHelicopter
		} else {
			*(DWORD*)GetPatch(xbLive.pPatches->MW3.Compass[2]) = 0x60000000; // Compass ownerdraw had width or height of 0
			*(DWORD*)GetPatch(xbLive.pPatches->MW3.Compass[3]) = 0x60000000; // Scan line border
			*(DWORD*)GetPatch(xbLive.pPatches->MW3.Compass[4]) = 0x60000000; // CG_CompassDrawTickertape
			*(DWORD*)GetPatch(xbLive.pPatches->MW3.Compass[5]) = 0x60000000; // CG_CompassDrawTickertape
			*(DWORD*)GetPatch(xbLive.pPatches->MW3.Compass[6]) = 0x60000000; // CG_CompassDrawPlayerMap
			*(DWORD*)GetPatch(xbLive.pPatches->MW3.Compass[7]) = 0x60000000; // CG_CompassDrawPlayer
			*(DWORD*)GetPatch(xbLive.pPatches->MW3.Compass[8]) = 0x60000000; // CG_CompassDrawCrates
			*(DWORD*)GetPatch(xbLive.pPatches->MW3.Compass[9]) = 0x60000000; // CG_CompassDrawFriendlies
			*(DWORD*)GetPatch(xbLive.pPatches->MW3.Compass[10]) = 0x60000000; // CG_CompassDrawEnemies
			*(DWORD*)GetPatch(xbLive.pPatches->MW3.Compass[11]) = 0x60000000; // CG_CompassDrawTurrets
			*(DWORD*)GetPatch(xbLive.pPatches->MW3.Compass[12]) = 0x60000000; // CG_CompassDrawMissiles
			*(DWORD*)GetPatch(xbLive.pPatches->MW3.Compass[13]) = 0x60000000; // CG_CompassDrawHelicopter

			if (lastHash != pUtils.Joaat(Engine::GetDvar<const char*>(GetPatch(xbLive.pPatches->MW3.ui_mapname)))) {
				lastHash = pUtils.Joaat(Engine::GetDvar<const char*>(GetPatch(xbLive.pPatches->MW3.ui_mapname)));
				Engine::SetDvar(GetPatch(xbLive.pPatches->MW3.compassMaxRange), Engine::GetDvar<float>(GetPatch(xbLive.pPatches->MW3.compassMaxRange)) * 1.5f);
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
			auto currentMenu = Invoke::Call<const char*>(GetPatch(xbLive.pPatches->MW3.UI_GetTopActiveMenuName), 0);
			if (!currentMenu || (strcmp(currentMenu, "scoreboard") && strcmp(currentMenu, "class"))) {
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
					Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW3.Compass[0]), COMPASS_TYPE_PARTIAL, Engine::GetCG(), &parent, &rect, &pos[0], &pos[1], &pos[2], &pos[3]);

					Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW3.Compass[1]), GetPatch(xbLive.pPatches->MW3.ScreenPlacement), &pos[0], &pos[1], &pos[2], &pos[3], 8, 8);
					pRenderer.DrawOutlinedRect(pos[0], pos[1], pos[2], pos[3], 2, Color(0, 0, 0, 0), Color(160, 57, 64), true);
				}

				Engine::CG_CompassDrawCrates(0, COMPASS_TYPE_PARTIAL, &parent, &rect, pRenderer.Materials.white, Color(0xFFFFFFFF).GetFloatPtr());
				Engine::CG_CompassDrawPlayer(0, COMPASS_TYPE_PARTIAL, &parent, &rect, Color(0x17c775FF).GetFloatPtr());
				Engine::CG_CompassDrawFriendlies(0, COMPASS_TYPE_PARTIAL, &parent, &rect, Color(0x3ce886FF).GetFloatPtr());
				Engine::CG_CompassDrawEnemies(0, COMPASS_TYPE_PARTIAL, &parent, &rect, Color(0xa03940FF).GetFloatPtr());
				Engine::CG_CompassDrawTurrets(0, COMPASS_TYPE_PARTIAL, &parent, &rect, Color(0xFFFFFFFF).GetFloatPtr());
				Engine::CG_CompassDrawMissiles(0, COMPASS_TYPE_PARTIAL, &parent, &rect, Color(0xFFFFFFFF).GetFloatPtr());
				Engine::CG_CompassDrawHelicopter(0, COMPASS_TYPE_PARTIAL, &parent, &rect, Color(0xFFFFFFFF).GetFloatPtr());
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