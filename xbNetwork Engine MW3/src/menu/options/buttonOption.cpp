#include "stdafx.h"

DWORD WINAPI KeyboardHandlerThread(LPVOID lp) {
	XOVERLAPPED Overlapped;
	ZeroMemory(&Overlapped, sizeof(Overlapped));

	WCHAR wideBuffer[0x100];
	XShowKeyboardUI(0, VKBD_DEFAULT, L"", L"xbLive Engine", L"Enter your message!", wideBuffer, 0x100, &Overlapped);

	while (!XHasOverlappedIoCompleted(&Overlapped)) Sleep(1000);

	if (lstrlenW(wideBuffer)) {
		char lowKeyboardBuffer[0x100];
		wcstombs(lowKeyboardBuffer, wideBuffer, 0x100);

		if (strlen(lowKeyboardBuffer)) {
			Invoke::Call<int>((DWORD)lp, lowKeyboardBuffer);
		}
	}

	return 0;
}

void ButtonOption::Render(int pos) {
	FuncOnUpdate();

	pRenderer.DrawString(szName, 435, 195 + (pos * pRenderer.fOptionHeight), pRenderer.Fonts.normalFont, 0.50f, Color(0xFFFFFFFF), false, false, JustifyLeft);
}

void ButtonOption::RenderSelected(int pos) {
	FuncCurrentOption();

	if (IsOptionPressed() && FuncRequirement()) {
		if (bHasKeyboard) {
			CreateThread(0, 0, KeyboardHandlerThread, FuncKeyboardCallback, 0, 0);
		}

		if (FuncOnActionWithArg) {
			FuncOnActionWithArg(pFuncArg);
		}

		FuncOnAction();
	}
}