#pragma once

class Title {
public:
	bool bInitialized;
	bool bPreGameInit;

	bool ApplyHooks();
	void Remove(bool bOverride = false);
};

extern Title pTitle;