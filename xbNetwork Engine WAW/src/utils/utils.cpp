#include "stdafx.h"
#include <unordered_map>

Utilities pUtils;

VOID Utilities::PatchInJump(PDWORD Address, DWORD Destination, BOOL Linked)
{
	if (Destination & 0x8000) Address[0] = (0x3D600000 + (((Destination >> 16) & 0xFFFF) + 1));
	else Address[0] = (0x3D600000 + ((Destination >> 16) & 0xFFFF));
	Address[1] = (0x396B0000 + (Destination & 0xFFFF));
	Address[2] = 0x7D6903A6;
	Address[3] = (0x4E800420 | Linked);
	doSync(Address);
}

DWORD Utilities::ResolveFunction(PCHAR Module, DWORD Ordinal)
{
	HANDLE Handle = 0;
	if (NT_SUCCESS(XexGetModuleHandle(Module, &Handle)))
	{
		DWORD Address = 0;
		if (NT_SUCCESS(XexGetProcedureAddress(Handle, Ordinal, &Address))) return Address;
	}
	return 0;
}

void Utilities::Split(const string& s, char c, vector<string>& v) {
	string::size_type i = 0;
	string::size_type j = s.find(c);

	while (j != string::npos) {
		v.push_back(s.substr(i, j - i));
		i = ++j;
		j = s.find(c, j);

		if (j == string::npos)
			v.push_back(s.substr(i, s.length()));
	}
}

vector<string> Utilities::GetFilesInDirectory(string folder, string extension) {
	vector<string> ret;
	string location = folder + extension;
	WIN32_FIND_DATAA fd;

	auto hFind = FindFirstFileA(location.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				ret.push_back(fd.cFileName);
			}
		} while (FindNextFileA(hFind, &fd));
	}

	return ret;
}

char vaBuffer[0x1000];
char* Utilities::va(const char* fmt, ...) {
	memset(vaBuffer, 0, 0x1000);
	va_list ap;
	va_start(ap, fmt);
	RtlVsprintf(vaBuffer, fmt, ap); // RtlVsprintf
	va_end(ap);
	return vaBuffer;
}

char* Utilities::vaBuff(char* vaBuffer, int size, const char* fmt, ...) {
	memset(vaBuffer, 0, size);
	va_list ap;
	va_start(ap, fmt);
	RtlVsprintf(vaBuffer, fmt, ap);
	va_end(ap);
	return vaBuffer;
}

bool Utilities::WriteFile(const CHAR* FilePath, const VOID* Data, DWORD Size) {
	// Open our file
	HANDLE fHandle = CreateFile(FilePath, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (fHandle == INVALID_HANDLE_VALUE) {
		LOG_PRINT(StrEnc("WriteFile - CreateFile failed"));
		return FALSE;
	}

	// Write our data and close
	DWORD writeSize = Size;
	if (::WriteFile(fHandle, Data, writeSize, &writeSize, NULL) != TRUE) {
		LOG_PRINT(StrEnc("WriteFile - WriteFile failed"));
		return FALSE;
	}

	CloseHandle(fHandle);

	// All done
	return TRUE;
}

bool Utilities::FileExists(const char* file) {
	if (GetFileAttributes(file) == -1) {
		DWORD lastError = GetLastError();
		if (lastError == ERROR_FILE_NOT_FOUND || lastError == ERROR_PATH_NOT_FOUND)
			return false;
	}
	return true;
}

void Utilities::EraseAllSubstrings(string& mainStr, string toErase) {
	size_t pos = string::npos;

	while ((pos = mainStr.find(toErase)) != string::npos) {
		mainStr.erase(pos, toErase.length());
	}
}

HRESULT Utilities::DoMountPath(const char* szDrive, const char* szDevice, const char* sysStr) {
	STRING DeviceName, LinkName;
	CHAR szDestinationDrive[MAX_PATH];
	RtlSnprintf(szDestinationDrive, MAX_PATH, sysStr, szDrive);
	RtlInitAnsiString(&DeviceName, szDevice);
	RtlInitAnsiString(&LinkName, szDestinationDrive);
	ObDeleteSymbolicLink(&LinkName);
	return (HRESULT)ObCreateSymbolicLink(&LinkName, &DeviceName);
}

HRESULT Utilities::MountPath(const char* szDrive, const char* szDevice, bool both) {
	HRESULT res;
	if (both) {
		res = DoMountPath(szDrive, szDevice, "\\System??\\%s");
		res = DoMountPath(szDrive, szDevice, "\\??\\%s");
	} else {
		if (KeGetCurrentProcessType() == 2) //SYSTEM_PROC
			res = DoMountPath(szDrive, szDevice, "\\System??\\%s");
		else
			res = DoMountPath(szDrive, szDevice, "\\??\\%s");
	}
	return res;
}

const char* Utilities::GetMountPath() {
	char* DEVICE_DYNAMIC = new char[MAX_PATH];
	wstring ws;
	PLDR_DATA_TABLE_ENTRY TableEntry;
	XexPcToFileHeader((PVOID)0x90e00000, &TableEntry);

	if (TableEntry) {

		ws = TableEntry->FullDllName.Buffer;
		string FullDllName(ws.begin(), ws.end());

		ws = TableEntry->BaseDllName.Buffer;
		string BaseDllName(ws.begin(), ws.end());

		string::size_type i = FullDllName.find(BaseDllName);

		if (i != string::npos)
			FullDllName.erase(i, BaseDllName.length());

		memset(DEVICE_DYNAMIC, 0x0, MAX_PATH);
		strcpy(DEVICE_DYNAMIC, FullDllName.c_str());
	} else {
		LOG_PRINT(StrEnc("Mounting failed!"));
	}

	return DEVICE_DYNAMIC;
}

void LaunchDashboardThread() {
	Sleep(1000);
	XSetLaunchData(NULL, 0);
	XamLoaderLaunchTitleEx(XLAUNCH_KEYWORD_DEFAULT_APP, NULL, NULL, 0);
	ExitThread(0xFF);
}

__declspec(noinline) DWORD Utilities::DecryptValue(DWORD val) {
	DWORD v = val;

	for (auto i = 49; i >= 0; i--) {
		v ^= (i ^ 69);
	}

	v += 100;
	v ^= 666;
	v ^= 76;
	v -= 747;
	v ^= 4712;
	v ^= 36;
	v ^= 45;
	v -= 585858;
	v ^= 454;
	v ^= 12;

	return v;
}

const char* Utilities::XorString(BYTE* str, int len, BYTE key) {
	for (int i = 0; i < len; i++) {
		str[i] ^= key;
	}
}

struct StrEncInfo {
	bool bPopulated;
	char szDecrypted[0x100];
};

unordered_map<DWORD, StrEncInfo*> storage;
const char* Utilities::XorStringNoLen(char* str, BYTE key) {
	if (str) {
		DWORD address = (DWORD)str;
		if (storage[address]) {
			if (storage[address]->bPopulated) {
				return storage[address]->szDecrypted;
			}
		}

		storage[address] = new StrEncInfo();
		storage[address]->bPopulated = true;

		for (int i = 0; i < strlen(str); i++) {
			storage[address]->szDecrypted[i] = str[i] ^ 0xFF;
			if (storage[address]->szDecrypted[i] == 0xFF)
				storage[address]->szDecrypted[i] = 0x0;
		}

		// fix \n
		for (int i = 0; i < strlen(storage[address]->szDecrypted); i++) {
			if (storage[address]->szDecrypted[i] == 0x5C) {
				if (i != strlen(storage[address]->szDecrypted) - 1) {
					if (storage[address]->szDecrypted[i + 1] == 0x6E) {
						if (storage[address]->szDecrypted[i + 2] == 0x0) {
							storage[address]->szDecrypted[i] = '\n';
							storage[address]->szDecrypted[i + 1] = 0x0;
						} else {
							storage[address]->szDecrypted[i] = ' ';
							storage[address]->szDecrypted[i + 1] = '\n';
						}
					}
				}
			}
		}

		return storage[address]->szDecrypted;
	}

	return str;
}

DWORD Utilities::GetModuleImportAddr(HANDLE HModule, HANDLE HImportedModule, DWORD Ordinal) {
	PLDR_DATA_TABLE_ENTRY_2 Module = (PLDR_DATA_TABLE_ENTRY_2)HModule;

	DWORD address = (DWORD)GetProcAddress((HMODULE)HImportedModule, (LPCSTR)Ordinal);

	if (address == NULL || HModule == NULL)
		return 0;

	void* headerBase = Module->XexHeaderBase;
	PXEX_IMPORT_DESCRIPTOR importDesc = (PXEX_IMPORT_DESCRIPTOR)RtlImageXexHeaderField(headerBase, 0x000103FF);
	if (importDesc == NULL)
		return 0;

	char* stringTable = (char*)(importDesc + 1);

	PXEX_IMPORT_TABLE_2 importTable = (PXEX_IMPORT_TABLE_2)(stringTable + importDesc->NameTableSize);

	for (DWORD x = 0; x < importDesc->ModuleCount; x++) {
		DWORD* importAdd = (DWORD*)(importTable + 1);
		for (DWORD y = 0; y < importTable->ImportTable.ImportCount; y++) {
			DWORD value = *((DWORD*)importAdd[y]);
			if (value == address) {
				return (DWORD)(&importAdd[y + 1]);
			}
		}

		importTable = (PXEX_IMPORT_TABLE_2)(((BYTE*)importTable) + importTable->TableSize);
	}

	return 0;
}

void Utilities::AngleVectors(Vector3<float> angles, Vector3<float>* forward, Vector3<float>* right, Vector3<float>* up) {
	float angle;
	float sr, sp, sy, cr, cp, cy;
	angle = angles.Y * (PI * 2.0f / 360.0f);
	sy = sinf(angle);
	cy = cosf(angle);
	angle = angles.X * (PI * 2.0f / 360.0f);
	sp = sinf(angle);
	cp = cosf(angle);
	angle = angles.Z * (PI * 2.0f / 360.0f);
	sr = sinf(angle);
	cr = cosf(angle);

	if (forward) {
		forward->X = cp * cy;
		forward->Y = cp * sy;
		forward->Z = -sp;
	}

	if (right) {
		right->X = (-1 * sr*sp*cy + -1 * cr*-sy);
		right->Y = (-1 * sr*sp*sy + -1 * cr*cy);
		right->Z = -1 * sr*cp;
	}

	if (up) {
		up->X = (cr*sp*cy + -sr * -sy);
		up->Y = (cr*sp*sy + -sr * cy);
		up->Z = cr * cp;
	}
}