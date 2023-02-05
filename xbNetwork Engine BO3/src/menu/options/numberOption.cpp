#include "stdafx.h"

static bool bLeftDisabled = false;
static bool bRightDisabled = false;
static int iLeftTimer = 0;
static int iRightTimer = 0;

template class NumberOption<int>;
template class NumberOption<float>;
template class NumberOption<BYTE>;

template <class Type>
ConfigSaveData NumberOption<Type>::GetSaveData() {
	ConfigSaveData tmp;
	tmp.bPopulated = bCanBeSaved;

	if (tmp.bPopulated) {
		tmp.Type = ScrollType == TOGGLE ? NUMBER_OPTION_TOGGLE : NUMBER_OPTION;
		tmp.ValueType = strstr(pFormat, "f") ? TYPE_FLOAT : TYPE_INT;

		if (tmp.ValueType == TYPE_FLOAT)
			tmp.Value.fValue = (float)*pNumber;
		else tmp.Value.iValue = (int)*pNumber;

		if (ScrollType == TOGGLE) tmp.bValue = *pBool;

		strcpy(tmp.szOptionName, szName);
		strcpy(tmp.szSubmenuName, szSubmenuName);
	}

	return tmp;
}

template <class Type>
void NumberOption<Type>::LoadConfig(string value) {
	if (pBool) {
		vector<string> splitVals;
		pUtils.Split(value, ',', splitVals);

		// FORMAT: true,12 - bool, int
		if (splitVals.size() == 2) {
			if (strstr(splitVals[0].c_str(), "yes") || strstr(splitVals[0].c_str(), "YES")
				|| strstr(splitVals[0].c_str(), "true") || strstr(splitVals[0].c_str(), "TRUE")
				|| strstr(splitVals[0].c_str(), "1")) {
				*pBool = true;
			}

			if (strstr(pFormat, "f")) {
				*pNumber = (Type)atof(splitVals[1].c_str());
			} else *pNumber = (Type)stoi(splitVals[1].c_str());
			FuncOnAction();
			return;
		}
	}

	if (strstr(pFormat, "f")) {
		*pNumber = (Type)atof(value.c_str());
	} else *pNumber = (Type)stoi(value.c_str());
	FuncOnAction();
}

template <class Type>
void NumberOption<Type>::Render(int pos) {
	FuncOnUpdate();

	switch (ScrollType) {
	case TOGGLE: {
		pRenderer.DrawOutlinedRect(830, 180.5f + (pos * pRenderer.fOptionHeight), 13, 13, 1, *pBool ? Color(160, 57, 64) : Color(0x383838FF), Color(0, 0, 0, 255), true);

		pRenderer.DrawOutlinedRect(830 - 83, 180.5f + (pos * pRenderer.fOptionHeight), 80, 13, 1, Color(0x383838FF), Color(0, 0, 0, 255), true);
		pRenderer.DrawRect(830 - 83, 180.5f + (pos * pRenderer.fOptionHeight), (float)((*pNumber * 80) / Max), 13, JustifyLeft, Color(160, 57, 64));

		auto text = pUtils.va(pFormat, *pNumber);
		pRenderer.DrawString(text, 800 - 13, 194 + (pos * pRenderer.fOptionHeight), pRenderer.Fonts.normalFont, 0.56f, Color(0xFFFFFFFF), false, false, JustifyCenter);
		break;
	}

	case SCROLL:
	case SCROLLSELECT:
		pRenderer.DrawOutlinedRect(833 - 86, 180.5f + (pos * pRenderer.fOptionHeight), 96, 13, 1, Color(0x383838FF), Color(0, 0, 0, 255), true);
		pRenderer.DrawRect(833 - 86, 180.5f + (pos * pRenderer.fOptionHeight), (float)((*pNumber * 96) / Max), 13, JustifyLeft, Color(160, 57, 64));

		auto text = pUtils.va(pFormat, *pNumber);
		pRenderer.DrawString(text, 800 - 8, 194 + (pos * pRenderer.fOptionHeight), pRenderer.Fonts.normalFont, 0.56f, Color(0xFFFFFFFF), false, false, JustifyCenter);
		break;
	}

	pRenderer.DrawString(szName, 435, 195 + (pos * pRenderer.fOptionHeight), pRenderer.Fonts.normalFont, 0.60f, Color(0xFFFFFFFF), false, false, JustifyLeft);
}

template <class Type>
void NumberOption<Type>::RenderSelected(int pos) {
	FuncCurrentOption();

	if (IsOptionPressed() && FuncRequirement()) {
		switch (ScrollType) {
		case TOGGLE: *pBool ^= true; FuncOnAction(); break;
		case SELECT: *pSelectedNumber = *pNumber; break;
		case SCROLL:
		case SCROLLSELECT: FuncOnAction();  break;
		}
	}

	if (IsJustPressed(DPAD_LEFT)) {
		if (!bLeftDisabled) {
			*pNumber -= Step;
			if (bLoop) {
				if (*pNumber < Min) *pNumber = Max;
			} else if (*pNumber < Min && bHasMin) *pNumber = Min;
			if (ScrollType == SCROLL) FuncOnAction();
			if (ScrollType == TOGGLE && *pBool) FuncOnAction();
		}
		bLeftDisabled = false;
		iLeftTimer = 0;
	}

	if (IsJustPressed(DPAD_RIGHT)) {
		if (!bRightDisabled) {
			*pNumber += Step;
			if (bLoop) {
				if (*pNumber > Max) *pNumber = Min;
			} else if (*pNumber > Max && bHasMax) *pNumber = Max;
			if (ScrollType == SCROLL) FuncOnAction();
			if (ScrollType == TOGGLE && *pBool) FuncOnAction();
		}
		bRightDisabled = false;
		iRightTimer = 0;
	}

	static int TIMER;

	if (IsDown(DPAD_LEFT)) {
		if (++iLeftTimer > 10) {
			bLeftDisabled = true;
			if ((Engine::TimeGetTime() - TIMER) > dwScrollSpeed) {
				*pNumber -= Step;
				if (bLoop) {
					if (*pNumber < Min) *pNumber = Max;
				} else if (*pNumber < Min && bHasMin) *pNumber = Min;
				if (ScrollType == SCROLL) FuncOnAction();
				if (ScrollType == TOGGLE && *pBool) FuncOnAction();
				TIMER = Engine::TimeGetTime();
			}
		}
	}

	if (IsDown(DPAD_RIGHT)) {
		if (++iRightTimer > 10) {
			bRightDisabled = true;
			if ((Engine::TimeGetTime() - TIMER) > dwScrollSpeed) {
				*pNumber += Step;
				if (bLoop) {
					if (*pNumber > Max) *pNumber = Min;
				} else if (*pNumber > Max && bHasMax) *pNumber = Max;
				if (ScrollType == SCROLL) FuncOnAction();
				if (ScrollType == TOGGLE && *pBool) FuncOnAction();
				TIMER = Engine::TimeGetTime();
			}
		}
	}
}