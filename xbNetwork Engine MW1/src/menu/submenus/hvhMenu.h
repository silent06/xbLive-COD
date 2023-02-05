#pragma once
#include "menu/submenu.h"

class HvHMenu : public Submenu {
public:
	static HvHMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	HvHMenu() : Submenu() {}
	~HvHMenu();
};

namespace HvHMenuVars {
	struct Vars {
		int iXDirection;
		bool bXDirection;

		int iYDirection;
		bool bYDirection;

		int iYSpeed;

		int iFakeLag;
		bool bFakeLag;

		int iCrouchEvent;
		bool bCrouchEvent;
	};

	extern Vars vars;
}