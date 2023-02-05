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

	Color WithOpacity(int opacity) {
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

struct UIContext {
	char _0x0000[0x2C];
	float fFramesPerSecond;
};

struct handle_s {
	int arg;
	handleCallback function;
	handleCall_t type;
	int* handle;
	clock_t interval;
	clock_t time;
	clock_t startTime;
};

struct RectDef {
	Vector2<float> vPosition;
	Vector2<float> vScale;
	BYTE bAlignLeft;
	BYTE bAlignRight;
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
	char _0x0000[4];
	Vector2<int> vScale;
	Vector2<float> vFOV;
	Vector3<float> vOrigin;
	Vector3<float> vViewAxis[3];
};

struct ClientInfo {
	char _0x0000[4];
	int iTeam;
	BYTE _0x0008[56];
	char szName[0x20];
	BYTE _0x0060[0x90];
};

struct Snapshot {
	BYTE _0x0000[0x3864];//0x0000
	DWORD dwPing;//0x3864 
};

struct TeamCheck {
	int iTeam;//0x0000
	BYTE _0x0004[0x10 - 0x04];//0x0004
	BYTE bValidCheck;//0x10
	BYTE _0x0011[0x59C - 0x11];//0x11
};

struct ClientName {
	char szName[32];//0x0000
	BYTE _0x0020[0x74 - 0x20];//0x0020
};

struct cg {
	int iCommandtime;
	BYTE _0x0004[24];
	Vector3<float> vOrigin;
	Vector3<float> vVelocity;
	BYTE _0x0034[328];
	int iClientNumber;
	BYTE _0x0180[0x1C8 - 0x180];
	int iHealth;
	DWORD PadFix;
	int iMaxHealth;
	BYTE _0x01CC[0x2FD8 - 0x1CC - 4];
	Snapshot* pSnap;
	BYTE _0x2FDC[0x6BAF0 - 0x2FDC];
	ClientInfo ClientInfo[18];
	BYTE _0x6CBD0[2412];
	RefDef Refdef;
	BYTE Padding[0xB943C - 0x6D584];
	TeamCheck ClientTeam[12];
	BYTE _0xBD78C[0xC5E24 - 0xBD78C];
	ClientName ClientName[12];
};

struct ServerInfo {
	Vector2<int> vPosition;
	Vector2<int> vScale;
	BYTE _0x0010[20];
	char szGametype[0x20];
	char szHostName[260];
	int iMaxClients;
	int iPrivateClients;
	char szMapname[64];
	BYTE _0x0190[0x6D40];
};

struct DSkelPartBits {
	int anim[6];
	int control[6];
	int worldCtrl[6];
	int skel[6];
};

/* 2044 */
struct DSkel {
	DSkelPartBits partBits;
	int timeStamp;
	DWORD *mat;
};

struct XModel {
	const char *pName;
	char bNumBones;
	char numRootBones;
	char numsurfs;
	char numReactiveMotionParts;
	float scale;
	unsigned int noScalePartBits[6];
	unsigned short *pBoneNames;
};

struct DObj_s {
	char _0x0000[0x10];
	DWORD locked;
	char _0x0014[0x84];
	XModel** ppModels;

	BYTE GetBoneCount() {
		return *(BYTE*)((DWORD)this + 0xA);
	}

	BYTE GetModelCount() {
		return *(BYTE*)((DWORD)this + 0x9);
	}
};

struct EntityEvent {
	int iEventType;//0x00
	int iEventParam;//0x04
};

struct Entity { // centity
	char _0x0000[0x2];
	BYTE bIsAlive1;
	BYTE bIsAlive2;
	BYTE _0x0004[0x10];
	Vector3<float> vOrigin;
	BYTE _0x0020[0x5D - 0x20];
	BYTE bIsAiming;
	BYTE bIsShooting;
	BYTE bStance;
	BYTE _0x0060[0xC];
	Vector3<float> vLastOrigin;
	BYTE _0x0078[0xC8 - 0x78];
	EntityType Type;
	DWORD dwStatus;
	BYTE _0x00D0[0xC];
	Vector3<float> vNewOrigin;
	BYTE _0x00E8[0x100 - 0xE8];
	Vector3<float> vAngles;
	BYTE _0x010C[0x154 - 0x10C];
	int iClientNumber;
	DWORD dwUnkShit;
	int iSolid;
	DWORD dwEventParm;
	int iEventSequence;
	EntityEvent Events[4];
	int iWeaponIndex;
	BYTE _0x018C[0x1C7 - 0x18C];
	BYTE bIsAlive3;
	BYTE _0x01C8[0x1EC - 0x1C8];

	int GetDogTeam() {
		return *(int*)((DWORD)this + 0x164);
	}
};

struct WeaponDef {
	const char* pWeaponName;
	char _0x0004[0x80];
	Material* pKillIcon;
	char _0x0088[0x4A0];
	DWORD dwKillIconType;
};

struct WeaponVariant {
	char _0x0008[8];
	WeaponDef* pWeaponDef;
};

struct UserCommand {
	int iCommandTime;
	DWORD dwButton;
	Vector3<int> vViewAngles;
	int iWeapon;
	int iOffHand;
	char bForwardmove;
	char bRightmove;
	unsigned short AirburstMarkDistance;
	unsigned short MeleeChargeEntity;
	char bMeleeChargeDist;
	char bSelectedLoc[2];
	char bSelectedLocAngle;
	char remoteControlAngles[2];
	char remoteControlMove[3];
	unsigned int sightedClientsMask;
	unsigned __int16 spawnTraceEntIndex;
	unsigned int sightedSpawnsMask;
	unsigned int partialSightedSpawnsMask;
};

struct ClientActive {
	BYTE _0x0000[156];
	Vector3<float> vOrigin;
	Vector3<float> vVelocity;
	BYTE _0x00B4[48];
	Vector3<float> vBaseAngles;
	BYTE _0x00F0[12768];
	Vector3<float> vViewAngles;
	UserCommand UserCommands[128];
	int iCurCmd;
	BYTE _0x50E0[35992];

	UserCommand* GetCommand(int cmdNum) {
		return &UserCommands[cmdNum & 0x7F];
	}
};

struct BulletFireParams {
	int iMaxEntityNumber;
	int iIgnoreEntIndex;
	float fDamageMultiplier;
	int iMethodOfDeath;
	int iUnk;
	Vector3<float> vOriginalStart;
	Vector3<float> vStart;
	Vector3<float> vEnd;
	Vector3<float> vDirection;
};

struct Trace {
	float fFraction;//0x00
	Vector3<float> vNormal;//0x04
	BYTE _0x0010[0x20];//0x10
};