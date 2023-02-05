#pragma once

#define docryptoBypass(a,b)  ((QWORD)((QWORD)( ((QWORD)0xA73E08A182551A1E) * ((QWORD)(b)) ) ^ (~(QWORD)(a))))

#if defined(RELEASE_VERSION)
#define GetPatch(a) ((DWORD)(docryptoBypass(a, (QWORD)((((DWORD*)&a - (DWORD*)&xbLive.pPatches->BO2))))))
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
	DWORD TransformSeed;
	DWORD BG_GetSpreadForWeapon;
	DWORD RandomBulletDir;
	DWORD GetEntityPtr;
	DWORD Com_GetClientDObj;
	DWORD CG_DObjGetWorldTagPos;
	DWORD SL_GetString;
	DWORD SL_ConvertToString;
	DWORD CG_GetPlayerViewOrigin;
	DWORD CG_LocationalTrace;
	DWORD FireBulletPenetrate;
	DWORD GetClientActive;
	DWORD CG_GetWeaponIndexForName;
	DWORD GetWeaponDef;
	DWORD CG_DrawGrenadePointer;
	DWORD CG_DrawGrenadeIcon;
	DWORD Dvar_GetString;
	DWORD CL_SetStance;
	DWORD CG_DObjGetLocalTagMatrix;
	DWORD CG_DObjGetWorldTagMatrix;
	DWORD Autowall[8];
	DWORD NoRecoil;
	DWORD NoSway[2];
	DWORD NoFlinch[2];
	DWORD ConstantRadar[2];
	DWORD DvarThirdPerson;
	DWORD DvarFOV;
	DWORD ServerID;
	DWORD Laser;
	DWORD ScreenPlacement;
	DWORD LocalNamePointer;
	DWORD DisableEngineCrosshair;
	DWORD PatchGameNames;
	DWORD DrawGrenadePointer[3];
	DWORD DrawGrenadeIcon[2];
	DWORD RedBoxPerk[2];
	DWORD GetTagPosPatch[2];
	DWORD DevkitCrashPatch;
	DWORD CG_EntityEvent;
	DWORD CG_Respawn;
	DWORD CL_SendCmd;
	DWORD Menu_PaintAll;
	DWORD XamInputGetState;
	DWORD Menu_PaintAllPointer;
	DWORD BG_Random;
};

class Cheats {
public:
	bool bHasPatches;
	Patches BO2;

	HRESULT Apply(PVOID data) {
#ifndef RELEASE_VERSION
		BO2.R_RegisterMaterial = 0x822CAE50;
		BO2.R_AddCmdDrawStretchPic = 0x828B86C0;
		BO2.R_AddCmdDrawText = 0x828B8BA0;
		BO2.R_TextWidth = 0x828B6FD8;
		BO2.CG_DrawRotatedPicPhysical = 0x821C7F58;
		BO2.R_NormalizedTextScale = 0x828B6ED8;
		BO2.cl_ingame = 0x82C6FDC4;
		BO2.GetCG = 0x82BBAE68;
		BO2.GetServerInfo = 0x82BBAE44;
		BO2.GetNetInfoAddress = 0x82CAC3A0;
		BO2.TimeGetTime = 0x827D8DA0;
		BO2.Cbuf_AddText = 0x824015E0;
		BO2.CL_AddReliableCommand = 0x822786E0;
		BO2.TransformSeed = 0x826961B8;
		BO2.BG_GetSpreadForWeapon = 0x826BB4E0;
		BO2.RandomBulletDir = 0x82696250;
		BO2.GetEntityPtr = 0x82BBC554;
		BO2.Com_GetClientDObj = 0x82414578;
		BO2.CG_DObjGetWorldTagPos = 0x821D03F0;
		BO2.SL_GetString = 0x82533528;
		BO2.SL_ConvertToString = 0x82532A18;
		BO2.CG_GetPlayerViewOrigin = 0x822544B0;
		BO2.CG_LocationalTrace = 0x8225C568;
		BO2.FireBulletPenetrate = 0x82258840;
		BO2.GetClientActive = 0x82C70F4C;
		BO2.CG_GetWeaponIndexForName = 0x826C0598;
		BO2.GetWeaponDef = 0x826BF988;
		BO2.CG_DrawGrenadePointer = 0x821BE100;
		BO2.CG_DrawGrenadeIcon = 0x821BE330;
		BO2.Dvar_GetString = 0x82496990;
		BO2.CL_SetStance = 0x8225DDA0;
		BO2.CG_DObjGetLocalTagMatrix = 0x821D0280;
		BO2.CG_DObjGetWorldTagMatrix = 0x821D0390;
		BO2.Autowall[0] = 0x822DFB90;
		BO2.Autowall[1] = 0x82258520;
		BO2.Autowall[2] = 0x82257E30;
		BO2.Autowall[3] = 0x82258CE4;
		BO2.Autowall[4] = 0x82258FAC;
		BO2.Autowall[5] = 0x8225900C;
		BO2.Autowall[6] = 0x82258D60;
		BO2.Autowall[7] = 0x82259B40;
		BO2.NoRecoil = 0x82259BC8;
		BO2.NoSway[0] = 0x826C6E6C;
		BO2.NoSway[1] = 0x826C7A7C;
		BO2.NoFlinch[0] = 0x826C7A64;
		BO2.NoFlinch[1] = 0x8223FE80;
		BO2.ConstantRadar[0] = 0x821B8FCC;
		BO2.ConstantRadar[1] = 0x821B8FEC;
		BO2.DvarThirdPerson = 0x82BBC584;
		BO2.DvarFOV = 0x82BC2774;
		BO2.ServerID = 0x82C15758;
		BO2.Laser = 0x82255E14;
		BO2.ScreenPlacement = 0x82CBC168;
		BO2.LocalNamePointer = 0x839691AC;
		BO2.DisableEngineCrosshair = 0x821C77F0;
		BO2.PatchGameNames = 0x821C3C74;
		BO2.DrawGrenadePointer[0] = 0x82B27E90;
		BO2.DrawGrenadePointer[1] = 0x82BBC6CC;
		BO2.DrawGrenadePointer[2] = 0x82BC2790;
		BO2.DrawGrenadeIcon[0] = 0x82B25F48;
		BO2.DrawGrenadeIcon[1] = 0x82BBC6C4;
		BO2.RedBoxPerk[0] = 0x821F608C;
		BO2.RedBoxPerk[1] = 0x821F609C;
		BO2.GetTagPosPatch[0] = 0x8219F3CC;
		BO2.GetTagPosPatch[1] = 0x821A1C04;
		BO2.DevkitCrashPatch = 0x8228CFB0;
		BO2.CG_EntityEvent = 0x821D3D78;
		BO2.CG_Respawn = 0x821FC8D8;
		BO2.CL_SendCmd = 0x8225EAA8;
		BO2.Menu_PaintAll = 0x824744E0;
		BO2.XamInputGetState = 0x8293D884;
		BO2.Menu_PaintAllPointer = 0x83ba29f0;
		BO2.BG_Random = 0x82697FC0;

		bHasPatches = true;
#else
		if (data) {
			memcpy(&BO2, data, sizeof(Patches));
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
		ZeroMemory(&BO2, sizeof(Patches));
		Apply(NULL);
		bHasPatches = true;
#endif
	}

#ifdef DUMP_PATCH_DATA
	void DumpPatches();
#endif
};