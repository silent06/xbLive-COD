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

	Vector2& operator + () const {
		return *this;
	}

	Vector2& operator - () const {
		return Vector2(-X, -Y);
	}

	Vector2& operator = (const Vector2& v) {
		X = v.X;
		Y = v.Y;
		return *this;
	}

	Vector2& operator += (const Vector2& v) {
		X += v.X;
		Y += v.Y;
		return *this;
	}

	Vector2& operator -= (const Vector2& v) {
		X -= v.X;
		Y -= v.Y;
		return *this;
	}

	Vector2& operator *= (float f) {
		X *= f;
		Y *= f;
		return *this;
	}

	Vector2& operator /= (float f) {
		float fInv = 1.0f / f;
		X *= fInv;
		Y *= fInv;
		return *this;
	}

	Vector2 operator * (float f) const {
		return Vector2(X * f, Y * f);
	}

	Vector2 operator + (const Vector2& v) const {
		return Vector2(X + v.X, Y + v.Y);
	}

	Vector2 operator - (const Vector2& v) const {
		return Vector2(X - v.X, Y - v.Y);
	}

	void Normalize() {
		float length = sqrt(X * X + Y * Y);
		if (length != 0) {
			X = X / length;
			Y = Y / length;
		}
	}

	Vector2& NormalizeInline() {
		Normalize();
		return *this;
	}

	bool IsNull() {
		return X == 0 && Y == 0;
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
	char _0x0010[0x18];
	float fFramesPerSecond;
};

struct RectDef {
	Vector2<float> vPosition;
	Vector2<float> vScale;
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
	BYTE _0x0008[0x10];
	Vector2<float> vFOV;
	float fTotalFOV;
	Vector3<float> vOrigin;
	BYTE _0x0030[4];
	Vector3<float> vViewAxis[3];
};

struct ClientInfo {
	char szName[0x20];
	int iTeam;
	BYTE _0x0024[952];
	int iIsAlive3;
	BYTE _0x03E0[152];
	int iIsAlive2;
	BYTE _0x047C[20];
	int iStance;
	BYTE _0x0494[200];
};

struct Snapshot {
	DWORD dwUnk;
	DWORD dwPing;
	DWORD dwPhysicsTime;
	DWORD dwServerTime;
};

struct cg {
	BYTE _0x0000[0x20];
	Snapshot* pSnap;
	Snapshot* pNextSnap;
	BYTE _0x0028[0x58 - 0x28];
	Vector3<float> vOrigin;
	BYTE _0x0064[204];
	int iClientNumber;
	BYTE _0x0134[104];
	int iHealth;
	char padding08[0x4];
	int iMaxHealth;
	BYTE _0x01A0[342880];
	RefDef Refdef;
	BYTE _0x53D60[588256];
	ClientInfo ClientInfo[18];
	BYTE _0xE97B8[15432];

	int GetPlayerState() {
		return (int)((DWORD)this + 0x50054);
	}
};

struct ServerInfo {
	Vector2<int> vPosition;
	Vector2<int> vScale;
	BYTE _0x0010[32];//0x10
	BYTE Gametype[32]; // 0x0030
	char szHostName[0x20];
	char _0x0064[0xE0];
	int iMaxClients;
	int iPrivateClients;
	char szMapname[64]; // 0x0158
	BYTE _0x0198[17712];//0x198
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

struct Entity { // centity
	BYTE _0x0000[40];//0x00
	Vector3<float> vOrigin;
	BYTE _0x0034[157];//0x34
	BYTE bIsAiming;
	BYTE bIsShooting;
	BYTE bStance;
	int _0x00D4;//0xD4
	BYTE _0x00D8[32];//0xD8
	EntityType iType;
	BYTE _0x00FC[0x20C - 0xFC];//0xFC
	int iClientNumber;
	BYTE _0x0210[0x244 - 0x210]; // 0x210
	int iWeaponIndex; //0x244
	BYTE _0x0248[0x2AC - 0x248]; //0x248
	int iIsAlive;//0x2AC
};

struct WeaponDef {
	const char* pWeaponName;
	char _0x0004[4];
	const char* pOverlayName;
	char _0x000C[0x610 - 0xC];
	Material* pKillIcon;
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
	char _0x0014[0x16 - 0x14];
	char bForwardmove;
	char bRightmove;
	char _0x0018[0x2C - 0x18]; // 0x18
};

struct ClientActive {
	BYTE _0x0000[120];//0x00
	Vector3<float> vOrigin;
	BYTE _0x0084[32];//0x84
	Vector3<float> vBaseAngles;
	BYTE _0x00B0[220];//0xB0
	int iHealth;//0x18C
	BYTE _0x0190[157936];//0x190
	Vector3<float> vViewAngles;
	BYTE _0x26A8C[0x66AA0 - 0x26A8C];//0x26A8C
	UserCommand UserCommands[128];
	int iCurCmd;//0x680A0

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
	char _0x0000[0x10];
	float fFraction;
	char _0x0014[0x64];
};