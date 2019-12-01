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
	//データの初期化
	const int fontsize = 32;
	const int thick = 16;
	const int default_fontsize = 16;
	//フォント(テキスト)作成-----------------------------------
	this->combo_label_header.font = create_font(fontsize, thick, false);
	this->combo_label_header.color = GetColor(255, 255, 255);
	this->combo_label_header.str = "Combo";
	this->combo_label_header.text_width = (int)strlen(this->combo_label_header.str);
	this->combo_label_header.pos = Point(ScreenData::width / 2 - ((this->combo_label_header.text_width * 32) / 2), ScreenData::height / 2 - fontsize);
	//コンボ数
	this->combo_label.font = create_font(fontsize, thick, false);
	this->combo_label.color = GetColor(255, 255, 255);
	this->combo_label.pos = Point(this->combo_label_header.pos.x, ScreenData::height / 2 + fontsize);
	//---------------------------------------------
	this->current_miss_cnt = 0;
	this->previous_miss_cnt = 0;
}

void ComboLabel::finalize()
{
	//フォントデータを破棄
	DeleteFontToHandle(this->combo_label_header.font);
	DeleteFontToHandle(this->combo_label.font);
}

void ComboLabel::update()
{
	//領域入れ替え
	this->previous_miss_cnt = this->current_miss_cnt;
	this->current_miss_cnt = Counter::miss_cnt;
	//文字列の長さをとる
	this->combo_label.text_width = (int)strlen(this->combo_label_header.str);
	//1フレーム前と比べてミスの数が違うなら
	if (this->previous_miss_cnt != this->current_miss_cnt) {
		Counter::combo_cnt = 0;//コンボを切る
	}
}

void ComboLabel::draw(bool a_brend)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);//ブレンドモードを設定
	this->combo_label_header.draw_font();//文字描画する
	//コンボ数表示
	std::string combonum = std::to_string(Counter::combo_cnt);
	this->combo_label.str = combonum.c_str();
	this->combo_label.draw_font();//コンボ数を文字描画
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//ブレンドモードをオフ
}
