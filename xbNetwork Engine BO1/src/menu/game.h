#pragma once

class Game {
public:
	bool bInitialized;
	UIContext* pContext;

	bool Initialize();
	void Run();
	void Shutdown();

	int iAimbotTarget;
	int iClosestAATarget;
	Priority Clients[18];
};

extern Game pGame;