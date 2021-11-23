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

	//콘솔 창 설정
	view.RemoveScrollbar();
	view.ConsoleSetting();

	/// <마우스 이벤트>
	/// DWORD prevMode = 0;
	/// HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
	/// GetConsoleMode(handle, &prevMode);
	/// SetConsoleMode(handle, prevMode & ~ENABLE_QUICK_EDIT_MODE | ENABLE_MOUSE_INPUT);
	/// </마우스 이벤트>

	int choice;
	while (true)
	{
		cin.clear();
		view.Home();
		cin >> choice;

		switch (choice)
		{
		case 1:	//자유 연주
			view.Piano();
			view.ViewInstrument(midi.instrument);
			view.ViewMetronomeBPM(midi.ReturnBPM());
			midi.PlayMidi();
			break;
		case 2:	//녹음 관련
			do {
				view.Record_Select();
				cin >> choice;
				switch (choice)
				{
				case 1: {
					//녹음 트랙 선택
					do {
						system("cls");
						cout << "녹음할 트랙을 선택해주세요(1 ~ 2) : ";
						cin >> choice;

						if (choice <= 0 || choice > 2) {
							cout << "1 ~ 2번 트랙을 선택해주세요";
							Sleep(1000);
						}
					} while (choice <= 0 || choice > 2);

					//악기 선택
					do {
						system("cls");
						cout << "악기를 선택해주세요(1 ~ 128) : ";
						cin >> midi.instrument;
						if (midi.instrument >= 1 && midi.instrument <= 128) {
							midi.Midi(midi.hDevice, 0xC0, choice - 1, midi.instrument - 1, 0);
						}
						else {
							cout << "1 ~ 128 중 선택해주세요";
							Sleep(1000);
						}
					} while (midi.instrument <= 0 || midi.instrument > 128);

					//메트로놈 설정
					int setBPM;
					do {
						system("cls");
						cout << "메트로놈 BPM을 설정해주세요(40BPM ~ 240BPM 설정 가능 , 0 : 비활성화) : ";
						cin >> setBPM;
						if (setBPM >= 40 && setBPM <= 240) {
							midi.SetBPM(setBPM);
							midi.Metronome_OnOff();
						}
						else if (setBPM == 0) {
							break;
						}
						else {
							cout << "40BPM ~ 240BPM 설정 가능" << endl << "0 : 비활성화";
							Sleep(1000);
						}
					} while (setBPM < 40 || setBPM > 240);

					view.Record();
					view.Piano();
					view.ViewInstrument(midi.instrument);
					record[choice - 1].RecordNote(midi, choice - 1);

					//메트로놈이 켜졌으면 종료
					if (setBPM >= 40 && setBPM <= 240) {
						midi.Metronome_OnOff();
					}
					break;
				}
				case 2: {
					system("cls");

					//재생
					thread t1(&RecordNoteClass::ReplayNote, &record[0], midi, 0);
					thread t2(&RecordNoteClass::ReplayNote, &record[1], midi, 1);

					t1.join();
					t2.join();
					break;
				}
				case 3:	//데이터 초기화
					if (view.Reset()) {
						for (int i = 0; i < sizeof(record) / sizeof(record[0]); i++) {
							record[i].ResetVector();
							record[i].ResetInputTotalNum();
						}
						system("cls");
						cout << "데이터를 초기화하였습니다." << endl;
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
				case 1:	//데이터 저장
					system("cls");
					cout << "저장할 파일 이름 : ";
					cin.ignore();
					getline(cin, fileName);
					fileSystem.WriteFile(record[0], fileName, 0);
					fileName += "_1";
					fileSystem.WriteFile(record[1], fileName, -1);
					break;
				case 2:	//데이터 불러오기
					system("cls");
					fileSystem.PrintFileList();
					cout << "불러올 파일 이름 : ";
					cin.ignore();
					getline(cin, fileName);
					fileSystem.ReadFile(record[0], fileName);
					midi.Midi(midi.hDevice, 0xC0, 0, record[0].Return_Instrument(), 0);
					fileName += "_1";
					fileSystem.ReadFile(record[1], fileName);
					midi.Midi(midi.hDevice, 0xC0, 1, record[1].Return_Instrument(), 0);
					break;
				case 3:	//데이터 삭제
					system("cls");
					fileSystem.PrintFileList();
					cout << "삭제할 파일 이름 : ";
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

	//midiOut 초기화 후 종료
	midiOutReset(midi.hDevice);
	midiOutClose(midi.hDevice);
	
	return 0;
}