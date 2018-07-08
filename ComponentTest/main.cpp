#include "Component.hpp"
#include <memory>
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	{
		EntityManager mane;

		//Entity�̐���
		auto& me(mane.AddEntity());
		auto& you(mane.AddEntity());
		
		//:(�R����)������Ɗ��̌^���w��ł���
		enum GrpupLabels : std::size_t
		{
			GROUP_ME,
			GROUP_YOU
		};

		me.AddComponent<PositionConponent>(0, 0);		//�����t���R���X�g���N�^���ĂԂƂ��͂�������
		me.AddComponent<EnableComponent>();
		me.AddGroup(GROUP_ME);									//�O���[�v�ɓo�^	
		auto& m_me(mane.GetGroup(GROUP_ME));			//�O���[�v���擾
		you.AddComponent<PositionConponent>(100, 100);
		you.AddGroup(GROUP_YOU);								
		auto& m_you(mane.GetGroup(GROUP_YOU));

		//�O���[�v�������邱�Ƃɂ���āA�`�惌�C���[(�X�V������)�𕪂��邱�Ƃ��ł���!!
		while (true)
		{
			//������������Entity�̑S�̂̍X�V������������������������
			mane.UpDate();
			//mane.Draw();
			//������������������������������������������������������
			//�������������O���[�v���ƂɍX�V������������������������
			for (auto& m : m_me)
			{
				std::cout << "ME�O���[�v�̕`��ł�" << std::endl;
				m->Draw();
			}
			for (auto& y : m_you)
			{
				std::cout << "YOU�O���[�v�̕`��ł�" << std::endl;
				y->Draw();
			}
			//������������������������������������������������������

			me.GetComponent<EnableComponent>().ESCKeyPush_Break();
			if (me.GetComponent<EnableComponent>().IsBreakEnable())
			{
				break;
			}
		}
	}
	system("pause");
}