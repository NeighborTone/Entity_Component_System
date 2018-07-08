#include "ECS.h"
void Entity::AddGroup(Group group)
{
	groupBitSet[group] = true;
	manager_.AddGroup(this, group);
}
