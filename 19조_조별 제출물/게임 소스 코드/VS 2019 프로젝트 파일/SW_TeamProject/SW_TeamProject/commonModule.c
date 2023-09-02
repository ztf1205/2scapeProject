#pragma warning(disable :4996)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#pragma comment (lib, "winmm.lib")
#include <mmsystem.h>;

#include "commonModule.h"

void GlobalVariableDefinition(void)
{
	gState = GSTATE_BEGIN;
	gLocation = GLOCATION_STATE;
	currentLevelIndex = 0;
	time = 0;
	jumpRemain = 0;

	P1_PosX = 0;
	P1_PosY = 0;
	P2_PosX = 0;
	P2_PosY = 0;

	coin = SYSTEM_MAX_COIN;
	P1_Life = SYSTEM_START_LIFE;
	P2_Life = SYSTEM_START_LIFE;
	P1_HitFlag = 0;
	P2_HitFlag = 0;
	P1_InvincibleTimeRemain = 0;
	P2_InvincibleTimeRemain = 0;


	ClearTime = 0;
	DeathCount = 0;
}


void SetColor(unsigned short text, unsigned short back)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}

void SetCurrentCursorPos(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void RemoveCursor(void)
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}


void GameSetting(void)
{
	HWND wh = GetConsoleWindow();
	system(SYSTEM_COLOR);
	system("mode con cols=152 lines=48");
	system("title 2scape Project");
	SetWindowPos(wh, HWND_TOP, 0, 0, 500, 500, SWP_NOSIZE);
	RemoveCursor();
	GlobalVariableDefinition();
	BuildMapDataArray();
}

void StateController(void)
{
	int i;
	char tmpStr[SYSTEM_MAX_ARRAYINDEX];
	switch (gState)
	{
	case GSTATE_EXIT:
		gLocation = GLOCATION_EXIT;
		PlaySound(TEXT("exit.wav"), NULL, SND_ASYNC); // �Ϲ� ���
		DrawOutline();
		SetColor(UI_COLOR, UI_BACKCOLOR);
		DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 22, "�÷��� �� �ּż� �����մϴ�.");
		DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 24, "<  ������ �����մϴ�  >");
		Effect_Rotation(WHITE);
		break;
	case GSTATE_BEGIN:
		PlaySound(TEXT("start.wav"), NULL, SND_ASYNC); // �Ϲ� ���
		gLocation = GLOCATION_LOBBY;
		DrawOutline();
		SetColor(UI_COLOR, UI_BACKCOLOR);
		PrintTitle();
		DrawString_Dot(UI_CENTER_X - 12, 25, "<  ������ �����մϴ�  >");
		Effect_Rotation(WHITE);
		PlaySound(TEXT("bgm.wav"), NULL, SND_ASYNC | SND_LOOP); // �ݺ� ���
		break;
	case GSTATE_START:
		currentLevelIndex = 0;
		gLocation = GLOCATION_GAME;
		coin = SYSTEM_MAX_COIN;//������ȸ �ʱ�ȭ
		ClearTime = 0;//Ŭ���� Ÿ�� �ʱ�ȭ
		DeathCount = 0;//����ī��Ʈ �ʱ�ȭ
		//pc�� ��� �ʱ�ȭ
		P1_Life = SYSTEM_START_LIFE;
		P2_Life = SYSTEM_START_LIFE;
		DrawOutline();
		SetColor(UI_COLOR, UI_BACKCOLOR);
		DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 18, "[ Stage 1 ]");
		Sleep(1000);
		break;
	case GSTATE_RETRY:
		gLocation = GLOCATION_GAME;
		DrawOutline();
		SetColor(UI_COLOR, UI_BACKCOLOR);
		DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 24, "Ŭ���� ���� .. �ٽ� �����մϴ� !");
		Sleep(1000);
		break;
	case GSTATE_GAMEOVER:
		gLocation = GLOCATION_LOBBY;
		DrawOutline();
		SetColor(UI_COLOR, UI_BACKCOLOR);
		DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 24, "�ǣ��ͣ� �ϣ֣ţ� ..");
		DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 26, "�κ� ȭ������ ���ư��ϴ�.");
		Sleep(1000);
		break;
	case GSTATE_CLEAR:
		if (currentLevelIndex == SYSTEM_MAX_LEVEL - 1)//3->���� Ŭ����
		{
			gState = GSTATE_ENDING;
			gLocation = GLOCATION_STATE;
		}
		else if (currentLevelIndex == SYSTEM_MAX_LEVEL - 2)//2->3 (���� ����)
		{
			currentLevelIndex++;
			gLocation = GLOCATION_GAME;
			BossStageEffect();
			ClearLog();
			SetColor(1, UI_BACKCOLOR);
			DrawString_Dot(GBOARD_RIGHT_POSITION_X + 11, 37, "��");
			SetColor(4, UI_BACKCOLOR);
			DrawString_Dot(GBOARD_RIGHT_POSITION_X + 11, 38, "����");
			SetColor(UI_COLOR, UI_BACKCOLOR);
			DrawString_Dot(GBOARD_RIGHT_POSITION_X + 15, 37, ": ���踦 �� �� �κ��� ����Ʈ����!");
			DrawString_Dot(GBOARD_RIGHT_POSITION_X + 17, 38, ": �ϴû� ���踦 ���� ���� ��");
		}
		else//1->2
		{
			currentLevelIndex++;
			gLocation = GLOCATION_GAME;
			DrawOutline();
			SetColor(UI_COLOR, UI_BACKCOLOR);
			DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 24, "�ӣԣ��ǣ� �ạ̃ţ���!!");
			DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 25, "���� ���������� ..");
			Sleep(2000);
			ClearLog();
			SetColor(1, UI_BACKCOLOR);
			DrawString_Dot(GBOARD_RIGHT_POSITION_X + 11, 37, "��");
			SetColor(4, UI_BACKCOLOR);
			DrawString_Dot(GBOARD_RIGHT_POSITION_X + 11, 38, "����");
			SetColor(UI_COLOR, UI_BACKCOLOR);
			DrawString_Dot(GBOARD_RIGHT_POSITION_X + 15, 37, ": ���峭 ����ġ�� �ʹ� ����.. ");
			DrawString_Dot(GBOARD_RIGHT_POSITION_X + 17, 38, ": �̷� ���� �ⱸ�� �����ž�.");
		}
		break;
	case GSTATE_ENDING:
		gLocation = GLOCATION_LOBBY;
		DrawOutline();
		SetColor(UI_COLOR, UI_BACKCOLOR);
		PrintTitle();
		DrawString_Dot(UI_CENTER_X - 5, UI_CENTER_Y - 1, "< ENDING >");
		Effect_Outline(BLUE_DARK);
		Sleep(1000);
		Effect_Outline(GREEN_DARK);
		Sleep(1000);
		SetColor(UI_COLOR, UI_BACKCOLOR);
		DrawString_Dot(UI_CENTER_X - 15, UI_CENTER_Y + 2, "�� �÷��� �ð�");
		DrawString_Dot_Int(UI_CENTER_X - 10, UI_CENTER_Y + 4, ClearTime);
		Effect_Outline(RED_DARK);
		Sleep(1000);
		Effect_Outline(YELLOW_DARK);
		Sleep(1000);
		SetColor(UI_COLOR, UI_BACKCOLOR);
		DrawString_Dot(UI_CENTER_X + 10, UI_CENTER_Y + 2, "���� Ƚ��");
		DrawString_Dot_Int(UI_CENTER_X + 12, UI_CENTER_Y + 4, DeathCount);
		Effect_Outline(MINT_DARK);
		Sleep(1000);
		Effect_Outline(PURPLE_DARK);
		Sleep(1000);
		//�Է´��
		i = 0;
		while (1)
		{
			if (_kbhit() != 0)
				break;
			else
			{
				switch (i%600)
				{
				case 0:
					Effect_Outline(BLUE_DARK);
					break;
				case 100:
					Effect_Outline(GREEN_DARK);
					break;
				case 200:
					Effect_Outline(RED_DARK);
					break;
				case 300:
					Effect_Outline(YELLOW_DARK);
					break;
				case 400:
					Effect_Outline(MINT_DARK);
					break;
				case 500:
					Effect_Outline(PURPLE_DARK);
					break;
				default:
					break;
				}
				if (i % 100 == 0)
				{
					SetColor(UI_COLOR, UI_BACKCOLOR);
					DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 + 9, 35, "<  PRESS ANY BUTTON TO CONTINUE  >");
				}
				else if (i % 50 == 0)
				{
					SetColor(UI_BACKCOLOR, UI_BACKCOLOR);
					DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 + 9, 35, "<  PRESS ANY BUTTON TO CONTINUE  >");
				}
				i++;
				Sleep(10);
			}
		}
		Effect_Outline(BLACK);
		// ���� ���
		break;
	case GSTATE_DESIGNTOOL_ON:
		gLocation = GLOCATION_LEVELDESIGN;
		break;
	case GSTATE_DESIGNTOOL_OFF:
		gLocation = GLOCATION_LOBBY;
		break;
	default:
		break;
	}
}

void inputReset(void)
{
	while (_kbhit() != 0)
		_getch();
	GetAsyncKeyState(0x51);//Q
	GetAsyncKeyState(0x4C);//L
}


void BuildMapDataArray(void)
{
	int index = 0, process = 0;
	int spaceIndex;
	char str[SYSTEM_MAX_ARRAYINDEX];
	char* ptr;
	FILE* fs;

	fs = fopen("data.csv", "r");
	fgets(str, SYSTEM_MAX_ARRAYINDEX, fs);//���� ������

	while (feof(fs) == 0)
	{
		fgets(str, SYSTEM_MAX_ARRAYINDEX, fs);
		process = 0;
		ptr = strtok(str, ",");
		ptr = strtok(NULL, ",");//��ĭ ������
		while (ptr != NULL)
		{
			switch (process)
			{
			case 0:
				mapData_Num[index] = atoi(ptr);
				break;
			case 1:
				strcpy(mapData_Char[index], ptr);
				spaceIndex = 0;
				while (mapData_Char[index][spaceIndex] == '1')
					mapData_Char[index][spaceIndex++] = ' ';
				break;
			case 2:
				mapData_Color[index] = atoi(ptr);
				break;
			case 3:
				mapData_BackColor[index] = atoi(ptr);
				break;
			default:
				break;
			}
			process++;
			ptr = strtok(NULL, ",");
		}
		index++;
	}
	fclose(fs);
}



int FindMapDataIndex(int data)
{
	int i;
	for (i = 0; i < SYSTEM_MAX_ARRAYINDEX + 1; i++)
	{
		if (mapData_Num[i] == data)
			return i;
	}
	return -1;
}



void DrawOutline(void)//������������
{
	SetColor(UI_COLOR, UI_BACKCOLOR);

	DrawString_Size(GBOARD_LEFT_POSITION_X, GBOARD_TOP_POSITION_Y + 1, 1, GBOARD_HEIGHT, "�� ", 2, 1);
	DrawString_Size(GBOARD_RIGHT_POSITION_X, GBOARD_TOP_POSITION_Y + 1, 1, GBOARD_HEIGHT, "�� ", 2, 1);

	DrawString_Size(GBOARD_LEFT_POSITION_X + 2, GBOARD_TOP_POSITION_Y, GBOARD_WIDTH, 1, "�� ", 2, 1);
	DrawString_Size(GBOARD_LEFT_POSITION_X + 2, GBOARD_BOTTOM_POSITION_Y, GBOARD_WIDTH, 1, "�� ", 2, 1);

	DrawString_Dot(GBOARD_LEFT_POSITION_X, GBOARD_TOP_POSITION_Y, "�� ");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X, GBOARD_TOP_POSITION_Y, "�� ");
	DrawString_Dot(GBOARD_LEFT_POSITION_X, GBOARD_BOTTOM_POSITION_Y, "�� ");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X, GBOARD_BOTTOM_POSITION_Y, "�� ");

	ClearGameScreen();
}

void DrawString_Size(int leftTop_X, int leftTop_Y, int width, int height, char* str, int sizeX, int sizeY)
{
	int x, y;
	for (y = leftTop_Y; y < leftTop_Y + height; y += sizeY)
	{
		for (x = leftTop_X; x < leftTop_X + width; x += sizeX)
		{
			DrawString_Dot(x, y, str);
		}
	}
}

void DrawString_Dot(int x, int y, char* str)
{
	SetCurrentCursorPos(x, y);
	printf("%s", str);
	SetCurrentCursorPos(0, 0);
}

void DrawString_Dot_Int(int x, int y, int num)
{
	SetCurrentCursorPos(x, y);
	printf("%d", num);
	SetCurrentCursorPos(0, 0);
}


void BuildExit(void)
{
	DrawOutline();
	DrawString_Dot(UI_CENTER_X, UI_CENTER_Y, "�÷��� ���ּż� �����մϴ�.");
}


void Effect_Rotation(int color)
{
	int i;
	//4���� �� �𼭸����� �ð�������� ä���ְ� �����
	Effect_Rotation_Keep(color);
	Effect_Rotation_Keep(BLACK);
	inputReset();
}

void Effect_Rotation_Keep(int color)
{
	int i;
	//4���� �� �𼭸����� �ð�������� ä���ֱ�
	for (i = 0; i <= GBOARD_WIDTH + 4; i += 2)
	{
		SetColor(BLACK, color);
		DrawString_Dot(GBOARD_LEFT_POSITION_X - 2 + i, GBOARD_TOP_POSITION_Y - 1, "��");//���𼭸�
		DrawString_Dot(GBOARD_RIGHT_POSITION_X + 2, GBOARD_TOP_POSITION_Y - 1 + i / 2, "��");//�����𼭸�
		DrawString_Dot(GBOARD_RIGHT_POSITION_X + 2 - i, GBOARD_BOTTOM_POSITION_Y + 1, "��");//�Ʒ��𼭸�
		DrawString_Dot(GBOARD_LEFT_POSITION_X - 2, GBOARD_BOTTOM_POSITION_Y + 1 - i / 2, "��");//�����𼭸�
		Sleep(1);
	}
	inputReset();
}

void Effect_Blink(int color)
{
	int i;
	//4���� �� �𼭸����� �ð�������� ä���ְ� �����
	Effect_Outline(color);
	Sleep(20);
	Effect_Outline(BLACK);
	inputReset();
}

void Effect_Outline(int color)
{
	int i;
	//4���� �� �𼭸����� �ð�������� ä���ֱ�
	for (i = 0; i <= GBOARD_WIDTH + 4; i += 2)
	{
		SetColor(BLACK, color);
		DrawString_Dot(GBOARD_LEFT_POSITION_X - 2 + i, GBOARD_TOP_POSITION_Y - 1, "��");//���𼭸�
		DrawString_Dot(GBOARD_RIGHT_POSITION_X + 2, GBOARD_TOP_POSITION_Y - 1 + i / 2, "��");//�����𼭸�
		DrawString_Dot(GBOARD_RIGHT_POSITION_X + 2 - i, GBOARD_BOTTOM_POSITION_Y + 1, "��");//�Ʒ��𼭸�
		DrawString_Dot(GBOARD_LEFT_POSITION_X - 2, GBOARD_BOTTOM_POSITION_Y + 1 - i / 2, "��");//�����𼭸�
	}
	inputReset();
}


void BossStageEffect(void) {
	for (int temp = 0; temp < 4; temp++) {
		SetColor(UI_COLOR, 4);
		PlaySound(TEXT("warning.wav"), NULL, SND_ASYNC); // �Ϲ� ���
		DrawString_Dot(GBOARD_ORIGIN_X + 2, GBOARD_ORIGIN_Y + (GBOARD_HEIGHT / 2) - 2, "�ף��ңΣɣΣ� !!      �ף��ңΣɣΣ� !!      �ף��ңΣɣΣ� !!      �ף��ңΣ� ");
		DrawString_Dot(GBOARD_ORIGIN_X + 2, GBOARD_ORIGIN_Y + (GBOARD_HEIGHT / 2) - 1, "�Σ� !!      �ף��ңΣɣΣ� !!      �ף��ңΣɣΣ� !!      �ף��ңΣɣΣ� !!    ");
		DrawString_Dot(GBOARD_ORIGIN_X + 2, GBOARD_ORIGIN_Y + (GBOARD_HEIGHT / 2), "  �ף��ңΣɣΣ� !!      �ף��ңΣɣΣ� !!      �ף��ңΣɣΣ� !!      �ף��ң� ");
		DrawString_Dot(GBOARD_ORIGIN_X + 2, GBOARD_ORIGIN_Y + (GBOARD_HEIGHT / 2) + 1, "�ɣΣ� !!      �ף��ңΣɣΣ� !!      �ף��ңΣɣΣ� !!      �ף��ңΣɣΣ� !!  ");
		DrawString_Dot(GBOARD_ORIGIN_X + 2, GBOARD_ORIGIN_Y + (GBOARD_HEIGHT / 2) + 2, "    �ף��ңΣɣΣ� !!      �ף��ңΣɣΣ� !!      �ף��ңΣɣΣ� !!      �ף��� ");
		Sleep(700);
		ClearGameScreen();
		Sleep(700);
	}
	PlaySound(TEXT("bgm.wav"), NULL, SND_ASYNC | SND_LOOP); // �ݺ� ���
}



void ClearGameScreen(void)
{
	SetColor(UI_COLOR, UI_BACKCOLOR);
	DrawString_Size(GBOARD_LEFT_POSITION_X + 2, GBOARD_TOP_POSITION_Y + 1, GBOARD_WIDTH, GBOARD_HEIGHT, "  ", 2, 1);
}

void ClearUI(void)
{
	SetColor(UI_COLOR, UI_BACKCOLOR);
	DrawString_Size(GBOARD_RIGHT_POSITION_X + 8, GBOARD_TOP_POSITION_Y, 50, 11, "  ", 2, 1);
}

void ClearLog(void)
{
	SetColor(UI_COLOR, UI_BACKCOLOR);
	DrawString_Size(GBOARD_RIGHT_POSITION_X + 11, 37, 40, 7, "  ", 2, 1);
}




void PrintTitle(void)
{
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 8, "������������������������������������������������������������ ");
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 9, "������������ �������� ���������������������������� ������ ");
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 10, "������������ �������� ��  ���������������������� ������ ");
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 11, "���������������� ���� ��  ���������������������� ������ ");
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 12, "���������������� ���� ���������� ��������   �� ������ ");
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 13, "���������������������������������� ��������   ���������� ");
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 14, "			���������������������������������������������������������������������� ");
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 15, "			������������������������������������������ �������� ���������� ���� ");
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 16, "			������������������������ ����  ���� �� �������� ��   �� �� ");
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 17, "			������������������������ ����  ���� �� �������� ��   �� �� ");
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 18, "			����   ���������������������������� �� �������� ������ �� �� ");
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 19, "			����   ���������������������������� �������������������� ������ ");
}