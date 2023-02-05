#include "stdafx.h"
#include "indicatorMenu.h"
#include "../visualMenu.h"
#include "../aimbotMenu.h"

using namespace IndicatorMenuVars;

namespace IndicatorMenuVars {
	Vars vars;

	void DrawPointer(Entity entity, Color pointer, Vector2<float> newScale = Vector2<float>(25.f, 16.f)) {
		auto center = Engine::GetCenter();
		auto offset = entity.vOrigin - Engine::GetCG()->vOrigin;

		float beforeW = Engine::GetDvar<float>(GetPatch(xbLive.pPatches->AW.DrawPointer[0])); 
		float beforeH = Engine::GetDvar<float>(GetPatch(xbLive.pPatches->AW.DrawPointer[1]));
		float beforeR = Engine::GetDvar<float>(GetPatch(xbLive.pPatches->AW.DrawPointer[2]));

		Engine::SetDvar(GetPatch(xbLive.pPatches->AW.DrawPointer[0]), newScale.X);
		Engine::SetDvar(GetPatch(xbLive.pPatches->AW.DrawPointer[1]), newScale.Y);
		Engine::SetDvar(GetPatch(xbLive.pPatches->AW.DrawPointer[2]), 30.f);

		*(short*)GetPatch(xbLive.pPatches->AW.DrawPointer[3]) = 0x0988;
		Engine::CG_DrawGrenadePointer(0, center.X, center.Y, &offset, pointer.GetFloatPtr());
		*(short*)GetPatch(xbLive.pPatches->AW.DrawPointer[3]) = 0xD010;

		Engine::SetDvar(GetPatch(xbLive.pPatches->AW.DrawPointer[0]), beforeW);
		Engine::SetDvar(GetPatch(xbLive.pPatches->AW.DrawPointer[1]), beforeH);
		Engine::SetDvar(GetPatch(xbLive.pPatches->AW.DrawPointer[2]), beforeR);
	}

	void Draw(Entity entity, Material* material, Color pointer, Color icon, bool drawPointer = true, Vector2<float> newIconScale = Vector2<float>(30.f, 30.f)) {
		auto center = Engine::GetCenter();
		auto offset = entity.vOrigin - Engine::GetCG()->vOrigin;

		if (drawPointer) Engine::CG_DrawGrenadePointer(0, center.X, center.Y, &offset, pointer.GetFloatPtr());

		Vector2<float> origScale;
		origScale.X = Engine::GetDvar<float>(GetPatch(xbLive.pPatches->AW.DrawGrenade[0]));
		origScale.Y = Engine::GetDvar<float>(GetPatch(xbLive.pPatches->AW.DrawGrenade[1]));

		Engine::SetDvar(GetPatch(xbLive.pPatches->AW.DrawGrenade[0]), newIconScale.X);
		Engine::SetDvar(GetPatch(xbLive.pPatches->AW.DrawGrenade[1]), newIconScale.Y);

		Engine::CG_DrawGrenadeIcon(0, center.X, center.Y, 1.f, &offset, 1.f, icon.GetFloatPtr(), material);

		Engine::SetDvar(GetPatch(xbLive.pPatches->AW.DrawGrenade[0]), origScale.X);
		Engine::SetDvar(GetPatch(xbLive.pPatches->AW.DrawGrenade[1]), origScale.Y);
	}
}

void IndicatorMenu::Init() {
	SetParentSubmenu<VisualMenu>();
	SetName("Indicators");

	addOption(ToggleOption("Players")
		.addToggle(vars.bPlayers).canBeSaved("Indicators")
		.addTooltip("Draws an indicator arrow to players."));

	addOption(ToggleOption("Equipment")
		.addToggle(vars.bEquipment).canBeSaved("Indicators")
		.addTooltip("Draws an indicator arrow to equipment."));

	addOption(ToggleOption("Dropped Items")
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
				if (i == Engine::GetCG()->bClientNumber) continue;

				if (Engine::IsAlive(i, false)) {
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
			for (int i = Engine::GetServerInfo()->iMaxClients; i < 0x7FF; i++) {
				auto entity = Engine::GetEntityPtr();

				if (vars.bEquipment) {
					if (Engine::IsWeaponEquipmentItem(entity[i].iWeaponIndex)
						&& !Engine::IsWeaponThis(entity[i].iWeaponIndex, WEAPON_SCAV)) {
						if (Engine::IsAlive(i, true)) {
							if ((Engine::GetDistance(Engine::GetCG()->Refdef.vOrigin, entity[i].vOrigin) < 1200.0f)) {
								DrawPointer(entity[i], vars.DrawEquipmentColor);
								Draw(entity[i], Engine::GetWeaponDef(entity[i].iWeaponIndex)->pKillIcon, Color(0xFFFFFFFF), Color(0xFFFFFFFF), false, Vector2<float>(18.f, 18.f));
							}
						}
					}
				}

				if (vars.bDroppedItems) {
					if (Engine::IsAlive(i, true) && entity[i].bType == ET_ITEM && (Engine::GetDistance(Engine::GetCG()->Refdef.vOrigin, entity[i].vOrigin) < 1500.0f)) {
						if (!Engine::IsWeaponThis(entity[i].iWeaponIndex, WEAPON_SCAV)) {
							Vector2<float> aspect;
							auto icon = Engine::GetWeaponMaterialWithAspect(entity[i].iWeaponIndex, &aspect);
							if (icon) {
								aspect.X *= 0.95f;
								aspect.Y *= 0.95f;
								DrawPointer(entity[i], vars.DrawEquipmentColor);
								Draw(entity[i], icon, Color(0xFFFFFFFF), Color(0xFFFFFFFF), false, aspect);
							}
						} else {
							DrawPointer(entity[i], Color(0xe455e8FF));
							Draw(entity[i], pRenderer.Materials.scavenger_pickup, Color(0xFFFFFFFF), Color(0xFFFFFFFF), false, Vector2<float>(45, 30));
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