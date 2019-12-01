#include "ResultSceneTitle.h"
#include"ScreenSystem.h"
#include"Define.h"

void ResultSceneTitle::initialize()
{
	//データ初期化
	this->anime = std::make_unique<Animation>();
	if (this->anime == nullptr) throw "ResultSceneTitle anime is null_ptr";//メモリ確保できていないなら例外を投げる
	this->anime->set("result");
	this->position = Vector2((ScreenData::width / 2 - result_width / 2), ScreenData::height / 10);
}

void ResultSceneTitle::finalize()
{
	this->anime.reset();
}

void ResultSceneTitle::update()
{
}
