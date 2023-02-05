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

	void Juggernaut() {
		Engine::Cbuf_AddText(0, pUtils.va("cmd mr %i 10 axis;", *(int*)(GetPatch(xbLive.pPatches->MW3.ServerID))));
	}

	void LeaveGame() {
		Engine::Cbuf_AddText(0, "disconnect");
	}

	void EndGame() {
		Engine::Cbuf_AddText(0, pUtils.va("cmd mr %i 3 endround;", *(int*)(GetPatch(xbLive.pPatches->MW3.ServerID))));
	}

	void NoRecoil() {
		*(DWORD*)(GetPatch(xbLive.pPatches->MW3.NoRecoil), vars.bNoRecoil ? 0x0 : 0x7);
	}

	void NoSway() {
		*(DWORD*)(GetPatch(xbLive.pPatches->MW3.NoSway[0]), vars.bNoSway ? 0x60000000 : 0x4BFFEA61);
		*(DWORD*)(GetPatch(xbLive.pPatches->MW3.NoSway[1]), vars.bNoSway ? 0x60000000 : 0x4BFFFB9D);
	}

	void NoFlinch() {
		*(DWORD*)(GetPatch(xbLive.pPatches->MW3.NoFlinch), vars.bNoFlinch ? 0x4e800020 : 0x7D8802A6);
	}

	void NoScreenEffects() {
		*(DWORD*)(GetPatch(xbLive.pPatches->MW3.NoScreenEffects[0]), vars.bNoScreenEffects ? 0x4e800020 : 0x3D400010);
		*(DWORD*)(GetPatch(xbLive.pPatches->MW3.NoScreenEffects[1]), vars.bNoScreenEffects ? 0x4e800020 : 0x7D8802A6);
		*(DWORD*)(GetPatch(xbLive.pPatches->MW3.NoScreenEffects[2]), vars.bNoScreenEffects ? 0x4e800020 : 0x7D8802A6);
		*(DWORD*)(GetPatch(xbLive.pPatches->MW3.NoScreenEffects[3]), vars.bNoScreenEffects ? 0x4e800020 : 0x3D400000);
		*(DWORD*)(GetPatch(xbLive.pPatches->MW3.NoScreenEffects[4]), vars.bNoScreenEffects ? 0x4e800020 : 0x3D600007);
		*(DWORD*)(GetPatch(xbLive.pPatches->MW3.NoScreenEffects[5]), vars.bNoScreenEffects ? 0x4e800020 : 0x7D8802A6);
	}

	void ConstantRadar() {
		*(DWORD*)(GetPatch(xbLive.pPatches->MW3.ConstantRadar), vars.bConstantRadar ? 0x3B800001 : 0x557C87FE);
	}

	void Laser() {
		*(DWORD*)(GetPatch(xbLive.pPatches->MW3.Laser),vars.bLaser ? 0x38600001 : 0x38600000);
	}

	void ChangeClass() {
		Engine::Cbuf_AddText(0, pUtils.va("cmd mr %i 10 custom%i", *(int*)(GetPatch(xbLive.pPatches->MW3.ServerID)), vars.iChangeClass));
	}

	void ChangeTeam() {
		switch (vars.iChangeTeam) {
		case 0:
			Engine::Cbuf_AddText(0, pUtils.va("cmd mr %i 3 allies;", *(int*)(GetPatch(xbLive.pPatches->MW3.ServerID))));
			break;
		case 1:
			Engine::Cbuf_AddText(0, pUtils.va("cmd mr %i 3 axis;", *(int*)(GetPatch(xbLive.pPatches->MW3.ServerID))));
			break;
		case 2:
			Engine::Cbuf_AddText(0, pUtils.va("cmd mr %i 3 spectator;", *(int*)(GetPatch(xbLive.pPatches->MW3.ServerID))));
			break;
		}
	}

	void DvarSetHearEveryone() {
		Engine::SetDvar(GetPatch(xbLive.pPatches->MW3.DvarSetHearEveryone[0]), vars.bHearEveryone);
		Engine::SetDvar(GetPatch(xbLive.pPatches->MW3.DvarSetHearEveryone[1]), vars.bHearEveryone);
	}

	void DvarThirdPerson() {
		Engine::SetDvar(GetPatch(xbLive.pPatches->MW3.DvarThirdPerson[0]), vars.bThirdPerson);
		Engine::SetDvar(GetPatch(xbLive.pPatches->MW3.DvarThirdPerson[1]), vars.fThirdPerson);
	}

	void DvarFOV() {
		Engine::SetDvar(GetPatch(xbLive.pPatches->MW3.DvarFOV), vars.fFOV);
	}

	VOID GetSpread_Mw3(int* seed, float* x, float* y) {
		float min, max, spread, x2, y2;
		Engine::BG_GetSpreadForWeapon(Engine::GetCG(), Engine::GetEntity(Engine::GetCG()->iClientNumber).iWeaponIndex, &min, &max);
		spread = (max - min) * (Engine::GetCG()->fAimSpreadScale * 0.00392156862) + min;
		Engine::RandomBulletDir(seed, &x2, &y2);
		*x = x2 * spread;
		*y = y2 * spread;
	}

	void NoSpread(UserCommand* oldCommand) {
		int Seed = oldCommand->iCommandTime;

		Engine::BG_SeedRandWithGameTime(&Seed);

		Vector3<float> SpreadAngles;
		GetSpread_Mw3(&Seed, &SpreadAngles.X, &SpreadAngles.Y);

		oldCommand->vViewAngles.X -= ANGLE2SHORT(-SpreadAngles.Y);
		oldCommand->vViewAngles.Y -= ANGLE2SHORT(-SpreadAngles.X);
	}

	namespace Bots {
		int getClient_s(int clientNum) {
			return *(int*)0x836C6310 + (clientNum * 0x68B80);
		}

		int bPort = 0;

		int SpawnAvaliableBot() {
			for (bPort = 0; bPort < 18; bPort++)
				if (!Engine::IsAlive(bPort, true))
					break;

			if (bPort == 18)
				return -1;

			printf("using entity %i\n", bPort);

			DWORD protocol = ((DWORD(*)())0x8232A320)();
			DWORD checksum = ((DWORD(*)())0x820E0B50)();

			DWORD rand1 = ((DWORD(*)(int, int))0x8226FC80)(0, INT_MAX);
			DWORD rand2 = ((DWORD(*)(int, int))0x8226FC80)(0, INT_MAX);

			char* connectBuffer = new char[0x400];
			sprintf(connectBuffer, "connect bot%d \"\\rate\\20000\\name\\bot%d\\natType\\1\\rank\\1\\prestige\\1\\ec_usingTag\\0\\ec_usingTitle\\0\\ec_TitleBg\\0\\ec_Level\\0\\ptd_prestige_black_ops\\0\\ptd_rank_black_ops\\0\\ptd_prestige_mw2\\0\\ptd_rank_mw2\\0\\ptd_prestige_world_at_war\\0\\ptd_rank_world_at_war\\0\\ptd_prestige_mw\\0\\ptd_rank_mw\\0\\protocol\\%i\\checksum\\%i\\challenge\\0\\statver\\26 3648679816\\invited\\1\\xuid\\%08x%08x\\onlineStats\\0\\migrating\\0\"", bPort - 1, bPort, protocol, checksum, rand1, rand2);
			((void(*)(const char*))0x822889F0)(connectBuffer);
			delete[] connectBuffer;

			((void(*)(int, int))0x822C8AB0)(0, bPort);
			((void(*)())0x82288A10)();

			int elPtr = getClient_s(bPort);
			if (elPtr == 0) return -1;

			*(short*)(elPtr + 0x352E6) = 0x3FF;
			*(int*)(elPtr + 0x352EC) = 1;

			UserCommand cmd;
			((void(*)(int))0x822C6DD0)(elPtr);
			((void(*)(int, UserCommand*))0x822C6F50)(elPtr, &cmd);

			return bPort;
		}

		void Scr_AddString(const char* value) {
			((void(*)(const char*))0x822BFC68)(value);
		}

		void Scr_NotifyNum(int entityNum, int classNum, int stringValue, int paramcount) {
			((void(*)(int, int, int, int))0x822BE548)(entityNum, classNum, stringValue, paramcount);
		}

		int SL_GetString(const char* string) {
			return ((int(*)(const char*, int))0x822B5C98)(string, 0);
		}

		void botPickTeam(int botNum, int* handle, handleCall_t type) {
			Scr_AddString("autoassign");
			Scr_AddString("team_marinesopfor");
			Scr_NotifyNum(botNum, 0, SL_GetString("menuresponse"), 2);
		}

		void botPickClass(int botNum, int* handle, handleCall_t type) {
			Scr_AddString("class2");
			Scr_AddString("changeclass");
			Scr_NotifyNum(botNum, 0, SL_GetString("menuresponse"), 2);
		}

		int HandleHookAllocTemp(int arg, handleCallback function, clock_t start_time) {
			if (function == NULL)
				return 0;
			handle_s* ev;
			for (int i = 1; i < 0x100; i++) {
				ev = &pUtils.m_hookEvents[i];
				if (ev->function == function && ev->arg == arg)
					return i;
				else if (ev->function == NULL) {
					ev->arg = arg;
					ev->function = function;
					ev->type = CALL_TEMP;
					ev->handle = NULL;
					ev->interval = 0;
					ev->startTime = *(int*)(0x82FDA080 + 0x4A8) + start_time;
					ev->time = ev->startTime;
					return (int)i;
				}
			}
			return 0;
		}

		void SpawnBot() {
			int bot = SpawnAvaliableBot();
			if (bot != -1) {
				HandleHookAllocTemp(bot, botPickTeam, 400); //delay this call 400 ms
				HandleHookAllocTemp(bot, botPickClass, 600); //delay this call 600 ms
			}
		}
	}
}

void MainMenu::Init() {
	SetName("Main");

#ifndef RELEASE_VERSION
	addOption(ButtonOption("[dev] Spawn Bots")
		.addFunction(Bots::SpawnBot));
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

	addOption(ToggleOption("Auto Un-infect")
		.addToggle(vars.bAutoUninfect).canBeSaved("Main")
		.addTooltip("Automatically switches your team if you get infected during the Infected game mode."));

	addOption(ButtonOption("Juggernaut")
		.addFunction(Juggernaut)
		.addTooltip("Swaps your class out for the Juggernaut class. You'll need to respawn if you're not host when selecting this."));

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
	if (Engine::InGame()) {
		if (vars.bAutoUninfect) {
			if (!strcmp(Engine::GetDvar<const char*>(GetPatch(xbLive.pPatches->MW3.ui_gametype)), "infect")) {
				if (Engine::GetClientInfo(Engine::GetCG()->iClientNumber).iTeam == 1) {
					Engine::Cbuf_AddText(0, pUtils.va("cmd mr %i 3 allies;", *(int*)(GetPatch(xbLive.pPatches->MW3.ServerID))));
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