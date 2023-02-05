#pragma once
#include "menu/submenu.h"

class GameInfoMenu : public Submenu {
public:
	static GameInfoMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	GameInfoMenu() : Submenu() {}
	~GameInfoMenu();
};

namespace GameInfoMenuVars {
	struct Vars {
		bool bEngineName;
		bool bTargetDetails;
		bool bScreenResolution;
		bool bFPS;
		bool bPing;
		bool bMap;
		bool bGameMode;
		bool bHost;
	};

	extern Vars vars;
}