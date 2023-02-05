#pragma once

class ColorOption : public Option {
private:
	void(*FuncOnAction)();
	void(*FuncCurrentOption)();
	void(*FuncOnUpdate)();

	bool bPreviewBox;
	bool bHasSubmenu;
	Color* pColor;

	bool bCanBeSaved;
	char szSubmenuName[20];
public:
	ColorOption(const char* name) : Option(name), FuncOnAction(nullsub), FuncOnUpdate(nullsub), FuncCurrentOption(nullsub), bPreviewBox(false), bHasSubmenu(false) { bCanBeSaved = false; }

	ColorOption& addPreviewBox() {
		bPreviewBox = true;
		return *this;
	}
	
	ColorOption& addSubmenu() {
		bHasSubmenu = true;
		return *this;
	}

	ColorOption& canBeSaved(const char* submenuName) {
		bCanBeSaved = true;
		strcpy(szSubmenuName, submenuName);
		return *this;
	}

	ColorOption& addColor(Color& color) {
		pColor = &color;
		return *this;
	}

	ColorOption& addFunction(void(*func)()) {
		FuncOnAction = func;
		return *this;
	}

	ColorOption& addOnUpdate(void(*func)()) {
		FuncOnUpdate = func;
		return *this;
	}

	ColorOption& addOnHover(void(*func)()) {
		FuncCurrentOption = func;
		return *this;
	}

	ColorOption& addRequirement(bool(*func)()) {
		FuncRequirement = func;
		return *this;
	}

	ColorOption& addTooltip(string tooltip) {
		Tooltip = tooltip;
		return *this;
	}

	void Render(int pos);
	void RenderSelected(int pos);
	void LoadConfig(string value);
	ConfigSaveData GetSaveData();
};