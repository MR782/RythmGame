#pragma once
#include"Object.h"
#include"BasicUI.h"

class MusicSelectGuide : public Object {
	Text guide_label;
public:
	void initialize()override;
	void finalize()override;
	void update()override;
	void draw(bool a_brend = false)override;
};