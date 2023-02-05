#include "stdafx.h"

bool DefaultRequirement() { return true; }
void nullsub() {}
void nullsub2(const char*) {}

void Option::Render(int pos) {}
void Option::RenderSelected(int pos) {}
void Option::LoadConfig(string value) {}

ConfigSaveData Option::GetSaveData() {
	ConfigSaveData tmp;
	tmp.bPopulated = false;
	return tmp;
}