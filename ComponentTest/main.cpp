#include "Component.hpp"
#include <memory>
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	{
		EntityManager mane;

		//Entityの生成
		auto& me(mane.AddEntity());
		auto& you(mane.AddEntity());

		me.AddComponent<PositionConponent>(0, 0);		//引数付きコンストラクタを呼ぶときはこうする
		me.AddComponent<EnableComponent>();
		you.AddComponent<PositionConponent>(100, 100);
	
		while (true)
		{
			//Entityの全体の更新
			mane.UpDate();
			mane.Draw();
			you.GetComponent<PositionConponent>().SetPos(me.GetComponent<PositionConponent>().pos);

			me.GetComponent<EnableComponent>().ESCKeyPush_Break();
			if (me.GetComponent<EnableComponent>().IsBreakEnable())
			{
				break;
			}
		}
	}
	system("pause");
}