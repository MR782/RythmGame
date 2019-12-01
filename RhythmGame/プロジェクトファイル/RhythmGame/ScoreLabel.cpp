#include "ScoreLabel.h"
#include"Define.h"
#include"ScreenSystem.h"
#include"Necessary.h"
#include"./dxlib/DxLib.h"

void ScoreLabel::initialize()
{
	//初期化
	this->anime = std::make_unique<Animation>();//メモリ確保
	if (this->anime == nullptr) throw "ScoreLabel anime is null_ptr";//メモリ確保できなかったなら
	this->anime->set("score");//画像をセット
	this->position = Vector2((ScreenData::width / 10 - ui_graph_width / 2), ScreenData::height / 5);
}

void ScoreLabel::finalize()
{
	this->anime.reset();//メモリ開放
}

void ScoreLabel::update()
{
}

void ScoreLabel::draw(bool a_brend)
{
	this->anime->draw_anime(this->position);
	//文字を描画
	DrawFormatString((int)this->position.x, (int)this->position.y + ui_graph_height, GetColor(0, 0, 0), " %d ", Necessary::get_score());
}

void ScoreLabel::set_position(Vector2 pos)
{
	//座標セット
	this->position = pos;
}
