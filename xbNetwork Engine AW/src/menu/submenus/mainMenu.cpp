#include "stdafx.h"
#include "mainMenu.h"
#include "main/gamertagManagerMenu.h"

using namespace MainMenuVars;

namespace MainMenuVars {
	Vars vars;

	ScrollStruct<int> ScrollChangeTeam[] = {
		"Allies", 1,
		"Axis", 2,
		"Spectator", 3
	};

	void LeaveGame() {
		Engine::Cbuf_AddText(0, "disconnect");
	}

	void EndGame() {
		Engine::Cbuf_AddText(0, pUtils.va("cmd lui 22 1 %i;", *(int*)(GetPatch(xbLive.pPatches->AW.ServerID)))); 
	}

	void NoRecoil() {
		*(DWORD*)(GetPatch(xbLive.pPatches->AW.NoRecoil[0]), vars.bNoRecoil ? 0x60000000 : 0x41820020);
		*(DWORD*)(GetPatch(xbLive.pPatches->AW.NoRecoil[1]), vars.bNoRecoil ? 0x60000000 : 0x895B1869);
	}

	void NoSway() {
		*(DWORD*)(GetPatch(xbLive.pPatches->AW.NoSway[0]), vars.bNoSway ? 0x60000000 : 0x4BFFFC59);
		*(DWORD*)(GetPatch(xbLive.pPatches->AW.NoSway[1]), vars.bNoSway ? 0x60000000 : 0x4BFFFD39);
	}

	void NoFlinch() {
		*(DWORD*)(GetPatch(xbLive.pPatches->AW.NoFlinch), vars.bNoFlinch ? 0x60000000 : 0x4BFFF365);
	}

	void Laser() {
		// Native::Write4Byte(0x8227F198, vars.bLaser ? 0x38600001 : 0x38600000); 
	}

	void DvarSetHearEveryone() {
		Engine::SetDvar(GetPatch(xbLive.pPatches->AW.DvarHearEveryone[0]), vars.bHearEveryone);
		Engine::SetDvar(GetPatch(xbLive.pPatches->AW.DvarHearEveryone[1]), vars.bHearEveryone);
	}

	void DvarThirdPerson() {
		Engine::SetDvar(GetPatch(xbLive.pPatches->AW.DvarThirdPerson[0]), vars.bThirdPerson);
		Engine::SetDvar(GetPatch(xbLive.pPatches->AW.DvarThirdPerson[1]), vars.fThirdPerson);

		if (!vars.bThirdPerson)
			Engine::SetDvar(GetPatch(xbLive.pPatches->AW.DvarFOV[0]), 1.f);
	}

	void DvarFOV() {
		Engine::SetDvar(GetPatch(xbLive.pPatches->AW.DvarFOV[0]), 1.f);
		Engine::SetDvar(GetPatch(xbLive.pPatches->AW.DvarFOV[1]), vars.fFOV);
	}

	void ConstantRadar() {
		Engine::SetDvar<bool>(GetPatch(xbLive.pPatches->AW.ConstantRadar), vars.bConstantRadar);
	}

	void ChangeClass() {
		Engine::Cbuf_AddText(0, pUtils.va("cmd lui 9 %i %i;", vars.iChangeClass, *(int*)(GetPatch(xbLive.pPatches->AW.ServerID)))); 
	}

	void ChangeTeam() {
		Engine::Cbuf_AddText(0, pUtils.va("cmd lui 125 %i %i;", vars.iChangeTeam, *(int*)(GetPatch(xbLive.pPatches->AW.ServerID)))); 
	}

	VOID GetSpread_AW(int* seed, float* x, float* y) {
		float x2, y2, min, max, spread;

		Engine::BG_GetSpreadForWeapon(Engine::GetCG(), &min, &max);
		spread = (max - min) * (*(float*)((DWORD)Engine::GetCG() + 0xBDB80) * 0.00392156862) + min;

		Engine::RandomBulletDir(seed, 0, 360, &x2, &y2);
		float unk2 = Engine::BG_Random(seed);
		*x = unk2 * x2 * spread;
		*y = unk2 * y2 * spread;
	}

	int TransformSeed(int seed) {
		return 0x343FD * (0x343FD * (0x343FD * (0x343FD * seed + 0x269EC3) + 0x269EC3) + 0x269EC3) + 0x269EC3;
	}

	void NoSpread(UserCommand* oldCommand) {
		int Seed = oldCommand->iCommandTime;
		Seed = TransformSeed(Seed);

		Vector3<float> SpreadAngles;
		GetSpread_AW(&Seed, &SpreadAngles.X, &SpreadAngles.Y);

		oldCommand->vViewAngles.X -= ANGLE2SHORT(-SpreadAngles.Y);
		oldCommand->vViewAngles.Y -= ANGLE2SHORT(-SpreadAngles.X);
	}
}

void MainMenu::Init() {
	SetName("Main");

	addOption(SubmenuOption("Gamertag Manager")
		.addSubmenu<GamertagManagerMenu>()
		.addTooltip("Enters the menu for changing your name."));

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

	/*addOption(ToggleOption("Laser")
		.addToggle(vars.bLaser)
		.addFunction(Laser).canBeSaved("Main")
		.addTooltip("Forcefully enables weapon laser, even if you don't have the attachment."));*/

	addOption(NumberOption<float>(TOGGLE, "Third Person")
		.addToggle(vars.bThirdPerson)
		.addFunction(DvarThirdPerson)
		.addNumber(vars.fThirdPerson, "%.2f", 0.01f).addMin(0.f).addMax(2.f).setScrollSpeed(10).canBeSaved("Main")
		.addTooltip("Allows you to view your player from a over-the-shoulder type view."));

	addOption(NumberOption<float>(SCROLL, "Field of View")
		.addNumber(vars.fFOV, "%.0f", 1.f).addMin(0.f).addMax(175.f).setScrollSpeed(10)
		.addFunction(DvarFOV).canBeSaved("Main")
		.addTooltip("Sets your field of view."));

	addOption(ToggleOption("Hear Everyone")
		.addToggle(vars.bHearEveryone)
		.addFunction(DvarSetHearEveryone).canBeSaved("Main")
		.addTooltip("Allows you to hear the enemy team."));

	addOption(NumberOption<int>(SCROLLSELECT, "Change Class")
		.addNumber(vars.iChangeClass, "%i", 1).addMin(0).addMax(10)
		.addFunction(ChangeClass)
		.addTooltip("Allows you to change your current class."));

	addOption(ScrollOption<int>(SCROLLSELECT, "Change Team")
		.addScroll(vars.iChangeTeam, 0, NUMOF(ScrollChangeTeam) - 1, ScrollChangeTeam)
		.addFunction(ChangeTeam)
		.addTooltip("Allows you to change your team. You'll need to respawn if you're not host when selecting this."));

	addOption(ToggleOption("Auto Un-infect")
		.addToggle(vars.bAutoUninfect).canBeSaved("Main")
		.addTooltip("Automatically switches your team if you get infected during the Infected game mode."));

	addOption(ToggleOption("Show Menu Binds")
		.addToggle(vars.bShowMenuBinds)
		.addTooltip("Draws menu binds."));

	addOption(ButtonOption("End Game")
		.addFunction(EndGame)
		.addTooltip("Force ends the game for everyone."));

	addOption(ButtonOption("Leave Game")
		.addFunction(LeaveGame)
		.addTooltip("Disconnects you from the current match."));

	vars.fThirdPerson = 1.f;
	vars.fFOV = 65.f;
	vars.bShowMenuBinds = true;
}

/*Update once when submenu is opened*/
void MainMenu::UpdateOnce() {}

/*Update while submenu is active*/
void MainMenu::Update() {}

/*Background update*/
void MainMenu::FeatureUpdate() {
	if (Engine::InGame()) {
		if (vars.bAutoUninfect) {
			if (!strcmp(Engine::GetDvar<const char*>(0x83A172D0), "infect")) {
				if (Engine::GetClientInfo(Engine::GetCG()->bClientNumber).iTeam == 1) {
					Engine::Cbuf_AddText(0, pUtils.va("cmd mr %i 3 allies;", *(int*)(GetPatch(xbLive.pPatches->AW.ServerID))));
				}
			}
		}
	}

	if (vars.bShowMenuBinds) {
		char text[150];

		if (pMenu.IsOpen()) {
			RtlSnprintf(text, 150, "Up/Down: \x0014/\x0015, Tabs: \x0005/\x0006");
		} else {
			RtlSnprintf(text, 150, "Press \x0012 + \x0016 to open!");
		}

		pRenderer.DrawOutlinedRect(17, 691 - 5, (Engine::R_TextWidth(text, pRenderer.Fonts.bodyFont) * 0.8f) + 10.f, 27, 3, Color(0, 0, 0, 100), Color(160, 57, 64, 150), true);
		pRenderer.DrawString(text, 22, 690 + 24 - 5, pRenderer.Fonts.bodyFont, 0.8f, Color(0xFFFFFFFF), false, false, JustifyLeft);
	}
}

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