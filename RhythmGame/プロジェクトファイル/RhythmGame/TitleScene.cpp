#include "TitleScene.h"
#include"ScreenSystem.h"
#include"Necessary.h"
#include"ScreenFunction.h"
#include"Mouse.h"
#include"SceneManager.h"
#include"Audio.h"
#include"MemoryFunc.h"
#include"./dxlib/DxLib.h"

Title::Title()
{
	this->title_ui = nullptr;
	this->back_graph_handle = 0;
}

void Title::initialize()
{
	//メモリ確保
	this->title_ui = new TitleUI();
	MemoryFunction::check_mem(this->title_ui);
	//リソースの読み込み
	MovieResource::load("title");
	Audio::load("title");
	this->back_graph_handle = GraphicResource::get_handle("title_back")[0];//1枚のため配列の0を指す
	//データの初期化
	this->title_ui->initialize();
	//オーディオデータの読み込み
	Audio::play("title",false);
	
}

void Title::finalize()
{
	this->title_ui->finalize();
	delete this->title_ui;
	//リソースデータの開放
	Audio::delete_soundData_name("title");
	MovieResource::delete_movie_mem("reaf");
}

void Title::update()
{
	if (ScreenFunction::check_brend_min()) {
		//UIの更新処理
		title_ui->update();
	}
	//シーン切り替え-----------------------------------------
	scene_change(Mouse::left_click_down(), SceneData::m_select);
}

void Title::draw()
{
	//背景を拡縮して描画
	DrawExtendGraph(0, 0, ScreenData::width, ScreenData::height, this->back_graph_handle, FALSE);
	//UIの描画
	title_ui->draw();
}
