#pragma once
#include"Object.h"

//�W���P�b�g�摜��\��

class Jacket : public Object {
public:
	void initialize()override;
	void finalize()override;
	void update()override;

	void change_jacket();//�I���y�Ȃɉ����ĉ摜��؂�ւ���
};