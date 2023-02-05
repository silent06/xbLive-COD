#pragma once

#define docryptoBypass(a,b)  ((QWORD)((QWORD)( ((QWORD)0x318FC3DA4C9D9BD0) * ((QWORD)(b)) ) ^ (~(QWORD)(a))))

#if defined(RELEASE_VERSION)
#define GetPatch(a) ((DWORD)(docryptoBypass(a, (QWORD)((((DWORD*)&a - (DWORD*)&xbLive.pPatches->WAW))))))
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
	DWORD CG_CompassCalcDimensions;
	DWORD CG_Trace;
	DWORD FireBulletPenetrate;
	DWORD CL_SetStance;
	DWORD CG_GetWeaponIndexForName;
	DWORD Cbuf_AddText;
	DWORD CG_DObjGetWorldTagPos;
	DWORD Com_GetClientDObj;
	DWORD SL_GetString;
	DWORD CG_DrawGrenadePointer;
	DWORD CG_DrawGrenadeIcon;
	DWORD BG_GetSpreadForWeapon;
	DWORD CG_GetPlayerViewOrigin;
	DWORD BG_Random;
	DWORD GetEntityPtr;
	DWORD GetCG;
	DWORD GetServerInfo;
	DWORD GetClientActive;
	DWORD cl_ingame;
	DWORD CL_AllLocalClientsDisconnected;
	DWORD TimeGetTime;
	DWORD ui_gametype;
	DWORD WeaponDefPointer;
	DWORD Autowall[2];
	DWORD ServerID;
	DWORD NoRecoil;
	DWORD NoSway;
	DWORD NoFlinch;
	DWORD ConstantRadar;
	DWORD Laser;
	DWORD DvarSetHearEveryone;
	DWORD DvarThirdPerson[2];
	DWORD DvarFOV;
	DWORD ScreenPlacement;
	DWORD XenonUserData;
	DWORD LocalNamePointer;
	DWORD ui_mapname;
	DWORD compassMaxRange;
	DWORD UI_GetTopActiveMenuName;
	DWORD Compass[23];
	DWORD DisableEngineCrosshair;
	DWORD PatchGameNames;
	DWORD DrawGrenadePointer[2];
	DWORD DrawGrenadeIcon[2];
	DWORD Com_error;
	DWORD CL_SendCmd;
	DWORD CG_Respawn;
	DWORD Menu_PaintAll;
	DWORD XamInputGetState;
	DWORD RB_SetTessTechnique;
	DWORD CG_EntityEvent;
};

class Cheats {
public:
	bool bHasPatches;
	Patches WAW;

	HRESULT Apply(PVOID data) {
#ifndef RELEASE_VERSION
		WAW.R_RegisterMaterial = 0x821EA5D8;
		WAW.R_AddCmdDrawStretchPic = 0x82401410;
		WAW.R_AddCmdDrawText = 0x82401C30;
		WAW.R_TextWidth = 0x823FFF28;
		WAW.CG_DrawRotatedPicPhysical = 0x8215CEC0;
		WAW.R_NormalizedTextScale = 0x823FFEF8;
		WAW.CG_CompassCalcDimensions = 0x8214FCF8;
		WAW.CG_Trace = 0x821A2C58;
		WAW.FireBulletPenetrate = 0x8219F6D0;
		WAW.CL_SetStance = 0x821AD7D0;
		WAW.CG_GetWeaponIndexForName = 0x82144EB0;
		WAW.Cbuf_AddText = 0x8226FF08;
		WAW.CG_DObjGetWorldTagPos = 0x82161EA8;
		WAW.Com_GetClientDObj = 0x822758E8;
		WAW.SL_GetString = 0x8222D368;
		WAW.CG_DrawGrenadePointer = 0x82156838;
		WAW.CG_DrawGrenadeIcon = 0x821569B0;
		WAW.BG_GetSpreadForWeapon = 0x82141650;
		WAW.CG_GetPlayerViewOrigin = 0x8219BD50;
		WAW.BG_Random = 0x822046D0;
		WAW.GetEntityPtr = 0x8268FC30;
		WAW.GetCG = 0x8268CD98;
		WAW.GetServerInfo = 0x8268CD78;
		WAW.GetClientActive = 0x826E8BD8;
		WAW.cl_ingame = 0x826E8AFC;
		WAW.CL_AllLocalClientsDisconnected = 0x821B4BF0;
		WAW.TimeGetTime = 0x82398968;
		WAW.ui_gametype = 0x84FAA55C;
		WAW.WeaponDefPointer = 0x824C6CF8;
		WAW.Autowall[0] = 0x821EDEF0;
		WAW.Autowall[1] = 0x8219F640;
		WAW.ServerID = 0x84F44BC8;
		WAW.NoRecoil = 0x821A0BFC;
		WAW.NoSway = 0x8214789C;
		WAW.NoFlinch = 0x8217BEDC;
		WAW.ConstantRadar = 0x821547B4;
		WAW.Laser = 0x8219C270;
		WAW.DvarSetHearEveryone = 0x82691610;
		WAW.DvarThirdPerson[0] = 0x82510454;
		WAW.DvarThirdPerson[1] = 0x82691474;
		WAW.DvarFOV = 0x82691678;
		WAW.ScreenPlacement = 0x8274F580;
		WAW.XenonUserData = 0x852336B0;
		WAW.LocalNamePointer = 0x8243D700;
		WAW.ui_mapname = 0x84FAA4D8;
		WAW.compassMaxRange = 0x824F7FF8;
		WAW.UI_GetTopActiveMenuName = 0x8229E4F8;
		WAW.Compass[0] = 0x821784BC;
		WAW.Compass[1] = 0x821785B8;
		WAW.Compass[2] = 0x82178754;
		WAW.Compass[3] = 0x821785E4;
		WAW.Compass[4] = 0x82178694;
		WAW.Compass[5] = 0x821786D8;
		WAW.Compass[6] = 0x82178728;
		WAW.Compass[7] = 0x8217878C;
		WAW.Compass[8] = 0x821787C4;
		WAW.Compass[9] = 0x82150088;
		WAW.Compass[10] = 0x82150358;
		WAW.Compass[11] = 0x82150610;
		WAW.Compass[12] = 0x82150890;
		WAW.Compass[13] = 0x821518C8;
		WAW.Compass[14] = 0x82150B48;
		WAW.Compass[15] = 0x821D69D8;
		WAW.Compass[16] = 0x821510A0;
		WAW.Compass[17] = 0x82151E30;
		WAW.Compass[18] = 0x82154DD8;
		WAW.Compass[19] = 0x821553A0;
		WAW.Compass[20] = 0x82153828;
		WAW.Compass[21] = 0x821544A0;
		WAW.Compass[22] = 0x82154680;
		WAW.DisableEngineCrosshair = 0x8215C898;
		WAW.PatchGameNames = 0x82159B48;
		WAW.DrawGrenadePointer[0] = 0x826915AC;
		WAW.DrawGrenadePointer[1] = 0x82691694;
		WAW.DrawGrenadeIcon[0] = 0x8268C4A8;
		WAW.DrawGrenadeIcon[1] = 0x826915A8;
		WAW.Com_error = 0x82272068;
		WAW.CL_SendCmd = 0x821B13A8;
		WAW.CG_Respawn = 0x8217BAA8;
		WAW.Menu_PaintAll = 0x822B2F38;
		WAW.XamInputGetState = 0x82463714;
		WAW.RB_SetTessTechnique = 0x82419510;
		WAW.CG_EntityEvent = 0x82165518;

		bHasPatches = true;
#else
		if (data) {
			memcpy(&WAW, data, sizeof(Patches));
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
		ZeroMemory(&WAW, sizeof(Patches));
		Apply(NULL);
		bHasPatches = true;
#endif
	}

#ifdef DUMP_PATCH_DATA
	void DumpPatches();
#endif
};