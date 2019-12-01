#include "GameSceneJacket.h"
#include"Necessary.h"
#include"ScreenSystem.h"
#include"Define.h"
#include"./dxlib/DxLib.h"

std::string GameSceneJacket::set_jacket()
{
	std::string name;
	switch (Necessary::get_music())
	{
	case MusicList::fancie:
		name = "fancie_jacket";
		break;
	case MusicList::monoceros:
		name = "monoceros_jacket";
		break;
	default:
		throw("Šy‹È‚É–³Œø‚È’l‚ª“ü‚Á‚Ä‚¢‚é");
		break;
	}
	return name;
}

void GameSceneJacket::initialize()
{
	this->position = Vector2(ScreenData::width - (jacket_width / 2),0);
	this->jacket_handle = GraphicResource::get_handle(set_jacket())[0];
}

void GameSceneJacket::finalize()
{
}

void GameSceneJacket::update()
{
}

void GameSceneJacket::draw(bool a_brend)
{
	DrawExtendGraph((int)this->position.x, (int)this->position.y,
		ScreenData::width, jacket_height / 2,
		this->jacket_handle, FALSE);
}
