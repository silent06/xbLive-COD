#pragma once

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

typedef HRESULT(*pDmSetMemory)(LPVOID lpbAddr, DWORD cb, LPCVOID lpbBuf, LPDWORD pcbRet);

class Utils {
public:
	HRESULT DoMountPath(const char* szDrive, const char* szDevice, const char* sysStr);
	HRESULT MountPath(const char* szDrive, const char* szDevice, bool both);
	const char* GetMountPath();
	VOID ComparePointerWrite(DWORD Address, DWORD Value);
	HRESULT setMemory(VOID* Destination, DWORD Value);
	HRESULT setMemory(VOID * Destination, VOID * Source, DWORD Length);
	VOID Utils::MakeThread(LPTHREAD_START_ROUTINE Address);
};

extern Utils pUtils;