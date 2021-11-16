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
	RecordNoteClass record[2];
	FileInOut fileSystem;

	midi.MidiAllo(midi.hDevice);

	view.RemoveScrollbar();
	view.ConsoleSetting();

	DWORD prevMode = 0;
	HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(handle, &prevMode);
	SetConsoleMode(handle, prevMode & ~ENABLE_QUICK_EDIT_MODE | ENABLE_MOUSE_INPUT);

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
					do {
						system("cls");
						cout << "������ Ʈ���� �������ּ���(1 ~ 2) : ";
						cin >> choice;

						if (choice <= 0 || choice > 2) {
							cout << "1 ~ 2�� Ʈ���� �������ּ���";
							Sleep(1000);
						}
					} while (choice <= 0 || choice > 2);
					do {
						cout << "�Ǳ⸦ �������ּ���(1 ~ 128) : ";
						cin >> midi.instrument;
						midi.Midi(midi.hDevice, 0xC0, choice - 1, midi.instrument - 1, 0);
					} while (midi.instrument <= 0 || midi.instrument >128);

					view.Record();
					record[choice - 1].RecordNote(midi, choice - 1);
					break;
				case 2: {
					//���
					thread t1(&RecordNoteClass::ReplayNote, &record[0], midi, 0);
					thread t2(&RecordNoteClass::ReplayNote, &record[1], midi, 1);

					t1.join();
					t2.join();
					break;
				}
				case 3:	//������ �ʱ�ȭ
					if (view.Reset()) {
						for (int i = 0; i < sizeof(record) / sizeof(record[0]); i++) {
							record[i].ResetVector();
							record[i].ResetInputTotalNum();
						}
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
					fileSystem.WriteFile(record[0], fileName, 0);
					fileName += "_1";
					fileSystem.WriteFile(record[1], fileName, -1);
					break;
				case 2:	//������ �ҷ�����
					system("cls");
					fileSystem.PrintFileList();
					cout << "�ҷ��� ���� �̸� : ";
					cin.ignore();
					getline(cin, fileName);
					fileSystem.ReadFile(record[0], fileName);
					midi.Midi(midi.hDevice, 0xC0, 0, record[0].Return_Instrument(), 0);
					fileName += "_1";
					fileSystem.ReadFile(record[1], fileName);
					midi.Midi(midi.hDevice, 0xC0, 1, record[1].Return_Instrument(), 0);
					break;
				case 3:	//������ ����
					system("cls");
					fileSystem.PrintFileList();
					cout << "������ ���� �̸� : ";
					cin.ignore();
					getline(cin, fileName);
					fileSystem.DataDelete(fileName);
				default:
					break;
				}
			} while (choice != 4);
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