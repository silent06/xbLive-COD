#include "stdafx.h"
#include "configMenu.h"
#include "../settingsMenu.h"

using namespace ConfigMenuVars;

namespace ConfigMenuVars {
	Vars vars;

	void OnCreateConfig(const char* name) {
		if (name) {
			bool dupe = false;
			int newDupe = 1;
			if (pUtils.FileExists(pUtils.va("%s%s.cfg", GAME_PATH, name))) {
				// one exists, let's find if there's more that we named (1), (2) etc
				for (int i = 1; i < 10; i++) {
					if (pUtils.FileExists(pUtils.va("%s%s (%i).cfg", GAME_PATH, name, i))) {
						newDupe = i + 1;
					} else {
						if (i != 1) {
							dupe = true;
							break;
						}
					}
				}
			}

			char newPath[MAX_PATH];
			if (dupe) {
				_snprintf(newPath, MAX_PATH, "%s%s (%i).cfg", GAME_PATH, name, newDupe);
			} else _snprintf(newPath, MAX_PATH, "%s%s.cfg", GAME_PATH, name);

			IniParse config;

			for (int i = 0; i < pSubmenuHandler.GetSubmenus().size(); i++) {
				auto options = pSubmenuHandler.GetSubmenus().at(i)->GetOptions();
				for (int j = 0; j < options.size(); j++) {
					auto configData = options[j].get()->GetSaveData();
					if (configData.bPopulated) {
						switch (configData.Type) {
						case TOGGLE_OPTION:
							config.SetBool(configData.szSubmenuName, configData.szOptionName, configData.bValue);
							break;

						case NUMBER_OPTION:
							if (configData.ValueType == TYPE_FLOAT)
								config.SetFloat(configData.szSubmenuName, configData.szOptionName, configData.Value.fValue);
							else config.SetInt(configData.szSubmenuName, configData.szOptionName, configData.Value.iValue);
							break;

						case NUMBER_OPTION_TOGGLE:
							if (configData.ValueType == TYPE_FLOAT)
								config.SetToggleFloat(configData.szSubmenuName, configData.szOptionName, configData.bValue, configData.Value.fValue);
							else config.SetToggleInt(configData.szSubmenuName, configData.szOptionName, configData.bValue, configData.Value.iValue);
							break;

						case SCROLL_OPTION:
							config.SetInt(configData.szSubmenuName, configData.szOptionName, configData.Value.iValue);
							break;

						case SCROLL_OPTION_TOGGLE:
							config.SetToggleInt(configData.szSubmenuName, configData.szOptionName, configData.bValue, configData.Value.iValue);
							break;

						case COLOR_OPTION:
							config.SetColor(configData.szSubmenuName, configData.szOptionName, Color(configData.Value.szColor[0], configData.Value.szColor[1], configData.Value.szColor[2], configData.Value.szColor[3]));
							break;
						}
					}
				}
			}

			config.SaveToFile(newPath);
		}
	}

	void LoadConfig() {
		auto configName = vars.vFiles[pMenu.iCurrentOption - 1];
		if (configName.c_str()) {

			IniParse config(pUtils.va("%s%s.cfg", GAME_PATH, configName.c_str()));
			if (config.IsGood()) {
				auto sections = config.GetSections();
				for (int fff = 0; fff < sections.size(); fff++) {
					for (int i = 0; i < pSubmenuHandler.GetSubmenus().size(); i++) {
						auto options = pSubmenuHandler.GetSubmenus().at(i)->GetOptions();
						for (int j = 0; j < options.size(); j++) {
							if (!strcmp(pSubmenuHandler.GetSubmenus().at(i)->GetName(), sections[fff].c_str())) {
								auto data = config.GetDataFromSection(sections[fff].c_str());
								for (int ff = 0; ff < data.size(); ff++) {
									if (!strcmp(data[ff].first.c_str(), options[j].get()->GetName())) {
										options[j].get()->LoadConfig(data[ff].second);
										break;
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void ConfigMenu::Init() {
	SetParentSubmenu<SettingsMenu>();
	SetName("Configs");

	addOption(ButtonOption("Create Config")
		.addKeyboard(OnCreateConfig)
		.addTooltip("Creates a config with your current settings."));

	//addOption(ButtonOption("Load Config")
		//.LoadConfig
		//.addTooltip("Load your current settings."));
}

/*Update once when submenu is opened*/
void ConfigMenu::UpdateOnce() {
	ClearOptionsOffset(1);

	vars.vFiles.clear();
	vars.vFiles = pUtils.GetFilesInDirectory(GAME_PATH, "*.cfg");

	for (int i = 0; i < vars.vFiles.size(); i++) {
		if (vars.vFiles[i].length() > 4) {
			vars.vFiles[i] = vars.vFiles[i].substr(0, vars.vFiles[i].length() - 4);
		}

		addOption(ButtonOption(string("Load: " + vars.vFiles[i]).c_str())
			.addFunction(LoadConfig));
	}
}

/*Update while submenu is active*/
void ConfigMenu::Update() {}

/*Background update*/
void ConfigMenu::FeatureUpdate() {}

/*Singleton*/
ConfigMenu* _instance;
ConfigMenu* ConfigMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new ConfigMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
ConfigMenu::~ConfigMenu() { delete _instance; }