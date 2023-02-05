#include "stdafx.h"

ConfigSaveData ToggleOption::GetSaveData() {
	ConfigSaveData tmp;
	tmp.bPopulated = bCanBeSaved;

	if (tmp.bPopulated) {
		tmp.Type = TOGGLE_OPTION;
		tmp.bValue = *pBool;
		strcpy(tmp.szOptionName, szName);
		strcpy(tmp.szSubmenuName, szSubmenuName);
	}

	return tmp;
}

void ToggleOption::LoadConfig(string value) {
	if (strstr(value.c_str(), StrEnc("yes")) || strstr(value.c_str(), StrEnc("YES"))
		|| strstr(value.c_str(), StrEnc("true")) || strstr(value.c_str(), StrEnc("TRUE"))
		|| strstr(value.c_str(), StrEnc("1"))) {
		*pBool = true;
		FuncOnAction();
	}
}

void ToggleOption::Render(int pos) {
	if (bHasOnUpdate)
		FuncOnUpdate(this);

	pRenderer.DrawOutlinedRect(830, 180.5f + (pos * pRenderer.fOptionHeight), 13, 13, 1, *pBool ? Color(160, 57, 64) : Color(0x383838FF), Color(0, 0, 0, 255), true);
	pRenderer.DrawString(szName, 435, 196 + (pos * pRenderer.fOptionHeight), pRenderer.Fonts.bodyFont, 0.76f, Color(0xFFFFFFFF), false, false, JustifyLeft);
}

void ToggleOption::RenderSelected(int pos) {
	FuncCurrentOption();
	if (IsOptionPressed() && FuncRequirement()) {
		*pBool ^= true;
		FuncOnAction();
	}
}