#include "stdafx.h"
#include "settingsMenu.h"
#include "settings/configMenu.h"
#include "color/colorEditorMenu.h"
#include "visualMenu.h"
#include "visual/espMenu.h"
#include "visual/indicatorMenu.h"
#include "visual/crosshairMenu.h"

using namespace SettingsMenuVars;

namespace SettingsMenuVars {
	Vars vars;
}

void SettingsMenu::Init() {
	SetName("Settings");

	addOption(SubmenuOption("Configs")
		.addSubmenu<ConfigMenu>()
		.addTooltip("Enters the config submenu."));

	addOption(ColorOption("Visuals - Draw Equipment")
		.addPreviewBox()
		.addSubmenu()
		.addColor(VisualMenuVars::vars.DrawEquipmentColor).canBeSaved("Settings")
		.addTooltip("Edit this color."));

	addOption(ColorOption("Visuals - Draw Dropped Items")
		.addPreviewBox()
		.addSubmenu()
		.addColor(VisualMenuVars::vars.DrawDroppedItemsColor).canBeSaved("Settings")
		.addTooltip("Edit this color."));

	addOption(ColorOption("ESP - Draw Box - Friendlies")
		.addPreviewBox()
		.addSubmenu()
		.addColor(ESPMenuVars::vars.DrawBoxFriendliesColor).canBeSaved("Settings")
		.addTooltip("Edit this color."));

	addOption(ColorOption("ESP - Draw Box - Enemies")
		.addPreviewBox()
		.addSubmenu()
		.addColor(ESPMenuVars::vars.DrawBoxEnemiesColor).canBeSaved("Settings")
		.addTooltip("Edit this color."));

	addOption(ColorOption("ESP - Draw Box - Aimbot Target")
		.addPreviewBox()
		.addSubmenu()
		.addColor(ESPMenuVars::vars.DrawBoxAimbotTargetColor).canBeSaved("Settings")
		.addTooltip("Edit this color."));

	addOption(ColorOption("ESP - Draw Names - Friendlies")
		.addPreviewBox()
		.addSubmenu()
		.addColor(ESPMenuVars::vars.DrawNameFriendliesColor).canBeSaved("Settings")
		.addTooltip("Edit this color."));

	addOption(ColorOption("ESP - Draw Names - Enemies")
		.addPreviewBox()
		.addSubmenu()
		.addColor(ESPMenuVars::vars.DrawNameEnemiesColor).canBeSaved("Settings")
		.addTooltip("Edit this color."));

	addOption(ColorOption("ESP - Draw Names - Aimbot Target")
		.addPreviewBox()
		.addSubmenu()
		.addColor(ESPMenuVars::vars.DrawNameAimbotTargetColor).canBeSaved("Settings")
		.addTooltip("Edit this color."));

	addOption(ColorOption("ESP - Draw Distance - Friendlies")
		.addPreviewBox()
		.addSubmenu()
		.addColor(ESPMenuVars::vars.DrawDistanceFriendliesColor).canBeSaved("Settings")
		.addTooltip("Edit this color."));

	addOption(ColorOption("ESP - Draw Distance - Enemies")
		.addPreviewBox()
		.addSubmenu()
		.addColor(ESPMenuVars::vars.DrawDistanceEnemiesColor).canBeSaved("Settings")
		.addTooltip("Edit this color."));

	addOption(ColorOption("ESP - Draw Distance - Aimbot Target")
		.addPreviewBox()
		.addSubmenu()
		.addColor(ESPMenuVars::vars.DrawDistanceAimbotTargetColor).canBeSaved("Settings")
		.addTooltip("Edit this color."));

	addOption(ColorOption("ESP - Draw Bones - Friendlies")
		.addPreviewBox()
		.addSubmenu()
		.addColor(ESPMenuVars::vars.DrawBonesFriendliesColor).canBeSaved("Settings")
		.addTooltip("Edit this color."));

	addOption(ColorOption("ESP - Draw Bones - Enemies")
		.addPreviewBox()
		.addSubmenu()
		.addColor(ESPMenuVars::vars.DrawBonesEnemiesColor).canBeSaved("Settings")
		.addTooltip("Edit this color."));

	addOption(ColorOption("ESP - Draw Bones - Aimbot Target")
		.addPreviewBox()
		.addSubmenu()
		.addColor(ESPMenuVars::vars.DrawBonesAimbotTargetColor).canBeSaved("Settings")
		.addTooltip("Edit this color."));

	addOption(ColorOption("ESP - Draw Snaplines - Friendlies")
		.addPreviewBox()
		.addSubmenu()
		.addColor(ESPMenuVars::vars.DrawSnaplinesFriendliesColor).canBeSaved("Settings")
		.addTooltip("Edit this color."));

	addOption(ColorOption("ESP - Draw Snaplines - Enemies")
		.addPreviewBox()
		.addSubmenu()
		.addColor(ESPMenuVars::vars.DrawSnaplinesEnemiesColor).canBeSaved("Settings")
		.addTooltip("Edit this color."));

	addOption(ColorOption("ESP - Draw Snaplines - Aimbot Target")
		.addPreviewBox()
		.addSubmenu()
		.addColor(ESPMenuVars::vars.DrawSnaplinesAimbotTargetColor).canBeSaved("Settings")
		.addTooltip("Edit this color."));

	addOption(ColorOption("ESP - Draw Dogs - Friendlies")
		.addPreviewBox()
		.addSubmenu()
		.addColor(ESPMenuVars::vars.DrawDogsFriendliesColor).canBeSaved("Settings")
		.addTooltip("Edit this color."));

	addOption(ColorOption("ESP - Draw Dogs - Enemies")
		.addPreviewBox()
		.addSubmenu()
		.addColor(ESPMenuVars::vars.DrawDogsEnemiesColor).canBeSaved("Settings")
		.addTooltip("Edit this color."));

	addOption(ColorOption("ESP - Draw RCXD - Friendlies")
		.addPreviewBox()
		.addSubmenu()
		.addColor(ESPMenuVars::vars.DrawRCXDFriendliesColor).canBeSaved("Settings")
		.addTooltip("Edit this color."));

	addOption(ColorOption("ESP - Draw RCXD - Enemies")
		.addPreviewBox()
		.addSubmenu()
		.addColor(ESPMenuVars::vars.DrawRCXDEnemiesColor).canBeSaved("Settings")
		.addTooltip("Edit this color."));

	addOption(ColorOption("Indicators - Draw Players - Friendlies")
		.addPreviewBox()
		.addSubmenu()
		.addColor(IndicatorMenuVars::vars.DrawPlayersFriendliesColor).canBeSaved("Settings")
		.addTooltip("Edit this color."));

	addOption(ColorOption("Indicators - Draw Players - Enemies")
		.addPreviewBox()
		.addSubmenu()
		.addColor(IndicatorMenuVars::vars.DrawPlayersEnemiesColor).canBeSaved("Settings")
		.addTooltip("Edit this color."));

	addOption(ColorOption("Indicators - Draw Players - Aimbot Target")
		.addPreviewBox()
		.addSubmenu()
		.addColor(IndicatorMenuVars::vars.DrawPlayersAimbotTargetColor).canBeSaved("Settings")
		.addTooltip("Edit this color."));

	addOption(ColorOption("Indicators - Draw Equipment")
		.addPreviewBox()
		.addSubmenu()
		.addColor(IndicatorMenuVars::vars.DrawEquipmentColor).canBeSaved("Settings")
		.addTooltip("Edit this color."));

	addOption(ColorOption("Indicators - Draw Dropped Items")
		.addPreviewBox()
		.addSubmenu()
		.addColor(IndicatorMenuVars::vars.DrawDroppedItemsColor).canBeSaved("Settings")
		.addTooltip("Edit this color."));

	addOption(ColorOption("Crosshair - Color")
		.addPreviewBox()
		.addSubmenu()
		.addColor(CrosshairMenuVars::vars.CrosshairColor).canBeSaved("Settings")
		.addTooltip("Edit this color."));
}

/*Update once when submenu is opened*/
void SettingsMenu::UpdateOnce() {}

/*Update while submenu is active*/
void SettingsMenu::Update() {}

/*Background update*/
void SettingsMenu::FeatureUpdate() {};

/*Singleton*/
SettingsMenu* _instance;
SettingsMenu* SettingsMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new SettingsMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
SettingsMenu::~SettingsMenu() { delete _instance; }