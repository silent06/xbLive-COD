#include "stdafx.h"

Utils pUtils;
pDmSetMemory DevSetMemory = NULL;

HRESULT Utils::DoMountPath(const char* szDrive, const char* szDevice, const char* sysStr) {
	STRING DeviceName, LinkName;
	CHAR szDestinationDrive[MAX_PATH];
	RtlSnprintf(szDestinationDrive, MAX_PATH, sysStr, szDrive);
	RtlInitAnsiString(&DeviceName, szDevice);
	RtlInitAnsiString(&LinkName, szDestinationDrive);
	ObDeleteSymbolicLink(&LinkName);
	return (HRESULT)ObCreateSymbolicLink(&LinkName, &DeviceName);
}

HRESULT Utils::MountPath(const char* szDrive, const char* szDevice, bool both) {
	HRESULT res;
	if (both) {
		res = DoMountPath(szDrive, szDevice, "\\System??\\%s");
		res = DoMountPath(szDrive, szDevice, "\\??\\%s");
	}
	else {
		if (KeGetCurrentProcessType() == 2) //SYSTEM_PROC
			res = DoMountPath(szDrive, szDevice, "\\System??\\%s");
		else
			res = DoMountPath(szDrive, szDevice, "\\??\\%s");
	}
	return res;
}

const char* Utils::GetMountPath() {
	return DEVICE_HDD;

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
	}
	else {
		LOG_PRINT("Mounting failed!");
	}

	return DEVICE_DYNAMIC;
}

HRESULT Utils::setMemory(VOID* Destination, VOID* Source, DWORD Length) {

	if (DevSetMemory == NULL) {
		DevSetMemory = (pDmSetMemory)Native::ResolveFunction("xbdm.xex", 40);
	}

	//if (!MmIsAddressValid((PVOID)Destination))
	//    return E_FAIL;

	if (DevSetMemory == NULL) {
		memcpy(Destination, Source, Length);
		return ERROR_SUCCESS;
	}
	else {
		if (DevSetMemory(Destination, Length, Source, NULL) == MAKE_HRESULT(0, 0x2da, 0))
			return ERROR_SUCCESS;
	}
	return E_FAIL;
}

HRESULT Utils::setMemory(VOID* Destination, DWORD Value) {
	return setMemory(Destination, &Value, 4);
}

VOID Utils::ComparePointerWrite(DWORD Address, DWORD Value)
{
	if (!MmIsAddressValid((PVOID)Address))
		return;

	if (*(DWORD*)Address == NULL)
		return;

	if (*(DWORD*)Address != Value) {
		*(DWORD*)Address == Value;
	}

	setMemory((PVOID)Address, Value);
}

VOID Utils::MakeThread(LPTHREAD_START_ROUTINE Address)
{
	HANDLE Handle = 0;
	ExCreateThread(&Handle, 0, 0, XapiThreadStartup, Address, 0, (EX_CREATE_FLAG_SUSPENDED | EX_CREATE_FLAG_SYSTEM | 0x18000424));
	XSetThreadProcessor(Handle, 4);
	SetThreadPriority(Handle, THREAD_PRIORITY_ABOVE_NORMAL);
	ResumeThread(Handle);
	CloseHandle(Handle);
}