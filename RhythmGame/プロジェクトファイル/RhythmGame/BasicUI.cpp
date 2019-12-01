#include "BasicUI.h"
#include"Mouse.h"
#include"Necessary.h"

int create_font(int size, int thick, bool is_anti_alias)
{
	int handle;
	//アンチエイリアスを使用するなら
	if (is_anti_alias) {
		handle = CreateFontToHandle("", size, thick, DX_FONTTYPE_ANTIALIASING);
	}
	else {
		handle = CreateFontToHandle("", size, thick, DX_FONTTYPE_NORMAL);
	}
	return handle;
}

Text::Text()
{
	this->color = 0;
	this->font = 0;
	this->text_width = 0;
	this->str = "";
	this->pos = { 0,0 };
}

void Text::set_font(const char* str, Point pos, int font, int color)
{
	this->str = str;
	this->pos = pos;
	this->font = font;
	this->color = color;
}

void Text::draw_font()
{
	DrawStringToHandle(this->pos.x, this->pos.y, this->str, this->color, this->font);
}

