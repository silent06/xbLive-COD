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
		bool bFastReload;
		bool bNoScreenEffects;
		bool bConstantRadar;
		bool bLaser;
		bool bAutoUninfect;
		bool bHearEveryone;
		bool bThirdPerson;
		bool bWasReloading;
		bool bReloadYPressed;
		bool bShowMenuBinds;

		float fThirdPerson;
		float fFOV;

		int iChangeClass;
		int iChangeTeam;
		int iReloadCount;
	};

	void DvarSetHearEveryone();
	void DvarThirdPerson();
	void DvarFOV();
	void NoSpread(UserCommand* oldCommand);
	extern Vars vars;
}