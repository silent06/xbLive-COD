#include "stdafx.h"

void ConstantLoop() {
	xbLive.Initialize();

#ifdef DUMP_PATCH_DATA
	xbLive.pPatches->DumpPatches();
#endif

	if (Native::XamGetCurrentTitleId() != GAME_TITLE) {
		LOG_DEV("Unsupported title!");
		xbLive.bTerminateProcess = true;
		goto jUnload;
	}

	if (!pSystemHooks.Apply()) {
		LOG_DEV("Failed to apply system hooks!");
		xbLive.bTerminateProcess = true;
		goto jUnload;
	}

	if (pUtils.MountPath(MOUNT_PATH, pUtils.GetMountPath(), FALSE) == 0) {
		LOG_DEV("Mounted path successfully!");
	}

	LOG_DEV("Started!");

#ifdef RELEASE_VERSION
	if (XexExecutableModuleHandle) {
		auto title = *XexExecutableModuleHandle;
		if (title) {
			auto data = Native::GetCheatPatches(Native::XamGetCurrentTitleId(), title->TimeDateStamp);

			if (data) {
				memcpy(&xbLive.pPatches->GTA, data + 4, *(DWORD*)((DWORD)data));
				xbLive.pPatches->bHasPatches = true;
			}
		}
	}
#endif

	if (xbLive.pPatches->bHasPatches) {
		while (!xbLive.bTerminateProcess) {
			if (Native::XamGetCurrentTitleId() == GAME_TITLE && !xbLive.bShutdownCheats) {
				if (!pGame.bInitialized) {
					/*Menu starts here!*/
					if (!pGame.Initialize()) {
						Sleep(1000);
					}
				} else {
					pGame.Run();
				}
			} else {
				LOG_DEV("Changing title! Shutdown initiated!");
				break;
			}
			Sleep(50);
		}

		if (pGame.bInitialized) {
			pGame.Shutdown();
		}
	}

jUnload:
	if (pSystemHooks.bInitialized)
		pSystemHooks.Remove();

	xbLive.Shutdown();

	LOG_DEV("Exiting!");

	xbLive.bConstantLoopRunning = false;
	Sleep(20000);/*Freeze correction for dash while unloading*/
	if (!xbLive.bExternUnload) {
		*(WORD*)((DWORD)xbLive.hMyModule + 64) = 1;
		DWORD exitCode;
		GetExitCodeThread(GetCurrentThread(), &exitCode);
		XexUnloadImageAndExitThread(xbLive.hMyModule, (HANDLE)exitCode);
	}
}

HRESULT HiddenThreadStartup() {
	HANDLE hThread; DWORD hThreadID;
	
	if (ExCreateThread(&hThread, 0, &hThreadID, (PVOID)XapiThreadStartup, (LPTHREAD_START_ROUTINE)ConstantLoop, NULL, 0x1c000427) != S_OK) {
		return E_FAIL;
	}

	xbLive.bConstantLoopRunning = true;

	XSetThreadProcessor(hThread, 4);
	ResumeThread(hThread);
	CloseHandle(hThread);

	return S_OK;
}
HRESULT Initialize() {
	pLog.Initialize();/*Clear Log*/
	if (FAILED(Invoker::Initialize())) {
		LOG_DEV("Invoker failed!");
		return E_FAIL;
	}

#ifdef RELEASE_VERSION
	BYTE* invokerentry = new BYTE[0x20];
	memset(invokerentry, 0, 0x20);

	*(BYTE*)(invokerentry) = 'x';
	*(BYTE*)(invokerentry + 1) = 'b';
	*(BYTE*)(invokerentry + 2) = 'd';
	*(BYTE*)(invokerentry + 3) = 'm';
	*(DWORD*)(invokerentry + 4) = (DWORD)HiddenThreadStartup;
	*(DWORD*)(invokerentry + 8) = 0x90f00000;
	LDR_DATA_TABLE_ENTRY* entry = (LDR_DATA_TABLE_ENTRY*)&invokerentry[12];

	// this call secretly initializes our thread
	XexPcToFileHeader(invokerentry, &entry);

	// this never gets past, as we'll make entry a nullptr
	if (entry) {
		if (entry->ImageBase == (void*)0x90f00000) {
			if (entry->Flags & 1) {
				if (entry->LoadCount == 3) {
					DWORD joker = entry->CheckSum ^ 1337;
					if (joker < 0x1000) {
						DbgPrint("DBG: Secret AES key is bad!\n");
					} else {
						XECRYPT_AES_STATE state;
						XeCryptAesKey(&state, invokerentry);
						XeCryptAesCbc(&state, (BYTE*)(0x90f00000 + 0x2000), 0x10, 0, 0, FALSE);
					}
				}
			}
		}
	}

	return S_OK;
#else
	return HiddenThreadStartup();
#endif
}

BOOL WINAPI DllMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved) {
	switch (dwReason) {
		case DLL_PROCESS_ATTACH: {
			srand(time(0));
			xbLive.hMyModule = hModule;
			xbLive.bDevkit = *(int*)0x8E038610 & 0x8000 ? false : true;

			if (FAILED(Initialize())) {
				*(WORD*)((DWORD)hModule + 64) = 1;
				return FALSE;
			}

			return TRUE;
		}

		case DLL_PROCESS_DETACH: {
			xbLive.bExternUnload = true;
			xbLive.bTerminateProcess = true;

			while (xbLive.bConstantLoopRunning) {
				Sleep(50);
			}

			LOG_PRINT("%s engine unloaded!", GAME_NAME);
			return TRUE;
		}
	}

	return FALSE;
}