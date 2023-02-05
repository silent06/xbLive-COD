#pragma once
#include "menu/submenu.h"

class ConfigMenu : public Submenu {
public:
	static ConfigMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	ConfigMenu() : Submenu() {}
	~ConfigMenu();
};

namespace ConfigMenuVars {
	struct Vars {
		vector<string> vFiles;
	};

	extern Vars vars;
}