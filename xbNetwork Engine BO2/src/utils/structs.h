#pragma once

typedef struct _XEX_IMPORT_TABLE_2 {
	DWORD                 TableSize;
	HV_IMAGE_IMPORT_TABLE ImportTable;
} XEX_IMPORT_TABLE_2, *PXEX_IMPORT_TABLE_2;

typedef struct _LDR_DATA_TABLE_ENTRY_2 {
	LIST_ENTRY     InLoadOrderLinks;
	LIST_ENTRY     InClosureOrderLinks;
	LIST_ENTRY     InInitializationOrderLinks;
	VOID*          NtHeadersBase;
	VOID*          ImageBase;
	DWORD          SizeOfNtImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
	DWORD          Flags;
	DWORD          SizeOfFullImage;
	VOID*          EntryPoint;
	WORD           LoadCount;
	WORD           ModuleIndex;
	VOID*          DllBaseOriginal;
	DWORD          CheckSum;
	DWORD          ModuleLoadFlags;
	DWORD          TimeDateStamp;
	VOID*          LoadedImports;
	VOID*          XexHeaderBase;
	union {
		ANSI_STRING               LoadFileName;
		struct {
			_LDR_DATA_TABLE_ENTRY* ClosureRoot;
			_LDR_DATA_TABLE_ENTRY* TraversalParent;
		} asEntry;
	};
} LDR_DATA_TABLE_ENTRY_2, *PLDR_DATA_TABLE_ENTRY_2;

#pragma region Vectors
template<typename T>
struct Vector2 {
	T X;
	T Y;

	Vector2() {}

	Vector2(T x, T y)
		: X(x), Y(y) {
	}

	bool operator != (Vector2& input) {
		return input.X != X && input.Y != Y;
	}

	void operator += (float value) {
		X += value;
		Y += value;
	}
};

template<typename T>
struct Vector3 {
	T X;
	T Y;
	T Z;

	Vector3() {}

	Vector3(T x, T y, T z)
		: X(x), Y(y), Z(z) {
	}

	// unary operators
	Vector3& operator + () const {
		return *this;
	}

	Vector3& operator - () const {
		return Vector3(-X, -Y, -Z);
	}

	Vector3& operator = (const Vector3& v) {
		X = v.X;
		Y = v.Y;
		Z = v.Z;
		return *this;
	}

	Vector3& operator += (const Vector3& v) {
		X += v.X;
		Y += v.Y;
		Z += v.Z;
		return *this;
	}

	Vector3& operator -= (const Vector3& v) {
		X -= v.X;
		Y -= v.Y;
		Z -= v.Z;
		return *this;
	}

	Vector3& operator *= (float f) {
		X *= f;
		Y *= f;
		Z *= f;
		return *this;
	}

	Vector3& operator /= (float f) {
		float fInv = 1.0f / f;
		X *= fInv;
		Y *= fInv;
		Z *= fInv;
		return *this;
	}

	Vector3 operator * (float f) const {
		return Vector3(X * f, Y * f, Z * f);
	}

	Vector3 operator + (const Vector3& v) const {
		return Vector3(X + v.X, Y + v.Y, Z + v.Z);
	}

	Vector3 operator - (const Vector3& v) const {
		return Vector3(X - v.X, Y - v.Y, Z - v.Z);
	}

	void Normalize() {
		float length = sqrt(X * X + Y * Y + Z * Z);
		if (length != 0) {
			X = X / length;
			Y = Y / length;
			Z = Z / length;
		}
	}

	Vector3& NormalizeInline() {
		Normalize();
		return *this;
	}

	bool IsNull() {
		return X == 0 && Y == 0 && Z == 0;
	}
};

template<typename T>
struct Vector4 {
	T X;
	T Y;
	T W;
	T H;

	Vector4() {}

	Vector4(T x, T y, T w, T h)
		: X(x), Y(y), W(w), H(h) {}

	// unary operators
	Vector4& operator + () const {
		return *this;
	}

	Vector4& operator - () const {
		return Vector4(-X, -Y, -W, -H);
	}

	Vector4& operator = (const Vector4& v) {
		X = v.X;
		Y = v.Y;
		W = v.W;
		H = v.H;
		return *this;
	}

	Vector4& operator += (const Vector4& v) {
		X += v.X;
		Y += v.Y;
		W += v.W;
		H += v.H;
		return *this;
	}

	Vector4& operator -= (const Vector4& v) {
		X -= v.X;
		Y -= v.Y;
		W -= v.W;
		H -= v.H;
		return *this;
	}

	Vector4& operator *= (float f) {
		X *= f;
		Y *= f;
		W *= f;
		H *= f;
		return *this;
	}

	Vector4& operator /= (float f) {
		float fInv = 1.0f / f;
		X *= fInv;
		Y *= fInv;
		W *= fInv;
		H *= fInv;
		return *this;
	}

	Vector4 operator * (float f) const {
		return Vector3(X * f, Y * f, W * f, H * f);
	}

	Vector4 operator + (const Vector4& v) const {
		return Vector3(X + v.X, Y + v.Y, W + v.W, H + v.H);
	}

	Vector4 operator - (const Vector4& v) const {
		return Vector3(X - v.X, Y - v.Y, W - v.W, H - v.H);
	}

	void Normalize() {
		float length = sqrt(X * X + Y * Y + W * W + H * H);
		if (length != 0) {
			X = X / length;
			Y = Y / length;
			W = W / length;
			H = H / length;
		}
	}

	Vector4& NormalizeInline() {
		Normalize();
		return *this;
	}

	bool IsNull() {
		return X == 0 && Y == 0 && W == 0 && H == 0;
	}
};
#pragma endregion

struct RGBA {
	BYTE R;
	BYTE G;
	BYTE B;
	BYTE A;

	RGBA() {}

	RGBA(BYTE _r, BYTE _g, BYTE _b, BYTE _a) {
		R = _r;
		G = _g;
		B = _b;
		A = _a;
	}
};

class Color {
public:
	RGBA Color_;

	Color() {}

	Color(BYTE r, BYTE g, BYTE b, BYTE a = 255)
		: Color_(RGBA(r, g, b, a)) {
	}

	Color(unsigned int hex) {
		Color_.R = (hex >> 24) & 0xFF;
		Color_.G = (hex >> 16) & 0xFF;
		Color_.B = (hex >> 8) & 0xFF;
		Color_.A = hex & 0xFF;

		if (Color_.A == 0) {
			Color_.A = 255;
		}
	}

	float* GetFloatPtr() {
		static float ptr[4];
		ptr[0] = float(Color_.R / 255.f);
		ptr[1] = float(Color_.G / 255.f);
		ptr[2] = float(Color_.B / 255.f);
		ptr[3] = float(Color_.A / 255.f);
		return ptr;
	}

	Color WithOpacity(BYTE opacity) {
		static Color col;
		col = *this;
		col.Color_.A = opacity;
		return col;
	}
};

struct FractionSorter {
	const char* pTag;
	float fFraction;
	int iTagPriority;

	FractionSorter() {
		fFraction = 0.0f;
	}

	FractionSorter(const char* tag, float fraction, int pri = 0)
		: pTag(tag), fFraction(fraction), iTagPriority(pri) {
	}
};

struct Priority {
	DWORD dwPriority;
	const char* pBestTag;
	bool bWallbangable;
	bool bVisible;
	bool bPrioritized;
	bool bValid;
};

template<typename Type>
struct ScrollStruct {
	const char* pName;
	Type Result;
};

// game
typedef void(*handleCallback)(int arg, int* handle, handleCall_t type);

struct handle_s {
	int arg;
	handleCallback function;
	handleCall_t type;
	int* handle;
	clock_t interval;
	clock_t time;
	clock_t startTime;
};

struct UIContext {
	char _0x0000[0xC];
	int iCurrentFrame;
	char _0x0010[0x18];
	float fFramesPerSecond;
};

struct RectDef {
	D3DXVECTOR4 Position;
	int iHorzAlign;
	int iVertAlign;
};

struct Material {
	const char* pName;
};

struct Font {
	const char* pFontName;
	int iPixelHeight;
	int pGlyphCount;
	Material* pMaterial;
	Material* pGlowMaterial;
	void* pGlyph;
};

struct RefDef {
	Vector2<int> vScale;
	char _0x0008[20];
	Vector2<float> vFOV;
	BYTE _0x0024[8];
	float fTotalFov;
	Vector3<float> vOrigin;
	char _0x003C[4];
	Vector3<float> vViewAxis[3];
};

struct ClientInfo {
	int iValid;
	int iValid2;
	BYTE _0x0008[4];
	char szName[32];
	int iTeam;
	BYTE _0x0030[80];
	char szClantag[8];
	BYTE _0x0088[4];
	int iRealIsAlive;
	BYTE _0x0090[0x50];
	BYTE bValid3;
	BYTE _0x00E1[0x573];
	int iFakeIsAlive;
	BYTE _0x0658[432];
};

struct Snapshot {
	int iSnapFlags;
	int iPing;
	int iServerTime;
	int iPhysicsTime;
	int iServerTime2;
};

struct cg {
	BYTE _0x0000[0x24];
	Snapshot* pSnap;
	Snapshot* pNextsnap;
	BYTE _0x002C[0x8C];
	Vector3<float> vOrigin;
	BYTE _0x00C4[364];
	int iClientNumber;
	BYTE _0x0234[0x3C];
	float fZoomState;
	BYTE _0x00274[0x54];
	int iHealth;
	char _0x02CC[4];
	int iMaxHealth;
	BYTE _0x002CC[0x4D5BC - 8];
	RefDef Refdef;
	BYTE _0x4D8EC[0x1C1A4];
	ClientInfo ClientInfo[18];

	DWORD GetPlayerState() {
		return (DWORD)this + 0x480A8;
	}
};

struct ServerInfo {
	BYTE _0x0000[7];
	Vector2<int> vScaling;
	BYTE _0x0010[0x20];
	char szGametype[0x20];
	char szHostName[0x100];
	int iMaxClients;
	int iPrivateClients;
	char szMapname[0x40];
	BYTE _0x0198[0x57D0];
};

struct XModel {
	char* pName;
	BYTE bNumBones;
	BYTE bNumRootBones;
	BYTE bNumSurfs;
	BYTE bLodRampType;
	unsigned short* pBoneNames;
};

struct DSkelPartBits {
	int anim[5];
	int control[5];
	int skel[5];
};

struct DSkel {
	DSkelPartBits PartBits;
	int iTimestamp;
	DWORD pAnimMat;
};

struct DObj_s {
	DWORD pXAnimTree;
	unsigned short sDuplicateParts;
	unsigned short sEntNum;
	BYTE bDuplicatePartsSize;
	BYTE bNumModels;
	BYTE bNumBones;
	DWORD dwIgnoreCollision;
	volatile int Locked;
	DSkel Skel;
	float fRadius;
	DWORD dwHidePartBits[5];
	BYTE bLocalClientIndex;
	BYTE bFlags;
	BYTE bNumRootAdjustMats;
	char* pIkState;
	XModel**ppModels;
};

struct DObjAnimMat {
	Vector4<float> vQuat;
	Vector3<float> vTranslation;
	float fTranslationWeight;
};

struct Entity {
	BYTE _0x0000[3];
	BYTE bType;
	BYTE _0x0004[40];
	Vector3<float> vOrigin;
	BYTE _0x0038[280];
	int iIsAlive2;
	BYTE _0x0154;
	BYTE bIsAiming;
	BYTE _0x0156;
	BYTE bStatus;
	BYTE _0x0158[84];
	int iTeamDog;
	int iWeaponIndex;
	int iWeaponIndexSecondary;
	BYTE _0x01B4[0x18];
	DWORD dwClientNum;
	int iFlags;
	BYTE _0x01D8[0x70];
	short iTeamRCXD_Dog_Heli;
	short iTeamTurret;
	BYTE _0x024C[92];
	short Type;
	BYTE _0x02AA[13];
	BYTE bWeaponNum;
	BYTE _0x02B8[180];
	int iIsAlive;
	BYTE _0x036D[4];

	Vector3<float> GetNextPredictedPosition() {
		return Vector3<float>(
			*(float*)((DWORD)this + 0x168),
			*(float*)((DWORD)this + 0x16C),
			*(float*)((DWORD)this + 0x170)
		);
	}

	Vector3<float> GetPreviousPredictedPosition() {
		return Vector3<float>(
			*(float*)((DWORD)this + 0x1E8),
			*(float*)((DWORD)this + 0x1EC),
			*(float*)((DWORD)this + 0x1F0)
		);
	}
};

struct WeaponDef {
	const char *szOverlayName;
	XModel **gunXModel;
	XModel *handXModel;
	const char *szModeName;
	unsigned __int16 *notetrackSoundMapKeys;
	unsigned __int16 *notetrackSoundMapValues;
	int playerAnimType;
	weapType_t weapType;
	weapClass_t weapClass;
	PenetrateType penetrateType;
	ImpactType impactType;
	weapInventoryType_t inventoryType;
	weapFireType_t fireType;
	weapClipType_t clipType;
	barrelType_t barrelType;
	int itemIndex;
	const char *parentWeaponName;
	int iJamFireTime;
	int overheatWeapon;
	float overheatRate;
	float cooldownRate;
	float overheatEndVal;
	bool coolWhileFiring;
	bool fuelTankWeapon;
	int iTankLifeTime;
	OffhandClass offhandClass;
	OffhandSlot offhandSlot;
	weapStance_t stance;
	DWORD *viewFlashEffect;
	DWORD *worldFlashEffect;
	DWORD *barrelCooldownEffect;
	int barrelCooldownMinCount;
	Vector3<float> vViewFlashOffset;
	Vector3<float> vWorldFlashOffset;
	const char *pickupSound;
	const char *pickupSoundPlayer;
	const char *ammoPickupSound;
	const char *ammoPickupSoundPlayer;
	const char *projectileSound;
	const char *pullbackSound;
	const char *pullbackSoundPlayer;
	const char *fireSound;
	const char *fireSoundPlayer;
	const char *fireLoopSound;
	const char *fireLoopSoundPlayer;
	const char *fireLoopEndSound;
	const char *fireLoopEndSoundPlayer;
	const char *fireStartSound;
	const char *fireStopSound;
	const char *fireKillcamSound;
	const char *fireStartSoundPlayer;
	const char *fireStopSoundPlayer;
	const char *fireKillcamSoundPlayer;
	const char *fireLastSound;
	const char *fireLastSoundPlayer;
	const char *emptyFireSound;
	const char *emptyFireSoundPlayer;
	const char *crackSound;
	const char *whizbySound;
	const char *meleeSwipeSound;
	const char *meleeSwipeSoundPlayer;
	const char *meleeHitSound;
	const char *meleeMissSound;
	const char *rechamberSound;
	const char *rechamberSoundPlayer;
	const char *reloadSound;
	const char *reloadSoundPlayer;
	const char *reloadEmptySound;
	const char *reloadEmptySoundPlayer;
	const char *reloadStartSound;
	const char *reloadStartSoundPlayer;
	const char *reloadEndSound;
	const char *reloadEndSoundPlayer;
	const char *rotateLoopSound;
	const char *rotateLoopSoundPlayer;
	const char *rotateStopSound;
	const char *rotateStopSoundPlayer;
	const char *deploySound;
	const char *deploySoundPlayer;
	const char *finishDeploySound;
	const char *finishDeploySoundPlayer;
	const char *breakdownSound;
	const char *breakdownSoundPlayer;
	const char *finishBreakdownSound;
	const char *finishBreakdownSoundPlayer;
	const char *detonateSound;
	const char *detonateSoundPlayer;
	const char *nightVisionWearSound;
	const char *nightVisionWearSoundPlayer;
	const char *nightVisionRemoveSound;
	const char *nightVisionRemoveSoundPlayer;
	const char *altSwitchSound;
	const char *altSwitchSoundPlayer;
	const char *raiseSound;
	const char *raiseSoundPlayer;
	const char *firstRaiseSound;
	const char *firstRaiseSoundPlayer;
	const char *adsRaiseSoundPlayer;
	const char *adsLowerSoundPlayer;
	const char *putawaySound;
	const char *putawaySoundPlayer;
	const char *overheatSound;
	const char *overheatSoundPlayer;
	const char *adsZoomSound;
	const char *shellCasing;
	const char *shellCasingPlayer;
	const char **bounceSound;
	const char *standMountedWeapdef;
	const char *crouchMountedWeapdef;
	const char *proneMountedWeapdef;
	int standMountedIndex;
	int crouchMountedIndex;
	int proneMountedIndex;
	DWORD *viewShellEjectEffect;
	DWORD *worldShellEjectEffect;
	DWORD *viewLastShotEjectEffect;
	DWORD *worldLastShotEjectEffect;
	Vector3<float> vViewShellEjectOffset;
	Vector3<float> vWorldShellEjectOffset;
	Vector3<float> vViewShellEjectRotation;
	Vector3<float> vWorldShellEjectRotation;
	Material *reticleCenter;
	Material *reticleSide;
	int iReticleCenterSize;
	int iReticleSideSize;
	int iReticleMinOfs;
	activeReticleType_t activeReticleType;
	Vector3<float> vStandMove;
	Vector3<float> vStandRot;
	Vector3<float> vDuckedOfs;
	Vector3<float> vDuckedMove;
	Vector3<float> vDuckedSprintOfs;
	Vector3<float> vDuckedSprintRot;
	Vector2<float> vDuckedSprintBob;
	float fDuckedSprintCycleScale;
	Vector3<float> vSprintOfs;
	Vector3<float> vSprintRot;
	Vector2<float> vSprintBob;
	float fSprintCycleScale;
	Vector3<float> vLowReadyOfs;
	Vector3<float> vLowReadyRot;
	Vector3<float> vRideOfs;
	Vector3<float> vRideRot;
	Vector3<float> vDtpOfs;
	Vector3<float> vDtpRot;
	Vector2<float> vDtpBob;
	float fDtpCycleScale;
	Vector3<float> vMantleOfs;
	Vector3<float> vMantleRot;
	Vector3<float> vSlideOfs;
	Vector3<float> vSlideRot;
	Vector3<float> vDuckedRot;
	Vector3<float> vProneOfs;
	Vector3<float> vProneMove;
	Vector3<float> vProneRot;
	Vector3<float> vStrafeMove;
	Vector3<float> vStrafeRot;
	float fPosMoveRate;
	float fPosProneMoveRate;
	float fStandMoveMinSpeed;
	float fDuckedMoveMinSpeed;
	float fProneMoveMinSpeed;
	float fPosRotRate;
	float fPosProneRotRate;
	float fStandRotMinSpeed;
	float fDuckedRotMinSpeed;
	float fProneRotMinSpeed;
	XModel **worldModel;
	XModel *worldClipModel;
	XModel *rocketModel;
	XModel *mountedModel;
	XModel *additionalMeleeModel;
	Material *fireTypeIcon;
	Material *pKillIcon;
	weaponIconRatioType_t hudIconRatio;
	Material *indicatorIcon;
	weaponIconRatioType_t indicatorIconRatio;
	Material *ammoCounterIcon;
};

struct UserCommand {
	int iServerTime;
	int iButtons;
	BYTE _0x0008[4];
	Vector3<int> vViewAngles;
	int iWeaponNum;
	char _0x001C[8];
	char bForwardmove;
	char bRightmove;
	BYTE _0x0026[0x16];
};

struct ClientActive {
	BYTE _0x0000[152];
	Vector3<float> vOrigin;
	BYTE _0x00A4[100];
	Vector3<float> vBaseAngles;
	BYTE _0x00114[404];
	int iHealth;
	BYTE _0x02AC[0x27F8];
	DWORD dwServerTimeSeed;
	BYTE _0x2AA8[0x1E4];
	Vector3<float> vViewAngles;
	BYTE _0x2C98[0x40010];
	UserCommand UserCommands[128];
	DWORD dwCommandNumber;

	UserCommand* GetCommand(int cmdNum) {
		return &UserCommands[cmdNum & 0x7F];
	}
};

struct BulletFireParams {
	int iWeaponEntIndex;
	int iIgnoreEntIndex;
	float fDamageMultiplier;
	int iMethodOfDeath;
	Vector3<float> vOrigStart;
	Vector3<float> vStart;
	Vector3<float> vEnd;
	Vector3<float> vDirection;
};

struct Trace {
	char _0x0000[0x10];
	float fFraction;
	char Buf04[0x60];
};

struct BulletTraceResults {
	Trace Trace;
	int iHitEnt;
	Vector3<float> vHitPos;
	bool bIgnoreHitEnt;
	int iSurfaceType;
};

struct _XenonUserData {
	int iSignInState;
	char szName[0x20];
	char unk1[0x4];
	XUID Xuid;
	char szXuidString[0x10];
	char unk2[0x28];
};

struct CRadarHud {
	Vector2<float> vPosition;
	Vector2<float> vScaling;
	char _0x000A[4];//0x0010
};

struct TraceCheckCount {
	unsigned short global;
	unsigned short unk;
	DWORD* partitions;
	DWORD* brushes;
};

struct TraceThreadInfo {
	TraceCheckCount checkcount;
	void* box_brush;
	void* box_model;
	void** geoms;
};