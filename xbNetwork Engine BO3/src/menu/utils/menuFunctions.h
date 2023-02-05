#pragma once
#include "../submenus/mainMenu.h"
//#include "../submenus/aimbotMenu.h"
//#include "../submenus/visualMenu.h"
//#include "../submenus/hvhMenu.h"
//#include "../submenus/playersMenu.h"
//#include "../submenus/settingsMenu.h"

static bool IsOptionPressed() {
	return pController.IsJustPressed(A);
}

static bool IsOpenPressed() {
	return pController.IsDown(DPAD_LEFT) && pController.IsDown(RIGHT_THUMB);
}

static void Up() {
	if (pSubmenuHandler.GetTotalOptions() == 0) return;
	pMenu.iCurrentOption--;
	if (pMenu.iScrollOffset > 0 && pMenu.iCurrentOption - pMenu.iScrollOffset == -1) pMenu.iScrollOffset--;
	pMenu.iBreakScroll = 1;
}

static void Down() {
	if (pSubmenuHandler.GetTotalOptions() == 0) return;
	pMenu.iCurrentOption++;
	if (pMenu.iScrollOffset < pSubmenuHandler.GetTotalOptions() - pMenu.iMaxOptions && pMenu.iCurrentOption - pMenu.iScrollOffset == pMenu.iMaxOptions) pMenu.iScrollOffset++;
	if (pSubmenuHandler.GetTotalOptions() >= pMenu.iMaxOptions && pMenu.iScrollOffset > pSubmenuHandler.GetTotalOptions() - pMenu.iMaxOptions) pMenu.iScrollOffset = pSubmenuHandler.GetTotalOptions() - pMenu.iMaxOptions;
	pMenu.iBreakScroll = 2;
}

static void Bottom() {
	if (pSubmenuHandler.GetTotalOptions() == 0) return;
	pMenu.iCurrentOption = pSubmenuHandler.GetTotalOptions() - 1;
	if (pSubmenuHandler.GetTotalOptions() >= pMenu.iMaxOptions) pMenu.iScrollOffset = pSubmenuHandler.GetTotalOptions() - pMenu.iMaxOptions;
	pMenu.iBreakScroll = 3;
}

static void Top() {
	if (pSubmenuHandler.GetTotalOptions() == 0) return;
	pMenu.iCurrentOption = 0;
	pMenu.iScrollOffset = 0;
	pMenu.iBreakScroll = 4;
}

static void MenuControls() {
	static int counter;
	static int delaytick = 150;

	if (counter < GetTickCount()) {
		if (pMenu.IsOpen()) {
			if (IsDown(DPAD_UP)) {
				if (pMenu.iCurrentOption == 0)
					Bottom();
				else
					Up();
				if (delaytick > 120) delaytick -= 15;
			} else if (IsDown(DPAD_DOWN)) {
				if (pMenu.iCurrentOption == pSubmenuHandler.GetTotalOptions() - 1)
					Top();
				else
					Down();
			} else if (IsJustPressed(B)) {
				pSubmenuHandler.SetSubmenuPrevious(false);
			} else if (IsJustPressed(LEFT_SHOULDER)) {
				pMenu.iCurrentOption = 0;
				pMenu.iScrollOffset = 0;
				pMenu.iSelectedTab--;
				pMenu.iSelectedTab = pMenu.iSelectedTab < 0 ? (6 - 1) : pMenu.iSelectedTab;

				switch (pMenu.iSelectedTab) {
				case 0: pSubmenuHandler.SetSubmenu(MainMenu::GetInstance()); break;
				//case 1: pSubmenuHandler.SetSubmenu(AimbotMenu::GetInstance()); break;
				//case 2: pSubmenuHandler.SetSubmenu(HvHMenu::GetInstance()); break;
				//case 3: pSubmenuHandler.SetSubmenu(VisualMenu::GetInstance()); break;
				//case 4: pSubmenuHandler.SetSubmenu(PlayersMenu::GetInstance()); break;
				//case 5: pSubmenuHandler.SetSubmenu(SettingsMenu::GetInstance()); break;
				}
			} else if (IsJustPressed(RIGHT_SHOULDER)) {
				pMenu.iCurrentOption = 0;
				pMenu.iScrollOffset = 0;
				pMenu.iSelectedTab++;
				pMenu.iSelectedTab = pMenu.iSelectedTab > (6 - 1) ? 0 : pMenu.iSelectedTab;

				switch (pMenu.iSelectedTab) {
				case 0: pSubmenuHandler.SetSubmenu(MainMenu::GetInstance()); break;
				//case 1: pSubmenuHandler.SetSubmenu(AimbotMenu::GetInstance()); break;
				//case 2: pSubmenuHandler.SetSubmenu(HvHMenu::GetInstance()); break;
				//case 3: pSubmenuHandler.SetSubmenu(VisualMenu::GetInstance()); break;
				//case 4: pSubmenuHandler.SetSubmenu(PlayersMenu::GetInstance()); break;
				//case 5: pSubmenuHandler.SetSubmenu(SettingsMenu::GetInstance()); break;
				}
			} else {
				delaytick = 150;
				return;
			}

			if (delaytick > 80) delaytick -= 15;
			counter = GetTickCount() + delaytick;
		}
	}
}