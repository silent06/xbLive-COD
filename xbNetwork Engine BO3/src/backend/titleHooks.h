#pragma once

class Title {
public:
	bool bInitialized;

	bool ApplyHooks();
	void Remove(bool bOverride = false);
};

extern Title pTitle;