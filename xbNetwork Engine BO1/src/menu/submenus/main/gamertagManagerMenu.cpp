#include "stdafx.h"
#include "gamertagManagerMenu.h"
#include "gamertagsMenu.h"
#include "../mainMenu.h"

using namespace GamertagManagerMenuVars;

namespace GamertagManagerMenuVars {
	Vars vars;

	ScrollStruct<int> ScrollPresetNames[] = {
		"I'm on XeCheats", 0,
		"xbLive.online", 1,
		"xbLive Engine", 2,
		"Kennedy shot first", 3,
		"Bush did 9/11", 4,
		"Fuck infections", 5,
		"Swoogity Boogity", 6,
		"I have sw4g", 7,
		"Aitch-V-Aitch?", 8,
		"Big brain time", 9,
		"Epstein touched me", 10,
		"Epstein didn't kill himself", 11
	};

	ScrollStruct<const char*> ScrollNameColors[] = {
		"^7White", "^7",
		"^1Red^7", "^1",
		"^2Green^7", "^2",
		"^3Yellow^7", "^3",
		"^4Blue^7", "^4",
		"^5Cyan^7", "^5",
		"^6Pink^7", "^6",
		"^0Black^7", "^0"
	};

	void SetGamertag(const char* pName) {
		char xuid[20];
		_ui64toa(Engine::GetXUIDFromNetInfo(Engine::GetCG()->iClientNumber, TRUE), xuid, 0x10);

		char szPayload[0x100];
		sprintf(szPayload, "userinfo \"\\rate\\20000\\snaps\\20\\name\\%s\\xuid\\%s\\natType\\1\rank\\1\\prestige\\0\"", pName, xuid);
		Engine::CL_AddReliableCommand(0, szPayload);
		strcpy((char*)GetPatch(xbLive.pPatches->BO1.LocalNamePointer), pName);
	}

	void SetGamertagColor(const char* pName, const char* Color) {
		char xuid[20];
		_ui64toa(Engine::GetXUIDFromNetInfo(Engine::GetCG()->iClientNumber, TRUE), xuid, 0x10);

		char szPayload[0x100];
		sprintf(szPayload, "userinfo \"\\rate\\20000\\snaps\\20\\name\\%s\\clanAbbrev\\%s\\xuid\\%s\\natType\\1\rank\\1\\prestige\\0\"", Engine::GetNameFromNetInfo(Engine::GetCG()->iClientNumber), Color, xuid);
		Engine::CL_AddReliableCommand(0, szPayload);
		strcpy((char*)GetPatch(xbLive.pPatches->BO1.LocalNamePointer), pName);
	}

	void SetPreset() {
		SetGamertag(ScrollPresetNames[ScrollPresetNames[vars.iPresetName].Result].pName);
	}

	void SetDefault() {
		SetGamertag(vars.szDefault);
	}

	void SetColor() {
		SetGamertagColor(Engine::GetNameFromNetInfo(Engine::GetCG()->iClientNumber), ScrollNameColors[vars.iColor].Result);
	}
}

void GamertagManagerMenu::Init() {
	SetParentSubmenu<MainMenu>();
	SetName("Gamertag Manager");

	addOption(SubmenuOption("Gamertags")
		.addSubmenu<GamertagsMenu>()
		.addTooltip("Set or cycle any gamertags you have inside of the Gamertags file inside our cache folder."));

	addOption(ButtonOption("Default Gamertag")
		.addFunction(SetDefault)
		.addTooltip("Sets your current gamertag back to your original."));

	addOption(ScrollOption<int>(SCROLLSELECT, "Preset Gamertags")
		.addScroll(vars.iPresetName, 0, NUMOF(ScrollPresetNames) - 1, ScrollPresetNames)
		.addFunction(SetPreset)
		.addTooltip("Choose a gamertag from our preset list."));

	addOption(ToggleOption("Rainbow Gamertag")
		.addToggle(vars.bRainbowGamertag).canBeSaved("Gamertag Manager")
		.addTooltip("Loops through a list of colors and sets your name to one of the colors."));

	addOption(NumberOption<int>(SCROLL, "Rainbow Gamertag Delay")
		.addNumber(vars.iRainbowDelay, "%ims", 100).addMin(0).addMax(5000)
		.addTooltip("Sets the delay between each rainbow gamertag update."));

	addOption(ScrollOption<const char*>(SCROLLSELECT, "Color")
		.addScroll(vars.iColor, 0, NUMOF(ScrollNameColors) - 1, ScrollNameColors)
		.addFunction(SetColor)
		.addTooltip("Sets the color of your name."));

	vars.iRainbowDelay = 500;
}

/*Update once when submenu is opened*/
void GamertagManagerMenu::UpdateOnce() {
	static once_flag init;
	call_once(&init, [] {
		strcpy(vars.szDefault, Engine::GetNameFromNetInfo(Engine::GetCG()->iClientNumber));
	});

	vars.vSavedGamertags.clear();

	FILE* gamertagFile = fopen(CACHE_PATH "Gamertags.txt", "r");
	if (gamertagFile) {
		DWORD dwCount = 0;

		char line[0x20];
		while (fgets(line, 0x20, gamertagFile)) {
			dwCount++;
			if (dwCount > 100) break;

			vars.vSavedGamertags.push_back(string(line));
		}

		fclose(gamertagFile);
	}
}

/*Update while submenu is active*/
void GamertagManagerMenu::Update() {}

/*Background update*/
void GamertagManagerMenu::FeatureUpdate() {
	if (vars.bRainbowGamertag) {
		static int timer = 0;
		static int current = 0;
		if (GetTickCount() - timer > vars.iRainbowDelay) {
			timer = GetTickCount();

			if (current >= NUMOF(ScrollNameColors)) current = 0;

			SetGamertagColor(Engine::GetNameFromNetInfo(Engine::GetCG()->iClientNumber), ScrollNameColors[current].Result);

			current++;
		}
	}
}

/*Singleton*/
GamertagManagerMenu* _instance;
GamertagManagerMenu* GamertagManagerMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new GamertagManagerMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
GamertagManagerMenu::~GamertagManagerMenu() { delete _instance; }