#pragma once
#include"JudgeButton.h"
#include"ScoreLabel.h"
#include"ComboLabel.h"
#include"GameSceneJacket.h"

class GameUI {
	std::vector<std::unique_ptr<Animation>> result;//リザルトUI
	std::vector<JudgeButton*> judge_button;//判定ボタン
	ScoreLabel* score_label;//スコア表示のラベル
	ComboLabel* combo_label;//コンボ表示のラベル
	GameSceneJacket* jacket;//プレイ中の楽曲を表示
public:
	GameUI();
	void initialize();
	void finalize();
	void update();
	void draw();
};