#pragma once

#define docryptoBypass(a,b)  ((QWORD)((QWORD)( ((QWORD)0x7BE679B7C7E51DF7) * ((QWORD)(b)) ) ^ (~(QWORD)(a))))

#if defined(RELEASE_VERSION)
#define GetPatch(a) ((DWORD)(docryptoBypass(a, (QWORD)((((DWORD*)&a - (DWORD*)&xbLive.pPatches->MW1))))))
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
	DWORD Dvar_GetString;
	DWORD CG_CompassCalcDimensions;
	DWORD CG_Trace;
	DWORD FireBulletPenetrate;
	DWORD CL_SetStance;
	DWORD CG_GetEntityBModelBounds;
	DWORD CG_GetWeaponIndexForName;
	DWORD CG_CalcNamePosition;
	DWORD Cbuf_AddText;
	DWORD CG_DObjGetWorldTagPos;
	DWORD AimTarget_GetTagPos;
	DWORD Com_GetClientDObj;
	DWORD SL_GetString;
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
	DWORD CL_AllLocalClientsDisconnected;
	DWORD TimeGetTime;
	DWORD GetWeaponDef;
	DWORD Autowall[2];
	DWORD ServerID;
	DWORD NoRecoil;
	DWORD NoSway[2];
	DWORD NoFlinch;
	DWORD ConstantRadar;
	DWORD Laser;
	DWORD DvarSetHearEveryone;
	DWORD DvarThirdPerson[2];
	DWORD DvarFOV;
	DWORD WeaponDefPointer;
	DWORD ScreenPlacement;
	DWORD LocalNamePointer;
	DWORD XenonUserData;
	DWORD DisableEngineCrosshair;
	DWORD PatchGameNames[2];
	DWORD ui_mapname;
	DWORD DrawGrenadePointer[2];
	DWORD DrawGrenadeIcon[2];
	DWORD compassMaxRange;
	DWORD UI_GetTopActiveMenuName;
	DWORD Compass[21];
	DWORD CL_ReadyToSendPacket;
	DWORD CG_EntityEvent;
	DWORD CG_Respawn;
	DWORD Menu_PaintAll;
	DWORD Menu_PaintAllPointer;
	DWORD XamInputGetState;
};

class Cheats {
public:
	bool bHasPatches;
	Patches MW1;

	HRESULT Apply(PVOID data) {
#ifndef RELEASE_VERSION
		MW1.R_RegisterMaterial = 0x822A0298;
		MW1.R_AddCmdDrawStretchPic = 0x8216BAE8;
		MW1.R_AddCmdDrawText = 0x8216C0B8;
		MW1.R_TextWidth = 0x8216EB00;
		MW1.CG_DrawRotatedPicPhysical = 0x82318A88;
		MW1.R_NormalizedTextScale = 0x8216E690;
		MW1.Dvar_GetBool = 0x821D15D8;
		MW1.Dvar_GetString = 0x821D1478;
		MW1.CG_CompassCalcDimensions = 0x82323E28;
		MW1.CG_Trace = 0x8235DAA0;
		MW1.FireBulletPenetrate = 0x822EC4D0;
		MW1.CL_SetStance = 0x822D92A0;
		MW1.CG_GetEntityBModelBounds = 0x8235C7A0;
		MW1.CG_GetWeaponIndexForName = 0x82332FA0;
		MW1.CG_CalcNamePosition = 0x8231B4B0;
		MW1.Cbuf_AddText = 0x82239FD0;
		MW1.CG_DObjGetWorldTagPos = 0x82316088;
		MW1.AimTarget_GetTagPos = 0x823464B8;
		MW1.Com_GetClientDObj = 0x82308E20;
		MW1.SL_GetString = 0x8221F798;
		MW1.CG_DrawGrenadePointer = 0x8231EC68;
		MW1.CG_DrawGrenadeIcon = 0x8231EB10;
		MW1.RandomBulletDir = 0x822E9758;
		MW1.BG_GetSpreadForWeapon = 0x8232C478;
		MW1.CG_GetPlayerViewOrigin = 0x822EB5E8;
		MW1.BG_Random = 0x822E8AA8;
		MW1.GetEntityPtr = 0x823F5054;
		MW1.GetCG = 0x823F28A0;
		MW1.GetServerInfo = 0x823F2890;
		MW1.GetClientActive = 0x82435AB8;
		MW1.cl_ingame = 0x82435A08;
		MW1.CL_AllLocalClientsDisconnected = 0x822CF5C0;
		MW1.TimeGetTime = 0x821037F0;
		MW1.GetWeaponDef = 0x8232B5D8;
		MW1.Autowall[0] = 0x8229C6B0;
		MW1.Autowall[1] = 0x822EC2F8;
		MW1.ServerID = 0x84B3DDD4;
		MW1.NoRecoil = 0x822EDAA0;
		MW1.NoSway[0] = 0x8233169C;
		MW1.NoSway[1] = 0x8233048C;
		MW1.NoFlinch = 0x8235E284;
		MW1.ConstantRadar = 0x82322564;
		MW1.Laser = 0x822EEE1C;
		MW1.DvarSetHearEveryone = 0x823F572C;
		MW1.DvarThirdPerson[0] = 0x823F27A0;
		MW1.DvarThirdPerson[1] = 0x823F5694;
		MW1.DvarFOV = 0x823F5784;
		MW1.WeaponDefPointer = 0x823B9F60;
		MW1.ScreenPlacement = 0x8246F308;
		MW1.LocalNamePointer = 0x8243D700;
		MW1.XenonUserData = 0x84C24BB8;
		MW1.DisableEngineCrosshair = 0x8231A680;
		MW1.PatchGameNames[0] = 0x8231D1F0;
		MW1.PatchGameNames[1] = 0x8231D498;
		MW1.ui_mapname = 0x849F2D6C;
		MW1.DrawGrenadePointer[0] = 0x823F56E0;
		MW1.DrawGrenadePointer[1] = 0x823F579C;
		MW1.DrawGrenadeIcon[0] = 0x823F27E8;
		MW1.DrawGrenadeIcon[1] = 0x823F56DC;
		MW1.compassMaxRange = 0x823E0420;
		MW1.UI_GetTopActiveMenuName = 0x821EA390;
		MW1.Compass[0] = 0x82308128;
		MW1.Compass[1] = 0x82308150;
		MW1.Compass[2] = 0x82308238;
		MW1.Compass[3] = 0x823081EC;
		MW1.Compass[4] = 0x82308210;
		MW1.Compass[5] = 0x823082A8;
		MW1.Compass[6] = 0x82308270;
		MW1.Compass[7] = 0x82308040;
		MW1.Compass[8] = 0x82324428;
		MW1.Compass[9] = 0x823253C0;
		MW1.Compass[10] = 0x82325680;
		MW1.Compass[11] = 0x82325920;
		MW1.Compass[12] = 0x82325BC0;
		MW1.Compass[13] = 0x823250B8;
		MW1.Compass[14] = 0x822B36E8;
		MW1.Compass[15] = 0x8246F308;
		MW1.Compass[16] = 0x82324020;
		MW1.Compass[17] = 0x82324C08;
		MW1.Compass[18] = 0x82322868;
		MW1.Compass[19] = 0x823223E8;
		MW1.Compass[20] = 0x82321DD8;
		MW1.CL_ReadyToSendPacket = 0x822D86A0;
		MW1.CG_EntityEvent = 0x82312C08;
		MW1.CG_Respawn = 0x8235DE98;
		MW1.Menu_PaintAll = 0x821E7558;
		MW1.Menu_PaintAllPointer = 0x849F2DF0;
		MW1.XamInputGetState = 0x8236E0C4;

		bHasPatches = true;
#else
		if (data) {
			memcpy(&MW1, data, sizeof(Patches));
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
		ZeroMemory(&MW1, sizeof(Patches));
		Apply(NULL);
		bHasPatches = true;
#endif
	}

#ifdef DUMP_PATCH_DATA
	void DumpPatches();
#endif
};