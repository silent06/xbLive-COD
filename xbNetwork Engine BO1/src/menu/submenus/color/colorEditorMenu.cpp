#include "stdafx.h"
#include "colorEditorMenu.h"
#include "../mainMenu.h"

using namespace ColorEditorMenuVars;

namespace ColorEditorMenuVars {
	Vars vars;

	void UpdateIt() {
		if (vars.pToUpdate) {
			*vars.pToUpdate = vars.ColorValue;
		}
	}
}

void ColorEditorMenu::Init() {
	SetName("Color Editor");

	addOption(NumberOption<BYTE>(SCROLL, "[R] Red")
		.addNumber(vars.ColorValue.Color_.R, "%i", 1).addMin(0).addMax(255).setScrollSpeed(20)
		.addFunction(UpdateIt)
		.addTooltip("Sets the red value of the color."));

	addOption(NumberOption<BYTE>(SCROLL, "[G] Green")
		.addNumber(vars.ColorValue.Color_.G, "%i", 1).addMin(0).addMax(255).setScrollSpeed(20)
		.addFunction(UpdateIt)
		.addTooltip("Sets the green value of the color."));

	addOption(NumberOption<BYTE>(SCROLL, "[B] Blue")
		.addNumber(vars.ColorValue.Color_.B, "%i", 1).addMin(0).addMax(255).setScrollSpeed(20)
		.addFunction(UpdateIt)
		.addTooltip("Sets the blue value of the color."));

	addOption(NumberOption<BYTE>(SCROLL, "[A] Alpha")
		.addNumber(vars.ColorValue.Color_.A, "%i", 1).addMin(0).addMax(255).setScrollSpeed(20)
		.addFunction(UpdateIt)
		.addTooltip("Sets the alpha value of the color."));

	addOption(ColorOption("Preview")
		.addPreviewBox()
		.addColor(vars.ColorValue)
		.addTooltip("Shows you what the color looks like."));
}

/*Update once when submenu is opened*/
void ColorEditorMenu::UpdateOnce() {
	if (vars.pToUpdate) {
		vars.ColorValue = *vars.pToUpdate;
	}
}

/*Update while submenu is active*/
void ColorEditorMenu::Update() {}

/*Background update*/
void ColorEditorMenu::FeatureUpdate() {}

/*Singleton*/
ColorEditorMenu* _instance;
ColorEditorMenu* ColorEditorMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new ColorEditorMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
ColorEditorMenu::~ColorEditorMenu() { delete _instance; }