#pragma once

#ifdef GLOBAL_VARIABLE_DECLARATION
#define EXT extern
#else
#define GLOBAL_VARIABLE_DECLARATION
#define EXT
#endif // GLOBAL_VARIABLE_DECLARATION

//������ ����
EXT int gState;
//������ ���� ��ġ
EXT int gLocation;
//������ ����
EXT int currentLevelIndex;
//���� ���� �ð�
EXT int time;
//���� �����ִ� ��
EXT int jumpRemain;
//������ ����Ǵ� ���Ӻ���
EXT int gameBoardArray[GARRAY_HEIGHT_MAXINDEX + 1][GARRAY_WIDTH_MAXINDEX + 1];

//���������� ����
EXT int mapData_Num[SYSTEM_MAX_ARRAYINDEX + 1];
//���������� ����
EXT char mapData_Char[SYSTEM_MAX_ARRAYINDEX + 1][SYSTEM_MAX_ARRAYINDEX + 1];
//���������� ���ڻ�
EXT int mapData_Color[SYSTEM_MAX_ARRAYINDEX + 1];
//���������� ����
EXT int mapData_BackColor[SYSTEM_MAX_ARRAYINDEX + 1];

//�� ����
EXT int map[SYSTEM_MAX_LEVEL][GARRAY_HEIGHT_MAXINDEX + 1][GARRAY_WIDTH_MAXINDEX + 1];

//P1�� x��ǥ
EXT int P1_PosX;
//P1�� y��ǥ
EXT int P1_PosY;
//P2�� x��ǥ
EXT int P2_PosX;
//P2�� y��ǥ
EXT int P2_PosY;

//������ȸ
EXT int coin;
//P1 ������
EXT int P1_Life;
//P2 ������
EXT int P2_Life;
//P1 �ǰ� ���� �����ϴ� �÷���
EXT int P1_HitFlag;
//P2 �ǰ� ���� �����ϴ� �÷���
EXT int P2_HitFlag;
//P1 �����ִ� ���� �ð�
EXT int P1_InvincibleTimeRemain;
//P2 �����ִ� ���� �ð�
EXT int P2_InvincibleTimeRemain;
//P1 ������ �� �÷���
EXT int P1_LifeUpFlag;
//P2 ������ �� �÷���
EXT int P2_LifeUpFlag;

//���� Ŭ���� Ÿ��
EXT int ClearTime;
//���� ī��Ʈ
EXT int DeathCount;