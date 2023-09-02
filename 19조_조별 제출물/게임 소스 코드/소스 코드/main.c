/*
<2021 SW설계기초 19조 팀프로젝트 - 2scape Project(Game)> v1.0.2
팀장 : 이승재
팀원 : 강민구, 하윤호, 한요한

<개발환경>
Window 10, Vs2019, C언어
*/

//개발자 모드(1/0) , 0이면 레벨 디자인 툴 접근제한
#define DEVELOP_MODE 0

/*
-----------------<개발자 메모 v1.0.2>-----------------

1.수정사항
-레벨디자인 툴에서 게임 시작할 때 버그 수정

2.남은 할 일
-프로그램 테스트 및 디버깅

-----------------------------------------------------
*/



#include "commonModule.h"
#include "designTool.h"
#include "lobbySystem.h"
#include "gameSystem.h"



/*#############################메인 시작#############################*/
int main()
{
	//게임 초기 설정
	GameSetting();
	//맵 빌드
	BuildMap();

	//게임 진행
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

	//게임 종료 처리
	BuildExit();
	while (1)
		Sleep(10000);
	return 0;
}
/*#############################메인 끝#############################*/