#include "midi.h"

MidiClass::MidiClass() {
    //���� �ʱ�ȭ �۾�
    //ex) 0x5A = "z", 0x53 = "s"
    BYTE pianoKey[NKEY] = {
        0x5A, 0x53, 0x58, 0x44, 0x43,
        0x56, 0x47, 0x42, 0x48, 0x4e,
        0x4A, 0x4d, 0xBC
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
    //
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

    view.ViewInstrument(instrument);
    while (true)
    {
        view.RenderImage(60, 0);

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
                    Midi(hDevice, 0x90, 0, (BYTE)(octave + key), 127);

                    //���� ȭ�� ���
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
                    Midi(hDevice, 0x80, 0, (BYTE)(octave + key), 127);
                }
            }
        }
        //�Ǳ� ���� ����
        //����Ű ����
        if (GetAsyncKeyState(VK_UP)) {
            // 0 ~ 127
            if (instrument < 127) {
                instrument++;
                Midi(hDevice, 0xC0, 0, instrument, 0);
                view.ViewInstrument(instrument);
                Sleep(200);
            }
        }
        //����Ű �Ʒ���
        if (GetAsyncKeyState(VK_DOWN)) {
            // 0 ~ 127
            if (instrument > 0) {
                instrument--;
                Midi(hDevice, 0xC0, 0, instrument, 0);
                view.ViewInstrument(instrument);
                Sleep(200);
            }
        }

        //ESC �Է½� ����
        if (GetAsyncKeyState(VK_ESCAPE))
            break;
    }
}