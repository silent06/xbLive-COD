#include "stdafx.h"

void Submenu::MenuUpdate() {
	Update();
	if (pName) pRenderer.DrawTitle(pName);

	pSubmenuHandler.iCurrentOptionsWithoutBreaks = 0;
	pSubmenuHandler.iTotalOptionsWithoutBreaks = 0;
	pSubmenuHandler.iTotalOptions = 0;

	vector<shared_ptr<Option>> tempOptions;
	tempOptions.reserve(Options.size());

	if (Options.size() > 0) {
		int relativeOptionPosition = 0, visibilityOffset = 0;

		for (size_t i = 0; i < Options.size(); i++) {
			if (Options.at(i)->IsVisible()) {
				tempOptions.push_back(Options.at(i));
				visibilityOffset++;
				pSubmenuHandler.iTotalOptions++;
				if (visibilityOffset <= pMenu.iCurrentOption) pSubmenuHandler.iCurrentOptionsWithoutBreaks++;
				pSubmenuHandler.iTotalOptionsWithoutBreaks++;
			}
		}

		for (int i = pMenu.iScrollOffset; i < pMenu.iScrollOffset + pMenu.iMaxOptions; i++) {
			if (i >= 0 && i < tempOptions.size()) {
				if (relativeOptionPosition >= pMenu.iMaxOptions) break;
				tempOptions.at(i)->Render(relativeOptionPosition);
				if (relativeOptionPosition == pMenu.iCurrentOption - pMenu.iScrollOffset) {
					Option* option = tempOptions.at(i).get();
					pRenderer.SetTooltip(option->GetTooltip());
					if (pMenu.IsOpen() && !IsOpenPressed()) option->RenderSelected(relativeOptionPosition);
				} relativeOptionPosition++;
			}
		}
	}
}

void Submenu::Init() {}
void Submenu::UpdateOnce() {}
void Submenu::Update() {}
void Submenu::FeatureUpdate() {}