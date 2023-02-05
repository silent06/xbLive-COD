#pragma once

class Engine {
public:
	// UI
	static Material* R_RegisterMaterial(const char* pFont, int iImageTrack);
	static Font* R_RegisterFont(const char* pFont, int iImageTrack);
	static void R_AddCmdDrawStretchPic(float x, float y, float width, float height, float xScale, float yScale, float xay, float yay, const float * color, Material* material);
	static void R_AddCmdDrawText(const char *text, int maxChars, Font *font, float x, float y, float xScale, float yScale, float rotation, const float *color, int style);
	static int R_TextWidth(const char* text, Font* font);
	static void CG_DrawRotatedPicPhysical(int scrPlacement, float x, float y, float width, float height, float angle, const float* color, Material* material);
	static int R_TextHeight(Font* font);
	static int R_NormalizedTextScale(Font* font, float scale);

	// Engine
	static DWORD TimeGetTime();
	static DWORD GetNetInfoAddress(int index);
	static const char* GetNameFromNetInfo(int index);
	static BYTE* GetIPFromNetInfo(int index);
	static BYTE* GetMacAddressFromNetInfo(int index);
	static QWORD GetXUIDFromNetInfo(int index, BOOL read = FALSE);
	static QWORD GetMachineIDFromNetInfo(int index);
	static void Cbuf_AddText(int localClient, const char* msg);
	static void CL_AddReliableCommand(int localClient, const char* msg);
	static DWORD TransformSeed(int* pSeed);
	static void BG_GetSpreadForWeapon(DWORD ps, int weapon, float* minSpread, float* maxSpread);
	static float RandomBulletDir(int* randomSeed);
	static int Com_GetClientDObj(int handle, int something);
	static bool CG_DObjGetWorldTagPos(Entity* entity, int dObj, DWORD tag, Vector3<float>* out);
	static short SL_GetString(const char* name, DWORD zero);
	static const char* SL_ConvertToString(short tag);
	static void CG_LocationalTrace(Trace *trace, Vector3<float> *start, Vector3<float> *end, int passEntityNum, int contMask, int u1, int u2);
	static bool CG_GetPlayerViewOrigin(int local, DWORD ps, Vector3<float>* origin);
	static void FireBulletPenetrate(int local, BulletFireParams *bp, DWORD weaponNum, Entity* centity_s, Vector3<float>* Origin, DWORD one, bool unk, BulletTraceResults *br);
	static DWORD CG_GetWeaponIndexForName(const char* name);
	static WeaponDef* GetWeaponDef(int weapon);
	static void CG_DrawGrenadePointer(int client, float centerX, float centerY, Vector3<float>* offset, float* color, float radiusOffset, float scaleFactor);
	static void CG_DrawGrenadeIcon(int client, float centerX, float centerY, Vector3<float>* offset, float* color, Material* material, float radiusOffset, float scaleFactor);
	static const char* Dvar_GetString(const char* dvar);
	static void CL_SetStance(int local, int stance);
	static DObjAnimMat* CG_DObjGetLocalTagMatrix(Entity* entity, DObj_s* dObj, unsigned int tagName);
	static DObjAnimMat* CG_DObjGetWorldTagMatrix(Entity* entity, DObj_s* dObj, unsigned int tagName, Vector3<float>* axis, Vector3<float>* origin);

	// Custom
	static bool InGame();
	static cg* GetCG();
	static ServerInfo* GetServerInfo();
	static Entity* GetEntityPtr();
	static Entity GetEntity(int index);
	static ClientInfo GetClientInfo(int index);
	static bool IsAlive(int index, bool player = false);
	static bool IsFriend(int index);
	static float GetBoneFraction(int client, const char* tag);
	static bool IsLookingAtMe(int index, float* degree);
	static float GetDistance(Vector3<float> from, Vector3<float> to);
	static Vector3<float> GetTagPosition(int client, const char* tag, bool cached = true);
	static void VectorToAngle(Vector3<float>* direction, Vector3<float>* out);
	static ClientActive* GetClientActive();
	static bool IsWeaponEquipmentItem(int weapon);
	static bool IsWeaponThis(int weapon, eWeaponCheck check);
	static void GetWeaponKillIconAspect(int type, Vector2<float>* aspect);
	static Vector2<float> GetCenter();
	static void CacheEquipmentIndexs();
	static bool WorldToScreen(Vector3<float> world, Vector3<float>* out);
	static Material* GetWeaponMaterialWithAspect(int weapon, Vector2<float>* aspect);

	// Inline statics
	template<typename T>
	static inline void SetDvar(DWORD dwAddress, T value) {
		*(T*)(*(DWORD*)(dwAddress) + 0x18) = value;
	}

	template<typename T>
	static inline T GetDvar(DWORD dwAddress) {
		return *(T*)(*(DWORD*)(dwAddress) +0x18);
	}

	static int EquipmentWeaponIndexs[16];
};