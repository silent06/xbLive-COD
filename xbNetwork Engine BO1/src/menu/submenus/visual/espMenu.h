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
		bool bDrawDogs;

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

		Color DrawDogsFriendliesColor;
		Color DrawDogsEnemiesColor;
	};

	void DrawESPLine(Vector3<float> center, float x1, float y1, float z1, float x2, float y2, float z2, Color color);
	void DrawESPLineEasy(Vector3<float> x, Vector3<float> y, Color color);
	void DrawBoneOnPlayer(int client, char*startBone, char*endBone, Color color);
	extern Vars vars;
}