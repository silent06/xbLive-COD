#include "stdafx.h"

void SubmenuOption::Render(int pos) {
	FuncOnUpdate();

	pRenderer.DrawString("->", 845, 196 + (pos * pRenderer.fOptionHeight), pRenderer.Fonts.normalFont, 0.50f, Color(0xFFFFFFFF), false, false, JustifyRight);
	pRenderer.DrawString(szName, 435, 196 + (pos * pRenderer.fOptionHeight), pRenderer.Fonts.normalFont, 0.50f, Color(0xFFFFFFFF), false, false, JustifyLeft);
}

void SubmenuOption::RenderSelected(int position) {
	FuncCurrentOption();
	if (FuncRequirement() && IsOptionPressed()) {
		FuncOnAction();
		pSubmenuHandler.SetSubmenu(pSubmenu);
	}
}