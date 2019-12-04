#include "Notes.h"
#include"KeyBoard.h"
#include"Mouse.h"
#include"GameScene.h"
#include"ScreenSystem.h"
#include"Necessary.h"
#include"Audio.h"
#include"Define.h"
#include"./dxlib/DxLib.h"

Notes::Notes() : Object()
{
	this->active = true;
	this->judge_key = JudgeKey::Key_D;
	this->judge_result = JudgeResult::none;
	this->key_down_timing = 0;
	this->is_first = false;
	this->perfect_timing = 0;
}

void Notes::initialize()
{
	throw" called super class method";
}

void Notes::finalize()
{
	this->anime.reset();
}

void Notes::update()
{
	move();
	//�����̔���L�[�������ꂽ�猻�݂̃Q�[���J�E���g���L�[���������^�C�~���O�Ƃ��ēo�^
	if (this->check_key()) {
		this->key_down_timing = Counter::game_cnt;
	}
	this->judge_result = this->judge();
	//���茋�ʂ��o�Ă���Ȃ�
	if (this->judge_result != JudgeResult::none) this->active = false;//���݂�����
}

void Notes::set_is_first(bool flag)
{
	this->is_first = flag;
}

bool Notes::get_active()
{
	return this->active;
}

JudgeResult Notes::get_result()
{
	return this->judge_result;
}

JudgeKey Notes::get_judge_key()
{
	return this->judge_key;
}

void Notes::set_contents(float timing, JudgeKey j_key)
{
	this->judge_key = j_key;
	//����L�[�ɂ���ď������W��ς���
	float posY = 0 + 1 * ((this->perfect_timing - Counter::game_cnt) * -(Model::judge_line->get_position().y) * 1);
	this->position =
		Vector2((float)((ScreenData::width / 2) - (judge_line_width / 2) + (int)(this->judge_key)* note_width),
			             posY);
	//�ړ��ʂƃ^�C�~���O���Z�b�g����
	this->perfect_timing = timing;
}

void Notes::move()
{
	//�I�_�̈ʒu + �I�_����n�_�ւ̕��� * ((���胉�C���ɂ��鎞�� - �Ȃ̍Đ�����)*���[���̒���*�X�s�[�h);                                    
	float posY = Model::judge_line->get_position().y + ((this->perfect_timing - Counter::game_cnt)
		* -(Model::judge_line->get_position().y) * (0.001f * Necessary::get_speed()));
	this->position.y = posY;
}

JudgeResult Notes::judge()
{
	JudgeResult result = JudgeResult::none;

	//perfect�̃^�C�~���O����ǂ̂��炢����Ă��邩�Ŕ��f����
	float absolute = abs(this->perfect_timing - this->key_down_timing);
	//�덷3�t���[���ȓ��Ȃ�
	if (absolute < 3) {
		//perfect����
		result = JudgeResult::perfect;
		//perfect�������������炷
		Audio::play("perfect");
	}
	//�덷5�t���[���ȓ��Ȃ�
	else if (absolute < 5) {
		//good����	
		result = JudgeResult::good;
		//good�������������炷
		Audio::play("good");
	}
	//�����肸��Ă���Ȃ�-----------------------
	else {
		if (this->position.y > Model::judge_line->get_position().y + judge_line_height) {
			//���ɂ���Ȃ�~�X�ɂ���
			result = JudgeResult::miss;
			//�~�X��������炷
			Audio::play("miss");
		}
		else return result;//�܂�������s��Ȃ�
	}
	//���茋�ʂ�Ԃ�
	return result;
}

bool Notes::check_key()
{
	bool check_key = false;
	//����L�[�ɂ���ď�����ς���---------------------
	switch (this->judge_key)
	{
	case JudgeKey::Key_D:
		check_key = KeyBoard::key_down(KEY_INPUT_D);
		break;
	case JudgeKey::Key_F:
		check_key = KeyBoard::key_down(KEY_INPUT_F);
		break;
	case JudgeKey::Key_J:
		check_key = KeyBoard::key_down(KEY_INPUT_J);
		break;
	case JudgeKey::Key_K:
		check_key = KeyBoard::key_down(KEY_INPUT_K);
		break;
	}
	return check_key;
}
