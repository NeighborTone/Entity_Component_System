#pragma once
#include "ECS.h"
#include <Windows.h>
#include <iostream>
namespace ECS
{
	struct Pos
{
	int
		x=0, 
		y=0;
};
class PositionConponent : public Component
{
public:
	PositionConponent() = default;
	PositionConponent(int xx, int yy)
	{
		pos.x = xx;
		pos.y = yy;
	}
	~PositionConponent() 
	{
		std::cout << "PositionConponentDestructor" << std::endl;
	}
	Pos pos;
	void Init() override
	{
		pos.x = 0;
		pos.y = 0;
	}

	void UpDate() override
	{
		++pos.x;
		++pos.y;
	}
	void Draw() override
	{
		std::cout << pos.x << std::endl;
	}
	void SetPos(int xx, int yy)
	{
		pos.x = xx;
		pos.y = yy;
	}
	void SetPos(Pos& ppos)
	{
		pos = ppos;
	}
};

class EnableComponent : public Component
{
private:
	bool enable = false;
public:
	~EnableComponent()
	{
		std::cout << "EnableComponentDestructor" << std::endl;
	}
	void ESCKeyPush_Break()
	{
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			enable = true;
		}
	}
	void SPACE_Disable()
	{
		if (GetAsyncKeyState(VK_SPACE))
		{
			enable = false;
		}
	}

	bool IsBreakEnable()
	{
		return enable;
	}

};

}

