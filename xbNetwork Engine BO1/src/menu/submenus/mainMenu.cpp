#include "stdafx.h"
#include "mainMenu.h"
#include "main/gamertagManagerMenu.h"
#include "visual/espMenu.h"

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
		*(DWORD*)(GetPatch(xbLive.pPatches->BO1.NoRecoil), vars.bNoRecoil ? 0x60000000 : 0x4BF67EC5);
	}

	void NoSway() {
		*(DWORD*)(GetPatch(xbLive.pPatches->BO1.NoSway), vars.bNoSway ? 0x60000000 : 0x4BFFEB09);
	}

	void NoFlinch() {
		*(DWORD*)(GetPatch(xbLive.pPatches->BO1.NoFlinch), vars.bNoFlinch ? 0x60000000 : 0x4BFFF77D);
	}

	void ConstantRadar() {
		*(DWORD*)(GetPatch(xbLive.pPatches->BO1.ConstantRadar), vars.bConstantRadar ? 0x60000000 : 0x419A0050);
	}

	void DvarThirdPerson() {
		Engine::SetDvar(GetPatch(xbLive.pPatches->BO1.DvarThirdPerson[0]), vars.fThirdPerson);
		Engine::SetDvar(GetPatch(xbLive.pPatches->BO1.DvarThirdPerson[1]), vars.bThirdPerson);
	}

	void DvarFOV() {
		Engine::SetDvar(GetPatch(xbLive.pPatches->BO1.DvarFOV), vars.fFOV);
	}

	void DvarSetHearEveryone() {
		Engine::Cbuf_AddText(0, pUtils.va("cg_everyoneHearsEveryone %i", vars.bHearEveryone));
	}

	void EndGame() {
		Engine::Cbuf_AddText(0, pUtils.va("cmd mr %i -1 endround;", *(int*)(GetPatch(xbLive.pPatches->BO1.ServerId)))); 
	}

	void LeaveGame() {
		Engine::Cbuf_AddText(0, "disconnect");
	}

	void ChangeClass() {
		Engine::Cbuf_AddText(0, pUtils.va("cmd mr %i 6 custom%i", *(int*)(GetPatch(xbLive.pPatches->BO1.ServerId)), vars.iChangeClass)); 
	}

	void ChangeTeam() {
		switch (vars.iChangeTeam) {
		case 0:
			Engine::Cbuf_AddText(0, pUtils.va("cmd mr %i 4 allies;", *(int*)(GetPatch(xbLive.pPatches->BO1.ServerId)))); 
			break;
		case 1:
			Engine::Cbuf_AddText(0, pUtils.va("cmd mr %i 4 axis;", *(int*)(GetPatch(xbLive.pPatches->BO1.ServerId)))); 
			break;
		case 2:
			Engine::Cbuf_AddText(0, pUtils.va("cmd mr %i 4 spectator;", *(int*)(GetPatch(xbLive.pPatches->BO1.ServerId)))); 
			break;
		}
	}

	void GetSpread_BO1(int* seed, float* x, float* y) {
		float flSpread, Spread, FinalSpread, minSpread, maxSpread, fx, fy;
		int randSeed = *seed;

		fx = Radians(Engine::RandomBulletDir(&randSeed) * 360);
		fy = Engine::RandomBulletDir(&randSeed);

		flSpread = *(float*)((DWORD)Engine::GetCG() + 0x69264);
		Spread = (flSpread * 0.00392156862);

		Engine::BG_GetSpreadForWeapon(Engine::GetCG()->GetPlayerState(), Engine::GetWeaponDef(Engine::GetEntity(Engine::GetCG()->iClientNumber).dwWeaponIndex), &minSpread, &maxSpread);
		FinalSpread = minSpread + ((maxSpread - minSpread) * Spread);

		*x = cos(fx) * fy * FinalSpread;
		*y = sin(fx) * fy * FinalSpread;
	}

	void NoSpread(UserCommand* pNextUserCommand, UserCommand* pUserCommand) {
		int Seed = pNextUserCommand->iServerTime;

		Vector3<float> SpreadAngles;
		GetSpread_BO1(&Seed, &SpreadAngles.X, &SpreadAngles.Y);

		pUserCommand->vViewAngles.X -= ANGLE2SHORT(-SpreadAngles.Y);
		pUserCommand->vViewAngles.Y -= ANGLE2SHORT(-SpreadAngles.X);
	}

	void DumpXModel() {
		/*for (int i = 0; i < 0x7FF; i++) {
			auto dobj = (DObj_s*)Engine::Com_GetClientDObj(i, 0);
			if (dobj) {
				auto modelCount = dobj->bNumModels;
				if (modelCount) {
					vector<string> names;
					for (int jj = 0; jj < modelCount; jj++) {
						auto xmodel = dobj->ppModels[jj];
						if (xmodel && xmodel->pName) {
							for (int j = 0; j < xmodel->bNumBones; j++) {
								auto str = Invoke::Call<const char*>(0x82460778, xmodel->pBoneNames[j], 0);
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

		for (int i = 0; i < 0x7FF; i++) {
			if (Engine::IsAlive(i)) {
				auto pos = Engine::GetTagPosition(i, "j_tail_base");
				if (!pos.IsNull()) {
					pUtils.WriteFile(pUtils.va("XBLIVE:\\dog_team_%i.bin", Engine::GetCG()->ClientInfo[Engine::GetCG()->iClientNumber].iTeam), &Engine::GetEntityPtr()[i], sizeof(Entity));
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
	/*
		0001 = A
		0002 = B
		0003 = X
		0004 = Y
		0005 = LB
		0006 = RB
		0010 = LS DOWN
		0011 = RS DOWN
		0012 = LT
		0013 = RT
		0014 = DPAD UP
		0015 = DPAD DOWN
		0016 = DPAD LEFT
		0017 = DPAD RIGHT
		0018 = LS CLICK
		0019 = RS CLICK
	*/

	if (vars.bShowMenuBinds) {
		char text[150];

		if (pMenu.IsOpen()) {
			RtlSnprintf(text, 150, "Up/Down: \x0014/\x0015, Tabs: \x0005/\x0006");
		} else {
			RtlSnprintf(text, 150, "Press \x0012 + \x0016 to open!");
		}

		pRenderer.DrawOutlinedRect(17, 691 - 5, (Engine::R_TextWidth(text, pRenderer.Fonts.normalFont) * 0.8f) + 10.f, 27, 3, Color(0, 0, 0, 100), Color(160, 57, 64, 150), true);
		pRenderer.DrawString(text, 22, 690 + 24 - 5, pRenderer.Fonts.normalFont, 0.8f, Color(0xFFFFFFFF), false, false, JustifyLeft);
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