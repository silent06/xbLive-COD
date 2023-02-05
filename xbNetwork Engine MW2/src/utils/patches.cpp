#include "stdafx.h"

#define DumpName MOUNT_PATH "\\xbLive Cheat Cache\\" GAME_NAME "-patch.bin"

#ifdef DUMP_PATCH_DATA
#define dumpPatch(a) ((DWORD)(docryptoBypass(a, (QWORD)((((DWORD*)&a - (DWORD*)&MW2))))))
BYTE dumpBuf[sizeof(Patches)];
void Cheats::DumpPatches() {
	if (!bHasPatches)
		return;

	LOG_DEV("Dumping!");

	memset(dumpBuf, 0, sizeof(Patches));

	DWORD *fileBuff = (DWORD*)&dumpBuf[0];
	for (int i = 0; i * 4 < sizeof(Patches); i += 1) {
		fileBuff[i] = (DWORD)dumpPatch(*(DWORD*)((DWORD)&MW2 + ((DWORD)i * 4)));
	}

	LOG_DEV("Writing!");

	if (pUtils.MountPath(MOUNT_PATH, pUtils.GetMountPath(), FALSE) == 0) {
		LOG_DEV("Mounted path successfully!");
	} else {
		LOG_DEV("Failed to mount path!");
		return;
	}

	pUtils.WriteFile(DumpName, dumpBuf, sizeof(Patches));
}
#endif