#pragma once

//게임 중 Key 입력 받기
void GameKeyInput(int developMode);
//게임 반복문
void GameLoop(int developMode);

//pc(1 or 2)를 해당방향으로 움직인다. direction=U,D,L,R
void MovingPlayer(int player, char direction);
//해당 타입이 버튼인지 아닌지 반환
int IsButton(int type);
//해당 타입이 색깔벽인지 아닌지 반환
int IsLockWall(int type);
//해당 타입이 숨겨진 색깔벽인지 아닌지 반환
int IsHiddenLockWall(int type);
//p1을 점프시킨다
void Jump1P(void);
//p1를 위한 중력 시스템
void GravitySystem(void);
//전역변수 hitFlag를 이용해서 피격시에 라이프를 깎는다
void LifeSystem(void);
//PC1 피격처리
void LifeSystem_PC1(void);
//PC2 피격처리
void LifeSystem_PC2(void);
//PC1 라이프 업
void LifeUp_PC1(void);
//PC2 라이프 업
void LifeUp_PC2(void);

//pc(GMAP)가 다음으로 움직일 수 있을지를 반환(0 or 1)
int MoveAble(int nextBlockType);
//p1이 점프할 수 있는지를 반환(0 or 1)
int JumpAble(void);
//현재 칸에서 나올 때의 트리거
void MoveOutTrigger(int pc, int currentBlockType, int nextBlockType);
//다음 칸으로 진입하면서 해당 칸에 있는 아이템, 블록에 따라서 트리거 실행
void MoveInTrigger(int pc,int currentBlockType, int nextBlockType);
//움직일 수 없을 때의 트리거
void StopTrigger(int pc, int nextBlockType);


//게임 진입시 해당하는 레벨을 화면에 그리고 초기 설정을 해줌
void BuildGame(int index);


//x y 좌표에 배열값에 mapData에 해당하는 정보를 그림
void DrawGameBoard(int x, int y, int mapData);
//x y 좌표의 게임 보드에 mapData값 할당로 바꿔줌
void ChangeGameBoard(int x, int y, int mapData);
//배열값을 바꾸고 화면에 그리는 것을 모두 수행함
void UpdateGameBoard(int x, int y, int mapData);
//해당 x,y 좌표에서 플레이어가 나오는 것을 처리
void MoveOutGameBoard(int x, int y, int pc);
//해당 x,y 좌표에 플레이어가 들어가는 것을 처리
void MoveInGameBoard(int x, int y, int pc);

//맵에 있는 발사대에서 화살 발사
void ShootArrow(void);
//발사된 화살들을 한칸씩 이동
void MoveArrow(void);

//투명벽 보여주기
void ShowHiddenWall(void);
//투명블럭 숨기기
void HideHiddenWall(void);

//코인 감소하면서 재도전 or 게임오버
void Retry(void);
//pc 죽음 처리 - 이펙트와 Retry()처리
void Death(int pc);
//pc 벽에 끼어서 죽음 처리 - 이펙트와 Retry()처리 + 벽끼임 문구
void Death_Wall(int pc);


/* 트리거 */

//토글 버튼에서 빠져나올 때의 트리거
void Trigger_ToggleButton_MoveOut(int currentBlockType, int nextBlockType);

//문통과시 레벨 클리어 구현(1명 통과? 2명 통과? 각각의 경우 따라 프로그램 수정)
void Trigger_Door(int pc);
//열쇠 처리 후 오브젝트 지우기
void Trigger_Key(int nextBlockType);
//버튼 처리
void Trigger_Button(int currentBlockType, int nextBlockType);
//토글 버튼에 들어갈 때의 트리거
void Trigger_ToggleButton_MoveIn(int nextBlockType);

//함정들이나 보스에 충돌 시 데미지를 입게 만드는 함수
void Trigger_Damage(int hitPc);


//특별한 트리거 처리
void SpecialTrigger(void);
//보스 트리거 처리
void SpecialTrigger_Boss(void);







/* 이펙트 */

//한 점을 중심으로 사각으로 퍼져나가는 이펙트
void Effect_Square(int x, int y, int color, int processDelay, int completeDelay);
//Effect_Square를 위한 함수
void Effect_Square_Line(int x, int y, int offset, int color, char direction, int isEffect);








//게임 상태 출력
void Game_Status(void);