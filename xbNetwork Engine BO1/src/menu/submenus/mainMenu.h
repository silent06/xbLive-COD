#pragma once
#include "menu/submenu.h"

class MainMenu : public Submenu {
public:
	static MainMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	MainMenu() : Submenu() {}
	~MainMenu();
};

namespace MainMenuVars {
	struct Vars {
		bool bNoRecoil;
		bool bNoSpread;
		bool bNoSway;
		bool bNoFlinch;
		bool bConstantRadar;
		bool bFastReload;
		bool bThirdPerson;
		bool bHearEveryone;
		bool bWasReloading;
		bool bReloadYPressed;
		bool bShowMenuBinds;
		
		float fFOV;
		float fThirdPerson;

		int iReloadCount;
		int iChangeTeam;
		int iChangeClass;
	};

	void NoSpread(UserCommand* pNextUserCommand, UserCommand* pUserCommand);
	void DvarThirdPerson();
	void DvarFOV();
	void DvarSetHearEveryone();

	extern Vars vars;
}