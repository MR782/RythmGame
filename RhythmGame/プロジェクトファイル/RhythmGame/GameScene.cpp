#include "GameScene.h"
#include"Necessary.h"
#include"Audio.h"
#include"GraphicResource.h"
#include"ScreenSystem.h"
#include"ScreenFunction.h"
#include"SceneManager.h"
#include"Define.h"
#include"MemoryFunc.h"
#include"./dxlib/DxLib.h"

//カウンタ
float Counter::game_cnt;
int Counter::perfect_cnt;
int Counter::good_cnt;
int Counter::miss_cnt;
int Counter::notes_num;
int Counter::combo_cnt;
//モデル
std::vector<std::unique_ptr<Notes>> Model::notes;
JudgeLine* Model::judge_line;
std::vector<std::unique_ptr<JudgeResultUI>> Model::judge_results;

Game::Game() :Scene()
{
	this->game_ui = nullptr;
	this->notes_creater = nullptr;
	this->result_creater = nullptr;
	this->start_time.QuadPart = 0;
	this->now_time.QuadPart = 0;
}

void Game::initialize()
{
	//リソース読み込み
	Audio::load("game");
	//データ削除
	Model::notes.clear();
	//メモリ確保 - メモリ確保できていないなら例外を投げる
	//判定ライン------------------------------------------------------------------
	Model::judge_line = new JudgeLine();
	MemoryFunction::check_mem(Model::judge_line);
	//UIの初期化
	this->game_ui = new GameUI();
	MemoryFunction::check_mem(this->game_ui);
	//ノーツの生成装置----------------------------------------------------------------
	notes_creater = new NotesCreater();
	MemoryFunction::check_mem(notes_creater);
	//判定結果の生成装置--------------------------------------------------------------
	result_creater = new JudgeResultCreater();
	//オブジェクトの初期化
	Model::judge_line->initialize();//判定ラインの初期化
	this->notes_creater->initialize();
	this->game_ui->initialize();//UIの初期化
	//選択楽曲によって読み込むデータを変える
	set_musical_score();
	if (Model::notes.empty())throw("生成するノーツが空っぽです");

	//カウンタの初期化-----------------------------------------------------------------
	this->start_time.QuadPart = (LONGLONG)GetNowHiPerformanceCount();//開始時間を取得
	this->now_time.QuadPart = 0;//時間の更新
	Counter::game_cnt = 0;
	Counter::perfect_cnt = 0;
	Counter::good_cnt = 0;
	Counter::miss_cnt = 0;
	Counter::combo_cnt = 0;
	Necessary::set_score(0);//スコアの初期化
	//画像をセット
	this->back_graph_handle = GraphicResource::get_handle("game_back")[0];

	start_music();
}

void Game::finalize()
{
	Model::judge_line->finalize();
	this->notes_creater->finalize();
	this->game_ui->finalize();
	//メモリ開放
	Model::judge_results.clear();
	Model::notes.clear();
	delete Model::judge_line;
	delete this->notes_creater;
	delete this->result_creater;
	delete this->game_ui;
}

void Game::update()
{
	//ゲームカウンタの更新
	this->now_time.QuadPart = (LONGLONG)GetNowHiPerformanceCount();//時間の更新
	//マイクロ秒からミリ秒に変換してフレームに変換
	Counter::game_cnt = ((now_time.QuadPart - start_time.QuadPart) / 1000) / 16.666666667f;//フレーム単位に変換
	//ノーツの更新処理
	for (auto itr = Model::notes.begin(); itr != Model::notes.end(); itr++) {
		if ((*itr) != nullptr) {
			(*itr)->update();
		}
	}
	//ノーツの削除処理
	delete_notes();
	//判定結果
	for (auto itr = Model::judge_results.begin(); itr != Model::judge_results.end(); itr++) {
		(*itr)->update();
	}
	//判定結果を可視化するUIの削除処理
	delete_judge_resultUI();
	//判定ラインの更新処理
	Model::judge_line->update();
	//UIの更新処理
	this->game_ui->update();

	//曲が終了したらフェードアウト開始----------------------
	if (Audio::check_play("monoceros") == false && Audio::check_play("fancie") == false) {
		Necessary::set_fade_ioFlag(true);
	}
	//暗転しきったら
	if (ScreenFunction::check_brend_max()) {
		//フェードインを行うよう指示を出す
		Necessary::set_fade_ioFlag(false);
		//シーンを切り替える
		scene_manager->change_scene(SceneData::result);
	}
}

void Game::draw()
{
	//背景の拡縮描画
	DrawExtendGraph(0, 0, ScreenData::width, ScreenData::height, this->back_graph_handle, FALSE);
	//レーンの描画-------------------------------------------------------------
	const int judge_lineX = (int)Model::judge_line->get_position().x;
	const int judge_lineY = (int)Model::judge_line->get_position().y;
	DrawBox(judge_lineX, 0, judge_lineX + judge_line_width, judge_lineY, GetColor(0, 0, 0), TRUE);
	for (int i = 0; i < buttonNum; i++) {
		DrawLine(judge_lineX + note_width * i, 0,
			judge_lineX + note_width * i,
			judge_lineY + judge_line_height,
			GetColor(255, 255, 255));
	}
	//判定ラインの描画---------------------------------------------------------
	Model::judge_line->draw();
	//ノーツの描画処理
	for (auto itr = Model::notes.begin(); itr != Model::notes.end(); itr++) {
		(*itr)->draw();
	}
	//UIの描画
	this->game_ui->draw();
	//判定結果
	for (auto itr = Model::judge_results.begin(); itr != Model::judge_results.end(); itr++) {
		(*itr)->draw();
	}
}

void Game::delete_notes()
{
	//条件を満たしたNotesを削除
	for (auto itr = Model::notes.begin(); itr != Model::notes.end(); itr++) {
		if ((*itr)->get_active() == false) {
			//判定が行われていないノーツがあるならもう一度探索
			const bool continue_flag = ((*itr)->get_result() == JudgeResult::none);
			if (continue_flag) continue;
			add_score((*itr)->get_result());
			//データを初期化してvectorに挿入
			MemoryFunction::check_mem(result_creater);
			result_creater->create((*itr)->get_result(), (*itr)->get_judge_key());
			Model::notes.erase((itr));//vectorから削除
			break;
		}
	}
}

void Game::delete_judge_resultUI()
{
	for (auto itr = Model::judge_results.begin(); itr != Model::judge_results.end(); itr++) {
		//存在するべきではないなら
		if ((*itr)->is_active() == false) {
			//配列から削除
			Model::judge_results.erase(itr);
			break;
		}
	}
}

void Game::set_musical_score()
{
	switch (Necessary::get_music())
	{
	case MusicList::monoceros:
		Model::notes = this->notes_creater->get_notes_data("monoceros");
		break;
	case MusicList::fancie:
		Model::notes = this->notes_creater->get_notes_data("fancie");
	}
}

void Game::start_music()
{
	//楽曲選択に基づいて変える
	switch (Necessary::get_music())
	{
	case MusicList::monoceros:
		Audio::play("monoceros");
		Counter::notes_num = notes_creater->get_all_notes_num("monoceros");
		break;
	case MusicList::fancie:
		Audio::play("fancie");
		Counter::notes_num = notes_creater->get_all_notes_num("fancie");
		break;
	default:
		throw "楽曲に無効な値が入っている";
		break;
	}
}

void Game::add_score(JudgeResult jr)
{
	int score = 0;
	//判定結果を描画するためのオブジェクトをvectorに追加
	//判定結果がどうだったかでスコアを増加させる
	switch (jr)
	{
	case JudgeResult::perfect:
		//増加するスコアの値を決定
		score = theoretical_value / Counter::notes_num;
		//カウンタ上昇
		Counter::perfect_cnt++;
		Counter::combo_cnt++;
		break;
	case JudgeResult::good:
		//増加するスコアの値を決定
		score = theoretical_value / Counter::notes_num / 2;
		//カウンタ上昇
		Counter::good_cnt++;
		Counter::combo_cnt++;
		break;
	case JudgeResult::miss:
		//増加するスコアの値を決定
		score = 0;
		//カウンタ上昇
		Counter::miss_cnt++;
		break;
	}
	//現在スコアに加算する
	Necessary::set_score(Necessary::get_score() + score);
}
