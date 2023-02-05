#pragma once
#include "menu/submenu.h"

class PlayersMenu : public Submenu {
public:
	static PlayersMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	PlayersMenu() : Submenu() {}
	~PlayersMenu();
};

namespace PlayersMenuVars {
	struct Player {
		int iID;
		const char* pName;
		float fDistance;

		Player() {}

		Player(int a, const char* b, float c) {
			iID = a;
			pName = b;
			fDistance = c;
		}
	};

	struct Vars {
		vector<Player> players;

		int iSortType;
	};

	extern Vars vars;
}