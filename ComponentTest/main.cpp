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
		
		//:(コロン)をつけると基底の型を指定できる
		enum GrpupLabels : std::size_t
		{
			GROUP_ME,
			GROUP_YOU
		};

		me.AddComponent<PositionConponent>(0, 0);		//引数付きコンストラクタを呼ぶときはこうする
		me.AddComponent<EnableComponent>();
		me.AddGroup(GROUP_ME);									//グループに登録	
		auto& m_me(mane.GetGroup(GROUP_ME));			//グループを取得
		you.AddComponent<PositionConponent>(100, 100);
		you.AddGroup(GROUP_YOU);								
		auto& m_you(mane.GetGroup(GROUP_YOU));

		//グループ分けすることによって、描画レイヤー(更新処理も)を分けることができる!!
		while (true)
		{
			//★★★★★★Entityの全体の更新★★★★★★★★★★★★
			mane.UpDate();
			//mane.Draw();
			//★★★★★★★★★★★★★★★★★★★★★★★★★★★
			//★★★★★★グループごとに更新★★★★★★★★★★★★
			for (auto& m : m_me)
			{
				std::cout << "MEグループの描画です" << std::endl;
				m->Draw();
			}
			for (auto& y : m_you)
			{
				std::cout << "YOUグループの描画です" << std::endl;
				y->Draw();
			}
			//★★★★★★★★★★★★★★★★★★★★★★★★★★★

			me.GetComponent<EnableComponent>().ESCKeyPush_Break();
			if (me.GetComponent<EnableComponent>().IsBreakEnable())
			{
				break;
			}
		}
	}
	system("pause");
}
