#include "commonModule.h"
#include "lobbySystem.h"

int Prologue_count = 0; // Prologue ���� ����(count == 0)�ÿ��� ���

void chat_Icon(int y) {
	int i;
	int breakFlag = 0;
	inputReset();
	while (1) {
		for (i = 0; i < 10; i++)
		{
			//�Է� ������ ���ﰢ�� ����� �ѱ��
			if (_kbhit() != 0)
			{
				DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) + 36, y + 1, "  ");
				breakFlag = 1;
				break;
			}
			//0.5�ʸ��� ���ﰢ�� ���
			if (i == 0)
			{
				DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) + 36, y + 1, "��");
			}
			//0.5�ʸ��� ���ﰢ�� ���
			if (i == 5)
			{
				DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) + 36, y + 1, "  ");
			}
			Sleep(100);
		}
		if (breakFlag) break;
	}
}

void Prologue_Guide(void) {
	SetColor(UI_COLOR, UI_BACKCOLOR);
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 11, 37, "���� ���丮�� ���� 1ȸ�� �÷��� �˴ϴ�.");
	DrawString_Dot((GBOARD_ORIGIN_X + GBOARD_WIDTH) - 16, GBOARD_ORIGIN_Y + GBOARD_HEIGHT - 1, "NEXT : SPACE BAR");
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 11, 15, "...");
	chat_Icon(15);
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 11, 17, "20xx��, ��� ����� �̻��� �������� ���� ����.");
	chat_Icon(17);
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 11, 19, "���� �߰��� �� ���� �����ϰ� �� �ð��̳� ����޶� �Ҹ��ƴ��� �𸥴�. ");
	chat_Icon(19);
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 11, 21, "�˰� �� ���� ���� ���������� �ϵ� �����̶� �� ��");
	chat_Icon(21);
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 11, 23, "�ױ⸸�� ��ٸ� �� ���⿡..");
	chat_Icon(23);
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 11, 25, "�׷��� ��� ����� �� ���� Ż���ϱ�� �ߴ� !");
	chat_Icon(25);
	ClearGameScreen();
	ClearLog();
	Prologue_count = 1;
}

void alert_log(void) {
	SetColor(1, UI_BACKCOLOR);
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 11, 37, "��");
	SetColor(4, UI_BACKCOLOR);
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 11, 38, "����");
	SetColor(UI_COLOR, UI_BACKCOLOR);
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 15, 37, ": ��� ���Ϸ� ���� �ھ�.");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 17, 38, ": ���� ���� ���� �� ���� �� ����.");
}

void LobbyLoop(int developMode)
{
	int i;
	int key;
	for (i = 0; i < 20; i++)
	{
		if (_kbhit() != 0)
		{
			key = _getch();
			switch (key)
			{
			case 'q':
				gState = GSTATE_EXIT;
				gLocation = GLOCATION_STATE;
				break;
			case 'l':
				if (developMode)
				{
					gState = GSTATE_DESIGNTOOL_ON;
					gLocation = GLOCATION_STATE;
				}
				break;
			case SPACE:
				ClearGameScreen();
				if (Prologue_count == 0) Prologue_Guide();
				DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 23, "��� ��� ������ Ż���� �� �ֵ��� �����ּ��� .. !");
				chat_Icon(23);
				alert_log();
				gState = GSTATE_START;
				gLocation = GLOCATION_STATE;
				break;
			default:
				break;
			}
		}
		if (gLocation == GLOCATION_STATE)
			break;
		//10�����Ӹ���(0.5��) Ÿ��Ʋ �����̱�
		if (i % 10 == 0)
		{
			BuildTitle((i / 10) % 2);
		}
		Sleep(50);
	}
}

void BuildTitle(int isRed) {
	int titleColor, pressColor;
	if (isRed)
	{
		titleColor = RED;
		pressColor = UI_COLOR;
	}
	else
	{
		titleColor = BLUE;
		pressColor = UI_BACKCOLOR;
	}

	SetColor(pressColor, UI_BACKCOLOR);
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 + 9, 35, "<  PRESS SPACE BAR TO START  >");

	SetColor(titleColor, UI_BACKCOLOR);
	PrintTitle();
}


void BuildLobby(void)
{
	inputReset();
	ClearUI();
	ClearLog();
	DrawOutline();
	SetColor(UI_COLOR, UI_BACKCOLOR);
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 24, "������  1P ��������������������������������������������  2P ��������������������������������������");
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 25, "��                                                    ��");
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 26, "��  ��,�� : �̵�Ű             ��,��,��,�� : �̵�Ű   ��");
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 27, "��  �� : ����Ű                                       ��");
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 28, "��                                                    ��");
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 29, "������������������������������������������������������������������������������������������������������������");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 16, "������ Item �禡��������������������������������������������");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 17, "��                                 ��");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 18, "��                                 ��");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 19, "��                                 ��");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 20, "��                                 ��");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 21, "��                                 ��");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 22, "��                                 ��");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 23, "��                                 ��");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 24, "����������������������������������������������������������������������");
	SetColor(UI_COLOR, 1);
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 12, 18, "��");
	SetColor(2, UI_BACKCOLOR);
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 12, 19, "��");
	SetColor(UI_BACKCOLOR, 3);
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 12, 20, "��");
	SetColor(4, UI_BACKCOLOR);
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 12, 21, "��");
	SetColor(UI_COLOR, UI_BACKCOLOR);
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 12, 22, "�� : �ⱸ");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 14, 18, " : ��");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 14, 19, " : ����");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 14, 20, " : ����ġ");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 14, 21, " : ������ ���ʽ�");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 26, "������ Key Instruction �禡����������������������");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 27, "��                                 ��");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 28, "��  SPACE BAR : ���ӽ���           ��");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 29, "��  ��,�� : 1P �̵�Ű              ��");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 30, "��  �� : 1P ����Ű                 ��");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 31, "��  W,A,S,D : 2P �̵�Ű            ��");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 32, "��  Q : ��������                   ��");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 33, "��                                 ��");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 34, "����������������������������������������������������������������������");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 36, "�զ���");
	SetColor(1, UI_BACKCOLOR);
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 14, 36, "��");
	SetColor(UI_COLOR, UI_BACKCOLOR);
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 16, 36, " : ��");
	SetColor(4, UI_BACKCOLOR);
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 24, 36, "��");
	SetColor(UI_COLOR, UI_BACKCOLOR);
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 26, 36, " : ����");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 34, 36, "��������������������������������������");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 37, "��                                           ��");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 38, "��                                           ��");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 39, "��                                           ��");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 40, "��                                           ��");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 41, "��                                           ��");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 42, "��                                           ��");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 43, "��                                           ��");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 44, "������������������������������������������������������������������������������������������");
}