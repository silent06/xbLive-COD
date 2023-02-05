#pragma once

class ToggleOption : public Option {
private:
	void(*FuncOnAction)();
	void(*FuncCurrentOption)();
	void(*FuncOnUpdate)(ToggleOption*);

	bool bHasOnUpdate;
	bool* pBool;
	bool pDefBool;
	bool bCanBeSaved;
	char szSubmenuName[20];
public:
	ToggleOption(const char* name) : Option(name), FuncOnAction(nullsub), bHasOnUpdate(false), FuncCurrentOption(nullsub), pBool(nullptr) { bCanBeSaved = false; }

	ToggleOption &addToggle(bool& toggle) {
		pBool = &toggle;
		pDefBool = toggle;
		return *this;
	}

	ToggleOption& canBeSaved(const char* submenuName) {
		bCanBeSaved = true;
		strcpy(szSubmenuName, submenuName);
		return *this;
	}

	ToggleOption& addFunction(void(*func)()) {
		FuncOnAction = func;
		return *this;
	}

	ToggleOption& addOnUpdate(void(*func)(ToggleOption*)) {
		bHasOnUpdate = true;
		FuncOnUpdate = func;
		return *this;
	}

	ToggleOption& addOnHover(void(*func)()) {
		FuncCurrentOption = func;
		return *this;
	}

	ToggleOption& addRequirement(bool(*func)()) {
		FuncRequirement = func;
		return *this;
	}

	ToggleOption& addTooltip(string tooltip) {
		Tooltip = tooltip;
		return *this;
	}

	const char* GetSubmenuName() { return szSubmenuName; }

	void Render(int pos);
	void RenderSelected(int pos);
	void LoadConfig(string value);
	ConfigSaveData GetSaveData();
};