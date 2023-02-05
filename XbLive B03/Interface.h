#pragma once

class Interface {
public:
	template<typename T>
	static T* GetInterface(DWORD dwHash) {
		HANDLE hModule = NULL;
		void* proc = nullptr;

		if (!NT_SUCCESS(XexGetModuleHandle((char*)"xbLive.xex", &hModule))) {
			return nullptr;
		}

		if (!NT_SUCCESS(XexGetProcedureAddress(hModule, 1, &proc))) {
			return nullptr;
		}

		return Invoke::Call<T*>((DWORD)proc, dwHash);
	}
};

class CodCheatInterface {
public:
	virtual NativeRegistration* GetRegistration() = 0;
};

extern CodCheatInterface* pCodCheatInterface;