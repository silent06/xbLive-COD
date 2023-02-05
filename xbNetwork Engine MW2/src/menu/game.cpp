#include "stdafx.h"

Game pGame;

void Game::Run() {
	// ran on loop
	Sleep(50);
}

bool Game::Initialize() {
	// init config here

	pGame.iAimbotTarget = -1;

	if (!pTitle.ApplyHooks()) {
		LOG_DEV("Failed to apply hooks! Removing any that were successful!");
		return false;
	}

	LOG_DEV("Game initialized!");
	xbLive.bGameInitialized = true;
	bInitialized = true;
	return true;
}

void Game::Shutdown() {
	pTitle.Remove();

	xbLive.bShutdownCheats = false;
	LOG_DEV("Game uninitialized!");
}