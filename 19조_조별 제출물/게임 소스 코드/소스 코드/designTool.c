#include "commonModule.h"
#include "designTool.h"


void AddMap_Size(int leftTop_X, int leftTop_Y, int width, int height, int type, int level)
{
	int i, j;
	for (i = leftTop_Y; i < leftTop_Y + height; i++)
	{
		for (j = leftTop_X; j < leftTop_X + width; j++)
		{
			map[level - 1][i][j] = type;
		}
	}
}

void AddMap_Pos(int leftTop_X, int leftTop_Y, int rightDown_X, int rightDown_Y, int type, int level)
{
	int i, j;
	for (i = leftTop_Y; i <= rightDown_Y; i++)
	{
		for (j = leftTop_X; j <= rightDown_X; j++)
		{
			map[level - 1][i][j] = type;
		}
	}
}

void AddMap_Dot(int x, int y, int type, int level)
{
	map[level - 1][y][x] = type;
}


/*
<배치 가능 블록>

1.기본요소
#define GMAP_SPACE 0
#define GMAP_PC1 1
#define GMAP_PC2 2
#define GMAP_WALL 3
#define GMAP_HIDDENWALL 4
#define GMAP_DOOR 5
#define GMAP_BOSS 6



2.함정요소
#define GMAP_SPIKE_UP 7
#define GMAP_SPIKE_DOWN 8
#define GMAP_SPIKE_LEFT 9
#define GMAP_SPIKE_RIGHT 10
#define GMAP_BOMB 11
#define GMAP_SHOOTER_UP 16
#define GMAP_SHOOTER_DOWN 17
#define GMAP_SHOOTER_LEFT 18
#define GMAP_SHOOTER_RIGHT 19



3.퍼즐요소
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
#define GMAP_BUTTON_GREEN 35
#define GMAP_BUTTON_MINT 38
#define GMAP_BUTTON_RED 41
#define GMAP_BUTTON_PURPLE 44
#define GMAP_BUTTON_YELLOW 47

#define GMAP_TOGGLE_BUTTON_BLUE 50
#define GMAP_TOGGLE_BUTTON_GREEN 53
#define GMAP_TOGGLE_BUTTON_MINT 56
#define GMAP_TOGGLE_BUTTON_RED 59
#define GMAP_TOGGLE_BUTTON_PURPLE 62
#define GMAP_TOGGLE_BUTTON_YELLOW 65

#define GMAP_BOSS_WALL 68

#define GMAP_FAKEBUTTON_BLUE 87
#define GMAP_FAKEBUTTON_GREEN 90
#define GMAP_FAKEBUTTON_MINT 93
#define GMAP_FAKEBUTTON_RED 96
#define GMAP_FAKEBUTTON_PURPLE 99
#define GMAP_FAKEBUTTON_YELLOW 102

*/


void BuildMap(void)
{
	/*##################################################################################
	##################################   < 레벨 1 시작 >   ##############################
	##################################################################################*/
	//필수 - PC1, PC2와 가장자리 벽
	AddMap_Dot(3, GARRAY_HEIGHT_MAXINDEX - 1, GMAP_PC1, 1);
	AddMap_Dot(36, 13, GMAP_PC2, 1);
	//AddMap_Dot(20, 13, GMAP_PC2, 1);
	AddMap_Pos(0, 0, GARRAY_WIDTH_MAXINDEX, 0, GMAP_WALL, 1);
	AddMap_Pos(0, GARRAY_HEIGHT_MAXINDEX, GARRAY_WIDTH_MAXINDEX, GARRAY_HEIGHT_MAXINDEX, GMAP_WALL, 1);
	AddMap_Pos(0, 1, 0, GARRAY_HEIGHT_MAXINDEX, GMAP_WALL, 1);
	AddMap_Pos(GARRAY_WIDTH_MAXINDEX, 1, GARRAY_WIDTH_MAXINDEX, GARRAY_HEIGHT_MAXINDEX, GMAP_WALL, 1);

	//벽
	AddMap_Pos(0, 38, 38, 38, GMAP_WALL, 1);//첫번째 가로줄
	AddMap_Pos(3, 35, 38, 35, GMAP_WALL, 1);//두번째 가로줄
	AddMap_Pos(38, 30, 38, 35, GMAP_WALL, 1);//세로줄 가로
	AddMap_Pos(37, 31, 37, 35, GMAP_WALL, 1);//세로줄 가로
	AddMap_Pos(36, 32, 36, 35, GMAP_WALL, 1);//세로줄 가로
	AddMap_Pos(35, 33, 35, 35, GMAP_WALL, 1);//세로줄 가로
	AddMap_Pos(34, 34, 34, 35, GMAP_WALL, 1);//세로줄 가로

	AddMap_Pos(7, 5, 7, 35, GMAP_WALL, 1);//세로줄
	AddMap_Pos(1, 32, 4, 32, GMAP_WALL, 1);//세로줄 가로
	AddMap_Pos(3, 29, 7, 29, GMAP_WALL, 1);//세로줄 가로
	AddMap_Pos(1, 26, 4, 26, GMAP_WALL, 1);//세로줄 가로
	AddMap_Pos(3, 23, 7, 23, GMAP_WALL, 1);//세로줄 가로
	AddMap_Pos(1, 20, 4, 20, GMAP_WALL, 1);//세로줄 가로
	AddMap_Pos(3, 17, 6, 17, GMAP_HIDDENWALL, 1);//세로줄 가로
	AddMap_Pos(1, 14, 4, 14, GMAP_HIDDENWALL, 1);//세로줄 가로
	AddMap_Pos(3, 11, 6, 11, GMAP_HIDDENWALL, 1);//세로줄 가로
	AddMap_Pos(1, 8, 4, 8, GMAP_HIDDENWALL, 1);//세로줄 가로
	AddMap_Pos(3, 5, 6, 5, GMAP_HIDDENWALL, 1);//세로줄 가로

	AddMap_Pos(3, 6, 4, 7, GMAP_LOCKWALL_BLUE, 1);//세로벽
	AddMap_Pos(3, 9, 4, 10, GMAP_LOCKWALL_RED, 1);//세로벽
	AddMap_Pos(3, 12, 4, 13, GMAP_LOCKWALL_BLUE, 1);//세로벽
	AddMap_Pos(3, 15, 4, 16, GMAP_LOCKWALL_RED, 1);//세로벽
	AddMap_Pos(3, 18, 4, 19, GMAP_LOCKWALL_BLUE, 1);//세로벽
	AddMap_Pos(3, 21, 4, 22, GMAP_LOCKWALL_RED, 1);//세로벽
	AddMap_Pos(3, 24, 4, 25, GMAP_LOCKWALL_BLUE, 1);//세로벽
	AddMap_Pos(3, 27, 4, 28, GMAP_LOCKWALL_RED, 1);//세로벽
	AddMap_Pos(3, 30, 4, 31, GMAP_LOCKWALL_BLUE, 1);//세로벽



	//따라올라가는벽

	AddMap_Pos(12, 14, 14, 14, GMAP_WALL, 1);//세로줄 가로
	AddMap_Pos(18, 14, 20, 14, GMAP_HIDDENWALL, 1);//세로줄 가로
	AddMap_Pos(24, 14, 26, 14, GMAP_WALL, 1);//세로줄 가로
	AddMap_Pos(30, 14, 31, 14, GMAP_HIDDENWALL, 1);//세로줄 가로

	AddMap_Pos(33, 14, 40, 14, GMAP_WALL, 1);
	AddMap_Pos(33, 0, 33, 10, GMAP_WALL, 1);
	AddMap_Pos(33, 11, 33, 13, GMAP_LOCKWALL_GREEN, 1);
	AddMap_Dot(32, 11 - 1, GMAP_KEY_GREEN, 1);


	AddMap_Pos(37, 16, 40, 16, GMAP_WALL, 1);//
	AddMap_Dot(40, 15, GMAP_DOOR, 1);


	AddMap_Dot(40, 1, GMAP_TOGGLE_BUTTON_BLUE, 1);
	AddMap_Dot(34, 1, GMAP_TOGGLE_BUTTON_RED, 1);

	AddMap_Pos(8, 34, 27, 34, GMAP_SHOOTER_UP, 1);//세로벽


	AddMap_Dot(GARRAY_WIDTH_MAXINDEX -1, GARRAY_HEIGHT_MAXINDEX - 5, GMAP_LIFEUP, 1);


	/*##################################################################################
	##################################   < 레벨 2 시작 >   ##############################
	##################################################################################*/
	//필수 - PC1, PC2와 가장자리 벽
	AddMap_Dot(2, GARRAY_HEIGHT_MAXINDEX - 1, GMAP_PC1, 2);
	AddMap_Dot(1, GARRAY_HEIGHT_MAXINDEX - 1, GMAP_PC2, 2);
	//AddMap_Dot(32, 8 - 1, GMAP_PC2, 2);
	AddMap_Pos(0, 0, GARRAY_WIDTH_MAXINDEX, 0, GMAP_WALL, 2);
	AddMap_Pos(0, GARRAY_HEIGHT_MAXINDEX, GARRAY_WIDTH_MAXINDEX, GARRAY_HEIGHT_MAXINDEX, GMAP_WALL, 2);
	AddMap_Pos(0, 1, 0, GARRAY_HEIGHT_MAXINDEX, GMAP_WALL, 2);
	AddMap_Pos(GARRAY_WIDTH_MAXINDEX, 1, GARRAY_WIDTH_MAXINDEX, GARRAY_HEIGHT_MAXINDEX, GMAP_WALL, 2);
	//미로
	AddMap_Pos(2, 39/*Y*/, 38, 39/*Y*/, GMAP_WALL, 2);//가로
	AddMap_Pos(2/*X*/, 3, 2/*X*/, 39, GMAP_WALL, 2);//세로
	AddMap_Pos(29/*X*/, 5, 29/*X*/, 39, GMAP_WALL, 2);//세로
	AddMap_Pos(2, 2/*Y*/, 39, 2/*Y*/, GMAP_WALL, 2);//가로
	AddMap_Pos(4, 4/*Y*/, 40, 4/*Y*/, GMAP_WALL, 2);//가로
	AddMap_Dot(4, 5, GMAP_WALL, 2);
	//틀
	AddMap_Dot(4, 7, GMAP_WALL, 2);
	AddMap_Dot(4, 8, GMAP_WALL, 2);
	AddMap_Dot(4, 9, GMAP_WALL, 2);
	AddMap_Dot(4, 10, GMAP_WALL, 2);
	AddMap_Dot(4, 11, GMAP_WALL, 2);
	AddMap_Dot(5, 7, GMAP_WALL, 2);
	AddMap_Dot(6, 7, GMAP_WALL, 2);
	AddMap_Dot(6, 6, GMAP_WALL, 2);
	AddMap_Dot(7, 6, GMAP_WALL, 2);
	AddMap_Dot(8, 6, GMAP_WALL, 2);
	AddMap_Dot(9, 6, GMAP_WALL, 2);
	AddMap_Dot(10, 6, GMAP_WALL, 2);
	AddMap_Dot(11, 6, GMAP_WALL, 2);
	AddMap_Dot(12, 6, GMAP_WALL, 2);
	AddMap_Dot(12, 7, GMAP_WALL, 2);
	AddMap_Dot(12, 8, GMAP_WALL, 2);
	AddMap_Dot(12, 9, GMAP_WALL, 2);
	AddMap_Dot(12, 10, GMAP_WALL, 2);
	AddMap_Dot(11, 10, GMAP_WALL, 2);
	AddMap_Dot(10, 10, GMAP_WALL, 2);
	AddMap_Dot(10, 11, GMAP_WALL, 2);
	AddMap_Dot(9, 11, GMAP_WALL, 2);
	AddMap_Dot(8, 11, GMAP_WALL, 2);
	AddMap_Dot(8, 12, GMAP_WALL, 2);
	AddMap_Dot(8, 13, GMAP_WALL, 2);
	AddMap_Dot(8, 14, GMAP_WALL, 2);
	AddMap_Dot(8, 15, GMAP_WALL, 2);
	AddMap_Dot(7, 15, GMAP_WALL, 2);
	AddMap_Dot(6, 15, GMAP_WALL, 2);
	AddMap_Dot(5, 15, GMAP_WALL, 2);
	AddMap_Dot(4, 15, GMAP_WALL, 2);
	AddMap_Dot(4, 16, GMAP_WALL, 2);
	AddMap_Dot(4, 17, GMAP_WALL, 2);
	AddMap_Dot(4, 18, GMAP_WALL, 2);
	AddMap_Dot(4, 19, GMAP_WALL, 2);
	//첫번째
	AddMap_Dot(3, 13, GMAP_WALL, 2);
	AddMap_Dot(4, 13, GMAP_WALL, 2);
	AddMap_Dot(5, 13, GMAP_WALL, 2);
	AddMap_Dot(6, 13, GMAP_WALL, 2);
	AddMap_Dot(6, 12, GMAP_WALL, 2);
	AddMap_Dot(6, 11, GMAP_WALL, 2);
	AddMap_Dot(6, 10, GMAP_WALL, 2);
	AddMap_Dot(6, 9, GMAP_WALL, 2);
	AddMap_Dot(7, 9, GMAP_WALL, 2);
	AddMap_Dot(8, 9, GMAP_WALL, 2);
	AddMap_Dot(8, 8, GMAP_WALL, 2);
	AddMap_Dot(9, 8, GMAP_WALL, 2);
	AddMap_Dot(10, 8, GMAP_WALL, 2);
	//두번쨰

	AddMap_Dot(23, 6, GMAP_WALL, 2);
	AddMap_Dot(22, 6, GMAP_WALL, 2);
	AddMap_Dot(21, 6, GMAP_WALL, 2);
	AddMap_Dot(20, 6, GMAP_WALL, 2);
	AddMap_Dot(19, 6, GMAP_WALL, 2);
	AddMap_Dot(18, 6, GMAP_WALL, 2);
	AddMap_Dot(17, 6, GMAP_WALL, 2);
	AddMap_Dot(16, 6, GMAP_WALL, 2);
	AddMap_Dot(15, 6, GMAP_WALL, 2);
	AddMap_Dot(14, 6, GMAP_WALL, 2);
	AddMap_Dot(14, 7, GMAP_WALL, 2);
	AddMap_Dot(14, 8, GMAP_WALL, 2);
	AddMap_Dot(14, 9, GMAP_WALL, 2);
	AddMap_Dot(14, 10, GMAP_WALL, 2);
	AddMap_Dot(14, 11, GMAP_WALL, 2);
	AddMap_Dot(14, 12, GMAP_WALL, 2);
	AddMap_Dot(13, 12, GMAP_WALL, 2);
	AddMap_Dot(12, 12, GMAP_WALL, 2);
	AddMap_Dot(12, 13, GMAP_WALL, 2);
	AddMap_Dot(11, 13, GMAP_WALL, 2);
	AddMap_Dot(10, 13, GMAP_WALL, 2);
	AddMap_Dot(10, 14, GMAP_WALL, 2);
	AddMap_Dot(10, 15, GMAP_WALL, 2);
	AddMap_Dot(11, 15, GMAP_WALL, 2);
	AddMap_Dot(12, 15, GMAP_WALL, 2);
	AddMap_Dot(13, 15, GMAP_WALL, 2);
	AddMap_Dot(14, 15, GMAP_WALL, 2);
	AddMap_Dot(14, 14, GMAP_WALL, 2);
	//3
	AddMap_Dot(20, 8, GMAP_WALL, 2);
	AddMap_Dot(19, 8, GMAP_WALL, 2);
	AddMap_Dot(18, 8, GMAP_WALL, 2);
	AddMap_Dot(17, 8, GMAP_WALL, 2);
	AddMap_Dot(16, 8, GMAP_WALL, 2);
	AddMap_Dot(16, 9, GMAP_WALL, 2);
	AddMap_Dot(16, 10, GMAP_WALL, 2);
	AddMap_Dot(16, 11, GMAP_WALL, 2);
	AddMap_Dot(16, 12, GMAP_WALL, 2);
	AddMap_Dot(16, 13, GMAP_WALL, 2);
	AddMap_Dot(16, 14, GMAP_WALL, 2);
	AddMap_Dot(16, 15, GMAP_WALL, 2);
	AddMap_Dot(16, 16, GMAP_WALL, 2);
	AddMap_Dot(16, 17, GMAP_WALL, 2);
	AddMap_Dot(15, 17, GMAP_WALL, 2);
	AddMap_Dot(14, 17, GMAP_WALL, 2);
	AddMap_Dot(13, 17, GMAP_WALL, 2);
	AddMap_Dot(12, 17, GMAP_WALL, 2);
	AddMap_Dot(11, 17, GMAP_WALL, 2);
	AddMap_Dot(10, 17, GMAP_WALL, 2);
	AddMap_Dot(10, 18, GMAP_WALL, 2);
	AddMap_Dot(10, 19, GMAP_WALL, 2);
	AddMap_Dot(10, 20, GMAP_WALL, 2);
	AddMap_Dot(10, 21, GMAP_WALL, 2);
	AddMap_Dot(10, 22, GMAP_WALL, 2);
	AddMap_Dot(10, 23, GMAP_WALL, 2);
	AddMap_Dot(10, 24, GMAP_WALL, 2);
	AddMap_Dot(10, 24, GMAP_WALL, 2);
	AddMap_Dot(10, 24, GMAP_WALL, 2);
	AddMap_Dot(9, 24, GMAP_WALL, 2);
	AddMap_Dot(8, 24, GMAP_WALL, 2);
	AddMap_Dot(7, 24, GMAP_WALL, 2);
	AddMap_Dot(6, 23, GMAP_WALL, 2);
	AddMap_Dot(6, 24, GMAP_WALL, 2);
	AddMap_Dot(5, 23, GMAP_WALL, 2);
	AddMap_Dot(5, 24, GMAP_WALL, 2);
	AddMap_Dot(4, 23, GMAP_WALL, 2);
	AddMap_Dot(4, 24, GMAP_WALL, 2);
	AddMap_Dot(4, 24, GMAP_WALL, 2);
	AddMap_Dot(4, 24, GMAP_WALL, 2);
	AddMap_Pos(4/*X*/, 24, 4/*X*/, 34, GMAP_WALL, 2);//세로
	//4
	AddMap_Pos(3, 21/*Y*/, 6, 21/*Y*/, GMAP_WALL, 2);//가로
	AddMap_Pos(6/*X*/, 17, 6/*X*/, 21, GMAP_WALL, 2);//세로
	AddMap_Pos(6, 17/*Y*/, 8, 17/*Y*/, GMAP_WALL, 2);//가로
	AddMap_Pos(8/*X*/, 17, 8/*X*/, 22, GMAP_WALL, 2);//세로
	AddMap_Pos(3, 36/*Y*/, 29, 36/*Y*/, GMAP_WALL, 2);//가로
	//5
	AddMap_Pos(6/*X*/, 26, 6/*X*/, 34, GMAP_WALL, 2);//세로
	AddMap_Pos(6, 26/*Y*/, 12, 26/*Y*/, GMAP_WALL, 2);//가로
	AddMap_Pos(12/*X*/, 19, 12/*X*/, 26, GMAP_WALL, 2);//세로
	AddMap_Pos(12, 19/*Y*/, 16, 19/*Y*/, GMAP_WALL, 2);//가로
	AddMap_Pos(16/*X*/, 19, 16/*X*/, 22, GMAP_WALL, 2);//세로
	AddMap_Pos(16, 22/*Y*/, 20, 22/*Y*/, GMAP_WALL, 2);//가로
	AddMap_Pos(20/*X*/, 12, 20/*X*/, 24, GMAP_WALL, 2);//세로
	AddMap_Pos(20, 12/*Y*/, 24, 12/*Y*/, GMAP_WALL, 2);//가로
	AddMap_Pos(24/*X*/, 10, 24/*X*/, 15, GMAP_WALL, 2);//세로
	AddMap_Pos(24, 10/*Y*/, 27, 10/*Y*/, GMAP_WALL, 2);//가로
	AddMap_Pos(27/*X*/, 6, 27/*X*/, 10, GMAP_WALL, 2);//세로
	//6
	AddMap_Pos(18/*X*/, 10, 18/*X*/, 20, GMAP_WALL, 2);//세로
	AddMap_Pos(18, 10/*Y*/, 22, 10/*Y*/, GMAP_WALL, 2);//가로
	AddMap_Pos(22/*X*/, 8, 22/*X*/, 10, GMAP_WALL, 2);//세로
	AddMap_Pos(22, 8/*Y*/, 25, 8/*Y*/, GMAP_WALL, 2);//가로
	AddMap_Pos(25/*X*/, 5, 25/*X*/, 8, GMAP_WALL, 2);//세로
	//7
	AddMap_Pos(8/*X*/, 28, 8/*X*/, 35, GMAP_WALL, 2);//세로
	AddMap_Pos(8, 28/*Y*/, 14, 28/*Y*/, GMAP_WALL, 2);//가로
	AddMap_Pos(14/*X*/, 21, 14/*X*/, 28, GMAP_WALL, 2);//세로
	//8
	AddMap_Pos(10, 34/*Y*/, 14, 34/*Y*/, GMAP_WALL, 2);//가로
	AddMap_Pos(10/*X*/, 30, 10/*X*/, 34, GMAP_WALL, 2);//세로
	AddMap_Pos(10, 30/*Y*/, 16, 30/*Y*/, GMAP_WALL, 2);//가로
	AddMap_Pos(16/*X*/, 24, 16/*X*/, 30, GMAP_WALL, 2);//세로
	AddMap_Pos(16, 24/*Y*/, 18, 24/*Y*/, GMAP_WALL, 2);//가로
	//9
	AddMap_Pos(12, 32/*Y*/, 18, 32/*Y*/, GMAP_WALL, 2);//가로
	AddMap_Pos(16/*X*/, 32, 16/*X*/, 34, GMAP_WALL, 2);//세로
	AddMap_Pos(18/*X*/, 26, 18/*X*/, 32, GMAP_WALL, 2);//세로
	AddMap_Pos(18, 26/*Y*/, 20, 26/*Y*/, GMAP_WALL, 2);//가로
	AddMap_Pos(16, 34/*Y*/, 20, 34/*Y*/, GMAP_WALL, 2);//가로
	AddMap_Pos(20/*X*/, 28, 20/*X*/, 34, GMAP_WALL, 2);//세로
	//10
	AddMap_Pos(26/*X*/, 12, 26/*X*/, 15, GMAP_WALL, 2);//세로
	AddMap_Pos(26, 12/*Y*/, 28, 12/*Y*/, GMAP_WALL, 2);//가로
	//11
	AddMap_Pos(21, 19/*Y*/, 28, 20/*Y*/, GMAP_WALL, 2);
	AddMap_Pos(21, 28/*Y*/, 28, 29/*Y*/, GMAP_WALL, 2);
	//미로제작끝

	AddMap_Dot(30, 17, GMAP_TOGGLE_BUTTON_RED, 2);
	AddMap_Dot(30, 18, GMAP_WALL, 2);
	AddMap_Dot(30, 23, GMAP_FAKEBUTTON_BLUE, 2);
	AddMap_Dot(30, 24, GMAP_WALL, 2);
	AddMap_Dot(30, 29, GMAP_FAKEBUTTON_RED, 2);
	AddMap_Dot(30, 30, GMAP_WALL, 2);
	AddMap_Dot(34, 17, GMAP_FAKEBUTTON_BLUE, 2);
	AddMap_Dot(34, 18, GMAP_WALL, 2);
	AddMap_Dot(34, 23, GMAP_FAKEBUTTON_RED, 2);
	AddMap_Dot(34, 24, GMAP_WALL, 2);
	AddMap_Dot(34, 29, GMAP_FAKEBUTTON_BLUE, 2);
	AddMap_Dot(34, 30, GMAP_WALL, 2);
	AddMap_Dot(38, 17, GMAP_FAKEBUTTON_RED, 2);
	AddMap_Dot(38, 18, GMAP_WALL, 2);
	AddMap_Dot(38, 23, GMAP_TOGGLE_BUTTON_BLUE, 2);
	AddMap_Dot(38, 24, GMAP_WALL, 2);
	AddMap_Dot(38, 29, GMAP_FAKEBUTTON_RED, 2);
	AddMap_Dot(38, 30, GMAP_WALL, 2);
	AddMap_Dot(32, 21, GMAP_WALL, 2);
	AddMap_Dot(32, 27, GMAP_WALL, 2);
	AddMap_Dot(32, 33, GMAP_WALL, 2);
	AddMap_Dot(33, 31, GMAP_SHOOTER_UP, 2);

	AddMap_Dot(36, 21, GMAP_WALL, 2);
	AddMap_Dot(36, 27, GMAP_WALL, 2);
	AddMap_Dot(35, 31, GMAP_SHOOTER_UP, 2);
	AddMap_Dot(36, 33, GMAP_WALL, 2);
	AddMap_Pos(32, 11/*Y*/, 40, 12/*Y*/, GMAP_WALL, 2);
	AddMap_Pos(3, 36/*Y*/, 33, 36/*Y*/, GMAP_WALL, 2);//가로
	AddMap_Pos(3, 37/*Y*/, 35, 37/*Y*/, GMAP_WALL, 2);//가로
	AddMap_Pos(3, 38/*Y*/, 37, 38/*Y*/, GMAP_WALL, 2);//가로

	AddMap_Pos(30, 11/*Y*/, 31, 12/*Y*/, GMAP_LOCKWALL_MINT, 2);//가로
	AddMap_Pos(3, 38/*Y*/, 37, 38/*Y*/, GMAP_WALL, 2);//가로
	//토글 벽
	AddMap_Dot(9, 15, GMAP_LOCKWALL_BLUE, 2);
	AddMap_Dot(20, 7, GMAP_LOCKWALL_BLUE, 2);
	AddMap_Dot(27, 5, GMAP_LOCKWALL_BLUE, 2);
	AddMap_Dot(20, 11, GMAP_LOCKWALL_BLUE, 2);
	AddMap_Dot(20, 25, GMAP_LOCKWALL_BLUE, 2);
	AddMap_Dot(6, 35, GMAP_LOCKWALL_BLUE, 2);
	AddMap_Dot(20, 35, GMAP_LOCKWALL_BLUE, 2);
	AddMap_Dot(7, 22, GMAP_LOCKWALL_BLUE, 2);
	//안보이는벽
	AddMap_Dot(6, 5, GMAP_LOCKWALL_RED, 2);
	AddMap_Dot(14, 5, GMAP_LOCKWALL_RED, 2);
	AddMap_Dot(19, 6, GMAP_LOCKWALL_RED, 2);
	AddMap_Dot(3, 34, GMAP_LOCKWALL_RED, 2);
	AddMap_Dot(15, 23, GMAP_LOCKWALL_RED, 2);
	AddMap_Dot(17, 18, GMAP_LOCKWALL_RED, 2);
	AddMap_Dot(11, 35, GMAP_LOCKWALL_RED, 2);
	AddMap_Dot(25, 12, GMAP_LOCKWALL_RED, 2);
	//키
	AddMap_Dot(25, 18, GMAP_TOGGLE_BUTTON_GREEN, 2);
	AddMap_Dot(25, 27, GMAP_TOGGLE_BUTTON_PURPLE, 2);
	AddMap_Dot(21, 25, GMAP_KEY_MINT, 2);

	AddMap_Dot(25, 35, GMAP_FAKEBUTTON_GREEN, 2);
	//해결
	AddMap_Dot(31, 15, GMAP_LOCKWALL_HIDE_GREEN, 2);
	AddMap_Dot(30, 12, GMAP_LOCKWALL_HIDE_PURPLE, 2);

	AddMap_Dot(34, 10, GMAP_DOOR, 2);




	/*##################################################################################
	##################################   < 레벨 3 시작 >   ##############################
	##################################################################################*/
	//필수 - PC1, PC2와 가장자리 벽
	AddMap_Dot(37, 34, GMAP_PC1, 3);
	AddMap_Dot(37, 39, GMAP_PC2, 3);

	AddMap_Pos(0, 0, GARRAY_WIDTH_MAXINDEX, 0, GMAP_WALL, 3);
	AddMap_Pos(0, GARRAY_HEIGHT_MAXINDEX, GARRAY_WIDTH_MAXINDEX, GARRAY_HEIGHT_MAXINDEX, GMAP_WALL, 3);
	AddMap_Pos(0, 1, 0, GARRAY_HEIGHT_MAXINDEX, GMAP_WALL, 3);
	AddMap_Pos(GARRAY_WIDTH_MAXINDEX, 1, GARRAY_WIDTH_MAXINDEX, GARRAY_HEIGHT_MAXINDEX, GMAP_WALL, 3);



	AddMap_Pos(0, 31/*Y*/, 15, 31/*Y*/, GMAP_WALL, 3);//가로
	AddMap_Pos(25, 31/*Y*/, 40, 31/*Y*/, GMAP_WALL, 3);//가로
	AddMap_Pos(15/*X*/, 31, 15/*X*/, 39, GMAP_WALL, 3);//세로
	AddMap_Pos(25/*X*/, 31, 25/*X*/, 39, GMAP_WALL, 3);//세로
	//1층 벽
	AddMap_Pos(36/*X*/, 32, 36/*X*/, 40, GMAP_LOCKWALL_BLUE, 3);//세로
	AddMap_Pos(37, 36/*Y*/, 40, 36/*Y*/, GMAP_LOCKWALL_BLUE, 3);//가로
	AddMap_Pos(26/*X*/, 32, 26/*X*/, 39, GMAP_SHOOTER_RIGHT, 3);//세로
	AddMap_Dot(40, 32, GMAP_TOGGLE_BUTTON_BLUE, 3);
	AddMap_Dot(40, 40, GMAP_TOGGLE_BUTTON_BLUE, 3);
	AddMap_Dot(25, 40, GMAP_TOGGLE_BUTTON_BLUE, 3);
	//1층-오른쪽
	AddMap_Pos(13/*X*/, 33, 13/*X*/, 40, GMAP_WALL, 3);//세로
	AddMap_Pos(2, 33/*Y*/, 13, 33/*Y*/, GMAP_WALL, 3);//가로
	AddMap_Pos(2/*X*/, 33, 2/*X*/, 39, GMAP_WALL, 3);//세로
	AddMap_Pos(2, 39/*Y*/, 11, 39/*Y*/, GMAP_WALL, 3);//가로
	AddMap_Pos(11/*X*/, 35, 11/*X*/, 39, GMAP_WALL, 3);//세로
	AddMap_Pos(4, 35/*Y*/, 11, 35/*Y*/, GMAP_WALL, 3);//가로
	AddMap_Pos(4/*X*/, 35, 4/*X*/, 37, GMAP_WALL, 3);//세로
	AddMap_Pos(4, 37/*Y*/, 9, 37/*Y*/, GMAP_WALL, 3);//가로
	AddMap_Dot(14, 39, GMAP_KEY_RED, 3);
	AddMap_Dot(14, 36, GMAP_KEY_RED, 3);
	AddMap_Dot(14, 33, GMAP_KEY_RED, 3);
	AddMap_Dot(12, 32, GMAP_KEY_RED, 3);
	AddMap_Dot(9, 32, GMAP_KEY_RED, 3);
	AddMap_Dot(6, 32, GMAP_KEY_RED, 3);
	AddMap_Dot(3, 32, GMAP_KEY_RED, 3);
	AddMap_Dot(1, 33, GMAP_KEY_RED, 3);
	AddMap_Dot(1, 36, GMAP_KEY_RED, 3);
	AddMap_Dot(1, 39, GMAP_KEY_RED, 3);
	AddMap_Dot(3, 40, GMAP_KEY_RED, 3);
	AddMap_Dot(6, 40, GMAP_KEY_RED, 3);
	AddMap_Dot(9, 40, GMAP_KEY_RED, 3);
	AddMap_Dot(12, 40, GMAP_KEY_RED, 3);
	AddMap_Dot(12, 37, GMAP_KEY_RED, 3);
	AddMap_Dot(12, 34, GMAP_KEY_RED, 3);
	AddMap_Dot(12, 40, GMAP_KEY_RED, 3);
	AddMap_Dot(12, 37, GMAP_KEY_RED, 3);
	AddMap_Dot(12, 34, GMAP_KEY_RED, 3);
	AddMap_Dot(9, 34, GMAP_KEY_RED, 3);
	AddMap_Dot(6, 34, GMAP_KEY_RED, 3);
	AddMap_Dot(3, 37, GMAP_KEY_RED, 3);
	AddMap_Dot(3, 34, GMAP_KEY_RED, 3);
	AddMap_Dot(5, 38, GMAP_KEY_RED, 3);
	AddMap_Dot(8, 38, GMAP_KEY_RED, 3);
	AddMap_Dot(10, 37, GMAP_KEY_RED, 3);
	AddMap_Dot(8, 36, GMAP_KEY_RED, 3);
	AddMap_Dot(5, 36, GMAP_KEY_RED, 3);
	AddMap_Dot(15, 40, GMAP_LOCKWALL_GREEN, 3);
	AddMap_Dot(14, 40, GMAP_LOCKWALL_YELLOW, 3);

	//1층-왼쪽






	AddMap_Pos(0, 20/*Y*/, 15, 20/*Y*/, GMAP_WALL, 3);//가로
	AddMap_Pos(25, 20/*Y*/, 40, 20/*Y*/, GMAP_WALL, 3);//가로
	AddMap_Pos(15/*X*/, 20, 15/*X*/, 29, GMAP_WALL, 3);//세로
	AddMap_Pos(25/*X*/, 20, 25/*X*/, 29, GMAP_WALL, 3);//세로
	//2층
	AddMap_Dot(26, 29, GMAP_FAKEBUTTON_GREEN, 3);
	AddMap_Dot(28, 29, GMAP_FAKEBUTTON_GREEN, 3);
	AddMap_Dot(30, 29, GMAP_FAKEBUTTON_GREEN, 3);
	AddMap_Dot(32, 29, GMAP_FAKEBUTTON_GREEN, 3);
	AddMap_Dot(34, 29, GMAP_FAKEBUTTON_GREEN, 3);
	AddMap_Dot(36, 29, GMAP_FAKEBUTTON_GREEN, 3);
	AddMap_Dot(38, 29, GMAP_FAKEBUTTON_GREEN, 3);
	AddMap_Dot(40, 29, GMAP_FAKEBUTTON_GREEN, 3);
	AddMap_Dot(26, 27, GMAP_FAKEBUTTON_GREEN, 3);
	AddMap_Dot(28, 27, GMAP_FAKEBUTTON_GREEN, 3);
	AddMap_Dot(30, 27, GMAP_FAKEBUTTON_GREEN, 3);
	AddMap_Dot(32, 27, GMAP_FAKEBUTTON_GREEN, 3);
	AddMap_Dot(34, 27, GMAP_FAKEBUTTON_GREEN, 3);
	AddMap_Dot(36, 27, GMAP_FAKEBUTTON_GREEN, 3);
	AddMap_Dot(38, 27, GMAP_FAKEBUTTON_GREEN, 3);
	AddMap_Dot(40, 27, GMAP_FAKEBUTTON_GREEN, 3);
	AddMap_Dot(26, 25, GMAP_FAKEBUTTON_GREEN, 3);
	AddMap_Dot(28, 25, GMAP_FAKEBUTTON_GREEN, 3);
	AddMap_Dot(30, 25, GMAP_FAKEBUTTON_GREEN, 3);
	AddMap_Dot(32, 25, GMAP_FAKEBUTTON_GREEN, 3);
	AddMap_Dot(34, 25, GMAP_FAKEBUTTON_GREEN, 3);
	AddMap_Dot(36, 25, GMAP_FAKEBUTTON_GREEN, 3);
	AddMap_Dot(38, 25, GMAP_FAKEBUTTON_GREEN, 3);
	AddMap_Dot(40, 25, GMAP_FAKEBUTTON_GREEN, 3);
	AddMap_Dot(26, 23, GMAP_FAKEBUTTON_GREEN, 3);
	AddMap_Dot(28, 23, GMAP_FAKEBUTTON_GREEN, 3);
	AddMap_Dot(30, 23, GMAP_FAKEBUTTON_GREEN, 3);
	AddMap_Dot(32, 23, GMAP_FAKEBUTTON_GREEN, 3);
	AddMap_Dot(34, 23, GMAP_FAKEBUTTON_GREEN, 3);
	AddMap_Dot(36, 23, GMAP_TOGGLE_BUTTON_GREEN, 3);
	AddMap_Dot(38, 23, GMAP_FAKEBUTTON_GREEN, 3);
	AddMap_Dot(40, 23, GMAP_FAKEBUTTON_GREEN, 3);
	AddMap_Dot(26, 21, GMAP_WALL, 3);
	AddMap_Dot(28, 21, GMAP_WALL, 3);
	AddMap_Dot(30, 21, GMAP_WALL, 3);
	AddMap_Dot(32, 21, GMAP_WALL, 3);
	AddMap_Dot(34, 21, GMAP_WALL, 3);
	AddMap_Dot(36, 21, GMAP_WALL, 3);
	AddMap_Dot(38, 21, GMAP_WALL, 3);
	AddMap_Dot(40, 21, GMAP_WALL, 3);
	AddMap_Dot(27, 22, GMAP_SHOOTER_DOWN, 3);
	AddMap_Dot(29, 20, GMAP_SHOOTER_DOWN, 3);
	AddMap_Dot(31, 22, GMAP_SHOOTER_DOWN, 3);
	AddMap_Dot(33, 20, GMAP_SHOOTER_DOWN, 3);
	AddMap_Dot(35, 22, GMAP_SHOOTER_DOWN, 3);
	AddMap_Dot(37, 20, GMAP_SHOOTER_DOWN, 3);
	AddMap_Dot(39, 22, GMAP_SHOOTER_DOWN, 3);
	AddMap_Dot(26, 28, GMAP_SHOOTER_RIGHT, 3);
	AddMap_Dot(26, 24, GMAP_SHOOTER_RIGHT, 3);
	AddMap_Dot(26, 26, GMAP_SHOOTER_RIGHT, 3);

	//2층 오른쪽
	AddMap_Dot(1, 21, GMAP_WALL, 3);
	//AddMap_Dot(1, 23, GMAP_BOMB, 3);
	AddMap_Dot(1, 25, GMAP_BOMB, 3);
	AddMap_Dot(1, 27, GMAP_BOMB, 3);
	AddMap_Dot(1, 29, GMAP_BOMB, 3);
	AddMap_Dot(3, 21, GMAP_WALL, 3);
	AddMap_Dot(3, 23, GMAP_BOMB, 3);
	AddMap_Dot(3, 25, GMAP_BOMB, 3);
	AddMap_Dot(3, 27, GMAP_BOMB, 3);
	AddMap_Dot(3, 29, GMAP_BOMB, 3);
	AddMap_Dot(5, 21, GMAP_WALL, 3);
	AddMap_Dot(5, 23, GMAP_BOMB, 3);
	AddMap_Dot(5, 25, GMAP_BOMB, 3);//
	AddMap_Dot(5, 27, GMAP_BOMB, 3);
	AddMap_Dot(5, 29, GMAP_BOMB, 3);
	AddMap_Dot(7, 21, GMAP_WALL, 3);
	AddMap_Dot(7, 23, GMAP_BOMB, 3);
	AddMap_Dot(7, 25, GMAP_BOMB, 3);
	AddMap_Dot(7, 27, GMAP_BOMB, 3);
	AddMap_Dot(7, 29, GMAP_BOMB, 3);
	AddMap_Dot(9, 21, GMAP_WALL, 3);
	AddMap_Dot(9, 23, GMAP_BOMB, 3);
	AddMap_Dot(9, 25, GMAP_BOMB, 3);
	AddMap_Dot(9, 27, GMAP_BOMB, 3);//
	AddMap_Dot(9, 29, GMAP_BOMB, 3);
	AddMap_Dot(11, 21, GMAP_WALL, 3);
	AddMap_Dot(11, 23, GMAP_BOMB, 3);
	AddMap_Dot(11, 25, GMAP_BOMB, 3);
	AddMap_Dot(11, 27, GMAP_BOMB, 3);
	AddMap_Dot(11, 29, GMAP_BOMB, 3);
	AddMap_Dot(13, 21, GMAP_WALL, 3);
	AddMap_Dot(13, 23, GMAP_BOMB, 3);
	AddMap_Dot(13, 25, GMAP_BOMB, 3);
	AddMap_Dot(13, 27, GMAP_BOMB, 3);
	AddMap_Dot(13, 29, GMAP_BOMB, 3);
	AddMap_Dot(14, 21, GMAP_WALL, 3);
	AddMap_Dot(14, 22, GMAP_WALL, 3);
	AddMap_Dot(14, 23, GMAP_WALL, 3);
	AddMap_Dot(14, 25, GMAP_WALL, 3);
	AddMap_Dot(14, 26, GMAP_WALL, 3);
	AddMap_Dot(14, 27, GMAP_WALL, 3);
	AddMap_Dot(14, 25, GMAP_WALL, 3);
	AddMap_Dot(14, 28, GMAP_WALL, 3);
	AddMap_Dot(14, 26, GMAP_WALL, 3);
	AddMap_Dot(14, 24, GMAP_WALL, 3);

	AddMap_Dot(2, 20, GMAP_SHOOTER_DOWN, 3);
	AddMap_Dot(4, 22, GMAP_SHOOTER_DOWN, 3);
	AddMap_Dot(6, 20, GMAP_SHOOTER_DOWN, 3);
	AddMap_Dot(8, 22, GMAP_SHOOTER_DOWN, 3);
	AddMap_Dot(10, 20, GMAP_SHOOTER_DOWN, 3);
	AddMap_Dot(12, 22, GMAP_SHOOTER_DOWN, 3);


	AddMap_Dot(13, 24, GMAP_SHOOTER_LEFT, 3);
	AddMap_Dot(13, 26, GMAP_SHOOTER_LEFT, 3);
	AddMap_Dot(13, 28, GMAP_SHOOTER_LEFT, 3);
	AddMap_Dot(1, 22, GMAP_KEY_YELLOW, 3);

	//2층 왼쪽



	AddMap_Pos(10/*X*/, 16, 30/*X*/, 16, GMAP_WALL, 3);//보스땅
	AddMap_Pos(9/*X*/, 17, 31/*X*/, 17, GMAP_WALL, 3);//보스땅
	AddMap_Pos(6/*X*/, 2, 9/*X*/, 3, GMAP_WALL, 3);//보스땅
	AddMap_Pos(31/*X*/, 2, 34/*X*/, 3, GMAP_WALL, 3);//보스땅

	AddMap_Pos(6/*X*/, 13, 7/*X*/, 14, GMAP_HIDDENWALL, 3);//보스땅
	AddMap_Pos(33/*X*/, 13, 34/*X*/, 14, GMAP_HIDDENWALL, 3);//보스땅

	AddMap_Pos(3/*X*/, 10, 4/*X*/, 11, GMAP_HIDDENWALL, 3);//보스땅
	AddMap_Pos(36/*X*/, 10, 37/*X*/, 11, GMAP_HIDDENWALL, 3);//보스땅

	AddMap_Pos(1/*X*/, 7, 2/*X*/, 8, GMAP_LOCKWALL_HIDE_GREEN, 3);//보스땅
	AddMap_Pos(39/*X*/, 7, 40/*X*/, 8, GMAP_LOCKWALL_HIDE_GREEN, 3);//보스땅

	AddMap_Pos(3/*X*/, 4, 4/*X*/, 5, GMAP_HIDDENWALL, 3);//보스땅
	AddMap_Pos(37/*X*/, 4, 38/*X*/, 5, GMAP_HIDDENWALL, 3);//보스땅


	//보스

	AddMap_Pos(18, 1/*Y*/, 22, 1/*Y*/, GMAP_LOCKWALL_HIDE_BLUE, 3);//가로
	AddMap_Pos(18, 5/*Y*/, 22, 5/*Y*/, GMAP_LOCKWALL_HIDE_BLUE, 3);//가로
	AddMap_Pos(19, 6/*Y*/, 21, 6/*Y*/, GMAP_LOCKWALL_HIDE_BLUE, 3);//가로
	AddMap_Pos(20, 7/*Y*/, 20, 7/*Y*/, GMAP_LOCKWALL_HIDE_BLUE, 3);//가로
	AddMap_Pos(18/*X*/, 1, 18/*X*/, 5, GMAP_LOCKWALL_HIDE_BLUE, 3);//세로
	AddMap_Pos(22/*X*/, 1, 22/*X*/, 5, GMAP_LOCKWALL_HIDE_BLUE, 3);//세로
	AddMap_Dot(19, 3, GMAP_LOCKWALL_HIDE_BLUE, 3);
	AddMap_Dot(21, 3, GMAP_LOCKWALL_HIDE_BLUE, 3);
	//머리
	AddMap_Pos(13, 3/*Y*/, 16, 3/*Y*/, GMAP_LOCKWALL_GREEN, 3);//가로
	AddMap_Pos(24, 3/*Y*/, 27, 3/*Y*/, GMAP_LOCKWALL_GREEN, 3);//가로
	AddMap_Pos(11, 4/*Y*/, 12, 4/*Y*/, GMAP_LOCKWALL_GREEN, 3);//가로
	AddMap_Pos(28, 4/*Y*/, 29, 4/*Y*/, GMAP_LOCKWALL_GREEN, 3);//가로
	AddMap_Pos(14, 5/*Y*/, 16, 5/*Y*/, GMAP_LOCKWALL_GREEN, 3);//가로
	AddMap_Pos(24, 5/*Y*/, 26, 5/*Y*/, GMAP_LOCKWALL_GREEN, 3);//가로
	AddMap_Pos(13, 6/*Y*/, 14, 6/*Y*/, GMAP_LOCKWALL_GREEN, 3);//가로
	AddMap_Pos(26, 6/*Y*/, 27, 6/*Y*/, GMAP_LOCKWALL_GREEN, 3);//가로
	AddMap_Pos(11/*X*/, 4, 11/*X*/, 9, GMAP_LOCKWALL_GREEN, 3);//세로
	AddMap_Pos(10/*X*/, 4, 10/*X*/, 9, GMAP_SHOOTER_LEFT, 3);//세로
	AddMap_Pos(29/*X*/, 4, 29/*X*/, 9, GMAP_LOCKWALL_GREEN, 3);//세로
	AddMap_Pos(30/*X*/, 4, 30/*X*/, 9, GMAP_SHOOTER_RIGHT, 3);//세로
	AddMap_Pos(13/*X*/, 6, 13/*X*/, 10, GMAP_LOCKWALL_GREEN, 3);//세로
	AddMap_Pos(27/*X*/, 6, 27/*X*/, 10, GMAP_LOCKWALL_GREEN, 3);//세로
	AddMap_Pos(12, 10/*Y*/, 13, 10/*Y*/, GMAP_LOCKWALL_GREEN, 3);//가로
	AddMap_Pos(27, 10/*Y*/, 28, 10/*Y*/, GMAP_LOCKWALL_GREEN, 3);//가로
	//팔
	AddMap_Dot(17, 5, GMAP_LOCKWALL_YELLOW, 3);
	AddMap_Dot(23, 5, GMAP_LOCKWALL_YELLOW, 3);
	AddMap_Pos(16, 6/*Y*/, 18, 6/*Y*/, GMAP_LOCKWALL_YELLOW, 3);//가로
	AddMap_Pos(22, 6/*Y*/, 24, 6/*Y*/, GMAP_LOCKWALL_YELLOW, 3);//가로
	AddMap_Pos(17, 7/*Y*/, 19, 7/*Y*/, GMAP_LOCKWALL_YELLOW, 3);//가로
	AddMap_Pos(21, 7/*Y*/, 23, 7/*Y*/, GMAP_LOCKWALL_YELLOW, 3);//가로
	AddMap_Pos(17, 8/*Y*/, 23, 8/*Y*/, GMAP_LOCKWALL_YELLOW, 3);//가로
	AddMap_Pos(18, 9/*Y*/, 19, 9/*Y*/, GMAP_LOCKWALL_YELLOW, 3);//가로
	AddMap_Pos(21, 9/*Y*/, 22, 9/*Y*/, GMAP_LOCKWALL_YELLOW, 3);//가로
	AddMap_Pos(19, 10/*Y*/, 21, 10/*Y*/, GMAP_LOCKWALL_YELLOW, 3);//가로
	AddMap_Dot(20, 11, GMAP_LOCKWALL_YELLOW, 3);
	AddMap_Pos(13, 4/*Y*/, 15, 4/*Y*/, GMAP_WALL, 3);//가로
	AddMap_Pos(12, 5/*Y*/, 13, 5/*Y*/, GMAP_WALL, 3);//가로
	AddMap_Pos(25, 4/*Y*/, 27, 4/*Y*/, GMAP_WALL, 3);//가로
	AddMap_Pos(27, 5/*Y*/, 28, 5/*Y*/, GMAP_WALL, 3);//가로

	//몸통
	AddMap_Pos(15/*X*/, 9, 15/*X*/, 15, GMAP_LOCKWALL_RED, 3);//세로
	AddMap_Pos(25/*X*/, 9, 25/*X*/, 15, GMAP_LOCKWALL_RED, 3);//세로
	AddMap_Pos(19/*X*/, 11, 19/*X*/, 15, GMAP_LOCKWALL_RED, 3);//세로
	AddMap_Pos(21/*X*/, 11, 21/*X*/, 15, GMAP_LOCKWALL_RED, 3);//세로
	AddMap_Pos(16, 9/*Y*/, 17, 9/*Y*/, GMAP_LOCKWALL_RED, 3);//가로
	AddMap_Pos(23, 9/*Y*/, 25, 9/*Y*/, GMAP_LOCKWALL_RED, 3);//가로
	AddMap_Pos(15, 15/*Y*/, 19, 15/*Y*/, GMAP_LOCKWALL_RED, 3);//가로
	AddMap_Pos(22, 15/*Y*/, 25, 15/*Y*/, GMAP_LOCKWALL_RED, 3);//가로
	AddMap_Dot(18, 10, GMAP_LOCKWALL_RED, 3);
	AddMap_Dot(22, 10, GMAP_LOCKWALL_RED, 3);
	//키
	AddMap_Dot(16, 4, GMAP_KEY_GREEN, 3);
	AddMap_Dot(24, 4, GMAP_KEY_GREEN, 3);
	AddMap_Dot(28, 9, GMAP_KEY_YELLOW, 3);//-노랑
	AddMap_Dot(20, 9, GMAP_KEY_BLUE, 3);//심장
	//라이프
	AddMap_Dot(17, 4, GMAP_LIFEUP, 3);
	AddMap_Dot(23, 4, GMAP_LIFEUP, 3);

	//추가함정
	AddMap_Dot(11, 10, GMAP_SHOOTER_DOWN, 3);//손
	AddMap_Dot(12, 11, GMAP_SHOOTER_DOWN, 3);//손
	AddMap_Dot(13, 11, GMAP_SHOOTER_DOWN, 3);//손
	AddMap_Dot(29, 10, GMAP_SHOOTER_DOWN, 3);//손
	AddMap_Dot(28, 11, GMAP_SHOOTER_DOWN, 3);//손
	AddMap_Dot(27, 11, GMAP_SHOOTER_DOWN, 3);//손
	AddMap_Dot(14, 7, GMAP_SHOOTER_DOWN, 3);//손
	AddMap_Dot(15, 6, GMAP_SHOOTER_DOWN, 3);//손
	AddMap_Dot(16, 7, GMAP_SHOOTER_DOWN, 3);//손
	AddMap_Dot(24, 7, GMAP_SHOOTER_DOWN, 3);//손
	AddMap_Dot(25, 6, GMAP_SHOOTER_DOWN, 3);//손
	AddMap_Dot(26, 7, GMAP_SHOOTER_DOWN, 3);//손
	AddMap_Dot(16, 8, GMAP_SPIKE_LEFT, 3);//손
	AddMap_Dot(24, 8, GMAP_SPIKE_RIGHT, 3);//손
	//다리
	AddMap_Dot(16, 13, GMAP_HIDDENWALL, 3);//
	AddMap_Dot(16, 11, GMAP_HIDDENWALL, 3);//
	AddMap_Dot(24, 13, GMAP_HIDDENWALL, 3);//
	AddMap_Dot(24, 11, GMAP_HIDDENWALL, 3);//

	//벽추가

	AddMap_Pos(16, 20/*Y*/, 24, 20/*Y*/, GMAP_LOCKWALL_MINT, 3);//가로
	AddMap_Dot(24, 23, GMAP_TOGGLE_BUTTON_MINT, 3);//
	AddMap_Dot(12, 9, GMAP_KEY_MINT, 3);//





}





void LevelDesignToolLoop(void)
{
	int i, j;
	char str[100] = "현재 레벨 : Level ";
	int len = strlen(str);
	int key;
	int drawFlag = 0;


	if (_kbhit() != 0)
	{
		key = _getch();
		switch (key)
		{
		case 'q':
			gState = GSTATE_DESIGNTOOL_OFF;
			gLocation = GLOCATION_STATE;
			break;
		case 'p':
			gState = GSTATE_RETRY;
			gLocation = GLOCATION_STATE;
			ClearUI();
			coin = SYSTEM_MAX_COIN;//도전기회 초기화
			ClearTime = 0;//클리어 타임 초기화
			DeathCount = 0;//데스카운트 초기화
			//pc의 목숨 초기화
			P1_Life = SYSTEM_START_LIFE;
			P2_Life = SYSTEM_START_LIFE;
			break;
		case LEFT:
			drawFlag = 1;
			currentLevelIndex--;
			if (currentLevelIndex < 0)
				currentLevelIndex = SYSTEM_MAX_LEVEL - 1;
			break;
		case RIGHT:
			drawFlag = 1;
			currentLevelIndex++;
			if (currentLevelIndex >= SYSTEM_MAX_LEVEL)
				currentLevelIndex = 0;
			break;
		case SPACE:
			drawFlag = 1;
			currentLevelIndex = 0;
			break;
		default:
			break;
		}
	}

	if (drawFlag)
	{
		SetColor(UI_COLOR, UI_BACKCOLOR);
		DrawString_Dot_Int(GBOARD_RIGHT_POSITION_X + len + 9, GBOARD_TOP_POSITION_Y, currentLevelIndex + 1);
		for (i = 0; i <= GARRAY_HEIGHT_MAXINDEX; i++)
		{
			for (j = 0; j <= GARRAY_WIDTH_MAXINDEX; j++)
			{
				UpdateGameBoard(j, i, map[currentLevelIndex][i][j]);
			}
		}
	}
}

void BuildLevelDesignTool(void)
{
	int i, j;
	char str[100] = "현재 레벨 : Level ";
	int len = strlen(str);

	ClearUI();
	SetColor(UI_COLOR, UI_BACKCOLOR);
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, GBOARD_TOP_POSITION_Y, str);
	DrawString_Dot_Int(GBOARD_RIGHT_POSITION_X + len + 9, GBOARD_TOP_POSITION_Y, currentLevelIndex + 1);
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, GBOARD_TOP_POSITION_Y + 1, "<디자인툴 전용 커맨드>");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, GBOARD_TOP_POSITION_Y + 2, "Space : 처음 레벨");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, GBOARD_TOP_POSITION_Y + 3, "→ : 다음 레벨");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, GBOARD_TOP_POSITION_Y + 4, "← : 이전 레벨");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, GBOARD_TOP_POSITION_Y + 5, "Q : 로비로 돌아가기");
	DrawString_Dot(GBOARD_RIGHT_POSITION_X + 8, GBOARD_TOP_POSITION_Y + 6, "P : 현재 레벨에서 플레이 시작");

	for (i = 0; i <= GARRAY_HEIGHT_MAXINDEX; i++)
	{
		for (j = 0; j <= GARRAY_WIDTH_MAXINDEX; j++)
		{
			UpdateGameBoard(j, i, map[currentLevelIndex][i][j]);
		}
	}
}