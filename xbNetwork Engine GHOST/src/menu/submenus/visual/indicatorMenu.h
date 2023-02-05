#pragma once
#include "menu/submenu.h"

class IndicatorMenu : public Submenu {
public:
	static IndicatorMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	IndicatorMenu() : Submenu() {}
	~IndicatorMenu();
};

namespace IndicatorMenuVars {
	struct Vars {
		bool bPlayers;
		bool bEquipment;
		bool bDroppedItems;

		Color DrawPlayersFriendliesColor;
		Color DrawPlayersEnemiesColor;
		Color DrawPlayersAimbotTargetColor;

		Color DrawEquipmentColor;
		Color DrawDroppedItemsColor;
	};

	extern Vars vars;
}