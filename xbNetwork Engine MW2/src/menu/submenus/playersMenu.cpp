#include "stdafx.h"
#include "playersMenu.h"
#include "players/editPlayerMenu.h"

using namespace PlayersMenuVars;

namespace PlayersMenuVars {
	Vars vars;

	ScrollStruct<int> SortTypes[] = {
		"ID", 0,
		"Distance", 1,
		"Alphabetical", 2
	};

	bool CompareDistance(Player& first, Player& second) {
		return first.fDistance < second.fDistance;
	}

	bool CompareNoCase(Player& first, Player& second) {
		int i = 0;
		string name1 = first.pName;
		string name2 = second.pName;

		while ((i < name1.length()) && (i < name2.length())) {
			if (tolower(name1[i]) < tolower(name2[i])) return true;
			if (tolower(name1[i]) > tolower(name2[i])) return false;
			i++;
		}

		return name1.length() < name2.length();
	}

	void OnPress() {
		EditPlayerMenuVars::vars.iEditingClient = vars.players[pMenu.iCurrentOption - 1].iID;
	}

	const char* GenerateName(Player player) {
		static char name[100];
		strcpy(name, "");

		if (vars.iSortType == 0) strcat(name, pUtils.va("^6[%i]^7", player.iID));
		if (vars.iSortType == 1) strcat(name, pUtils.va("^5[%.0fm]^7", player.fDistance));
		if (!strcmp(player.pName, Engine::GetServerInfo()->szHostName)) strcat(name, "^3[H]^7");
		if (player.iID == Engine::GetCG()->iClientNumber) strcat(name, "^1[ME]^7");
		if (pGame.Clients[player.iID].bPrioritized) strcat(name, "^2[P]^7");

		if (strlen(name) > 1)
			strcat(name, " ");
		strcat(name, player.pName);
		return name;
	}
}

void PlayersMenu::Init() {
	addOption(ScrollOption<int>(SCROLL, "Sort Player List")
		.addScroll(vars.iSortType, 0, NUMOF(SortTypes) - 1, SortTypes)
		.addTooltip("Sort the player list."));
}

/*Update once when submenu is opened*/
void PlayersMenu::UpdateOnce() {}

/*Update while submenu is active*/
void PlayersMenu::Update() {
	if (Engine::InGame()) {
		static int timer = 0;

		if (GetTickCount() - timer > 250) {
			timer = GetTickCount();

			ClearOptionsOffset(1);
			vars.players.clear();

			for (int i = 0; i < Engine::GetServerInfo()->iMaxClients; i++) {
				if (Engine::GetCG()->ClientInfo[i].bValidCheck && Engine::GetCG()->ClientInfo[i].szName) {
					vars.players.push_back(Player(i, Engine::GetCG()->ClientInfo[i].szName, Engine::GetDistance(Engine::GetEntity(i).vOrigin, Engine::GetEntity(Engine::GetCG()->iClientNumber).vOrigin) * 0.03048f));
				}
			}

			switch (vars.iSortType) {
			case 1: sort(vars.players.begin(), vars.players.end(), CompareDistance); break;
			case 2: sort(vars.players.begin(), vars.players.end(), CompareNoCase); break;
			}

			for (int i = 0; i < vars.players.size(); i++) {
				addOption(SubmenuOption(GenerateName(vars.players[i]))
					.addFunction(OnPress)
					.addTooltip("^3[H]^7 = Host\n^2[P]^7 = Prioritized\n^1[ME]^7 = You, silly :P")
					.addSubmenu<EditPlayerMenu>());
			}
		}
	} else {
		ClearOptionsOffset(1);
		addOption(ButtonOption("You need to be in game :P"));
	}
}

/*Background update*/
void PlayersMenu::FeatureUpdate() {}

/*Singleton*/
PlayersMenu* _instance;
PlayersMenu* PlayersMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new PlayersMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
PlayersMenu::~PlayersMenu() { delete _instance; }