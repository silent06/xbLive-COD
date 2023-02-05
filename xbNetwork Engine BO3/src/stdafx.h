#pragma once
#define _USE_MATH_DEFINES

/*Required game information*/
#define GAME_NAME "BO3"
#define GAME_TITLE 0x4156091D

#pragma warning(disable : 4244)
#pragma warning(disable : 4172)
#pragma warning(disable : 4800)
#pragma warning(disable : 4018)

#include <xtl.h>
#include <xboxmath.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <time.h>
#include <vector>
#include <array>
#include <ppcintrinsics.h>
#include <math.h>
#include <fstream>
#include <cstdio>
#include <tchar.h>
#include <sstream>
#include <fstream>
#include <assert.h>
#include <vector>
#include <xhttp.h>
#include <string>
#include <xaudio2.h>
#include <xact3wb.h>
#include <functional>
#include <unordered_map>

#include "xkelib.h"

using namespace std;

#define NUMOF(x) (sizeof(x)/sizeof(x[0]))

#define RELEASE_VERSION
//#define DUMP_PATCH_DATA

#ifdef RELEASE_VERSION
#undef DUMP_PATCH_DATA
//#define USING_FUNC_OBF
#define USING_STR_OBF
#endif

#ifdef USING_STR_OBF
#define StrEnc(x) pUtils.XorStringNoLen("!|"#x, 0xFF)
#else
#define StrEnc(x) x
#endif

#define MOUNT_PATH "XBLIVE:"
#define CACHE_PATH MOUNT_PATH "\\xbLive Cheat Cache\\"
#define GAME_PATH CACHE_PATH GAME_NAME "\\"
#define ONLOAD_INI_PATH CACHE_PATH GAME_NAME "-xbLive.ini"
#define LOG_PATH CACHE_PATH GAME_NAME "-xbLive.log"
#define DEVICE_HDD "\\Device\\Harddisk0\\Partition1\\"
#define DEVICE_USB "\\Device\\Mass0"

#define ENCRYPTION_MARKER_BEGIN { \
	__asm { mr r4, r4 } \
	__asm { rlwinm r31, r31, 0,30,30 } \
	__asm { mr r5, r5 } \
	__asm { nop } \
}
#define ENCRYPTION_MARKER_END { \
	__asm { mr r5, r5 } \
	__asm { rlwinm r31, r31, 0,30,30 } \
	__asm { mr r4, r4 } \
	__asm { nop } \
}

static PKPCR GetThreadKPCR() {
	__asm {
		mr r3, r13
		blr
	}
} 

template<typename T>
__declspec(noinline) static bool ValidPtr(T* ptr) {
	DWORD address = (DWORD)ptr;
	if (ptr && (address > 0x30000000 && address < 0x80000000) && HIWORD(ptr) && MmIsAddressValid((void*)ptr)) {
		return true;
	}

	return false;
}

/*Utils*/
#include "utils/enums.h"
#include "utils/structs.h"
#include "utils/log.h"
#include "utils/patches.h"
#include "utils/global.h"
#include "utils/utils.h"
#include "utils/fibers.h"
#include "utils/ini.h"
#include "utils/memory/memoryCacher.h"

/*Security*/
#include "security/nativeInvoker.h"
#include "security/natives.h"
#include "security/functionObfuscation.h"
#include "utils/interface.h"

/*Engine*/
#include "engine/engine.h"

/*Backend*/
#include "backend/hooking.h"
#include "backend/systemHooks.h"
#include "backend/titleHooks.h"

/*Renderer*/
#include "menu/renderer.h"

/*Input*/
#include "utils/input/controller.h"

/*Options*/
#include "menu/options/option.h"
#include "menu/options/buttonOption.h"
#include "menu/options/toggleOption.h"
#include "menu/options/numberOption.h"
#include "menu/options/scrollOption.h"
#include "menu/options/submenuOption.h"
#include "menu/options/colorOption.h"

/*Submenu*/
#include "menu/submenu.h"
#include "menu/submenuHandler.h"

/*Menu*/
#include "menu/game.h"
#include "menu/menu.h"
#include "menu/utils/menuFunctions.h"