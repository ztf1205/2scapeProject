#pragma once

/*레벨디자이너가 이용하는 함수 AddMap_~ 3가지
type은 바꿔주고 싶은 아이템이나 블럭을 의미함 ex : GMAP_WALL
level은 바꾸고 싶은 레벨(1~3)
size와 pos는 사각형 영역을 바꿔주고 dot은 한점만 바꿔줌*/

//좌측 상단의 좌표와 너비와 높이를 이용해서 사각형 영역의 맵을 채운다
void AddMap_Size(int leftTop_X, int leftTop_Y, int width, int height, int type, int level);
//좌측 상단의 좌표와 우측 하단의 좌표를 이용해서 사각형 영역의 맵을 채운다
void AddMap_Pos(int leftTop_X, int leftTop_Y, int rightDown_X, int rightDown_Y, int type, int level);
//한 점의 맵을 채운다
void AddMap_Dot(int x, int y, int type, int level);


//AddMap_~을 호출하여 레벨을 제작한다
void BuildMap(void);


//레벨디자인 툴 루프
void LevelDesignToolLoop(void);

//레벨디자인 툴 빌드
void BuildLevelDesignTool(void);