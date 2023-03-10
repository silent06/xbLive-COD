#include "stdafx.h"

SystemHooks pSystemHooks;

Detour<void> OriginalExTerminateTitleProcess;
void ExTerminateTitleProcessHook(int r3) {
	LOG_DEV("ExTerminateTitleProcess!");

	Terminate();

	OriginalExTerminateTitleProcess.CallOriginal(0);
}

bool SystemHooks::Apply() {
	if (!bInitialized) {
		OriginalExTerminateTitleProcess.SetupDetour((DWORD)pUtils.ResolveFunction(MODULE_KERNEL, 0x1A), &ExTerminateTitleProcessHook);

		LOG_DEV("Applied detours! 2");
		bInitialized = true;
		return true;
	} else {
		LOG_DEV("System hooks already initialized!");
	}

	return false;
}

void SystemHooks::Remove() {
	if (bInitialized) {
		OriginalExTerminateTitleProcess.TakeDownDetour();
		LOG_DEV("Take down detour 4 hooks");
		bInitialized = false;

	} else {
		LOG_DEV("TitleHooks have not been initialized!");
	}
}