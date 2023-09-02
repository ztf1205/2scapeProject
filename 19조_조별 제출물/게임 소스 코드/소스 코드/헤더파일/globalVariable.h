#pragma once

#ifdef GLOBAL_VARIABLE_DECLARATION
#define EXT extern
#else
#define GLOBAL_VARIABLE_DECLARATION
#define EXT
#endif // GLOBAL_VARIABLE_DECLARATION

//게임의 상태
EXT int gState;
//게임의 현재 위치
EXT int gLocation;
//현재의 레벨
EXT int currentLevelIndex;
//게임 진행 시간
EXT int time;
//점프 남아있는 힘
EXT int jumpRemain;
//게임이 진행되는 게임보드
EXT int gameBoardArray[GARRAY_HEIGHT_MAXINDEX + 1][GARRAY_WIDTH_MAXINDEX + 1];

//엑셀데이터 숫자
EXT int mapData_Num[SYSTEM_MAX_ARRAYINDEX + 1];
//엑셀데이터 글자
EXT char mapData_Char[SYSTEM_MAX_ARRAYINDEX + 1][SYSTEM_MAX_ARRAYINDEX + 1];
//엑셀데이터 글자색
EXT int mapData_Color[SYSTEM_MAX_ARRAYINDEX + 1];
//엑셀데이터 배경색
EXT int mapData_BackColor[SYSTEM_MAX_ARRAYINDEX + 1];

//맵 정보
EXT int map[SYSTEM_MAX_LEVEL][GARRAY_HEIGHT_MAXINDEX + 1][GARRAY_WIDTH_MAXINDEX + 1];

//P1의 x좌표
EXT int P1_PosX;
//P1의 y좌표
EXT int P1_PosY;
//P2의 x좌표
EXT int P2_PosX;
//P2의 y좌표
EXT int P2_PosY;

//도전기회
EXT int coin;
//P1 라이프
EXT int P1_Life;
//P2 라이프
EXT int P2_Life;
//P1 피격 여부 저장하는 플래그
EXT int P1_HitFlag;
//P2 피격 여부 저장하는 플래그
EXT int P2_HitFlag;
//P1 남아있는 무적 시간
EXT int P1_InvincibleTimeRemain;
//P2 남아있는 무적 시간
EXT int P2_InvincibleTimeRemain;
//P1 라이프 업 플래그
EXT int P1_LifeUpFlag;
//P2 라이프 업 플래그
EXT int P2_LifeUpFlag;

//최종 클리어 타임
EXT int ClearTime;
//데스 카운트
EXT int DeathCount;