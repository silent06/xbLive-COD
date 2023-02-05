#include "stdafx.h"
#include "indicatorMenu.h"
#include "../visualMenu.h"

using namespace IndicatorMenuVars;

namespace IndicatorMenuVars {
	Vars vars;

	void DrawPointer(Entity entity, Color pointer, Vector2<float> newScale = Vector2<float>(25.f, 16.f)) {
		Engine::SetDvar(GetPatch(xbLive.pPatches->BO1.DrawGrenadePointer[0]), 75.f);

		auto center = Engine::GetCenter();
		auto offset = entity.vOrigin - Engine::GetCG()->vOrigin;

		float beforeW = Engine::GetDvar<float>(GetPatch(xbLive.pPatches->BO1.DrawGrenadePointer[1]));
		float beforeH = Engine::GetDvar<float>(GetPatch(xbLive.pPatches->BO1.DrawGrenadePointer[2]));

		Engine::SetDvar(GetPatch(xbLive.pPatches->BO1.DrawGrenadePointer[1]), newScale.X);
		Engine::SetDvar(GetPatch(xbLive.pPatches->BO1.DrawGrenadePointer[2]), newScale.Y);

		Engine::CG_DrawGrenadePointer(0, center.X, center.Y, &offset, pointer.GetFloatPtr(), 0.f, 1.0f);

		Engine::SetDvar(GetPatch(xbLive.pPatches->BO1.DrawGrenadePointer[1]), beforeW);
		Engine::SetDvar(GetPatch(xbLive.pPatches->BO1.DrawGrenadePointer[2]), beforeH);
	}

	void Draw(Entity entity, Material* material, Color pointer, Color icon, bool drawPointer = true, Vector2<float> newIconScale = Vector2<float>(30.f, 30.f)) {
		Engine::SetDvar(GetPatch(xbLive.pPatches->BO1.DrawGrenadePointer[0]), 75.f);

		auto center = Engine::GetCenter();
		auto offset = entity.vOrigin - Engine::GetCG()->vOrigin;

		if (drawPointer) Engine::CG_DrawGrenadePointer(0, center.X, center.Y, &offset, pointer.GetFloatPtr(), 0.f, 1.0f);

		Vector2<float> origScale;
		origScale.X = Engine::GetDvar<float>(GetPatch(xbLive.pPatches->BO1.DrawGrenadeIcon[0]));
		origScale.Y = Engine::GetDvar<float>(GetPatch(xbLive.pPatches->BO1.DrawGrenadeIcon[1]));

		Engine::SetDvar(GetPatch(xbLive.pPatches->BO1.DrawGrenadeIcon[0]), newIconScale.X);
		Engine::SetDvar(GetPatch(xbLive.pPatches->BO1.DrawGrenadeIcon[1]), newIconScale.Y);

		Engine::CG_DrawGrenadeIcon(0, center.X, center.Y, &offset, icon.GetFloatPtr(), material, 0.f, 1.0f);

		Engine::SetDvar(GetPatch(xbLive.pPatches->BO1.DrawGrenadeIcon[0]), origScale.X);
		Engine::SetDvar(GetPatch(xbLive.pPatches->BO1.DrawGrenadeIcon[1]), origScale.Y);
	}
}

void IndicatorMenu::Init() {
	SetParentSubmenu<VisualMenu>();
	SetName("Indicators");

	addOption(ToggleOption("Draw Players")
		.addToggle(vars.bPlayers).canBeSaved("Indicators")
		.addTooltip("Draws an indicator arrow to players."));

	addOption(ToggleOption("Draw Equipment")
		.addToggle(vars.bEquipment).canBeSaved("Indicators")
		.addTooltip("Draws an indicator arrow to equipment."));

	addOption(ToggleOption("Draw Dropped Items")
		.addToggle(vars.bDroppedItems).canBeSaved("Indicators")
		.addTooltip("Draws an indicator arrow to dropped items."));

	vars.DrawPlayersFriendliesColor = Color(0x00d43fFF);
	vars.DrawPlayersEnemiesColor = Color(0xa03940FF);
	vars.DrawPlayersAimbotTargetColor = Color(0xa8a828FF);

	vars.DrawEquipmentColor = Color(0xFFFFFFFF);
	vars.DrawDroppedItemsColor = Color(0xe455e8FF);
}

/*Update once when submenu is opened*/
void IndicatorMenu::UpdateOnce() {}

/*Update while submenu is active*/
void IndicatorMenu::Update() {}

/*Background update*/
void IndicatorMenu::FeatureUpdate() {
	if (Engine::InGame()) {
		if (vars.bPlayers) {
			for (int i = 0; i < Engine::GetServerInfo()->iMaxClients; i++) {
				if (i == Engine::GetCG()->iClientNumber) continue;

				if (Engine::IsAlive(i, true)) {
					auto entity = Engine::GetEntity(i);
					Color color = Engine::IsFriend(i) ? vars.DrawPlayersFriendliesColor : vars.DrawPlayersEnemiesColor;

					if (AimbotMenuVars::vars.bShowAimbotTarget && i == pGame.iAimbotTarget) {
						color = vars.DrawPlayersAimbotTargetColor;
					}

					DrawPointer(entity, color);
				}
			}
		}

		if (vars.bDroppedItems || vars.bEquipment) {
			for (int i = 18; i < 0x7FF; i++) {
				auto entity = Engine::GetEntityPtr();

				if (vars.bEquipment) {
					if (Engine::IsAlive(i) && (Engine::GetDistance(Engine::GetCG()->Refdef.vOrigin, entity[i].vOrigin) < 1500.0f)) {
						if (Engine::IsWeaponEquipmentItem(entity[i].dwWeaponIndex)) {
							Vector2<float> aspect;
							auto icon = Engine::GetWeaponMaterialWithAspect(entity[i].dwWeaponIndex, &aspect);
							if (icon) {
								DrawPointer(entity[i], vars.DrawEquipmentColor);
								Draw(entity[i], icon, Color(0xFFFFFFFF), Color(0xFFFFFFFF), false, Vector2<float>(18.f, 18.f)); // aspect.X, aspect.Y
							}
						}
					}
				}

				if (vars.bDroppedItems) {
					if (Engine::IsAlive(i) && entity[i].GetType() == ET_ITEM && (Engine::GetDistance(Engine::GetCG()->Refdef.vOrigin, entity[i].vOrigin) < 1500.0f)) {
						int index = *(int*)((DWORD)&entity[i] + 0x274);
						if (index && index < 0x800) {
							if (!Engine::IsWeaponThis(index, WEAPON_SCAV)) {
								Vector2<float> aspect;
								auto icon = Engine::GetWeaponMaterialWithAspect(index, &aspect);
								if (icon && icon->pName) {
									DrawPointer(entity[i], vars.DrawEquipmentColor);
									Draw(entity[i], icon, Color(0xFFFFFFFF), Color(0xFFFFFFFF), false, aspect);
								}
							} else {
								DrawPointer(entity[i], vars.DrawDroppedItemsColor);
								Draw(entity[i], pRenderer.Materials.hud_scavenger_pickup, Color(0xFFFFFFFF), Color(0xFFFFFFFF), false, Vector2<float>(45, 30));
							}
						}
					}
				}
			}
		}
	}
}

/*Singleton*/
IndicatorMenu* _instance;
IndicatorMenu* IndicatorMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new IndicatorMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
IndicatorMenu::~IndicatorMenu() { delete _instance; }