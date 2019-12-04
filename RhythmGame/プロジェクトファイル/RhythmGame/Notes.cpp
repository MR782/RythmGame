#include "Notes.h"
#include"KeyBoard.h"
#include"Mouse.h"
#include"GameScene.h"
#include"ScreenSystem.h"
#include"Necessary.h"
#include"Audio.h"
#include"Define.h"
#include"./dxlib/DxLib.h"

Notes::Notes() : Object()
{
	this->active = true;
	this->judge_key = JudgeKey::Key_D;
	this->judge_result = JudgeResult::none;
	this->key_down_timing = 0;
	this->is_first = false;
	this->perfect_timing = 0;
}

void Notes::initialize()
{
	throw" called super class method";
}

void Notes::finalize()
{
	this->anime.reset();
}

void Notes::update()
{
	move();
	//自分の判定キーが押されたら現在のゲームカウントをキーを押したタイミングとして登録
	if (this->check_key()) {
		this->key_down_timing = Counter::game_cnt;
	}
	this->judge_result = this->judge();
	//判定結果が出ているなら
	if (this->judge_result != JudgeResult::none) this->active = false;//存在を消す
}

void Notes::set_is_first(bool flag)
{
	this->is_first = flag;
}

bool Notes::get_active()
{
	return this->active;
}

JudgeResult Notes::get_result()
{
	return this->judge_result;
}

JudgeKey Notes::get_judge_key()
{
	return this->judge_key;
}

void Notes::set_contents(float timing, JudgeKey j_key)
{
	this->judge_key = j_key;
	//判定キーによって初期座標を変える
	float posY = 0 + 1 * ((this->perfect_timing - Counter::game_cnt) * -(Model::judge_line->get_position().y) * 1);
	this->position =
		Vector2((float)((ScreenData::width / 2) - (judge_line_width / 2) + (int)(this->judge_key)* note_width),
			             posY);
	//移動量とタイミングをセットする
	this->perfect_timing = timing;
}

void Notes::move()
{
	//終点の位置 + 終点から始点への方向 * ((判定ラインにくる時間 - 曲の再生時間)*レーンの長さ*スピード);                                    
	float posY = Model::judge_line->get_position().y + ((this->perfect_timing - Counter::game_cnt)
		* -(Model::judge_line->get_position().y) * (0.001f * Necessary::get_speed()));
	this->position.y = posY;
}

JudgeResult Notes::judge()
{
	JudgeResult result = JudgeResult::none;

	//perfectのタイミングからどのくらいずれているかで判断する
	float absolute = abs(this->perfect_timing - this->key_down_timing);
	//誤差3フレーム以内なら
	if (absolute < 3) {
		//perfect判定
		result = JudgeResult::perfect;
		//perfect判定をした音を鳴らす
		Audio::play("perfect");
	}
	//誤差5フレーム以内なら
	else if (absolute < 5) {
		//good判定	
		result = JudgeResult::good;
		//good判定をした音を鳴らす
		Audio::play("good");
	}
	//それよりずれているなら-----------------------
	else {
		if (this->position.y > Model::judge_line->get_position().y + judge_line_height) {
			//下にいるならミスにする
			result = JudgeResult::miss;
			//ミスした音を鳴らす
			Audio::play("miss");
		}
		else return result;//まだ判定を行わない
	}
	//判定結果を返す
	return result;
}

bool Notes::check_key()
{
	bool check_key = false;
	//判定キーによって処理を変える---------------------
	switch (this->judge_key)
	{
	case JudgeKey::Key_D:
		check_key = KeyBoard::key_down(KEY_INPUT_D);
		break;
	case JudgeKey::Key_F:
		check_key = KeyBoard::key_down(KEY_INPUT_F);
		break;
	case JudgeKey::Key_J:
		check_key = KeyBoard::key_down(KEY_INPUT_J);
		break;
	case JudgeKey::Key_K:
		check_key = KeyBoard::key_down(KEY_INPUT_K);
		break;
	}
	return check_key;
}
