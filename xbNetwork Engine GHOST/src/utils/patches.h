#pragma once

#define docryptoBypass(a,b)  ((QWORD)((QWORD)( ((QWORD)0x9C7DFD3921E55B26) * ((QWORD)(b)) ) ^ (~(QWORD)(a))))

#if defined(RELEASE_VERSION)
#define GetPatch(a) ((DWORD)(docryptoBypass(a, (QWORD)((((DWORD*)&a - (DWORD*)&xbLive.pPatches->GHOSTS))))))
#else
#define	GetPatch(a) (a)
#endif

struct Patches {
	DWORD R_RegisterMaterial;
	DWORD R_AddCmdDrawStretchPic;
	DWORD R_AddCmdDrawText;
	DWORD R_TextWidth;
	DWORD CG_DrawRotatedPicPhysical;
	DWORD R_NormalizedTextScale;
	DWORD Dvar_GetBool;
	DWORD CG_WorldPosToCompass;
	DWORD CG_Trace;
	DWORD FireBulletPenetrate;
	DWORD CL_SetStance;
	DWORD CG_GetEntityBModelBounds;
	DWORD CG_GetWeaponIndexForName;
	DWORD CG_CalcNamePosition;
	DWORD Cbuf_AddText;
	DWORD CG_DObjGetWorldTagPos;
	DWORD GetTagPosition;
	DWORD Com_GetClientDObj;
	DWORD SL_GetString;
	DWORD AimAssist_GetTagPos;
	DWORD CG_DrawGrenadePointer;
	DWORD CG_DrawGrenadeIcon;
	DWORD RandomBulletDir;
	DWORD BG_SeedRandWithGameTime;
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
	DWORD WeaponDefPointer;
	DWORD Menu_PaintAllPointer;
	DWORD CompassGetVars;
	DWORD DirtyDiskError;
	DWORD SetupCompass;
	DWORD SetupMinimapIcons;
	DWORD SetupMinimap;
	DWORD Menu_PaintAll;
	DWORD CG_EntityEvent;
	DWORD CG_Respawn;
	DWORD CL_CreateNewCommands;
	DWORD CL_SendCmd;
	DWORD XamInputGetState;
	DWORD ServerID;
	DWORD NoRecoil;
	DWORD NoSway[2];
	DWORD NoFlinch;
	DWORD Laser;
	DWORD DvarSetHearEveryone[2];
	DWORD DvarThirdPerson[2];
	DWORD DvarFOV;
	DWORD ConstantRadar[4];
	DWORD ScreenPlacement;
	DWORD XenonUserData;
	DWORD ui_mapname;
	DWORD compassMaxRange;
	DWORD Compass[14];
	DWORD DisableEngineCrosshair;
	DWORD PatchGameNames[2];
	DWORD DrawGrenadePointer[2];
	DWORD DrawGrenadeIcon[2];
	DWORD Autowall[4];
};

class Cheats {
public:
	bool bHasPatches;
	Patches GHOSTS;

	HRESULT Apply(PVOID data) {
#ifndef RELEASE_VERSION
		GHOSTS.R_RegisterMaterial = 0x82376680;
		GHOSTS.R_AddCmdDrawStretchPic = 0x8266AF28;
		GHOSTS.R_AddCmdDrawText = 0x8266CEB8;
		GHOSTS.R_TextWidth = 0x8264DC78;
		GHOSTS.CG_DrawRotatedPicPhysical = 0x82270138;
		GHOSTS.R_NormalizedTextScale = 0x8264DC18;
		GHOSTS.Dvar_GetBool = 0x825639B0;
		GHOSTS.CG_WorldPosToCompass = 0x8225FD18;
		GHOSTS.CG_Trace = 0x822CB3B0;
		GHOSTS.FireBulletPenetrate = 0x822C7518;
		GHOSTS.CL_SetStance = 0x822D3A38;
		GHOSTS.CG_GetEntityBModelBounds = 0x822C9728;
		GHOSTS.CG_GetWeaponIndexForName = 0x8224A260;
		GHOSTS.CG_CalcNamePosition = 0x8226A098;
		GHOSTS.Cbuf_AddText = 0x8244C738;
		GHOSTS.CG_DObjGetWorldTagPos = 0x82273BC8;
		GHOSTS.GetTagPosition = 0x821379E0;
		GHOSTS.Com_GetClientDObj = 0x824723D8;
		GHOSTS.SL_GetString = 0x824934A8;
		GHOSTS.AimAssist_GetTagPos = 0x821379E0;
		GHOSTS.CG_DrawGrenadePointer = 0x822679A8;
		GHOSTS.CG_DrawGrenadeIcon = 0x82267B78;
		GHOSTS.RandomBulletDir = 0x822C2558;
		GHOSTS.BG_SeedRandWithGameTime = 0x82234840;
		GHOSTS.BG_GetSpreadForWeapon = 0x82254700;
		GHOSTS.CG_GetPlayerViewOrigin = 0x822BC078;
		GHOSTS.BG_Random = 0x8222EC70;
		GHOSTS.GetEntityPtr = 0x82AD11AC;
		GHOSTS.GetCG = 0x82AD56FC;
		GHOSTS.GetServerInfo = 0x82AD56F8;
		GHOSTS.GetClientActive = 0x82BAC404;
		GHOSTS.cl_ingame = 0x82B14194;
		GHOSTS.TimeGetTime = 0x8272E2E8;
		GHOSTS.ui_gametype = 0x83CAC2BC;
		GHOSTS.GetWeaponDef = 0x8213EDE0;
		GHOSTS.WeaponDefPointer = 0x82A96FD0;
		GHOSTS.Menu_PaintAllPointer = 0x83D51E20;
		GHOSTS.CompassGetVars = 0x8220D438;
		GHOSTS.DirtyDiskError = 0x82688558;
		GHOSTS.SetupCompass = 0x8220D778;
		GHOSTS.SetupMinimapIcons = 0x8220DA60;
		GHOSTS.SetupMinimap = 0x8220D8B0;
		GHOSTS.Menu_PaintAll = 0x822E7298;
		GHOSTS.CG_EntityEvent = 0x822785C0;
		GHOSTS.CG_Respawn = 0x82292740;
		GHOSTS.CL_CreateNewCommands = 0x822D67E8;
		GHOSTS.CL_SendCmd = 0x822D6CF8;
		GHOSTS.XamInputGetState = 0x828103EC;
		GHOSTS.ServerID = 0x82B55908;
		GHOSTS.NoRecoil = 0x822C9344;
		GHOSTS.NoSway[0] = 0x822583D0;
		GHOSTS.NoSway[1] = 0x82258BEC;
		GHOSTS.NoFlinch = 0x82292B64;
		GHOSTS.Laser = 0x8227F198;
		GHOSTS.DvarSetHearEveryone[0] = 0x82ACCA54;
		GHOSTS.DvarSetHearEveryone[1] = 0x82ACCA6C;
		GHOSTS.DvarThirdPerson[0] = 0x82A90960;
		GHOSTS.DvarThirdPerson[1] = 0x82ACCAD8;
		GHOSTS.DvarFOV = 0x82ACCADC;
		GHOSTS.ConstantRadar[0] = 0x82A90964;
		GHOSTS.ConstantRadar[1] = 0x822653A0;
		GHOSTS.ConstantRadar[2] = 0x82265794;
		GHOSTS.ConstantRadar[3] = 0x82265800;
		GHOSTS.ScreenPlacement = 0x82bcdd10;
		GHOSTS.XenonUserData = 0x83F0A358;
		GHOSTS.ui_mapname = 0x83CAC2C0;
		GHOSTS.compassMaxRange = 0x82ABF328;
		GHOSTS.Compass[0] = 0x8225F3D8;
		GHOSTS.Compass[1] = 0x82315010;
		GHOSTS.Compass[2] = 0x82315378;
		GHOSTS.Compass[3] = 0x82260B50;
		GHOSTS.Compass[4] = 0x82266520;
		GHOSTS.Compass[5] = 0x82266180;
		GHOSTS.Compass[6] = 0x82261A60;
		GHOSTS.Compass[7] = 0x82265AF8;
		GHOSTS.Compass[8] = 0x82264A38;
		GHOSTS.Compass[9] = 0x82265248;
		GHOSTS.Compass[10] = 0x82266D70;
		GHOSTS.Compass[11] = 0x825ED198;
		GHOSTS.Compass[12] = 0x82260E40;
		GHOSTS.Compass[13] = 0x82AD0D7C;
		GHOSTS.DisableEngineCrosshair = 0x8226EE90;
		GHOSTS.PatchGameNames[0] = 0x8226BA18;
		GHOSTS.PatchGameNames[1] = 0x8226BC0C;
		GHOSTS.DrawGrenadePointer[0] = 0x82ACCC5C;
		GHOSTS.DrawGrenadePointer[1] = 0x82ACCC60;
		GHOSTS.DrawGrenadeIcon[0] = 0x82ACCC68;
		GHOSTS.DrawGrenadeIcon[1] = 0x82ACCC6C;
		GHOSTS.Autowall[0] = 0x822C73C0;
		GHOSTS.Autowall[1] = 0x82385B38;
		GHOSTS.Autowall[2] = 0x822C784C;
		GHOSTS.Autowall[3] = 0x822C9380;

		bHasPatches = true;
#else
		if (data) {
			memcpy(&GHOSTS, data, sizeof(Patches));
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
		ZeroMemory(&GHOSTS, sizeof(Patches));
		Apply(NULL);
		bHasPatches = true;
#endif
	}

#ifdef DUMP_PATCH_DATA
	void DumpPatches();
#endif
};