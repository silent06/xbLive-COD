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
	char _0x0010[0x1C];
	float fFramesPerSecond;
};

struct RectDef {
	Vector2<float> vPosition;
	Vector2<float> vScale;
	int iHorzAlign;
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
	Vector2<float> vFOV;
	Vector3<float> vOrigin;
	Vector3<float> vViewAxis[3];
};

struct ClientInfo {
	char szName[0x10];
	char _0x0010[0x10];
	int iTeam;
	char _0x0024[0x2C];
	BYTE bValidCheck;
	char _0x0051[0x42F];
	int iIsAlive;
	char _0x0484[0xC];
	int iStance;
	char _0x0494[0x5C];
	int iIsAlive2;
	char _0x04F4[0x50];

	const char* GetPrimaryWeaponModel() {
		return (char*)((DWORD)this + 0xD8);
	}

	const char* GetSecondaryWeaponModel() {
		return (char*)((DWORD)this + 0x117);
	}
};

struct Snapshot {
	DWORD dwServertime;
	char _0x0004[0x3180];
	DWORD dwPing;
	DWORD dwServertime2;
};

struct cg {
	int iCommandtime;
	char _0x0004[0x8];
	int iFlags;
	char _0x000A[0xC];
	Vector3<float> vOrigin;
	char _0x0028[0x38];
	Vector3<float> vSpawnAngles;
	char _0x006C[0x45];
	BYTE bMantling;
	char _0x00B2;
	BYTE bStance;
	char _0x00B4[0x50];
	int iClientNumber;
	char _0x0108[0x48];
	int iHealth;
	char padding08[0x4];
	int iMaxHealth;
	char _0x015C[0x164];
	float fZoomState;
	float fAimSpreadScale;
	char _0x02C8[0x3100];
	Snapshot* pSnap;
	Snapshot* pNextSnap;
	BYTE _0x33D0[0x6785E];
	RefDef Refdef;
	char _0x6AC6E[0x8C21A];
	ClientInfo ClientInfo[18];
	char _0xFCD50[0x10B0];
};

struct ServerInfo {
	Vector2<int> vPosition;
	Vector2<int> vScale;
	char _0x0010[0x10];
	char szGametype[0x20];
	char szHostName[0x20];
	char _0x0064[0xE4];
	int iMaxClients;
	int iPrivateClients;
	char szMapname[0x40];
};

struct XModel {
	char* pName;
	BYTE bNumBones;
};

struct DObj_s {
	char _0x0000[0x10];
	long locked;
	char _0x0014[0x84];
	XModel** ppModels;

	BYTE GetBoneCount() {
		return *(BYTE*)((DWORD)this + 0xA);
	}

	BYTE GetModelCount() {
		return *(BYTE*)((DWORD)this + 0x9);
	}
};

struct Entity {
	char _0x0000[0x2];
	char bAlive;
	char _0x0003[0x15];
	Vector3<float> vOrigin;
	char _0x0024[61];
	BYTE bIsAiming;
	BYTE bIsShooting;
	BYTE bStance;
	char _0x0064[0x14];
	Vector3<float> vPreviousOrigin;
	char _0x0084[0x18];
	Vector3<float> vAngles;
	char _0x00A8[0x28];
	int iClientNumber;
	EntityType iType;
	char _0x00D8[0x1C];
	Vector3<float> vNewOrigin;
	char _0x0100[0x5A];
	short sDroppedWeaponNum;
	char _0x015C[0x24];
	int iAliveChecks[3];
	char _0x018C[0x10];
	short iWeaponIndex;
	short iSecondaryWeaponIndex;
	BYTE _0x01A0[2];//0x1A0
	BYTE isAlive2;//0x1A2
	BYTE _0x01A3;//0x1A3
	DWORD unk;//0x1A4
	BYTE _0x01A8[40];//0x1A8
	int iIsAlive2;
	BYTE _0x01D4[36];

	int GetSecondaryWeaponID() {
		return iSecondaryWeaponIndex;
	}

	Vector3<float> GetPreviousPredictedPosition() {
		return vPreviousOrigin;
	}

	Vector3<float> GetNextPredictedPosition() {
		return vNewOrigin;
	}
};

struct WeaponDef {
	const char* pWeaponName;
	char _0x0004[4];
	const char* pOverlayName;
	char _0x000C[120];
	Material* pKillIcon;
};

struct WeaponVariant {
	char _0x0008[8];
	WeaponDef* pWeaponDef;
};

struct UserCommand {
	int iCommandTime;
	DWORD dwButton;
	Vector3<int> vViewAngles;
	short sWeapon;
	short sOffHand;
	char unkBuf[2];
	signed char bForwardmove;
	signed char bRightmove;
	signed char bUnkMove;
	char _0x001C[0xB];
};

struct ClientActive {
	bool bUsingAds;
	BYTE _0x0001[0x7F];
	DWORD dwServerTime;
	char _0x0084[0x18];
	Vector3<float> vOrigin;
	char _0x00A8[0x38];
	Vector3<float> vBaseAngles;
	char _0x00EC[0x326C];
	Vector3<float> vViewAngles;
	UserCommand UserCommands[128];
	int iCurCmd;

	UserCommand* GetCommand(int cmdNum) {
		return &UserCommands[cmdNum & 0x7F];
	}
};

struct BulletFireParams {
	int iWeaponEntIndex;
	int iIgnoreEntIndex;
	float fDamageMultiplier;
	int iMethodOfDeath;
	Vector3<float> vOriginalStart;
	Vector3<float> vStart;
	Vector3<float> vEnd;
	Vector3<float> vDirection;
};

struct Trace {
	float fFraction;
	Vector3<float> vNormal;
	int iSurfaceFlags;
	int iContents;
	Material* pMaterial;
	TraceHitType HitType;
	unsigned short HitId;
	unsigned short ModelIndex;
	unsigned short PartName;
	unsigned short PartGroup;
	bool bAllsolid;
	bool bStartsolid;
	bool bWalkable;
	char _0x002B[5];
	Vector3<float> vEndPosition;
	char _0x003C[4];
	unsigned long ulMaterialType;
	char _0x0044[0x20];
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