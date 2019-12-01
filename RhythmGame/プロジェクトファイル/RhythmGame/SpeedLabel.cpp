#include "SpeedLabel.h"
#include"Necessary.h"
#include"ScreenSystem.h"
#include<string.h>
#include"./dxlib/DxLib.h"

void SpeedLabel::initialize()
{
	const int font_size = 32;
	//文字
	this->speed_label_header.color = GetColor(0, 0, 0);
	this->speed_label_header.font = create_font(font_size, 16, false);
	this->speed_label_header.str = "Speed : ";
	this->speed_label_header.text_width = (int)strlen(this->speed_label_header.str);
	this->speed_label_header.pos = Point((ScreenData::width / 2) - ((font_size * (this->speed_label_header.text_width / 2))),ScreenData::height - (font_size * 2));
	//スピード表示
	this->speed_label.color = GetColor(0, 0, 0);
	this->speed_label.font = create_font(font_size, 16, false);
	this->speed_label.str = "%d";
	this->speed_label.text_width = (int)strlen(this->speed_label.str);
	this->speed_label.pos = Point(this->speed_label_header.pos.x + (font_size * (this->speed_label_header.text_width / 2)), this->speed_label_header.pos.y);
}

void SpeedLabel::finalize()
{
	DeleteFontToHandle(this->speed_label.font);
}

void SpeedLabel::update()
{
}

void SpeedLabel::draw(bool flag)
{
	this->speed_label_header.draw_font();
	this->speed_label.drawformat_font(Necessary::get_speed());
}
