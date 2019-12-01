#include "ScoreLabel.h"
#include"Define.h"
#include"ScreenSystem.h"
#include"Necessary.h"
#include"./dxlib/DxLib.h"

void ScoreLabel::initialize()
{
	//������
	this->anime = std::make_unique<Animation>();//�������m��
	if (this->anime == nullptr) throw "ScoreLabel anime is null_ptr";//�������m�ۂł��Ȃ������Ȃ�
	this->anime->set("score");//�摜���Z�b�g
	this->position = Vector2((ScreenData::width / 10 - ui_graph_width / 2), ScreenData::height / 5);
}

void ScoreLabel::finalize()
{
	this->anime.reset();//�������J��
}

void ScoreLabel::update()
{
}

void ScoreLabel::draw(bool a_brend)
{
	this->anime->draw_anime(this->position);
	//������`��
	DrawFormatString((int)this->position.x, (int)this->position.y + ui_graph_height, GetColor(0, 0, 0), " %d ", Necessary::get_score());
}

void ScoreLabel::set_position(Vector2 pos)
{
	//���W�Z�b�g
	this->position = pos;
}
