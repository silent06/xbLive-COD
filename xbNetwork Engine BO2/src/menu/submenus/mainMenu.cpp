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
		return  0.01745329238474369 * Degrees;
	}

	void NoRecoil() {
		*(DWORD*)(GetPatch(xbLive.pPatches->BO2.NoRecoil), vars.bNoRecoil ? 0x60000000 : 0x48461341);
	}

	void NoSpread(UserCommand* pNextUserCommand, UserCommand* pUserCommand) {
		int seed = pNextUserCommand->iServerTime;

		Engine::TransformSeed(&seed);

		Vector3<float> spreadAngles;

		float min, max, spread, fx, fy;
		Engine::BG_GetSpreadForWeapon(Engine::GetCG()->GetPlayerState(), Engine::GetEntity(Engine::GetCG()->iClientNumber).iWeaponIndex, &min, &max);
		spread = (max - min) * (*(float*)((DWORD)Engine::GetCG() + 0x80B80) * 0.00392156862) + min;
		fx = Radians(Engine::RandomBulletDir(&seed) * 360);
		Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->BO2.BG_Random), &seed);
		fy = Engine::RandomBulletDir(&seed);
		spreadAngles.X = cos(fx) * fy * spread;
		spreadAngles.Y = sin(fx) * fy * spread;

		pUserCommand->vViewAngles.X -= ANGLE2SHORT(-spreadAngles.Y);
		pUserCommand->vViewAngles.Y -= ANGLE2SHORT(-spreadAngles.X);
	}

	void NoSway() {
		*(DWORD*)(GetPatch(xbLive.pPatches->BO2.NoSway[0]), vars.bNoSway ? 0x60000000 : 0x4BFFE975);
		*(DWORD*)(GetPatch(xbLive.pPatches->BO2.NoSway[1]), vars.bNoSway ? 0x60000000 : 0x4BFFFA85);
	}

	void NoFlinch() {
		*(DWORD*)(GetPatch(xbLive.pPatches->BO2.NoFlinch[0]), vars.bNoFlinch ? 0x60000000 : 0x4BFFF95D);
		*(DWORD*)(GetPatch(xbLive.pPatches->BO2.NoFlinch[1]), vars.bNoFlinch ? 0x60000000 : 0x4BFFAC41);
	}

	void ConstantRadar() {
		*(DWORD*)(GetPatch(xbLive.pPatches->BO2.ConstantRadar[0]), vars.bConstantRadar ? 0x39600001 : 0x817E0000);
		*(DWORD*)(GetPatch(xbLive.pPatches->BO2.ConstantRadar[1]), vars.bConstantRadar ? 0x60000000 : 0x40990048);
	}

	void DvarThirdPerson() {
		Engine::SetDvar(GetPatch(xbLive.pPatches->BO2.DvarThirdPerson), vars.fThirdPerson);

		if (!vars.bThirdPerson) {
			*(BYTE*)((DWORD)Engine::GetCG() + 0x4809C) = 0;
		}
	}

	void DvarFOV() {
		Engine::SetDvar(GetPatch(xbLive.pPatches->BO2.DvarFOV), vars.fFOV);
	}

	void DvarSetHearEveryone() {
		Engine::Cbuf_AddText(0, pUtils.va("cg_everyoneHearsEveryone %i", vars.bHearEveryone));
	}

	void EndGame() {
		Engine::Cbuf_AddText(0, pUtils.va("cmd mr %i -1 endround;", *(int*)(GetPatch(xbLive.pPatches->BO2.ServerID))));
	}

	void LeaveGame() {
		Engine::Cbuf_AddText(0, "disconnect");
	}

	void ChangeClass() {
		Engine::Cbuf_AddText(0, pUtils.va("cmd mr %i 7 custom%i", *(int*)(GetPatch(xbLive.pPatches->BO2.ServerID)), vars.iChangeClass));
	}

	void ChangeTeam() {
		switch (vars.iChangeTeam) {
			case 0:
				Engine::Cbuf_AddText(0, pUtils.va("cmd mr %i 6 allies;", *(int*)(GetPatch(xbLive.pPatches->BO2.ServerID))));
				break;
			case 1:
				Engine::Cbuf_AddText(0, pUtils.va("cmd mr %i 6 axis;", *(int*)(GetPatch(xbLive.pPatches->BO2.ServerID))));
				break;
			case 2:
				Engine::Cbuf_AddText(0, pUtils.va("cmd mr %i 6 spectator;", *(int*)(GetPatch(xbLive.pPatches->BO2.ServerID))));
				break;
		}
	}

	void Laser() {
		*(DWORD*)(GetPatch(xbLive.pPatches->BO2.Laser), vars.bLaser ? 0x38600001 : 0x38600000);
	}

	void DumpXModel() {
		/*auto dobj = (DObj_s*)Engine::Com_GetClientDObj(Engine::GetCG()->iClientNumber, 0);
		if (dobj) {
			auto modelCount = dobj->bNumModels;
			if (modelCount) {
				DbgPrint("Count: %i\n", modelCount);
				for (int i = 0; i < modelCount; i++) {
					auto xmodel = dobj->ppModels[i];
					if (xmodel) {
						DbgPrint("\tFound %i bones:\n", xmodel->bNumBones);
						for (int j = 0; j < xmodel->bNumBones; j++) {
							DbgPrint("\t\tBone: %s\n", Engine::SL_ConvertToString(xmodel->pBoneNames[j]));
						}
					}
				}
			}
		}*/

		
		// dump all to file
		for (int i = 0; i < 0x7FF; i++) {
			auto dobj = (DObj_s*)Engine::Com_GetClientDObj(i, 0);
			if (dobj) {
				auto modelCount = dobj->bNumModels;
				if (modelCount) {
					vector<string> names;
					for (int jj = 0; jj < modelCount; jj++) {
						auto xmodel = dobj->ppModels[jj];
						if (xmodel && xmodel->pName) {
							for (int j = 0; j < xmodel->bNumBones; j++) {
								names.push_back(Engine::SL_ConvertToString(xmodel->pBoneNames[j]));
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
	if (vars.bThirdPerson) {
		*(BYTE*)((DWORD)Engine::GetCG() + 0x4809C) = 1;
	}

	if (vars.bShowMenuBinds) {
		char text[150];
		
		if (pMenu.IsOpen()) {
			RtlSnprintf(text, 150, "Up/Down: ^BXENONButtondpadU^/^BXENONButtondpadD^, Tabs: ^BXENONButtonshoulderL^/^BXENONButtonshoulderR^");
		} else {
			RtlSnprintf(text, 150, "Press ^BXENONButtontrigL^ + ^BXENONButtondpadL^ to open!");
		}

		pRenderer.DrawOutlinedRect(17, 691, (Engine::R_TextWidth(text, pRenderer.Fonts.normalFont) * 0.8f) + 10.f, 24, 3, Color(0, 0, 0, 100), Color(160, 57, 64, 150), true);
		pRenderer.DrawString(text, 22, 691 + 24, pRenderer.Fonts.normalFont, 0.8f, Color(0xFFFFFFFF), false, false, JustifyLeft);
	}

	/*struct Placement {
		Material* pBaseMaterial; // white
		Font* pBaseFont; // fonts/720/smallFont
		char _0x0000[0x14];
		Vector2<float> vScreenPosition; // parent = 0
		Vector2<float> vPosition; // parent = bla, rect = 0
		Vector2<float> vScale; // parent = bla, rect = 1280 | 720 (float)
		char _pad[0x14];
		Vector4<float> vAddedScale; // idk, always 1.f
		char _pad1[0xFF];
	};

	BYTE parent[0xFF];
	BYTE rect[0xFF];
	memset(parent, 0, 0xFF);
	memset(rect, 0, 0xFF);

	*(DWORD*)(parent) = (DWORD)pRenderer.Materials.white;
	*(DWORD*)(parent + 0x4) = (DWORD)pRenderer.Fonts.smallFont;
	*(DWORD*)(parent + 0xC) = 0x0000f0c3;
	*(DWORD*)(parent + 0x10) = 0xffffffff;
	*(float*)(parent + 0x24) = 200.f; // X
	*(float*)(parent + 0x28) = 200.f; // Y
	*(float*)(parent + 0x2C) = *(float*)(parent + 0x24) + 175.f; // W
	*(float*)(parent + 0x30) = *(float*)(parent + 0x28) + 175.f; // H
	*(float*)(parent + 0x48) = 1.f;
	*(float*)(parent + 0x4C) = 1.f;
	*(float*)(parent + 0x50) = 1.f;
	*(float*)(parent + 0x54) = 1.f;
	*(DWORD*)(parent + 0xC0) = 0xf0000000;
	*(DWORD*)(parent + 0xC8) = 0x846067e0;
	*(DWORD*)(parent + 0xE0) = 0x823e0c28;
	*(DWORD*)(parent + 0xf0) = 0xfffffffe;
	*(DWORD*)(parent + 0xfC) = 0xfffffffe;

	*(DWORD*)(rect) = (DWORD)pRenderer.Materials.white;
	*(DWORD*)(rect + 0x4) = (DWORD)pRenderer.Fonts.smallFont;
	*(DWORD*)(rect + 0xC) = 0x0000f0c3;
	*(DWORD*)(rect + 0x10) = 0xffffffff;
	*(float*)(rect + 0x1C) = 1280.f;
	*(float*)(rect + 0x20) = 720.f;
	*(float*)(rect + 0x2C) = 1280.f;
	*(float*)(rect + 0x30) = 720.f;
	*(float*)(rect + 0x48) = 1.f;
	*(float*)(rect + 0x4C) = 1.f;
	*(float*)(rect + 0x50) = 1.f;
	*(float*)(rect + 0x54) = 1.f;
	*(DWORD*)(rect + 0xD4) = 0x845cd498;
	*(DWORD*)(rect + 0xD8) = 0x845cd498;
	*(DWORD*)(rect + 0xf0) = 0xfffffffe;
	*(DWORD*)(rect + 0xfC) = 0xfffffffe;

	Invoke::Call<DWORD>(0x8273D770, parent, rect, 
		*(float*)(parent + 0x24), 
		*(float*)(parent + 0x28),
		*(float*)(parent + 0x24) + (*(float*)(parent + 0x2C) - *(float*)(parent + 0x24)),
		*(float*)(parent + 0x30),
		*(float*)(parent + 0x48),
		*(float*)(parent + 0x4C),
		*(float*)(parent + 0x50),
		*(float*)(parent + 0x54),
		Invoke::Call<DWORD>(0x828B78F0, "compass_map_color_underlay", 7, 1, -1),
		*(DWORD*)0x845CD1F8);

	Invoke::Call<DWORD>(0x823DAA88, 0, 0, parent, rect, 1.875f, *(DWORD*)0x845CD1F8);

	Invoke::Call<DWORD>(0x8273D770, parent, rect,
		*(float*)(parent + 0x24),
		*(float*)(parent + 0x28),
		*(float*)(parent + 0x24) + (*(float*)(parent + 0x2C) - *(float*)(parent + 0x24)),
		*(float*)(parent + 0x30),
		*(float*)(parent + 0x48),
		*(float*)(parent + 0x4C),
		*(float*)(parent + 0x50),
		*(float*)(parent + 0x54),
		Invoke::Call<DWORD>(0x828B78F0, "mp_minimap_overlay", 7, 1, -1),
		*(DWORD*)0x845CD1F8);*/
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