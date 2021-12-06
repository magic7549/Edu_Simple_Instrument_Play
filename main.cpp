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
	RecordNoteClass record[3];
	FileInOut fileSystem;

	midi.MidiAllo(midi.hDevice);

	//�ܼ� â ����
	view.RemoveScrollbar();
	view.ConsoleSetting();

	int choice;
	while (true) {
		view.Home();

		cin >> choice;
		cin.ignore();	//cin ���� ���� ���ۿ� �����ִ� '\n'�� ����� ����
		switch (choice)	{
		case 1:	//���� ����
			view.Piano();
			midi.PlayMidi();
			break;
		case 2:	//���� ����
			do {
				view.Record_Select();
				cin >> choice;
				cin.ignore();
				switch (choice) {
				case 1: {
					//���� Ʈ�� ����
					do {
						system("cls");
						cout << "\n\n\n\n\n\n\n\n\n\n" << endl;
						cout << "                        ������ Ʈ���� �������ּ���(1 ~ 3) : ";
						cin >> choice;
						cin.ignore();

						if (choice <= 0 || choice > 3) {
							cout << endl << "                        1 ~ 3�� Ʈ���� �������ּ���";
							Sleep(1000);
						}
					} while (choice <= 0 || choice > 3);

					//�Ǳ� ����
					do {
						system("cls");
						cout << "\n\n\n\n\n\n\n\n\n\n" << endl;
						cout << "                        �Ǳ⸦ �������ּ���(1 ~ 128) : ";
						cin >> midi.instrument;
						midi.instrument -= 1;
						cin.ignore();

						if (midi.instrument >= 0 && midi.instrument <= 127) {
							midi.Midi(midi.hDevice, 0xC0, choice - 1, midi.instrument, 0);
						}
						else {
							cout << endl << "                        1 ~ 128 �� �������ּ���";
							Sleep(1000);
						}
					} while (midi.instrument < 0 || midi.instrument >= 128);

					//��Ʈ�γ� ����
					int setBPM;
					do {
						system("cls");
						cout << "\n\n\n\n\n\n\n\n\n\n" << endl;
						cout << "      ��Ʈ�γ� BPM�� �������ּ���(40BPM ~ 240BPM ���� ���� , 0 : ��Ȱ��ȭ) : ";
						cin >> setBPM;
						cin.ignore();

						if (setBPM >= 40 && setBPM <= 240) {
							midi.SetBPM(setBPM);
							midi.Metronome_OnOff();
						}
						else if (setBPM == 0) {
							midi.SetBPM(setBPM);
							break;
						}
						else {
							cout << endl << "      40BPM ~ 240BPM ���� ����" << endl << "      0 : ��Ȱ��ȭ";
							Sleep(1000);
						}
					} while (setBPM < 40 || setBPM > 240);

					view.Record();
					view.Piano();
					cout << "���� ���� : ESC" << endl << endl;
					view.ViewInstrument(midi.instrument);
					view.ViewMetronomeBPM(midi.ReturnBPM());
					record[choice - 1].RecordNote(midi, choice - 1);

					//��Ʈ�γ��� �������� ����
					if (setBPM >= 40 && setBPM <= 240) {
						midi.Metronome_OnOff();
					}
					break;
				}
				case 2: {
					system("cls");
					view.Piano();

					//���
					thread t1(&RecordNoteClass::ReplayNote, &record[0], midi, 0);
					thread t2(&RecordNoteClass::ReplayNote, &record[1], midi, 1);
					thread t3(&RecordNoteClass::ReplayNote, &record[2], midi, 2);


					t1.join();
					t2.join();
					t3.join();
					break;
				}
				case 3:	//������ �ʱ�ȭ
					if (view.Reset()) {
						for (int i = 0; i < sizeof(record) / sizeof(record[0]); i++) {
							record[i].ResetVector();
							record[i].ResetInputTotalNum();
						}
						system("cls");
						cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n " << endl;
						cout << "                               �����͸� �ʱ�ȭ�Ͽ����ϴ�." << endl;
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
				cin.ignore();

				switch (choice) {
				case 1:	//������ ����
					system("cls");
					cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n " << endl;
					cout << "                       ������ ���� �̸� (exit �Է� �� ���) : ";
					getline(cin, fileName);

					if (fileName != "exit") {
						fileSystem.WriteFile(record[0], fileName, 0);
						fileSystem.WriteFile(record[1], fileName + "_1", -1);
						fileSystem.WriteFile(record[2], fileName + "_2", -1);
					}
					break;
				case 2:	//������ �ҷ�����
					system("cls");
					cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n " << endl;
					fileSystem.PrintFileList();

					cout << "                       �ҷ��� ���� �̸� (exit �Է� �� ���) : ";
					getline(cin, fileName);

					if (fileName != "exit") {
						fileSystem.ReadFile(record[0], fileName);
						midi.Midi(midi.hDevice, 0xC0, 0, record[0].Return_Instrument(), 0);

						fileSystem.ReadFile(record[1], fileName + "_1");
						midi.Midi(midi.hDevice, 0xC0, 1, record[1].Return_Instrument(), 0);

						fileSystem.ReadFile(record[2], fileName + "_2");
						midi.Midi(midi.hDevice, 0xC0, 2, record[2].Return_Instrument(), 0);
					}
					break;
				case 3:	//������ ����
					system("cls");
					cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n " << endl;
					fileSystem.PrintFileList();

					cout << "                    ������ ���� �̸� (exit �Է� �� ���) : ";
					getline(cin, fileName);

					if (fileName != "exit") {
						fileSystem.DataDelete(fileName);
					}
				default:
					break;
				}
			} while (choice != 4);
			break;
		}
		case 4:	//����
			//html �����۸�ũ
			system("explorer help.html");
			break;
		case 5: //����
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