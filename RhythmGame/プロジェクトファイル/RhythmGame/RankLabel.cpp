#include "RankLabel.h"
#include"GameScene.h"
#include"ScreenSystem.h"
#include"Define.h"
#include"./dxlib/DxLib.h"

RankLabel::RankLabel()
{
	this->rank_handle = 0;
}

void RankLabel::initialize()
{
	//�f�[�^�̏�����
	this->rank_handle = GraphicResource::get_handle(check_rank())[0];
	this->position = Vector2(ScreenData::width / 2 + rank_graph_size, ScreenData::height / 2);
}

void RankLabel::finalize()
{
	this->anime.reset();
}

void RankLabel::update()
{
}

void RankLabel::draw(bool)
{
	DrawExtendGraph((int)this->position.x, (int)this->position.y,
		(int)this->position.x + rank_graph_size, (int)this->position.y +  rank_graph_size,
		this->rank_handle, TRUE);
}

std::string RankLabel::check_rank()
{
	//�����N���`�F�b�N����
	std::string name = "";
	int game_score = Necessary::get_score();
	if (game_score < rankB_border)       name ="rankC";
	else if (game_score < rankA_border)  name = "rankB";
	else if (game_score < rankS_border) name = "rankA";
	else						        name = "rankS";
	return name;
}
