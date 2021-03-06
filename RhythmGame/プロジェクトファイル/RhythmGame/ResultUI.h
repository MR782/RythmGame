#pragma once
#include"Animation.h"
#include"Movie.h"
#include"ResultGuide.h"
#include"ScoreLabel.h"
#include"RankLabel.h"
#include"ResultSceneTitle.h"
#include"GameResult.h"

class ResultUI {
	ResultGuide* guide;//ガイド表示
	ScoreLabel* score;//スコア
	RankLabel* rank;//ランク
	ResultSceneTitle* scene_title;//result　を表示する
	GameResult* game_result;//フルコンボ時の表示(AP含む)
	//画像---------------------------------------------------------
	std::vector<std::unique_ptr<Animation>> result;//リザルトUI
	//ムービー----------------------------------------------------
	std::unique_ptr<Movie> result_mv;//movie
public:
	ResultUI();
	void initialize();
	void finalize();
	void update();
	void draw();
};