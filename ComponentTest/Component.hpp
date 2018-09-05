#pragma once
#include "ECS.h"
#include <Windows.h>
#include <iostream>
namespace ECS
{
	struct Position : public ComponentData
	{
		Position() = default;
		Position(float xx, float yy) :x(xx), y(yy) {}
		float x, y;
	};

	//‹¤’Ê‚Ìƒf[ƒ^‚É‘Î‚·‚éˆ—
	class Move : public Component
	{
	private:
		Position* pos = nullptr;
	public:
		//AddComponentŽž‚ÉŒÄ‚Î‚ê‚é
		virtual void Initialize() override
		{
			if (entity->HasComponent<Position>())
			{
				pos = &entity->GetComponent<Position>();
			}
		}
		virtual void Update() override
		{
			++pos->x;
		}
		virtual void Draw2D() override
		{
			std::cout << "Xposition : " << pos->x << std::endl;
		}
	};

}

