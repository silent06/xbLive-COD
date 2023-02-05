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
	char _0x0000[0x20];
	Vector2<int> vResolution;
	char _0x0028[0x4];
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
	BYTE _0x0000[4];
	Vector2<WORD> vScale;
	BYTE _0x0008[8];
	Vector2<float> vFOV;
	Vector3<float> vOrigin;
	Vector3<float> vViewAxis[3];
	BYTE _0x0048[4];
	float fZoomProgress; 
	Vector3<float> vViewOrigin; 
};

struct ClientInfo {
	int iValid;
	int iTeam;
	BYTE _0x0008[3116];
};

struct ClientName {
	char szPlayerName[32];
	BYTE _0x0020[276];
};

struct ClientName2 {
	char szPlayerName[32];
	BYTE _0x0020[0x74 - 0x20];
};

struct Snapshot {
	BYTE _0x0000[0x3D4C];
	DWORD dwPing;
};

struct cg {
	BYTE bClientNumber;
	BYTE _0x0001[75];
	int iCommandtime;
	BYTE _0x0050[8];
	int iFlags;
	BYTE _0x005C[28];
	Vector3<float> vOrigin;
	Vector3<float> vVelocity;
	BYTE _0x0090[336];
	int iHealth;
	DWORD PadFix;
	int iMaxHealth;
	BYTE _0x01E4[0x1B030 - 0x1E4 - 8];
	ClientName ClientName[18];
	BYTE _0x1C5D8[0x377C0 - 0x1C5D8];
	RefDef Refdef;
	BYTE _0x3781C[0xA05A0 - 0x3781C];
	ClientInfo ClientInfo[18];
	BYTE _0xAE148[0xBBCE9 - 0xAE148];
	ClientName2 ClientName2[18];

	// CG_ProcessSnapshots: n < cgameGlob->latestSnapshotNum
	Snapshot* GetSnapshot() {
		return (Snapshot*)*(DWORD*)((DWORD)this + 0x3258);
	}

	Snapshot* GetNextShapshot() {
		return (Snapshot*)*(DWORD*)((DWORD)this + 0x325C);
	}
};

struct ServerInfo {
	BYTE _0x0000[36];
	char szGametype[0x20];
	char szHostName[260];
	int iMaxClients;
	int iPrivateClients;
	char szMapname[64];
	BYTE _0x0190[54100];
};

struct DObj_s {};

struct Entity { // centity
	BYTE _0x0000[20];
	Vector3<float> vOrigin;
	Vector3<float> vAngles;
	BYTE _0x002C[64];
	int iFlags;
	BYTE _0x0070[0xD8 - 0x70];
	WORD wClientNumber;
	BYTE _0x00DA[10];
	BYTE bType;
	BYTE _0x00E5[0x124 - 0xE5];
	int iWeaponIndex;
	BYTE _0x0128[0x1DB - 0x128];
	BYTE bAlive;
	BYTE _0x01DC[48];

	BYTE GetStatus() {
		return *(BYTE*)((DWORD)this + 0x6D);
	}
};

struct WeaponDef {
	const char* pWeaponName;
	char _0x0004[0x774];
	Material* pKillIcon; // 0x778 
	char _0x077C[0x8];
	DWORD dwKillIconType; // 0x784
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
	char _0x001E[0x22];
};

struct ClientActive {
	BYTE _0x0000[248];
	Vector3<float> vOrigin;
	BYTE _0x0104[12];
	Vector3<float> vBaseAngles;
	BYTE _0x011C[0x3568 - 0x11C];
	Vector3<float> vViewAngles;
	UserCommand UserCommands[128];
	int iCurCmd;
	BYTE _0x56F8[42120];

	UserCommand* GetCommand(int cmdNum) {
		return &UserCommands[cmdNum & 0x7F];
	}
};

struct BulletFireParams {
	short sWorldEntNum;
	short sIgnoreEntIndex;
	float fDamageMultiplier;
	int iMethodOfDeath;
	int iUnk;
	Vector3<float> vOriginalStart;
	Vector3<float> vStart;
	Vector3<float> vEnd;
	Vector3<float> vDirection;
};

struct Trace {
	float fFraction;
	Vector3<float> vNormal;
	BYTE _0x0010[0x20];
};