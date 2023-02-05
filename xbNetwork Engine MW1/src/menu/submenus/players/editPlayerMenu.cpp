#include "stdafx.h"
#include "editPlayerMenu.h"
#include "../playersMenu.h"

using namespace EditPlayerMenuVars;

namespace EditPlayerMenuVars {
	Vars vars;

	void OnPrioritize(ToggleOption* option) {
		option->addToggle(pGame.Clients[vars.iEditingClient].bPrioritized);
	}
}

void EditPlayerMenu::Init() {
	SetParentSubmenu<PlayersMenu>();
	SetName("Edit Player");

	addOption(ToggleOption("Prioritize")
		.addToggle(pGame.Clients[vars.iEditingClient].bPrioritized)
		.addOnUpdate(OnPrioritize)
		.addTooltip("Whether to run more bone scans on the client."));
}

/*Update once when submenu is opened*/
void EditPlayerMenu::UpdateOnce() {}

/*Update while submenu is active*/
void EditPlayerMenu::Update() {
	static int timer = 0;
	static bool update = true;

	if (GetTickCount() - timer > 250) {
		timer = GetTickCount();
		if (!Engine::IsAlive(vars.iEditingClient)) {
			pSubmenuHandler.SetSubmenuPrevious(true);
		}
	}
}

/*Background update*/
void EditPlayerMenu::FeatureUpdate() {}

/*Singleton*/
EditPlayerMenu* _instance;
EditPlayerMenu* EditPlayerMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new EditPlayerMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
EditPlayerMenu::~EditPlayerMenu() { delete _instance; }