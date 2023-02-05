#pragma once

#define docryptoBypass(a,b)  ((QWORD)((QWORD)( ((QWORD)0xFBAFE048C66E1015) * ((QWORD)(b)) ) ^ (~(QWORD)(a))))

#if defined(RELEASE_VERSION)
#define GetPatch(a) ((DWORD)(docryptoBypass(a, (QWORD)((((DWORD*)&a - (DWORD*)&xbLive.pPatches->AW))))))
#else
#define	GetPatch(a) (a)
#endif

struct Patches {
	DWORD R_RegisterMaterial;
	DWORD R_AddCmdDrawStretchPic;
	DWORD R_AddCmdDrawText;
	DWORD R_TextWidth;
	DWORD CG_DrawRotatedPicPhysical;
	DWORD Dvar_GetBool;
	DWORD CG_Trace;
	DWORD FireBulletPenetrate;
	DWORD CL_SetStance;
	DWORD CG_GetEntityBModelBounds;
	DWORD CG_GetWeaponIndexForName;
	DWORD CG_CalcNamePosition;
	DWORD Cbuf_AddText;
	DWORD CG_DObjGetWorldTagPos;
	DWORD Com_GetClientDObj;
	DWORD SL_GetString;
	DWORD AimAssist_GetTagPos;
	DWORD CG_DrawGrenadePointer;
	DWORD CG_DrawGrenadeIcon;
	DWORD RandomBulletDir;
	DWORD BG_GetSpreadForWeapon;
	DWORD CG_GetPlayerViewOrigin;
	DWORD BG_Random;
	DWORD GetEntityPtr;
	DWORD GetCG;
	DWORD GetServerInfo;
	DWORD GetClientActive;
	DWORD cl_ingame;
	DWORD TimeGetTime;
	DWORD ui_gametype;
	DWORD GetWeaponDef;
	DWORD SetupCompass;
	DWORD SetupMinimapIcons;
	DWORD SetupMinimap;
	DWORD Menu_PaintAll;
	DWORD CG_EntityEvent;
	DWORD CG_Respawn;
	DWORD CL_CreateNewCommands;
	DWORD CL_SendCmd;
	DWORD XamInputGetState;
	DWORD CompassGetVars;
	DWORD Menu_PaintAllReturnFix;
	DWORD Autowall[3];
	DWORD ScreenPlacement[2];
	DWORD ServerID;
	DWORD NoRecoil[2];
	DWORD NoSway[2];
	DWORD NoFlinch;
	DWORD DvarHearEveryone[2];
	DWORD DvarThirdPerson[2];
	DWORD DvarFOV[2];
	DWORD ConstantRadar;
	DWORD ui_mapname;
	DWORD compassMaxRange;
	DWORD CalculateCompassPosition;
	DWORD ScrView_ApplyRect;
	DWORD DrawCompass[12];
	DWORD DisableEngineCrosshair;
	DWORD DisableGameNames;
	DWORD DrawPointer[4];
	DWORD DrawGrenade[2];
	DWORD XenonUserData;
	DWORD Menu_PaintAllPointer;
};
class Cheats {
public:
	bool bHasPatches;
	Patches AW;

	HRESULT Apply(PVOID data) {
#ifndef RELEASE_VERSION
		AW.DrawGrenade[0] = 0x829AAEA4;
		AW.DrawGrenade[1] = 0x829AAEA8;
		AW.DrawPointer[0] = 0x829AAE9C;
		AW.DrawPointer[1] = 0x829AAEA0;
		AW.DrawPointer[2] = 0x829AAEAC;
		AW.DrawPointer[3] = 0x826302D6;
		AW.DisableGameNames = 0x8262D338;
		AW.DisableEngineCrosshair = 0x8262AF18;
		AW.DrawCompass[0] = 0x82639840;
		AW.DrawCompass[1] = 0x82633E28;
		AW.DrawCompass[2] = 0x826344B0;
		AW.DrawCompass[3] = 0x82637ED0;
		AW.DrawCompass[4] = 0x826348D8;
		AW.DrawCompass[5] = 0x82635928;
		AW.DrawCompass[6] = 0x82634FB8;
		AW.DrawCompass[7] = 0x826360E8;
		AW.DrawCompass[8] = 0x827A3450;
		AW.DrawCompass[9] = 0x826340B8;
		AW.DrawCompass[10] = 0x82638D28;
		AW.DrawCompass[11] = 0x82ACB044;
		AW.ScrView_ApplyRect = 0x82573978;
		AW.CalculateCompassPosition = 0x82637CE0;
		AW.compassMaxRange = 0x8296AE64;
		AW.ui_mapname = 0x83A172D4;
		AW.ConstantRadar = 0x82A773AC;
		AW.DvarFOV[0] = 0x829AAEB0;
		AW.DvarFOV[1] = 0x829AAEB4;
		AW.DvarThirdPerson[0] = 0x82A773A8;
		AW.DvarThirdPerson[1] = 0x829AAEB0;
		AW.DvarHearEveryone[0] = 0x829AAE84;
		AW.DvarHearEveryone[1] = 0x82ABDD94;
		AW.NoFlinch = 0x826019F4;
		AW.NoSway[0] = 0x82640418;
		AW.NoSway[1] = 0x826404D0;
		AW.NoRecoil[0] = 0x82648CEC;
		AW.NoRecoil[1] = 0x82648CF0;
		AW.ServerID = 0x82B4F1D4;
		AW.ScreenPlacement[0] = 0x82B94570;
		AW.ScreenPlacement[1] = 0x82B94648;
		AW.Autowall[0] = 0x825D22F8;
		AW.Autowall[1] = 0x82535D78;
		AW.Autowall[2] = 0x825D27DC;
		AW.Menu_PaintAllReturnFix = 0x8239DCB4;
		AW.CompassGetVars = 0x826878F8;
		AW.XamInputGetState = 0x827D35B4;
		AW.CL_SendCmd = 0x825B5420;
		AW.CL_CreateNewCommands = 0x825B79D8;
		AW.CG_Respawn = 0x826012E8;
		AW.CG_EntityEvent = 0x8261E5C8;
		AW.Menu_PaintAll = 0x8238FA70;
		AW.SetupMinimap = 0x8268F458;
		AW.SetupMinimapIcons = 0x8268FED0;
		AW.SetupCompass = 0x8268F520;
		AW.GetWeaponDef = 0x820F01D0;
		AW.ui_gametype = 0x83A172D0;
		AW.TimeGetTime = 0x82145400;
		AW.cl_ingame = 0x82B0D2A4;
		AW.GetClientActive = 0x82B0D308;
		AW.GetServerInfo = 0x82ACFE34;
		AW.GetCG = 0x82AD0298;
		AW.GetEntityPtr = 0x82ACFE30;
		AW.BG_Random = 0x82663EF0;
		AW.CG_GetPlayerViewOrigin = 0x825D39C0;
		AW.BG_GetSpreadForWeapon = 0x82647658;
		AW.RandomBulletDir = 0x825C45B8;
		AW.CG_DrawGrenadeIcon = 0x8262FE00;
		AW.CG_DrawGrenadePointer = 0x826300B0;
		AW.R_RegisterMaterial = 0x82544098;
		AW.R_AddCmdDrawStretchPic = 0x82295118;
		AW.R_AddCmdDrawText = 0x82295F60;
		AW.R_TextWidth = 0x822AC770;
		AW.CG_DrawRotatedPicPhysical = 0x826289C0;
		AW.Dvar_GetBool = 0x82364D40;
		AW.CG_Trace = 0x825C2238;
		AW.FireBulletPenetrate = 0x825D2420;
		AW.CL_SetStance = 0x825B59E8;
		AW.CG_GetEntityBModelBounds = 0x8243E5A0;
		AW.CG_GetWeaponIndexForName = 0x8248CF08;
		AW.CG_CalcNamePosition = 0x8262C140;
		AW.Cbuf_AddText = 0x82472B80;
		AW.CG_DObjGetWorldTagPos = 0x82623E10;
		AW.Com_GetClientDObj = 0x83B09C2C;
		AW.SL_GetString = 0x8242FD70;
		AW.AimAssist_GetTagPos = 0x82774628;
		AW.XenonUserData = 0x843DECB0;
		AW.Menu_PaintAllPointer = 0x841B0280;

		bHasPatches = true;
#else
		if (data) {
			memcpy(&AW, data, sizeof(Patches));
			bHasPatches = true;
			return S_OK;
		}
		else {
			bHasPatches = FALSE;
			return E_FAIL;
		}
#endif
		return S_OK;
	}

	void Initialize() {
		bHasPatches = false;

#ifndef RELEASE_VERSION
		ZeroMemory(&AW, sizeof(Patches));
		Apply(NULL);
		bHasPatches = true;
#endif
	}

#ifdef DUMP_PATCH_DATA
	void DumpPatches();
#endif
};
/*class Cheats {
public:
	bool bHasPatches;
	Patches AW;

	HRESULT Apply(PVOID data) {

#ifdef RELEASE_VERSION
		ZeroMemory(&AW, sizeof(Patches));
		Apply(NULL);
		bHasPatches = true;
#else

		AW.DrawGrenade[0] = 0x829AAEA4;
		AW.DrawGrenade[1] = 0x829AAEA8;
		AW.DrawPointer[0] = 0x829AAE9C;
		AW.DrawPointer[1] = 0x829AAEA0;
		AW.DrawPointer[2] = 0x829AAEAC;
		AW.DrawPointer[3] = 0x826302D6;
		AW.DisableGameNames = 0x8262D338;
		AW.DisableEngineCrosshair = 0x8262AF18;
		AW.DrawCompass[0] = 0x82639840;
		AW.DrawCompass[1] = 0x82633E28;
		AW.DrawCompass[2] = 0x826344B0;
		AW.DrawCompass[3] = 0x82637ED0;
		AW.DrawCompass[4] = 0x826348D8;
		AW.DrawCompass[5] = 0x82635928;
		AW.DrawCompass[6] = 0x82634FB8;
		AW.DrawCompass[7] = 0x826360E8;
		AW.DrawCompass[8] = 0x827A3450;
		AW.DrawCompass[9] = 0x826340B8;
		AW.DrawCompass[10] = 0x82638D28;
		AW.DrawCompass[11] = 0x82ACB044;
		AW.ScrView_ApplyRect = 0x82573978;
		AW.CalculateCompassPosition = 0x82637CE0;
		AW.compassMaxRange = 0x8296AE64;
		AW.ui_mapname = 0x83A172D4;
		AW.ConstantRadar = 0x82A773AC;
		AW.DvarFOV[0] = 0x829AAEB0;
		AW.DvarFOV[1] = 0x829AAEB4;
		AW.DvarThirdPerson[0] = 0x82A773A8;
		AW.DvarThirdPerson[1] = 0x829AAEB0;
		AW.DvarHearEveryone[0] = 0x829AAE84;
		AW.DvarHearEveryone[1] = 0x82ABDD94;
		AW.NoFlinch = 0x826019F4;
		AW.NoSway[0] = 0x82640418;
		AW.NoSway[1] = 0x826404D0;
		AW.NoRecoil[0] = 0x82648CEC;
		AW.NoRecoil[1] = 0x82648CF0;
		AW.ServerID = 0x82B4F1D4;
		AW.ScreenPlacement[0] = 0x82B94570;
		AW.ScreenPlacement[1] = 0x82B94648;
		AW.Autowall[0] = 0x825D22F8;
		AW.Autowall[1] = 0x82535D78;
		AW.Autowall[2] = 0x825D27DC;
		AW.Menu_PaintAllReturnFix = 0x8239DCB4;
		AW.CompassGetVars = 0x826878F8;
		AW.XamInputGetState = 0x827D35B4;
		AW.CL_SendCmd = 0x825B5420;
		AW.CL_CreateNewCommands = 0x825B79D8;
		AW.CG_Respawn = 0x826012E8;
		AW.CG_EntityEvent = 0x8261E5C8;
		AW.Menu_PaintAll = 0x8238FA70;
		AW.SetupMinimap = 0x8268F458;
		AW.SetupMinimapIcons = 0x8268FED0;
		AW.SetupCompass = 0x8268F520;
		AW.GetWeaponDef = 0x820F01D0;
		AW.ui_gametype = 0x83A172D0;
		AW.TimeGetTime = 0x82145400;
		AW.cl_ingame = 0x82B0D2A4;
		AW.GetClientActive = 0x82B0D308;
		AW.GetServerInfo = 0x82ACFE34;
		AW.GetCG = 0x82AD0298;
		AW.GetEntityPtr = 0x82ACFE30;
		AW.BG_Random = 0x82663EF0;
		AW.CG_GetPlayerViewOrigin = 0x825D39C0;
		AW.BG_GetSpreadForWeapon = 0x82647658;
		AW.RandomBulletDir = 0x825C45B8;
		AW.CG_DrawGrenadeIcon = 0x8262FE00;
		AW.CG_DrawGrenadePointer = 0x826300B0;
		AW.R_RegisterMaterial = 0x82544098;
		AW.R_AddCmdDrawStretchPic = 0x82295118;
		AW.R_AddCmdDrawText = 0x82295F60;
		AW.R_TextWidth = 0x822AC770;
		AW.CG_DrawRotatedPicPhysical = 0x826289C0;
		AW.Dvar_GetBool = 0x82364D40;
		AW.CG_Trace = 0x825C2238;
		AW.FireBulletPenetrate = 0x825D2420;
		AW.CL_SetStance = 0x825B59E8;
		AW.CG_GetEntityBModelBounds = 0x8243E5A0;
		AW.CG_GetWeaponIndexForName = 0x8248CF08;
		AW.CG_CalcNamePosition = 0x8262C140;
		AW.Cbuf_AddText = 0x82472B80;
		AW.CG_DObjGetWorldTagPos = 0x82623E10;
		AW.Com_GetClientDObj = 0x83B09C2C;
		AW.SL_GetString = 0x8242FD70;
		AW.AimAssist_GetTagPos = 0x82774628;
		AW.XenonUserData = 0x843DECB0;
		AW.Menu_PaintAllPointer = 0x841B0280;
		LOG_PRINT("starting patches 6");
		if (data) {
			memcpy(&AW, data, sizeof(Patches));
			LOG_PRINT("starting patches 7");
			bHasPatches = true;
			return S_OK;
		}
		else {
			bHasPatches = FALSE;
			return E_FAIL;
		}

		bHasPatches = true;
#endif	

		return S_OK;
	}

#ifdef RELEASE_VERSION
	void Initialize() {
		bHasPatches = false;
	}
#endif
	

#ifdef DUMP_PATCH_DATA
	void DumpPatches();
#endif
};
*/