#pragma once

#define PI (3.14159265358979323846264338327950288f)
#define ANGLE2SHORT(x) ((int)((x) * 65536 / 360) & 65535)
#define SHORT2ANGLE(x) ((x)*(360.0 / 65536))

#define PRIORITY_SHOOTING_NOT_AIMING 70
#define PRIORITY_AIMING_NOT_SHOOTING 72
#define PRIORITY_AIMING_AND_SHOOTING 75
#define PRIORITY_SHIELD_SECONDARY 80
#define PRIORITY_CLOSEST_CLIENT 120
#define PRIORITY_AIMING_AT_ME 80
#define PRIORITY_AIMING_AT_ME_THE_MOST 90
#define PRIORITY_VISIBLE 150
#define PRIORITY_WALLBANGABLE 100

struct once_flag {
	bool bDone;
};

static void call_once(once_flag* flag, function<void()> func) {
	if (flag) {
		if (!flag->bDone) {
			if (func) {
				func();
			}

			flag->bDone = true;
		}
	}
}

class Invoke {
public:
	template<typename T>
	static T Call(DWORD dwAddress) { return ((T(*)())dwAddress)(); }

	template<typename T, typename P1>
	static T Call(DWORD dwAddress, P1 p1) { return ((T(*)(P1))dwAddress)(p1); }

	template<typename T, typename P1, typename P2>
	static T Call(DWORD dwAddress, P1 p1, P2 p2) { return ((T(*)(P1, P2))dwAddress)(p1, p2); }

	template<typename T, typename P1, typename P2, typename P3>
	static T Call(DWORD dwAddress, P1 p1, P2 p2, P3 p3) { return ((T(*)(P1, P2, P3))dwAddress)(p1, p2, p3); }

	template<typename T, typename P1, typename P2, typename P3, typename P4>
	static T Call(DWORD dwAddress, P1 p1, P2 p2, P3 p3, P4 p4) { return ((T(*)(P1, P2, P3, P4))dwAddress)(p1, p2, p3, p4); }

	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5>
	static T Call(DWORD dwAddress, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) { return ((T(*)(P1, P2, P3, P4, P5))dwAddress)(p1, p2, p3, p4, p5); }

	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	static T Call(DWORD dwAddress, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6) { return ((T(*)(P1, P2, P3, P4, P5, P6))dwAddress)(p1, p2, p3, p4, p5, p6); }

	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	static T Call(DWORD dwAddress, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7) { return ((T(*)(P1, P2, P3, P4, P5, P6, P7))dwAddress)(p1, p2, p3, p4, p5, p6, p7); }

	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	static T Call(DWORD dwAddress, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8) { return ((T(*)(P1, P2, P3, P4, P5, P6, P7, P8))dwAddress)(p1, p2, p3, p4, p5, p6, p7, p8); }

	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
	static T Call(DWORD dwAddress, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9) { return ((T(*)(P1, P2, P3, P4, P5, P6, P7, P8, P9))dwAddress)(p1, p2, p3, p4, p5, p6, p7, p8, p9); }

	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10>
	static T Call(DWORD dwAddress, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10) { return ((T(*)(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10))dwAddress)(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); }

	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11>
	static T Call(DWORD dwAddress, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11) { return ((T(*)(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11))dwAddress)(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); }

	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12>
	static T Call(DWORD dwAddress, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12) { return ((T(*)(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12))dwAddress)(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); }

	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13>
	static T Call(DWORD dwAddress, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12, P13 p13) { return ((T(*)(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13))dwAddress)(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); }
};

class Utilities {
public:
	handle_s m_hookEvents[0x100];
	VOID PatchInJump(PDWORD Address, DWORD Destination, BOOL Linked);
	DWORD ResolveFunction(PCHAR Module, DWORD Ordinal);
	void Split(const string& s, char c, vector<string>& v);
	vector<string> GetFilesInDirectory(string folder, string extension = "*.*");
	void EraseAllSubstrings(string& mainStr, string toErase);
	bool FileExists(const char* file);
	HRESULT DoMountPath(const char* szDrive, const char* szDevice, const char* sysStr);
	HRESULT MountPath(const char* szDrive, const char* szDevice, bool both);
	const char* GetMountPath();
	char* va(const char* fmt, ...);
	bool WriteFile(const CHAR* FilePath, const VOID* Data, DWORD Size);
	DWORD DecryptValue(DWORD val);
	const char* XorString(BYTE* str, int len, BYTE key);
	const char* XorStringNoLen(char* str, BYTE key);
	DWORD GetModuleImportAddr(HANDLE HModule, HANDLE HImportedModule, DWORD Ordinal);
	void AngleVectors(Vector3<float> angles, Vector3<float>* forward, Vector3<float>* right, Vector3<float>* up);

	DWORD Joaat(const char* value) {
		size_t len = strlen(value);
		unsigned int hash, i;
		for (hash = i = 0; i < len; ++i) {
			hash += tolower(value[i]);
			hash += (hash << 10);
			hash ^= (hash >> 6);
		}
		hash += (hash << 3);
		hash ^= (hash >> 11);
		hash += (hash << 15);
		return hash;
	}

	float FloatMinMax(float min, float max) {
		float random = ((float)rand()) / (float)RAND_MAX;
		float range = max - min;
		return (random * range) + min;
	}
};

extern Utilities pUtils;