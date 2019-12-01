#include "ResultGuide.h"
#include"ScreenSystem.h"
#include"Define.h"
#include"./dxlib/DxLib.h"

ResultGuide::ResultGuide()
{
	this->blend_cnt = 255;
	this->b_state = BlendState::Subtraction;
}

void ResultGuide::initialize()
{
	//データ初期化
	this->blend_cnt = 255;
	this->b_state = BlendState::Subtraction;
	this->position = Vector2(ScreenData::width / 2 - result_guide_width / 2, ScreenData::height - result_guide_height * 2);
	this->anime = std::make_unique<Animation>();//メモリ確保
	if (this->anime == nullptr) throw "ResultGuide anime is null_ptr";//メモリ確保できていないなら例外を投げる
	this->anime->set("result_guide");
}

void ResultGuide::finalize()
{
	this->anime.reset();
}

void ResultGuide::update()
{
	//αブレンド用のカウンタ
	if (this->b_state == BlendState::Addition) this->blend_cnt += blend_speed;
	else if (this->b_state == BlendState::Subtraction) this->blend_cnt -= blend_speed;
	check_brendCnt();
}
