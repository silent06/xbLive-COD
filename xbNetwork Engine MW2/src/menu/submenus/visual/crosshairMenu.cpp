#include "stdafx.h"
#include "crosshairMenu.h"
#include "../visualMenu.h"

using namespace CrosshairMenuVars;

namespace CrosshairMenuVars {
	Vars vars;

	void DisableEngineCrosshair() {
		*(DWORD*)GetPatch(xbLive.pPatches->MW2.DisableEngineCrosshair) = vars.bDisableEngineCrosshair ? 0x4e800020 : 0x7D8802A6;
	}
}

void CrosshairMenu::Init() {
	SetParentSubmenu<VisualMenu>();
	SetName("Crosshair");

	addOption(ToggleOption("Disable Engine Crosshair")
		.addToggle(vars.bDisableEngineCrosshair)
		.addFunction(DisableEngineCrosshair).canBeSaved("Crosshair")
		.addTooltip("Disables the engines crosshair."));

	addOption(ToggleOption("Draw Custom Crosshair")
		.addToggle(vars.bDrawCustomCrosshair).canBeSaved("Crosshair")
		.addTooltip("Draws a custom crosshair."));

	addOption(ToggleOption("Rotate Custom Crosshair")
		.addToggle(vars.bRotateCustomCrosshair).canBeSaved("Crosshair")
		.addTooltip("Rotates the custom crosshair."));

	addOption(NumberOption<int>(SCROLL, "Custom Crosshair Base Rotation")
		.addNumber(vars.iRotation, "%i", 1).addMin(0).addMax(90).setScrollSpeed(10).canBeSaved("Crosshair")
		.addTooltip("Sets the base rotation for the crosshair (non spin mode)."));

	addOption(NumberOption<int>(SCROLL, "Custom Crosshair Rotate Speed")
		.addNumber(vars.iRotateSpeed, "%i", 1).addMin(0).addMax(50).setScrollSpeed(10).canBeSaved("Crosshair")
		.addTooltip("Sets the speed for the rotating crosshair."));

	addOption(NumberOption<int>(SCROLL, "Custom Crosshair Size")
		.addNumber(vars.iSize, "%i", 1).addMin(0).addMax(300).setScrollSpeed(10).canBeSaved("Crosshair")
		.addTooltip("Sets the scale of the crosshair."));

	vars.iRotation = 45;
	vars.iRotateSpeed = 5;
	vars.iSize = 34;
	vars.CrosshairColor = Color(0xFFFFFFFF);
}

/*Update once when submenu is opened*/
void CrosshairMenu::UpdateOnce() {}

/*Update while submenu is active*/
void CrosshairMenu::Update() {}

/*Background update*/
void CrosshairMenu::FeatureUpdate() {
	if (Engine::InGame()) {
		if (vars.bDrawCustomCrosshair) {
			auto center = Vector2<float>(Engine::GetCG()->Refdef.vScale.X * 0.5f, Engine::GetCG()->Refdef.vScale.Y * 0.5f);

			if (vars.bRotateCustomCrosshair) {
				static int rotation = 0;
				rotation += vars.iRotateSpeed;
				if (rotation > 360) rotation = 0;

				Engine::CG_DrawRotatedPicPhysical(GetPatch(xbLive.pPatches->MW2.ScreenPlacement), center.X - (vars.iSize / 2), center.Y, vars.iSize, 2, rotation, vars.CrosshairColor.GetFloatPtr(), pRenderer.Materials.white);
				Engine::CG_DrawRotatedPicPhysical(GetPatch(xbLive.pPatches->MW2.ScreenPlacement), center.X - (vars.iSize / 2), center.Y, vars.iSize, 2, rotation + 90, vars.CrosshairColor.GetFloatPtr(), pRenderer.Materials.white);
			} else {
				Engine::CG_DrawRotatedPicPhysical(GetPatch(xbLive.pPatches->MW2.ScreenPlacement), center.X - (vars.iSize / 2), center.Y, vars.iSize, 2, vars.iRotation, vars.CrosshairColor.GetFloatPtr(), pRenderer.Materials.white);
				Engine::CG_DrawRotatedPicPhysical(GetPatch(xbLive.pPatches->MW2.ScreenPlacement), center.X - (vars.iSize / 2), center.Y, vars.iSize, 2, vars.iRotation + 90, vars.CrosshairColor.GetFloatPtr(), pRenderer.Materials.white);
			}
		}
	}
}

/*Singleton*/
CrosshairMenu* _instance;
CrosshairMenu* CrosshairMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new CrosshairMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
CrosshairMenu::~CrosshairMenu() { delete _instance; }