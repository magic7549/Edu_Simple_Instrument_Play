#pragma once
#include<Windows.h>	//BYTE ���� ����ϱ� ����
#include<iostream>
#include<conio.h>
#include<string>
using namespace std;

class View {
	string instrumentText[128];
public:
	View();
	void ConsoleSetting();	//�ܼ� â ����
	void Home();	//ù ȭ��
	void Free_Play();	//���� ����
	void Record_Select();	//���� ���� �޴�
	void Record();	//���� ȭ��
	bool Reset();	//���� ȭ��
	void FileRelation();	//���� ����
	void ShowDoReMi(BYTE key);	//���� �ؽ�Ʈ�� ���
	void RenderImage(int x, int y);		//�̹��� ���
	void Gotoxy(int x, int y);	//Ŀ�� �̵�
	void NowCursorPosition(int& x, int& y);	//���� Ŀ�� ��ġ
	void RemoveScrollbar();		//��ũ�ѹ� ����
	void ViewInstrument(int instrument);	//���� �Ǳ� ���� ǥ��
};