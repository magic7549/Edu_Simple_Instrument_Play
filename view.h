#pragma once
#include<Windows.h>	//BYTE 형식 사용하기 위함
#include<iostream>
#include<conio.h>
#include<string>
using namespace std;

class View {
	string instrumentText[128];
public:
	View();
	void ConsoleSetting();	//콘솔 창 설정
	void Home();	//첫 화면
	void Free_Play();	//자유 연주
	void Record_Select();	//녹음 선택 메뉴
	void Record();	//녹음 화면
	bool Reset();	//리셋 화면
	void FileRelation();	//파일 관련
	void ShowDoReMi(BYTE key);	//음계 텍스트로 출력
	void RenderImage(int x, int y);		//이미지 출력
	void Gotoxy(int x, int y);	//커서 이동
	void NowCursorPosition(int& x, int& y);	//현재 커서 위치
	void RemoveScrollbar();		//스크롤바 제거
	void ViewInstrument(int instrument);	//현재 악기 종류 표시
};