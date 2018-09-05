#include "ECS.h"

void ECS::Entity::AddGroup(Group group) noexcept
{
	groupBitSet[group] = true;
	manager_.AddToGroup(this, group);
}
