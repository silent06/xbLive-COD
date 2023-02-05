#pragma once
#include "menu/submenu.h"

class ESPMenu : public Submenu {
public:
	static ESPMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	ESPMenu() : Submenu() {}
	~ESPMenu();
};

namespace ESPMenuVars {
	struct Vars {
		bool bDrawEnemies;
		bool bDrawFriendlies;
		bool bDrawBox;
		bool bDrawNames;
		bool bDrawDistance;
		bool bDrawBones;
		bool bDrawSnaplines;

		int iDrawBoxSelection;
		int iDrawSnaplinesSelection;

		Color DrawBoxFriendliesColor;
		Color DrawBoxEnemiesColor;
		Color DrawBoxAimbotTargetColor;

		Color DrawNameFriendliesColor;
		Color DrawNameEnemiesColor;
		Color DrawNameAimbotTargetColor;

		Color DrawDistanceFriendliesColor;
		Color DrawDistanceEnemiesColor;
		Color DrawDistanceAimbotTargetColor;

		Color DrawBonesFriendliesColor;
		Color DrawBonesEnemiesColor;
		Color DrawBonesAimbotTargetColor;

		Color DrawSnaplinesFriendliesColor;
		Color DrawSnaplinesEnemiesColor;
		Color DrawSnaplinesAimbotTargetColor;
	};

	extern Vars vars;
}