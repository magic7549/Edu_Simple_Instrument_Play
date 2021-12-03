#include "midi.h"

MidiClass::MidiClass() {
    //���� �ʱ�ȭ �۾�
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
//device : midiOut�� ���� ��ȯ���� �ڵ� (���� ���ϸ� �Ҵ���� �Ǳ�?)
//status : � ��ȣ�� ������ (0x90 : Note on, 0x80 : Note off)
//channel : ��ȣ�� ���� ä�� (0 ~ 15)
//note : ���� ����
//vol : ����
void MidiClass::Midi(HMIDIOUT device, int status, int channel, int note, int vol) {
    //�̵��ȣ�� ������ ���ؼ��� ��Ʈ�������� 3����Ʈ¥�� �޼����� ���� �� ��������
    //�׿� ���� ��Ʈ���� �۾�
    DWORD dwMsg = (status | channel | (note << 8) | (vol << 16));
    //��� ��ġ�� �����͸� ����(�Ҹ� ���)
    midiOutShortMsg(device, dwMsg);
}
void MidiClass::MidiAllo(HMIDIOUT& hDevice) {
    //midiOut�� ���� �׿� ���� �ڵ��� hDevice�� ����
    //�Ҵ翡 �����ߴ��� Ȯ���ϱ� ���� success�� �� ����
    int success = midiOutOpen(&hDevice, MIDIMAPPER, 0, 0, CALLBACK_NULL);

    //�Ҵ� �������� ���
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
        //�Ҹ� ���
        for (key = 0; key < NKEY; key++) {
            //pianoKey ������ �Ҵ�� Ű�� ������ ��
            //0x8000�� ���� üũ �� �� ��� ������ Ű�� ���Ⱦ ���ǹ� ����
            if (GetAsyncKeyState(pianoKey[key]) & 0x8000) {
                //������ �� Ű�� ���� ���� ������
                if (pianoKeyOnOff[key] == 0) {
                    //������ ������
                    pianoKeyOnOff[key] = 1;

                    //���� Ű�� �ش��ϴ� �� ���
                    //0x90 : Note on
                    Midi(hDevice, 0x90, 14, (BYTE)(octave + key), 127);

                    //���� ȭ�� ���
                    view.DisplayInput(key, true);
                    view.ShowDoReMi(key);
                }
            }
        }
        //Ű�� ������ ��
        for (key = 0; key < NKEY; key++) {
            //Ű�� �Էµ� ���� �ƴ϶��
            if (!(GetAsyncKeyState(pianoKey[key]) & 0x8000)) {
                //������ �Էµ� ���� �ִ� Ű���
                if (pianoKeyOnOff[key] != 0) {
                    //���� ���� ���� ������
                    pianoKeyOnOff[key] = 0;

                    //�Ҹ� ����
                    //0x80 : Note off
                    Midi(hDevice, 0x80, 14, (BYTE)(octave + key), 127);

                    //�Է� ǥ�� ����
                    view.DisplayInput(key, false);
                }
            }
        }

        //�Ǳ� ���� ����
        //����Ű ����
        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            // 0 ~ 127
            if (instrument < 127) {
                instrument++;
                Midi(hDevice, 0xC0, 10, instrument, 0);
                view.ViewInstrument(instrument);
                Sleep(200);
            }
        }
        //����Ű �Ʒ���
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
        //��Ʈ�γ�
        if (GetAsyncKeyState(0x51) & 0x8000) {
            Metronome_OnOff();
            Sleep(200);
        }
        //����Ű ����
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            // 40 ~ 240
            if (bpm < 240) {
                bpm++;
                view.ViewMetronomeBPM(bpm);
                Sleep(100);
            }
        }
        //����Ű ������
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            // 40 ~ 240
            if (bpm > 40) {
                bpm--;
                view.ViewMetronomeBPM(bpm);
                Sleep(100);
            }
        }

        //ESC �Է½� ����
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