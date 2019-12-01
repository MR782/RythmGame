#pragma once
#include"Object.h"

class GameResult : public Object {
public:
	void initialize()override;
	void finalize()override;
	void update()override;
};