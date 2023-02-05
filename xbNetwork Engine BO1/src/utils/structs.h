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
	Vector2<float> vPosition;
	Vector2<float> vScale;
	int iHorzAlign;
	int iVertAlign;
	int unk1;
	int unk2;
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
	float fFOV;
	Vector3<float> vOrigin;
	char _0x003C[4];
	Vector3<float> vViewAxis[3];
	int iServerTime;
};

struct ClientInfo {
	int iValid;
	int iValid2;
	BYTE _0x0008[4];
	char szName[32];
	int iTeam;
	BYTE _0x0030[52];
	int iIsAlive;
	BYTE _0x0068[0x3E8];
	Vector3<float> vAngles;
	BYTE _0x045C[0x174];
};

struct Snapshot {
	int iSnapFlags;
	int iPing;
	int iServerTime;
	int iPhysicsTime;
	int iServerTime2;
};

struct cg {
	int iClientNumber;
	int iLocalClientNumber;
	BYTE _0x0008[0x20];
	Snapshot* pSnap;
	Snapshot* pNextsnap;
	BYTE _0x0030[0x84];
	Vector3<float> vOrigin;
	BYTE _0x00C0[268616];
	RefDef Refdef;
	BYTE _0x41A64[114136];
	DWORD dwSway;
	BYTE _0x5D844[692];
	ClientInfo ClientInfo[18];
	BYTE _0x6666C[19092];

	float GetZoomState() {
		return *(float*)((DWORD)this + 0x01F8);
	}

	int GetPlayerState() {
		return ((DWORD)this + 0x3EF9C);
	}

	int GetHealth() {
		return *(int*)((DWORD)this + 0x0254);
	}

	int GetMaxHealth() {
		return *(int*)((DWORD)this + 0x025C);
	}
};

struct ServerInfo {
	BYTE _0x0000[7];
	Vector2<int> vScale;
	BYTE _0x0010[32];
	CHAR szGametype[32];
	CHAR szHostName[256];
	int iMaxClients;
	int iPrivateClients;
	char szMapname[0x40];
	BYTE _0x0198[12600];
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
	char* pIkState;
	XModel**ppModels;
};

struct DObjAnimMat {
	Vector4<float> vQuat;
	Vector3<float> vTranslation;
	float fTranslationWeight;
};

struct Entity {
	BYTE _0x0000[28];
	int iGodmodeCheck;
	BYTE _0x0020[16];
	Vector3<float> vOrigin;
	BYTE _0x003C[301];
	BYTE bState1; // 2 = sprinting || 8 = aiming
	BYTE placeholder; //0x16A not actually type just a place holder
	BYTE bState2; // 0x40 = shooting || 0x04 or 0x06 or 0x44 or 0x46 = crouched || 0x0A or 0x4A or 0x8 or 0x48 = prone
	BYTE _0x016C[112];
	int iClientNumber;
	int _0x01E0;
	BYTE _0x01E4[130];
	BYTE bIsAlive;
	BYTE _0x0267[0x2A4 - 0x267];
	DWORD dwWeaponIndex;
	BYTE _0x02A8[0x318 - 0x2A8];
	int _0x0318;
	
	Vector3<float> GetPreviousPredictedPosition() {
		return *(Vector3<float>*)((DWORD)this + 0x17C);
	}

	Vector3<float> GetNextPredictedPosition() {
		return *(Vector3<float>*)((DWORD)this + 0x1F4);
	}

	int GetFlags() {
		return *(int*)((DWORD)this + 0x168);
	}

	short GetType() {
		return *(short*)((DWORD)this + 0x29A);
	}

	int GetTeam() {
		return *(int*)((DWORD)this + 0x238);
	}
};

struct WeaponDef {
	const char *szOverlayName;
	XModel **gunXModel;
	XModel *handXModel;
	const char *szModeName;

	DWORD GetKillIconType() {
		return *(DWORD*)((DWORD)this + 0x57C);
	}

	Material* GetKillIcon() {
		return (Material*)*(DWORD*)((DWORD)this + 0x578);
	}
};

#pragma pack(push, 1)
struct UserCommand {
	int iServerTime;
	int iButtons;
	BYTE _0x0008[4];
	Vector3<int> vViewAngles;
	short sWeaponID;
	int unk;
	signed char bForwardmove;
	signed char bRightmove;
	BYTE _0x0026[0x14];
};
#pragma pack(pop)

struct ClientActive {
	BYTE _0x0000[76];//0x00
	Vector3<float> vOrigin;
	BYTE _0x0058[84];//0x58
	Vector3<float> vBaseAngles;
	BYTE _0x00B8[308];//0xB8
	int iHealth;
	BYTE _0x01F0[9808];//0x1F0
	Vector3<float> vViewAngles;
	BYTE _0x284C[262160];//0x284C
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