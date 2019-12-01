#pragma once
#include"JudgeButton.h"
#include"ScoreLabel.h"
#include"ComboLabel.h"
#include"GameSceneJacket.h"

class GameUI {
	std::vector<std::unique_ptr<Animation>> result;//���U���gUI
	std::vector<JudgeButton*> judge_button;//����{�^��
	ScoreLabel* score_label;//�X�R�A�\���̃��x��
	ComboLabel* combo_label;//�R���{�\���̃��x��
	GameSceneJacket* jacket;//�v���C���̊y�Ȃ�\��
public:
	GameUI();
	void initialize();
	void finalize();
	void update();
	void draw();
};