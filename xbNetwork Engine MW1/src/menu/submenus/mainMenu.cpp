#include "stdafx.h"
#include "mainMenu.h"
#include "main/gamertagManagerMenu.h"

using namespace MainMenuVars;

namespace MainMenuVars {
	Vars vars;

	ScrollStruct<int> ScrollChangeTeam[] = {
		"Allies", 0,
		"Axis", 1,
		"Spectator", 2
	};

	void LeaveGame() {
		Engine::Cbuf_AddText(0, "disconnect");
	}

	void EndGame() {
		Engine::Cbuf_AddText(0, pUtils.va("mr %i -1 endround;", *(int*)(GetPatch(xbLive.pPatches->MW1.ServerID)))); 
	}

	void NoRecoil() {
		*(DWORD*)(GetPatch(xbLive.pPatches->MW1.NoRecoil), vars.bNoRecoil ? 0x60000000 : 0x4803DD41);
	}

	void NoSway() {
		*(DWORD*)(GetPatch(xbLive.pPatches->MW1.NoSway[0]), vars.bNoSway ? 0x60000000 : 0x4BFFB3DD);
		*(DWORD*)(GetPatch(xbLive.pPatches->MW1.NoSway[1]), vars.bNoSway ? 0x60000000 : 0x4BFFC3B5);
	}

	void NoFlinch() {
		*(DWORD*)(GetPatch(xbLive.pPatches->MW1.NoFlinch), vars.bNoFlinch ? 0x60000000 : 0x4BFFF8A5);
	}

	void ConstantRadar() {
		*(DWORD*)(GetPatch(xbLive.pPatches->MW1.ConstantRadar), vars.bConstantRadar ? 0x38600001 : 0x4BEAF075);
	}

	void Laser() {
		*(DWORD*)(GetPatch(xbLive.pPatches->MW1.Laser), vars.bLaser ? 0x48000024 : 0x39400000);
	}

	void ChangeClass() {
		Engine::Cbuf_AddText(0, pUtils.va("cmd mr %i 13 custom%i", *(int*)(GetPatch(xbLive.pPatches->MW1.ServerID)), vars.iChangeClass));
	}

	void ChangeTeam() {
		switch (vars.iChangeTeam) {
		case 0:
			Engine::Cbuf_AddText(0, pUtils.va("cmd mr %i 4 allies", *(int*)(GetPatch(xbLive.pPatches->MW1.ServerID))));
			break;
		case 1:
			Engine::Cbuf_AddText(0, pUtils.va("cmd mr %i 4 axis", *(int*)(GetPatch(xbLive.pPatches->MW1.ServerID))));
			break;
		case 2:
			Engine::Cbuf_AddText(0, pUtils.va("cmd mr %i 4 spectator", *(int*)(GetPatch(xbLive.pPatches->MW1.ServerID))));
			break;
		}
	}

	void DvarSetHearEveryone() {
		Engine::SetDvar(GetPatch(xbLive.pPatches->MW1.DvarSetHearEveryone), vars.bHearEveryone);
	}

	void DvarThirdPerson() {
		Engine::SetDvar(GetPatch(xbLive.pPatches->MW1.DvarThirdPerson[0]), vars.bThirdPerson);
		Engine::SetDvar(GetPatch(xbLive.pPatches->MW1.DvarThirdPerson[1]), vars.fThirdPerson);
	}

	void DvarFOV() {
		Engine::SetDvar(GetPatch(xbLive.pPatches->MW1.DvarFOV), vars.fFOV);
	}

	VOID GetSpread_Mw1(int seed, float* x, float* y) {
		float spread = ((float)((*(float*)((DWORD)Engine::GetCG() + 0xF09DC)) * 0.00392156862));

		float min, max, x2, y2;
		DWORD playerState = (((DWORD)Engine::GetCG() + 0x44744));
		DWORD weaponDef = *(DWORD*)(GetPatch(xbLive.pPatches->MW1.WeaponDefPointer) + ((Engine::GetEntity(Engine::GetCG()->iClientNumber).iWeaponIndex) << 2));

		Engine::BG_GetSpreadForWeapon(playerState, weaponDef, &min, &max);
		spread = min + (max - min) * spread;
		Engine::RandomBulletDir(seed, &x2, &y2);
		*x = x2 * spread;
		*y = y2 * spread;
	}

	void NoSpread(UserCommand* oldCommand, UserCommand* nextCommand) {
		int seed = nextCommand->iCommandTime;

		Vector3<float> SpreadAngles;
		GetSpread_Mw1(seed, &SpreadAngles.X, &SpreadAngles.Y);

		oldCommand->vViewAngles.X -= ANGLE2SHORT(-SpreadAngles.Y);
		oldCommand->vViewAngles.Y -= ANGLE2SHORT(-SpreadAngles.X);
	}

	void SpawnBots() {
		Engine::Cbuf_AddText(0, "developer 1;developer_script 1;set scr_testclients 7;fast_restart");
	}
}

void MainMenu::Init() {
	SetName("Main");

#ifndef RELEASE_VERSION
	addOption(ButtonOption("[dev] Spawn Bots")
		.addFunction(SpawnBots));
#endif

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

	addOption(ToggleOption("Laser")
		.addToggle(vars.bLaser)
		.addFunction(Laser).canBeSaved("Main")
		.addTooltip("Forcefully enables weapon laser, even if you don't have the attachment."));

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

	addOption(NumberOption<int>(SCROLLSELECT, "Change Class")
		.addNumber(vars.iChangeClass, "%i", 1).addMin(1).addMax(10)
		.addFunction(ChangeClass)
		.addTooltip("Allows you to change your current class."));

	addOption(ScrollOption<int>(SCROLLSELECT, "Change Team")
		.addScroll(vars.iChangeTeam, 0, NUMOF(ScrollChangeTeam) - 1, ScrollChangeTeam)
		.addFunction(ChangeTeam)
		.addTooltip("Allows you to change your team. You'll need to respawn if you're not host when selecting this."));

	addOption(ToggleOption("Show Menu Binds")
		.addToggle(vars.bShowMenuBinds)
		.addTooltip("Draws menu binds."));

	addOption(ButtonOption("End Game")
		.addFunction(EndGame)
		.addTooltip("Force ends the game for everyone."));

	addOption(ButtonOption("Leave Game")
		.addFunction(LeaveGame)
		.addTooltip("Disconnects you from the current match."));

	vars.fThirdPerson = 30.f;
	vars.fFOV = 65.f;
	vars.iChangeClass = 1;
	vars.bShowMenuBinds = true;
}

/*Update once when submenu is opened*/
void MainMenu::UpdateOnce() {}

/*Update while submenu is active*/
void MainMenu::Update() {}

/*Background update*/
void MainMenu::FeatureUpdate() {
	if (vars.bShowMenuBinds) {
		char text[150];

		if (pMenu.IsOpen()) {
			RtlSnprintf(text, 150, "Up/Down: \x0014/\x0015, Tabs: \x0005/\x0006");
		} else {
			RtlSnprintf(text, 150, "Press \x0012 + \x0016 to open!");
		}

		pRenderer.DrawOutlinedRect(17, 691 - 5, (Engine::R_TextWidth(text, pRenderer.Fonts.normalFont) * 0.8f) + 10.f, 27, 3, Color(0, 0, 0, 100), Color(160, 57, 64, 150), true);
		pRenderer.DrawString(text, 22, 690 + 24, pRenderer.Fonts.normalFont, 0.8f, Color(0xFFFFFFFF), false, false, JustifyLeft);
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