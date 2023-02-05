#pragma once

struct DontFuckingFreeThis {
	DObj_s* pDObj;
	bool bCanFree;
};

class Game {
public:
	bool bInitialized;
	bool bResetState;
	UIContext* pContext;

	bool Initialize();
	void Run();
	void Shutdown();

	int iClosestAATarget;
	int iAimbotTarget;
	Priority Clients[18];
};

extern Game pGame;