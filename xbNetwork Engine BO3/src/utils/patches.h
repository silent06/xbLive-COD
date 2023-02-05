#pragma once

struct Patches {
	DWORD dwNigger;
};

class Cheats {
public:
	bool bHasPatches;
	Patches GTA;

	HRESULT Apply(PVOID data) {
#ifndef RELEASE_VERSION
		// set ur vars here
		GTA.dwNigger = 1337;

		bHasPatches = true;
#else
		if (data) {
			memcpy(&GTA, data, sizeof(Patches));
			bHasPatches = true;
			return S_OK;
		} else {
			bHasPatches = FALSE;
			return E_FAIL;
		}
#endif
		return S_OK;
	}

	void Initialize() {
		bHasPatches = false;

#ifndef RELEASE_VERSION
		ZeroMemory(&GTA, sizeof(Patches));
		Apply(NULL);
		bHasPatches = true;
#endif
	}

#ifdef DUMP_PATCH_DATA
	void DumpPatches();
#endif
};