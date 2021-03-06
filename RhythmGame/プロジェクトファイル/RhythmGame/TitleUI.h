#pragma once
#include<memory>
#include"Animation.h"
#include"Scene.h"
#include"Movie.h"
#include"TitleLogo.h"
#include"TitleGuide.h"

class TitleUI {
	TitleGuide* guide;//案内文字の画像
	TitleLogo* title_logo;//タイトルロゴ
	std::unique_ptr<Movie> title_mv;
public:
	TitleUI();
	void initialize();
	void finalize();
	void update();
	void draw();
};