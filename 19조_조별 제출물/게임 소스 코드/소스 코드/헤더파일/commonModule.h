#pragma once

#pragma warning(disable :4996)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>

#include "macro.h"
#include "globalVariable.h"

//전역변수 정의
void GlobalVariableDefinition(void);
//글자 색 text로 바꾸고 배경색을 back으로 바꿈. 콘솔 색상 사용(0~15)
void SetColor(unsigned short text, unsigned short back);
//커서위치 x y 로 이동
void SetCurrentCursorPos(int x, int y);
//커서 숨기기
void RemoveCursor(void);

//기본적인 게임 세팅을 해준다.
void GameSetting(void);

//게임 상태 관리
void StateController(void);

//이전에 처리하지 못한 키 입력을 리셋함
void inputReset(void);

//엑셀 데이터 읽어와서 배열에 저장
void BuildMapDataArray(void);
//엑셀 데이터의 배열 값이 전역변수배열에서 어떤 인덱스를 차지했을지를 알려줌
int FindMapDataIndex(int data);


//화면 윤곽선 그리기
void DrawOutline(void);
//좌측상단 좌표와 너비와 높이를 기준으로 문자열을 출력함. 문자열의 사이즈를 지정할 수 있음
void DrawString_Size(int leftTop_X, int leftTop_Y, int width, int height, char* str, int sizeX, int sizeY);
//x y 좌표에 문자열을 출력
void DrawString_Dot(int x, int y, char* str);
//x y 좌표에 숫자를 출력
void DrawString_Dot_Int(int x, int y, int num);

// 게임 종료시 종료화면을 그림
void BuildExit(void);


//화면 주위를 도는 이펙트
void Effect_Rotation(int color);
//화면 주위를 채우는 이펙트
void Effect_Rotation_Keep(int color);
//화면 주위에 깜빡이는 이펙트
void Effect_Blink(int color);
//화면주위의 색을 바꾸는 이펙트
void Effect_Outline(int color);

//보스 스테이지 진입 연출
void BossStageEffect(void);


//게임 화면 지우기
void ClearGameScreen(void);
//우측 상단 UI 지우기
void ClearUI(void);
//좌측 하단 로그 지우기
void ClearLog(void);



//게임 타이틀 출력
void PrintTitle(void);