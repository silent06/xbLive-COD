#include "stdafx.h"

Hooking pHooking;


VOID Hooking::patchInJump(DWORD* Address, DWORD Destination, bool Linked)
{
	Address[0] = 0x3D600000 + ((Destination >> 16) & 0xFFFF);
	if (Destination & 0x8000)
		Address[0] += 1;
	Address[1] = 0x396B0000 + (Destination & 0xFFFF);
	Address[2] = 0x7D6903A6;
	Address[3] = Linked ? 0x4E800421 : 0x4E800420;
}

VOID __declspec(naked) GLPR(VOID) {
	__asm
	{
		std     r14, -0x98(sp)
		std     r15, -0x90(sp)
		std     r16, -0x88(sp)
		std     r17, -0x80(sp)
		std     r18, -0x78(sp)
		std     r19, -0x70(sp)
		std     r20, -0x68(sp)
		std     r21, -0x60(sp)
		std     r22, -0x58(sp)
		std     r23, -0x50(sp)
		std     r24, -0x48(sp)
		std     r25, -0x40(sp)
		std     r26, -0x38(sp)
		std     r27, -0x30(sp)
		std     r28, -0x28(sp)
		std     r29, -0x20(sp)
		std     r30, -0x18(sp)
		std     r31, -0x10(sp)
		stw     r12, -0x8(sp)
		blr
	}
}

DWORD Hooking::RelinkGPLR(DWORD SFSOffset, DWORD* SaveStubAddress, DWORD* OriginalAddress)
{
	DWORD Instruction = NULL, Replacing;
	DWORD* Saver = (DWORD*)GLPR;

	if (SFSOffset & 0x2000000)
		SFSOffset |= 0xFC000000;

	Replacing = OriginalAddress[SFSOffset / 0x04];
	for (DWORD i = NULL; i < 0x14; i++) {
		if (Replacing == Saver[i]) {
			DWORD NewAddress = (DWORD)&Saver[i] - (DWORD)SaveStubAddress;
			Instruction = (0x48000001 | (NewAddress & 0x03FFFFFC));
		}
	}
	return Instruction;
}

VOID Hooking::hookFunctionStart(PDWORD Address, PDWORD SaveStub, DWORD Destination)
{
	if ((SaveStub != NULL) && (Address != NULL)) {

		HookContext cxt;
		cxt.dwAddress = Address;
		memcpy(cxt.szAsm, (void*)Address, 0x10);
		vHookContext.push_back(cxt);/*Pushback Hook to save for Unhooking later after exiting game*/
		
		DWORD AddressRelocation = (DWORD)(&Address[4]);
		if (AddressRelocation & 0x8000) {
			SaveStub[0] = 0x3D600000 + (((AddressRelocation >> 16) & 0xFFFF) + 1);
		}
		else {
			SaveStub[0] = 0x3D600000 + ((AddressRelocation >> 16) & 0xFFFF);
		}
		SaveStub[1] = 0x396B0000 + (AddressRelocation & 0xFFFF);
		SaveStub[2] = 0x7D6903A6;

		for (int i = 0; i < 4; i++) {
			if ((Address[i] & 0x48000003) == 0x48000001) {
				SaveStub[i + 3] = RelinkGPLR((Address[i] & ~0x48000003), &SaveStub[i + 3], &Address[i]);
			}
			else {
				SaveStub[i + 3] = Address[i];
			}
		}

		SaveStub[7] = 0x4E800420;
		__dcbst(0, SaveStub);
		__sync();
		__isync();
		patchInJump(Address, Destination, FALSE);
	}
}
void Hooking::Unhook(PDWORD dwAddress) {
	for (int i = 0; i < vHookContext.size(); i++) {
		if (dwAddress == vHookContext.at(i).dwAddress) {
			memcpy((void*)vHookContext.at(i).dwAddress, vHookContext.at(i).szAsm, vHookContext.at(i).bWriteSize);
			LOG_PRINT("Unhooked: Address=0x%X", vHookContext.at(i).dwAddress);
			break;
		}
	}
}
void Hooking::UnhookAll() {
	for (int i = 0; i < vHookContext.size(); i++) {
		memcpy((void*)vHookContext.at(i).dwAddress, vHookContext.at(i).szAsm, vHookContext.at(i).bWriteSize);
		LOG_PRINT("Unhooked: Address=0x%X", vHookContext.at(i).dwAddress);
	}
}