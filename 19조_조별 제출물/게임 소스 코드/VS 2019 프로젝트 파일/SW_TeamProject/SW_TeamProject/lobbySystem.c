#include "commonModule.h"
#include "lobbySystem.h"

int Prologue_count = 0; // Prologue 최초 시작(count == 0)시에만 출력

void chat_Icon(int y) {
	int i;
	int breakFlag = 0;
	inputReset();
	while (1) {
		for (i = 0; i < 10; i++)
		{
			//입력 들어오면 역삼각형 지우고 넘기기
			if (_kbhit() != 0)
			{
				DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) + 36, y + 1, "  ");
				breakFlag = 1;
				break;
			}
			//0.5초마다 역삼각형 출력
			if (i == 0)
			{
				DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) + 36, y + 1, "▼");
			}
			//0.5초마다 역삼각형 출력
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
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 11, 37, "시작 스토리는 최초 1회만 플레이 됩니다.");
	DrawString_Dot((GBOARD_ORIGIN_X + GBOARD_WIDTH) - 16, GBOARD_ORIGIN_Y + GBOARD_HEIGHT - 1, "NEXT : SPACE BAR");
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 11, 15, "...");
	chat_Icon(15);
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 11, 17, "20xx년, 잭과 로즈는 이상한 공간에서 눈을 떴다.");
	chat_Icon(17);
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 11, 19, "눈을 뜨고나서 몇 번을 부정하고 몇 시간이나 살려달라 소리쳤는지 모른다. ");
	chat_Icon(19);
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 11, 21, "알게 된 것은 지금 비현실적인 일들 투성이란 것 뿐");
	chat_Icon(21);
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 11, 23, "죽기만을 기다릴 수 없기에..");
	chat_Icon(23);
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 11, 25, "그렇게 잭과 로즈는 이 곳을 탈출하기로 했다 !");
	chat_Icon(25);
	ClearGameScreen();
	ClearLog();
	Prologue_count = 1;
}

void alert_log(void) {
	SetColor(1, UI_BACKCOLOR);
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 11, 37, "잭");
	SetColor(4, UI_BACKCOLOR);
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 11, 38, "로즈");
	SetColor(UI_COLOR, UI_BACKCOLOR);
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 15, 37, ": 로즈를 구하러 가야 겠어.");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 17, 38, ": 내가 잭을 도울 수 있을 것 같아.");
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
				DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 23, "잭과 로즈가 무사히 탈출할 수 있도록 도와주세요 .. !");
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
		//10프레임마다(0.5초) 타이틀 깜빡이기
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
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 24, "┏━━  1P ━━━━━━━━━━━━━━━━━━━┳━━  2P ━━━━━━━━━━━━━━━━━━┓");
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 25, "┃                                                    ┃");
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 26, "┃  ←,→ : 이동키             Ｗ,Ａ,Ｓ,Ｄ : 이동키   ┃");
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 27, "┃  ↑ : 점프키                                       ┃");
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 28, "┃                                                    ┃");
	DrawString_Dot((GBOARD_ORIGIN_X + (GBOARD_WIDTH / 2)) / 2 - 3, 29, "┗━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━┛");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 16, "┌─→ Item ←──────────────────────┐");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 17, "│                                 │");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 18, "│                                 │");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 19, "│                                 │");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 20, "│                                 │");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 21, "│                                 │");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 22, "│                                 │");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 23, "│                                 │");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 24, "└─────────────────────────────────┘");
	SetColor(UI_COLOR, 1);
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 12, 18, "■");
	SetColor(2, UI_BACKCOLOR);
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 12, 19, "※");
	SetColor(UI_BACKCOLOR, 3);
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 12, 20, "●");
	SetColor(4, UI_BACKCOLOR);
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 12, 21, "♥");
	SetColor(UI_COLOR, UI_BACKCOLOR);
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 12, 22, "★ : 출구");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 14, 18, " : 문");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 14, 19, " : 열쇠");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 14, 20, " : 스위치");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 14, 21, " : 라이프 보너스");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 26, "┌─→ Key Instruction ←───────────┐");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 27, "│                                 │");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 28, "│  SPACE BAR : 게임시작           │");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 29, "│  ←,→ : 1P 이동키              │");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 30, "│  ↑ : 1P 점프키                 │");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 31, "│  W,A,S,D : 2P 이동키            │");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 32, "│  Q : 게임종료                   │");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 33, "│                                 │");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 34, "└─────────────────────────────────┘");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 36, "≡──");
	SetColor(1, UI_BACKCOLOR);
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 14, 36, "■");
	SetColor(UI_COLOR, UI_BACKCOLOR);
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 16, 36, " : 잭");
	SetColor(4, UI_BACKCOLOR);
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 24, 36, "■");
	SetColor(UI_COLOR, UI_BACKCOLOR);
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 26, 36, " : 로즈");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 34, 36, "──────────────────┐");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 37, "│                                           │");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 38, "│                                           │");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 39, "│                                           │");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 40, "│                                           │");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 41, "│                                           │");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 42, "│                                           │");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 43, "│                                           │");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, 44, "└───────────────────────────────────────────┘");
}