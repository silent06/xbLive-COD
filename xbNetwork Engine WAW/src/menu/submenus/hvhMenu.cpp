#include "stdafx.h"
#include "hvhMenu.h"

using namespace HvHMenuVars;

namespace HvHMenuVars {
	Vars vars;

	ScrollStruct<int> XDirections[] = {
		"Verticle Jitter", 0, // Changed from spin, set speed to 45
		"Look Up", 1, // Looking up all the time
		"Look Down", 2, // Looking down all the time
	};

	ScrollStruct<int> YDirections[] = {
		"Random Jitter", 0, // Changed from shield
		"Spin", 1, // Spins around
		"Fake", 2, // Static angle
	};

	ScrollStruct<int> CrouchEvents[] = {
		"On Damage", 0,
		"On Target", 1,
		"Always", 2
	};

	bool YRequirement() {
		return vars.iYDirection == 1;
	}
}

void HvHMenu::Init() {
	SetName("HvH");

	addOption(ScrollOption<int>(TOGGLE, "X Direction")
		.addScroll(vars.iXDirection, 0, NUMOF(XDirections) - 1, XDirections)
		.addToggle(vars.bXDirection).canBeSaved("HvH")
		.addTooltip("Choose the AA style for the X axis."));

	addOption(ScrollOption<int>(TOGGLE, "Y Direction")
		.addScroll(vars.iYDirection, 0, NUMOF(YDirections) - 1, YDirections)
		.addToggle(vars.bYDirection).canBeSaved("HvH")
		.addTooltip("Choose the AA style for the Y axis."));

	addOption(NumberOption<int>(SCROLL, "Spin Speed")
		.addNumber(vars.iYSpeed, "%i", 1).addMin(0).addMax(45).setScrollSpeed(10)
		.addRequirement(YRequirement).canBeSaved("HvH")
		.addTooltip("Choose the spin speed for the Y axis."));

	addOption(NumberOption<int>(TOGGLE, "Fake Lag")
		.addNumber(vars.iFakeLag, "%i", 1).addMin(0).addMax(10)
		.addToggle(vars.bFakeLag).canBeSaved("HvH")
		.addTooltip("Choose the packet choke delay."));

	addOption(ScrollOption<int>(TOGGLE, "Crouch Event")
		.addScroll(vars.iCrouchEvent, 0, NUMOF(CrouchEvents) - 1, CrouchEvents)
		.addToggle(vars.bCrouchEvent).canBeSaved("HvH")
		.addTooltip("Crouch on a specified event."));

	vars.iYSpeed = 10;
	vars.iFakeLag = 1;
	vars.iXDirection = 1;
	vars.iYDirection = 1;
}

/*Update once when submenu is opened*/
void HvHMenu::UpdateOnce() {}

/*Update while submenu is active*/
void HvHMenu::Update() {}

/*Background update*/
void HvHMenu::FeatureUpdate() {}

/*Singleton*/
HvHMenu* _instance;
HvHMenu* HvHMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new HvHMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
HvHMenu::~HvHMenu() { delete _instance; }