#pragma once

template<typename Type>
class ScrollOption;

template<typename Type>
void v_idk(ScrollOption<Type>*) {}

template<typename Type>
class ScrollOption : public Option {
private:
	void(*FuncOnAction)();
	void(*FuncCurrentOption)();
	void(*FuncOnUpdate)(ScrollOption*);

	ScrollOptionType ScrollType;
	int* pNumber;
	shared_ptr<int> SelectedNumberStorage;
	int* pSelectedNumber;
	bool* pBool;
	int iMin;
	int iMax;

	int iScrollSpeed;

	bool bHasMin;
	bool bHasMax;
	bool bLoop;

	bool bLeftDisabled;
	bool bRightDisabled;
	int iLeftTimer;
	int iRightTimer;

	bool bCanBeSaved;

	ScrollStruct<Type>* pScrollStruct;
	char szSubmenuName[20];
public:
	ScrollOption(ScrollOptionType type, const char* name) : Option(name), ScrollType(type), bHasMin(false), bCanBeSaved(false), bHasMax(false), bLoop(false), iScrollSpeed(25), FuncOnAction(nullsub), FuncCurrentOption(nullsub), FuncOnUpdate(v_idk) {}

	ScrollOption& addScroll(int& number, int min, int max, ScrollStruct<Type>* scrollStruct) {
		if (ScrollType == SELECT) {
			SelectedNumberStorage = make_shared<int>(0);
			pSelectedNumber = SelectedNumberStorage.get();
		}

		bIsScrollOption = true;
		bHasMin = true;
		bHasMax = true;
		iMin = min;
		iMax = max;
		pNumber = &number;
		pScrollStruct = scrollStruct;
		return *this;
	}

	ScrollOption& canBeSaved(const char* submenuName) {
		bCanBeSaved = true;
		strcpy(szSubmenuName, submenuName);
		return *this;
	}

	ScrollOption& addToggle(bool& toggle) {
		pBool = &toggle;
		return *this;
	}

	ScrollOption& addFunction(void(*func)()) {
		FuncOnAction = func;
		return *this;
	}

	ScrollOption& addOnUpdate(void(*func)(ScrollOption*)) {
		FuncOnUpdate = func;
		return *this;
	}

	ScrollOption& addRequirement(bool(*func)()) {
		FuncRequirement = func;
		return *this;
	}

	ScrollOption& addOnHover(void(*func)()) {
		FuncCurrentOption = func;
		return *this;
	}

	ScrollOption &canLoop() {
		bLoop = true;
		return *this;
	}

	ScrollOption& addTooltip(string tooltip) {
		Tooltip = tooltip;
		return *this;
	}

	const char* GetSubmenuName() { return szSubmenuName; }

	void LoadConfig(string value) {
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

				*pNumber = stoi(splitVals[1].c_str());
				FuncOnAction();
				return;
			}
		}

		*pNumber = stoi(value.c_str());
		FuncOnAction();
	}

	ConfigSaveData GetSaveData() {
		ConfigSaveData tmp;
		tmp.bPopulated = bCanBeSaved && pNumber != nullptr;

		if (tmp.bPopulated) {
			tmp.Type = ScrollType == TOGGLE ? SCROLL_OPTION_TOGGLE : SCROLL_OPTION;
			tmp.Value.iValue = (int)*pNumber;
			
			if (ScrollType == TOGGLE) tmp.bValue = *pBool;

			strcpy(tmp.szOptionName, szName);
			strcpy(tmp.szSubmenuName, szSubmenuName);
		}

		return tmp;
	}

	void Render(int pos) {
		FuncOnUpdate(this);

		switch (ScrollType) {
		case TOGGLE: {
			pRenderer.DrawOutlinedRect(830, 180.5f + (pos * pRenderer.fOptionHeight), 13, 13, 1, *pBool ? Color(160, 57, 64) : Color(0x383838FF), Color(0, 0, 0, 255), true);

			auto text = pScrollStruct[*pNumber].pName;
			pRenderer.DrawString(text, 820, 195 + (pos * pRenderer.fOptionHeight), pRenderer.Fonts.normalFont, 0.60f, Color(0xFFFFFFFF), false, false, JustifyRight);
			break;
		}

		case SCROLL:
		case SCROLLSELECT:
		default:
			auto text = pScrollStruct[*pNumber].pName;
			pRenderer.DrawString(text, 845, 195 + (pos * pRenderer.fOptionHeight), pRenderer.Fonts.normalFont, 0.60f, Color(0xFFFFFFFF), false, false, JustifyRight);
			break;
		}

		pRenderer.DrawString(szName, 435, 195 + (pos * pRenderer.fOptionHeight), pRenderer.Fonts.normalFont, 0.60f, Color(0xFFFFFFFF), false, false, JustifyLeft);
	}

	void RenderSelected(int pos) {
		FuncCurrentOption();

		if (IsOptionPressed() && FuncRequirement()) {
			switch (ScrollType) {
			case TOGGLE: *pBool ^= true; break;
			case SELECT: *pSelectedNumber = *pNumber; break;

			default:
			case SCROLLSELECT: FuncOnAction(); break;
			}
		}

		if (IsJustPressed(DPAD_LEFT)) {
			if (!bLeftDisabled) {
				*pNumber -= 1;
				if (bLoop) {
					if (*pNumber < iMin) *pNumber = iMax;
				} else if (*pNumber < iMin && bHasMin) *pNumber = iMin;
				if (ScrollType == SCROLL) FuncOnAction();
				if (ScrollType == TOGGLE && *pBool) FuncOnAction();
			}
			bLeftDisabled = false;
			iLeftTimer = 0;
		}

		if (IsJustPressed(DPAD_RIGHT)) {
			if (!bRightDisabled) {
				*pNumber += 1;
				if (bLoop) {
					if (*pNumber > iMax) *pNumber = iMin;
				} else if (*pNumber > iMax && bHasMax) *pNumber = iMax;
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
				if ((Engine::TimeGetTime() - TIMER) > iScrollSpeed) {
					*pNumber -= 1;
					if (bLoop) {
						if (*pNumber < iMin) *pNumber = iMax;
					} else if (*pNumber < iMin && bHasMin) *pNumber = iMin;
					if (ScrollType == SCROLL) FuncOnAction();
					if (ScrollType == TOGGLE && *pBool) FuncOnAction();
					TIMER = Engine::TimeGetTime();
				}
			}
		}

		if (IsDown(DPAD_RIGHT)) {
			if (++iRightTimer > 10) {
				bRightDisabled = true;
				if ((Engine::TimeGetTime() - TIMER) > iScrollSpeed) {
					*pNumber += 1;
					if (bLoop) {
						if (*pNumber > iMax) *pNumber = iMin;
					} else if (*pNumber > iMax && bHasMax) *pNumber = iMax;
					if (ScrollType == SCROLL) FuncOnAction();
					if (ScrollType == TOGGLE && *pBool) FuncOnAction();
					TIMER = Engine::TimeGetTime();
				}
			}
		}

		// pRenderer.SetTooltip(Tooltip);
	}
};