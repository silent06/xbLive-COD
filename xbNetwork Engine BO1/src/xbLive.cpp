#include "stdafx.h"

void ConstantLoop() {
	xbLive.Initialize();

#ifdef DUMP_PATCH_DATA
	xbLive.pPatches->DumpPatches();
#endif

	if (XamGetCurrentTitleId() != GAME_TITLE) {
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
				memcpy(&xbLive.pPatches->BO1, data + 4, *(DWORD*)((DWORD)data));
				xbLive.pPatches->bHasPatches = true;
			}
		}
	}
#endif
	PLDR_DATA_TABLE_ENTRY entry;
	XexPcToFileHeader((PVOID)0x82000000, &entry);
	if (wcscmp(entry->BaseDllName.Buffer, L"default_mp.xex") == 0) {
		if (xbLive.pPatches->bHasPatches) {
			while (!xbLive.bTerminateProcess) {
				if (Native::XamGetCurrentTitleId() == GAME_TITLE && !xbLive.bShutdownCheats) {

					if (!pGame.bInitialized) {
						/*Menu starts here*/
						if (!pGame.Initialize()) {
							Sleep(1000);
						}
					}
					else
					{
						pGame.Run();
					}
				}
				else {
					LOG_DEV("Changing title! Shutdown initiated!");

					break;
				}
				Sleep(50);
			}

			if (pGame.bInitialized) {
				pGame.Shutdown();
			}
		}
	}

jUnload:
	if (pSystemHooks.bInitialized)
		pSystemHooks.Remove();

	xbLive.Shutdown();

	LOG_DEV("Exiting!");

	xbLive.bConstantLoopRunning = false;
	xbLive.bTerminateProcess = true;
	Sleep(20000);/*Freeze correction for dash while unloading*/
	if (!xbLive.bExternUnload) {
		*(WORD*)((DWORD)xbLive.hMyModule + 64) = 1;
		DWORD exitCode;
		LOG_DEV("Exiting thread");
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
		return TRUE;
	}
	}

	return FALSE;
}

BYTE szObfuscationData[0x1000] = { 'n', 'i', 'g', 'g', 'e', 'r', '6', '9' };

extern "C" BOOL WINAPI _CRT_INIT(HANDLE hModule, DWORD dwReason, LPVOID lpReserved);

#pragma code_seg(push, r1, ".ptext")
#pragma pack(push)
#pragma pack(1)
struct ObfuscationData {
	DWORD dwStart;
	DWORD dwSize;
	BYTE bStaticXor;
	BYTE bRC4KeyXor;
	BYTE szRC4Key[0x30];
};
#pragma pack(pop)

#pragma optimize( "", off )
__forceinline DWORD RandomStuff(int rand) {
	auto address = rand;

	address += 999;
	address ^= 1337;
	address ^= 0x1337;
	address += 69;
	address ^= 333;
	address ^= 666;
	address += 123;
	address -= 0x44 + 0xec + 0xa3 + 0x38 + 0x6c + 0xc5 + 0x70 + (0xdd ^ 12) + (12 << 8);
	address ^= 100;
	address ^= 0x12;
	address += 999;
	address ^= 1337;
	address ^= 0x1337;
	address += 69;
	address ^= 333;
	address ^= 666;
	address += 123;
	address -= 0x54 + 0xec + 0xa3 + 0x38 + 0x6c + 0xc5 + 0x70 + (0xdd ^ 12) + (12 << 8);
	address ^= 100;
	address ^= 0x12;
	address += 999;
	address ^= 1337;
	address ^= 0x1337;
	address += 69;
	address ^= 333;
	address ^= 666;
	address += 123;
	address -= 0x64 + 0xec + 0xa3 + 0x38 + 0x6c + 0xc5 + 0x70 + (0xdd ^ 12) + (12 << 8);
	address ^= 100;
	address ^= 0x12;
	address += 999;
	address ^= 1337;
	address ^= 0x1337;
	address += 69;
	address ^= 333;
	address ^= 666;
	address += 123;
	address -= 0xe4 + 0xec + 0xa3 + 0x38 + 0x6c + 0xc5 + 0x70 + (0xdd ^ 12) + (12 << 8);
	address ^= 100;
	address ^= 0x12;

	return address;
}
__forceinline byte RandomStuffByte(DWORD rand) {
	DWORD address = rand;

	address += 999;
	address ^= 1337;
	address ^= 0x1337;
	address += 69;
	address ^= 333;
	address ^= 666;
	address += 123;
	address -= 0x44 + 0xec + 0xa3 + 0x38 + 0x6c + 0xc5 + 0x70 + (0xdd ^ 12) + (12 << 8);
	address ^= 100;
	address ^= 0x12;
	address += 999;
	address ^= 1337;
	address ^= 0x1337;
	address += 69;
	address ^= 333;
	address ^= 666;
	address += 123;
	address -= 0x54 + 0xec + 0xa3 + 0x38 + 0x6c + 0xc5 + 0x70 + (0xdd ^ 12) + (12 << 8);
	address ^= 100;
	address ^= 0x12;
	address += 999;
	address ^= 1337;
	address ^= 0x1337;
	address += 69;
	address ^= 333;
	address ^= 666;
	address += 123;
	address -= 0x64 + 0xec + 0xa3 + 0x38 + 0x6c + 0xc5 + 0x70 + (0xdd ^ 12) + (12 << 8);
	address ^= 100;
	address ^= 0x12;
	address += 999;
	address ^= 1337;
	address ^= 0x1337;
	address += 69;
	address ^= 333;
	address ^= 666;
	address += 123;
	address -= 0xe4 + 0xec + 0xa3 + 0x38 + 0x6c + 0xc5 + 0x70 + (0xdd ^ 12) + (12 << 8);
	address ^= 100;
	address ^= 0x12;

	return (byte)(address & 0xFF);
}

BOOL APIENTRY SecureDllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	if (*(DWORD*)szObfuscationData != 0x6E696767) {
		ObfuscationData* data = (ObfuscationData*)szObfuscationData;

		// decrypt RC4 key
		for (auto i = 0; i < sizeof(data->szRC4Key); i++) {
			data->szRC4Key[i] ^= data->bRC4KeyXor;
		}

		RandomStuff(0x6E696767);
		RandomStuffByte(0x6E696767);

		// run new shit
		for (auto address = data->dwStart; address < (data->dwStart + data->dwSize); address++) {
			*(BYTE*)address = (*(BYTE*)address) ^ RandomStuffByte(0x12);
		}

		// run static xor
		for (auto address = data->dwStart; address < (data->dwStart + data->dwSize); address++) {
			*(BYTE*)address = (*(BYTE*)address) ^ data->bStaticXor;
		}

		RandomStuff(0x48565050);
		RandomStuffByte(0x48565050);

		// run RC4
		BYTE* pbKey = (BYTE*)data->szRC4Key;
		DWORD cbKey = sizeof(data->szRC4Key);
		BYTE* pbInpOut = (BYTE*)data->dwStart;
		DWORD cbInpOut = data->dwSize;

		byte s[256];
		byte k[256];
		byte temp;
		int i, j;

		if (!pbKey || !pbInpOut || !cbInpOut) {
			*(WORD*)((DWORD)hModule + 64) = 1;
			return FALSE;
		}

		for (i = 0; i < 256; i++) {
			s[i] = (byte)i;
			k[i] = pbKey[i % cbKey];
			RandomStuffByte(0x96969696);
		}

		j = 0;
		for (i = 0; i < 256; i++) {
			j = (j + s[i] + k[i]) % 256;
			temp = s[i];
			s[i] = s[j];
			s[j] = temp;
		}

		i = j = 0;
		for (int x = 0; x < cbInpOut; x++) {
			i = (i + 1) % 256;
			j = (j + s[i]) % 256;
			temp = s[i];
			s[i] = s[j];
			s[j] = temp;
			int t = (s[i] + s[j]) % 256;
			pbInpOut[x] ^= s[t];
		}

		for (auto address = data->dwStart; address < (data->dwStart + data->dwSize); address++) {
			if (address % 4 == 0) {
				__dcbst(NULL, (PVOID)address);
				__sync();
				__isync();
			}
		}

		RandomStuff(0x12121AAA);
		RandomStuffByte(0x12121AAA);
	}

	_CRT_INIT(hModule, ul_reason_for_call, lpReserved);
	return DllMain(hModule, ul_reason_for_call, lpReserved);
}
#pragma optimize( "", on )
#pragma code_seg(pop, r1)