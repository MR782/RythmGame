#include "MusicSelectGuide.h"
#include"ScreenSystem.h"
#include<string.h>
#include"./dxlib/DxLib.h"

void MusicSelectGuide::initialize()
{
	//�Œ�f�[�^�̒�`
	const int font_size = 16;
	//�t�H���g�̍쐬
	this->guide_label.color = GetColor(0, 0, 0);
	this->guide_label.font = create_font(font_size, 16, false);
	this->guide_label.str = "DFJK ���x�ݒ�@���� �y�ȑI���@Enter ����";
	this->guide_label.text_width = (int)strlen(this->guide_label.str);
	this->guide_label.pos = Point(ScreenData::width / 2 - (this->guide_label.text_width * (font_size/ 2)) / 2, ScreenData::height - font_size);
}

void MusicSelectGuide::finalize()
{
	//�t�H���g�폜
	DeleteFontToHandle(this->guide_label.font);
}

void MusicSelectGuide::update()
{
}

void MusicSelectGuide::draw(bool a_brend)
{
	this->guide_label.draw_font();
}
