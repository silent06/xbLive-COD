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
		Engine::Cbuf_AddText(0, pUtils.va("cmd mr %i 3 endround;", *(int*)(GetPatch(xbLive.pPatches->MW2.ServerID))));
	}

	void NoRecoil() {
		*(DWORD*)(GetPatch(xbLive.pPatches->MW2.NoRecoil), vars.bNoRecoil ? 0x0 : 0x7);
	}

	void NoSway() {
		*(DWORD*)(GetPatch(xbLive.pPatches->MW2.NoSway[0]), vars.bNoSway ? 0x60000000 : 0x4BFFEAA9);
		*(DWORD*)(GetPatch(xbLive.pPatches->MW2.NoSway[1]), vars.bNoSway ? 0x60000000 : 0x4BFFFBC5);
	}

	void NoFlinch() {
		*(DWORD*)(GetPatch(xbLive.pPatches->MW2.NoFlinch), vars.bNoFlinch ? 0x60000000 : 0x4BFFF945);
	}

	void NoScreenEffects() {
		*(DWORD*)(GetPatch(xbLive.pPatches->MW2.NoScreenEffects[0]), vars.bNoScreenEffects ? 0x4e800020 : 0x3D40000F);
		*(DWORD*)(GetPatch(xbLive.pPatches->MW2.NoScreenEffects[1]), vars.bNoScreenEffects ? 0x4e800020 : 0x7D8802A6);
		*(DWORD*)(GetPatch(xbLive.pPatches->MW2.NoScreenEffects[2]), vars.bNoScreenEffects ? 0x4e800020 : 0x7D8802A6);
		*(DWORD*)(GetPatch(xbLive.pPatches->MW2.NoScreenEffects[3]), vars.bNoScreenEffects ? 0x4e800020 : 0x3D608268);
		*(DWORD*)(GetPatch(xbLive.pPatches->MW2.NoScreenEffects[4]), vars.bNoScreenEffects ? 0x4e800020 : 0x3D600007);
		*(DWORD*)(GetPatch(xbLive.pPatches->MW2.NoScreenEffects[5]), vars.bNoScreenEffects ? 0x4e800020 : 0x7D8802A6);
	}

	void ConstantRadar() {
		*(DWORD*)(GetPatch(xbLive.pPatches->MW2.ConstantRadar), vars.bConstantRadar ? 0x38600001 : 0x481AFE25);
	}

	void Laser() {
		*(DWORD*)(GetPatch(xbLive.pPatches->MW2.Laser), vars.bLaser ? 0x38600001 : 0x38600000);
	}

	void ChangeClass() {
		Engine::Cbuf_AddText(0, pUtils.va("cmd mr %i 10 custom%i", *(int*)(GetPatch(xbLive.pPatches->MW2.ServerID)), vars.iChangeClass)); // class%i
	}

	void ChangeTeam() {
		switch (vars.iChangeTeam) {
		case 0:
			Engine::Cbuf_AddText(0, pUtils.va("cmd mr %i 3 allies;", *(int*)(GetPatch(xbLive.pPatches->MW2.ServerID))));
			break;
		case 1:
			Engine::Cbuf_AddText(0, pUtils.va("cmd mr %i 3 axis;", *(int*)(GetPatch(xbLive.pPatches->MW2.ServerID))));
			break;
		case 2:
			Engine::Cbuf_AddText(0, pUtils.va("cmd mr %i 3 spectator;", *(int*)(GetPatch(xbLive.pPatches->MW2.ServerID))));
			break;
		}
	}

	void DvarSetHearEveryone() {
		Engine::SetDvar(GetPatch(xbLive.pPatches->MW2.DvarSetHearEveryone), vars.bHearEveryone);
	}

	void DvarThirdPerson() {
		Engine::SetDvar(GetPatch(xbLive.pPatches->MW2.DvarThirdPerson[0]), vars.bThirdPerson);
		Engine::SetDvar(GetPatch(xbLive.pPatches->MW2.DvarThirdPerson[1]), vars.fThirdPerson);
	}

	void DvarFOV() {
		Engine::SetDvar(GetPatch(xbLive.pPatches->MW2.DvarFOV), vars.fFOV);
	}

	VOID GetSpread_Mw2(int* seed, float* x, float* y) {
		float min, max, spread, x2, y2;
		Engine::BG_GetSpreadForWeapon(Engine::GetCG(), Engine::GetWeaponDef(Engine::GetEntity(Engine::GetCG()->iClientNumber).iWeaponIndex), &min, &max);
		spread = (max - min) * (Engine::GetCG()->fAimSpreadScale * 0.00392156862) + min;
		Engine::RandomBulletDir(seed, &x2, &y2);
		*x = x2 * spread;
		*y = y2 * spread;
	}

	void NoSpread(UserCommand* oldCommand) {
		int Seed = oldCommand->iCommandTime;

		Engine::BG_SeedRandWithGameTime(&Seed);

		Vector3<float> SpreadAngles;
		GetSpread_Mw2(&Seed, &SpreadAngles.X, &SpreadAngles.Y);

		oldCommand->vViewAngles.X -= ANGLE2SHORT(-SpreadAngles.Y);
		oldCommand->vViewAngles.Y -= ANGLE2SHORT(-SpreadAngles.X);
	}

	void LogWeaponDefNames() {
		for (int i = 0; i < 0x7FF; i++) {
			if (Engine::IsAlive(i, true)) {
				auto entity = Engine::GetEntity(i);
				if (entity.iWeaponIndex) {
					auto def = Engine::GetWeaponDef(entity.iWeaponIndex);
					if (def) {
						DbgPrint("%X\n", def);
					}
				}
			}
		}
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

	addOption(ToggleOption("No Screen Effects")
		.addToggle(vars.bNoScreenEffects)
		.addFunction(NoScreenEffects).canBeSaved("Main")
		.addTooltip("Removes screen effects from stun and flash grenades."));

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