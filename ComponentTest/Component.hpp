#pragma once
#include "ECS.hpp"

class PositionConponent : public Component
{
private:
	int 
		x,
		y;
public:
	int X() { return x; }
	int Y() { return y; }

	void Init() override
	{
		x = 0;
		y = 0;
	}

	void UpDate() override
	{
		++x;
		++y;
	}

	void SetPos(int xx, int yy)
	{
		x = xx;
		y = yy;
	}


};