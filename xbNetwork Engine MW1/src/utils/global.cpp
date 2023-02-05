#include "stdafx.h"

Global xbLive;

void Global::Shutdown() {
	XPhysicalFree(pPatches);
}

HRESULT Global::Initialize() {
	LOG_DEV("Applying Patches");
	pPatches = (Cheats*)XPhysicalAlloc(sizeof(Cheats), MAXULONG_PTR, NULL, PAGE_READWRITE);
	pPatches->Initialize();

	return STATUS_SUCCESS;
}

bool bTerminating = false;
void Terminate() {
	if (xbLive.bGameInitialized && !bTerminating) {
		bTerminating = true;
		xbLive.bShutdownCheats = true;

		while (xbLive.bShutdownCheats) {
			Sleep(50);
		}
	}
}