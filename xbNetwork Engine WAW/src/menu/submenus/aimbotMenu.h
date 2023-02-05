#pragma once
#include "menu/submenu.h"

class AimbotMenu : public Submenu {
public:
	static AimbotMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	AimbotMenu() : Submenu() {}
	~AimbotMenu();
};

namespace AimbotMenuVars {
	struct Vars {
		bool bAimbot;
		bool bAimingRequired;
		bool bPositionPrediction;
		bool bIncreasedPenetrationChecks;
		bool bAutoFire;
		bool bAutoADS;
		bool bShowAimbotTarget;
		bool bAutowall;
		bool bTeleport;

		int iAimFilter;
		int iAimType;
		int iAimTag;
		int iAutoFireDelay;

		float fAimSmoothing;
		float fPositionPrediction;

		Vector3<int> vSilentAngles;
	};

	extern ScrollStruct<int> ScrollAimTag[22];
	extern ScrollStruct<int> ScrollAutowallBoneTags[7];
	bool IsTargetVisible(float fraction);
	bool IsClientWallbangable(int client, const char* bone);
	void SilentAim(UserCommand* oldCommand, Vector3<float> toAngle);
	void SnapAim(Vector3<float> toAngle);
	void SilentAim(UserCommand* oldCommand, Vector3<float> toAngle);
	int CalculateBestClient();
	extern Vars vars;
}