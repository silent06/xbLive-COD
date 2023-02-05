#include "stdafx.h"
#include "compassMenu.h"
#include "../visualMenu.h"

using namespace CompassMenuVars;

namespace CompassMenuVars {
	Vars vars;

	void DisableEngineCompass() {
		if (!vars.bDisableEngineCompass) {
			*(DWORD*)GetPatch(xbLive.pPatches->MW1.Compass[0]) = 0x4801CF91;
			*(DWORD*)GetPatch(xbLive.pPatches->MW1.Compass[1]) = 0x4801BED1;
			*(DWORD*)GetPatch(xbLive.pPatches->MW1.Compass[2]) = 0x4801C9D1;
			*(DWORD*)GetPatch(xbLive.pPatches->MW1.Compass[3]) = 0x4801A67D;
			*(DWORD*)GetPatch(xbLive.pPatches->MW1.Compass[4]) = 0x4801A1D9;
			*(DWORD*)GetPatch(xbLive.pPatches->MW1.Compass[5]) = 0x48019B31;
			*(DWORD*)GetPatch(xbLive.pPatches->MW1.Compass[6]) = 0x48019B69;
			*(DWORD*)GetPatch(xbLive.pPatches->MW1.Compass[7]) = 0x4801DE39;
			*(DWORD*)GetPatch(xbLive.pPatches->MW1.Compass[8]) = 0x7D8802A6;
			*(DWORD*)GetPatch(xbLive.pPatches->MW1.Compass[9]) = 0x7D8802A6;
			*(DWORD*)GetPatch(xbLive.pPatches->MW1.Compass[10]) = 0x7D8802A6;
			*(DWORD*)GetPatch(xbLive.pPatches->MW1.Compass[11]) = 0x7D8802A6;
			*(DWORD*)GetPatch(xbLive.pPatches->MW1.Compass[12]) = 0x7D8802A6;
		} else {
			*(DWORD*)GetPatch(xbLive.pPatches->MW1.Compass[0]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->MW1.Compass[1]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->MW1.Compass[2]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->MW1.Compass[3]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->MW1.Compass[4]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->MW1.Compass[5]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->MW1.Compass[6]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->MW1.Compass[7]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->MW1.Compass[8]) = 0x4e800020;
			*(DWORD*)GetPatch(xbLive.pPatches->MW1.Compass[9]) = 0x4e800020;
			*(DWORD*)GetPatch(xbLive.pPatches->MW1.Compass[10]) = 0x4e800020;
			*(DWORD*)GetPatch(xbLive.pPatches->MW1.Compass[11]) = 0x4e800020;
			*(DWORD*)GetPatch(xbLive.pPatches->MW1.Compass[12]) = 0x4e800020;

			static DWORD lastHash = 0;
			if (lastHash != pUtils.Joaat(Engine::GetDvar<const char*>(GetPatch(xbLive.pPatches->MW1.ui_mapname)))) {
				lastHash = pUtils.Joaat(Engine::GetDvar<const char*>(GetPatch(xbLive.pPatches->MW1.ui_mapname)));
				Engine::SetDvar(GetPatch(xbLive.pPatches->MW1.compassMaxRange), Engine::GetDvar<float>(GetPatch(xbLive.pPatches->MW1.compassMaxRange)) * 1.5f);
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
		.addToggle(vars.bDrawCustomCompass)
		.canBeSaved("Compass")
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
			auto currentMenu = Invoke::Call<const char*>(GetPatch(xbLive.pPatches->MW1.UI_GetTopActiveMenuName), 0);
			if (!currentMenu || (strcmp(currentMenu, "scoreboard") && strcmp(currentMenu, "class"))) {
				auto center = Engine::GetCenter();

				RectDef parent, rect;
				parent.vPosition.X = 0.f;
				parent.vPosition.Y = 0.f;
				parent.vScale.X = vars.fCustomCompassScale;
				parent.vScale.Y = vars.fCustomCompassScale;
				parent.iHorzAlign = 1;
				parent.iVertAlign = 1;

				rect.vPosition.X = 0;
				rect.vPosition.Y = 0;
				rect.vScale.X = vars.fCustomCompassScale;
				rect.vScale.Y = vars.fCustomCompassScale;
				rect.iHorzAlign = 1;
				rect.iVertAlign = 1;

				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW1.Compass[13]), 0, COMPASS_TYPE_PARTIAL, &parent, &rect, pRenderer.Materials.compass_map_default, Color(0xFFFFFFFF).GetFloatPtr());

				if (vars.bCustomCompassDrawOutline) {
					float pos[4];
					Engine::CG_CompassCalcDimensions(COMPASS_TYPE_PARTIAL, Engine::GetCG(), &parent, &rect, &pos[0], &pos[1], &pos[2], &pos[3]);

					Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW1.Compass[14]), GetPatch(xbLive.pPatches->MW1.Compass[15]), &pos[0], &pos[1], &pos[2], &pos[3], rect.iHorzAlign, rect.iVertAlign);
					pRenderer.DrawOutlinedRect(pos[0], pos[1], pos[2], pos[3], 2, Color(0, 0, 0, 0), Color(160, 57, 64), true);
				}

				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW1.Compass[16]), 0, COMPASS_TYPE_PARTIAL, &parent, &rect, pRenderer.Materials.objective_line, Color(0xFFFFFFFF).GetFloatPtr());
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW1.Compass[17]), 0, COMPASS_TYPE_PARTIAL, &parent, &rect, pRenderer.Materials.compassping_player, Color(0x17c775FF).GetFloatPtr());
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW1.Compass[18]), 0, COMPASS_TYPE_PARTIAL, &parent, &rect, Color(0x3ce886FF).GetFloatPtr());
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW1.Compass[19]), 0, COMPASS_TYPE_PARTIAL, &parent, &rect, Color(0xa03940FF).GetFloatPtr());
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW1.Compass[20]), 0, COMPASS_TYPE_PARTIAL, 0xD, &parent, &rect, pRenderer.Materials.compass_objpoint_airstrike_busy, pRenderer.Materials.compass_objpoint_airstrike_friendly, Color(0xFFFFFFFF).GetFloatPtr());
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW1.Compass[20]), 0, COMPASS_TYPE_PARTIAL, 0xC, &parent, &rect, pRenderer.Materials.compass_objpoint_helicopter_busy, pRenderer.Materials.compass_objpoint_helicopter_friendly, Color(0xFFFFFFFF).GetFloatPtr());
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