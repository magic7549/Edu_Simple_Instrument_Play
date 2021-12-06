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

	//콘솔 창 설정
	view.RemoveScrollbar();
	view.ConsoleSetting();

	int choice;
	while (true) {
		view.Home();

		cin >> choice;
		cin.ignore();	//cin 으로 인해 버퍼에 남아있는 '\n'을 지우기 위함
		switch (choice)	{
		case 1:	//자유 연주
			view.Piano();
			midi.PlayMidi();
			break;
		case 2:	//녹음 관련
			do {
				view.Record_Select();
				cin >> choice;
				cin.ignore();
				switch (choice) {
				case 1: {
					//녹음 트랙 선택
					do {
						system("cls");
						cout << "\n\n\n\n\n\n\n\n\n\n" << endl;
						cout << "                        녹음할 트랙을 선택해주세요(1 ~ 3) : ";
						cin >> choice;
						cin.ignore();

						if (choice <= 0 || choice > 3) {
							cout << endl << "                        1 ~ 3번 트랙을 선택해주세요";
							Sleep(1000);
						}
					} while (choice <= 0 || choice > 3);

					//악기 선택
					do {
						system("cls");
						cout << "\n\n\n\n\n\n\n\n\n\n" << endl;
						cout << "                        악기를 선택해주세요(1 ~ 128) : ";
						cin >> midi.instrument;
						midi.instrument -= 1;
						cin.ignore();

						if (midi.instrument >= 0 && midi.instrument <= 127) {
							midi.Midi(midi.hDevice, 0xC0, choice - 1, midi.instrument, 0);
						}
						else {
							cout << endl << "                        1 ~ 128 중 선택해주세요";
							Sleep(1000);
						}
					} while (midi.instrument < 0 || midi.instrument >= 128);

					//메트로놈 설정
					int setBPM;
					do {
						system("cls");
						cout << "\n\n\n\n\n\n\n\n\n\n" << endl;
						cout << "      메트로놈 BPM을 설정해주세요(40BPM ~ 240BPM 설정 가능 , 0 : 비활성화) : ";
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
							cout << endl << "      40BPM ~ 240BPM 설정 가능" << endl << "      0 : 비활성화";
							Sleep(1000);
						}
					} while (setBPM < 40 || setBPM > 240);

					view.Record();
					view.Piano();
					cout << "녹음 종료 : ESC" << endl << endl;
					view.ViewInstrument(midi.instrument);
					view.ViewMetronomeBPM(midi.ReturnBPM());
					record[choice - 1].RecordNote(midi, choice - 1);

					//메트로놈이 켜졌으면 종료
					if (setBPM >= 40 && setBPM <= 240) {
						midi.Metronome_OnOff();
					}
					break;
				}
				case 2: {
					system("cls");
					view.Piano();

					//재생
					thread t1(&RecordNoteClass::ReplayNote, &record[0], midi, 0);
					thread t2(&RecordNoteClass::ReplayNote, &record[1], midi, 1);
					thread t3(&RecordNoteClass::ReplayNote, &record[2], midi, 2);


					t1.join();
					t2.join();
					t3.join();
					break;
				}
				case 3:	//데이터 초기화
					if (view.Reset()) {
						for (int i = 0; i < sizeof(record) / sizeof(record[0]); i++) {
							record[i].ResetVector();
							record[i].ResetInputTotalNum();
						}
						system("cls");
						cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n " << endl;
						cout << "                               데이터를 초기화하였습니다." << endl;
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
				case 1:	//데이터 저장
					system("cls");
					cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n " << endl;
					cout << "                       저장할 파일 이름 (exit 입력 시 취소) : ";
					getline(cin, fileName);

					if (fileName != "exit") {
						fileSystem.WriteFile(record[0], fileName, 0);
						fileSystem.WriteFile(record[1], fileName + "_1", -1);
						fileSystem.WriteFile(record[2], fileName + "_2", -1);
					}
					break;
				case 2:	//데이터 불러오기
					system("cls");
					cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n " << endl;
					fileSystem.PrintFileList();

					cout << "                       불러올 파일 이름 (exit 입력 시 취소) : ";
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
				case 3:	//데이터 삭제
					system("cls");
					cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n " << endl;
					fileSystem.PrintFileList();

					cout << "                    삭제할 파일 이름 (exit 입력 시 취소) : ";
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
		case 4:	//도움말
			//html 하이퍼링크
			system("explorer help.html");
			break;
		case 5: //종료
			return 0;
		default:
			break;
		}
	}

	//midiOut 초기화 후 종료
	midiOutReset(midi.hDevice);
	midiOutClose(midi.hDevice);
	
	return 0;
}