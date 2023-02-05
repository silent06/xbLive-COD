#include "stdafx.h"

int Engine::EquipmentWeaponIndexs[16];

Material* Engine::R_RegisterMaterial(const char* pFont, int iImageTrack) {
	return Invoke::Call<Material*>(GetPatch(xbLive.pPatches->BO1.R_RegisterMaterial), 0x06, pFont, iImageTrack);
}

Font* Engine::R_RegisterFont(const char* pFont, int iImageTrack) {
	return Invoke::Call<Font*>(GetPatch(xbLive.pPatches->BO1.R_RegisterMaterial), 0x15, pFont, iImageTrack);
}

void Engine::R_AddCmdDrawStretchPic(float x, float y, float width, float height, float xScale, float yScale, float xay, float yay, const float * color, Material* material) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->BO1.R_AddCmdDrawStretchPic), x, y, width, height, xScale, yScale, xay, yay, color, material);
}

void Engine::R_AddCmdDrawText(const char *text, int maxChars, Font *font, float x, float y, float xScale, float yScale, float rotation, const float *color, int style) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->BO1.R_AddCmdDrawText), text, maxChars, font, x, y, xScale, yScale, rotation, color, style);
}

int Engine::R_TextWidth(const char* text, Font* font) {
	if (font == nullptr) return 0;
	return Invoke::Call<int>(GetPatch(xbLive.pPatches->BO1.R_TextWidth), text, 0x7FFFFFFF, font);
}

void Engine::CG_DrawRotatedPicPhysical(int scrPlacement, float x, float y, float width, float height, float angle, const float* color, Material* material) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->BO1.CG_DrawRotatedPicPhysical), scrPlacement, x, y, width, height, angle, color, material);
}

int Engine::R_TextHeight(Font* font) {
	return font->iPixelHeight;
}

int Engine::R_NormalizedTextScale(Font* font, float scale) {
	return Invoke::Call<int>(GetPatch(xbLive.pPatches->BO1.R_NormalizedTextScale), font, scale);
}

bool Engine::InGame() {
	return GetDvar<bool>(GetPatch(xbLive.pPatches->BO1.cl_ingame)) && GetCG() != nullptr;
}

cg* Engine::GetCG() {
	return *(cg**)GetPatch(xbLive.pPatches->BO1.GetCG);
}

ServerInfo* Engine::GetServerInfo() {
	return *(ServerInfo**)GetPatch(xbLive.pPatches->BO1.GetServerInfo);
}

DWORD Engine::GetNetInfoAddress(int index) {
	return (GetPatch(xbLive.pPatches->BO1.GetNetInfoAddress) + (index * 0x200));
}

DWORD Engine::TimeGetTime() {
	return Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->BO1.TimeGetTime));
}

const char* Engine::GetNameFromNetInfo(int index) {
	return (char*)(GetNetInfoAddress(index) + 0x08); 
}

BYTE* Engine::GetIPFromNetInfo(int index) {
	return (BYTE*)(GetNetInfoAddress(index) + 0x60); 
}

BYTE* Engine::GetMacAddressFromNetInfo(int index) {
	return (BYTE*)(GetNetInfoAddress(index) + 0x82); 
}

QWORD Engine::GetXUIDFromNetInfo(int index, BOOL read) {
	if (read)
		return *(QWORD*)GetNetInfoAddress(index);
	return GetNetInfoAddress(index);
}

QWORD Engine::GetMachineIDFromNetInfo(int index) {
	return _byteswap_uint64(*(QWORD*)(GetNetInfoAddress(index) + 0x74)); 
}

void Engine::Cbuf_AddText(int localClient, const char* msg) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->BO1.Cbuf_AddText), localClient, msg);
}

void Engine::CL_AddReliableCommand(int localClient, const char* msg) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->BO1.CL_AddReliableCommand), localClient, msg);
}

void Engine::BG_GetSpreadForWeapon(DWORD ps, WeaponDef* weapon, float* minSpread, float* maxSpread) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->BO1.BG_GetSpreadForWeapon), ps, weapon, minSpread, maxSpread);
}

float Engine::RandomBulletDir(int* randomSeed) {
	return Invoke::Call<float>(GetPatch(xbLive.pPatches->BO1.RandomBulletDir), randomSeed);
}

Entity* Engine::GetEntityPtr() {
	return *(Entity**)GetPatch(xbLive.pPatches->BO1.GetEntityPtr);
}

Entity Engine::GetEntity(int index) {
	if (GetEntityPtr()) {
		return GetEntityPtr()[index];
	}

	return Entity();
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

bool Engine::IsAlive(int index, bool player) {
	auto entity = GetEntity(index);

	if (player) {
		if (entity.GetType() != ET_PLAYER && entity.GetType() != ET_VEHICLE_CORPSE)
			return false;
	}

	if ((entity._0x0318 & 0x40000000) == 0)
		return false;

	if (*(BYTE*)((DWORD)&entity + 2) == 0)
		return false;

	return true;
}

bool Engine::IsFriend(int index) {
	auto cg = GetCG();
	if (!cg) return false;

	return cg->ClientInfo[index].iTeam == cg->ClientInfo[cg->iClientNumber].iTeam && cg->ClientInfo[cg->iClientNumber].iTeam != 0;
}

int Engine::Com_GetClientDObj(int handle, int something) {
	return Invoke::Call<int>(GetPatch(xbLive.pPatches->BO1.Com_GetClientDObj), handle, something);
}

bool Engine::CG_DObjGetWorldTagPos(Entity* entity, int dObj, DWORD tag, Vector3<float>* out) {
	return Invoke::Call<bool>(GetPatch(xbLive.pPatches->BO1.CG_DObjGetWorldTagPos), entity, dObj, tag, out);
}

short Engine::SL_GetString(const char* name) {
	return Invoke::Call<short>(GetPatch(xbLive.pPatches->BO1.SL_GetString), name, 0, 0);
}

bool Engine::IsLookingAtMe(int index, float* pDegree) {
	return false;
}

float Engine::GetDistance(Vector3<float> from, Vector3<float> to) {
	float dx = to.X - from.X;
	float dy = to.Y - from.Y;
	float dz = to.Z - from.Z;
	return (float)sqrt((dx * dx) + (dy * dy) + (dz * dz));
}

bool Engine::CG_GetPlayerViewOrigin(int local, DWORD ps, Vector3<float>* origin) {
	return Invoke::Call<bool>(GetPatch(xbLive.pPatches->BO1.CG_GetPlayerViewOrigin), local, ps, origin);
}

float Engine::GetBoneFraction(int client, const char* tag) {
	Trace t;
	Vector3<float> visibleVec;

	auto cg = GetCG();
	if (!cg) return 0.f;

	DObj_s* dobj = (DObj_s*)Engine::Com_GetClientDObj(client, 0);
	if (!dobj) {
		return 0.f;
	}

	Vector3<float> pos;
	if (Engine::CG_DObjGetWorldTagPos(&GetEntity(client), (int)dobj, SL_GetString(tag), &pos)) {
		Vector3<float> myPos;
		CG_GetPlayerViewOrigin(0, Engine::GetCG()->GetPlayerState(), &myPos);

		CG_LocationalTrace(&t, &myPos, &pos, client, 0x803003, 0, 0);
		return t.fFraction;
	}

	return 0.f;
}

void Engine::CG_LocationalTrace(Trace *trace, Vector3<float> *start, Vector3<float> *end, int passEntityNum, int contMask, int u1, int u2) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->BO1.CG_LocationalTrace), trace, start, end, passEntityNum, contMask, u1, u2);
}

Vector3<float> Engine::GetTagPosition(int client, const char* tag, bool cached) {
	if (!IsAlive(client)) {
		return Vector3<float>(0.f, 0.f, 0.f);
	}

	int dobj = Engine::Com_GetClientDObj(client, 0);
	if (!dobj) {
		return Vector3<float>(0.f, 0.f, 0.f);
	}

	Vector3<float> out;
	if (Engine::CG_DObjGetWorldTagPos(&GetEntity(client), dobj, SL_GetString(tag), &out)) {
		return out;
	}

	return Vector3<float>(0.f, 0.f, 0.f);
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

	if (out->Z > 360.0f)
		out->Z -= 360.0f;
	if (out->Z < 0.0f)
		out->Z += 360.0f;
}

void Engine::FireBulletPenetrate(int local, BulletFireParams *bp, DWORD weaponNum, Entity* centity_s, Vector3<float>* Origin, DWORD one, bool unk, BulletTraceResults *br) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->BO1.FireBulletPenetrate), local, bp, weaponNum, centity_s, Origin, one, unk, br);
}

ClientActive* Engine::GetClientActive() {
	return *(ClientActive**)GetPatch(xbLive.pPatches->BO1.GetClientActive);
}

DWORD Engine::CG_GetWeaponIndexForName(const char* name) {
	return Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->BO1.CG_GetWeaponIndexForName), name);
}

Vector2<float> Engine::GetCenter() {
	return Vector2<float>(Engine::GetCG()->Refdef.vScale.X * 0.5f, Engine::GetCG()->Refdef.vScale.Y * 0.5f);
}

WeaponDef* Engine::GetWeaponDef(int weapon) {
	return Invoke::Call<WeaponDef*>(GetPatch(xbLive.pPatches->BO1.GetWeaponDef), weapon);
}

void Engine::CG_DrawGrenadePointer(int client, float centerX, float centerY, Vector3<float>* offset, float* color, float radiusOffset, float scaleFactor) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->BO1.CG_DrawGrenadePointer), client, centerX, centerY, offset, color, radiusOffset, scaleFactor);
}

void Engine::CG_DrawGrenadeIcon(int client, float centerX, float centerY, Vector3<float>* offset, float* color, Material* material, float radiusOffset, float scaleFactor) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->BO1.CG_DrawGrenadeIcon), client, centerX, centerY, offset, color, material, radiusOffset, scaleFactor);
}

void Engine::CL_SetStance(int local, int stance) {
	Invoke::Call<DWORD>(GetPatch(xbLive.pPatches->BO1.CL_SetStance), local, stance);
}

const char* Engine::Dvar_GetString(const char* str) {
	return Invoke::Call<const char*>(GetPatch(xbLive.pPatches->BO1.Dvar_GetString), str);
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

void Engine::CacheEquipmentIndexs() {
	const char* names[] = {
		"concussion_grenade_mp",
		"frag_grenade_mp",
		"willy_pete_mp",
		"sticky_grenade_mp",
		"sensor_grenade_mp",
		"hatchet_mp",
		"emp_grenade_mp",
		"bouncingbetty_mp",
		"proximity_grenade_mp",
		"satchel_charge_mp",
		"claymore_mp",
		"flash_grenade_mp",
		"trophy_system_mp",
		"tactical_insertion_mp",
		"scavenger_item_mp",
		"riotshield_mp"
	};

	for (int i = 0; i < 16; i++) {
		EquipmentWeaponIndexs[i] = CG_GetWeaponIndexForName(names[i]);
	}
}

bool Engine::IsWeaponEquipmentItem(int weapon) {
	for (int i = 0; i < 16; i++) {
		if (EquipmentWeaponIndexs[i] == weapon) {
			return true;
		}
	}

	return false;
}

bool Engine::IsWeaponThis(int weapon, eWeaponCheck check) {
	return weapon == EquipmentWeaponIndexs[check];
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

Material* Engine::GetWeaponMaterialWithAspect(int weapon, Vector2<float>* aspect) {
	auto weaponDef = GetWeaponDef(weapon);

	if (weaponDef) {
		GetWeaponKillIconAspect(weaponDef->GetKillIconType(), aspect);
		return weaponDef->GetKillIcon();
	}

	return nullptr;
}