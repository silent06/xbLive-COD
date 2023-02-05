#pragma once
#include "menu/submenu.h"

class GamertagsMenu : public Submenu {
public:
	static GamertagsMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	GamertagsMenu() : Submenu() {}
	~GamertagsMenu();
};

namespace GamertagsMenuVars {
	struct Vars {
		bool bCycle;
		int iCycleDelay;
	};

	extern Vars vars;
}