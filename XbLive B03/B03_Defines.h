#pragma once
#include "stdafx.h"
#include "Vector.h"

// angle conversions
#define GetPointer(X) *(DWORD*)(X);
#define GetPointer(X) *(DWORD*)(X);
#define M_1PI 3.14159265359f
#define M_2PI 6.28318530718f
#define AngleToShort(X) ((int)((X) * 65536 / 360) & 65535)
#define	ShortToAngle(X) ((X) * (360 / 65536))

// Some engine colors
static Vector4
purpleB03 = Vector4(0.6f, 0.2f, 0.8f, 1.0f),
whiteBO3 = Vector4(1, 1, 1, 1),
blackBO3 = Vector4(0, 0, 0, 1),
L_blackBO3 = Vector4(0, 0, 0, 0.2),
L_red2BO3 = Vector4(1, 0, 0, 0.4),
BlueStormzBO3 = Vector4(0.118, 0.639, 0.902, 1),
L_green2BO3 = Vector4(0, 1, 0, 0.4),
redBO3 = Vector4(1, 0, 0, 1),
greenBO3 = Vector4(0, 1, 0, 1),
blueBO3 = Vector4(0, 0, 1, 1),
yellowBO3 = Vector4(1, 1, 0, 1),
greyBO3 = Vector4(1.0f, 1.0f, 1.0f, 0.50f);

template<typename T> union XAssetPoolEntryBO3 {
	T entry;
	T *next;
};

template<typename T, int size> struct XAssetPoolBO3 {
	T *freeHead;
	XAssetPoolEntryBO3<T> entries[size];
};

enum XAssetTypeBO3 {
	physpresetBO3,
	physconstraintsBO3,
	destructibledefBO3,
	xanimBO3,
	xmodelBO3,
	xmodelmeshBO3,
	materialBO3,
	pixelshaderBO3,
	techsetBO3,
	imageBO3,
	soundBO3,
	sound_patchBO3,
	col_mapBO3,
	com_mapBO3,
	game_mapBO3,
	map_entsBO3,
	gfx_mapBO3,
	lightdefBO3,
	lensflaredefBO3,
	ui_mapBO3,
	fontBO3,
	fonticonBO3,
	localizeBO3,
	weaponBO3,
	weapondefBO3,
	weaponvariantBO3,
	weaponfullBO3,
	cgmediatableBO3,
	playersoundstableBO3,
	playerfxtableBO3,
	sharedweaponsoundsBO3,
	attachmentBO3,
	attachmentuniqueBO3,
	weaponcamoBO3,
	customizationtableBO3,
	customizationtable_feimagesBO3,
	customizationtablecolorBO3,
	snddriverglobalsBO3,
	fxBO3,
	fx_aliasBO3,
	tagfxBO3,
	klfBO3,
	impactsfxtableBO3,
	impactsoundstableBO3,
	player_characterBO3,
	aitypeBO3,
	characterBO3,
	xmodelaliasBO3,
	rawfileBO3,
	stringtableBO3,
	structuredtableBO3,
	leaderboarddefBO3,
	ddlBO3,
	glassesBO3,
	texturelistBO3,
	scriptparsetreeBO3,
	keyvaluepairsBO3,
	vehicleBO3,
	addon_map_entsBO3,
	tracerBO3,
	skinnedvertsBO3,
	slugBO3,
	surfacefxtableBO3,
	surfacesounddefBO3,
	footsteptableBO3,
	entityfximpactsBO3,
	entitysoundimpactsBO3,
	zbarrierBO3,
	vehiclefxdefBO3,
	vehiclesounddefBO3,
	typeinfoBO3,
	scriptbundleBO3,
	scriptbundlelistBO3,
	rumbleBO3,
	bulletpenetrationBO3,
	locdmgtableBO3,
	aimtableBO3,
	animselectortableBO3,
	animmappingtableBO3,
	animstatemachineBO3,
	behaviortreeBO3,
	behaviorstatemachineBO3,
	ttfBO3,
	lightdescriptionBO3,
	shellshockBO3,
	xcamBO3,
	bgcacheBO3,
	texturecomboBO3,
	flametableBO3,
	bitfieldBO3,
	attachmentcosmeticvariantBO3,
	maptableBO3,
	maptableloadingimagesBO3,
	medalBO3,
	medaltableBO3,
	objectiveBO3,
	objectivelistBO3,
	umbra_tomeBO3,
	navmeshBO3,
	navvolumeBO3,
	binaryhtmlBO3,
	laserBO3,
	beamBO3,
	streamerhintBO3,
	texture_atlasBO3,
	gfx_map_trzoneBO3,
	col_map_trzoneBO3,
	stringBO3,
	assetlistBO3,
	reportBO3,
	dependBO3
};

#pragma pack(push, 2)
struct GlyphBO3 {
	unsigned __int16 letter;
	char x0;
	char y0;
	char dx;
	char pixelWidth;
	char pixelHeight;
	float s0;
	float t0;
	float s1;
	float t1;
};
#pragma pack(pop)

struct KerningPairsBO3 {
	unsigned __int16 wFirst;
	unsigned __int16 wSecond;
	int iKernAmount;
};

struct Font_sBO3 {
	const char *fontName;
	int pixelHeight;
	int isScalingAllowed;
	int glyphCount;
	int kerningPairsCount;
	/*Material *material;
	Material *glowMaterial;*/
	void *material;
	void *glowMaterial;
	GlyphBO3 *glyphs;
	KerningPairsBO3 *kerningPairs;
};


struct RawFileBO3 {
	const char *name;
	int length;
	const char *buffer;
};

union XAssetHeaderBO3 {
	Font_sBO3 *font;
	RawFileBO3 *rawfile;
	void *data;
};

#pragma pack(push, 1)

enum entityType_tBO3 {
	ET_GENERALBO3,
	ET_PLAYERBO3,
	ET_PLAYER_CORPSEBO3,
	ET_ITEMBO3,
	ET_MISSILEBO3,
	ET_PLAYER_INVISIBLEBO3,
	ET_SCRIPTMOVERBO3,
	ET_SOUND_BLENDBO3,
	ET_FXBO3,
	ET_LOOP_FXBO3,
	ET_PRIMARY_LIGHTBO3,
	ET_LENSFLAREBO3,
	ET_REFLECTION_PROBEBO3,
	ET_HELICOPTERBO3,
	ET_PLANEBO3,
	ET_VEHICLEBO3,
	ET_VEHICLE_SPAWNERBO3,
	ET_VEHICLE_CORPSEBO3,
	ET_ACTORBO3,
	ET_ACTOR_SPAWNERBO3,
	ET_ACTOR_CORPSEBO3,
	ET_STREAMER_HINTBO3,
	ET_ZBARRIERBO3,
	ET_TRIGGERBO3
};

struct cached_client_tag_tBO3 {
	int time; // 0x0000
	Vector3 lastLocalTagOrigin; // 0x0004
	int visible; // 0x0010 doesnt update
	int predictedTime; // 0x0014
	Vector3 predictedPosition; // 0x0018
	Vector3 predictedAngles; // 0x0024
}; // size: 0x30

struct ClientTagCacheBO3 {
	cached_client_tag_tBO3 aim_head_tag; // 0x0000
	cached_client_tag_tBO3 aim_highest_tag; // 0x0030
}; // size: 0x60 possibly different
C_ASSERT(sizeof(ClientTagCacheBO3) == 0x60);

enum flags_tBO3 {
	FLAG_STANDINGBO3 = 0x02,
	FLAG_CROUCHBO3 = 0x04,
	FLAG_PRONEBO3 = 0x08,
	FLAG_SPRINTINGBO3 = 0x20000,
	FLAG_DEATHBO3 = 0x40000, // cant use this bc its reset during killcam
	FLAG_ADSBO3 = 0x80000
};

struct centity_sBO3 {
	BYTE _0x0000[40];
	Vector3 origin; // 0x0028
	Vector3 angles; // 0x0034
	BYTE _0x0040[536]; //0x0040 - 0x0258
	int clientNumber; // 0x0258
	BYTE _0x025C[4]; // 0x025C
	int flags; // 0x0260
	BYTE _0x0264[300]; // 0x0264 - 0x0390
	int weapon; // 0x0390
	BYTE _0x0394[45]; // 0x0394
	BYTE eType; // 0x03C1
	BYTE _0x03C2[58]; // 0x03C2 - 0x03F4
	ClientTagCacheBO3 *clientTagCache; // 0x03F4
	BYTE _0x03FC[480]; // 0x0454 - 0x0638
	BYTE alive; // 0x0638
	BYTE _0x063C[95]; // 0x063C
}; // size: 0x640
C_ASSERT(sizeof(centity_sBO3) == 0x640);

enum buttonsBO3 {
	BT_LTBO3 = 0x100080,
	BT_RTBO3 = 0x80000000
};

struct usercmd_sBO3 {
	int time; // 0x0000
	int buttons; // 0x0004
	BYTE _0x0008[8];
	int angles[3]; // 0x0010
	BYTE _0x001C[36];
}; // size: 0x40

struct clientActive_tBO3 {
	BYTE _0x0000[208];
	Vector3 origin; // 0x00D0
	Vector3 velocity; // 0x00DC
	BYTE _0x00E8[0x15C - 0xE8];
	Vector3 spawnAngles; // 0x015C
	BYTE _0x0168[0x31A0 - 0x168];
	Vector3 viewAngles; // 0x31A0
	BYTE _0x31AC[0x231BC - 0x31AC];
	usercmd_sBO3 usercmds[128]; // 0x231BC
	int commandNumber; // 0x251BC

	usercmd_sBO3 *getUserCmd(int i) {
		return &usercmds[i & 0x7F];
	}

	usercmd_sBO3 *getUserCmd() {
		return getUserCmd(this->commandNumber);
	}

}; // size: custom

struct cgs_tBO3 {
	int viewX; // 0x0000
	int viewY; // 0x0004
	int viewWidth; // 0x0008
	int viewHeight; // 0x000C
	float viewAspect; // 0x0010
	BYTE _0x0014[24];
	int localServer; // 0x002C
	char gametype[32]; // 0x0030
	char hostname[256]; // 0x0050
	int maxClients; // 0x0150
	BYTE _0x0154[4];
	char mappath[64]; // 0x0158
	char mapname[64]; // 0x0198
}; // size: custom

struct refdef_sBO3 {
	int x; // 0x0000
	int y; // 0x0004
	int width; // 0x0008
	int height; // 0x000C
	BYTE _0x0010[100];
	float zoomProgress; // 0x0074
	float tanHalfFovX; // 0x0078
	float tanHalfFovY; // 0x007C
	BYTE _0x0080[4];
	Vector3 viewOrigin; // 0x0084
	BYTE _0x0090[16];
	Vector3 viewAxis[3]; // 0x00A0
	BYTE _0x00C4[4];
	int time; // 0x00C8
}; // size: custom: 0xCC

struct clientInfo_tBO3 {
	int infoValid; // 0x0000
	int nextValid; // 0x0004
	int clientNumber; // 0x0008
	char name[32]; // 0x000C
	int team; // 0x002C
	int oldteam; // 0x0030
	int ffateam; // 0x0034
	int lastrank; // 0x0038
	BYTE _0x003C[36];
	char clantag[4]; // 0x0060
	BYTE _0x0064[4];
	int ping; // 0x0068
	int status_icon; // 0x006C
	int place; // 0x0070
	int score; // 0x0074
	int kills; // 0x0078
	int assists; // 0x007C
	int deaths; // 0x0080
	BYTE _0x0084[68];
	int health; // 0x00C8
	BYTE _0x00CC[1308];
	long long flags; // 0x05E8
	BYTE _0x05F0[908];
	int weapon; // 0x097C
}; // size: 0x980
C_ASSERT(sizeof(clientInfo_tBO3) == 0x980);

struct playerState_sBO3 {
	BYTE _0x0000[4];
	int cmdTime; // 0x0004
	BYTE _0x0008[88];
	Vector3 origin; // 0x0060
	Vector3 velocity; // 0x006C
	BYTE _0x0078[592];
	float weaponPosFraction; //0x02C8
}; // size: custom: 0x02CC




struct cg_sBO3 {
	int clientNumber; // 0x0000
	int localClientNumber; // 0x0004
	BYTE _0x0008[156];
	int stanceState; // 0x00A4
	BYTE _0x00A8[24];
	Vector3 origin; // 0x00C0
	Vector3 velocity; // 0x00CC
	BYTE _0x00D8[0x2C180 - 0xD8];
	playerState_sBO3 ps; // 0x2C180
	BYTE _0x2C44C[0x32550 - 0x2C44C];
	refdef_sBO3 refdef;  // 0x32550
	BYTE _0x3261C[0x54E10 - 0x3261C];
	clientInfo_tBO3 ci[12]; // 0x54E10
	BYTE _0x5C010[0x675A0 - 0x5C010];
	float aimSpreadScale; // 0x675A0
};

/*struct game_shit_s  {
	cgs_t *cgs;
	BYTE _one[0x14];
	cg_s *cg;
	BYTE _two[0x10];
	centity_s *cents;
	BYTE _three[0x15701A4];
	clientActive_t *client;
};*/

struct GfxCmdDrawText2DBO3 {
	BYTE _0x0000[12];
	float x; // 0x000C
	float y; // 0x0010
	float w; // 0x0014
	BYTE _0x0018[8];
	Font_sBO3 *font; // 0x0020
	float xScale; // 0x0024
	float yScale; // 0x0028
	int color; // 0x002C
	int maxChars; // 0x0030
	int renderFlags; // 0x0034
	BYTE _0x0038[12];
	int glowForceColor; // 0x0044
	int fxDecayDuration; // 0x0048
	int fxRedactDecayStartTime; // 0x004C
	int fxRedactDecayDuration; // 0x0050
	BYTE _0x0054[16];
	float padding; // 0x0064
	int text; // 0x0068
};

enum TraceHitTypeBO3 : int {
	TRACE_HITTYPE_NONEBO3 = 0x00,
	TRACE_HITTYPE_ENTITYBO3 = 0x01,
	TRACE_HITTYPE_DYNENT_MODELBO3 = 0x02,
	TRACE_HITTYPE_DYNENT_BRUSHBO3 = 0x03,
	TRACE_HITTYPE_GLASSBO3 = 0x04,
};

// i could easily do the rest but im lazy
struct trace_tBO3 {
	BYTE _0x0000[16];
	float fraction; // 0x0010
	BYTE _0x0014[44];
};

struct BulletFireParamsBO3 {
	int weaponEntIndex; // 0x00
	int ignoreEntIndex; // 0x04
	float damageMultiplier; // 0x08
	int methodOfDeath; // 0x0C
	Vector3 origStart; // 0x10
	Vector3 start; // 0x1C
	Vector3 end; // 0x28
	Vector3 dir; // 0x34
	BYTE _0x40[12];
}; // size: 0x4C

#pragma pack(pop)