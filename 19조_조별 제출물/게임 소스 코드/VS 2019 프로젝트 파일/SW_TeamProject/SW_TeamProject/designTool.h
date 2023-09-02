#pragma once

/*���������̳ʰ� �̿��ϴ� �Լ� AddMap_~ 3����
type�� �ٲ��ְ� ���� �������̳� ���� �ǹ��� ex : GMAP_WALL
level�� �ٲٰ� ���� ����(1~3)
size�� pos�� �簢�� ������ �ٲ��ְ� dot�� ������ �ٲ���*/

//���� ����� ��ǥ�� �ʺ�� ���̸� �̿��ؼ� �簢�� ������ ���� ä���
void AddMap_Size(int leftTop_X, int leftTop_Y, int width, int height, int type, int level);
//���� ����� ��ǥ�� ���� �ϴ��� ��ǥ�� �̿��ؼ� �簢�� ������ ���� ä���
void AddMap_Pos(int leftTop_X, int leftTop_Y, int rightDown_X, int rightDown_Y, int type, int level);
//�� ���� ���� ä���
void AddMap_Dot(int x, int y, int type, int level);


//AddMap_~�� ȣ���Ͽ� ������ �����Ѵ�
void BuildMap(void);


//���������� �� ����
void LevelDesignToolLoop(void);

//���������� �� ����
void BuildLevelDesignTool(void);