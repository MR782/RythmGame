#pragma once
#include"Scene.h"
#include"ResultUI.h"

class Result : public Scene {
	ResultUI* result_ui;
public:
	void initialize()override;
	void finalize()override;
	void update()override;
	void draw()override;
};