#pragma once
#include"Object.h"

//�Q�[�����ʂ̃����N�\��

class RankLabel : public Object {
	std::string check_rank();//�Q�[���̃X�R�A�Ń����N��t����
	int rank_handle;//�摜�n���h�����i�[����
public:
	RankLabel();
	void initialize()override;
	void finalize()override;
	void update()override;
	void draw(bool a_brend = false)override;
};