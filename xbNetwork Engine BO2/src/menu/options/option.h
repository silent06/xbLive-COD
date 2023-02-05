#pragma once

bool DefaultRequirement();
void nullsub();
void nullsub2(const char*);

enum eConfigSaveType {
	TOGGLE_OPTION,
	NUMBER_OPTION,
	NUMBER_OPTION_TOGGLE,
	SCROLL_OPTION,
	SCROLL_OPTION_TOGGLE,
	COLOR_OPTION
};

enum eConfigSaveValueType {
	TYPE_FLOAT,
	TYPE_INT
};

struct ConfigSaveData {
	bool bPopulated;
	eConfigSaveType Type;
	eConfigSaveValueType ValueType;
	bool bValue;

	union {
		float fValue;
		int iValue;
		BYTE szColor[4];
	} Value;

	char szSubmenuName[20];
	char szOptionName[50];
};

class Option {
protected:
	bool(*FuncRequirement)();
	char szName[50];
	string Tooltip;
	bool bVisible;
	byte bHoverTimer;
	bool bIsScrollOption;

public:
	Option() : bVisible(true), bIsScrollOption(false), FuncRequirement(DefaultRequirement), bHoverTimer(0) {}
	Option(const char* name) : bVisible(true), bIsScrollOption(false), FuncRequirement(DefaultRequirement), bHoverTimer(0) { SetName(name); }

	virtual void Render(int pos);
	virtual void RenderSelected(int pos);
	virtual ConfigSaveData GetSaveData();
	virtual void LoadConfig(string value);

	virtual void SetName(const char* name) {
		strcpy(szName, name);
	}

	void SetVisible(bool visible) {
		bVisible = visible;
	}

	bool IsVisible() {
		return bVisible && FuncRequirement();
	}

	bool IsScroll() {
		return bIsScrollOption;
	}

	const char* GetName() {
		return szName;
	}

	string GetTooltip() {
		return Tooltip;
	}
};