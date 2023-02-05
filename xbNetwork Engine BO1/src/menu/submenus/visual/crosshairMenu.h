#pragma once
#include "menu/submenu.h"

class CrosshairMenu : public Submenu {
public:
	static CrosshairMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	CrosshairMenu() : Submenu() {}
	~CrosshairMenu();
};

namespace CrosshairMenuVars {
	struct Vars {
		bool bDisableEngineCrosshair;
		bool bDrawCustomCrosshair;
		bool bRotateCustomCrosshair;

		int iRotateSpeed;
		int iRotation;
		int iSize;

		Color CrosshairColor;
	};

	extern Vars vars;
}