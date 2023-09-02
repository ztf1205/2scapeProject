#pragma once


/*아스키 코드*/

//키보드 ↑ 의 아스키코드
#define UP 72
//키보드 ↓ 의 아스키코드
#define DOWN 80
//키보드 ← 의 아스키코드
#define LEFT 75
//키보드 → 의 아스키코드
#define RIGHT 77
//키보드 스페이스바의 아스키코드
#define SPACE 32




/*게임보드*/

//게임보드 너비, 게임보드가 차지하는 X좌표 길이
#define GBOARD_WIDTH 80
//게임보드 높이, 게임보드가 차지하는 Y좌표 길이
#define GBOARD_HEIGHT 40
//게임보드가 시작되는 좌상단 X좌표
#define GBOARD_ORIGIN_X 4
//게임보드가 시작되는 좌상단 Y좌표
#define GBOARD_ORIGIN_Y 3

//게임보드 가장 상단의 Y좌표
#define GBOARD_TOP_POSITION_Y GBOARD_ORIGIN_Y
//게임보드 가장 하단의 Y좌표
#define GBOARD_BOTTOM_POSITION_Y (GBOARD_ORIGIN_Y + GBOARD_HEIGHT + 1)
//게임보드 가장 좌측의 X좌표
#define GBOARD_LEFT_POSITION_X GBOARD_ORIGIN_X
//게임보드 가장 우측의 X좌표
#define GBOARD_RIGHT_POSITION_X (GBOARD_ORIGIN_X + GBOARD_WIDTH + 2)





/*게임보드 배열*/

//게임보드 너비의 최대 인덱스
#define GARRAY_WIDTH_MAXINDEX ((GBOARD_WIDTH / 2) + 1)
//게임보드 높이의 최대 인덱스
#define GARRAY_HEIGHT_MAXINDEX (GBOARD_HEIGHT + 1)





/*게임위치*/
//종료화면의 gLocation 값
#define GLOCATION_EXIT 0
//로비의 gLocation 값
#define GLOCATION_LOBBY 1
//게임의 gLocation 값
#define GLOCATION_GAME 2
//상태 관리의 gLocation 값
#define GLOCATION_STATE 3
//디자인 툴의 gLocation 값
#define GLOCATION_LEVELDESIGN 4






/*게임상태*/

//게임 종료의 gState 값
#define GSTATE_EXIT 0
//게임 실행의 gState 값
#define GSTATE_BEGIN 1
//레벨 1 부터 게임 시작의 gState 값
#define GSTATE_START 2
//레벨 재시작의 gState 값
#define GSTATE_RETRY 3
//게임 오버의 gState 값
#define GSTATE_GAMEOVER 4
//레벨 클리어의 gState 값
#define GSTATE_CLEAR 5
//게임 엔딩의 gState 값
#define GSTATE_ENDING 6
//디자인툴 실행의 gState 값
#define GSTATE_DESIGNTOOL_ON 7
//디자인툴 종료의 gState 값
#define GSTATE_DESIGNTOOL_OFF 8






/*맵 정보-배열값*/

#define GMAP_SPACE 0
#define GMAP_PC1 1
#define GMAP_PC2 2
#define GMAP_WALL 3
#define GMAP_HIDDENWALL 4
#define GMAP_DOOR 5
#define GMAP_BOSS 6
#define GMAP_SPIKE_UP 7
#define GMAP_SPIKE_DOWN 8
#define GMAP_SPIKE_LEFT 9
#define GMAP_SPIKE_RIGHT 10
#define GMAP_BOMB 11
#define GMAP_ARROW_UP 12
#define GMAP_ARROW_DOWN 13
#define GMAP_ARROW_LEFT 14
#define GMAP_ARROW_RIGHT 15
#define GMAP_SHOOTER_UP 16
#define GMAP_SHOOTER_DOWN 17
#define GMAP_SHOOTER_LEFT 18
#define GMAP_SHOOTER_RIGHT 19
#define GMAP_LOCKWALL_BLUE 20
#define GMAP_LOCKWALL_GREEN 21
#define GMAP_LOCKWALL_MINT 22
#define GMAP_LOCKWALL_RED 23
#define GMAP_LOCKWALL_PURPLE 24
#define GMAP_LOCKWALL_YELLOW 25
#define GMAP_KEY_BLUE 26
#define GMAP_KEY_GREEN 27
#define GMAP_KEY_MINT 28
#define GMAP_KEY_RED 29
#define GMAP_KEY_PURPLE 30
#define GMAP_KEY_YELLOW 31
#define GMAP_BUTTON_BLUE 32
#define GMAP_BUTTON_BLUE_PC1 33
#define GMAP_BUTTON_BLUE_PC2 34
#define GMAP_BUTTON_GREEN 35
#define GMAP_BUTTON_GREEN_PC1 36
#define GMAP_BUTTON_GREEN_PC2 37
#define GMAP_BUTTON_MINT 38
#define GMAP_BUTTON_MINT_PC1 39
#define GMAP_BUTTON_MINT_PC2 40
#define GMAP_BUTTON_RED 41
#define GMAP_BUTTON_RED_PC1 42
#define GMAP_BUTTON_RED_PC2 43
#define GMAP_BUTTON_PURPLE 44
#define GMAP_BUTTON_PURPLE_PC1 45
#define GMAP_BUTTON_PURPLE_PC2 46
#define GMAP_BUTTON_YELLOW 47
#define GMAP_BUTTON_YELLOW_PC1 48
#define GMAP_BUTTON_YELLOW_PC2 49
#define GMAP_TOGGLE_BUTTON_BLUE 50
#define GMAP_TOGGLE_BUTTON_BLUE_PC1 51
#define GMAP_TOGGLE_BUTTON_BLUE_PC2 52
#define GMAP_TOGGLE_BUTTON_GREEN 53
#define GMAP_TOGGLE_BUTTON_GREEN_PC1 54
#define GMAP_TOGGLE_BUTTON_GREEN_PC2 55
#define GMAP_TOGGLE_BUTTON_MINT 56
#define GMAP_TOGGLE_BUTTON_MINT_PC1 57
#define GMAP_TOGGLE_BUTTON_MINT_PC2 58
#define GMAP_TOGGLE_BUTTON_RED 59
#define GMAP_TOGGLE_BUTTON_RED_PC1 60
#define GMAP_TOGGLE_BUTTON_RED_PC2 61
#define GMAP_TOGGLE_BUTTON_PURPLE 62
#define GMAP_TOGGLE_BUTTON_PURPLE_PC1 63
#define GMAP_TOGGLE_BUTTON_PURPLE_PC2 64
#define GMAP_TOGGLE_BUTTON_YELLOW 65
#define GMAP_TOGGLE_BUTTON_YELLOW_PC1 66
#define GMAP_TOGGLE_BUTTON_YELLOW_PC2 67
#define GMAP_BOSS_WALL 68
#define GMAP_LOCKWALL_HIDE_BLUE 69
#define GMAP_LOCKWALL_HIDE_BLUE_PC1 70
#define GMAP_LOCKWALL_HIDE_BLUE_PC2 71
#define GMAP_LOCKWALL_HIDE_GREEN 72
#define GMAP_LOCKWALL_HIDE_GREEN_PC1 73
#define GMAP_LOCKWALL_HIDE_GREEN_PC2 74
#define GMAP_LOCKWALL_HIDE_MINT 75
#define GMAP_LOCKWALL_HIDE_MINT_PC1 76
#define GMAP_LOCKWALL_HIDE_MINT_PC2 77
#define GMAP_LOCKWALL_HIDE_RED 78
#define GMAP_LOCKWALL_HIDE_RED_PC1 79
#define GMAP_LOCKWALL_HIDE_RED_PC2 80
#define GMAP_LOCKWALL_HIDE_PURPLE 81
#define GMAP_LOCKWALL_HIDE_PURPLE_PC1 82
#define GMAP_LOCKWALL_HIDE_PURPLE_PC2 83
#define GMAP_LOCKWALL_HIDE_YELLOW 84
#define GMAP_LOCKWALL_HIDE_YELLOW_PC1 85
#define GMAP_LOCKWALL_HIDE_YELLOW_PC2 86
#define GMAP_FAKEBUTTON_BLUE 87
#define GMAP_FAKEBUTTON_BLUE_PC1 88
#define GMAP_FAKEBUTTON_BLUE_PC2 89
#define GMAP_FAKEBUTTON_GREEN 90
#define GMAP_FAKEBUTTON_GREEN_PC1 91
#define GMAP_FAKEBUTTON_GREEN_PC2 92
#define GMAP_FAKEBUTTON_MINT 93
#define GMAP_FAKEBUTTON_MINT_PC1 94
#define GMAP_FAKEBUTTON_MINT_PC2 95
#define GMAP_FAKEBUTTON_RED 96
#define GMAP_FAKEBUTTON_RED_PC1 97
#define GMAP_FAKEBUTTON_RED_PC2 98
#define GMAP_FAKEBUTTON_PURPLE 99
#define GMAP_FAKEBUTTON_PURPLE_PC1 100
#define GMAP_FAKEBUTTON_PURPLE_PC2 101
#define GMAP_FAKEBUTTON_YELLOW 102
#define GMAP_FAKEBUTTON_YELLOW_PC1 103
#define GMAP_FAKEBUTTON_YELLOW_PC2 104GMAP_LIFEUP
#define GMAP_LIFEUP 105





/*UI정보*/
//UI의 글자색의 콘솔 색상값
#define UI_COLOR 15
//UI의 배경색의 콘솔 색상값
#define UI_BACKCOLOR 0
//게임화면 중앙 X좌표
#define UI_CENTER_X GBOARD_ORIGIN_X + GBOARD_WIDTH / 2
//게임화면 중앙 Y좌표
#define UI_CENTER_Y GBOARD_ORIGIN_Y + GBOARD_HEIGHT / 2





/*시스템 정보*/

//게임의 기본 글자색과 배경색
#define SYSTEM_COLOR "color 0F"
//게임에서 사용하는 배열의 최댓값
#define SYSTEM_MAX_ARRAYINDEX 300
//게임의 마지막 레벨(보스 스테이지)
#define SYSTEM_MAX_LEVEL 3
//1p의 최대 점프높이
#define SYSTEM_MAX_JUMPHEIGHT 3
//시작 코인
#define SYSTEM_MAX_COIN 5
//시작 라이프
#define SYSTEM_START_LIFE 3
//최대 라이프
#define SYSTEM_MAX_LIFE 5
//시작 라이프
#define SYSTEM_MAX_INVINCIBLETIME 1



/*게임 루프 시분할*/

//1회 시뮬레이션 시간
#define GAMELOOP_TIME 100
//1차 반복 횟수
#define GAMELOOP_1  5//500
//2차 반복 횟수
#define GAMELOOP_2 2//1000
//3차 반복 횟수
#define GAMELOOP_3 3//3000
//4차 반복 횟수
#define GAMELOOP_4 2//6000




/*색깔 정보*/

//검정색의 콘솔 색상값
#define BLACK 0
//파랑색의 콘솔 색상값
#define BLUE_DARK 1
//초록색의 콘솔 색상값
#define GREEN_DARK 2
//옥색의 콘솔 색상값
#define MINT_DARK 3
//빨강색의 콘솔 색상값
#define RED_DARK 4
//자주색의 콘솔 색상값
#define PURPLE_DARK 5
//노랑색의 콘솔 색상값
#define YELLOW_DARK 6
//흰색의 콘솔 색상값
#define WHITE_DARK 7
//회색의 콘솔 색상값
#define GREY 8
//밝은 파랑색의 콘솔 색상값
#define BLUE 9
//밝은 초록색의 콘솔 색상값
#define GREEN 10
//밝은 옥색의 콘솔 색상값
#define MINT 11
//밝은 빨강색의 콘솔 색상값
#define RED 12
//밝은 자주색의 콘솔 색상값
#define PURPLE 13
//밝은 노랑색의 콘솔 색상값
#define YELLOW 14
//밝은 흰색의 콘솔 색상값
#define WHITE 15