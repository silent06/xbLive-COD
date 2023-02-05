#include "stdafx.h"
#include "visualMenu.h"
#include "visual/crosshairMenu.h"
#include "visual/indicatorMenu.h"
#include "visual/gameInfoMenu.h"
#include "visual/espMenu.h"
#include "visual/compassMenu.h"

using namespace VisualMenuVars;

namespace VisualMenuVars {
	Vars vars;
}

void VisualMenu::Init() {
	SetName("Visual");

	addOption(SubmenuOption("Crosshair")
		.addSubmenu<CrosshairMenu>()
		.addTooltip("Enters the menu for crosshair options."));

	addOption(SubmenuOption("Indicators")
		.addSubmenu<IndicatorMenu>()
		.addTooltip("Enters the menu for indicator options."));

	addOption(SubmenuOption("Compass")
		.addSubmenu<CompassMenu>()
		.addTooltip("Enters the menu for compass options."));

	addOption(SubmenuOption("Game Info")
		.addSubmenu<GameInfoMenu>()
		.addTooltip("Enters the menu for showing game info."));

	addOption(SubmenuOption("ESP")
		.addSubmenu<ESPMenu>()
		.addTooltip("Enteres the menu for ESP options."));

	addOption(ToggleOption("Draw Equipment")
		.addToggle(vars.bDrawEquipment).canBeSaved("Visual")
		.addTooltip("Shows equipment in the world."));

	addOption(ToggleOption("Draw Dropped Items")
		.addToggle(vars.bDrawDroppedItems).canBeSaved("Visual")
		.addTooltip("Shows dropped items in the world."));

	addOption(ToggleOption("Draw Health Bar")
		.addToggle(vars.bDrawHealthBar).canBeSaved("Visual")
		.addTooltip("Shows a bar to represent your health."));

	vars.DrawEquipmentColor = Color(0xFFFFFFFF);
	vars.DrawDroppedItemsColor = Color(0xedededFF);
}

/*Update once when submenu is opened*/
void VisualMenu::UpdateOnce() {}

/*Update while submenu is active*/
void VisualMenu::Update() {}

/*Background update*/
void VisualMenu::FeatureUpdate() {
	if (Engine::InGame()) {
		// entity loops
		for (int i = Engine::GetServerInfo()->iMaxClients; i < 0x7FF; i++) {
			auto entity = Engine::GetEntityPtr();

			if (vars.bDrawEquipment) {
				if (Engine::IsAlive(i, true) && (Engine::GetDistance(Engine::GetCG()->Refdef.vOrigin, entity[i].vOrigin) < 1500.0f)) {
					if (Engine::IsWeaponEquipmentItem(entity[i].iWeaponIndex)) {
						Vector3<float> topLocationOut;
						if (Engine::WorldToScreen(entity[i].vOrigin, &topLocationOut)) {
							Vector2<float> aspect;
							auto icon = Engine::GetWeaponMaterialWithAspect(entity[i].iWeaponIndex, &aspect);
							if (icon) {
								Engine::CG_DrawRotatedPicPhysical(GetPatch(xbLive.pPatches->AW.ScreenPlacement[0]), topLocationOut.X - 20, topLocationOut.Y - 20, 20, 20, 0.0, vars.DrawEquipmentColor.GetFloatPtr(), icon);
							}
						}
					}
				}
			}

			if (vars.bDrawDroppedItems) {
				bool scav = false;
				if (Engine::IsAlive(i, true) && entity[i].bType == ET_ITEM && (Engine::GetDistance(Engine::GetCG()->Refdef.vOrigin, entity[i].vOrigin) < 1500.0f)) {
					Vector3<float> topLocationOut;
					if (Engine::WorldToScreen(entity[i].vOrigin, &topLocationOut)) {
						if (Engine::IsWeaponThis(entity[i].iWeaponIndex, WEAPON_SCAV)) {
							scav = true;
						}

						if (!scav) {
							Vector2<float> aspect;
							auto icon = Engine::GetWeaponMaterialWithAspect(entity[i].iWeaponIndex, &aspect);
							if (icon) {
								Engine::CG_DrawRotatedPicPhysical(GetPatch(xbLive.pPatches->AW.ScreenPlacement[0]), topLocationOut.X - (aspect.X / 2), topLocationOut.Y - (aspect.Y / 2), aspect.X, aspect.Y, 0.0, vars.DrawDroppedItemsColor.GetFloatPtr(), icon);
							}
						} else {
							Engine::CG_DrawRotatedPicPhysical(GetPatch(xbLive.pPatches->AW.ScreenPlacement[0]), topLocationOut.X - 45, topLocationOut.Y - 10, 45, 30, 0.0, vars.DrawDroppedItemsColor.GetFloatPtr(), pRenderer.Materials.scavenger_pickup);
						}
					}
				}
			}
		}

		if (vars.bDrawHealthBar) {
			if (Engine::GetCG()->iMaxHealth != 0) {
				auto center = Engine::GetCenter();
				pRenderer.DrawOutlinedRect(center.X - 125, center.Y + 322, 250, 18, 1, Color(0, 0, 0, 0), Color(160, 57, 64, 150), true);
				pRenderer.DrawOutlinedRect(center.X - 125, center.Y + 322, (((250 * Engine::GetCG()->iHealth) / Engine::GetCG()->iMaxHealth)), 18, 3, Color(0, 0, 0, 100), Color(0, 0, 0, 0), true);
				pRenderer.DrawString(pUtils.va("%i / %i", Engine::GetCG()->iHealth, Engine::GetCG()->iMaxHealth), 640, 700, pRenderer.Fonts. bodyFont, 0.79f, Color(0xFFFFFFFF), false, false, JustifyCenter);
			}
		}
	}
}

/*Singleton*/
VisualMenu* _instance;
VisualMenu* VisualMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new VisualMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
VisualMenu::~VisualMenu() { delete _instance; }