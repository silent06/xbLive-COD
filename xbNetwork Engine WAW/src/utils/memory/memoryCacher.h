#pragma once

class MemoryCacher {
public:
	MemoryCacher(DWORD dwAddress, DWORD dwSize);
	void Restore();
private:
	BYTE* pPtrForBytes;
	DWORD dwPtrAddress;
	DWORD dwPtrSize;
};