#include "stdafx.h"
#include "mainMenu.h"
//#include "main/gamertagManagerMenu.h"
//#include "visual/espMenu.h"

using namespace MainMenuVars;

namespace MainMenuVars {
	Vars vars;

	ScrollStruct<int> ScrollChangeTeam[] = {
		"Allies", 0,
		"Axis", 1,
		"Spectator", 2
	};

	double Radians(float Degrees) {
		return 0.01745329238474369 * Degrees;
	}

	void NoRecoil() {
		*(DWORD*)(0x82227624, vars.bNoRecoil ? 0x60000000 : 0x4BF67EC5);
	}

	void NoSway() {
		*(DWORD*)(0x82195200, vars.bNoSway ? 0x60000000 : 0x4BFFEB09);
	}

	void NoFlinch() {
		*(DWORD*)(0x821E0824, vars.bNoFlinch ? 0x60000000 : 0x4BFFF77D);
	}

	void ConstantRadar() {
		*(DWORD*)(0x821A81A0, vars.bConstantRadar ? 0x60000000 : 0x419A0050);
	}

	void DvarThirdPerson() {
		Engine::SetDvar(0x829680DC, vars.fThirdPerson); 

		if (!vars.bThirdPerson) {
			*(BYTE*)(*(int*)(0x828D7118) + 0x18) = 0; 
		}
	}

	void DvarFOV() {
		Engine::SetDvar(0x82968374, vars.fFOV); 
	}

	void DvarSetHearEveryone() {
		Engine::Cbuf_AddText(0, pUtils.va("cg_everyoneHearsEveryone %i", vars.bHearEveryone));
	}

	void EndGame() {
		Engine::Cbuf_AddText(0, pUtils.va("cmd mr %i -1 endround;", *(int*)(0x829BE624))); 
	}

	void LeaveGame() {
		Engine::Cbuf_AddText(0, "disconnect");
	}

	void GetSpread_BO3(int* seed, float* x, float* y) {
		
	}

	void NoSpread(UserCommand* pNextUserCommand, UserCommand* pUserCommand) {
		
	}
}

void MainMenu::Init() {
	SetName("Main");

	/*addOption(SubmenuOption("Gamertag Manager")
		.addSubmenu<GamertagManagerMenu>()
		.addTooltip("Enters the menu for changing your name."));*/

	addOption(ToggleOption("No Recoil")
		.addToggle(vars.bNoRecoil)
		.addFunction(NoRecoil).canBeSaved("Main")
		.addTooltip("Removes weapon recoil so you can shoot and your weapon won't kick up."));

	addOption(ToggleOption("No Spread")
		.addToggle(vars.bNoSpread).canBeSaved("Main")
		.addTooltip("Removes weapon spread so your bullets shoot straight."));

	addOption(ToggleOption("No Sway")
		.addToggle(vars.bNoSway)
		.addFunction(NoSway).canBeSaved("Main")
		.addTooltip("Removes sway so your weapon is held perfectly still (snipers have the most impact)."));

	addOption(ToggleOption("No Flinch")
		.addToggle(vars.bNoFlinch)
		.addFunction(NoFlinch).canBeSaved("Main")
		.addTooltip("Removes flinch so your gun doesn't move when aiming in and getting shot."));
	
	addOption(ToggleOption("Fast Reload")
		.addToggle(vars.bFastReload).canBeSaved("Main")
		.addTooltip("Reloads your weapon faster."));

	addOption(ToggleOption("Constant Radar")
		.addToggle(vars.bConstantRadar)
		.addFunction(ConstantRadar).canBeSaved("Main")
		.addTooltip("Makes the radar always show friendlies and hostiles."));

	addOption(NumberOption<float>(TOGGLE, "Third Person")
		.addToggle(vars.bThirdPerson)
		.addFunction(DvarThirdPerson)
		.addNumber(vars.fThirdPerson, "%.0f", 1.0f).addMin(1.f).addMax(250.f).setScrollSpeed(10).canBeSaved("Main")
		.addTooltip("Allows you to view your player from a over-the-shoulder type view."));

	addOption(NumberOption<float>(SCROLL, "Field of View")
		.addNumber(vars.fFOV, "%.0f", 1.f).addMin(0.f).addMax(175.f).setScrollSpeed(10)
		.addFunction(DvarFOV).canBeSaved("Main")
		.addTooltip("Sets your field of view."));

	addOption(ToggleOption("Hear Everyone")
		.addToggle(vars.bHearEveryone)
		.addFunction(DvarSetHearEveryone).canBeSaved("Main")
		.addTooltip("Allows you to hear the enemy team."));

	addOption(ButtonOption("End Game")
		.addFunction(EndGame)
		.addTooltip("Force ends the game for everyone."));

	addOption(ButtonOption("Leave Game")
		.addFunction(LeaveGame)
		.addTooltip("Disconnects you from the current match."));

	vars.fThirdPerson = 30.f;
	vars.fFOV = 65.f;
	vars.iChangeClass = 1;
}

/*Update once when submenu is opened*/
void MainMenu::UpdateOnce() {}

/*Update while submenu is active*/
void MainMenu::Update() {}

/*Background update*/
void MainMenu::FeatureUpdate() {}

/*Singleton*/
MainMenu* _instance;
MainMenu* MainMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new MainMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
MainMenu::~MainMenu() { delete _instance; }