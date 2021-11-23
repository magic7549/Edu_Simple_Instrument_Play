#pragma once
#include<Windows.h>	//BYTE 형식 사용하기 위함
#include<iostream>
#include<conio.h>
#include<string>
using namespace std;

class View {
	string instrumentText[128];
	int x, y;	//커서 좌표
public:
	View();
	void ConsoleSetting();	//콘솔 창 설정
	void RemoveScrollbar();		//스크롤바 제거
	void Piano();	//피아노 그림
	void DisplayInput(int key, bool isPush);	//피아노 그림에 현재 눌린 키 표시
	void ShowDoReMi(BYTE key);	//음계 텍스트로 출력
	void Home();	//첫 화면
	void Record_Select();	//녹음 선택 메뉴
	void Record();	//녹음 화면
	bool Reset();	//리셋 화면
	void FileRelation();	//파일 관련
	void Gotoxy(int x, int y);	//커서 이동
	void NowCursorPosition(int& x, int& y);	//현재 커서 위치
	void ViewInstrument(int instrument);	//현재 악기 종류 표시
	void ViewMetronomeBPM(int bpm);	//메트로놈 BPM 표시
};