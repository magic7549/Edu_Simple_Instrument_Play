#pragma once
#include<Windows.h>	//BYTE ���� ����ϱ� ����
#include<iostream>
#include<conio.h>
#include<string>
using namespace std;

class View {
	string instrumentText[128];
	int x, y;	//Ŀ�� ��ǥ
public:
	View();
	void ConsoleSetting();	//�ܼ� â ����
	void RemoveScrollbar();		//��ũ�ѹ� ����
	void Piano();	//�ǾƳ� �׸�
	void DisplayInput(int key, bool isPush);	//�ǾƳ� �׸��� ���� ���� Ű ǥ��
	void ShowDoReMi(BYTE key);	//���� �ؽ�Ʈ�� ���
	void Home();	//ù ȭ��
	void Record_Select();	//���� ���� �޴�
	void Record();	//���� ȭ��
	bool Reset();	//���� ȭ��
	void FileRelation();	//���� ����
	void Gotoxy(int x, int y);	//Ŀ�� �̵�
	void NowCursorPosition(int& x, int& y);	//���� Ŀ�� ��ġ
	void ViewInstrument(int instrument);	//���� �Ǳ� ���� ǥ��
	void ViewMetronomeBPM(int bpm);	//��Ʈ�γ� BPM ǥ��
};