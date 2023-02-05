#include "stdafx.h"

Controller pController;

void Controller::Update() {
	XINPUT_STATE pState;
	XInputGetState(0, &pState);

	State[A].bIsDown = (pState.Gamepad.wButtons & XINPUT_GAMEPAD_A) || bABypass;
	State[X].bIsDown = (pState.Gamepad.wButtons & XINPUT_GAMEPAD_X);
	State[Y].bIsDown = (pState.Gamepad.wButtons & XINPUT_GAMEPAD_Y);
	State[B].bIsDown = (pState.Gamepad.wButtons & XINPUT_GAMEPAD_B) || bBBypass;
	State[DPAD_UP].bIsDown = (pState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP);
	State[DPAD_DOWN].bIsDown = (pState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
	State[DPAD_LEFT].bIsDown = (pState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) || bLeftBypass;
	State[DPAD_RIGHT].bIsDown = (pState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) || bRightBypass;
	State[START].bIsDown = (pState.Gamepad.wButtons & XINPUT_GAMEPAD_START);
	State[BACK].bIsDown = (pState.Gamepad.wButtons & XINPUT_GAMEPAD_BACK);
	State[LEFT_THUMB].bIsDown = (pState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB);
	State[RIGHT_THUMB].bIsDown = (pState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB);
	State[LEFT_SHOULDER].bIsDown = (pState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) || bLeftBumperBypass;
	State[RIGHT_SHOULDER].bIsDown = (pState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) || bRightBumperBypass;
	State[LEFT_TRIGGER].bIsDown = pState.Gamepad.bLeftTrigger > 35;
	State[RIGHT_TRIGGER].bIsDown = pState.Gamepad.bRightTrigger > 35;

	for (int i = 0; i < 16; i++) {
		State[i].bWasJustPressed = !State[i].bWasJustDown && State[i].bIsDown;
		State[i].bWasJustDown = State[i].bIsDown;
	}

	bLeftBumperBypass = false;
	bRightBumperBypass = false;
	bLeftBypass = false;
	bRightBypass = false;
	bABypass = false;
	bBBypass = false;
}

bool Controller::IsAiming() {
	return State[LEFT_TRIGGER].bIsDown;
}

bool Controller::IsDown(int key) {
	return State[key].bIsDown;
}

bool Controller::IsJustPressed(int key) {
	return State[key].bWasJustPressed;
}

bool IsDown(int key) {
	return pController.IsDown(key);
}

bool IsJustPressed(int key) {
	return pController.IsJustPressed(key);
}