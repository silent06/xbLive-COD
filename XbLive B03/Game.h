#pragma once

class Game {
public:
	bool bInitialized;

	bool Initialize();
	void Run();
	void Shutdown();
};

extern Game pGame;