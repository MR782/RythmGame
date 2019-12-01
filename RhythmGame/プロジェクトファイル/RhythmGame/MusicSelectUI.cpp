#include "MusicSelectUI.h"
#include"Necessary.h"
#include"KeyBoard.h"
#include"Audio.h"
#include"Define.h"
#include"ScreenSystem.h"
#include"MemoryFunc.h"
#include"./dxlib/DxLib.h"

MusicSelectUI::MusicSelectUI()
{
	this->cursol[0] = nullptr;
	this->cursol[1] = nullptr;
	this->jacket = nullptr;
	this->guide = nullptr;
	this->speed_label = nullptr;
}

void MusicSelectUI::initialize()
{
	//カーソルの初期化
	{
		std::string graph_name[cursolNum] = { "select_cursol_L","select_cursol_R" };
		//座標決定
		int posY = (ScreenData::height / 2) - (select_cursol_height / 2);
		Vector2 pos[cursolNum] = { Vector2(ScreenData::width / 10, posY),Vector2(ScreenData::width - (ScreenData::width / 10) - select_cursol_width, posY) };
		//カーソルの数初期化を行う
		for (int i = 0; i < cursolNum; i++) {
			this->cursol[i] = new Cursol();	//メモリ確保
			MemoryFunction::check_mem(this->cursol[i]);
			this->cursol[i]->initialize();
			this->cursol[i]->set_graph(graph_name[i]);
			this->cursol[i]->set_position(pos[i]);
		}
	}
	//ムービーをセット
	this->m_select_movie = std::make_unique<Movie>();
	if (this->m_select_movie == nullptr) throw "MusicSelect movie is null_ptr";//メモリ確保できていないなら例外を投げる;
	this->m_select_movie->set("autumn_leaves");
	//楽曲ジャケット用
	this->jacket = new Jacket();
	MemoryFunction::check_mem(this->jacket);
	this->jacket->initialize();
	//ガイドの初期化
	this->guide =new MusicSelectGuide();
	MemoryFunction::check_mem(this->guide);
	this->guide->initialize();
	//スピード表示
	this->speed_label = new SpeedLabel();
	MemoryFunction::check_mem(this->speed_label);
	this->speed_label->initialize();
}

void MusicSelectUI::finalize()
{
	//終了処理とメモリ開放
	for (int i = 0; i < cursolNum; i++) {
		this->cursol[i]->finalize();
	}
	this->jacket->finalize();
	this->guide->finalize();
	this->speed_label->finalize();

	delete this->guide;
	delete this->speed_label;
	delete this->jacket;
	for (int i = 0; i < cursolNum; i++) {
		delete this->cursol[i];
	}
}

void MusicSelectUI::update()
{
	//ジャケットの更新処理
	this->jacket->update();
	//指定のキーが押されたら選択楽曲を変える----------------------------------
	change_music();
}

void MusicSelectUI::draw()
{
	//ムービーの描画
	this->m_select_movie->draw();
	//カーソルの描画
	for (int i = 0; i < cursolNum; i++) {
		this->cursol[i]->draw();
	}
	//ジャケットの描画
	this->jacket->draw();
	//ガイドの表示
	this->guide->draw();
	//スピード表示
	this->speed_label->draw();
}

void MusicSelectUI::change_music()
{
	//現在選択中の楽曲を入れる
	int now_select = (int)Necessary::get_music();
	//指定のキーが押されたら選択楽曲を変える
	if (KeyBoard::key_down(KEY_INPUT_RIGHT)) {
		//1つずらす
		now_select = (now_select + 1) % (int)MusicList::MusicNum;
		Necessary::set_music(MusicList(now_select));
		//効果音を鳴らす
		Audio::play("cursol");
	}
	if (KeyBoard::key_down(KEY_INPUT_LEFT)) {
		//効果音を鳴らす
		Audio::play("cursol");
		//1つずらす
		now_select = (now_select + ((int)MusicList::MusicNum - 1)) % (int)MusicList::MusicNum;
		Necessary::set_music(MusicList(now_select));
	}
}