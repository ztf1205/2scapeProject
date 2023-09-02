#pragma once

//���� �� Key �Է� �ޱ�
void GameKeyInput(int developMode);
//���� �ݺ���
void GameLoop(int developMode);

//pc(1 or 2)�� �ش�������� �����δ�. direction=U,D,L,R
void MovingPlayer(int player, char direction);
//�ش� Ÿ���� ��ư���� �ƴ��� ��ȯ
int IsButton(int type);
//�ش� Ÿ���� �������� �ƴ��� ��ȯ
int IsLockWall(int type);
//�ش� Ÿ���� ������ �������� �ƴ��� ��ȯ
int IsHiddenLockWall(int type);
//p1�� ������Ų��
void Jump1P(void);
//p1�� ���� �߷� �ý���
void GravitySystem(void);
//�������� hitFlag�� �̿��ؼ� �ǰݽÿ� �������� ��´�
void LifeSystem(void);
//PC1 �ǰ�ó��
void LifeSystem_PC1(void);
//PC2 �ǰ�ó��
void LifeSystem_PC2(void);
//PC1 ������ ��
void LifeUp_PC1(void);
//PC2 ������ ��
void LifeUp_PC2(void);

//pc(GMAP)�� �������� ������ �� �������� ��ȯ(0 or 1)
int MoveAble(int nextBlockType);
//p1�� ������ �� �ִ����� ��ȯ(0 or 1)
int JumpAble(void);
//���� ĭ���� ���� ���� Ʈ����
void MoveOutTrigger(int pc, int currentBlockType, int nextBlockType);
//���� ĭ���� �����ϸ鼭 �ش� ĭ�� �ִ� ������, ��Ͽ� ���� Ʈ���� ����
void MoveInTrigger(int pc,int currentBlockType, int nextBlockType);
//������ �� ���� ���� Ʈ����
void StopTrigger(int pc, int nextBlockType);


//���� ���Խ� �ش��ϴ� ������ ȭ�鿡 �׸��� �ʱ� ������ ����
void BuildGame(int index);


//x y ��ǥ�� �迭���� mapData�� �ش��ϴ� ������ �׸�
void DrawGameBoard(int x, int y, int mapData);
//x y ��ǥ�� ���� ���忡 mapData�� �Ҵ�� �ٲ���
void ChangeGameBoard(int x, int y, int mapData);
//�迭���� �ٲٰ� ȭ�鿡 �׸��� ���� ��� ������
void UpdateGameBoard(int x, int y, int mapData);
//�ش� x,y ��ǥ���� �÷��̾ ������ ���� ó��
void MoveOutGameBoard(int x, int y, int pc);
//�ش� x,y ��ǥ�� �÷��̾ ���� ���� ó��
void MoveInGameBoard(int x, int y, int pc);

//�ʿ� �ִ� �߻�뿡�� ȭ�� �߻�
void ShootArrow(void);
//�߻�� ȭ����� ��ĭ�� �̵�
void MoveArrow(void);

//���� �����ֱ�
void ShowHiddenWall(void);
//����� �����
void HideHiddenWall(void);

//���� �����ϸ鼭 �絵�� or ���ӿ���
void Retry(void);
//pc ���� ó�� - ����Ʈ�� Retry()ó��
void Death(int pc);
//pc ���� ��� ���� ó�� - ����Ʈ�� Retry()ó�� + ������ ����
void Death_Wall(int pc);


/* Ʈ���� */

//��� ��ư���� �������� ���� Ʈ����
void Trigger_ToggleButton_MoveOut(int currentBlockType, int nextBlockType);

//������� ���� Ŭ���� ����(1�� ���? 2�� ���? ������ ��� ���� ���α׷� ����)
void Trigger_Door(int pc);
//���� ó�� �� ������Ʈ �����
void Trigger_Key(int nextBlockType);
//��ư ó��
void Trigger_Button(int currentBlockType, int nextBlockType);
//��� ��ư�� �� ���� Ʈ����
void Trigger_ToggleButton_MoveIn(int nextBlockType);

//�������̳� ������ �浹 �� �������� �԰� ����� �Լ�
void Trigger_Damage(int hitPc);


//Ư���� Ʈ���� ó��
void SpecialTrigger(void);
//���� Ʈ���� ó��
void SpecialTrigger_Boss(void);







/* ����Ʈ */

//�� ���� �߽����� �簢���� ���������� ����Ʈ
void Effect_Square(int x, int y, int color, int processDelay, int completeDelay);
//Effect_Square�� ���� �Լ�
void Effect_Square_Line(int x, int y, int offset, int color, char direction, int isEffect);








//���� ���� ���
void Game_Status(void);