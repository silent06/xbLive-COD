#pragma once

enum eJustify {
	JustifyLeft,
	JustifyCenter,
	JustifyRight
};

class Renderer {
public:
	struct Fonts {
		Font* bigDevFont;
		Font* smallDevFont;
		Font* consoleFont;
		Font* extraBigFont;
		Font* normalFont;
		Font* boldFont;
		Font* smallFont;
		Font* bigFont;
	} Fonts;

	struct Materials {
		Material* white;
		Material* map_grid_square;
		Material* compass_map_default;
		Material* tow_filter_overlay_no_signal;
		Material* objective_line;
		Material* compassping_dog;
		Material* compassping_player;
		Material* hud_scavenger_pickup;
	} Materials;

	void Initialize();

	void DrawTopRight(const char* text, int pos);
	float CalculateXValueWithAlign(float x, const char* text, Font* font, float scale, eJustify justify);
	string WordWrap(string txt, Font* font, float fontScale, int maxX, int* lines);
	int Clamp(int val, int min, int max);

	void DrawOutlinedRect(float x, float y, float w, float h, float thickness, Color boxColor, Color borderColor, bool sides = false);
	void DrawString(const char* text, float x, float y, Font* font, float scale, Color color, bool outlined, bool shadow, eJustify justify);
	void DrawShader(float x, float y, float width, float height, Color color, Material* material);
	void DrawRect(float x, float y, float width, float height, eJustify justify, Color color);
	void DrawLine(float X1, float Y1, float X2, float Y2, float width, Color color, Material* Shader);
	void DrawTitle(const char* pTitle);

	void Render();
	void RenderHeader();
	void RenderSubHeader();
	void RenderBackground();
	void RenderOptionHighlight();
	void RenderFooter();

	void Ease(float& toEase, float& easeFrom, float multiplier) {
		toEase += toEase < easeFrom ? fabs(toEase - easeFrom) / multiplier : -fabs(toEase - easeFrom) / multiplier;
	}

	void SetTooltip(string name) {
		strTooltip = name;
	}

	float fRenderOptions;
	float fOptionHeight;
	string strTooltip;
	int iTooltipLines;
};

extern Renderer pRenderer;