#pragma once

#define docryptoBypass(a,b)  ((QWORD)((QWORD)( ((QWORD)0xB8D16D2BA64FFEAC) * ((QWORD)(b)) ) ^ (~(QWORD)(a))))

#if defined(RELEASE_VERSION)
#define GetPatch(a) ((DWORD)(docryptoBypass(a, (QWORD)((((DWORD*)&a - (DWORD*)&xbLive.pPatches->MW2))))))
#else
#define	GetPatch(a) (a)
#endif

struct Patches {
	DWORD R_RegisterMaterial;
	DWORD R_RegisterFont;
	DWORD R_AddCmdDrawStretchPic;
	DWORD R_AddCmdDrawText;
	DWORD R_TextWidth;
	DWORD CG_DrawRotatedPicPhysical;
	DWORD CG_DrawRotatedPic;
	DWORD R_NormalizedTextScale;
	DWORD Dvar_GetBool;
	DWORD Dvar_GetString;
	DWORD CG_CompassDrawPlayerMap;
	DWORD CG_CompassDrawPlayer;
	DWORD CG_CompassDrawCrates;
	DWORD CG_CompassDrawPlanes;
	DWORD CG_CompassDrawFriendlies;
	DWORD CG_CompassDrawEnemies;
	DWORD CG_CompassDrawMissiles;
	DWORD CG_CompassDrawTurrets;
	DWORD CG_CompassDrawHelicopter;
	DWORD CG_WorldPosToCompass;
	DWORD CG_CompassCalcDimensions;
	DWORD CG_Trace;
	DWORD FireBulletPenetrate;
	DWORD CL_SetStance;
	DWORD CG_GetEntityBModelBounds;
	DWORD CG_GetWeaponIndexForName;
	DWORD TimeGetTime;
	DWORD Cbuf_AddText;
	DWORD CG_DObjGetWorldTagPos;
	DWORD AimTarget_GetTagPos;
	DWORD Com_GetClientDObj;
	DWORD SL_GetString;
	DWORD CG_RegisterTag;
	DWORD AimAssist_GetTagPos;
	DWORD CG_DrawGrenadePointer;
	DWORD CG_DrawGrenadeIcon;
	DWORD RandomBulletDir;
	DWORD BG_SeedRandWithGameTime;
	DWORD BG_GetSpreadForWeapon;
	DWORD CG_GetPlayerViewOrigin;
	DWORD CG_BulletEndPos;
	DWORD VectorToAngle;
	DWORD BG_Random;
	DWORD GetEntityPtr;
	DWORD GetCG;
	DWORD GetServerInfo;
	DWORD GetClientActive;
	DWORD XenonUserData;
	DWORD cl_ingame;
	DWORD GetWeaponDef;
	DWORD WeaponDefPointer;
	DWORD CrashFix[2];
	DWORD Menu_PaintAllReturn;
	DWORD CG_EntityEvent;
	DWORD CG_Respawn;
	DWORD Menu_PaintAll;
	DWORD XamInputGetState;
	DWORD CL_SendCmd;
	DWORD Autowall[4];
	DWORD ServerID;
	DWORD NoRecoil;
	DWORD NoSway[2];
	DWORD NoFlinch;
	DWORD NoScreenEffects[6];
	DWORD ConstantRadar;
	DWORD Laser;
	DWORD DvarSetHearEveryone;
	DWORD DvarThirdPerson[2];
	DWORD DvarFOV;
	DWORD ScreenPlacement;
	DWORD UI_GetTopActiveMenuName;
	DWORD Scr_ApplyRect;
	DWORD ui_mapname;
	DWORD compassMaxRange;
	DWORD Compass[12];
	DWORD DisableEngineCrosshair;
	DWORD PatchGameNames[2];
	DWORD DrawGrenadePointer[2];
	DWORD DrawGrenadeIcon[2];
};

class Cheats {
public:
	bool bHasPatches;
	Patches MW2;

	HRESULT Apply(PVOID data) {
#ifndef RELEASE_VERSION
		MW2.R_RegisterMaterial = 0x8234E510;
		MW2.R_RegisterFont = 0x8234DCB0;
		MW2.R_AddCmdDrawStretchPic = 0x8234F9B8;
		MW2.R_AddCmdDrawText = 0x82350278;
		MW2.R_TextWidth = 0x8234DD20;
		MW2.CG_DrawRotatedPicPhysical = 0x820F7900;
		MW2.CG_DrawRotatedPic = 0x820F7AB0;
		MW2.R_NormalizedTextScale = 0x8234DCC0;
		MW2.Dvar_GetBool = 0x8229EEE8;
		MW2.Dvar_GetString = 0x8229F0A8;
		MW2.CG_CompassDrawPlayerMap = 0x820EC0C8;
		MW2.CG_CompassDrawPlayer = 0x820EC7A0;
		MW2.CG_CompassDrawCrates = 0x820ED520;
		MW2.CG_CompassDrawPlanes = 0x820ECA10;
		MW2.CG_CompassDrawFriendlies = 0x820EE938;
		MW2.CG_CompassDrawEnemies = 0x820EEFA8;
		MW2.CG_CompassDrawMissiles = 0x820EFEA0;
		MW2.CG_CompassDrawTurrets = 0x820EF3B8;
		MW2.CG_CompassDrawHelicopter = 0x82315F90;
		MW2.CG_WorldPosToCompass = 0x820EB0A0;
		MW2.CG_CompassCalcDimensions = 0x820EB278;
		MW2.CG_Trace = 0x82136E88;
		MW2.FireBulletPenetrate = 0x82134648;
		MW2.CL_SetStance = 0x8213E600;
		MW2.CG_GetEntityBModelBounds = 0x82135D10;
		MW2.CG_GetWeaponIndexForName = 0x822105A8;
		MW2.TimeGetTime = 0x82332268;
		MW2.Cbuf_AddText = 0x82224990;
		MW2.CG_DObjGetWorldTagPos = 0x820FB9E8;
		MW2.AimTarget_GetTagPos = 0x820C5830;
		MW2.Com_GetClientDObj = 0x8222FCC0;
		MW2.SL_GetString = 0x82242250;
		MW2.CG_RegisterTag = 0x821F2A78;
		MW2.AimAssist_GetTagPos = 0x820C4458;
		MW2.CG_DrawGrenadePointer = 0x820F17F0;
		MW2.CG_DrawGrenadeIcon = 0x820F1958;
		MW2.RandomBulletDir = 0x8212EF78;
		MW2.BG_SeedRandWithGameTime = 0x820D94B8;
		MW2.BG_GetSpreadForWeapon = 0x820E33F0;
		MW2.CG_GetPlayerViewOrigin = 0x8212E670;
		MW2.CG_BulletEndPos = 0x8212F000;
		MW2.VectorToAngle = 0x82289930;
		MW2.BG_Random = 0x820D76F0;
		MW2.GetEntityPtr = 0x825BE150;
		MW2.GetCG = 0x825B8638;
		MW2.GetServerInfo = 0x825B861C;
		MW2.GetClientActive = 0x82682350;
		MW2.XenonUserData = 0x838BA820;
		MW2.cl_ingame = 0x825E21F0;
		MW2.GetWeaponDef = 0x820E22C0;
		MW2.WeaponDefPointer = 0x820E22D8;
		MW2.CrashFix[0] = 0x820C588C;
		MW2.CrashFix[1] = 0x82127E88;
		MW2.Menu_PaintAllReturn = 0x82276A28;
		MW2.CG_EntityEvent = 0x820FD778;
		MW2.CG_Respawn = 0x82112D58;
		MW2.Menu_PaintAll = 0x82285E98;
		MW2.XamInputGetState = 0x823B64C4;
		MW2.CL_SendCmd = 0x821406E8;
		MW2.Autowall[0] = 0x82134510;
		MW2.Autowall[1] = 0x8213492C;
		MW2.Autowall[2] = 0x821A4A50;
		MW2.Autowall[3] = 0x8212EB48;
		MW2.ServerID = 0x826237E0;
		MW2.NoRecoil = 0x82135BE3;
		MW2.NoSway[0] = 0x820E5B38;
		MW2.NoSway[1] = 0x820E657C;
		MW2.NoFlinch = 0x821131A4;
		MW2.NoScreenEffects[0] = 0x8211F8F8;
		MW2.NoScreenEffects[1] = 0x820F1370;
		MW2.NoScreenEffects[2] = 0x8211EE70;
		MW2.NoScreenEffects[3] = 0x821388D8;
		MW2.NoScreenEffects[4] = 0x8211F8D0;
		MW2.NoScreenEffects[5] = 0x8211F830;
		MW2.ConstantRadar = 0x820EF0C4;
		MW2.Laser = 0x82104090;
		MW2.DvarSetHearEveryone = 0x825BE868;
		MW2.DvarThirdPerson[0] = 0x825B435C;
		MW2.DvarThirdPerson[1] = 0x825BE790;
		MW2.DvarFOV = 0x825BE8C8;
		MW2.ScreenPlacement = 0x82691100;
		MW2.UI_GetTopActiveMenuName = 0x82271020;
		MW2.Scr_ApplyRect = 0x82164E78;
		MW2.ui_mapname = 0x836477B8;
		MW2.compassMaxRange = 0x8259BAC0;
		MW2.Compass[0] = 0x820EB324;
		MW2.Compass[1] = 0x8227968C;
		MW2.Compass[2] = 0x82110318;
		MW2.Compass[3] = 0x82110350;
		MW2.Compass[4] = 0x821102A8;
		MW2.Compass[5] = 0x821103A8;
		MW2.Compass[6] = 0x821102E0;
		MW2.Compass[7] = 0x8211036C;
		MW2.Compass[8] = 0x82110388;
		MW2.Compass[9] = 0x821103F8;
		MW2.Compass[10] = 0x821103DC;
		MW2.Compass[11] = 0x821103C0;
		MW2.DisableEngineCrosshair = 0x820F59B8;
		MW2.PatchGameNames[0] = 0x820F32C8;
		MW2.PatchGameNames[1] = 0x820F30A0;
		MW2.DrawGrenadePointer[0] = 0x825BE7FC;
		MW2.DrawGrenadePointer[1] = 0x825BE8DC;
		MW2.DrawGrenadeIcon[0] = 0x825B8554;
		MW2.DrawGrenadeIcon[1] = 0x825BE7F0;

		bHasPatches = true;
#else
		if (data) {
			memcpy(&MW2, data, sizeof(Patches));
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
		ZeroMemory(&MW2, sizeof(Patches));
		Apply(NULL);
		bHasPatches = true;
#endif
	}

#ifdef DUMP_PATCH_DATA
	void DumpPatches();
#endif
};