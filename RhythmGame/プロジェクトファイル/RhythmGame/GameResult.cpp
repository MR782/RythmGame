#include "GameResult.h"
#include"ScreenSystem.h"
#include"Define.h"
#include"SceneManager.h"

void GameResult::initialize()
{
	//�f�[�^������
	this->anime = std::make_unique<Animation>();//�������m��
	this->position = Vector2(ScreenData::width / 2 + fullcombo_graph_width / 2, ScreenData::height / 2 + fullcombo_graph_height * 2);
	if (this->anime == nullptr) throw "GameResult anime is null_ptr";//�������m�ۂł��Ă��Ȃ��Ȃ��O�𓊂���
	this->anime->set("");//��̉摜���Z�b�g
	//�~�X����0��
	if (Counter::miss_cnt == 0) {
		//good��0�Ȃ�
		if (Counter::good_cnt == 0) {
			//AllPerfect�Ƃ���
			this->anime->set("all_perfect");
		}
		//good������Ȃ�
		else {
			//FullCombo�ƕ\��
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
