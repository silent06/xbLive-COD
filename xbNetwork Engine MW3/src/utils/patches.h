#pragma once

#define docryptoBypass(a,b)  ((QWORD)((QWORD)( ((QWORD)0x5DA1EE035704C819) * ((QWORD)(b)) ) ^ (~(QWORD)(a))))

#if defined(RELEASE_VERSION)
#define GetPatch(a) ((DWORD)(docryptoBypass(a, (QWORD)((((DWORD*)&a - (DWORD*)&xbLive.pPatches->MW3))))))
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
	DWORD R_NormalizedTextScale;
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
	DWORD AimAssist_GetTagPos;
	DWORD CG_DrawGrenadePointer;
	DWORD CG_DrawGrenadeIcon;
	DWORD RandomBulletDir;
	DWORD BG_SeedRandWithGameTime;
	DWORD BG_GetSpreadForWeapon;
	DWORD CG_GetPlayerViewOrigin;
	DWORD VectorToAngle;
	DWORD BG_Random;
	DWORD GetEntityPtr;
	DWORD GetCG;
	DWORD GetServerInfo;
	DWORD GetClientActive;
	DWORD GetXenonUserData;
	DWORD cl_ingame;
	DWORD TimeGetTime;
	DWORD ui_gametype;
	DWORD GetWeaponDefID;
	DWORD GetWeaponDef;
	DWORD Menu_PaintAllReturn;
	DWORD CG_EntityEvent;
	DWORD CG_Respawn;
	DWORD CL_CreateNewCommands;
	DWORD Menu_PaintAll;
	DWORD XamInputGetState;
	DWORD CL_SendCmd;
	DWORD BoneNotFoundErrorPatch;
	DWORD Autowall[4];
	DWORD ServerID;
	DWORD NoRecoil;
	DWORD NoSway[2];
	DWORD NoFlinch;
	DWORD NoScreenEffects[6];
	DWORD ConstantRadar;
	DWORD Laser;
	DWORD DvarSetHearEveryone[2];
	DWORD DvarThirdPerson[2];
	DWORD DvarFOV;
	DWORD ScreenPlacement;
	DWORD LocalNamePointer;
	DWORD DisableEngineCrosshair;
	DWORD PatchGameNames;
	DWORD ui_mapname;
	DWORD DrawGrenadePointer[2];
	DWORD DrawGrenadeIcon[2];
	DWORD compassMaxRange;
	DWORD UI_GetTopActiveMenuName;
	DWORD Compass[14];
};

class Cheats {
public:
	bool bHasPatches;
	Patches MW3;

	HRESULT Apply(PVOID data) {
#ifndef RELEASE_VERSION
		MW3.R_RegisterMaterial = 0x82413F48;
		MW3.R_RegisterFont = 0x82407A90;
		MW3.R_AddCmdDrawStretchPic = 0x8241F100;
		MW3.R_AddCmdDrawText = 0x8241F9E0;
		MW3.R_TextWidth = 0x82407B00;
		MW3.CG_DrawRotatedPicPhysical = 0x82117668;
		MW3.R_NormalizedTextScale = 0x82407AA0;
		MW3.CG_CompassDrawPlayerMap = 0x8210AC98;
		MW3.CG_CompassDrawPlayer = 0x8210B540;
		MW3.CG_CompassDrawCrates = 0x8210C328;
		MW3.CG_CompassDrawPlanes = 0x8210B818;
		MW3.CG_CompassDrawFriendlies = 0x8210DB68;
		MW3.CG_CompassDrawEnemies = 0x8210E3E0;
		MW3.CG_CompassDrawMissiles = 0x8210FE10;
		MW3.CG_CompassDrawTurrets = 0x8210E9A8;
		MW3.CG_CompassDrawHelicopter = 0x823AD678;
		MW3.CG_WorldPosToCompass = 0x82109C50;
		MW3.CG_Trace = 0x821631B8;
		MW3.FireBulletPenetrate = 0x8215FB08;
		MW3.CL_SetStance = 0x8216B928;
		MW3.CG_GetEntityBModelBounds = 0x82161610;
		MW3.CG_GetWeaponIndexForName = 0x820F7CB8;
		MW3.CG_CalcNamePosition = 0x82112908;
		MW3.Cbuf_AddText = 0x82287F68;
		MW3.CG_DObjGetWorldTagPos = 0x8211BCB8;
		MW3.AimTarget_GetTagPos = 0x820D4C40;
		MW3.Com_GetClientDObj = 0x822A28D0;
		MW3.SL_GetString = 0x822B5CC8;
		MW3.AimAssist_GetTagPos = 0x820D3860;
		MW3.CG_DrawGrenadePointer = 0x82111B88;
		MW3.CG_DrawGrenadeIcon = 0x82111D40;
		MW3.RandomBulletDir = 0x82159BE8;
		MW3.BG_SeedRandWithGameTime = 0x820E9C28;
		MW3.BG_GetSpreadForWeapon = 0x82101B08;
		MW3.CG_GetPlayerViewOrigin = 0x82159240;
		MW3.VectorToAngle = 0x823155F0;
		MW3.BG_Random = 0x820E7E20;
		MW3.GetEntityPtr = 0x826436B8;
		MW3.GetCG = 0x8263EE60;
		MW3.GetServerInfo = 0x8263EE44;
		MW3.GetClientActive = 0x82713DC4;
		MW3.GetXenonUserData = 0x839691A8;
		MW3.cl_ingame = 0x82713608;
		MW3.TimeGetTime = 0x824F0458;
		MW3.ui_gametype = 0x836E5ACC;
		MW3.GetWeaponDefID = 0x820D5A10;
		MW3.GetWeaponDef = 0x825E0318;
		MW3.Menu_PaintAllReturn = 0x8231198C;
		MW3.CG_EntityEvent = 0x8211DCD0;
		MW3.CG_Respawn = 0x82135BC0;
		MW3.CL_CreateNewCommands = 0x8216D8C8;
		MW3.Menu_PaintAll = 0x823091D0;
		MW3.XamInputGetState = 0x8257FF4C;
		MW3.CL_SendCmd = 0x8216DF18;
		MW3.BoneNotFoundErrorPatch = 0x820D4C98;
		MW3.Autowall[0] = 0x8215F9C0;
		MW3.Autowall[1] = 0x8215FDEC;
		MW3.Autowall[2] = 0x821FDF18;
		MW3.Autowall[3] = 0x82159738;
		MW3.ServerID = 0x826B81E8;
		MW3.NoRecoil = 0x821614BB;
		MW3.NoSway[0] = 0x82103CD8;
		MW3.NoSway[1] = 0x8210468C;
		MW3.NoFlinch = 0x820E5AE8;
		MW3.NoScreenEffects[0] = 0x82144130;
		MW3.NoScreenEffects[1] = 0x82111688;
		MW3.NoScreenEffects[2] = 0x82143610;
		MW3.NoScreenEffects[3] = 0x82164EF8;
		MW3.NoScreenEffects[4] = 0x82144108;
		MW3.NoScreenEffects[5] = 0x82143FC8;
		MW3.ConstantRadar = 0x8210E58C;
		MW3.Laser = 0x82124BD0;
		MW3.DvarSetHearEveryone[0] = 0x82643E60;
		MW3.DvarSetHearEveryone[1] = 0x8263EE10;
		MW3.DvarThirdPerson[0] = 0x8263ED14;
		MW3.DvarThirdPerson[1] = 0x82643CF0;
		MW3.DvarFOV = 0x82643EC4;
		MW3.ScreenPlacement = 0x827322C0;
		MW3.LocalNamePointer = 0x839691AC;
		MW3.DisableEngineCrosshair = 0x82116E78;
		MW3.PatchGameNames = 0x82112A30;
		MW3.ui_mapname = 0x836E5A18;
		MW3.DrawGrenadePointer[0] = 0x82643DF0;
		MW3.DrawGrenadePointer[1] = 0x82643ED8;
		MW3.DrawGrenadeIcon[0] = 0x8263ED60;
		MW3.DrawGrenadeIcon[1] = 0x82643DE8;
		MW3.compassMaxRange = 0x8261E0A4;
		MW3.UI_GetTopActiveMenuName = 0x822F06D0;
		MW3.Compass[0] = 0x82109E28;
		MW3.Compass[1] = 0x821A6428;
		MW3.Compass[2] = 0x82109ED4;
		MW3.Compass[3] = 0x822FF05C;
		MW3.Compass[4] = 0x82132D60;
		MW3.Compass[5] = 0x82132D98;
		MW3.Compass[6] = 0x82132CF0;
		MW3.Compass[7] = 0x82132DEC;
		MW3.Compass[8] = 0x82132D28;
		MW3.Compass[9] = 0x82132DB4;
		MW3.Compass[10] = 0x82132DD0;
		MW3.Compass[11] = 0x82132E2C;
		MW3.Compass[12] = 0x82132E10;
		MW3.Compass[13] = 0x82133340;

		bHasPatches = true;
#else
		if (data) {
			memcpy(&MW3, data, sizeof(Patches));
			bHasPatches = true;
			return S_OK;
		} else {
			bHasPatches = false;
			return E_FAIL;
		}
#endif
		return S_OK;
	}

	void Initialize() {
		bHasPatches = false;

#ifndef RELEASE_VERSION
		ZeroMemory(&MW3, sizeof(Patches));
		Apply(NULL);
		bHasPatches = true;
#endif
	}

#ifdef DUMP_PATCH_DATA
	void DumpPatches();
#endif
};