#include "Component.hpp"
#include <memory>
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
using namespace ECS;
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	{
		EntityManager mane;

		//Entityの生成
		auto& me(mane.AddEntity());
		auto& you(mane.AddEntity());
		
		
		enum GroupLayer : std::size_t
		{
			GROUP_ME = 1u,
			GROUP_YOU,
			MAX
		};
		//Entityを1つ以上のコンポーネントで要素を作る
		me.AddComponent<Position>(0.f, 0.f);
		me.AddComponent<Move>();
		me.AddGroup(GROUP_ME);

		you.AddComponent<Position>(1000.f, 0.f);
		you.AddComponent<Move>();
		you.AddGroup(GROUP_YOU);
		//グループ分けすることによって、描画レイヤー(更新処理も)を分けることができる!!
		while (true)
		{
			//★★★★★★Entityの全体の更新★★★★★★★★★★★★
			mane.Refresh();
			mane.Update();
			
			//★★★★★★グループごとに更新★★★★★★★★★★★★
			mane.OrderByDraw(MAX);
			//★★★★★★★★★★★★★★★★★★★★★★★★★★★

		}
	}
	system("pause");
}
