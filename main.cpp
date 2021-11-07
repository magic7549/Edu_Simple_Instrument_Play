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
		case 1:	//자유 연주
			view.Free_Play();
			midi.PlayMidi();
			break;
		case 2:	//녹음 관련
			do {
				view.Record_Select();
				cin >> choice;
				switch (choice)
				{
				case 1:	//녹음
					view.Record();
					record.RecordNote(midi);
					break;
				case 2:	//재생
					record.ReplayNote(midi);
					break;
				case 3:	//데이터 초기화
					if (view.Reset()) {
						record.ResetVector();
						record.ResetInputTotalNum();
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
					fileSystem.WriteFile(record, fileName);
					break;
				case 2:	//데이터 불러오기
					system("cls");
					cout << "불러올 파일 이름 : ";
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

	//midiOut 초기화 후 종료
	midiOutReset(midi.hDevice);
	midiOutClose(midi.hDevice);
	
	return 0;
}