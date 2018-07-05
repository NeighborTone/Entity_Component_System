#include <iostream>
#include "Component.hpp"

int main()
{
	EntityManager mane;
	auto& me(mane.AddEntity());

	me.AddComponent<PositionConponent>();

	while (1)
	{
		mane.UpDate();
		std::cout << me.GetComponent<PositionConponent>().X() << std::endl;

		if (me.GetComponent<PositionConponent>().X() >= 300)
		{
			break;
		}
	}

	system("pause");
}