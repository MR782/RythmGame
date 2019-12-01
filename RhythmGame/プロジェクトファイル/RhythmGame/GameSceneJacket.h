#pragma once
#include"Jacket.h"

class GameSceneJacket : public Object {
	std::string set_jacket();
	int jacket_handle;
public:
	void initialize()override;
	void finalize()override;
	void update()override;
	void draw(bool a_brend = false)override;
};