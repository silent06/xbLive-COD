#pragma once
#include "menu/submenu.h"

class VisualMenu : public Submenu {
public:
	static VisualMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	VisualMenu() : Submenu() {}
	~VisualMenu();
};

namespace VisualMenuVars {
	struct Vars {
		bool bDrawEquipment;
		bool bDrawDroppedItems;
		bool bDrawHealthBar;

		Color DrawEquipmentColor;
		Color DrawDroppedItemsColor;
	};

	extern Vars vars;
}