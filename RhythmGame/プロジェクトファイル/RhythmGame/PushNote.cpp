#include "PushNote.h"
#include"Audio.h"
#include"SceneManager.h"
#include"Define.h"

JudgeResult PushNotes::judge()
{
	JudgeResult result = JudgeResult::none;

	//perfectのタイミングからどのくらいずれているかで判断する
	float absolute = abs(this->perfect_timing - this->key_down_timing);
	//誤差6フレーム以内なら
	if (absolute < 6) {
		//perfect判定
		result = JudgeResult::perfect;
		//perfect判定をした音を鳴らす
		Audio::play("perfect");
	}
	//誤差8フレーム以内なら
	else if (absolute < 8) {
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
		//判定ラインより上にいるなら
		else return result;//まだ判定を行わない
	}
	//判定結果を返す
	return result;
}

void PushNotes::initialize()
{
	this->anime = std::make_unique<Animation>();//メモリ確保
	if (this->anime == nullptr)throw "PushNotes anime is null_ptr";//メモリ確保できていないなら例外を投げる
	this->anime->set("tap_notes");
}
