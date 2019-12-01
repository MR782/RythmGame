#pragma once
#include"Object.h"

//���茋��
enum class JudgeResult {
	perfect,
	good,
	miss,
	none
};

//������s���L�[
enum class JudgeKey {
	Key_D,//0
	Key_F,//1
	Key_J,//2
	Key_K,//3
	JudgeKeyNum//
};

class Notes : public Object {
	bool active;//�����t���O
	JudgeResult judge_result;//���茋��
	//���\�b�h
	void move();//�ړ����s��
protected:
	JudgeKey judge_key;//����L�[
	float key_down_timing;//����L�[�������ꂽ�^�C�~���O
	float perfect_timing;//perfect�̃^�C�~���O(�t���[���P��)
	virtual bool check_key();
	virtual JudgeResult judge();//������s��
public:
	Notes();
	void initialize()override;
	void finalize()final;
	void update()final;

	bool get_active();//�����t���O���󂯎�点��
	JudgeResult get_result();//���茋�ʂ��󂯎�点��
	JudgeKey get_judge_key();//����L�[���󂯎�点��
	void set_contents(float timing,JudgeKey j_key);//�f�[�^������
};