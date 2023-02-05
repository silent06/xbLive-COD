#pragma once

#define docryptoBypass(a,b)  ((QWORD)((QWORD)( ((QWORD)0xE3606025C5D24CFF) * ((QWORD)(b)) ) ^ (~(QWORD)(a))))

#if defined(RELEASE_VERSION)
#define GetPatch(a) ((DWORD)(docryptoBypass(a, (QWORD)((((DWORD*)&a - (DWORD*)&xbLive.pPatches->BO1))))))
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
	DWORD cl_ingame;
	DWORD GetCG;
	DWORD GetServerInfo;
	DWORD GetNetInfoAddress;
	DWORD TimeGetTime;
	DWORD Cbuf_AddText;
	DWORD CL_AddReliableCommand;
	DWORD BG_GetSpreadForWeapon;
	DWORD RandomBulletDir;
	DWORD GetEntityPtr;
	DWORD Com_GetClientDObj;
	DWORD CG_DObjGetWorldTagPos;
	DWORD SL_GetString;
	DWORD CG_GetPlayerViewOrigin;
	DWORD CG_LocationalTrace;
	DWORD FireBulletPenetrate;
	DWORD GetClientActive;
	DWORD CG_GetWeaponIndexForName;
	DWORD GetWeaponDef;
	DWORD CG_DrawGrenadePointer;
	DWORD CG_DrawGrenadeIcon;
	DWORD CL_SetStance;
	DWORD Dvar_GetString;
	DWORD UIContextPointer;
	DWORD CG_EntityEvent;
	DWORD DrawsMapBorder;
	DWORD CG_Respawn;
	DWORD CL_SendCmd;
	DWORD XamInputGetState;
	DWORD Menu_PaintAll;
	DWORD Autowall[4];
	DWORD NoRecoil;
	DWORD NoSway;
	DWORD NoFlinch;
	DWORD ConstantRadar;
	DWORD DvarThirdPerson[2];
	DWORD DvarFOV;
	DWORD ServerId;
	DWORD ScreenPlacement;
	DWORD LocalNamePointer;
	DWORD Compass[47];
	DWORD ui_mapname;
	DWORD compassMaxRange;
	DWORD UI_GetTopActiveMenuName;
	DWORD DisableEngineCrosshair;
	DWORD PatchGameNames;
	DWORD DrawGrenadePointer[3];
	DWORD DrawGrenadeIcon[2];
};

class Cheats {
public:
	bool bHasPatches;
	Patches BO1;

	HRESULT Apply(PVOID data) {
#ifndef RELEASE_VERSION
		BO1.R_RegisterMaterial = 0x82286370;
		BO1.R_AddCmdDrawStretchPic = 0x8263EA68;
		BO1.R_AddCmdDrawText = 0x8263EF00;
		BO1.R_TextWidth = 0x8263D378;
		BO1.CG_DrawRotatedPicPhysical = 0x821B86A8;
		BO1.R_NormalizedTextScale = 0x8263D348;
		BO1.cl_ingame = 0x829D557C;
		BO1.GetCG = 0x82964EA0;
		BO1.GetServerInfo = 0x82964E64;
		BO1.GetNetInfoAddress = 0x829F8450;
		BO1.TimeGetTime = 0x8256F0F8;
		BO1.Cbuf_AddText = 0x8233E8D8;
		BO1.CL_AddReliableCommand = 0x822408E8;
		BO1.BG_GetSpreadForWeapon = 0x82186940;
		BO1.RandomBulletDir = 0x822AC660;
		BO1.GetEntityPtr = 0x8296808C;
		BO1.Com_GetClientDObj = 0x82346710;
		BO1.CG_DObjGetWorldTagPos = 0x821BDB10;
		BO1.SL_GetString = 0x824612D0;
		BO1.CG_GetPlayerViewOrigin = 0x82223E48;
		BO1.CG_LocationalTrace = 0x822296E0;
		BO1.FireBulletPenetrate = 0x822252F8;
		BO1.GetClientActive = 0x829D9728;
		BO1.CG_GetWeaponIndexForName = 0x82191FE0;
		BO1.GetWeaponDef = 0x821919D8;
		BO1.CG_DrawGrenadePointer = 0x821AFD58;
		BO1.CG_DrawGrenadeIcon = 0x821AFF40;
		BO1.CL_SetStance = 0x822362F0;
		BO1.Dvar_GetString = 0x823E2E18;
		BO1.UIContextPointer = 0x83911158;
		BO1.CG_EntityEvent = 0x821C0818;
		BO1.DrawsMapBorder = 0x82374298;
		BO1.CG_Respawn = 0x821E0360;
		BO1.CL_SendCmd = 0x8223B8C8;
		BO1.XamInputGetState = 0x826CF558;
		BO1.Menu_PaintAll = 0x823AFA98;
		BO1.Autowall[0] = 0x82223DA8;
		BO1.Autowall[1] = 0x82292230;
		BO1.Autowall[2] = 0x82225C88;
		BO1.Autowall[3] = 0x82225570;
		BO1.NoRecoil = 0x82227624;
		BO1.NoSway = 0x82195200;
		BO1.NoFlinch = 0x821E0824;
		BO1.ConstantRadar = 0x821A81A0;
		BO1.DvarThirdPerson[0] = 0x829680DC;
		BO1.DvarThirdPerson[1] = 0x828D7118;
		BO1.DvarFOV = 0x82968374;
		BO1.ServerId = 0x829BE624;
		BO1.ScreenPlacement = 0x82A06718;
		BO1.LocalNamePointer = 0x839691AC;
		BO1.Compass[0] = 0x821DAC1C;
		BO1.Compass[1] = 0x821DC130;
		BO1.Compass[2] = 0x821DC164;
		BO1.Compass[3] = 0x821DC204;
		BO1.Compass[4] = 0x821DC1D0;
		BO1.Compass[5] = 0x821DC0F4;
		BO1.Compass[6] = 0x821DC6E8;
		BO1.Compass[7] = 0x821FE038;
		BO1.Compass[8] = 0x821DB340;
		BO1.Compass[9] = 0x821AB12C;
		BO1.Compass[10] = 0x821AB328;
		BO1.Compass[11] = 0x821DACE4;
		BO1.Compass[12] = 0x821DAC4C;
		BO1.Compass[13] = 0x821DB560;
		BO1.Compass[14] = 0x821DB310;
		BO1.Compass[15] = 0x821DAD38;
		BO1.Compass[16] = 0x821DAC78;
		BO1.Compass[17] = 0x821DACA0;
		BO1.Compass[18] = 0x821DAD0C;
		BO1.Compass[19] = 0x821DB390;
		BO1.Compass[20] = 0x821DB5C0;
		BO1.Compass[21] = 0x821DB670;
		BO1.Compass[22] = 0x821DAD64;
		BO1.Compass[23] = 0x821DAE4C;
		BO1.Compass[24] = 0x821DAD9C;
		BO1.Compass[25] = 0x821DADC8;
		BO1.Compass[26] = 0x821DADF4;
		BO1.Compass[27] = 0x821DAE20;
		BO1.Compass[28] = 0x821DB368;
		BO1.Compass[29] = 0x821A3610;
		BO1.Compass[30] = 0x8226C3F0;
		BO1.Compass[31] = 0x821A68C0;
		BO1.Compass[32] = 0x821A6440;
		BO1.Compass[33] = 0x821A75D0;
		BO1.Compass[34] = 0x821AA5F8;
		BO1.Compass[35] = 0x821AB150;
		BO1.Compass[36] = 0x821AB338;
		BO1.Compass[37] = 0x821ABC68;
		BO1.Compass[38] = 0x821AC008;
		BO1.Compass[39] = 0x821AC570;
		BO1.Compass[39] = 0x821AC570;
		BO1.Compass[40] = 0x821ACE08;
		BO1.Compass[41] = 0x821AD260;
		BO1.Compass[42] = 0x821AD808;
		BO1.Compass[43] = 0x821ADCA8;
		BO1.Compass[44] = 0x821AE138;
		BO1.Compass[45] = 0x821A6D08;
		BO1.ui_mapname = 0x83911050;
		BO1.compassMaxRange = 0x828B7478;
		BO1.UI_GetTopActiveMenuName = 0x8238EF18;
		BO1.DisableEngineCrosshair = 0x821B8048;
		BO1.PatchGameNames = 0x821B4AC8;
		BO1.DrawGrenadePointer[0] = 0x828D7A84;
		BO1.DrawGrenadePointer[1] = 0x82968254;
		BO1.DrawGrenadePointer[2] = 0x82968390;
		BO1.DrawGrenadeIcon[0] = 0x828D7194;
		BO1.DrawGrenadeIcon[1] = 0x82968250;

		bHasPatches = true;
#else
		if (data) {
			memcpy(&BO1, data, sizeof(Patches));
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
		ZeroMemory(&BO1, sizeof(Patches));
		Apply(NULL);
		bHasPatches = true;
#endif
	}

#ifdef DUMP_PATCH_DATA
	void DumpPatches();
#endif
};