#include "GameUI.h"
#include"Define.h"
#include"SceneManager.h"
#include"ScreenSystem.h"
#include"MemoryFunc.h"
#include"./dxlib/DxLib.h"

GameUI::GameUI()
{
	this->score_label = nullptr;
	this->combo_label = nullptr;
}

void GameUI::initialize()
{
	//JudgeButton�̏�����-----------------------------------------------------------------------------
	{
		std::string name[buttonNum][2];
		name[0][0] = "not_pushD"; name[0][1] = "pushD";//D�L�[
		name[1][0] = "not_pushF"; name[1][1] = "pushF";//F�L�[
		name[2][0] = "not_pushJ"; name[2][1] = "pushJ";//J�L�[
		name[3][0] = "not_pushK"; name[3][1] = "pushK";//K�L�[
		//�v�f�ǉ�
		for (int i = 0; i < buttonNum; i++) {
			judge_button.push_back(new JudgeButton());
		}
		int cnt = 0;
		for (auto itr = judge_button.begin(); itr != judge_button.end(); itr++, cnt++) {
			MemoryFunction::check_mem(*itr);
			(*itr)->initialize();
			//�������W
			Vector2 pos = Vector2(Model::judge_line->get_position().x + (note_width * cnt),//x
				Model::judge_line->get_position().y + judge_line_height);//y
			//�����f�[�^�Z�b�g
			(*itr)->set_contents(pos, name[cnt], JudgeKey(cnt));
		}
	}
	//UI---------------------------------------------------------------------------------------------
	{
		std::string name[judge_resultNum] = { "perfect","good","miss" };
		//�g�p�������
		for (int i = 0; i < judge_resultNum; i++) {
			result.push_back(std::unique_ptr<Animation>());
		}
		//�摜�Z�b�g
		int i = 0;
		for (auto itr = result.begin(); itr != result.end(); itr++, i++) {
			(*itr) = std::make_unique<Animation>();//�������m��
			(*itr)->set(name[i]);
		}
	}
	//�X�R�AUI--------------------------------------------------------------------------------------------
	this->score_label = new ScoreLabel();
	MemoryFunction::check_mem(this->score_label);
	this->score_label->initialize();
	//�R���{���x���̏�����
	this->combo_label =new ComboLabel();
	MemoryFunction::check_mem(this->combo_label);
	this->combo_label->initialize();
	//�W���P�b�g�摜
	this->jacket = new GameSceneJacket();
	MemoryFunction::check_mem(this->jacket);
	this->jacket->initialize();
}

void GameUI::finalize()
{
	this->combo_label->finalize();
	this->score_label->finalize();
	this->jacket->finalize();
	for (auto itr : judge_button) {
		(itr)->finalize();
		delete (itr);
	}
	this->result.clear();
	this->judge_button.clear();
	delete this->combo_label;
	delete this->score_label;
	delete this->jacket;
}

void GameUI::update()
{
	//����{�^���̍X�V����
	for (auto itr : judge_button) {
		(itr)->update();
	}
	this->combo_label->update();
}

void GameUI::draw()
{
	//����{�^���̕`�揈��
	for (auto itr : judge_button) {
		(itr)->draw();
	}
	//result
	int cnt = 0;
	for (auto itr = result.begin(); itr != result.end(); itr++, cnt++) {
		Point pos((ScreenData::width / 10 - ui_graph_width / 2), ScreenData::height / 2 + (cnt * ui_graph_height));
		(*itr)->draw_anime(pos);
		int counter = 0;
		switch (cnt)
		{
		case 0: counter = Counter::perfect_cnt; break;
		case 1:counter = Counter::good_cnt;     break;
		case 2:counter = Counter::miss_cnt;    break;
		}
		DrawFormatString(pos.x + ui_graph_width, pos.y + (ui_graph_height / 3), GetColor(0, 0, 0), "%d", counter);
	}
	//score
	this->score_label->draw();
	//combo
	this->combo_label->draw();
	//jacket
	this->jacket->draw();
}
