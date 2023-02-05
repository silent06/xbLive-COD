#pragma once
#include "menu/submenu.h"

class EditPlayerMenu : public Submenu {
public:
	static EditPlayerMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	EditPlayerMenu() : Submenu() {}
	~EditPlayerMenu();
};

namespace EditPlayerMenuVars {
	struct Vars {
		int iEditingClient;
	};

	extern Vars vars;
}