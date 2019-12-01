#include "Jacket.h"
#include"ScreenSystem.h"
#include"Define.h"
#include"Necessary.h"

void Jacket::initialize()
{
	this->anime = std::make_unique<Animation>();//メモリ確保
	if (this->anime == nullptr) throw "Jacket anime is null_ptr";//メモリ確保できていないなら例外を投げる
	this->anime->set("monoceros_jacket");//初期画像をセット
	//中心にセット
	this->position = Vector2((ScreenData::width / 2) - (jacket_width / 2), (ScreenData::height / 2) - (jacket_height / 2));
}

void Jacket::finalize()
{
	this->anime.reset();
}

void Jacket::update()
{
	change_jacket();
}

void Jacket::change_jacket()
{
	//難易度と楽曲によって画像を変える
	switch (Necessary::get_music())
	{
	case MusicList::monoceros:
		this->anime->set("monoceros_jacket");
		break;
	case MusicList::fancie:
		this->anime->set("fancie_jacket");
		break;
	}
}
