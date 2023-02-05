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
		Engine::Cbuf_AddText(0, pUtils.va("cmd lui 9 1 %i;", *(int*)(GetPatch(xbLive.pPatches->GHOSTS.ServerID))));
	}

	void NoRecoil() {
		*(DWORD*)(GetPatch(xbLive.pPatches->GHOSTS.NoRecoil), vars.bNoRecoil ? 0x60000000 : 0x4BF8AE4D);
	}

	void NoSway() {
		*(DWORD*)(GetPatch(xbLive.pPatches->GHOSTS.NoSway[0]), vars.bNoSway ? 0x60000000 : 0x4BFFEAA1);
		*(DWORD*)(GetPatch(xbLive.pPatches->GHOSTS.NoSway[1]), vars.bNoSway ? 0x60000000 : 0x4BFFFBA5);
	}

	void NoFlinch() {
		*(DWORD*)(GetPatch(xbLive.pPatches->GHOSTS.NoFlinch), vars.bNoFlinch ? 0x60000000 : 0x4BFFF91D);
	}

	void Laser() {
		*(DWORD*)(GetPatch(xbLive.pPatches->GHOSTS.Laser),vars.bLaser ? 0x38600001 : 0x38600000);
	}

	void DvarSetHearEveryone() {
		Engine::SetDvar(GetPatch(xbLive.pPatches->GHOSTS.DvarSetHearEveryone[0]), vars.bHearEveryone);
		Engine::SetDvar(GetPatch(xbLive.pPatches->GHOSTS.DvarSetHearEveryone[1]), vars.bHearEveryone);
	}

	void DvarThirdPerson() {
		Engine::SetDvar(GetPatch(xbLive.pPatches->GHOSTS.DvarThirdPerson[0]), vars.bThirdPerson);
		Engine::SetDvar(GetPatch(xbLive.pPatches->GHOSTS.DvarThirdPerson[1]), vars.fThirdPerson);
	}

	void DvarFOV() {
		Engine::SetDvar(GetPatch(xbLive.pPatches->GHOSTS.DvarFOV), vars.fFOV);
	}

	void ConstantRadar() {
		Engine::SetDvar<bool>(GetPatch(xbLive.pPatches->GHOSTS.ConstantRadar[0]), vars.bConstantRadar);

		*(DWORD*)GetPatch(xbLive.pPatches->GHOSTS.ConstantRadar[1]) = vars.bConstantRadar ? 0x60000000 : 0x419A0008;
		*(DWORD*)GetPatch(xbLive.pPatches->GHOSTS.ConstantRadar[2]) = vars.bConstantRadar ? 0x4800000C : 0x409A000C;
		*(DWORD*)GetPatch(xbLive.pPatches->GHOSTS.ConstantRadar[3]) = vars.bConstantRadar ? 0x60000000 : 0x419A0110;
	}

	void ChangeClass() {
		Engine::Cbuf_AddText(0, pUtils.va("cmd lui 5 %i %i;", vars.iChangeClass, *(int*)(GetPatch(xbLive.pPatches->GHOSTS.ServerID))));
	}

	void ChangeTeam() {
		Engine::Cbuf_AddText(0, pUtils.va("cmd lui 68 %i %i;", ScrollChangeTeam[vars.iChangeTeam].Result, *(int*)(GetPatch(xbLive.pPatches->GHOSTS.ServerID))));
	}

	VOID GetSpread_Ghost(int* seed, float* x, float* y) {
		float x2, y2, min, max, spread;
		Engine::BG_GetSpreadForWeapon(Engine::GetCG(), Engine::GetEntity(Engine::GetCG()->iClientNumber).iWeaponIndex, &min, &max);

		spread = (max - min) * (*(float*)((DWORD)Engine::GetCG() + 0xC77E0) * 0.00392156862) + min;
		Engine::RandomBulletDir(seed, 0, 360, &x2, &y2);
		float HAX = Engine::BG_Random(seed);

		*x = spread * x2 * HAX;
		*y = spread * y2 * HAX;
	}

	void NoSpread(UserCommand* oldCommand) {
		int Seed = oldCommand->iCommandTime;
		Engine::BG_SeedRandWithGameTime(&Seed);

		Vector3<float> SpreadAngles;
		GetSpread_Ghost(&Seed, &SpreadAngles.X, &SpreadAngles.Y);

		// Apply our no spread
		oldCommand->vViewAngles.X -= ANGLE2SHORT(-SpreadAngles.Y);
		oldCommand->vViewAngles.Y -= ANGLE2SHORT(-SpreadAngles.X);
	}

	void DumpXModel() {
		/*for (int i = 0; i < 0x7FF; i++) {
			auto dobj = (DObj_s*)Engine::Com_GetClientDObj(i, 0);
			if (dobj) {
				auto modelCount = dobj->GetModelCount();
				if (modelCount) {
					vector<string> names;
					for (int jj = 0; jj < modelCount; jj++) {
						auto xmodel = dobj->ppModels[jj];
						if (xmodel && xmodel->pName) {
							for (int j = 0; j < xmodel->bNumBones; j++) {
								auto str = Invoke::Call<const char*>(0x82492318, xmodel->pBoneNames[j]);
								if (str) {
									names.push_back(str);
								}
							}

							FILE* fp = fopen(pUtils.va("XBLIVE:\\XModels\\%s.txt", xmodel->pName), "w");
							if (fp) {
								for (int fff = 0; fff < names.size(); fff++) {
									fprintf(fp, "%s\n", names[fff].c_str());
								}
								fclose(fp);
							}
						}
					}
				}
			}
		}*/
	}

	void LogWeaponDefNames() {
		for (int i = 0; i < 0x7FF; i++) {
			if (Engine::IsAlive(i, true)) {
				auto entity = Engine::GetEntity(i);
				if (entity.iWeaponIndex) {
					auto def = *(DWORD*)(0x82A96FD0 + ((entity.iWeaponIndex * 4) & 0x3FC));
					if (def) {
						DbgPrint("%s\n", (char*)*(DWORD*)(def));
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
			if (!strcmp(Engine::GetDvar<const char*>(GetPatch(xbLive.pPatches->GHOSTS.ui_gametype)), "infect")) {
				if (Engine::GetCG()->ClientTeam[Engine::GetCG()->iClientNumber].iTeam == 1) {
					Engine::Cbuf_AddText(0, pUtils.va("cmd mr %i 3 allies;", *(int*)(GetPatch(xbLive.pPatches->GHOSTS.ServerID))));
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