#pragma once
#include "menu/submenu.h"

class CompassMenu : public Submenu {
public:
	static CompassMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	CompassMenu() : Submenu() {}
	~CompassMenu();
};

namespace CompassMenuVars {
	struct Vars {
		bool bDisableEngineCompass;
		bool bDrawCustomCompass;
		bool bCustomCompassDrawOutline;
		CompassType CurrentlyRenderedType;
		float fCustomCompassScale;
		Vector2<float> vPosition;
	};

	void DisableEngineCompass();
	extern Vars vars;
}