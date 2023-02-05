#pragma once

class Engine {
public:
	// UI
	static Material* R_RegisterMaterial(const char* pFont, int iImageTrack);
	static Font* R_RegisterFont(const char* pFont, int iImageTrack);
	static void R_AddCmdDrawStretchPic(float x, float y, float width, float height, float xScale, float yScale, float xay, float yay, const float * color, Material* material);
	static void R_AddCmdDrawText(const char *text, int maxChars, Font *font, float x, float y, float xScale, float yScale, float rotation, const float *color, int style);
	static int R_TextWidth(const char* text, Font* font);
	static void* CG_DrawRotatedPicPhysical(int scrPlacement, float x, float y, float width, float height, float angle, const float* color, Material* material);
	static int R_TextHeight(Font* font);
	static int R_NormalizedTextScale(Font* font, float scale);

	// Dvars
	static bool Dvar_GetBool(const char* dvar);
	static const char* Dvar_GetString(const char* dvar);

	// Compass
	static bool CG_CompassCalcDimensions(CompassType compassType, cg* cg, RectDef* parentRect, RectDef* rect, float* x, float* y, float* w, float* h);

	// Trace
	static void CG_Trace(Trace* trace, Vector3<float>* start, Vector3<float>* end, int ignore, int mask = 0x803003);
	static void FireBulletPenetrate(int client, BulletFireParams* bullet, WeaponDef* weapon, Entity* entity, Vector3<float>* viewOrigin, bool unkBool);

	// Misc
	static void Cbuf_AddText(int localPlayer, const char* command);
	static bool CG_DObjGetWorldTagPos(Entity* entity, int dObj, DWORD tag, Vector3<float>* out);
	static bool AimTarget_GetTagPos(int localClientNum, Entity* entity, short tagIndex, Vector3<float>* out);
	static Vector3<float> GetTagPosition(int client, const char* tag);
	static int Com_GetClientDObj(int handle, int something);
	static DWORD SL_GetString(const char* str);
	static void CG_DrawGrenadePointer(int localClientNum, float centerX, float centerY, Vector3<float>* grenadeOffset, float* color);
	static void CG_DrawGrenadeIcon(int localClientNum, float centerX, float centerY, Vector3<float>* grenadeOffset, float* color, Material* material);
	static void RandomBulletDir(int randomSeed, float* x, float* y);
	static void BG_GetSpreadForWeapon(DWORD ps, int weapon, float* minSpread, float* maxSpread);
	static void CG_GetPlayerViewOrigin(int client, DWORD ps, Vector3<float>* out);
	static void VectorToAngle(Vector3<float>* direction, Vector3<float>* out);
	static float BG_Random(int* pSeed);
	static void CL_SetStance(int client, int stance);
	static void CG_GetEntityBModelBounds(Entity* entity, Vector3<float>* min, Vector3<float>* max, Vector3<float>* absMin, Vector3<float>* absMax);
	static int CG_GetWeaponIndexForName(const char* name);
	static bool CG_CalcNamePosition(int client, Vector3<float>* out, float* outx, float* outy);

	// Custom
	static Vector2<float> GetCenter();
	static Entity* GetEntityPtr();
	static Entity GetEntity(int index);
	static cg* GetCG();
	static ClientInfo GetClientInfo(int index);
	static ServerInfo* GetServerInfo();
	static ClientActive* GetClientActive();
	static bool InGame();
	static DWORD TimeGetTime();
	static bool IsFriend(int client);
	static bool IsAlive(int clientNum, bool notPlayer = false);
	static float GetBoneFraction(int client, const char* aimtag);
	static bool IsLookingAtMe(int client, float* pDegree);
	static float GetDistance(Vector3<float> from, Vector3<float> to);
	static bool WorldToScreen(Vector3<float> in, Vector3<float>* out);
	static void GetWeaponKillIconAspect(int type, Vector2<float>* aspect);
	static WeaponDef* GetWeaponDef(int weapon);
	static Material* GetWeaponMaterialWithAspect(int weapon, Vector2<float>* aspect);
	static bool IsWeaponEquipmentItem(int weapon);
	static bool IsWeaponThis(int weapon, eWeaponCheck check);
	static int GetWeaponIndex(eWeaponCheck check);
	static void CacheEquipmentIndexs();

	// Inline statics
	template<typename T>
	static inline void SetDvar(DWORD dwAddress, T value) {
		*(T*)(*(DWORD*)(dwAddress) + 12) = value;
	}

	template<typename T>
	static inline T GetDvar(DWORD dwAddress) {
		return *(T*)(*(DWORD*)(dwAddress) + 12);
	}

	static int EquipmentWeaponIndexs[6];
};