#pragma once
#include"Object.h"

//ゲームスコアを表示する

class ScoreLabel : public Object {
public:
	void initialize()override;
	void finalize()override;
	void update()override;
	void draw(bool a_brend = false)override;

	void set_position(Vector2 pos);
};