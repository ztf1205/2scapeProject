#pragma once

#pragma warning(disable :4996)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>

#include "macro.h"
#include "globalVariable.h"

//�������� ����
void GlobalVariableDefinition(void);
//���� �� text�� �ٲٰ� ������ back���� �ٲ�. �ܼ� ���� ���(0~15)
void SetColor(unsigned short text, unsigned short back);
//Ŀ����ġ x y �� �̵�
void SetCurrentCursorPos(int x, int y);
//Ŀ�� �����
void RemoveCursor(void);

//�⺻���� ���� ������ ���ش�.
void GameSetting(void);

//���� ���� ����
void StateController(void);

//������ ó������ ���� Ű �Է��� ������
void inputReset(void);

//���� ������ �о�ͼ� �迭�� ����
void BuildMapDataArray(void);
//���� �������� �迭 ���� ���������迭���� � �ε����� ������������ �˷���
int FindMapDataIndex(int data);


//ȭ�� ������ �׸���
void DrawOutline(void);
//������� ��ǥ�� �ʺ�� ���̸� �������� ���ڿ��� �����. ���ڿ��� ����� ������ �� ����
void DrawString_Size(int leftTop_X, int leftTop_Y, int width, int height, char* str, int sizeX, int sizeY);
//x y ��ǥ�� ���ڿ��� ���
void DrawString_Dot(int x, int y, char* str);
//x y ��ǥ�� ���ڸ� ���
void DrawString_Dot_Int(int x, int y, int num);

// ���� ����� ����ȭ���� �׸�
void BuildExit(void);


//ȭ�� ������ ���� ����Ʈ
void Effect_Rotation(int color);
//ȭ�� ������ ä��� ����Ʈ
void Effect_Rotation_Keep(int color);
//ȭ�� ������ �����̴� ����Ʈ
void Effect_Blink(int color);
//ȭ�������� ���� �ٲٴ� ����Ʈ
void Effect_Outline(int color);

//���� �������� ���� ����
void BossStageEffect(void);


//���� ȭ�� �����
void ClearGameScreen(void);
//���� ��� UI �����
void ClearUI(void);
//���� �ϴ� �α� �����
void ClearLog(void);



//���� Ÿ��Ʋ ���
void PrintTitle(void);