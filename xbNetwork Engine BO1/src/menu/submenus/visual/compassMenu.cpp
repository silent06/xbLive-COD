#include "stdafx.h"
#include "compassMenu.h"
#include "../visualMenu.h"

using namespace CompassMenuVars;

namespace CompassMenuVars {
	Vars vars;

	void DisableEngineCompass() {
		static DWORD lastHash = 0;


		if (!vars.bDisableEngineCompass) {
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[0]) = 0x4BFC8C85;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[1]) = 0x4BFC7F21;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[2]) = 0x4BFC81AD;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[3]) = 0x4BFC83B5;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[4]) = 0x4BFC8661;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[5]) = 0x4BFC96A5;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[6]) = 0x4BFCA9D9;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[7]) = 0x4BFA7FD1;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[8]) = 0x4BFCB341;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[9]) = 0x4BFFFBAD;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[10]) = 0x4BFFF9B1;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[11]) = 0x4BFD046D;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[12]) = 0x4BFCBC75;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[13]) = 0x4BFCAEE1;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[14]) = 0x4BFCB5B1;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[15]) = 0x4BFCBFD1;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[16]) = 0x4BFCC959;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[17]) = 0x4BFCF959;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[18]) = 0x4BFD062D;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[19]) = 0x4BFD08D9;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[20]) = 0x4BFD0A49;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[21]) = 0x4BFD0E21;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[22]) = 0x4BFD180D;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[23]) = 0x4BFD1725;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[24]) = 0x4BFD206D;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[25]) = 0x4BFD2499;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[26]) = 0x4BFD2A15;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[27]) = 0x4BFD2E89;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[28]) = 0x4BFD2DD1;
		} else {
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[0]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[1]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[2]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[3]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[4]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[5]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[6]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[7]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[8]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[9]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[10]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[11]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[12]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[13]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[14]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[15]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[16]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[17]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[18]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[19]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[20]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[21]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[22]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[23]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[24]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[25]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[26]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[27]) = 0x60000000;
			*(DWORD*)GetPatch(xbLive.pPatches->BO1.Compass[28]) = 0x60000000;

			if (lastHash != pUtils.Joaat(Engine::GetDvar<const char*>(GetPatch(xbLive.pPatches->BO1.ui_mapname)))) {
				lastHash = pUtils.Joaat(Engine::GetDvar<const char*>(GetPatch(xbLive.pPatches->BO1.ui_mapname)));
				Engine::SetDvar(GetPatch(xbLive.pPatches->BO1.compassMaxRange), Engine::GetDvar<float>(GetPatch(xbLive.pPatches->BO1.compassMaxRange)) * 1.5f);
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
			auto currentMenu = Invoke::Call<const char*>(GetPatch(xbLive.pPatches->BO1.UI_GetTopActiveMenuName), 0);
			if (!currentMenu || (strcmp(currentMenu, "scoreboard") && strcmp(currentMenu, "class"))) {
				RectDef parent, rect;
				parent.vPosition.X = 0.f;
				parent.vPosition.Y = 0.f;
				parent.vScale.X = vars.fCustomCompassScale;
				parent.vScale.Y = vars.fCustomCompassScale;
				parent.iHorzAlign = 0x00000008;
				parent.iVertAlign = 0x00000008;

				rect.vPosition.X = 0.f;
				rect.vPosition.Y = 0.f;
				rect.vScale.X = vars.fCustomCompassScale;
				rect.vScale.Y = vars.fCustomCompassScale;
				rect.iHorzAlign = 0x00000008;
				rect.iVertAlign = 0x00000008;

				float pos[4];
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->BO1.Compass[29]), 0, Engine::GetCG(), &parent, &rect, &pos[0], &pos[1], &pos[2], &pos[3]);

				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->BO1.Compass[30]), GetPatch(xbLive.pPatches->BO1.ScreenPlacement), &pos[0], &pos[1], &pos[2], &pos[3], rect.iHorzAlign, rect.iVertAlign);
				pRenderer.DrawRect(pos[0], pos[1], pos[2], pos[3], JustifyLeft, Color(0, 0, 0, 102));

				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->BO1.Compass[31]), 0, 0, &parent, &rect, pRenderer.Materials.map_grid_square, Color(0xFFFFFFFF).GetFloatPtr(), 0);
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->BO1.Compass[31]), 0, 0, &parent, &rect, pRenderer.Materials.compass_map_default, Color(0xFFFFFFFF).GetFloatPtr(), 0);

				if (vars.bCustomCompassDrawOutline) {
					pRenderer.DrawOutlinedRect(pos[0], pos[1], pos[2], pos[3], 2, Color(0, 0, 0, 0), Color(160, 57, 64), true);
				}

				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->BO1.Compass[32]), 0, 0, &parent, &rect, pRenderer.Materials.tow_filter_overlay_no_signal, Color(0xFFFFFFFF).GetFloatPtr(), 0);
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->BO1.Compass[33]), 0, 0, &parent, &rect, pRenderer.Materials.objective_line, Color(0xFFFFFFFF).GetFloatPtr());
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->BO1.Compass[34]), 0, 0, &parent, &rect, Color(0xFFFFFFFF).GetFloatPtr());
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->BO1.Compass[35]), 0, 0, &parent, &rect, Color(0xFFFFFFFF).GetFloatPtr());
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->BO1.Compass[36]), 0, 0, &parent, &rect, Color(0xFFFFFFFF).GetFloatPtr());
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->BO1.Compass[37]), 0, 0, &parent, &rect, Color(0xFFFFFFFF).GetFloatPtr());
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->BO1.Compass[38]), 0, 0, &parent, &rect, Color(0xFFFFFFFF).GetFloatPtr());
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->BO1.Compass[39]), 0, 0, 0xE, &parent, &rect, Color(0xFFFFFFFF).GetFloatPtr());
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->BO1.Compass[39]), 0, 0, 0xD, &parent, &rect, Color(0xFFFFFFFF).GetFloatPtr());
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->BO1.Compass[40]), 0, 0, 0x11, &parent, &rect, pRenderer.Materials.compassping_dog, Color(0xFFFFFFFF).GetFloatPtr());
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->BO1.Compass[41]), 0, 0, 0xB, &parent, &rect, Color(0xFFFFFFFF).GetFloatPtr());
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->BO1.Compass[42]), 0, 0, 0xC, &parent, &rect, Color(0xFFFFFFFF).GetFloatPtr());
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->BO1.Compass[43]), 0, 0, 0x4, &parent, &rect, Color(0xFFFFFFFF).GetFloatPtr());
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->BO1.Compass[44]), 0, 0, &parent, &rect, Color(0xFFFFFFFF).GetFloatPtr());
				Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->BO1.Compass[45]), 0, 0, &parent, &rect, pRenderer.Materials.compassping_player, Color(0x17c775FF).GetFloatPtr());
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