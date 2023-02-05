#pragma once

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

/*Required game information*/
#define GAME_NAME "Black OPS 3"
#define GAME_TITLE 0x4156091D

#define MOUNT_PATH "xbLive:"
#define CACHE_PATH MOUNT_PATH "\\xbLive Cheat Cache\\"
#define GAME_PATH CACHE_PATH GAME_NAME "\\"
#define ONLOAD_INI_PATH CACHE_PATH GAME_NAME "-xbLive.ini"
#define LOG_PATH CACHE_PATH GAME_NAME "-xbLive.log"
#define DEVICE_HDD "\\Device\\Harddisk0\\Partition1\\"
#define DEVICE_USB "\\Device\\Mass0"

/*Utils*/
#include "Log.h"
#include "Global.h"
#include "Utils.h"

/*Security*/
#include "nativeInvoker.h"
#include "natives.h"
#include "interface.h"

/*Backend*/
#include "Hooking.h"
#include "SystemHooks.h"
#include "TitleHooks.h"
#include "B03_Defines.h"
#include "Vector.h"

/*Game*/
#include "Game.h"