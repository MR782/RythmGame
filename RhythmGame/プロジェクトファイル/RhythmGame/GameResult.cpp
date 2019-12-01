#include "GameResult.h"
#include"ScreenSystem.h"
#include"Define.h"
#include"SceneManager.h"

void GameResult::initialize()
{
	//データ初期化
	this->anime = std::make_unique<Animation>();//メモリ確保
	this->position = Vector2(ScreenData::width / 2 + fullcombo_graph_width / 2, ScreenData::height / 2 + fullcombo_graph_height * 2);
	if (this->anime == nullptr) throw "GameResult anime is null_ptr";//メモリ確保できていないなら例外を投げる
	this->anime->set("");//空の画像をセット
	//ミス数が0で
	if (Counter::miss_cnt == 0) {
		//goodも0なら
		if (Counter::good_cnt == 0) {
			//AllPerfectとする
			this->anime->set("all_perfect");
		}
		//goodがあるなら
		else {
			//FullComboと表示
			this->anime->set("full_combo");
		}
	}
}

void GameResult::finalize()
{
	this->anime.reset();
}

void GameResult::update()
{
}
