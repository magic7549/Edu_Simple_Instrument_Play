#include<iostream>
#include<conio.h>
#include<thread>

#include "view.h"
#include "midi.h"
#include "record.h"
#include "fileInOut.h"
using namespace std;

int main() {
	View view;
	MidiClass midi;
	RecordNoteClass record;
	FileInOut fileSystem;

	midi.MidiAllo(midi.hDevice);

	view.RemoveScrollbar();

	int choice;
	while (true)
	{
		view.Home();
		cin >> choice;

		switch (choice)
		{
		case 1:	//���� ����
			view.Free_Play();
			midi.PlayMidi();
			break;
		case 2:	//���� ����
			do {
				view.Record_Select();
				cin >> choice;
				switch (choice)
				{
				case 1:	//����
					view.Record();
					record.RecordNote(midi);
					break;
				case 2:	//���
					record.ReplayNote(midi);
					break;
				case 3:	//������ �ʱ�ȭ
					if (view.Reset()) {
						record.ResetVector();
						record.ResetInputTotalNum();
						system("cls");
						cout << "�����͸� �ʱ�ȭ�Ͽ����ϴ�." << endl;
						Sleep(1000);
					}
					break;
				default:
					break;
				}
			} while (choice != 4);
			break;
		case 3: {
			string fileName;
			do {
				view.FileRelation();
				cin >> choice;
				switch (choice)
				{
				case 1:	//������ ����
					system("cls");
					cout << "������ ���� �̸� : ";
					cin.ignore();
					getline(cin, fileName);
					fileSystem.WriteFile(record, fileName);
					break;
				case 2:	//������ �ҷ�����
					system("cls");
					cout << "�ҷ��� ���� �̸� : ";
					cin.ignore();
					getline(cin, fileName);
					fileSystem.ReadFile(record, fileName);
					break;
				default:
					break;
				}
			} while (choice != 3);
			break;
		}
		case 4:
			return 0;
		default:
			break;
		}
	}

	//midiOut �ʱ�ȭ �� ����
	midiOutReset(midi.hDevice);
	midiOutClose(midi.hDevice);
	
	return 0;
}