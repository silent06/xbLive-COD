#pragma once
#include "../submenu.h"

class SettingsMenu : public Submenu {
public:
	static SettingsMenu* GetInstance();

	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate();

	SettingsMenu() : Submenu() {}
	~SettingsMenu();
};

namespace SettingsMenuVars {
	struct Vars {

	};

	extern Vars vars;
}