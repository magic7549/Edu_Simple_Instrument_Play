#include "record.h"

void RecordNoteClass::ResetInputTotalNum() {
    inputTotalNum = 0;
}
void RecordNoteClass::AddInputTotalNum() {
    inputTotalNum++;
}
void RecordNoteClass::DivideInputTotalNum() {
    inputTotalNum /= 2;
}
int RecordNoteClass::ReturnInputTotalNum() {
    return inputTotalNum;
}
void RecordNoteClass::ResetVector() {
    //저장된 값이 있을 경우 초기화
    for (BYTE key = 0; key < NKEY; key++) {
        if (recordNote[key].size() != 0) {
            vector<double>::iterator it;
            for (; recordNote[key].size() != 0;) {
                it = recordNote[key].begin();
                it = recordNote[key].erase(it);
            }
        }
    }
}
void RecordNoteClass::RecordNote(MidiClass& midi) {
    View view;

    //초기화 작업
    ResetVector();
    ResetInputTotalNum();
    midi.instrument = 0;
    midi.Midi(midi.hDevice, 0xC0, 0, midi.instrument, 0); //악기 피아노로 설정

    start = clock();

    BYTE key;
    view.ViewInstrument(midi.instrument);

    //커서 이동 시키기
    view.Gotoxy(0, 20);

    while (true)
    {
        view.RenderImage(60, 20);
        for (key = 0; key < NKEY; key++) {
            //pianoKey 변수에 할당된 키가 눌렸을 때
            //0x8000을 같이 체크 안 할 경우 이전에 키가 눌렸어도 조건문 실행
            if (GetAsyncKeyState(midi.pianoKey[key]) & 0x8000) {
                //이전에 이 키를 누른 적이 없으면
                if (midi.pianoKeyOnOff[key] == 0) {
                    midi.pianoKeyOnOff[key] = 1;

                    //녹음 버튼을 누른 후 지난 시간 체크
                    finish = clock();
                    duration = (double)(finish - start) / CLOCKS_PER_SEC;

                    //지난 시간을 각 음계마다 따로 저장
                    recordNote[key].push_back(duration);

                    midi.Midi(midi.hDevice, 0x90, 0, (BYTE)(48 + key), 127);

                    //총 몇번의 키 입력이 있었는지 체크하여, 후에 재생 컨트롤
                    AddInputTotalNum();

                    view.ShowDoReMi(key);
                }
            }
        }
        //키를 떼었을 때
        for (key = 0; key < NKEY; key++) {
            //키가 입력된 것이 아니라면
            if (!(GetAsyncKeyState(midi.pianoKey[key]) & 0x8000)) {
                //이전에 입력된 적이 있는 키라면
                if (midi.pianoKeyOnOff[key] != 0) {
                    midi.pianoKeyOnOff[key] = 0;

                    finish = clock();
                    duration = (double)(finish - start) / CLOCKS_PER_SEC;

                    //지난 시간을 각 음계마다 따로 저장
                    recordNote[key].push_back(duration);

                    midi.Midi(midi.hDevice, 0x80, 0, (BYTE)(48 + key), 127);
                }
            }
        }
        //악기 종류 변경
        //방향키 위쪽
        if (GetAsyncKeyState(VK_UP)) {
            // 0 ~ 127
            if (midi.instrument < 127) {
                midi.instrument++;
                midi.Midi(midi.hDevice, 0xC0, 0, midi.instrument, 0);
                view.ViewInstrument(midi.instrument);

                //악기 종류 저장
                recordNote[13].push_back(duration);

                Sleep(200);
            }
        }
        //방향키 아래쪽
        if (GetAsyncKeyState(VK_DOWN)) {
            // 0 ~ 127
            if (midi.instrument > 0) {
                midi.instrument--;
                midi.Midi(midi.hDevice, 0xC0, 0, midi.instrument, 0);
                view.ViewInstrument(midi.instrument);

                //악기 종류 저장
                recordNote[14].push_back(duration);

                Sleep(200);
            }
        }

        //ESC 입력시 종료
        if (GetAsyncKeyState(VK_ESCAPE))
            break;
    }
}
void RecordNoteClass::ReplayNote(MidiClass& midi) {
    BYTE key;
    View view;
    MidiClass mc;

    //초기화 작업
    midi.instrument = 0;
    midi.Midi(midi.hDevice, 0xC0, 0, midi.instrument, 0); //악기 피아노로 설정

    //벡터 확인을 위한 이터레이터
    vector<double>::iterator it_instrumentUp = recordNote[13].begin();
    vector<double>::iterator it_instrumentDown = recordNote[14].begin();

    //녹음 재생
    system("cls");
    int inputKeyNum[NKEY] = { 0, };      //재생시 각 음계마다 몇번 째 배열까지 재생했는지 체크
    int finishRecordCheck = ReturnInputTotalNum();  //재생 완료했는지 체크
    start = clock();
    while (true) {
        //재생 완료했으면 반복문 종료
        if (finishRecordCheck <= 0) {
            Sleep(500);
            break;
        }

        for (key = 0; key < NKEY - 2; key++) {
            //시간 체크
            finish = clock();
            duration = (double)(finish - start) / CLOCKS_PER_SEC;

            //각 음계마다 저장된 값을 다 재생했을 경우 패스
            if (inputKeyNum[key] >= recordNote[key].size())
                continue;

            //현재 시간이 녹음된 시간보다 같거나 클경우
            //즉, 각 음계를 재생할 시간이 됐을 경우
            if (duration >= recordNote[key][inputKeyNum[key]]) {
                //inputKeyNum[key]가 짝수면
                //각 음계 재생
                if ((inputKeyNum[key] % 2) == 0) {
                    midi.Midi(midi.hDevice, 0x90, 0, (BYTE)(48 + key), 127);
                    inputKeyNum[key]++;
                    view.ShowDoReMi(key);
                }
                //각 음계 재생 멈춤
                else {
                    midi.Midi(midi.hDevice, 0x80, 0, (BYTE)(48 + key), 127);
                    inputKeyNum[key]++;
                    finishRecordCheck--;
                }
            }
        }
        //녹음하면서 바꾼 악기 적용 : 악기 번호 증가
        if (!recordNote[13].empty() && it_instrumentUp != recordNote[13].end()) {
            //시간 체크
            finish = clock();
            duration = (double)(finish - start) / CLOCKS_PER_SEC;

            //현재 시간이 녹음된 시간보다 같거나 클경우
            if (duration >= *it_instrumentUp) {
                midi.instrument++;
                midi.Midi(midi.hDevice, 0xC0, 0, midi.instrument, 0);
                it_instrumentUp++;
            }
        }
        //녹음하면서 바꾼 악기 적용 : 악기 번호 감소
        if (!recordNote[14].empty() && it_instrumentDown != recordNote[14].end()) {
            //시간 체크
            finish = clock();
            duration = (double)(finish - start) / CLOCKS_PER_SEC;

            //현재 시간이 녹음된 시간보다 같거나 클경우
            if (duration >= *it_instrumentDown) {
                midi.instrument--;
                midi.Midi(midi.hDevice, 0xC0, 0, midi.instrument, 0);
                it_instrumentDown++;
            }
        }
    }
}
