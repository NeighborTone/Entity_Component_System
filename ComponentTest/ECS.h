#pragma once
#include <bitset>
#include <array>
#include <memory>
#include <vector>

class Entity;
class Component;
class EntityManager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID GetNewComponentTypeID()
{
	static ComponentID lastID = 0u;
	return ++lastID;
}

template <typename T> inline ComponentID GetComponentTypeID() noexcept
{
	static ComponentID typeID = GetNewComponentTypeID();
	return typeID;
}

constexpr std::size_t MaxComponents = 32;
constexpr std::size_t MaxGroups = 32;

using ComponentBitSet = std::bitset<MaxComponents>;
using ComponentArray = std::array<Component*, MaxComponents>;
using GroupBitSet = std::bitset<MaxGroups>;

class Component
{
public:
	Entity* entity;

	virtual void Init() {}
	virtual void UpDate() {}
	virtual void Draw() {}
	virtual ~Component() {}
};

class Entity
{
private:
	EntityManager& manager_;
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;
	ComponentArray  componentArray;
	ComponentBitSet componentBitSet;
	GroupBitSet groupBitSet;
public:

	Entity(EntityManager& manager): manager_(manager){}

	void UpDate()
	{
		for (auto& c : components) c->UpDate();
	}
	void Draw() 
	{
		for (auto& c : components) c->Draw();
	}
	bool IsActive() const { return active; }
	void Destroy() { active = false; }

	bool HasGroup(Group group)
	{
		return groupBitSet[group];
	}

	void AddGroup(Group group);

	void DeleteGroup(Group group)
	{
		groupBitSet[group] = false;
	}

	template <typename T> bool HasComponent() const
	{
		return componentBitSet[GetComponentTypeID<T>()];
	}

	//�R���|�[�l���g�̒ǉ����\�b�h
	//�ǉ����ꂽ��R���|�[�l���g�̏��������\�b�h���Ă΂��
	template <typename T, typename... TArgs> T& AddComponent(TArgs&&... args)
	{
		//Tips: std::forward
		//�֐��e���v���[�g�̈�����]������B
		//���̊֐��́A�n���ꂽ������T&&�^�ɃL���X�g���ĕԂ��B�i���FT�����Ӓl�Q�Ƃ̏ꍇ�ɂ�T&&�����Ӓl�Q�ƂɂȂ�A����ȊO�̏ꍇ��T&&�͉E�Ӓl�Q�ƂɂȂ�B�j
		//���̊֐��́A��ɓ]���֐��iforwarding function�j�̎�����P��������ړI�Ŏg����F
		T* c(new T(std::forward<TArgs>(args)...));	
		c->entity = this;
		std::unique_ptr<Component> uPtr(c);
		components.emplace_back(std::move(uPtr));

		componentArray[GetComponentTypeID<T>()] = c;
		componentBitSet[GetComponentTypeID<T>()] = true;

		//c->Init();
		return *c;
	}

	template<typename T> T& GetComponent() const
	{
		auto ptr(componentArray[GetComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

};

class EntityManager
{
private:
	std::vector<std::unique_ptr<Entity>> entityes;
	std::array<std::vector<Entity*>, MaxGroups> groupedEntities;
public:
	void UpDate()
	{
		for (auto& e : entityes) e->UpDate();
	}
	void Draw()
	{
		for (auto& e : entityes) e->Draw();
	}

	//�o�^���Ă���Entity�ŃA�N�e�B�u�łȂ����̂��폜����
	void Refresh()
	{
		for (auto i(0u); i < MaxGroups; ++i)
		{
			auto& v(groupedEntities[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v),
					[i](Entity* entity)
			{
				return !entity->IsActive() || !entity->HasGroup(i);
			}),
				std::end(v));
		}

		entityes.erase(std::remove_if(std::begin(entityes), std::end(entityes),
			[](const std::unique_ptr<Entity> &pEntity)
		{
			return !pEntity->IsActive();
		}),
			std::end(entityes));
	}

	std::vector<Entity*>& GetGroup(Group group)
	{
		return groupedEntities[group];
	}

	void AddGroup(Entity* pEntity, Group group)
	{
		groupedEntities[group].emplace_back(pEntity);
	}
	Entity& AddEntity()
	{
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr(e);
		entityes.emplace_back(std::move(uPtr));
		return *e;
	}
};