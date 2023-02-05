#pragma once

class Game {
public:
	bool bInitialized;

	bool Initialize();
	void Run();
	void Shutdown();

	int iAimbotTarget;
	Priority Clients[18];
};

extern Game pGame;