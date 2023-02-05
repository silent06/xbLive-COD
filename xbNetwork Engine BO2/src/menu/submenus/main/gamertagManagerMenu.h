#pragma once
#include "menu/submenu.h"

class GamertagManagerMenu : public Submenu {
public:
	static GamertagManagerMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	GamertagManagerMenu() : Submenu() {}
	~GamertagManagerMenu();
};

namespace GamertagManagerMenuVars
{
	struct Vars {
		bool bRainbowGamertag;

		char szDefault[0x32];

		int iPresetName;
		int iRainbowDelay;
		int iColor;

		vector<string> vSavedGamertags;
	};

	void SetGamertag(const char* pName);
	extern Vars vars;
}