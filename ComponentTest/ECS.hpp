#pragma once
#include <bitset>
#include <array>
#include <memory>
#include <vector>

class Entity;
class Component;

using ComponentID = std::size_t;

inline ComponentID GetComponentTypeID()
{
	static ComponentID lastID = 0;
	return ++lastID;
}

template <typename T> inline ComponentID GetComponentTypeID() noexcept
{
	static ComponentID typeID = GetComponentTypeID();
	return typeID;
}

constexpr std::size_t MaxComponents = 32;

using ComponentBitSet = std::bitset<MaxComponents>;
using ComponentArray = std::array<Component*, MaxComponents>;

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
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;
	ComponentArray  componentArray;
	ComponentBitSet componentBitSet;
public:
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

	template <typename T> bool HasComponent() const
	{
		return componentBitSet[GetComponentTypeID<T>()];
	}

	//コンポーネントの追加メソッド
	//追加されたらコンポーネントの初期化メソッドが呼ばれる
	template <typename T, typename... TArgs> T& AddComponent(TArgs&&... args)
	{
		//Tips: std::forward
		//関数テンプレートの引数を転送する。
		//この関数は、渡された引数をT&&型にキャストして返す。（注：Tが左辺値参照の場合にはT&&も左辺値参照になり、それ以外の場合にT&&は右辺値参照になる。）
		//この関数は、主に転送関数（forwarding function）の実装を単純化する目的で使われる：
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

public:
	void UpDate()
	{
		for (auto& e : entityes) e->UpDate();
	}
	void Draw()
	{
		for (auto& e : entityes) e->Draw();
	}

	//登録してアクティブでないものを削除する
	void Refresh()
	{
		entityes.erase(std::remove_if(std::begin(entityes), std::end(entityes),
			[](const std::unique_ptr<Entity> &pEntity)
		{
			return !pEntity->IsActive();
		}),
			std::end(entityes));
	}

	Entity& AddEntity()
	{
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr(e);
		entityes.emplace_back(std::move(uPtr));
		return *e;
	}
};