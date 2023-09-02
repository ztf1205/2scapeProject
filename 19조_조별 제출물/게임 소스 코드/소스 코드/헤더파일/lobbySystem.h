#pragma once

//화면에 깜빡이는 화살표 출력
void chat_Icon(int y);

//프롤로그 연출
void Prologue_Guide(void);

//log 대사 출력
void alert_log(void);

//로비 반복문
void LobbyLoop(int developMode);

//게임 타이틀 빨강 혹은 파랑으로 그리기 및 press문구 깜빡이기
void BuildTitle(int isRed);

//로비 진입시 로비를 화면에 그림
void BuildLobby(void);