#pragma once
#include"Object.h"

//ゲーム結果のランク表示

class RankLabel : public Object {
	std::string check_rank();//ゲームのスコアでランクを付ける
	int rank_handle;//画像ハンドルを格納する
public:
	RankLabel();
	void initialize()override;
	void finalize()override;
	void update()override;
	void draw(bool a_brend = false)override;
};