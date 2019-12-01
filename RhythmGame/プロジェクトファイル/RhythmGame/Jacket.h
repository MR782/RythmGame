#pragma once
#include"Object.h"

//ジャケット画像を表示

class Jacket : public Object {
public:
	void initialize()override;
	void finalize()override;
	void update()override;

	void change_jacket();//選択楽曲に応じて画像を切り替える
};