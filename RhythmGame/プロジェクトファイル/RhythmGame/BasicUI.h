#pragma once
#include<iostream>
#include"Purpose.h"
#include"./dxlib/DxLib.h"

//UIに必要なものの定義

struct Text {
	Text();
	const char* str;//描画する文字
	int text_width;//テキストの長さ
	Point pos;//表示座標
	int font;//フォントハンドル
	int color;//色
	void set_font(const char* str, Point pos, int font, int color);
	void draw_font();
	template<typename T>
	void drawformat_font(T data);
};

int create_font(int size,int thick,bool is_anti_alias);


template<typename T>
void Text::drawformat_font(T data)
{
	DrawFormatStringToHandle(this->pos.x, this->pos.y, this->color, this->font, this->str, data);
}