#pragma once
#include"Notes.h"
#include"JudgeLine.h"
#include"NotesCreater.h"
#include"Scene.h"
#include"JudgeResultUI.h"
#include"GameUI.h"
#include"JudgeResultCreater.h"

class Game : public Scene{
	//�Q�[���V�[���J�n����
	LARGE_INTEGER start_time;
	LARGE_INTEGER now_time;
	//�m�[�c�̐������u
	NotesCreater *notes_creater;
	//���茋�ʂ̐������u
	JudgeResultCreater *result_creater;
	//UI
	GameUI* game_ui;
	//���\�b�h
	//�����𖞂������I�u�W�F�N�g��vector����폜
	void delete_notes();
	void delete_judge_resultUI();
	//�I���y�Ȃɂ���ĕ��ʃf�[�^������
	void set_musical_score();
	//���y���Đ�����
	void start_music();
	//�X�R�A��ǉ�����
	void add_score(JudgeResult jr);
public:
	Game();
	void initialize()override;
	void finalize()override;
	void update()override;
	void draw()override;
};

namespace Counter {
	extern float game_cnt;//�Q�[���J�E���^
	extern int notes_num;//�m�[�c�̍��v��
	extern int combo_cnt;//�R���{��
	//�m�[�c�̔��茋�ʂ̐����i�[
	extern int perfect_cnt;
	extern int good_cnt;
	extern int miss_cnt;
}

namespace Model {
	//�Q�[�����I�u�W�F�N�g(�L�����N�^�[)
	extern std::vector<std::unique_ptr<Notes>> notes;
	extern JudgeLine* judge_line;
	extern std::vector<std::unique_ptr<JudgeResultUI>> judge_results;
}