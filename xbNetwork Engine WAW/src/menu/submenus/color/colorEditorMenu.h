#pragma once
#include "menu/submenu.h"
#include "utils/structs.h"

class ColorEditorMenu : public Submenu {
public:
	static ColorEditorMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	ColorEditorMenu() : Submenu() {}
	~ColorEditorMenu();
};

namespace ColorEditorMenuVars {
	struct Vars {
		Color* pToUpdate;
		Color ColorValue;
	};

	extern Vars vars;
}