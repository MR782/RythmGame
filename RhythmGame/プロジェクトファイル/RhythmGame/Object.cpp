#include "Object.h"
#include"./dxlib/DxLib.h"

void Object::check_brendCnt()
{
	if (this->blend_cnt >= 255) this->b_state = BlendState::Subtraction;//Maxまでいったら減少開始
	else if (this->blend_cnt <= 0) this->b_state = BlendState::Addition;//Minまで行ったら増加開始
}

Object::Object()
{
	this->blend_cnt = 0;
	this->b_state = BlendState::Subtraction;
}

void Object::draw(bool a_brend)
{
	if (this->anime == nullptr) throw "anime is null_ptr";//メモリ確保できていないなら例外を投げる
	if(a_brend) SetDrawBlendMode(DX_BLENDMODE_ALPHA, this->blend_cnt);//ブレンドモードを設定
	this->anime->draw_anime(this->position);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//ブレンドモードをオフ
}

Vector2 Object::get_position()
{
	return this->position;
}
