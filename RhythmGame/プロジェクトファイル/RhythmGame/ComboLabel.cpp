#include "ComboLabel.h"
#include"ScreenSystem.h"
#include"SceneManager.h"
#include"dxlib/DxLib.h"

ComboLabel::ComboLabel()
{
	this->previous_miss_cnt = 0;
	this->current_miss_cnt = 0;
}

void ComboLabel::initialize()
{
	//�f�[�^�̏�����
	const int fontsize = 32;
	const int thick = 16;
	const int default_fontsize = 16;
	//�t�H���g(�e�L�X�g)�쐬-----------------------------------
	this->combo_label_header.font = create_font(fontsize, thick, false);
	this->combo_label_header.color = GetColor(255, 255, 255);
	this->combo_label_header.str = "Combo";
	this->combo_label_header.text_width = (int)strlen(this->combo_label_header.str);
	this->combo_label_header.pos = Point(ScreenData::width / 2 - ((this->combo_label_header.text_width * 32) / 2), ScreenData::height / 2 - fontsize);
	//�R���{��
	this->combo_label.font = create_font(fontsize, thick, false);
	this->combo_label.color = GetColor(255, 255, 255);
	this->combo_label.pos = Point(this->combo_label_header.pos.x, ScreenData::height / 2 + fontsize);
	//---------------------------------------------
	this->current_miss_cnt = 0;
	this->previous_miss_cnt = 0;
}

void ComboLabel::finalize()
{
	//�t�H���g�f�[�^��j��
	DeleteFontToHandle(this->combo_label_header.font);
	DeleteFontToHandle(this->combo_label.font);
}

void ComboLabel::update()
{
	//�̈����ւ�
	this->previous_miss_cnt = this->current_miss_cnt;
	this->current_miss_cnt = Counter::miss_cnt;
	//������̒������Ƃ�
	this->combo_label.text_width = (int)strlen(this->combo_label_header.str);
	//1�t���[���O�Ɣ�ׂă~�X�̐����Ⴄ�Ȃ�
	if (this->previous_miss_cnt != this->current_miss_cnt) {
		Counter::combo_cnt = 0;//�R���{��؂�
	}
}

void ComboLabel::draw(bool a_brend)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);//�u�����h���[�h��ݒ�
	this->combo_label_header.draw_font();//�����`�悷��
	//�R���{���\��
	std::string combonum = std::to_string(Counter::combo_cnt);
	this->combo_label.str = combonum.c_str();
	this->combo_label.draw_font();//�R���{���𕶎��`��
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//�u�����h���[�h���I�t
}
