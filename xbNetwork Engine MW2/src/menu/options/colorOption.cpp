#include "stdafx.h"
#include "menu/submenus/color/colorEditorMenu.h"

void ColorOption::Render(int pos) {
	FuncOnUpdate();

	if (bPreviewBox && pColor) {
		pRenderer.DrawOutlinedRect(830, 180.5f + (pos * pRenderer.fOptionHeight), 13, 13, 1, *pColor, *pColor, true);
	}

	pRenderer.DrawString(szName, 435, 195 + (pos * pRenderer.fOptionHeight), pRenderer.Fonts.normalFont, 0.50f, Color(0xFFFFFFFF), false, false, JustifyLeft);
}

void ColorOption::RenderSelected(int position) {
	FuncCurrentOption();
	if (IsOptionPressed()) {
		FuncOnAction();

		if (bHasSubmenu) {
			ColorEditorMenuVars::vars.pToUpdate = pColor;
			ColorEditorMenu::GetInstance()->SetName(szName);
			ColorEditorMenu::GetInstance()->SetParentSubmenu(pSubmenuHandler.GetCurrentSubmenu());
			pSubmenuHandler.SetSubmenu(ColorEditorMenu::GetInstance());
		}
	}
}

void ColorOption::LoadConfig(string value) {
	vector<string> splitVals;
	pUtils.Split(value, ',', splitVals);

	if (splitVals.size() == 4) {
		*pColor = Color(
			atoi(splitVals[0].c_str()),
			atoi(splitVals[1].c_str()),
			atoi(splitVals[2].c_str()),
			atoi(splitVals[3].c_str()));

		FuncOnAction();
	}
}

ConfigSaveData ColorOption::GetSaveData() {
	ConfigSaveData tmp;
	tmp.bPopulated = bCanBeSaved;

	if (tmp.bPopulated) {
		tmp.Type = COLOR_OPTION;
		tmp.Value.szColor[0] = pColor->Color_.R;
		tmp.Value.szColor[1] = pColor->Color_.G;
		tmp.Value.szColor[2] = pColor->Color_.B;
		tmp.Value.szColor[3] = pColor->Color_.A;

		strcpy(tmp.szOptionName, szName);
		strcpy(tmp.szSubmenuName, szSubmenuName);
	}

	return tmp;
}