#include "stdafx.h"
#include "gamertagsMenu.h"
#include "gamertagManagerMenu.h"

using namespace GamertagsMenuVars;

namespace GamertagsMenuVars {
	Vars vars;
	
	void SetGamertag() {
		GamertagManagerMenuVars::SetGamertag(GamertagManagerMenuVars::vars.vSavedGamertags[pMenu.iCurrentOption - 2].c_str());
	}
}

void GamertagsMenu::Init() {
	SetParentSubmenu<GamertagManagerMenu>();
	SetName("Gamertags");

	vars.iCycleDelay = 1000;
}

/*Update once when submenu is opened*/
void GamertagsMenu::UpdateOnce() {
	ClearOptionsOffset(0);

	if (GamertagManagerMenuVars::vars.vSavedGamertags.size() > 0) {
		addOption(ToggleOption("Cycle")
			.addToggle(vars.bCycle)
			.addTooltip("Cycles through your list and applies your name."));

		addOption(NumberOption<int>(SCROLL, "Cycle Delay")
			.addNumber(vars.iCycleDelay, "%ims", 100).addMin(0).addMax(5000)
			.addTooltip("Sets the delay between each gamertag cycle."));

		for (int i = 0; i < GamertagManagerMenuVars::vars.vSavedGamertags.size(); i++) {
			addOption(ButtonOption(GamertagManagerMenuVars::vars.vSavedGamertags[i].c_str())
				.addFunction(SetGamertag)
				.addTooltip("Sets this gamertag."));
		}
	} else {
		addOption(ButtonOption("You don't have any saved gamertags :("));
	}
}

/*Update while submenu is active*/
void GamertagsMenu::Update() {}

/*Background update*/
void GamertagsMenu::FeatureUpdate() {
	if (vars.bCycle) {
		static int current = 0;
		static int timer = 0;
		if (GetTickCount() - timer > vars.iCycleDelay) {
			timer = GetTickCount();

			if (current >= GamertagManagerMenuVars::vars.vSavedGamertags.size()) current = 0;

			GamertagManagerMenuVars::SetGamertag(GamertagManagerMenuVars::vars.vSavedGamertags[current].c_str());

			current++;
		}
	}
}

/*Singleton*/
GamertagsMenu* _instance;
GamertagsMenu* GamertagsMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new GamertagsMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
GamertagsMenu::~GamertagsMenu() { delete _instance; }