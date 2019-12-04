#include "NotesRane.h"
#include"MemoryFunc.h"
#include"GameScene.h"
#include"Define.h"

bool NotesController::delete_notes(std::vector<std::unique_ptr<Notes>>& rane)
{
	for (auto itr = rane.begin(); itr != rane.end(); itr++) {
		//�m�[�c���폜����

		if ((*itr)->get_active() == false) {
			//���肪�s���Ă��Ȃ��m�[�c������Ȃ������x�T��
			const bool continue_flag = ((*itr)->get_result() == JudgeResult::none);
			if (continue_flag) continue;
			add_score((*itr)->get_result());
			//�f�[�^������������vector�ɑ}��
			MemoryFunction::check_mem(result_creater);
			result_creater->create((*itr)->get_result(), (*itr)->get_judge_key());
			
			rane.erase((itr));//vector����폜
			//(*itr)->set_is_first(itr == rane.begin());
			return true;
		}
	}
	return false;
}

void NotesController::callUpdate(std::vector<std::unique_ptr<Notes>>& rane)
{

	for (auto itr = rane.begin(); itr != rane.end(); itr++) {
		(*itr)->update();
	}
	delete_notes(rane);
}

void NotesController::callDraw(std::vector<std::unique_ptr<Notes>>& rane)
{
	for (auto itr = rane.begin(); itr != rane.end(); itr++) {
		(*itr)->draw();
	}
}

void NotesController::initialize()
{
	rane_data["D"].clear();
	rane_data["F"].clear();
	rane_data["J"].clear();
	rane_data["K"].clear();
	//�������m��
	this->result_creater = new JudgeResultCreater();
	MemoryFunction::check_mem(this->result_creater);
	//���[�����Ƃɔz�u(�Q�[���V�[���ɓo�^�����f�[�^���ړ�����)
	if (Model::notes.empty()) throw"�m�[�c�f�[�^������ۂł�";
	for (auto itr = Model::notes.begin(); itr != Model::notes.end(); itr++) {
		switch ((*itr)->get_judge_key())
		{
		case JudgeKey::Key_D:
			rane_data["D"].push_back(std::move(*itr));
			break;
		case JudgeKey::Key_F:
			rane_data["F"].push_back(std::move(*itr));
			break;
		case JudgeKey::Key_J:
			rane_data["J"].push_back(std::move(*itr));
			break;
		case JudgeKey::Key_K:
			rane_data["K"].push_back(std::move(*itr));
			break;
		}
	}
	rane_data["D"].at(0)->set_is_first(true);
	rane_data["F"].at(0)->set_is_first(true);
	rane_data["J"].at(0)->set_is_first(true);
	rane_data["K"].at(0)->set_is_first(true);
}

void NotesController::finalize()
{
	this->rane_data.clear();
}

void NotesController::update()
{
	callUpdate(rane_data["D"]);
	callUpdate(rane_data["F"]);
	callUpdate(rane_data["J"]);
	callUpdate(rane_data["K"]);
}

void NotesController::draw(bool a_brend)
{
	callDraw(rane_data["D"]);
	callDraw(rane_data["F"]);
	callDraw(rane_data["J"]);
	callDraw(rane_data["K"]);
}

void NotesController::add_score(JudgeResult jr)
{
	int score = 0;
	//���茋�ʂ�`�悷�邽�߂̃I�u�W�F�N�g��vector�ɒǉ�
	//���茋�ʂ��ǂ����������ŃX�R�A�𑝉�������
	switch (jr)
	{
	case JudgeResult::perfect:
		//��������X�R�A�̒l������
		score = theoretical_value / Counter::notes_num;
		//�J�E���^�㏸
		Counter::perfect_cnt++;
		Counter::combo_cnt++;
		break;
	case JudgeResult::good:
		//��������X�R�A�̒l������
		score = theoretical_value / Counter::notes_num / 2;
		//�J�E���^�㏸
		Counter::good_cnt++;
		Counter::combo_cnt++;
		break;
	case JudgeResult::miss:
		//��������X�R�A�̒l������
		score = 0;
		//�J�E���^�㏸
		Counter::miss_cnt++;
		break;
	}
	//���݃X�R�A�ɉ��Z����
	Necessary::set_score(Necessary::get_score() + score);
}
