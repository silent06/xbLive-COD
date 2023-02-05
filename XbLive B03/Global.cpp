#include "stdafx.h"

Global xbLive;

bool bTerminating = false;
void Terminate() {
	if (xbLive.bGameInitialized && !bTerminating) {
		bTerminating = true;
		xbLive.bShutdownCheats = true;

		while (xbLive.bShutdownCheats) {
			Sleep(10);
		}
	}
}