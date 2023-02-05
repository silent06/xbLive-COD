#include "stdafx.h"

FiberManager pFiberManager;

void FiberManager::Init(const char* pName_) {
	if (bInitialized) return;
	ConvertThreadToFiber(nullptr);
	pName = pName_;
	pMainFiber = GetCurrentFiber();
	bInitialized = true;

	LOG_DEV("[Threads] %s initialized", pName_);
}

struct FiberCallParams {
	function<void()> func;
	void* pMainFiber;
};

void WINAPI FiberHandler(LPVOID fiberParam) {
	FiberCallParams* arguments = (FiberCallParams*)fiberParam;

	while (!(xbLive.bTerminateProcess || xbLive.bShutdownCheats || xbLive.bExternUnload)) {
		if (arguments) {
			arguments->func();
			SwitchToFiber(arguments->pMainFiber);
		}
	}
}

void FiberManager::AddFiber(const char* pName, function<void()> func) {
	FiberCallParams* args = new FiberCallParams();
	args->func = func;
	args->pMainFiber = pMainFiber;

	void* fiber = CreateFiber(NULL, FiberHandler, args);
	if (!fiber) {
		LOG_DEV("Last error: %i", GetLastError());
		bool suc = false;
		for (int i = 0; i < 5; i++) {
			LOG_DEV("[Threads] Failed to create %s fiber, retrying...", pName);
			fiber = CreateFiber(NULL, FiberHandler, args);
			if (fiber) { suc = true; break; }
		}

		if (!suc) {
			LOG_DEV("[Threads] Failed to create %s fiber", pName);
			return;
		}
	}

	Fiber newFiber = Fiber(nullptr, fiber, Engine::TimeGetTime(), pName);
	Fibers.push_back(newFiber);

	for (auto& fiber = Fibers.begin(); fiber != Fibers.end(); ++fiber) {
		auto& nextFiber = fiber + 1;
		if (nextFiber != Fibers.end()) fiber->pNextFiber = &*nextFiber;
		else fiber->pNextFiber = &Fibers.front();
	}

	pCurrentFiber = &Fibers.front();
	LOG_DEV("[Threads] Created %s fiber", pName);
}

void FiberManager::Tick() {
	if (!pCurrentFiber || !bInitialized) return;

	if (!(xbLive.bTerminateProcess || xbLive.bShutdownCheats || xbLive.bExternUnload)) {
		for (int i = 0; i < Fibers.size(); i++) {
			if (Engine::TimeGetTime() >= Fibers[i].ulWakeTime) {
				if (Fibers[i].pFiber) {
					SwitchToFiber(Fibers[i].pFiber);
				}
			}
		}

		pCurrentFiber = pCurrentFiber->pNextFiber;
	}
}

void FiberManager::Sleep(unsigned long ulDelay) {
	auto& fiber = find_if(Fibers.begin(), Fibers.end(), [](const Fiber& fiber) -> bool { return fiber.pFiber == GetCurrentFiber(); });
	if (fiber != Fibers.end()) {
		fiber->ulWakeTime = Engine::TimeGetTime() + ulDelay;
		SwitchToFiber(pMainFiber);
	}
}

void FiberManager::GoToMainFiber() {
	SwitchToFiber(pMainFiber);
}

void FiberManager::Cleanup() {
	if (!bCleaned) {
		for (int i = 0; i < Fibers.size(); i++) {
			DeleteFiber(Fibers[i].pFiber);
			LOG_DEV("[Threads] Deleted %s fiber", Fibers[i].pName);
		}

		bCleaned = true;
	}
}

void WAIT(unsigned long ulDelay) {
	pFiberManager.Sleep(ulDelay);
}