#include "midi.h"

MidiClass::MidiClass() {
    //변수 초기화 작업
    //ex) 0x5A = "z", 0x53 = "s"
    BYTE pianoKey[NKEY] = {
        0x5A, 0x53, 0x58, 0x44, 0x43,
        0x56, 0x47, 0x42, 0x48, 0x4e,
        0x4A, 0x4d, 0xBC, 0x4C, 0xBE,
        0xBA, 0xBF
    };
    for (int i = 0; i < NKEY; i++)
    {
        this->pianoKey[i] = pianoKey[i];
    }

    for (int i = 0; i < NKEY; i++)
    {
        pianoKeyOnOff[i] = 0;
    }
    octave = 48;
    instrument = 0;
    hDevice = NULL;
    bpm = 120;
    isMetronome = false;
}
//device : midiOut을 열고 반환받은 핸들 (쉽게 말하면 할당받은 악기?)
//status : 어떤 신호를 보낼지 (0x90 : Note on, 0x80 : Note off)
//channel : 신호를 보낼 채널 (0 ~ 15)
//note : 음의 높이
//vol : 볼륨
void MidiClass::Midi(HMIDIOUT device, int status, int channel, int note, int vol) {
    //미디신호를 보내기 위해서는 비트연산으로 3바이트짜리 메세지를 만든 후 보내야함
    //그에 따른 비트연산 작업
    DWORD dwMsg = (status | channel | (note << 8) | (vol << 16));
    //출력 장치로 데이터를 보냄(소리 재생)
    midiOutShortMsg(device, dwMsg);
}
void MidiClass::MidiAllo(HMIDIOUT& hDevice) {
    //midiOut을 열고 그에 대한 핸들을 hDevice에 저장
    //할당에 성공했는지 확인하기 위해 success에 값 저장
    int success = midiOutOpen(&hDevice, MIDIMAPPER, 0, 0, CALLBACK_NULL);

    //할당 실패했을 경우
    if (success != 0) {
        cout << "midi allocation fail..." << endl;
        Sleep(2000);
    }
}
void MidiClass::PlayMidi() {
    View view;
    BYTE key;

    while (true)
    {
        //소리 출력
        for (key = 0; key < NKEY; key++) {
            //pianoKey 변수에 할당된 키가 눌렸을 때
            //0x8000을 같이 체크 안 할 경우 이전에 키가 눌렸어도 조건문 실행
            if (GetAsyncKeyState(pianoKey[key]) & 0x8000) {
                //이전에 이 키를 누른 적이 없으면
                if (pianoKeyOnOff[key] == 0) {
                    //눌렀던 것으로
                    pianoKeyOnOff[key] = 1;

                    //누른 키에 해당하는 음 재생
                    //0x90 : Note on
                    Midi(hDevice, 0x90, 14, (BYTE)(octave + key), 127);

                    //음계 화면 출력
                    view.DisplayInput(key, true);
                    view.ShowDoReMi(key);
                }
            }
        }
        //키를 떼었을 때
        for (key = 0; key < NKEY; key++) {
            //키가 입력된 것이 아니라면
            if (!(GetAsyncKeyState(pianoKey[key]) & 0x8000)) {
                //이전에 입력된 적이 있는 키라면
                if (pianoKeyOnOff[key] != 0) {
                    //누른 적이 없는 것으로
                    pianoKeyOnOff[key] = 0;

                    //소리 멈춤
                    //0x80 : Note off
                    Midi(hDevice, 0x80, 14, (BYTE)(octave + key), 127);

                    //입력 표시 지움
                    view.DisplayInput(key, false);
                }
            }
        }

        //악기 종류 변경
        //방향키 위쪽
        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            // 0 ~ 127
            if (instrument < 127) {
                instrument++;
                Midi(hDevice, 0xC0, 10, instrument, 0);
                view.ViewInstrument(instrument);
                Sleep(200);
            }
        }
        //방향키 아래쪽
        if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            // 0 ~ 127
            if (instrument > 0) {
                instrument--;
                Midi(hDevice, 0xC0, 10, instrument, 0);
                view.ViewInstrument(instrument);
                Sleep(200);
            }
        }

        //Q
        //메트로놈
        if (GetAsyncKeyState(0x51) & 0x8000) {
            Metronome_OnOff();
            Sleep(200);
        }
        //방향키 왼쪽
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            // 40 ~ 240
            if (bpm < 240) {
                bpm++;
                view.ViewMetronomeBPM(bpm);
                Sleep(100);
            }
        }
        //방향키 오른쪽
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            // 40 ~ 240
            if (bpm > 40) {
                bpm--;
                view.ViewMetronomeBPM(bpm);
                Sleep(100);
            }
        }

        //ESC 입력시 종료
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            isMetronome = false;
            break;
        }
    }
}
void MidiClass::Metronome() {
    Midi(hDevice, 0xC0, 15, 115, 0);
    while (isMetronome) {
        Midi(hDevice, 0x90, 15, (BYTE)(octave + 4), 127);
        Sleep(50);
        Midi(hDevice, 0x80, 15, (BYTE)(octave + 4), 127);
        Sleep(60.0 / bpm * 1000 - 50);
    }
}
void MidiClass::Metronome_OnOff() {
    if (isMetronome) {
        isMetronome = false;
    }
    else {
        isMetronome = true;
        thread thread_metronome(&MidiClass::Metronome, this);
        thread_metronome.detach();
    }
}
void MidiClass::SetBPM(int inputBPM) {
    bpm = inputBPM;
}
int MidiClass::ReturnBPM() {
    return bpm;
}