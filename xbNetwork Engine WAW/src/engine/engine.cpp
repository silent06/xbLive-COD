#include "stdafx.h"

int Engine::EquipmentWeaponIndexs[6];

Material* Engine::R_RegisterMaterial(const char* pFont, int iImageTrack) {
	return Invoke::Call<Material*>(GetPatch(xbLive.pPatches->WAW.R_RegisterMaterial), 0x06, pFont, iImageTrack);
}

Font* Engine::R_RegisterFont(const char* pFont, int iImageTrack) {
	return Invoke::Call<Font*>(GetPatch(xbLive.pPatches->WAW.R_RegisterMaterial), 0x15, pFont, iImageTrack);
}

void Engine::R_AddCmdDrawStretchPic(float x, float y, float width, float height, float xScale, float yScale, float xay, float yay, const float * color, Material* material) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->WAW.R_AddCmdDrawStretchPic), x, y, width, height, xScale, yScale, xay, yay, color, material);
}

void Engine::R_AddCmdDrawText(const char *text, int maxChars, Font *font, float x, float y, float xScale, float yScale, float rotation, const float *color, int style) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->WAW.R_AddCmdDrawText), text, maxChars, font, x, y, xScale, yScale, rotation, color, style);
};

int Engine::R_TextWidth(const char* text, Font* font) {
	if (!text) return 0;
	return Invoke::Call<int>(GetPatch(xbLive.pPatches->WAW.R_TextWidth), text, 0x7FFFFFFF, font);
}

void* Engine::CG_DrawRotatedPicPhysical(int scrPlacement, float x, float y, float width, float height, float angle, const float* color, Material* material) {
	return Invoke::Call<void*>(GetPatch(xbLive.pPatches->WAW.CG_DrawRotatedPicPhysical), scrPlacement, x, y, width, height, angle, color, material);
}

int Engine::R_TextHeight(Font* font) {
	return font ? font->iPixelHeight : 0;
}

int Engine::R_NormalizedTextScale(Font* font, float scale) {
	return Invoke::Call<int>(GetPatch(xbLive.pPatches->WAW.R_NormalizedTextScale), font, scale);
}

bool Engine::CG_CompassCalcDimensions(CompassType compassType, cg* cg, RectDef* parentRect, RectDef* rect, float* x, float* y, float* w, float* h) {
	return Invoke::Call<bool>(GetPatch(xbLive.pPatches->WAW.CG_CompassCalcDimensions), compassType, cg, parentRect, rect, x, y, w, h);
}

void Engine::CG_Trace(Trace* trace, Vector3<float>* start, Vector3<float>* end, int ignore, int mask) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->WAW.CG_Trace), trace, start, end, ignore, mask);
}

void Engine::FireBulletPenetrate(int client, BulletFireParams* bullet, WeaponDef* weapon, Entity* entity, Vector3<float>* viewOrigin, bool unkBool, DWORD a) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->WAW.FireBulletPenetrate), client, bullet, weapon, entity, viewOrigin, unkBool, a);
}

void Engine::CL_SetStance(int client, int stance) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->WAW.CL_SetStance), client, stance);
}

int Engine::CG_GetWeaponIndexForName(const char* name) {
	return Invoke::Call<int>(GetPatch(xbLive.pPatches->WAW.CG_GetWeaponIndexForName), name, 0);
}

void Engine::Cbuf_AddText(int localPlayer, const char* command) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->WAW.Cbuf_AddText), localPlayer, command);
}

bool Engine::CG_DObjGetWorldTagPos(Entity* entity, int dObj, DWORD tag, Vector3<float>* out) {
	return Invoke::Call<bool>(GetPatch(xbLive.pPatches->WAW.CG_DObjGetWorldTagPos), entity, dObj, tag, out);
}

Vector3<float> Engine::GetTagPosition(int client, const char* tag) {
	if (!IsAlive(client)) {
		return Vector3<float>(0.f, 0.f, 0.f);
	}

	int dobj = Engine::Com_GetClientDObj(GetEntity(client).iClientNumber, 0);
	if (!dobj) {
		return Vector3<float>(0.f, 0.f, 0.f);
	}

	Vector3<float> out;
	if (Engine::CG_DObjGetWorldTagPos(&GetEntity(client), dobj, SL_GetString(tag), &out)) {
		return out;
	}

	return Vector3<float>(0.f, 0.f, 0.f);
}

int Engine::Com_GetClientDObj(int handle, int something) {
	return Invoke::Call<int>(GetPatch(xbLive.pPatches->WAW.Com_GetClientDObj), handle, something);
}

DWORD Engine::SL_GetString(const char* str) {
	return Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->WAW.SL_GetString), str);
}

void Engine::CG_DrawGrenadePointer(int localClientNum, float centerX, float centerY, Vector3<float>* grenadeOffset, float* color) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->WAW.CG_DrawGrenadePointer), localClientNum, centerX, centerY, grenadeOffset, color);
}

void Engine::CG_DrawGrenadeIcon(int localClientNum, float centerX, float centerY, Vector3<float>* grenadeOffset, float* color, Material* material) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->WAW.CG_DrawGrenadeIcon), localClientNum, centerX, centerY, grenadeOffset, color, material);
}

void Engine::BG_GetSpreadForWeapon(DWORD ps, WeaponDef* weapon, float* minSpread, float* maxSpread) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->WAW.BG_GetSpreadForWeapon), ps, weapon, minSpread, maxSpread);
}

void Engine::CG_GetPlayerViewOrigin(int client, DWORD ps, Vector3<float>* out) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->WAW.CG_GetPlayerViewOrigin), client, ps, out);
}

void Engine::VectorToAngle(Vector3<float>* direction, Vector3<float>* out) {
	float forward, yaw, pitch, PiDiv = (180.0f / XM_PI);

	if (direction->Y == 0 && direction->X == 0) {
		yaw = 0;
		if (direction->Z > 0)
			pitch = 90;
		else
			pitch = 270;
	} else {
		if (direction->X)
			yaw = (atan2(direction->Y, direction->X) * PiDiv);
		else if (direction->Y > 0)
			yaw = 90.0f;
		else
			yaw = 270.0f;

		if (yaw < 0.0f)
			yaw += 360.0f;

		forward = sqrt((direction->X * direction->X) + (direction->Y * direction->Y));
		pitch = (atan2(direction->Z, forward) * PiDiv);

		if (pitch < 0.0f)
			pitch += 360;
	}

	out->X = 360.0f - pitch;
	out->Y = yaw;
	out->Z = 0.0f;

	if (out->X > 360.0f)
		out->X -= 360.0f;
	if (out->X < 0.0f)
		out->X += 360.0f;

	if (out->Y > 360.0f)
		out->Y -= 360.0f;
	if (out->Y < 0.0f)
		out->Y += 360.0f;
}

float Engine::BG_Random(int* pSeed) {
	return Invoke::Call<float>(GetPatch(xbLive.pPatches->WAW.BG_Random), pSeed);
}

Entity* Engine::GetEntityPtr() {
	return *(Entity**)GetPatch(xbLive.pPatches->WAW.GetEntityPtr);
}

Entity Engine::GetEntity(int index) {
	if (GetEntityPtr()) {
		return GetEntityPtr()[index];
	}
	
	return Entity();
}

cg* Engine::GetCG() {
	return *(cg**)GetPatch(xbLive.pPatches->WAW.GetCG);
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
	return *(ServerInfo**)GetPatch(xbLive.pPatches->WAW.GetServerInfo);
}

ClientActive* Engine::GetClientActive() {
	return *(ClientActive**)GetPatch(xbLive.pPatches->WAW.GetClientActive);
}

Vector2<float> Engine::GetCenter() {
	return Vector2<float>(Engine::GetCG()->Refdef.vScale.X * 0.5f, Engine::GetCG()->Refdef.vScale.Y * 0.5f);
}

bool Engine::InGame() {
	return GetDvar<bool>(GetPatch(xbLive.pPatches->WAW.cl_ingame)) && GetCG() != nullptr && !Invoke::Call<bool>(GetPatch(xbLive.pPatches->WAW.CL_AllLocalClientsDisconnected));
}

DWORD Engine::TimeGetTime() {
	return Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->WAW.TimeGetTime));
}

bool Engine::IsFriend(int client) {
	auto cg = GetCG();
	if (!cg) return false;

	return cg->ClientInfo[client].iTeam == cg->ClientInfo[cg->iClientNumber].iTeam && strcmp(GetDvar<const char*>(GetPatch(xbLive.pPatches->WAW.ui_gametype)), "dm");
}

bool Engine::IsAlive(int clientNum, bool notPlayer) {
	auto cg = GetCG();
	if (!cg) return false;

	if (notPlayer) return GetEntity(clientNum).iIsAlive & 0x40000000;

	return GetEntity(clientNum).iType == 1 && GetEntity(clientNum).iIsAlive & 0x40000000;
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
	return (WeaponDef*)*(DWORD*)(GetPatch(xbLive.pPatches->WAW.WeaponDefPointer) + (weapon * 4));
}

Material* Engine::GetWeaponMaterialWithAspect(int weapon, Vector2<float>* aspect) {
	auto def = GetWeaponDef(weapon);
	if (def) {
		GetWeaponKillIconAspect(def->dwKillIconType, aspect);
		return def->pKillIcon;
	}

	return nullptr;
}

void Engine::CacheEquipmentIndexs() {
	const char* names[] = {
		"frag_grenade_mp", // fine
		"sticky_grenade_mp", // fine
		"mine_bouncing_betty_mp", // fine
		"m8_white_smoke_mp", // fine
		"signal_flare_mp", // fine
	};

	for (int i = 0; i < 5; i++) {
		EquipmentWeaponIndexs[i] = CG_GetWeaponIndexForName(names[i]);
	}
}

int Engine::FixDroppedItemIndex(int num) {
	__asm
	{
		mr        r9, r3
		srawi     r7, r9, 8
		addze     r6, r7
		slwi      r4, r6, 8
		subf      r3, r4, r9
		blr
	}
}

bool Engine::IsWeaponEquipmentItem(int weapon) {
	for (int i = 0; i < 5; i++) {
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