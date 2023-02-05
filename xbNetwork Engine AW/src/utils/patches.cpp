#include "stdafx.h"

#define DumpName MOUNT_PATH "\\xbLive Cheat Cache\\" GAME_NAME "-patch.bin"

#ifdef DUMP_PATCH_DATA
#define dumpPatch(a) ((DWORD)(docryptoBypass(a, (QWORD)((((DWORD*)&a - (DWORD*)&AW))))))
BYTE dumpBuf[sizeof(Patches)];
void Cheats::DumpPatches() {
	if (!bHasPatches)
		return;

	LOG_PRINT("Dumping!");

	memset(dumpBuf, 0, sizeof(Patches));

	DWORD *fileBuff = (DWORD*)&dumpBuf[0];
	for (int i = 0; i * 4 < sizeof(Patches); i += 1) {
		fileBuff[i] = (DWORD)dumpPatch(*(DWORD*)((DWORD)&AW + ((DWORD)i * 4)));
	}

	LOG_PRINT("Writing!");

	if (pUtils.MountPath(MOUNT_PATH, pUtils.GetMountPath(), FALSE) == 0) {
		LOG_PRINT("Mounted path successfully!");
	} else {
		LOG_PRINT("Failed to mount path!");
		return;
	}

	pUtils.WriteFile(DumpName, dumpBuf, sizeof(Patches));
}
#endif