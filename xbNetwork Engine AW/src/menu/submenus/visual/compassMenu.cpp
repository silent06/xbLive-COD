#include "stdafx.h"
#include "compassMenu.h"
#include "../visualMenu.h"

using namespace CompassMenuVars;

namespace CompassMenuVars {
	Vars vars;

	void DisableEngineCompass() {
		static DWORD lastHash = 0;

		if (vars.bDisableEngineCompass) {
			if (lastHash != pUtils.Joaat(Engine::GetDvar<const char*>(GetPatch(xbLive.pPatches->AW.ui_mapname)))) {
				lastHash = pUtils.Joaat(Engine::GetDvar<const char*>(GetPatch(xbLive.pPatches->AW.ui_mapname)));
				Engine::SetDvar(GetPatch(xbLive.pPatches->AW.compassMaxRange), Engine::GetDvar<float>(GetPatch(xbLive.pPatches->AW.compassMaxRange)) * 1.5f);
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
			if (CompassMenuVars::vars.CurrentlyRenderedType == COMPASS_TYPE_PARTIAL) {
				RectDef parent;
				parent.vPosition.X = 0.f;
				parent.vPosition.Y = 0.f;
				parent.vScale.X = 0.f;
				parent.vScale.Y = 0.f;
				parent.bAlignLeft = 0x5;
				parent.bAlignRight = 0x5;

				RectDef rect;
				rect.vPosition.X = vars.vPosition.X;
				rect.vPosition.Y = vars.vPosition.Y;
				rect.vScale.X = vars.fCustomCompassScale;
				rect.vScale.Y = vars.fCustomCompassScale;
				rect.bAlignLeft = 0xC;
				rect.bAlignRight = 0xD;

				float pos[4];
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->AW.CalculateCompassPosition), COMPASS_TYPE_PARTIAL, Engine::GetCG(), &parent, &rect, &pos[0], &pos[1], &pos[2], &pos[3]);

				auto renderPtr = 0;

				auto ptr = *(DWORD*)0x82B94514;
				if (ptr < 1) {
					renderPtr = GetPatch(xbLive.pPatches->AW.ScreenPlacement[1]);
				} else {
					if (ptr == 1) {
						renderPtr = GetPatch(xbLive.pPatches->AW.ScreenPlacement[0]);
					} else {
						renderPtr = GetPatch(xbLive.pPatches->AW.ScreenPlacement[1]);
					}
				}

				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->AW.ScrView_ApplyRect), renderPtr, &pos[0], &pos[1], &pos[2], &pos[3], 0xC, 0xD);
				pRenderer.DrawRect(pos[0], pos[1], pos[2], pos[3], JustifyLeft, Color(0, 0, 0, 102)); // bg

				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->AW.DrawCompass[0]), 0, COMPASS_TYPE_PARTIAL, &parent, &rect, Color(255, 255, 255, 255).GetFloatPtr(), 0); // map

				if (vars.bCustomCompassDrawOutline) {
					pRenderer.DrawOutlinedRect(pos[0], pos[1], pos[2], pos[3], 2, Color(0, 0, 0, 0), Color(160, 57, 64), true);
				}

				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->AW.DrawCompass[1]), 0, COMPASS_TYPE_PARTIAL, &parent, &rect, Color(255, 255, 255, 255).GetFloatPtr(), 0);
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->AW.DrawCompass[2]), 0, COMPASS_TYPE_PARTIAL, &parent, &rect, Color(255, 255, 255, 255).GetFloatPtr(), 0);
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->AW.DrawCompass[3]), 0, COMPASS_TYPE_PARTIAL, &parent, &rect, *(DWORD*)(GetPatch(xbLive.pPatches->AW.DrawCompass[11])), Color(255, 255, 255, 255).GetFloatPtr(), 0);
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->AW.DrawCompass[4]), 0, COMPASS_TYPE_PARTIAL, &parent, &rect, Color(255, 255, 255, 255).GetFloatPtr(), 0);
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->AW.DrawCompass[5]), 0, COMPASS_TYPE_PARTIAL, &parent, &rect, 0); // friendlies
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->AW.DrawCompass[6]), 0, COMPASS_TYPE_PARTIAL, &parent, &rect, Color(0xa03940FF).GetFloatPtr(), 0); // enemies
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->AW.DrawCompass[7]), 0, COMPASS_TYPE_PARTIAL, &parent, &rect, Color(255, 255, 255, 255).GetFloatPtr(), 0);
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->AW.DrawCompass[8]), 0, COMPASS_TYPE_PARTIAL, &parent, &rect, Color(255, 255, 255, 255).GetFloatPtr(), 0);
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->AW.DrawCompass[9]), 0, COMPASS_TYPE_PARTIAL, &parent, &rect, 0);
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->AW.DrawCompass[10]), 0, COMPASS_TYPE_PARTIAL, &parent, &rect, 0); // player
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