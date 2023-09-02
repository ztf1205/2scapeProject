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

	//������ ��� ����
	if (developMode)
	{
		if (GetAsyncKeyState(0x4C))//L-������ ����
		{
			ClearLog();
			SetColor(UI_COLOR, UI_BACKCOLOR);
			DrawString_Dot(GBOARD_RIGHT_POSITION_X + 11, 37, "������ ����!(������ ��� ����)");
			P1_Life=SYSTEM_MAX_LIFE;
			P2_Life= SYSTEM_MAX_LIFE;
			Game_Status();//ui����
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
	//ȭ�� ��� ����
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
					//0.1�ʸ��� �Է¹ް� �߷� ����, ������ó��
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
				//0.5�ʸ��� ȭ�� �����̱�
				MoveArrow();
				if (gLocation == GLOCATION_STATE)
					break;
			}
			if (gLocation == GLOCATION_STATE)
				break;
			//1�ʸ��� �ð� ����, Ŭ����Ÿ�� ����
			time++;
			ClearTime++;
			Game_Status();//ui����
		}
		if (gLocation == GLOCATION_STATE)
			break;
		//3�ʸ��� ȭ�� �߻� �� �ڵ������� ó��
		if (i % 2 == 0)
			HideHiddenWall();
		else
			ShowHiddenWall();
		ShootArrow();
		if (gLocation == GLOCATION_STATE)
			break;
	}
	//6�ʸ���
}





void MovingPlayer(int pc, char direction)
{
	int currentPosX, currentPosY;
	int nextPosX, nextPosY;
	int currentBlockType, nextBlockType;

	//pc �� ��ȯ, ���� ĭ �˾Ƴ���
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
	else//�߸��� pc��
		return;


	//���� ĭ �˾Ƴ���
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
	default://�߸��� ���Ⱚ
		return;
		break;
	}
	//���� ���� ���� �� ã��
	currentBlockType = gameBoardArray[currentPosY][currentPosX] - pc;
	nextBlockType = gameBoardArray[nextPosY][nextPosX];

	//���� ĭ���� ������ �� �ִٸ�
	if (MoveAble(nextBlockType))
	{
		MoveOutTrigger(pc, currentBlockType, nextBlockType);
		MoveInTrigger(pc, currentBlockType, nextBlockType);
		//��ĭ �����̱�(pc��ǥ �������� ��ȭ �� ���Ӻ��� ������Ʈ)
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
	//���� ĭ���� ������ �� ���ٸ�
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
	//1�� ����� ������ ���ӿ����ϱ� 2�Ǵ� ó��X
	if (gLocation == GLOCATION_STATE)
		return;
	LifeSystem_PC2();
}



void LifeSystem_PC1(void)
{
	//�¾Ҵµ� ������ �ƴ϶�� �ǰ�ó��
	if (P1_HitFlag && P1_InvincibleTimeRemain == 0)
	{
		//������ ����
		P1_Life--;
		P2_Life--;
		Game_Status();//ui����
		//��� ���
		ClearLog();
		SetColor(1, UI_BACKCOLOR);
		DrawString_Dot(GBOARD_RIGHT_POSITION_X + 11, 37, "��");
		SetColor(UI_COLOR, UI_BACKCOLOR);
		DrawString_Dot(GBOARD_RIGHT_POSITION_X + 15, 37, ": ����!... ���� �ݵ�� ��������..!");
		//�ǰ� ����Ʈ
		Effect_Blink(RED);
		//���� ������ ������
		if (P1_Life <= 0)
		{
			Death(GMAP_PC1);
		}
		//���� ������ ������
		else
		{
			//��������
			P1_InvincibleTimeRemain = SYSTEM_MAX_INVINCIBLETIME;
		}
	}
	//���� or ���� ����
	else
	{
		//�����̶��
		if (P1_InvincibleTimeRemain > 0)
		{
			//�����ð� ����
			P1_InvincibleTimeRemain--;
		}
	}
	//�÷��� �ʱ�ȭ
	P1_HitFlag = 0;
}


void LifeSystem_PC2(void)
{
	//�¾Ҵµ� ������ �ƴ϶�� �ǰ�ó��
	if (P2_HitFlag && P2_InvincibleTimeRemain == 0)
	{
		//������ ����
		P1_Life--;
		P2_Life--;
		Game_Status();//ui����
		//��� ���
		ClearLog();
		SetColor(4, UI_BACKCOLOR);
		DrawString_Dot(GBOARD_RIGHT_POSITION_X + 11, 37, "����");
		SetColor(UI_COLOR, UI_BACKCOLOR);
		DrawString_Dot(GBOARD_RIGHT_POSITION_X + 17, 37, ": �ƾ�! �̷���.. �츰 ���� �� ����.");
		//�ǰ� ����Ʈ
		Effect_Blink(RED);
		//���� ������ ������
		if (P2_Life <= 0)
		{
			Death(GMAP_PC2);
		}
		//���� ������ ������
		else
		{
			//��������
			P2_InvincibleTimeRemain = SYSTEM_MAX_INVINCIBLETIME;
		}
	}
	//���� or ���� ����
	else
	{
		//�����̶��
		if (P2_InvincibleTimeRemain > 0)
		{
			//�����ð� ����
			P2_InvincibleTimeRemain--;
		}
	}
	//�÷��� �ʱ�ȭ
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
			DrawString_Dot(GBOARD_RIGHT_POSITION_X + 11, 37, "�������� ���� á���ϴ�.");
			P1_Life = SYSTEM_MAX_LIFE;
			P2_Life = SYSTEM_MAX_LIFE;
		}
		else
		{
			ClearLog();
			SetColor(UI_COLOR, UI_BACKCOLOR);
			DrawString_Dot(GBOARD_RIGHT_POSITION_X + 11, 37, "������ ���ʽ�! Life + 1");
			P1_Life++;
			P2_Life++;
			Game_Status();//ui����
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
			DrawString_Dot(GBOARD_RIGHT_POSITION_X + 11, 37, "�������� ���� á���ϴ�.");
			P1_Life = SYSTEM_MAX_LIFE;
			P2_Life = SYSTEM_MAX_LIFE;
		}
		else
		{
			ClearLog();
			SetColor(UI_COLOR, UI_BACKCOLOR);
			DrawString_Dot(GBOARD_RIGHT_POSITION_X + 11, 37, "������ ���ʽ�! Life + 1");
			P1_Life++;
			P2_Life++;
			Game_Status();//ui����
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
	//�ð� �ʱ�ȭ
	time = 0;

	//�÷���, �����ð� �ʱ�ȭ
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

	//�÷��̾ ȭ�쿡 �¾Ҵ��� �ȸ¾Ҵ��� �����ϴ� �÷���. 0=�ȸ���, 1=p1����, 2=p2����, 3=p1,p2 �� �� ����
	int hitFlag = 0;

	//�߻��� ȭ���� Ÿ��
	int arrowType = -1;

	//ȭ���� �߻�� ��ġ
	int arrowPosX, arrowPosY;

	
	//�� ������ �����鼭 ȭ�� �߻�, �浹 ����
	for (i = 1; i < GARRAY_HEIGHT_MAXINDEX; i++)
	{
		for (j = 1; j < GARRAY_WIDTH_MAXINDEX; j++)
		{
			//�ش�ĭ �������� Ȯ���ϰ� ��ǥ �Ҵ�
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

			//ȭ���� �ƴϸ� ���� ������ �Ѿ��
			if (arrowType == -1)
				continue;
			//ȭ���̸� �߻�
			else
			{
				//������̸� �߻�
				if (gameBoardArray[arrowPosY][arrowPosX] == GMAP_SPACE)
				{
					UpdateGameBoard(arrowPosX, arrowPosY, arrowType);
				}
				//�÷��̾�� �±�
				else if (gameBoardArray[arrowPosY][arrowPosX] == GMAP_PC1)
				{
					P1_HitFlag = 1;
				}
				//�÷��̾�� �±�
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

	//�� ȭ���� ��ġ������ �����ϴ� arrowArray, x��ǥ,y��ǥ,type ����
	int arrowArray[SYSTEM_MAX_ARRAYINDEX][3] = { 0 };

	//���� �����Ͱ� ����� �ִ� �ε����� �����ϴ� arrowArrayMaxIndex
	int arrowArrayMaxIndex = -1;
	
	//�÷��̾ ȭ�쿡 �¾Ҵ��� �ȸ¾Ҵ��� �����ϴ� �÷���. 0=�ȸ���, 1=p1����, 2=p2����, 3=p1,p2 �� �� ����
	int hitFlag = 0;

	//������ ȭ���� Ÿ��
	int arrowType = -1;

	//ȭ���� ������ ��ġ
	int arrowPosX, arrowPosY;

	//�� ������ �����鼭 ȭ���� �ӽ� �迭�� �����ϰ� �ʿ� �ִ� ȭ���� �����
	for (i = 0; i <= GARRAY_HEIGHT_MAXINDEX; i++)
	{
		for (j = 0; j <= GARRAY_WIDTH_MAXINDEX; j++)
		{
			//ȭ������ Ȯ��
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

			//ȭ���� �ƴϸ� ���� ��
			if (arrowType == -1)
				continue;
			//ȭ���̸� arrowArray�� ȭ�� ���� �߰�
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

	//�迭�� �ִ� ȭ����� ������ ��ĭ�� �����̰� ���Ӱ� ����, �浹 ����
	for (i = 0; i <= arrowArrayMaxIndex; i++)
	{
		//ȭ��Ÿ�Կ� ���� �������� ������ ��ġ �Ҵ�
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

		//������̸� �����̱�
		if (gameBoardArray[arrowPosY][arrowPosX] == GMAP_SPACE)
		{
			UpdateGameBoard(arrowPosX, arrowPosY, arrowType);
		}
		//p1�� ������ ������
		else if (gameBoardArray[arrowPosY][arrowPosX] == GMAP_PC1)
		{
			P1_HitFlag = 1;
		}
		//p2�� ������ ������
		else if (gameBoardArray[arrowPosY][arrowPosX] == GMAP_PC2)
		{
			P2_HitFlag = 2;
		}
		else
		{
			//�ٸ� ��ü�� ���ٸ� �ൿ���� �׳� �Ҹ�
		}
	}
}


void ShowHiddenWall(void)
{
	int x, y;
	//�ݺ��� ���� ���� �� �����ֱ�
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
	//�ݺ��� ���� ���� �� �����
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
	//���� ����
	coin--;
	DeathCount++;//����ī��Ʈ ����
	Game_Status();//ui����
	if (coin)//���� ���� ������
	{
		//pc�� ��� �ʱ�ȭ
		P1_Life = SYSTEM_START_LIFE;
		P2_Life = SYSTEM_START_LIFE;
		//�����
		gState = GSTATE_RETRY;
		gLocation = GLOCATION_STATE;
	}
	else//���� ���� ������
	{
		//���ӿ���
		gState = GSTATE_GAMEOVER;
		gLocation = GLOCATION_STATE;
	}
}

void Death(int pc)
{
	int pcPosX, pcPosY;

	//pc�� ���� pc ��ġ �˾Ƴ���
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
		//�߸��� pc��
		return;
		break;
	}

	//����Ʈ �ְ� retryó��
	Effect_Square(pcPosX, pcPosY, RED, 5, 250);
	Retry();
}


void Death_Wall(int pc)
{
	//������ ����
	P1_Life = 0;
	P2_Life = 0;
	Game_Status();//ui����
	Death(pc);
	DrawOutline();
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 24, "��! ���� ������ �ʰ� �����ؾ� �մϴ�.");
	Sleep(1500);
}


/* Ʈ���� */

void Trigger_ToggleButton_MoveOut(int currentBlockType, int nextBlockType)
{
	int x, y;
	int hiddenColorWall, baseColorWall;
	
	//�� �÷��̾ ��� ��� �ִ� ��Ȳ�̸� �״�� �����ؾ� �ϹǷ� �������X-����
	if (gameBoardArray[P1_PosY][P1_PosX] == currentBlockType + GMAP_PC1 && gameBoardArray[P2_PosY][P2_PosX] == currentBlockType + GMAP_PC2)
	{
		return;
	}

	//���� ĭ�� ���� ��۹�ư�̸� ��� ��� �ǹǷ� �������X-����
	if (currentBlockType == nextBlockType)
	{
		return;
	}


	//��ư�� ���� �� ���� �Ǵ�
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
	default://�߸��� ��ư ��
		return;
		break;
	}


	//�÷��̾�� ��ġ�� �Ǹ� �ѹ濡 �װ� ���� ����ó��
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

	//�ݺ��� ���� ������ �� �ٽ� ����
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
	PlaySound(TEXT("start.wav"), NULL, SND_ASYNC); // �Ϲ� ���
	//pc�� ���� pc ��ġ �˾Ƴ���
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
		//�߸��� pc��
		return;
		break;
	}

	//����Ʈ �ְ� Ŭ����ó��
	Effect_Square(pcPosX, pcPosY, WHITE, 5, 250);
	gState = GSTATE_CLEAR;
	gLocation = GLOCATION_STATE;
	PlaySound(TEXT("bgm.wav"), NULL, SND_ASYNC | SND_LOOP); // �ݺ� ���
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

	//Ű ���� ã��
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

	//Ű 2�� �̻��̸� �Ѿ��
	if (keyAmount >= 2)
	{
		return;
	}
	//Ű 1���� ����
	else
	{
		for (y = 0; y <= GARRAY_WIDTH_MAXINDEX; y++)
		{
			for (x = 0; x <= GARRAY_WIDTH_MAXINDEX; x++)
			{
				//���̳� �����̸� ���������
				if (gameBoardArray[y][x] == baseColorWall || gameBoardArray[y][x] == hiddenColorWall)
				{
					UpdateGameBoard(x, y, GMAP_SPACE);
				}
				//PC�� ���� ������ PC��
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


	//��ư ���� ã��
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
	
	//�ڽ��� ĭ���� �̹� ������ �־ +-=0�̸� ����
	if (currentBlockType == nextBlockType)
	{
		return;
	}
	//�ȴ��� ��ư 2�� �̻��̸� �Ѿ��
	else if (buttonAmount >= 2)
	{
		return;
	}
	//��ư 1���� ����
	else
	{
		for (y = 0; y <= GARRAY_WIDTH_MAXINDEX; y++)
		{
			for (x = 0; x <= GARRAY_WIDTH_MAXINDEX; x++)
			{
				//���̳� �����̸� ���������
				if (gameBoardArray[y][x] == baseColorWall || gameBoardArray[y][x] == hiddenColorWall)
				{
					UpdateGameBoard(x, y, GMAP_SPACE);
				}
				//PC�� ���� ������ PC��
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


	//��ư�� ���� �� ���� �Ǵ�
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
	default://�߸��� ��ư ��
		return;
		break;
	}

	//�ݺ��� ���� ������ �� �ٽ� ����
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
	
	//������ �ִ��� �Ǻ� �� �÷��� ����
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

	//���� ���ٸ� Ŭ����ó��
	if (clearFlag)
	{
		//���
		ClearLog();
		SetColor(1, UI_BACKCOLOR);
		DrawString_Dot(GBOARD_RIGHT_POSITION_X + 11, 37, "��");
		SetColor(4, UI_BACKCOLOR);
		DrawString_Dot(GBOARD_RIGHT_POSITION_X + 11, 38, "����");
		SetColor(UI_COLOR, UI_BACKCOLOR);
		DrawString_Dot(GBOARD_RIGHT_POSITION_X + 15, 37, ": �츮�� �س¾�, ����! ");
		DrawString_Dot(GBOARD_RIGHT_POSITION_X + 17, 38, ": ���� � ����������");
		//����Ʈ�ֱ�
		PlaySound(TEXT("start.wav"), NULL, SND_ASYNC); // �Ϲ� ���
		Effect_Rotation(GREY);
		Effect_Rotation_Keep(GREY);
		//�������� ���� ���ֱ�
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
		//����
		PlaySound(TEXT("firework.wav"), NULL, SND_ASYNC); // �Ϲ� ���
		Effect_Square(25, 20, BLUE_DARK, 0, 0);
		PlaySound(TEXT("firework.wav"), NULL, SND_ASYNC); // �Ϲ� ���
		Effect_Square(20, 15, RED_DARK, 0, 0);
		PlaySound(TEXT("firework.wav"), NULL, SND_ASYNC); // �Ϲ� ���
		Effect_Square(25, 25, GREEN_DARK, 0, 0);
		PlaySound(TEXT("firework.wav"), NULL, SND_ASYNC); // �Ϲ� ���
		Effect_Square(15, 25, PURPLE_DARK, 0, 0);
		PlaySound(TEXT("firework.wav"), NULL, SND_ASYNC); // �Ϲ� ���
		Effect_Square(25, 10, YELLOW_DARK, 0, 0);
		PlaySound(TEXT("firework.wav"), NULL, SND_ASYNC); // �Ϲ� ���
		Effect_Square(10, 25, MINT_DARK, 0, 0);
		Effect_Rotation_Keep(BLACK);
		Sleep(500);
		PlaySound(TEXT("bgm.wav"), NULL, SND_ASYNC | SND_LOOP); // �ݺ� ���
		//Ŭ����
		gState = GSTATE_CLEAR;
		gLocation = GLOCATION_STATE;
	}
	//���� ������ �׳� ����
	else
	{
		return;
	}
}











void Effect_Square(int x, int y, int color, int processDelay, int completeDelay)
{
	//�߽ɿ��� ���� �󸶳� ������������ ����
	int offset;
	//�ִ� ������ ��
	int maxOffset;

	//processDelay���� 1���� ������ 1�� �����, 0�̸� ����Ʈ�� ������ �ʱ� ����
	if (processDelay < 1)
		processDelay = 1;

	//�ִ� ������ �� ã��
	maxOffset = GARRAY_WIDTH_MAXINDEX;
	if (maxOffset < GARRAY_HEIGHT_MAXINDEX)
		maxOffset = GARRAY_HEIGHT_MAXINDEX;

	//������ �÷����鼭 �簢���� ����Ʈ
	for (offset = 0; offset <= maxOffset; offset++)
	{
		//�����¿쿡 ���ؼ� ���� �׸���
		
		//���� ���� ����ȭ������ �׸���
		Effect_Square_Line(x, y, offset, color, 'u', 0);
		Effect_Square_Line(x, y, offset, color, 'd', 0);
		Effect_Square_Line(x, y, offset, color, 'l', 0);
		Effect_Square_Line(x, y, offset, color, 'r', 0);

		//���� ���� ����Ʈ�� �׸���
		Effect_Square_Line(x, y, offset + 1, color, 'u', 1);
		Effect_Square_Line(x, y, offset + 1, color, 'd', 1);
		Effect_Square_Line(x, y, offset + 1, color, 'l', 1);
		Effect_Square_Line(x, y, offset + 1, color, 'r', 1);

		//�׸��� ������ ������
		Sleep(processDelay);
	}
	//�׸��� ������ ������
	Sleep(completeDelay);

	inputReset();
}


void Effect_Square_Line(int x, int y, int offset, int color, char direction, int isEffect)
{
	int i, j;
	//�������� ��ǥ
	int startX, startY;
	//������ ��ǥ
	int endX, endY;

	//�������� ���� ã��
	switch (direction)
	{
	case 'u':
		//��ġ�� ȭ�� ���� ����
		if (y - offset < 0)
			return;

		//x�� ȭ�� �������� ó���ϱ�
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
		//��ġ�� ȭ�� �Ʒ��� ����
		if (y + offset > GARRAY_HEIGHT_MAXINDEX)
			return;

		//x�� ȭ�� �������� ó���ϱ�
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
		//��ġ�� ȭ�� �����̸� ����
		if (x - offset < 0)
			return;

		//y�� ȭ�� �������� ó���ϱ�
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
		//��ġ�� ȭ�� �������̸� ����
		if (x + offset > GARRAY_WIDTH_MAXINDEX)
			return;
		
		//y�� ȭ�� �������� ó���ϱ�
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
		//�߸��� ������ ����
		return;
		break;
	}


	//����Ʈ�� ����Ʈ �׸���
	if (isEffect)
	{
		//�������� ������ ���Ӻ��� ��ġ ���ϸ鼭 x�� 2��� ��ȯ
		startX = startX * 2 + GBOARD_ORIGIN_X;
		startY += GBOARD_ORIGIN_Y;
		endX = endX * 2 + GBOARD_ORIGIN_X;
		endY += GBOARD_ORIGIN_Y;

		SetColor(color, BLACK);
		DrawString_Size(startX, startY, endX - startX + 1, endY - startY + 1, "��", 2, 1);
	}
	//����Ʈ �ƴϸ� ����ȭ�� �׸���
	else
	{
		//�ݺ��� ���� ���Ӻ��� �׸���
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
		if (i <= P1_Life) DrawString_Dot(GBOARD_RIGHT_POSITION_X + 10 + strlen("Life :") + (i * 2), 12, "��");
		else DrawString_Dot(GBOARD_RIGHT_POSITION_X + 10 + strlen("Life :") + (i * 2), 12, "��");
	}
}