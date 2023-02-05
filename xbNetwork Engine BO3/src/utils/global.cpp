#include "stdafx.h"

Global xbLive;

void Global::Shutdown() {
	XPhysicalFree(pPatches);
}

HRESULT Global::Initialize() {
	pPatches = (Cheats*)XPhysicalAlloc(sizeof(Cheats), MAXULONG_PTR, NULL, PAGE_READWRITE);
	pPatches->Initialize();

	return STATUS_SUCCESS;
}

bool bTerminating = false;
void Terminate() {
	if (xbLive.bGameInitialized && !bTerminating) {
		bTerminating = true;
		LOG_DEV("Title is terminating!");
		LOG_DEV("No more web requests are busy!");

		xbLive.bShutdownCheats = true;

		while (xbLive.bShutdownCheats) {
			Sleep(50);
		}

		LOG_DEV("Cheats are fully shutdown!");
	}
}