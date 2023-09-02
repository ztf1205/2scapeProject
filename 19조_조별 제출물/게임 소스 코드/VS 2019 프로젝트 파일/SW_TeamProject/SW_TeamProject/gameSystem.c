#include "commonModule.h"
#include "gameSystem.h"

void GameKeyInput(int developMode)
{
	if (GetAsyncKeyState(VK_UP))
		Jump1P();
	if (GetAsyncKeyState(VK_DOWN)){}
	if (GetAsyncKeyState(VK_LEFT))
		MovingPlayer(1, 'L');
	if (GetAsyncKeyState(VK_RIGHT))
		MovingPlayer(1, 'R');

	if (GetAsyncKeyState(0x57))//W
		MovingPlayer(2, 'U');
	if (GetAsyncKeyState(0x53))//S
		MovingPlayer(2, 'D');
	if (GetAsyncKeyState(0x41))//A
		MovingPlayer(2, 'L');
	if (GetAsyncKeyState(0x44))//D
		MovingPlayer(2, 'R');

	//개발자 모드 전용
	if (developMode)
	{
		if (GetAsyncKeyState(0x4C))//L-라이프 충전
		{
			ClearLog();
			SetColor(UI_COLOR, UI_BACKCOLOR);
			DrawString_Dot(GBOARD_RIGHT_POSITION_X + 11, 37, "라이프 충전!(개발자 모드 전용)");
			P1_Life=SYSTEM_MAX_LIFE;
			P2_Life= SYSTEM_MAX_LIFE;
			Game_Status();//ui업뎃
		}
	}

	if (GetAsyncKeyState(0x51))//Q
	{
		gState = GSTATE_GAMEOVER;
		gLocation = GLOCATION_STATE;
	}

}

void GameLoop(int developMode)
{
	int i, j, k, l;
	//화살 쏘며 시작
	ShootArrow();
	for (i = 0; i < GAMELOOP_4; i++)
	{
		for (j = 0; j < GAMELOOP_3; j++)
		{
			for (k = 0; k < GAMELOOP_2; k++)
			{
				for (l = 0; l < GAMELOOP_1; l++)
				{
					if (gLocation == GLOCATION_STATE)
						break;
					//0.1초마다 입력받고 중력 적용, 라이프처리
					GameKeyInput(developMode);
					GravitySystem();
					LifeSystem();
					SpecialTrigger();
					if (gLocation == GLOCATION_STATE)
						break;
					Sleep(GAMELOOP_TIME);
				}
				if (gLocation == GLOCATION_STATE)
					break;
				//0.5초마다 화살 움직이기
				MoveArrow();
				if (gLocation == GLOCATION_STATE)
					break;
			}
			if (gLocation == GLOCATION_STATE)
				break;
			//1초마다 시간 증가, 클리어타임 증가
			time++;
			ClearTime++;
			Game_Status();//ui업뎃
		}
		if (gLocation == GLOCATION_STATE)
			break;
		//3초마다 화살 발사 및 자동투명블록 처리
		if (i % 2 == 0)
			HideHiddenWall();
		else
			ShowHiddenWall();
		ShootArrow();
		if (gLocation == GLOCATION_STATE)
			break;
	}
	//6초마다
}





void MovingPlayer(int pc, char direction)
{
	int currentPosX, currentPosY;
	int nextPosX, nextPosY;
	int currentBlockType, nextBlockType;

	//pc 값 변환, 현재 칸 알아내기
	if (pc == 1)
	{
		pc = GMAP_PC1;
		currentPosX = P1_PosX;
		currentPosY = P1_PosY;
	}
	else if (pc == 2)
	{
		pc = GMAP_PC2;
		currentPosX = P2_PosX;
		currentPosY = P2_PosY;
	}
	else//잘못된 pc값
		return;


	//다음 칸 알아내기
	switch (direction)
	{
	case 'U':
		nextPosX = currentPosX;
		nextPosY = currentPosY - 1;
		break;
	case 'D':
		nextPosX = currentPosX;
		nextPosY = currentPosY + 1;
		break;
	case 'L':
		nextPosX = currentPosX - 1;
		nextPosY = currentPosY;
		break;
	case 'R':
		nextPosX = currentPosX + 1;
		nextPosY = currentPosY;
		break;
	default://잘못된 방향값
		return;
		break;
	}
	//현재 블럭과 다음 블럭 찾기
	currentBlockType = gameBoardArray[currentPosY][currentPosX] - pc;
	nextBlockType = gameBoardArray[nextPosY][nextPosX];

	//다음 칸으로 움직일 수 있다면
	if (MoveAble(nextBlockType))
	{
		MoveOutTrigger(pc, currentBlockType, nextBlockType);
		MoveInTrigger(pc, currentBlockType, nextBlockType);
		//한칸 움직이기(pc좌표 전역변수 변화 및 게임보드 업데이트)
		if (pc == GMAP_PC1)
		{
			P1_PosX = nextPosX;
			P1_PosY = nextPosY;
		}
		else//pc==GMAP_PC2
		{
			P2_PosX = nextPosX;
			P2_PosY = nextPosY;
		}

		if (IsButton(currentBlockType) || IsHiddenLockWall(currentBlockType))
			MoveOutGameBoard(currentPosX, currentPosY, pc);
		else
			UpdateGameBoard(currentPosX, currentPosY, GMAP_SPACE);

		if(IsButton(nextBlockType) || IsHiddenLockWall(nextBlockType))
			MoveInGameBoard(nextPosX, nextPosY, pc);
		else
			UpdateGameBoard(nextPosX, nextPosY, pc);

	}
	//다음 칸으로 움직일 수 없다면
	else
	{
		StopTrigger(pc, nextBlockType);
	}
}


int IsButton(int type)
{
	int isButton = 0;
	switch (type)
	{
	case GMAP_BUTTON_BLUE:
	case GMAP_BUTTON_GREEN:
	case GMAP_BUTTON_MINT:
	case GMAP_BUTTON_RED:
	case GMAP_BUTTON_PURPLE:
	case GMAP_BUTTON_YELLOW:
	case GMAP_TOGGLE_BUTTON_BLUE:
	case GMAP_TOGGLE_BUTTON_GREEN:
	case GMAP_TOGGLE_BUTTON_MINT:
	case GMAP_TOGGLE_BUTTON_RED:
	case GMAP_TOGGLE_BUTTON_PURPLE:
	case GMAP_TOGGLE_BUTTON_YELLOW:
	case GMAP_FAKEBUTTON_BLUE:
	case GMAP_FAKEBUTTON_GREEN:
	case GMAP_FAKEBUTTON_MINT:
	case GMAP_FAKEBUTTON_RED:
	case GMAP_FAKEBUTTON_PURPLE:
	case GMAP_FAKEBUTTON_YELLOW:
		isButton = 1;
		break;
	default:
		break;
	}
	return isButton;
}

int IsLockWall(int type)
{
	int isLockWall = 0;
	switch (type)
	{
	case GMAP_LOCKWALL_BLUE:
	case GMAP_LOCKWALL_GREEN:
	case GMAP_LOCKWALL_MINT:
	case GMAP_LOCKWALL_RED:
	case GMAP_LOCKWALL_PURPLE:
	case GMAP_LOCKWALL_YELLOW:
		isLockWall = 1;
		break;
	default:
		break;
	}

	return isLockWall;
}

int IsHiddenLockWall(int type)
{
	int isHiddenLockWall = 0;
	switch (type)
	{
	case GMAP_LOCKWALL_HIDE_BLUE:
	case GMAP_LOCKWALL_HIDE_GREEN:
	case GMAP_LOCKWALL_HIDE_MINT:
	case GMAP_LOCKWALL_HIDE_RED:
	case GMAP_LOCKWALL_HIDE_PURPLE:
	case GMAP_LOCKWALL_HIDE_YELLOW:
		isHiddenLockWall = 1;
		break;
	default:
		break;
	}

	return isHiddenLockWall;
}



void Jump1P(void)
{
	if (JumpAble())
	{
		jumpRemain = SYSTEM_MAX_JUMPHEIGHT;
		StopTrigger(GMAP_PC1, gameBoardArray[P1_PosY + 1][P1_PosX]);
	}
}


void GravitySystem(void)
{
	if (jumpRemain == 0)
	{
		jumpRemain--;
	}
	else if (jumpRemain > 0)
	{
		MovingPlayer(GMAP_PC1, 'U');
		jumpRemain--;
	}
	else
	{
		MovingPlayer(GMAP_PC1, 'D');
	}
}



void LifeSystem(void)
{
	LifeSystem_PC1();
	//1피 사망시 어차피 게임오버니까 2피는 처리X
	if (gLocation == GLOCATION_STATE)
		return;
	LifeSystem_PC2();
}



void LifeSystem_PC1(void)
{
	//맞았는데 무적이 아니라면 피격처리
	if (P1_HitFlag && P1_InvincibleTimeRemain == 0)
	{
		//라이프 감소
		P1_Life--;
		P2_Life--;
		Game_Status();//ui업뎃
		//대사 출력
		ClearLog();
		SetColor(1, UI_BACKCOLOR);
		DrawString_Dot(GBOARD_RIGHT_POSITION_X + 11, 37, "잭");
		SetColor(UI_COLOR, UI_BACKCOLOR);
		DrawString_Dot(GBOARD_RIGHT_POSITION_X + 15, 37, ": 으악!... 참고 반드시 나가야해..!");
		//피격 이펙트
		Effect_Blink(RED);
		//남은 라이프 없으면
		if (P1_Life <= 0)
		{
			Death(GMAP_PC1);
		}
		//남은 라이프 있으면
		else
		{
			//무적시작
			P1_InvincibleTimeRemain = SYSTEM_MAX_INVINCIBLETIME;
		}
	}
	//무적 or 맞지 않음
	else
	{
		//무적이라면
		if (P1_InvincibleTimeRemain > 0)
		{
			//무적시간 감소
			P1_InvincibleTimeRemain--;
		}
	}
	//플래그 초기화
	P1_HitFlag = 0;
}


void LifeSystem_PC2(void)
{
	//맞았는데 무적이 아니라면 피격처리
	if (P2_HitFlag && P2_InvincibleTimeRemain == 0)
	{
		//라이프 감소
		P1_Life--;
		P2_Life--;
		Game_Status();//ui업뎃
		//대사 출력
		ClearLog();
		SetColor(4, UI_BACKCOLOR);
		DrawString_Dot(GBOARD_RIGHT_POSITION_X + 11, 37, "로즈");
		SetColor(UI_COLOR, UI_BACKCOLOR);
		DrawString_Dot(GBOARD_RIGHT_POSITION_X + 17, 37, ": 아야! 이러면.. 우린 나갈 수 없어.");
		//피격 이펙트
		Effect_Blink(RED);
		//남은 라이프 없으면
		if (P2_Life <= 0)
		{
			Death(GMAP_PC2);
		}
		//남은 라이프 있으면
		else
		{
			//무적시작
			P2_InvincibleTimeRemain = SYSTEM_MAX_INVINCIBLETIME;
		}
	}
	//무적 or 맞지 않음
	else
	{
		//무적이라면
		if (P2_InvincibleTimeRemain > 0)
		{
			//무적시간 감소
			P2_InvincibleTimeRemain--;
		}
	}
	//플래그 초기화
	P2_HitFlag = 0;
}

void LifeUp_PC1(void)
{
	if (P1_LifeUpFlag == 1)
	{
		if (P1_Life >= SYSTEM_MAX_LIFE)
		{
			ClearLog();
			SetColor(UI_COLOR, UI_BACKCOLOR);
			DrawString_Dot(GBOARD_RIGHT_POSITION_X + 11, 37, "라이프가 가득 찼습니다.");
			P1_Life = SYSTEM_MAX_LIFE;
			P2_Life = SYSTEM_MAX_LIFE;
		}
		else
		{
			ClearLog();
			SetColor(UI_COLOR, UI_BACKCOLOR);
			DrawString_Dot(GBOARD_RIGHT_POSITION_X + 11, 37, "라이프 보너스! Life + 1");
			P1_Life++;
			P2_Life++;
			Game_Status();//ui업뎃
		}
	}

	P1_LifeUpFlag = 0;
}

void LifeUp_PC2(void)
{
	if (P2_LifeUpFlag == 1)
	{
		if (P2_Life >= SYSTEM_MAX_LIFE)
		{
			ClearLog();
			SetColor(UI_COLOR, UI_BACKCOLOR);
			DrawString_Dot(GBOARD_RIGHT_POSITION_X + 11, 37, "라이프가 가득 찼습니다.");
			P1_Life = SYSTEM_MAX_LIFE;
			P2_Life = SYSTEM_MAX_LIFE;
		}
		else
		{
			ClearLog();
			SetColor(UI_COLOR, UI_BACKCOLOR);
			DrawString_Dot(GBOARD_RIGHT_POSITION_X + 11, 37, "라이프 보너스! Life + 1");
			P1_Life++;
			P2_Life++;
			Game_Status();//ui업뎃
		}
	}
	P2_LifeUpFlag = 0;
}


int MoveAble(int nextBlockType)
{
	int moveAble;
	
	switch (nextBlockType)
	{
	case GMAP_SPACE:
	case GMAP_DOOR:
	case GMAP_BOMB:
	case GMAP_ARROW_UP:
	case GMAP_ARROW_DOWN:
	case GMAP_ARROW_LEFT:
	case GMAP_ARROW_RIGHT:
	case GMAP_KEY_BLUE:
	case GMAP_KEY_GREEN:
	case GMAP_KEY_MINT:
	case GMAP_KEY_RED:
	case GMAP_KEY_PURPLE:
	case GMAP_KEY_YELLOW:
	case GMAP_BUTTON_BLUE:
	case GMAP_BUTTON_GREEN:
	case GMAP_BUTTON_MINT:
	case GMAP_BUTTON_RED:
	case GMAP_BUTTON_PURPLE:
	case GMAP_BUTTON_YELLOW:
	case GMAP_TOGGLE_BUTTON_BLUE:
	case GMAP_TOGGLE_BUTTON_GREEN:
	case GMAP_TOGGLE_BUTTON_MINT:
	case GMAP_TOGGLE_BUTTON_RED:
	case GMAP_TOGGLE_BUTTON_PURPLE:
	case GMAP_TOGGLE_BUTTON_YELLOW:
	case GMAP_LOCKWALL_HIDE_BLUE:
	case GMAP_LOCKWALL_HIDE_GREEN:
	case GMAP_LOCKWALL_HIDE_MINT:
	case GMAP_LOCKWALL_HIDE_RED:
	case GMAP_LOCKWALL_HIDE_PURPLE:
	case GMAP_LOCKWALL_HIDE_YELLOW:
	case GMAP_FAKEBUTTON_BLUE:
	case GMAP_FAKEBUTTON_GREEN:
	case GMAP_FAKEBUTTON_MINT:
	case GMAP_FAKEBUTTON_RED:
	case GMAP_FAKEBUTTON_PURPLE:
	case GMAP_FAKEBUTTON_YELLOW:
	case GMAP_LIFEUP:
		moveAble = 1;
		break;
	default:
		moveAble = 0;
		break;
	}
	return moveAble;
}

int JumpAble(void)
{
	int jumpAble;
	int floorBlock = gameBoardArray[P1_PosY + 1][P1_PosX];

	jumpAble = !MoveAble(floorBlock);

	return jumpAble;
}

void MoveOutTrigger(int pc, int currentBlockType, int nextBlockType)
{
	switch (currentBlockType)
	{
	case GMAP_TOGGLE_BUTTON_BLUE:
	case GMAP_TOGGLE_BUTTON_GREEN:
	case GMAP_TOGGLE_BUTTON_MINT:
	case GMAP_TOGGLE_BUTTON_RED:
	case GMAP_TOGGLE_BUTTON_PURPLE:
	case GMAP_TOGGLE_BUTTON_YELLOW:
		Trigger_ToggleButton_MoveOut(currentBlockType, nextBlockType);
		break;
	default:
		break;
	}
}

void MoveInTrigger(int pc,int currentBlockType, int nextBlockType)
{
	switch (nextBlockType)
	{
	case GMAP_DOOR:
		Trigger_Door(pc);
		break;
	case GMAP_BOMB:
	case GMAP_ARROW_UP:
	case GMAP_ARROW_DOWN:
	case GMAP_ARROW_LEFT:
	case GMAP_ARROW_RIGHT:
		Trigger_Damage(pc);
		break;
	case GMAP_KEY_BLUE:
	case GMAP_KEY_GREEN:
	case GMAP_KEY_MINT:
	case GMAP_KEY_RED:
	case GMAP_KEY_PURPLE:
	case GMAP_KEY_YELLOW:
		Trigger_Key(nextBlockType);
		break;
	case GMAP_BUTTON_BLUE:
	case GMAP_BUTTON_GREEN:
	case GMAP_BUTTON_MINT:
	case GMAP_BUTTON_RED:
	case GMAP_BUTTON_PURPLE:
	case GMAP_BUTTON_YELLOW:
		Trigger_Button(currentBlockType, nextBlockType);
		break;
	case GMAP_TOGGLE_BUTTON_BLUE:
	case GMAP_TOGGLE_BUTTON_GREEN:
	case GMAP_TOGGLE_BUTTON_MINT:
	case GMAP_TOGGLE_BUTTON_RED:
	case GMAP_TOGGLE_BUTTON_PURPLE:
	case GMAP_TOGGLE_BUTTON_YELLOW:
		Trigger_ToggleButton_MoveIn(nextBlockType);
		break;
	case GMAP_LIFEUP:
		P1_LifeUpFlag = 1;
		LifeUp_PC1();
	default:
		break;
	}
}

void StopTrigger(int pc, int nextBlockType)
{
	switch (nextBlockType)
	{
	case GMAP_BOSS:
	case GMAP_SPIKE_UP:
	case GMAP_SPIKE_DOWN:
	case GMAP_SPIKE_LEFT:
	case GMAP_SPIKE_RIGHT:
	case GMAP_SHOOTER_UP:
	case GMAP_SHOOTER_DOWN:
	case GMAP_SHOOTER_LEFT:
	case GMAP_SHOOTER_RIGHT:
		Trigger_Damage(pc);
		break;
	default:
		break;
	}
}


void BuildGame(int index)
{
	int i, j;
	for (i = 0; i <= GARRAY_HEIGHT_MAXINDEX; i++)
	{
		for (j = 0; j <= GARRAY_WIDTH_MAXINDEX; j++)
		{
			gameBoardArray[i][j] = map[index][i][j];
			DrawGameBoard(j, i, gameBoardArray[i][j]);
			if (gameBoardArray[i][j] == GMAP_PC1)
			{
				P1_PosX = j;
				P1_PosY = i;
			}
			if (gameBoardArray[i][j] == GMAP_PC2)
			{
				P2_PosX = j;
				P2_PosY = i;
			}
		}
	}
	//시간 초기화
	time = 0;

	//플래그, 무적시간 초기화
	P1_HitFlag = 0;
	P2_HitFlag = 0;
	P1_InvincibleTimeRemain = 0;
	P2_InvincibleTimeRemain = 0;


	ClearUI();
	Game_Status();

	inputReset();
}




void DrawGameBoard(int x, int y, int mapData)
{
	SetColor(mapData_Color[FindMapDataIndex(mapData)], mapData_BackColor[FindMapDataIndex(mapData)]);
	DrawString_Dot(GBOARD_LEFT_POSITION_X + x * 2, GBOARD_TOP_POSITION_Y + y, mapData_Char[FindMapDataIndex(mapData)]);
}


void ChangeGameBoard(int x, int y, int mapData)
{
	gameBoardArray[y][x] = mapData;
}

void UpdateGameBoard(int x, int y, int mapData)
{
	DrawGameBoard(x, y, mapData);
	ChangeGameBoard(x, y, mapData);
}

void MoveOutGameBoard(int x, int y, int pc)
{
	gameBoardArray[y][x] -= pc;
	DrawGameBoard(x, y, gameBoardArray[y][x]);
}

void MoveInGameBoard(int x, int y, int pc)
{
	gameBoardArray[y][x] += pc;
	DrawGameBoard(x, y, gameBoardArray[y][x]);
}


void ShootArrow(void)
{
	int i, j;

	//플레이어가 화살에 맞았는지 안맞았는지 저장하는 플래그. 0=안맞음, 1=p1맞음, 2=p2맞음, 3=p1,p2 둘 다 맞음
	int hitFlag = 0;

	//발사할 화살의 타입
	int arrowType = -1;

	//화살이 발사될 위치
	int arrowPosX, arrowPosY;

	
	//맵 정보를 읽으면서 화살 발사, 충돌 판정
	for (i = 1; i < GARRAY_HEIGHT_MAXINDEX; i++)
	{
		for (j = 1; j < GARRAY_WIDTH_MAXINDEX; j++)
		{
			//해당칸 슈터인지 확인하고 좌표 할당
			switch (gameBoardArray[i][j])
			{
			case GMAP_SHOOTER_UP:
				arrowType = GMAP_ARROW_UP;
				arrowPosX = j;
				arrowPosY = i - 1;
				break;
			case GMAP_SHOOTER_DOWN:
				arrowType = GMAP_ARROW_DOWN;
				arrowPosX = j;
				arrowPosY = i + 1;
				break;
			case GMAP_SHOOTER_LEFT:
				arrowType = GMAP_ARROW_LEFT;
				arrowPosX = j - 1;
				arrowPosY = i;
				break;
			case GMAP_SHOOTER_RIGHT:
				arrowType = GMAP_ARROW_RIGHT;
				arrowPosX = j + 1;
				arrowPosY = i;
				break;
			default:
				arrowType = -1;
				break;
			}

			//화살이 아니면 다음 블럭으로 넘어가기
			if (arrowType == -1)
				continue;
			//화살이면 발사
			else
			{
				//빈공간이면 발사
				if (gameBoardArray[arrowPosY][arrowPosX] == GMAP_SPACE)
				{
					UpdateGameBoard(arrowPosX, arrowPosY, arrowType);
				}
				//플레이어면 맞기
				else if (gameBoardArray[arrowPosY][arrowPosX] == GMAP_PC1)
				{
					P1_HitFlag = 1;
				}
				//플레이어면 맞기
				else if (gameBoardArray[arrowPosY][arrowPosX] == GMAP_PC2)
				{
					P2_HitFlag = 2;
				}
			}
		}
	}
}


void MoveArrow(void)
{
	int i, j;

	//각 화살의 위치정보를 저장하는 arrowArray, x좌표,y좌표,type 저장
	int arrowArray[SYSTEM_MAX_ARRAYINDEX][3] = { 0 };

	//현재 데이터가 저장된 최대 인덱스를 저장하는 arrowArrayMaxIndex
	int arrowArrayMaxIndex = -1;
	
	//플레이어가 화살에 맞았는지 안맞았는지 저장하는 플래그. 0=안맞음, 1=p1맞음, 2=p2맞음, 3=p1,p2 둘 다 맞음
	int hitFlag = 0;

	//움직일 화살의 타입
	int arrowType = -1;

	//화살이 움직일 위치
	int arrowPosX, arrowPosY;

	//맵 정보를 읽으면서 화살을 임시 배열에 저장하고 맵에 있는 화살은 지우기
	for (i = 0; i <= GARRAY_HEIGHT_MAXINDEX; i++)
	{
		for (j = 0; j <= GARRAY_WIDTH_MAXINDEX; j++)
		{
			//화살인지 확인
			switch (gameBoardArray[i][j])
			{
			case GMAP_ARROW_UP:
			case GMAP_ARROW_DOWN:
			case GMAP_ARROW_LEFT:
			case GMAP_ARROW_RIGHT:
				arrowType = gameBoardArray[i][j];
				break;
			default:
				arrowType = -1;
				break;
			}

			//화살이 아니면 다음 블럭
			if (arrowType == -1)
				continue;
			//화살이면 arrowArray에 화살 정보 추가
			else
			{
				arrowArrayMaxIndex++;
				arrowArray[arrowArrayMaxIndex][0] = j;
				arrowArray[arrowArrayMaxIndex][1] = i;
				arrowArray[arrowArrayMaxIndex][2] = arrowType;
				UpdateGameBoard(j, i, GMAP_SPACE);
			}
		}
	}

	//배열에 있는 화살들을 방향대로 한칸씩 움직이고 새롭게 배정, 충돌 판정
	for (i = 0; i <= arrowArrayMaxIndex; i++)
	{
		//화살타입에 따라서 다음으로 움직일 위치 할당
		arrowType = arrowArray[i][2];
		switch (arrowType)
		{
		case GMAP_ARROW_UP:
			arrowPosX = arrowArray[i][0];
			arrowPosY = arrowArray[i][1] - 1;
			break;
		case GMAP_ARROW_DOWN:
			arrowPosX = arrowArray[i][0];
			arrowPosY = arrowArray[i][1] + 1;
			break;
		case GMAP_ARROW_LEFT:
			arrowPosX = arrowArray[i][0] - 1;
			arrowPosY = arrowArray[i][1];
			break;
		case GMAP_ARROW_RIGHT:
			arrowPosX = arrowArray[i][0] + 1;
			arrowPosY = arrowArray[i][1];
			break;
		default:
			break;
		}

		//빈공간이면 움직이기
		if (gameBoardArray[arrowPosY][arrowPosX] == GMAP_SPACE)
		{
			UpdateGameBoard(arrowPosX, arrowPosY, arrowType);
		}
		//p1이 있으면 데미지
		else if (gameBoardArray[arrowPosY][arrowPosX] == GMAP_PC1)
		{
			P1_HitFlag = 1;
		}
		//p2가 있으면 데미지
		else if (gameBoardArray[arrowPosY][arrowPosX] == GMAP_PC2)
		{
			P2_HitFlag = 2;
		}
		else
		{
			//다른 물체면 별다른 행동없이 그냥 소멸
		}
	}
}


void ShowHiddenWall(void)
{
	int x, y;
	//반복문 돌며 숨김 벽 보여주기
	for (y = 0; y <= GARRAY_WIDTH_MAXINDEX; y++)
	{
		for (x = 0; x <= GARRAY_WIDTH_MAXINDEX; x++)
		{
			if (gameBoardArray[y][x] == GMAP_HIDDENWALL)
			{
				DrawGameBoard(x, y, GMAP_HIDDENWALL);
			}
		}
	}
}

void HideHiddenWall(void)
{
	int x, y;
	//반복문 돌며 숨김 벽 숨기기
	for (y = 0; y <= GARRAY_WIDTH_MAXINDEX; y++)
	{
		for (x = 0; x <= GARRAY_WIDTH_MAXINDEX; x++)
		{
			if (gameBoardArray[y][x] == GMAP_HIDDENWALL)
			{
				DrawGameBoard(x, y, GMAP_SPACE);
			}
		}
	}
}


void Retry(void)
{
	//코인 감소
	coin--;
	DeathCount++;//데스카운트 업뎃
	Game_Status();//ui업뎃
	if (coin)//남은 코인 있으면
	{
		//pc의 목숨 초기화
		P1_Life = SYSTEM_START_LIFE;
		P2_Life = SYSTEM_START_LIFE;
		//재시작
		gState = GSTATE_RETRY;
		gLocation = GLOCATION_STATE;
	}
	else//남은 코인 없으면
	{
		//게임오버
		gState = GSTATE_GAMEOVER;
		gLocation = GLOCATION_STATE;
	}
}

void Death(int pc)
{
	int pcPosX, pcPosY;

	//pc에 따라서 pc 위치 알아내기
	switch (pc)
	{
	case GMAP_PC1:
		pcPosX = P1_PosX;
		pcPosY = P1_PosY;
		break;
	case GMAP_PC2:
		pcPosX = P2_PosX;
		pcPosY = P2_PosY;
		break;
	default:
		//잘못된 pc값
		return;
		break;
	}

	//이펙트 주고 retry처리
	Effect_Square(pcPosX, pcPosY, RED, 5, 250);
	Retry();
}


void Death_Wall(int pc)
{
	//라이프 감소
	P1_Life = 0;
	P2_Life = 0;
	Game_Status();//ui업뎃
	Death(pc);
	DrawOutline();
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 24, "앗! 벽에 끼이지 않게 조심해야 합니다.");
	Sleep(1500);
}


/* 트리거 */

void Trigger_ToggleButton_MoveOut(int currentBlockType, int nextBlockType)
{
	int x, y;
	int hiddenColorWall, baseColorWall;
	
	//두 플레이어가 모두 밝고 있는 상황이면 그대로 유지해야 하므로 변경사항X-리턴
	if (gameBoardArray[P1_PosY][P1_PosX] == currentBlockType + GMAP_PC1 && gameBoardArray[P2_PosY][P2_PosX] == currentBlockType + GMAP_PC2)
	{
		return;
	}

	//다음 칸이 같은 토글버튼이면 계속 밝게 되므로 변경사항X-리턴
	if (currentBlockType == nextBlockType)
	{
		return;
	}


	//버튼에 따라 벽 색깔 판단
	switch (currentBlockType)
	{
	case GMAP_TOGGLE_BUTTON_BLUE:
		hiddenColorWall = GMAP_LOCKWALL_HIDE_BLUE;
		baseColorWall = GMAP_LOCKWALL_BLUE;
		break;
	case GMAP_TOGGLE_BUTTON_GREEN:
		hiddenColorWall = GMAP_LOCKWALL_HIDE_GREEN;
		baseColorWall = GMAP_LOCKWALL_GREEN;
		break;
	case GMAP_TOGGLE_BUTTON_MINT:
		hiddenColorWall = GMAP_LOCKWALL_HIDE_MINT;
		baseColorWall = GMAP_LOCKWALL_MINT;
		break;
	case GMAP_TOGGLE_BUTTON_RED:
		hiddenColorWall = GMAP_LOCKWALL_HIDE_RED;
		baseColorWall = GMAP_LOCKWALL_RED;
		break;
	case GMAP_TOGGLE_BUTTON_PURPLE:
		hiddenColorWall = GMAP_LOCKWALL_HIDE_PURPLE;
		baseColorWall = GMAP_LOCKWALL_PURPLE;
		break;
	case GMAP_TOGGLE_BUTTON_YELLOW:
		hiddenColorWall = GMAP_LOCKWALL_HIDE_YELLOW;
		baseColorWall = GMAP_LOCKWALL_YELLOW;
		break;
	default://잘못된 버튼 값
		return;
		break;
	}


	//플레이어랑 겹치게 되면 한방에 죽고 코인 감소처리
	if (gameBoardArray[P1_PosY][P1_PosX] == hiddenColorWall + GMAP_PC1)
	{
		Death_Wall(GMAP_PC1);
		return;
	}
	else if (gameBoardArray[P2_PosY][P2_PosX] == hiddenColorWall + GMAP_PC2)
	{
		Death_Wall(GMAP_PC2);
		return;
	}

	//반복문 돌며 숨겨진 벽 다시 등장
	for (y = 0; y <= GARRAY_WIDTH_MAXINDEX; y++)
	{
		for (x = 0; x <= GARRAY_WIDTH_MAXINDEX; x++)
		{
			if (gameBoardArray[y][x] == hiddenColorWall)
			{
				UpdateGameBoard(x, y, baseColorWall);
			}
		}
	}
}




void Trigger_Door(int pc)
{
	int pcPosX, pcPosY;
	PlaySound(TEXT("start.wav"), NULL, SND_ASYNC); // 일반 재생
	//pc에 따라서 pc 위치 알아내기
	switch (pc)
	{
	case GMAP_PC1:
		pcPosX = P1_PosX;
		pcPosY = P1_PosY;
		break;
	case GMAP_PC2:
		pcPosX = P2_PosX;
		pcPosY = P2_PosY;
		break;
	default:
		//잘못된 pc값
		return;
		break;
	}

	//이펙트 주고 클리어처리
	Effect_Square(pcPosX, pcPosY, WHITE, 5, 250);
	gState = GSTATE_CLEAR;
	gLocation = GLOCATION_STATE;
	PlaySound(TEXT("bgm.wav"), NULL, SND_ASYNC | SND_LOOP); // 반복 재생
}

void Trigger_Key(int nextBlockType)
{
	int x, y;
	int hiddenColorWall, baseColorWall;
	int keyAmount = 0;


	switch (nextBlockType)
	{
	case GMAP_KEY_BLUE:
		hiddenColorWall = GMAP_LOCKWALL_HIDE_BLUE;
		baseColorWall = GMAP_LOCKWALL_BLUE;
		break;
	case GMAP_KEY_GREEN:
		hiddenColorWall = GMAP_LOCKWALL_HIDE_GREEN;
		baseColorWall = GMAP_LOCKWALL_GREEN;
		break;
	case GMAP_KEY_MINT:
		hiddenColorWall = GMAP_LOCKWALL_HIDE_MINT;
		baseColorWall = GMAP_LOCKWALL_MINT;
		break;
	case GMAP_KEY_RED:
		hiddenColorWall = GMAP_LOCKWALL_HIDE_RED;
		baseColorWall = GMAP_LOCKWALL_RED;
		break;
	case GMAP_KEY_PURPLE:
		hiddenColorWall = GMAP_LOCKWALL_HIDE_PURPLE;
		baseColorWall = GMAP_LOCKWALL_PURPLE;
		break;
	case GMAP_KEY_YELLOW:
		hiddenColorWall = GMAP_LOCKWALL_HIDE_YELLOW;
		baseColorWall = GMAP_LOCKWALL_YELLOW;
		break;
	default:
		return;
		break;
	}

	//키 갯수 찾기
	for (y = 0; y <= GARRAY_WIDTH_MAXINDEX; y++)
	{
		for (x = 0; x <= GARRAY_WIDTH_MAXINDEX; x++)
		{
			if (gameBoardArray[y][x] == nextBlockType)
			{
				keyAmount++;
			}
		}
	}

	//키 2개 이상이면 넘어가기
	if (keyAmount >= 2)
	{
		return;
	}
	//키 1개면 열기
	else
	{
		for (y = 0; y <= GARRAY_WIDTH_MAXINDEX; y++)
		{
			for (x = 0; x <= GARRAY_WIDTH_MAXINDEX; x++)
			{
				//벽이나 색깔벽이면 빈공간으로
				if (gameBoardArray[y][x] == baseColorWall || gameBoardArray[y][x] == hiddenColorWall)
				{
					UpdateGameBoard(x, y, GMAP_SPACE);
				}
				//PC와 겹쳐 있으면 PC로
				else if (gameBoardArray[y][x] == hiddenColorWall + GMAP_PC1 || gameBoardArray[y][x] == hiddenColorWall + GMAP_PC2)
				{
					UpdateGameBoard(x, y, gameBoardArray[y][x] - hiddenColorWall);
				}
			}
		}
	}
}

void Trigger_Button(int currentBlockType, int nextBlockType)
{
	int x, y;
	int hiddenColorWall, baseColorWall;
	int buttonAmount = 0;


	switch (nextBlockType)
	{
	case GMAP_BUTTON_BLUE:
		hiddenColorWall = GMAP_LOCKWALL_HIDE_BLUE;
		baseColorWall = GMAP_LOCKWALL_BLUE;
		break;
	case GMAP_BUTTON_GREEN:
		hiddenColorWall = GMAP_LOCKWALL_HIDE_GREEN;
		baseColorWall = GMAP_LOCKWALL_GREEN;
		break;
	case GMAP_BUTTON_MINT:
		hiddenColorWall = GMAP_LOCKWALL_HIDE_MINT;
		baseColorWall = GMAP_LOCKWALL_MINT;
		break;
	case GMAP_BUTTON_RED:
		hiddenColorWall = GMAP_LOCKWALL_HIDE_RED;
		baseColorWall = GMAP_LOCKWALL_RED;
		break;
	case GMAP_BUTTON_PURPLE:
		hiddenColorWall = GMAP_LOCKWALL_HIDE_PURPLE;
		baseColorWall = GMAP_LOCKWALL_PURPLE;
		break;
	case GMAP_BUTTON_YELLOW:
		hiddenColorWall = GMAP_LOCKWALL_HIDE_YELLOW;
		baseColorWall = GMAP_LOCKWALL_YELLOW;
		break;
	default:
		return;
		break;
	}


	//버튼 갯수 찾기
	for (y = 0; y <= GARRAY_WIDTH_MAXINDEX; y++)
	{
		for (x = 0; x <= GARRAY_WIDTH_MAXINDEX; x++)
		{
			if (gameBoardArray[y][x] == nextBlockType)
			{
				buttonAmount++;
			}
		}
	}
	
	//자신의 칸에서 이미 누르고 있어서 +-=0이면 리턴
	if (currentBlockType == nextBlockType)
	{
		return;
	}
	//안눌린 버튼 2개 이상이면 넘어가기
	else if (buttonAmount >= 2)
	{
		return;
	}
	//버튼 1개면 열기
	else
	{
		for (y = 0; y <= GARRAY_WIDTH_MAXINDEX; y++)
		{
			for (x = 0; x <= GARRAY_WIDTH_MAXINDEX; x++)
			{
				//벽이나 색깔벽이면 빈공간으로
				if (gameBoardArray[y][x] == baseColorWall || gameBoardArray[y][x] == hiddenColorWall)
				{
					UpdateGameBoard(x, y, GMAP_SPACE);
				}
				//PC와 겹쳐 있으면 PC로
				else if (gameBoardArray[y][x] == hiddenColorWall + GMAP_PC1 || gameBoardArray[y][x] == hiddenColorWall + GMAP_PC2)
				{
					UpdateGameBoard(x, y, gameBoardArray[y][x] - hiddenColorWall);
				}
			}
		}
	}
}

void Trigger_ToggleButton_MoveIn(int nextBlockType)
{
	int x, y;
	int hiddenColorWall, baseColorWall;


	//버튼에 따라 벽 색깔 판단
	switch (nextBlockType)
	{
	case GMAP_TOGGLE_BUTTON_BLUE:
		hiddenColorWall = GMAP_LOCKWALL_HIDE_BLUE;
		baseColorWall = GMAP_LOCKWALL_BLUE;
		break;
	case GMAP_TOGGLE_BUTTON_GREEN:
		hiddenColorWall = GMAP_LOCKWALL_HIDE_GREEN;
		baseColorWall = GMAP_LOCKWALL_GREEN;
		break;
	case GMAP_TOGGLE_BUTTON_MINT:
		hiddenColorWall = GMAP_LOCKWALL_HIDE_MINT;
		baseColorWall = GMAP_LOCKWALL_MINT;
		break;
	case GMAP_TOGGLE_BUTTON_RED:
		hiddenColorWall = GMAP_LOCKWALL_HIDE_RED;
		baseColorWall = GMAP_LOCKWALL_RED;
		break;
	case GMAP_TOGGLE_BUTTON_PURPLE:
		hiddenColorWall = GMAP_LOCKWALL_HIDE_PURPLE;
		baseColorWall = GMAP_LOCKWALL_PURPLE;
		break;
	case GMAP_TOGGLE_BUTTON_YELLOW:
		hiddenColorWall = GMAP_LOCKWALL_HIDE_YELLOW;
		baseColorWall = GMAP_LOCKWALL_YELLOW;
		break;
	default://잘못된 버튼 값
		return;
		break;
	}

	//반복문 돌며 숨겨진 벽 다시 등장
	for (y = 0; y <= GARRAY_WIDTH_MAXINDEX; y++)
	{
		for (x = 0; x <= GARRAY_WIDTH_MAXINDEX; x++)
		{
			if (gameBoardArray[y][x] == baseColorWall)
			{
				UpdateGameBoard(x, y, hiddenColorWall);
			}
		}
	}
}





void Trigger_Damage(int hitPc)
{
	switch (hitPc)
	{
	case GMAP_PC1:
		P1_HitFlag = 1;
		break;
	case GMAP_PC2:
		P2_HitFlag = 1;
		break;
	default:
		break;
	}
}






void SpecialTrigger(void)
{
	switch (currentLevelIndex + 1)
	{
	case SYSTEM_MAX_LEVEL:
		SpecialTrigger_Boss();
		break;
	default:
		break;
	}
}


void SpecialTrigger_Boss(void)
{
	int i;
	int x, y;
	int clearFlag = 1;
	
	//색깔벽이 있는지 판별 후 플래그 설정
	for (y = 0; y <= GARRAY_HEIGHT_MAXINDEX; y++)
	{
		for (x = 0; x <= GARRAY_WIDTH_MAXINDEX; x++)
		{
			if (IsLockWall(gameBoardArray[y][x]) || IsHiddenLockWall(gameBoardArray[y][x]))
			{
				clearFlag = 0;
				break;
			}
		}
		if (clearFlag == 0)
			break;
	}

	//색깔벽 없다면 클리어처리
	if (clearFlag)
	{
		//대사
		ClearLog();
		SetColor(1, UI_BACKCOLOR);
		DrawString_Dot(GBOARD_RIGHT_POSITION_X + 11, 37, "잭");
		SetColor(4, UI_BACKCOLOR);
		DrawString_Dot(GBOARD_RIGHT_POSITION_X + 11, 38, "로즈");
		SetColor(UI_COLOR, UI_BACKCOLOR);
		DrawString_Dot(GBOARD_RIGHT_POSITION_X + 15, 37, ": 우리가 해냈어, 로즈! ");
		DrawString_Dot(GBOARD_RIGHT_POSITION_X + 17, 38, ": 이제 어서 빠져나가자");
		//이펙트주기
		PlaySound(TEXT("start.wav"), NULL, SND_ASYNC); // 일반 재생
		Effect_Rotation(GREY);
		Effect_Rotation_Keep(GREY);
		//보스벽과 보스 없애기
		for (y = 0; y <= GARRAY_HEIGHT_MAXINDEX; y++)
		{
			for (x = 0; x <= GARRAY_WIDTH_MAXINDEX; x++)
			{
				if (gameBoardArray[y][x] == GMAP_BOSS_WALL || gameBoardArray[y][x] == GMAP_BOSS)
				{
					UpdateGameBoard(x, y, GMAP_SPACE);
					Sleep(1);
				}
			}
		}
		//폭죽
		PlaySound(TEXT("firework.wav"), NULL, SND_ASYNC); // 일반 재생
		Effect_Square(25, 20, BLUE_DARK, 0, 0);
		PlaySound(TEXT("firework.wav"), NULL, SND_ASYNC); // 일반 재생
		Effect_Square(20, 15, RED_DARK, 0, 0);
		PlaySound(TEXT("firework.wav"), NULL, SND_ASYNC); // 일반 재생
		Effect_Square(25, 25, GREEN_DARK, 0, 0);
		PlaySound(TEXT("firework.wav"), NULL, SND_ASYNC); // 일반 재생
		Effect_Square(15, 25, PURPLE_DARK, 0, 0);
		PlaySound(TEXT("firework.wav"), NULL, SND_ASYNC); // 일반 재생
		Effect_Square(25, 10, YELLOW_DARK, 0, 0);
		PlaySound(TEXT("firework.wav"), NULL, SND_ASYNC); // 일반 재생
		Effect_Square(10, 25, MINT_DARK, 0, 0);
		Effect_Rotation_Keep(BLACK);
		Sleep(500);
		PlaySound(TEXT("bgm.wav"), NULL, SND_ASYNC | SND_LOOP); // 반복 재생
		//클리어
		gState = GSTATE_CLEAR;
		gLocation = GLOCATION_STATE;
	}
	//색깔벽 있으면 그냥 리턴
	else
	{
		return;
	}
}











void Effect_Square(int x, int y, int color, int processDelay, int completeDelay)
{
	//중심에서 부터 얼마나 퍼져나갔는지 저장
	int offset;
	//최대 오프셋 값
	int maxOffset;

	//processDelay값이 1보다 작으면 1로 만들기, 0이면 이펙트가 보이지 않기 때문
	if (processDelay < 1)
		processDelay = 1;

	//최대 오프셋 값 찾기
	maxOffset = GARRAY_WIDTH_MAXINDEX;
	if (maxOffset < GARRAY_HEIGHT_MAXINDEX)
		maxOffset = GARRAY_HEIGHT_MAXINDEX;

	//오프셋 늘려가면서 사각으로 이펙트
	for (offset = 0; offset <= maxOffset; offset++)
	{
		//상하좌우에 대해서 각각 그리기
		
		//현재 구간 게임화면으로 그리기
		Effect_Square_Line(x, y, offset, color, 'u', 0);
		Effect_Square_Line(x, y, offset, color, 'd', 0);
		Effect_Square_Line(x, y, offset, color, 'l', 0);
		Effect_Square_Line(x, y, offset, color, 'r', 0);

		//다음 구간 이펙트로 그리기
		Effect_Square_Line(x, y, offset + 1, color, 'u', 1);
		Effect_Square_Line(x, y, offset + 1, color, 'd', 1);
		Effect_Square_Line(x, y, offset + 1, color, 'l', 1);
		Effect_Square_Line(x, y, offset + 1, color, 'r', 1);

		//그리는 동안의 딜레이
		Sleep(processDelay);
	}
	//그리고 나서의 딜레이
	Sleep(completeDelay);

	inputReset();
}


void Effect_Square_Line(int x, int y, int offset, int color, char direction, int isEffect)
{
	int i, j;
	//시작점의 좌표
	int startX, startY;
	//끝점의 좌표
	int endX, endY;

	//시작점과 끝점 찾기
	switch (direction)
	{
	case 'u':
		//위치가 화면 위면 리턴
		if (y - offset < 0)
			return;

		//x값 화면 안쪽으로 처리하기
		if (x - offset >= 0)
			startX = x - offset;
		else
			startX = 0;
		if (x + offset <= GARRAY_WIDTH_MAXINDEX)
			endX = x + offset;
		else
			endX = GARRAY_WIDTH_MAXINDEX;

		startY = y - offset;
		endY = startY;
		break;
	case 'd':
		//위치가 화면 아래면 리턴
		if (y + offset > GARRAY_HEIGHT_MAXINDEX)
			return;

		//x값 화면 안쪽으로 처리하기
		if (x - offset >= 0)
			startX = x - offset;
		else
			startX = 0;
		if (x + offset <= GARRAY_WIDTH_MAXINDEX)
			endX = x + offset;
		else
			endX = GARRAY_WIDTH_MAXINDEX;

		startY = y + offset;
		endY = startY;
		break;
	case 'l':
		//위치가 화면 왼쪽이면 리턴
		if (x - offset < 0)
			return;

		//y값 화면 안쪽으로 처리하기
		if (y - offset >= 0)
			startY = y - offset;
		else
			startY = 0;
		if (y + offset <= GARRAY_HEIGHT_MAXINDEX)
			endY = y + offset;
		else
			endY = GARRAY_HEIGHT_MAXINDEX;

		startX = x - offset;
		endX = startX;
		break;
	case 'r':
		//위치가 화면 오른쪽이면 리턴
		if (x + offset > GARRAY_WIDTH_MAXINDEX)
			return;
		
		//y값 화면 안쪽으로 처리하기
		if (y - offset >= 0)
			startY = y - offset;
		else
			startY = 0;
		if (y + offset <= GARRAY_HEIGHT_MAXINDEX)
			endY = y + offset;
		else
			endY = GARRAY_HEIGHT_MAXINDEX;

		startX = x + offset;
		endX = startX;
		break;
	default:
		//잘못된 방향은 리턴
		return;
		break;
	}


	//이펙트면 이펙트 그리기
	if (isEffect)
	{
		//시작점과 끝점에 게임보드 위치 더하면서 x는 2배로 변환
		startX = startX * 2 + GBOARD_ORIGIN_X;
		startY += GBOARD_ORIGIN_Y;
		endX = endX * 2 + GBOARD_ORIGIN_X;
		endY += GBOARD_ORIGIN_Y;

		SetColor(color, BLACK);
		DrawString_Size(startX, startY, endX - startX + 1, endY - startY + 1, "■", 2, 1);
	}
	//이펙트 아니면 게임화면 그리기
	else
	{
		//반복문 돌며 게임보드 그리기
		for (i = startX; i <= endX; i++)
		{
			for (j = startY; j <= endY; j++)
			{
				DrawGameBoard(i, j, gameBoardArray[j][i]);
			}
		}
	}
}















void Game_Status(void) {
	SetColor(UI_COLOR, UI_BACKCOLOR);
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 10, 4, "Coin : ");
	DrawString_Dot_Int(GBOARD_RIGHT_POSITION_X + 10 + strlen("Time : "), 4, coin);
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 10, 6, "Stage ");
	DrawString_Dot_Int(GBOARD_RIGHT_POSITION_X + 10 + strlen("Stage "), 6, currentLevelIndex + 1);
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 10, 8, "========================");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 10, 10, "Time : ");
	DrawString_Dot_Int(GBOARD_RIGHT_POSITION_X + 10 + strlen("Time : "), 10, time);

	SetColor(UI_COLOR, 4);
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 10, 12, "Life :  ");
	SetColor(UI_COLOR, 4);
	for (int i = 1; i <= SYSTEM_MAX_LIFE; i++) {
		if (i <= P1_Life) DrawString_Dot(GBOARD_RIGHT_POSITION_X + 10 + strlen("Life :") + (i * 2), 12, "♥");
		else DrawString_Dot(GBOARD_RIGHT_POSITION_X + 10 + strlen("Life :") + (i * 2), 12, "♡");
	}
}