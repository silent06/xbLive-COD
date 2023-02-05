#include "stdafx.h"

MemoryCacher::MemoryCacher(DWORD dwAddress, DWORD dwSize) {
	if (dwSize) {
		dwPtrAddress = dwAddress;
		pPtrForBytes = new BYTE[dwSize];
		memcpy(pPtrForBytes, (void*)dwAddress, dwSize);
	}
}

void MemoryCacher::Restore() {
	memcpy((void*)dwPtrAddress, pPtrForBytes, dwPtrSize);
	delete[] pPtrForBytes;
}