#pragma once
#include"Object.h"
#include"BasicUI.h"

class SpeedLabel : public Object {
	Text speed_label_header;//�����\��
	Text speed_label;//���݂̃X�s�[�h��\��
public:
	void initialize()override;
	void finalize()override;
	void update()override;
	void draw(bool flag = false)override;
};