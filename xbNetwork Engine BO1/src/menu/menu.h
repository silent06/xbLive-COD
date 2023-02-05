#pragma once

class Menu {
public:
	bool bOpen;
	Vector2<float> vCenter;

	int iCurrentRenderingScroll;
	int iMaxOptions;
	int iCurrentOption;
	int iScrollOffset;
	int iBreakScroll;
	int iSelectedTab;

	void Render();
	void ASyncUpdate();
	void Initialize();

	bool IsSelected(int op);

	void Open() { bOpen = true; pSubmenuHandler.SetSubmenuMain(); }
	void Close() { bOpen = false; }
	void ToggleOpen() { Open(); }
	bool IsOpen() { return bOpen; }
};

extern Menu pMenu;