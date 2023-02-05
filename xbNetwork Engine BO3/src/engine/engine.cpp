#include "stdafx.h"

int Engine::EquipmentWeaponIndexs[16];

Material* Engine::R_RegisterMaterial(const char* pFont, int iImageTrack) {
	return Invoke::Call<Material*>(0x82328110, 0x06, pFont, iImageTrack); 
}

Font* Engine::R_RegisterFont(const char* pFont, int iImageTrack) {
	return Invoke::Call<Font*>(0x82328110, 0x14, pFont, iImageTrack); 
}

void Engine::R_AddCmdDrawStretchPic(float x, float y, float width, float height, float xScale, float yScale, float xay, float yay, const float * color, Material* material) {
	Invoke::Call<DWORD>(0x824AE300, x, y, width, height, xScale, yScale, xay, yay, color, material); 
}

void Engine::R_AddCmdDrawText(const char *text, int maxChars, Font *font, float x, float y, float xScale, float yScale, const float *color, int style) {
	Invoke::Call<DWORD>(0x824AE7C0, text, maxChars, font, x, y, xScale, yScale, color, style); 
}

int Engine::R_TextWidth(const char* text, Font* font) {
	if (font == nullptr) return 0;
	return Invoke::Call<int>(0x824A1000, text, 0x7FFFFFFF, font, 0); 
}

void Engine::CG_DrawRotatedPicPhysical(int scrPlacement, float x, float y, float width, float height, float angle, const float* color, Material* material) {
	Invoke::Call<DWORD>(0x82210468, scrPlacement, x, y, width, height, angle, color, material, 0); 
}

int Engine::R_TextHeight(Font* font) {
	return font->iPixelHeight;
}

int Engine::R_NormalizedTextScale(Font* font, float scale) {
	return ((scale * 48) / R_TextHeight(font)); 
}

bool Engine::InGame() {
	int result;
	int *IntStack[10];
	IntStack[9] = &result;
	Invoke::Call<DWORD>(0x825D5A70, IntStack); 
	return result != 0 && GetCG() != nullptr;
}

cg* Engine::GetCG() {
	return *(cg**)0x82E819D8; 
}

ServerInfo* Engine::GetServerInfo() {
	return *(ServerInfo**)0x82E819C0; 
}

DWORD Engine::GetNetInfoAddress(int index) {
	return (0x82B7E640 + (index * 0x350)); 
}

DWORD Engine::TimeGetTime() {
	return Invoke::Call<DWORD>(0x826EEC98); 
}

const char* Engine::GetNameFromNetInfo(int index) {
	return (char*)(GetNetInfoAddress(index)); 
}

BYTE* Engine::GetIPFromNetInfo(int index) {
	return (BYTE*)(GetNetInfoAddress(index) + 0x29C); 
}

QWORD Engine::GetXUIDFromNetInfo(int index, BOOL read) {
	return GetNetInfoAddress(index) + 0x2E8; 
}

QWORD Engine::GetMachineIDFromNetInfo(int index) {
	return _byteswap_uint64(*(QWORD*)(GetNetInfoAddress(index) + 0x74)); 
}

void Engine::Cbuf_AddText(int localClient, const char* msg) {
	Invoke::Call<DWORD>(0x8263A6A0, localClient, msg); 
}

void Engine::BG_GetSpreadForWeapon(DWORD ps, WeaponDef* weapon, float* minSpread, float* maxSpread) {
	Invoke::Call<DWORD>(0x821DC870, ps, weapon, minSpread, maxSpread); 
}

double Engine::BG_Random(int*seed) { 
	int ye = 0x343FD * *seed + 0x269EC3;
	*seed = ye;
	return (double)(ye >> 17) * 0.000030517578;
}

float Engine::RandomBulletDir(int* randomSeed, float* x, float* y) { 
	float theta = (BG_Random(randomSeed) * 360.0f) * 0.01745329251;
	float radius = BG_Random(randomSeed);
	*x = radius * cos(theta);
	*y = radius * sin(theta);
}

Entity* Engine::GetEntityPtr() {
	return *(Entity**)0x82E819EC; 
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
	return GetEntity(index).IsAlive();
}

bool Engine::IsFriend(int index) {
	auto cg = GetCG();
	if (!cg) return false;

	return cg->ClientInfo[index].iTeam == cg->ClientInfo[cg->iClientNumber].iTeam && cg->ClientInfo[cg->iClientNumber].iTeam != 0;
}

int Engine::Com_GetClientDObj(int handle, int something) { 
	int DObj_s = *(short *)(0x83EC1440 + ((handle + (something * 0x4C1)) << 1));

	if (!DObj_s)
		return 0;

	return 0x83E71440 + (DObj_s * 0xA0);
}

bool Engine::CG_DObjGetWorldTagPos(Entity* entity, int dObj, DWORD tag, Vector3<float>* out) {
	return Invoke::Call<bool>(0x8221ACF0, entity, dObj, tag, out); 
}

short Engine::SL_GetString(const char* name) {
	return Invoke::Call<short>(0x822D2248, name, 0, strlen(name) + 1, 8); 
}

bool Engine::IsLookingAtMe(int index, float* pDegree) {
	return false;
}

float Engine::GetDistance(Vector3<float> from, Vector3<float> to) {
	float dx = to.X - from.X;
	float dy = to.Y - from.Y;
	float dz = to.Z - from.Z;
	return (float)sqrt((dx * dx) + (dy * dy) + (dz * dz)) * 0.03048f;
}

bool Engine::CG_GetPlayerViewOrigin(int local, DWORD ps, Vector3<float>* origin) {
	return Invoke::Call<bool>(0x822730E0, local, ps, origin); 
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
		CG_GetPlayerViewOrigin(0, *(int*)0x844C1BC0, &myPos); 

		CG_LocationalTrace(&t, &myPos, &pos, client, 0x818011, 0, 0);
		return t.fFraction;
	}

	return 0.f;
}

void Engine::CG_LocationalTrace(Trace *trace, Vector3<float> *start, Vector3<float> *end, int passEntityNum, int contMask, int u1, int u2) {
	Invoke::Call<DWORD>(0x82285838, trace, start, end, passEntityNum, contMask, u1, u2); 
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

void Engine::FireBulletPenetrate(int local, BulletFireParams *bp, DWORD weaponNum, DWORD unk0, Vector3<float> *tracerStart, DWORD unk1, BulletTraceResults *bulletTraceResults) {
	Invoke::Call<DWORD>(0x82272708, local, bp, weaponNum, unk0, tracerStart, unk1, bulletTraceResults); 
}

ClientActive* Engine::GetClientActive() {
	return *(ClientActive**)0x84475F74; 
}

DWORD Engine::CG_GetWeaponIndexForName(const char* name) {
	return Invoke::Call<DWORD>(0x821F7718, name, 0); 
}

Vector2<float> Engine::GetCenter() {
	return Vector2<float>(Engine::GetCG()->Refdef.vScale.X * 0.5f, Engine::GetCG()->Refdef.vScale.Y * 0.5f);
}

WeaponDef* Engine::GetWeaponDef(int weapon) {
	return (WeaponDef*)*(DWORD*)(0x82DE5E60 + (((weapon * 4) & 0xFFFFFFFC) & 0x3FC)); 
}

void Engine::CG_DrawGrenadePointer(int client, float centerX, float centerY, Vector3<float>* offset, float* color, float radiusOffset, float scaleFactor) {
	Invoke::Call<DWORD>(0x82211FD0, client, centerX, centerY, offset, color, radiusOffset, scaleFactor); 
}

void Engine::CG_DrawGrenadeIcon(int client, float centerX, float centerY, Vector3<float>* offset, float* color, Material* material, float radiusOffset, float scaleFactor) {
	Invoke::Call<DWORD>(0x82212160, client, centerX, centerY, offset, color, material, radiusOffset, scaleFactor); 
}

void Engine::CL_SetStance(int local, int stance) {
	Invoke::Call<DWORD>(0x822362F0, local, stance); 
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
	/*auto weaponDef = GetWeaponDef(weapon);

	if (weaponDef) {
		GetWeaponKillIconAspect(weaponDef->GetKillIconType(), aspect);
		return weaponDef->GetKillIcon();
	}*/

	return nullptr;
}