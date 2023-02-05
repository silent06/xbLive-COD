#pragma once

struct GamePadState {
	int bIsDown;
	bool bWasJustPressed;
	bool bWasJustDown;

	void reset() {
		bIsDown = false;
		bWasJustPressed = false;
	}
};

class Controller {
public:
	GamePadState State[16];
	bool bLeftBypass;
	bool bRightBypass;
	bool bLeftBumperBypass;
	bool bRightBumperBypass;
	bool bABypass;
	bool bBBypass;

	void Update();
	bool IsJustPressed(int key);
	bool IsDown(int key);
	bool IsAiming();
	bool IsShooting();
};

extern Controller pController;

bool IsDown(int key);
bool IsJustPressed(int key);