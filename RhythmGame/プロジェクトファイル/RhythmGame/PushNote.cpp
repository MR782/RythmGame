#include "PushNote.h"
#include"Audio.h"
#include"SceneManager.h"
#include"Define.h"

JudgeResult PushNotes::judge()
{
	JudgeResult result = JudgeResult::none;

	//perfect�̃^�C�~���O����ǂ̂��炢����Ă��邩�Ŕ��f����
	float absolute = abs(this->perfect_timing - this->key_down_timing);
	//�덷6�t���[���ȓ��Ȃ�
	if (absolute < 6) {
		//perfect����
		result = JudgeResult::perfect;
		//perfect�������������炷
		Audio::play("perfect");
	}
	//�덷8�t���[���ȓ��Ȃ�
	else if (absolute < 8) {
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
		//���胉�C������ɂ���Ȃ�
		else return result;//�܂�������s��Ȃ�
	}
	//���茋�ʂ�Ԃ�
	return result;
}

void PushNotes::initialize()
{
	this->anime = std::make_unique<Animation>();//�������m��
	if (this->anime == nullptr)throw "PushNotes anime is null_ptr";//�������m�ۂł��Ă��Ȃ��Ȃ��O�𓊂���
	this->anime->set("tap_notes");
}
