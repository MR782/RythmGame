#include "HoldNote.h"
#include"KeyBoard.h"
#include"SceneManager.h"
#include"Define.h"
#include"Audio.h"
#include"./dxlib/DxLib.h"

JudgeResult HoldNotes::judge()
{
	JudgeResult jr = JudgeResult::none;
	//���[���̐擪�o�Ȃ��Ȃ�܂�������s��Ȃ�
	if (this->is_first == false) return jr;
	float absolute = abs(this->perfect_timing - this->key_down_timing);//��Βl�����߂�
	if (absolute >= 2) {
		//�܂����肷��ׂ��łȂ��Ȃ�
		if (this->position.y  < Model::judge_line->get_position().y + note_height) {
			return jr;
		}
		//�ʂ�߂�����miss�ƂȂ�
		else {
			//�~�X��������炷
			Audio::play("miss");
			jr = JudgeResult::miss;
		}
	}
	//�m�[�c���d�Ȃ�^�C�~���O�ɂ������艟����Ă���Ȃ�
	//else{}
	else {//3�t���[���̊Ԕ��肵�Ă���(-1,0,1)
		//perfect�������������炷
		Audio::play("perfect");
		//perfect����
		jr = JudgeResult::perfect;
	}
	return jr;
}

bool HoldNotes::check_key()
{
	bool check_key = false;
	//����L�[�ɂ���ď�����ς���---------------------
	switch (this->judge_key)
	{
	case JudgeKey::Key_D:
		check_key = KeyBoard::key_press(KEY_INPUT_D);
		break;
	case JudgeKey::Key_F:
		check_key = KeyBoard::key_press(KEY_INPUT_F);
		break;
	case JudgeKey::Key_J:
		check_key = KeyBoard::key_press(KEY_INPUT_J);
		break;
	case JudgeKey::Key_K:
		check_key = KeyBoard::key_press(KEY_INPUT_K);
		break;
	}
	return check_key;
}

void HoldNotes::initialize()
{
	this->anime = std::make_unique<Animation>();
	if (this->anime == nullptr)throw "HoldNotes anime is null_ptr";//�������m�ۂł��Ă��Ȃ��Ȃ��O�𓊂���
	this->anime->set("hold_notes");
}
