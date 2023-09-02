#pragma once


/*�ƽ�Ű �ڵ�*/

//Ű���� �� �� �ƽ�Ű�ڵ�
#define UP 72
//Ű���� �� �� �ƽ�Ű�ڵ�
#define DOWN 80
//Ű���� �� �� �ƽ�Ű�ڵ�
#define LEFT 75
//Ű���� �� �� �ƽ�Ű�ڵ�
#define RIGHT 77
//Ű���� �����̽����� �ƽ�Ű�ڵ�
#define SPACE 32




/*���Ӻ���*/

//���Ӻ��� �ʺ�, ���Ӻ��尡 �����ϴ� X��ǥ ����
#define GBOARD_WIDTH 80
//���Ӻ��� ����, ���Ӻ��尡 �����ϴ� Y��ǥ ����
#define GBOARD_HEIGHT 40
//���Ӻ��尡 ���۵Ǵ� �»�� X��ǥ
#define GBOARD_ORIGIN_X 4
//���Ӻ��尡 ���۵Ǵ� �»�� Y��ǥ
#define GBOARD_ORIGIN_Y 3

//���Ӻ��� ���� ����� Y��ǥ
#define GBOARD_TOP_POSITION_Y GBOARD_ORIGIN_Y
//���Ӻ��� ���� �ϴ��� Y��ǥ
#define GBOARD_BOTTOM_POSITION_Y (GBOARD_ORIGIN_Y + GBOARD_HEIGHT + 1)
//���Ӻ��� ���� ������ X��ǥ
#define GBOARD_LEFT_POSITION_X GBOARD_ORIGIN_X
//���Ӻ��� ���� ������ X��ǥ
#define GBOARD_RIGHT_POSITION_X (GBOARD_ORIGIN_X + GBOARD_WIDTH + 2)





/*���Ӻ��� �迭*/

//���Ӻ��� �ʺ��� �ִ� �ε���
#define GARRAY_WIDTH_MAXINDEX ((GBOARD_WIDTH / 2) + 1)
//���Ӻ��� ������ �ִ� �ε���
#define GARRAY_HEIGHT_MAXINDEX (GBOARD_HEIGHT + 1)





/*������ġ*/
//����ȭ���� gLocation ��
#define GLOCATION_EXIT 0
//�κ��� gLocation ��
#define GLOCATION_LOBBY 1
//������ gLocation ��
#define GLOCATION_GAME 2
//���� ������ gLocation ��
#define GLOCATION_STATE 3
//������ ���� gLocation ��
#define GLOCATION_LEVELDESIGN 4






/*���ӻ���*/

//���� ������ gState ��
#define GSTATE_EXIT 0
//���� ������ gState ��
#define GSTATE_BEGIN 1
//���� 1 ���� ���� ������ gState ��
#define GSTATE_START 2
//���� ������� gState ��
#define GSTATE_RETRY 3
//���� ������ gState ��
#define GSTATE_GAMEOVER 4
//���� Ŭ������ gState ��
#define GSTATE_CLEAR 5
//���� ������ gState ��
#define GSTATE_ENDING 6
//�������� ������ gState ��
#define GSTATE_DESIGNTOOL_ON 7
//�������� ������ gState ��
#define GSTATE_DESIGNTOOL_OFF 8






/*�� ����-�迭��*/

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





/*UI����*/
//UI�� ���ڻ��� �ܼ� ����
#define UI_COLOR 15
//UI�� ������ �ܼ� ����
#define UI_BACKCOLOR 0
//����ȭ�� �߾� X��ǥ
#define UI_CENTER_X GBOARD_ORIGIN_X + GBOARD_WIDTH / 2
//����ȭ�� �߾� Y��ǥ
#define UI_CENTER_Y GBOARD_ORIGIN_Y + GBOARD_HEIGHT / 2





/*�ý��� ����*/

//������ �⺻ ���ڻ��� ����
#define SYSTEM_COLOR "color 0F"
//���ӿ��� ����ϴ� �迭�� �ִ�
#define SYSTEM_MAX_ARRAYINDEX 300
//������ ������ ����(���� ��������)
#define SYSTEM_MAX_LEVEL 3
//1p�� �ִ� ��������
#define SYSTEM_MAX_JUMPHEIGHT 3
//���� ����
#define SYSTEM_MAX_COIN 5
//���� ������
#define SYSTEM_START_LIFE 3
//�ִ� ������
#define SYSTEM_MAX_LIFE 5
//���� ������
#define SYSTEM_MAX_INVINCIBLETIME 1



/*���� ���� �ú���*/

//1ȸ �ùķ��̼� �ð�
#define GAMELOOP_TIME 100
//1�� �ݺ� Ƚ��
#define GAMELOOP_1  5//500
//2�� �ݺ� Ƚ��
#define GAMELOOP_2 2//1000
//3�� �ݺ� Ƚ��
#define GAMELOOP_3 3//3000
//4�� �ݺ� Ƚ��
#define GAMELOOP_4 2//6000




/*���� ����*/

//�������� �ܼ� ����
#define BLACK 0
//�Ķ����� �ܼ� ����
#define BLUE_DARK 1
//�ʷϻ��� �ܼ� ����
#define GREEN_DARK 2
//������ �ܼ� ����
#define MINT_DARK 3
//�������� �ܼ� ����
#define RED_DARK 4
//���ֻ��� �ܼ� ����
#define PURPLE_DARK 5
//������� �ܼ� ����
#define YELLOW_DARK 6
//����� �ܼ� ����
#define WHITE_DARK 7
//ȸ���� �ܼ� ����
#define GREY 8
//���� �Ķ����� �ܼ� ����
#define BLUE 9
//���� �ʷϻ��� �ܼ� ����
#define GREEN 10
//���� ������ �ܼ� ����
#define MINT 11
//���� �������� �ܼ� ����
#define RED 12
//���� ���ֻ��� �ܼ� ����
#define PURPLE 13
//���� ������� �ܼ� ����
#define YELLOW 14
//���� ����� �ܼ� ����
#define WHITE 15