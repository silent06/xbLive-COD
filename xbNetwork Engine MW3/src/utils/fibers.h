#pragma once

struct Fiber {
	Fiber* pNextFiber;
	void* pFiber;
	unsigned long ulWakeTime;
	const char* pName;

	Fiber() {}

	Fiber(Fiber* a, void* b, unsigned long c, const char* d) {
		pNextFiber = a;
		pFiber = b;
		ulWakeTime = c;
		pName = d;
	}
};

class FiberManager {
public:
	void Init(const char* pName);
	void Tick();
	void AddFiber(const char* pName, function<void()> func);
	void Sleep(unsigned long ulDelay);
	void GoToMainFiber();
	void Cleanup();

	vector<Fiber> GetFibers() { return Fibers; }
private:
	vector<Fiber> Fibers;
	void* pMainFiber;
	Fiber* pCurrentFiber;
	const char* pName;
	bool bInitialized;
	bool bCleaned;
};

extern FiberManager pFiberManager;

void WAIT(unsigned long ulDelay);