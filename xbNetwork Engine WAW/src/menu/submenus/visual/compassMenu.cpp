#include "stdafx.h"
#include "compassMenu.h"
#include "../visualMenu.h"

using namespace CompassMenuVars;

namespace CompassMenuVars {
	Vars vars;

	void DisableEngineCompass() {
		static DWORD lastHash = 0;

		if (!vars.bDisableEngineCompass) {
			*(DWORD*)GetPatch(xbLive.pPatches->WAW.Compass[0]) = 0x4BFD7ACD;
			*(DWORD*)GetPatch(xbLive.pPatches->WAW.Compass[1]) = 0x4BFD8591;
			*(DWORD*)GetPatch(xbLive.pPatches->WAW.Compass[2]) = 0x4BFD894D;
			*(DWORD*)GetPatch(xbLive.pPatches->WAW.Compass[3]) = 0x4BFD984D;
			*(DWORD*)GetPatch(xbLive.pPatches->WAW.Compass[4]) = 0x4BFDB195;
			*(DWORD*)GetPatch(xbLive.pPatches->WAW.Compass[5]) = 0x4BFDBDC9;
			*(DWORD*)GetPatch(xbLive.pPatches->WAW.Compass[6]) = 0x4BFDBF59;
			*(DWORD*)GetPatch(xbLive.pPatches->WAW.Compass[7]) = 0x4BFDC64D;
			*(DWORD*)GetPatch(xbLive.pPatches->WAW.Compass[8]) = 0x4BFDCBDD;
			*(DWORD*)GetPatch(xbLive.pPatches->WAW.Compass[9]) = 0x7D8802A6;
			*(DWORD*)GetPatch(xbLive.pPatches->WAW.Compass[10]) = 0x7D8802A6;
			*(DWORD*)GetPatch(xbLive.pPatches->WAW.Compass[11]) = 0x7D8802A6;
			*(DWORD*)GetPatch(xbLive.pPatches->WAW.Compass[12]) = 0x7D8802A6;
			*(DWORD*)GetPatch(xbLive.pPatches->WAW.Compass[13]) = 0x7D8802A6;
		} else {
			*(DWORD*)GetPatch(xbLive.pPatches->WAW.Compass[0]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->WAW.Compass[1]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->WAW.Compass[2]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->WAW.Compass[3]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->WAW.Compass[4]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->WAW.Compass[5]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->WAW.Compass[6]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->WAW.Compass[7]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->WAW.Compass[8]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->WAW.Compass[9]) = 0x4e800020;
			*(DWORD*)GetPatch(xbLive.pPatches->WAW.Compass[10]) = 0x4e800020;
			*(DWORD*)GetPatch(xbLive.pPatches->WAW.Compass[11]) = 0x4e800020;
			*(DWORD*)GetPatch(xbLive.pPatches->WAW.Compass[12]) = 0x4e800020;
			*(DWORD*)GetPatch(xbLive.pPatches->WAW.Compass[13]) = 0x4e800020;

			if (lastHash != pUtils.Joaat(Engine::GetDvar<const char*>(GetPatch(xbLive.pPatches->WAW.ui_mapname)))) {
				lastHash = pUtils.Joaat(Engine::GetDvar<const char*>(GetPatch(xbLive.pPatches->WAW.ui_mapname)));
				Engine::SetDvar(GetPatch(xbLive.pPatches->WAW.compassMaxRange), Engine::GetDvar<float>(GetPatch(xbLive.pPatches->WAW.compassMaxRange)) * 1.5f);
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
			auto currentMenu = Invoke::Call<const char*>(GetPatch(xbLive.pPatches->WAW.UI_GetTopActiveMenuName), 0);
			if (!currentMenu || (strcmp(currentMenu, "scoreboard") && strcmp(currentMenu, "class"))) {
				auto center = Engine::GetCenter();

				RectDef parent, rect;
				parent.vPosition.X = 0.f;
				parent.vPosition.Y = 0.f;
				parent.vScale.X = vars.fCustomCompassScale;
				parent.vScale.Y = vars.fCustomCompassScale;
				parent.iHorzAlign = 1;
				parent.iVertAlign = 1;

				rect.vPosition.X = 0.f;
				rect.vPosition.Y = 0.f;
				rect.vScale.X = vars.fCustomCompassScale;
				rect.vScale.Y = vars.fCustomCompassScale;
				rect.iHorzAlign = 1;
				rect.iVertAlign = 1;

				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->WAW.Compass[14]), 0, COMPASS_TYPE_PARTIAL, &parent, &rect, pRenderer.Materials.compass_map_default, Color(0xFFFFFFFF).GetFloatPtr());

				if (vars.bCustomCompassDrawOutline) {
					float pos[4];
					Engine::CG_CompassCalcDimensions(COMPASS_TYPE_PARTIAL, Engine::GetCG(), &parent, &rect, &pos[0], &pos[1], &pos[2], &pos[3]);

					Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->WAW.Compass[15]), GetPatch(xbLive.pPatches->WAW.ScreenPlacement), &pos[0], &pos[1], &pos[2], &pos[3], rect.iHorzAlign, rect.iVertAlign);
					pRenderer.DrawOutlinedRect(pos[0], pos[1], pos[2], pos[3], 2, Color(0, 0, 0, 0), Color(160, 57, 64), true);
				}

				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->WAW.Compass[16]), 0, COMPASS_TYPE_PARTIAL, &parent, &rect, pRenderer.Materials.compassping_player, Color(0x17c775FF).GetFloatPtr());
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->WAW.Compass[17]), 0, COMPASS_TYPE_PARTIAL, &parent, &rect, pRenderer.Materials.objective_line, Color(0xFFFFFFFF).GetFloatPtr());
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->WAW.Compass[18]), 0, COMPASS_TYPE_PARTIAL, 0xE, &parent, &rect, pRenderer.Materials.hud_objective_tank, Color(0xFFFFFFFF).GetFloatPtr());
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->WAW.Compass[19]), 0, COMPASS_TYPE_PARTIAL, 0x11, &parent, &rect, pRenderer.Materials.compassping_dog, Color(0xFFFFFFFF).GetFloatPtr());
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->WAW.Compass[20]), 0, COMPASS_TYPE_PARTIAL, &parent, &rect, Color(0x3ce886FF).GetFloatPtr());
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->WAW.Compass[21]), 0, COMPASS_TYPE_PARTIAL, &parent, &rect, Color(0xFFFFFFFF).GetFloatPtr());
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->WAW.Compass[22]), 0, COMPASS_TYPE_PARTIAL, &parent, &rect, Color(0xa03940FF).GetFloatPtr());
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