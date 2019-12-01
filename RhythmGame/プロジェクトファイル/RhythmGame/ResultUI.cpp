#include "ResultUI.h"
#include"Define.h"
#include"ScreenSystem.h"
#include"SceneManager.h"
#include"MemoryFunc.h"
#include"./dxlib/DxLib.h"

ResultUI::ResultUI()
{
	this->game_result = nullptr;
	this->guide = nullptr;
	this->rank = nullptr;
	this->scene_title = nullptr;
	this->score = nullptr;
}

void ResultUI::initialize()
{
	//UI---------------------------------------------------------------------------------------------
	{
		std::string name[judge_resultNum] = { "perfect","good","miss" };
		//要素数追加
		for (int i = 0; i < judge_resultNum; i++) {
			result.push_back(std::unique_ptr<Animation>());
		}
		//画像セット
		int i = 0;
		for (auto itr = result.begin(); itr != result.end(); itr++, i++) {
			(*itr) = std::make_unique<Animation>();//メモリ確保
			if ((*itr) == nullptr) throw"ResultUI result is null_ptr";
			(*itr)->set(name[i]);//画像セット
		}
	}
	//スコアUI--------------------------------------------------------------------------------------------
	this->score = new ScoreLabel();
	MemoryFunction::check_mem(this->score);
	this->score->initialize();
	this->score->set_position(Vector2((ScreenData::width / 2 - ui_graph_width / 2), ScreenData::height / 3));
	//ランク----------------------------------------------------------------------------------------------
	this->rank = new RankLabel();
	MemoryFunction::check_mem(this->rank);
	this->rank->initialize();
	//シーンタイトル--------------------------------------------------------------------------------
	this->scene_title = new ResultSceneTitle();
	MemoryFunction::check_mem(this->scene_title);
	this->scene_title->initialize();
	//ガイド-------------------------------------------------------------------------------------
	this->guide = new ResultGuide();
	MemoryFunction::check_mem(this->guide);
	this->guide->initialize();
	//フルコンボ表示------------------------------------------------------------------------------
	this->game_result = new GameResult();
	MemoryFunction::check_mem(this->guide);
	this->game_result->initialize();
	//ムービー--------------------------------------------------------------------------------------
	this->result_mv = std::make_unique<Movie>();
	if (this->result_mv == nullptr)throw"ResultUI movie is null_ptr";
	this->result_mv->set("reaf");
}

void ResultUI::finalize()
{
	//終了処理
	this->score->finalize();
	this->guide->finalize();
	this->scene_title->finalize();
	this->game_result->finalize();
	this->rank->finalize();
	//メモリ開放
	this->result.clear();
	delete this->score;
	delete this->guide;
	delete this->scene_title;
	delete this->game_result;
	delete this->rank;
}

void ResultUI::update()
{
	this->guide->update();
}

void ResultUI::draw()
{
	//葉っぱの描画
	this->result_mv->draw();
	//scenetitle--------------------------------------------------------
	this->scene_title->draw();
	//result--------------------------------------------------------------
	int cnt = 0;
	for (auto itr = result.begin(); itr != result.end(); itr++, cnt++) {
		Point pos((ScreenData::width / 2 - ui_graph_width / 2), ScreenData::height / 2 + (cnt * ui_graph_height));
		(*itr)->draw_anime(pos);
		int counter = 0;
		switch (cnt) {
		case 0:	counter = Counter::perfect_cnt;	break;
		case 1:	counter = Counter::good_cnt;	break;
		case 2:	counter = Counter::miss_cnt;	break;
		}
		//文字の描画
		DrawFormatString(pos.x + ui_graph_width, pos.y + (ui_graph_height / 3), GetColor(0, 0, 0), "%d", counter);
	}
	//score---------------------------------------------------------------------
	this->score->draw();
	//rank-----------------------------------------------------------------------
	this->rank->draw();
	//fullcomb,AllPerfect表示-----------------------------------------------------
	this->game_result->draw();
	//guide-----------------------------------------------------------------------
	this->guide->draw(true);
}
