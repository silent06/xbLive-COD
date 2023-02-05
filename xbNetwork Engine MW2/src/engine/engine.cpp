#include "stdafx.h"

int Engine::EquipmentWeaponIndexs[14];

Material* Engine::R_RegisterMaterial(const char* pFont, int iImageTrack) {
	return Invoke::Call<Material*>(GetPatch(xbLive.pPatches->MW2.R_RegisterMaterial), pFont, iImageTrack);
}

Font* Engine::R_RegisterFont(const char* pFont, int iImageTrack) {
	return Invoke::Call<Font*>(GetPatch(xbLive.pPatches->MW2.R_RegisterFont), pFont, iImageTrack);
}

void Engine::R_AddCmdDrawStretchPic(float x, float y, float width, float height, float xScale, float yScale, float xay, float yay, const float * color, Material* material) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW2.R_AddCmdDrawStretchPic), x, y, width, height, xScale, yScale, xay, yay, color, material);
}

void Engine::R_AddCmdDrawText(const char *text, int maxChars, Font *font, float x, float y, float xScale, float yScale, float rotation, const float *color, int style) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW2.R_AddCmdDrawText), text, maxChars, font, x, y, xScale, yScale, rotation, color, style);
};

int Engine::R_TextWidth(const char* text, Font* font) {
	return Invoke::Call<int>(GetPatch(xbLive.pPatches->MW2.R_TextWidth), text, strlen(text) + 1, font);
}

void Engine::CG_DrawRotatedPicPhysical(int scrPlacement, float x, float y, float width, float height, float angle, const float* color, Material* material) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW2.CG_DrawRotatedPicPhysical), scrPlacement, x, y, width, height, angle, color, material);
}

void Engine::CG_DrawRotatedPic(int scrPlacement, float x, float y, float w, float h, int horz, int vert, float angle, float* color, Material* material) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW2.CG_DrawRotatedPic), scrPlacement, x, y, w, h, horz, vert, angle, color, material);
}

int Engine::R_TextHeight(Font* font) {
	return font ? font->iPixelHeight : 0;
}

int Engine::R_NormalizedTextScale(Font* font, float scale) {
	return Invoke::Call<int>(GetPatch(xbLive.pPatches->MW2.R_NormalizedTextScale), font, scale);
}

bool Engine::Dvar_GetBool(const char* dvar) {
	return Invoke::Call<bool>(GetPatch(xbLive.pPatches->MW2.Dvar_GetBool), dvar);
}

const char* Engine::Dvar_GetString(const char* dvar) {
	return Invoke::Call<const char*>(GetPatch(xbLive.pPatches->MW2.Dvar_GetString), dvar);
}

void Engine::CG_CompassDrawPlayerMap(int localClientNum, CompassType compassType, RectDef* parentRect, RectDef* rect, Material* material, float* color) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW2.CG_CompassDrawPlayerMap), localClientNum, compassType, parentRect, rect, material, color);
}

void Engine::CG_CompassDrawPlayer(int localClientNum, CompassType compassType, RectDef* parentRect, RectDef* rect, Material* material, float* color) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW2.CG_CompassDrawPlayer), localClientNum, compassType, parentRect, rect, material, color);
}

void Engine::CG_CompassDrawCrates(int localClientNum, CompassType compassType, RectDef* parentRect, RectDef* rect, Material* material, float* color) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW2.CG_CompassDrawCrates), localClientNum, compassType, parentRect, rect, material, color);
}

void Engine::CG_CompassDrawPlanes(int localClientNum, CompassType compassType, RectDef* parentRect, RectDef* rect, Material* material, float* color) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW2.CG_CompassDrawPlanes), localClientNum, compassType, parentRect, rect, material, color);
}

void Engine::CG_CompassDrawFriendlies(int localClientNum, CompassType compassType, RectDef* parentRect, RectDef* rect, float* color) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW2.CG_CompassDrawFriendlies), localClientNum, compassType, parentRect, rect, color);
}

void Engine::CG_CompassDrawEnemies(int localClientNum, CompassType compassType, RectDef* parentRect, RectDef* rect, float* color) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW2.CG_CompassDrawEnemies), localClientNum, compassType, parentRect, rect, color);
}

void Engine::CG_CompassDrawMissiles(int localClientNum, CompassType compassType, RectDef* parentRect, RectDef* rect, float* color) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW2.CG_CompassDrawMissiles), localClientNum, compassType, parentRect, rect, color);
}

void Engine::CG_CompassDrawTurrets(int localClientNum, CompassType compassType, RectDef* parentRect, RectDef* rect, float* color) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW2.CG_CompassDrawTurrets), localClientNum, compassType, parentRect, rect, color);
}

void Engine::CG_CompassDrawHelicopter(int localClientNum, RectDef* parentRect, RectDef* rect, float* color) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW2.CG_CompassDrawHelicopter), localClientNum, parentRect, rect, color);
}

bool Engine::CG_WorldPosToCompass(CompassType compassType, cg* cg, RectDef* mapRect, Vector2<float>* north, Vector3<float>* world, Vector3<float>* origin, Vector2<float>* out, Vector2<float>* outClipped) {
	return Invoke::Call<bool>(GetPatch(xbLive.pPatches->MW2.CG_WorldPosToCompass), compassType, cg, mapRect, north, world, origin, out, outClipped);
}

bool Engine::CG_CompassCalcDimensions(CompassType compassType, cg* cg, RectDef* parentRect, RectDef* rect, float* x, float* y, float* w, float* h) {
	return Invoke::Call<bool>(GetPatch(xbLive.pPatches->MW2.CG_CompassCalcDimensions), compassType, cg, parentRect, rect, x, y, w, h);
}

void Engine::CG_Trace(Trace* trace, Vector3<float>* start, Vector3<float>* end, int ignore, int mask) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW2.CG_Trace), trace, start, end, ignore, mask);
}

void Engine::FireBulletPenetrate(int client, BulletFireParams* bullet, int weapon, Entity* entity, int alwaysMinusOne, Vector3<float>* viewOrigin, bool unkBool) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW2.FireBulletPenetrate), client, bullet, weapon, entity, alwaysMinusOne, viewOrigin, unkBool);
}

void Engine::CL_SetStance(int client, int stance) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW2.CL_SetStance), client, stance);
}

void Engine::CG_GetEntityBModelBounds(Entity* entity, Vector3<float>* min, Vector3<float>* max) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW2.CG_GetEntityBModelBounds), entity, min, max);
}

int Engine::CG_GetWeaponIndexForName(const char* name) {
	return Invoke::Call<int>(GetPatch(xbLive.pPatches->MW2.CG_GetWeaponIndexForName), name);
}

DWORD Engine::TimeGetTime() {
	return Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW2.TimeGetTime));
}

void Engine::Cbuf_AddText(int localPlayer, const char* command) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW2.Cbuf_AddText), localPlayer, command);
}

bool Engine::CG_DObjGetWorldTagPos(Entity* entity, int dObj, DWORD tag, Vector3<float>* out) {
	return Invoke::Call<bool>(GetPatch(xbLive.pPatches->MW2.CG_DObjGetWorldTagPos), entity, dObj, tag, out);
}

bool Engine::AimTarget_GetTagPos(Entity* entity, short tagIndex, Vector3<float>* out) {
	return Invoke::Call<bool>(GetPatch(xbLive.pPatches->MW2.AimTarget_GetTagPos), entity, tagIndex, out);
}

Vector3<float> Engine::GetTagPosition(int client, const char* tag) {
	if (!IsAlive(client)) {
		return Vector3<float>(0.f, 0.f, 0.f);
	}

	int dobj = Engine::Com_GetClientDObj(client, 0);
	if (!dobj) {
		return Vector3<float>(0.f, 0.f, 0.f);
	}

	Vector3<float> out;
	if (AimTarget_GetTagPos(&GetEntity(client), SL_GetString(tag), &out)) {
		return out;
	}

	return Vector3<float>(0.f, 0.f, 0.f);
}

int Engine::Com_GetClientDObj(int handle, int something) {
	return Invoke::Call<int>(GetPatch(xbLive.pPatches->MW2.Com_GetClientDObj), handle, something);
}

DWORD Engine::SL_GetString(const char* str) {
	return Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW2.SL_GetString), str, 0);
}

short Engine::CG_RegisterTag(const char* str) {
	return Invoke::Call<short>(GetPatch(xbLive.pPatches->MW2.CG_RegisterTag), str);
}

int Engine::AimAssist_GetTagPos(int mask, Entity* entity, short tag, Vector3<float>* out) {
	return Invoke::Call<int>(GetPatch(xbLive.pPatches->MW2.AimAssist_GetTagPos), mask, entity, tag, out);
}

void Engine::CG_DrawGrenadePointer(int localClientNum, float centerX, float centerY, Vector3<float>* grenadeOffset, float* color) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW2.CG_DrawGrenadePointer), localClientNum, centerX, centerY, grenadeOffset, color);
}

void Engine::CG_DrawGrenadeIcon(int localClientNum, float centerX, float centerY, Vector3<float>* grenadeOffset, float* color, Material* material) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW2.CG_DrawGrenadeIcon), localClientNum, centerX, centerY, grenadeOffset, color, material);
}

void Engine::RandomBulletDir(int* randomSeed, float* x, float* y) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW2.RandomBulletDir), randomSeed, x, y);
}

void Engine::BG_SeedRandWithGameTime(int* seed) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW2.BG_SeedRandWithGameTime), seed);
}

void Engine::BG_GetSpreadForWeapon(cg* ps, WeaponDef* weapon, float* minSpread, float* maxSpread) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW2.BG_GetSpreadForWeapon), ps, weapon, minSpread, maxSpread);
}

void Engine::CG_GetPlayerViewOrigin(int client, cg* ps, Vector3<float>* out) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW2.CG_GetPlayerViewOrigin), client, ps, out);
}

void Engine::CG_BulletEndPos(int* seed, float spread, float* viewOrigin, float* spreadEndVec, float* spreadDirection, float* viewX, float* viewY, float* viewZ, float maxRange) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW2.CG_BulletEndPos), seed, spread, viewOrigin, spreadEndVec, spreadDirection, viewX, viewY, viewZ, maxRange);
}

void Engine::VectorToAngle(Vector3<float>* direction, Vector3<float>* out) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW2.VectorToAngle), direction, out);
}

float Engine::BG_Random(int* pSeed) {
	return Invoke::Call<float>(GetPatch(xbLive.pPatches->MW2.BG_Random), pSeed);
}

Entity* Engine::GetEntityPtr() {
	return *(Entity**)GetPatch(xbLive.pPatches->MW2.GetEntityPtr);
}

Entity Engine::GetEntity(int index) {
	if (GetEntityPtr()) {
		return GetEntityPtr()[index];
	}

	return Entity();
}

cg* Engine::GetCG() {
	return *(cg**)GetPatch(xbLive.pPatches->MW2.GetCG);
}

ClientInfo Engine::GetClientInfo(int index) {
	auto cg = GetCG();
	if (cg) {
		if (cg->ClientInfo) {
			return cg->ClientInfo[index];
		}
	}

	return ClientInfo();
}

ServerInfo* Engine::GetServerInfo() {
	return *(ServerInfo**)GetPatch(xbLive.pPatches->MW2.GetServerInfo);
}

ClientActive* Engine::GetClientActive() {
	return *(ClientActive**)GetPatch(xbLive.pPatches->MW2.GetClientActive);
}

_XenonUserData Engine::GetXenonUserData(int index) {
	_XenonUserData* XenonUserData = (_XenonUserData*)GetPatch(xbLive.pPatches->MW2.XenonUserData);
	if (XenonUserData) {
		return XenonUserData[index];
	}

	return _XenonUserData();
}

Vector2<float> Engine::GetCenter() {
	return Vector2<float>(Engine::GetCG()->Refdef.vScale.X * 0.5f, Engine::GetCG()->Refdef.vScale.Y * 0.5f);
}

bool Engine::InGame() {
	return GetDvar<bool>(GetPatch(xbLive.pPatches->MW2.cl_ingame)) && GetCG() != nullptr;
}

bool Engine::IsFriend(int client) {
	auto cg = GetCG();
	if (!cg) return false;

	return cg->ClientInfo[client].iTeam == cg->ClientInfo[cg->iClientNumber].iTeam && strcmp(Dvar_GetString("ui_gametype"), "dm");
}

bool Engine::IsAlive(int clientNum, bool notPlayer) {
	auto entity = GetEntity(clientNum);

	if (notPlayer) return (entity.iIsAlive2 & 1) != 0;
	if ((entity.iIsAlive2 & 1) == 0 || entity.iType != 1) return false;
	return (entity.iIsAlive2 & 1 && entity.iType == 1) /* && Engine::GetCG()->ClientInfo[clientNum].bValidCheck && Engine::GetCG()->ClientInfo[clientNum].iTeam < 3*/;
}

float Engine::GetBoneFraction(int client, const char* aimtag) {
	if (!IsAlive(client)) 0.f;

	Trace t;

	auto cg = GetCG();
	if (!cg) return 0.f;

	auto pos = GetTagPosition(client, aimtag);
	if (!pos.IsNull()) {
		CG_Trace(&t, &cg->Refdef.vOrigin, &pos, client);
		return t.fFraction;
	}

	return 0.f;
}

bool Engine::IsLookingAtMe(int client, float* pDegree) {
	return false;
}

float Engine::GetDistance(Vector3<float> from, Vector3<float> to) {
	float dx = to.X - from.X;
	float dy = to.Y - from.Y;
	float dz = to.Z - from.Z;
	return (float)sqrt((dx * dx) + (dy * dy) + (dz * dz))/* * 0.03048f*/;
}

bool Engine::WorldToScreen(Vector3<float> world, Vector3<float>* out) {
	auto cg = Engine::GetCG();

	Vector3<float> position;
	position.X = world.X - cg->Refdef.vOrigin.X;
	position.Y = world.Y - cg->Refdef.vOrigin.Y;
	position.Z = world.Z - cg->Refdef.vOrigin.Z;

	Vector3<float> transform;
	transform.X = (position.X * cg->Refdef.vViewAxis[1].X) + (position.Y * cg->Refdef.vViewAxis[1].Y) + (position.Z * cg->Refdef.vViewAxis[1].Z);
	transform.Y = (position.X * cg->Refdef.vViewAxis[2].X) + (position.Y * cg->Refdef.vViewAxis[2].Y) + (position.Z * cg->Refdef.vViewAxis[2].Z);
	transform.Z = (position.X * cg->Refdef.vViewAxis[0].X) + (position.Y * cg->Refdef.vViewAxis[0].Y) + (position.Z * cg->Refdef.vViewAxis[0].Z);

	if (transform.Z < 0.1f) {
		return false;
	}

	out->X = (cg->Refdef.vScale.X * 0.5f) * (1 - (transform.X / cg->Refdef.vFOV.X / transform.Z));
	out->Y = (cg->Refdef.vScale.Y * 0.5f) * (1 - (transform.Y / cg->Refdef.vFOV.Y / transform.Z));

	return true;
}

void Engine::GetWeaponKillIconAspect(int type, Vector2<float>* aspect) {
	float width = 1.4f, height = 1.4f;

	if (type == 0) { //1:1
		width = 1.4f;
		height = 1.4f;
	} else if (type == 1) { //2:1
		width = 2.8f;
		height = 1.4f;
	} else if (type == 2) { //3:1
		width = 2.8f;
		height = 0.7f;
	}
	width *= 20.0f;
	height *= 20.0f;
	aspect->X = width;
	aspect->Y = height;
}

WeaponDef* Engine::GetWeaponDef(int weapon) {
	return Invoke::Call<WeaponDef*>(GetPatch(xbLive.pPatches->MW2.GetWeaponDef), weapon);
}

Material* Engine::GetWeaponMaterialWithAspect(int weapon, Vector2<float>* aspect) {
	auto def = GetWeaponDef(weapon);
	GetWeaponKillIconAspect(*(DWORD*)((DWORD)def + 0x3D0), aspect);
	return (Material*)*(DWORD*)(Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->MW2.WeaponDefPointer), weapon) + 0x48);
}

void Engine::CacheEquipmentIndexs() {
	const char* names[] = {
		"frag_grenade_mp", // 
		"concussion_grenade_mp",//
		"flash_grenade_mp",//
		"smoke_grenade_mp",//
		"semtex_mp", // 
		"throwingknife_mp", //
		"flare_mp",//
		"claymore_mp",//
		"c4_mp",//
		"scavenger_bag_mp",
		"riotshield_mp"//
	};

	for (int i = 0; i < 11; i++) {
		EquipmentWeaponIndexs[i] = CG_GetWeaponIndexForName(names[i]);
	}
}

bool Engine::IsWeaponEquipmentItem(int weapon) {
	for (int i = 0; i < 11; i++) {
		if (EquipmentWeaponIndexs[i] == weapon) {
			return true;
		}
	}

	return false;
}

bool Engine::IsWeaponThis(int weapon, eWeaponCheck check) {
	return weapon == EquipmentWeaponIndexs[check];
}

int Engine::GetWeaponIndex(eWeaponCheck check) {
	return EquipmentWeaponIndexs[check];
}