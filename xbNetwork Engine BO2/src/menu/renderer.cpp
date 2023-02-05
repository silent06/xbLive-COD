#include "stdafx.h"

Renderer pRenderer;

void Renderer::Initialize() {
	/*Materials*/
	Materials.white = Engine::R_RegisterMaterial("white", 0);
	Materials.specialty_scavenger = Engine::R_RegisterMaterial("specialty_scavenger", 0);

	/*Fonts*/
	Fonts.bigDevFont = Engine::R_RegisterFont("fonts/bigDevFont", 0);
	Fonts.smallDevFont = Engine::R_RegisterFont("fonts/smallDevFont", 0);
	Fonts.consoleFont = Engine::R_RegisterFont("fonts/720/consolefont", 0);
	Fonts.extraBigFont = Engine::R_RegisterFont("fonts/720/extrabigfont", 0);
	Fonts.normalFont = Engine::R_RegisterFont("fonts/720/normalfont", 0);
	Fonts.boldFont = Engine::R_RegisterFont("fonts/720/boldfont", 0);
	Fonts.smallFont = Engine::R_RegisterFont("fonts/720/smallfont", 0);
	Fonts.bigFont = Engine::R_RegisterFont("fonts/720/bigfont", 0);

	fOptionHeight = 21.f;
}

void Renderer::DrawTopRight(const char* text, int pos) {
	int textWidth = Engine::R_TextWidth(text, Fonts.normalFont);
	DrawOutlinedRect(1260.f - (textWidth * 0.54f), (pos * 29.f), (textWidth * 0.54f) + 10.f, 22.f, 3, Color(0, 0, 0, 100), Color(160, 57, 64, 150), true);
	DrawString(text, CalculateXValueWithAlign(1265.f, text, Fonts.normalFont, 0.54f, JustifyLeft), 20.f + (pos * 29.f), Fonts.normalFont, 0.54f, Color(0xFFFFFFFF), false, false, JustifyRight);
}

float Renderer::CalculateXValueWithAlign(float x, const char* text, Font* font, float scale, eJustify justify) {
	if (justify == JustifyLeft)
		return x;
	if (justify == JustifyCenter)
		return x - (Engine::R_TextWidth(text, font) / 2 * scale);
	if (justify == JustifyRight)
		return x - (Engine::R_TextWidth(text, font) * scale);

	return 0;
}

string Renderer::WordWrap(string text, Font* font, float fontScale, int maxX, int* lines) {
	*lines = 1;

	vector<int> newLines(1);

	if (strstr(text.c_str(), "\n")) {
		for (size_t i = 0; i < text.length(); i++) {
			string newstr = text.substr(0, i);
			int pos = newstr.find_last_of("\n");
			if (pos > 1) {
				auto vit = find(newLines.begin(), newLines.end(), pos);
				if (vit == newLines.end()) {
					newLines.push_back(pos);
					*lines = *lines + 1;
				}
			}
		}
	}

	int curPos = 0;
	string query = text;

loop:
	auto len = Engine::R_TextWidth(query.c_str(), font) * fontScale;
	if (len >= maxX) {
		for (int i = 0; i < query.size(); i++) {
			auto str = query.substr(0, i);
			len = Engine::R_TextWidth(str.c_str(), font) * fontScale;
			if (len >= maxX) {
				auto lastSpace = str.find_last_of(' ');
				if (lastSpace) {
					text[curPos + lastSpace] = '\n';
					curPos += lastSpace;
					query = text.substr(curPos);
					*lines = *lines + 1;
					goto loop;
				}
			}
		}
	}

	return text;
}

int Renderer::Clamp(int val, int min, int max) {
	return val < min ? min : val > max ? max : val;
}

void Renderer::DrawString(const char* text, float x, float y, Font* font, float scale, Color color, bool outlined, bool shadow, eJustify justify) {
	float defaultX = CalculateXValueWithAlign(x, text, font, scale, justify);

	Engine::R_AddCmdDrawText(text, 0x7FFFFFFF, font, defaultX, y, scale, scale, 0.f, color.GetFloatPtr(), 0);

	if (outlined) {
		Engine::R_AddCmdDrawText(text, 0x7FFFFFFF, font, defaultX, y, scale + 0.02f, scale + 0.02f, 0.f, Color(0, 0, 0, 255).GetFloatPtr(), 0);
	}

	if (shadow) {
		Engine::R_AddCmdDrawText(text, 0x7FFFFFFF, font, defaultX + 3.f, y + 3.f, scale, scale, 0.f, Color(0, 0, 0, 255).GetFloatPtr(), 0);
	}
}

void Renderer::DrawOutlinedRect(float x, float y, float w, float h, float thickness, Color boxColor, Color borderColor, bool sides) {
	Engine::R_AddCmdDrawStretchPic(x, y, w, h, 1.f, 1.f, 1.f, 1.f, boxColor.GetFloatPtr(), Materials.white); // bg 
	Engine::R_AddCmdDrawStretchPic(x, y - thickness, w, thickness, 1, 1, 1, 1, borderColor.GetFloatPtr(), Materials.white); // top bar
	Engine::R_AddCmdDrawStretchPic(x, y + h, w, thickness, 1, 1, 1, 1, borderColor.GetFloatPtr(), Materials.white); // bottom bar

	if (sides) {
		Engine::R_AddCmdDrawStretchPic(x - thickness, y - thickness, thickness, h + (thickness * 2), 1, 1, 1, 1, borderColor.GetFloatPtr(), Materials.white); // left bar
		Engine::R_AddCmdDrawStretchPic(x + w, y - thickness, thickness, h + (thickness * 2), 1, 1, 1, 1, borderColor.GetFloatPtr(), Materials.white); // right bar
	}
}

void Renderer::DrawShader(float x, float y, float width, float height, Color color, Material* material) {
	Engine::R_AddCmdDrawStretchPic(x, y, width, height, 1, 1, 1, 1, color.GetFloatPtr(), material);
}

void Renderer::DrawLine(float X1, float Y1, float X2, float Y2, float width, Color color, Material* Shader) {
	float X, Y, Angle, L1, L2, H1;
	H1 = Y2 - Y1;
	L1 = X2 - X1;
	L2 = sqrt(L1 * L1 + H1 * H1);
	X = X1 + ((L1 - L2) / 2);
	Y = Y1 + (H1 / 2);
	Angle = (float)atan(H1 / L1) * (180.f / 3.14159265358979323846f);
	Engine::CG_DrawRotatedPicPhysical(GetPatch(xbLive.pPatches->BO2.ScreenPlacement), X, Y, L2, width, Angle, color.GetFloatPtr(), Shader);
}

void Renderer::DrawTitle(const char* pTitle) {
	DrawString(pTitle, pMenu.vCenter.X, 149.f, Fonts.normalFont, 0.45f, Color(0xFFFFFFFF), false, false, JustifyCenter);
}

void Renderer::DrawRect(float x, float y, float width, float height, eJustify justify, Color color) {
	if (justify == JustifyLeft) {
		DrawShader(x, y, width, height, color, Materials.white);
	}

	if (justify == JustifyCenter) {
		DrawShader(x - (width / 2), y, width, height, color, Materials.white);
	}

	if (justify == JustifyRight) {
		DrawShader(x - width, y, width, height, color, Materials.white);
	}
}

void Renderer::Render() {
	RenderHeader();
	RenderSubHeader();
	RenderBackground();
	RenderOptionHighlight();
	RenderFooter();
}

void Renderer::RenderOptionHighlight() {
	pMenu.iCurrentRenderingScroll = Clamp(pMenu.iCurrentOption - pMenu.iScrollOffset > pMenu.iMaxOptions ? pMenu.iMaxOptions : (pMenu.iCurrentOption - pMenu.iScrollOffset) + 1, 0, pMenu.iMaxOptions);

	float width = 425;

	int Y_coord = Clamp(pMenu.iCurrentOption - pMenu.iScrollOffset > pMenu.iMaxOptions ? pMenu.iMaxOptions : pMenu.iCurrentOption - pMenu.iScrollOffset, 0, pMenu.iMaxOptions);
	auto scrollYCoord = 176 + (Y_coord) * fOptionHeight;

	DrawRect(pMenu.vCenter.X - (width / 2), scrollYCoord, width, fOptionHeight, JustifyLeft, Color(160, 57, 56, 200)); // scroller
}

void Renderer::RenderHeader() {
	float width = 425;
	DrawOutlinedRect(pMenu.vCenter.X - (width / 2), pMenu.vCenter.Y - 209 - 25 + 2 + 4, width, 18, 1, Color(0, 0, 0, 150), Color(160, 57, 56));

	DrawString("xbLive.online", 433.f, 149.f, Fonts.normalFont, 0.45f, Color(0xFFFFFFFF), false, false, JustifyLeft);
	DrawString("v1.0a", 845.f, 149.f, Fonts.normalFont, 0.45f, Color(0xFFFFFFFF), false, false, JustifyRight);
}

void Renderer::RenderSubHeader() {
	float width = 425;
	DrawRect(pMenu.vCenter.X - (width / 2), pMenu.vCenter.Y - 209, width, 23, JustifyLeft, Color(0x2C2727DC));

	float tabSpace = width / 6; // 6 tabs

	pRenderer.DrawRect(pMenu.vCenter.X - (width / 2) + (tabSpace * pMenu.iSelectedTab), 149 + 2, tabSpace, 23 - 2, JustifyLeft, Color(160, 57, 56));
	pRenderer.DrawRect(pMenu.vCenter.X - (width / 2) + (tabSpace * pMenu.iSelectedTab), 172, tabSpace, 2, JustifyLeft, Color(199, 71, 70));

	DrawString("Main", 391.5 + (tabSpace * 1), 170, Fonts.normalFont, 0.60f, Color(0xFFFFFFFF), false, false, JustifyCenter);
	DrawString("Aimbot", 391.5 + (tabSpace * 2), 170, Fonts.normalFont, 0.60f, Color(0xFFFFFFFF), false, false, JustifyCenter);
	DrawString("HvH", 391.5 + (tabSpace * 3), 170, Fonts.normalFont, 0.60f, Color(0xFFFFFFFF), false, false, JustifyCenter);
	DrawString("Visuals", 391.5 + (tabSpace * 4), 170, Fonts.normalFont, 0.60f, Color(0xFFFFFFFF), false, false, JustifyCenter);
	DrawString("Players", 391.5 + (tabSpace * 5), 170, Fonts.normalFont, 0.60f, Color(0xFFFFFFFF), false, false, JustifyCenter);
	DrawString("Settings", 391.5 + (tabSpace * 6), 170, Fonts.normalFont, 0.60f, Color(0xFFFFFFFF), false, false, JustifyCenter);
}

void Renderer::RenderBackground() {
	float width = 425;

	fRenderOptions = (float)(pSubmenuHandler.GetTotalOptions() > pMenu.iMaxOptions ? pMenu.iMaxOptions : pSubmenuHandler.GetTotalOptions());

	DrawRect(pMenu.vCenter.X - (width / 2), 174, width, (fRenderOptions * fOptionHeight) + 3, JustifyLeft, Color(0, 0, 0, 130));
}

void Renderer::RenderFooter() {
	auto y = 174 + (fRenderOptions * fOptionHeight) + 4;

	float width = 425;
	if (strTooltip.length() == 0) {
		DrawOutlinedRect(pMenu.vCenter.X - (width / 2), y, width, 18, 1, Color(0, 0, 0, 130), Color(160, 57, 56));
	} else {
		string tip = WordWrap(strTooltip, Fonts.normalFont, 0.60f, width - 10, &iTooltipLines);
		DrawOutlinedRect(pMenu.vCenter.X - (width / 2), y, width, iTooltipLines == 1 ? fOptionHeight * 1.35f : iTooltipLines * (fOptionHeight * 1.1f), 1, Color(0, 0, 0, 150), Color(160, 57, 56));
		DrawString(tip.c_str(), pMenu.vCenter.X - (width / 2) + 8, y + 22, Fonts.normalFont, 0.60f, Color(0xFFFFFFFF), false, false, JustifyLeft);
	}
}
