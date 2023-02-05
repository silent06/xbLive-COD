#include "stdafx.h"

Invoker pInvoker;

DWORD* Invoker::Call(DWORD NativeAddress, NativeManager* Context) {
	DWORD* result = nullptr;
	NativeHandler handler = GetNativeHandler(NativeAddress);
	if (handler) {
		__try {
			handler(Context);
		} __except (true) {}
		result = (DWORD*)Context->GetResultPointer();
	}

	return result;
}

#pragma optimize( "", off )
NativeHandler Invoker::GetNativeHandler(DWORD NativeAddress) {
	NativeHandler Handler = nullptr;

	for (int i = 0; i < NativeTable->GetCount(); i++) {
		if (NativeTable->RandomStuff(1) != 0xFFFF) { // fattest meme
			if (NativeTable->GetAddress(i) == NativeAddress) {
				Handler = NativeTable->GetFunction(i);
				break;
			}
		}
	}

	return Handler;
}
#pragma optimize( "", on )

HRESULT Invoker::Initialize() {
	pCodCheatInterface = Interface::GetInterface<CodCheatInterface>(0x13371336); 
	
	if (pCodCheatInterface) {
		pInvoker.SetTable(pCodCheatInterface->GetRegistration());
	}

	LOG_DEV("Native table: %X", pInvoker.GetTable());

	return S_OK;
}