/*
<2021 SW������� 19�� ��������Ʈ - 2scape Project(Game)> v1.0.2
���� : �̽���
���� : ���α�, ����ȣ, �ѿ���

<����ȯ��>
Window 10, Vs2019, C���
*/

//������ ���(1/0) , 0�̸� ���� ������ �� ��������
#define DEVELOP_MODE 0

/*
-----------------<������ �޸� v1.0.2>-----------------

1.��������
-���������� ������ ���� ������ �� ���� ����

2.���� �� ��
-���α׷� �׽�Ʈ �� �����

-----------------------------------------------------
*/



#include "commonModule.h"
#include "designTool.h"
#include "lobbySystem.h"
#include "gameSystem.h"



/*#############################���� ����#############################*/
int main()
{
	//���� �ʱ� ����
	GameSetting();
	//�� ����
	BuildMap();

	//���� ����
	while (1)
	{

		if (gLocation == GLOCATION_STATE)
			StateController();

		if (gLocation == GLOCATION_LOBBY)
		{
			BuildLobby();
			while (gLocation == GLOCATION_LOBBY)
			{
				LobbyLoop(DEVELOP_MODE);
			}
		}

		if (gLocation == GLOCATION_GAME)
		{
			BuildGame(currentLevelIndex);
			while (gLocation == GLOCATION_GAME)
			{
				GameLoop(DEVELOP_MODE);
			}
		}

		if (gLocation == GLOCATION_EXIT)
			break;

		if (gLocation == GLOCATION_LEVELDESIGN)
		{
			BuildLevelDesignTool();
			while (gLocation == GLOCATION_LEVELDESIGN)
			{
				LevelDesignToolLoop();
			}
		}
	}

	//���� ���� ó��
	BuildExit();
	while (1)
		Sleep(10000);
	return 0;
}
/*#############################���� ��#############################*/