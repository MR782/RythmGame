#include "MusicSelectGuide.h"
#include"ScreenSystem.h"
#include<string.h>
#include"./dxlib/DxLib.h"

void MusicSelectGuide::initialize()
{
	//固定データの定義
	const int font_size = 16;
	//フォントの作成
	this->guide_label.color = GetColor(0, 0, 0);
	this->guide_label.font = create_font(font_size, 16, false);
	this->guide_label.str = "DFJK 速度設定　←→ 楽曲選択　Enter 決定";
	this->guide_label.text_width = (int)strlen(this->guide_label.str);
	this->guide_label.pos = Point(ScreenData::width / 2 - (this->guide_label.text_width * (font_size/ 2)) / 2, ScreenData::height - font_size);
}

void MusicSelectGuide::finalize()
{
	//フォント削除
	DeleteFontToHandle(this->guide_label.font);
}

void MusicSelectGuide::update()
{
}

void MusicSelectGuide::draw(bool a_brend)
{
	this->guide_label.draw_font();
}
