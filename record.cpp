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
    //����� ���� ���� ��� �ʱ�ȭ
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
void RecordNoteClass::ReplayNote(MidiClass& midi) {
    BYTE key;
    View view;
    MidiClass mc;

    //���� ���
    system("cls");
    int inputKeyNum[NKEY] = { 0, };      //����� �� ���踶�� ��� ° �迭���� ����ߴ��� üũ
    int finishRecordCheck = ReturnInputTotalNum();  //��� �Ϸ��ߴ��� üũ
    start = clock();

    while (true) {
        //��� �Ϸ������� �ݺ��� ����
        if (finishRecordCheck <= 0) {
            Sleep(500);
            break;
        }

        for (key = 0; key < NKEY; key++) {
            //�ð� üũ
            finish = clock();
            duration = (double)(finish - start) / CLOCKS_PER_SEC;

            //�� ���踶�� ����� ���� �� ������� ��� �н�
            if (inputKeyNum[key] >= recordNote[key].size())
                continue;

            //���� �ð��� ������ �ð����� ���ų� Ŭ���
            //��, �� ���踦 ����� �ð��� ���� ���
            if (duration >= recordNote[key][inputKeyNum[key]]) {
                //inputKeyNum[key]�� ¦����
                //�� ���� ���
                if ((inputKeyNum[key] % 2) == 0) {
                    midi.Midi(midi.hDevice, 0x90, 0, (BYTE)(48 + key), 127);
                    inputKeyNum[key]++;
                    view.ShowDoReMi(key);
                }
                //�� ���� ��� ����
                else {
                    midi.Midi(midi.hDevice, 0x80, 0, (BYTE)(48 + key), 127);
                    inputKeyNum[key]++;
                    finishRecordCheck--;
                }
            }
        }
    }
}
void RecordNoteClass::RecordNote(MidiClass& midi) {
    View view;

    ResetVector();
    ResetInputTotalNum();
    start = clock();

    BYTE key;
    while (true)
    {
        for (key = 0; key < NKEY; key++) {
            //pianoKey ������ �Ҵ�� Ű�� ������ ��
            //0x8000�� ���� üũ �� �� ��� ������ Ű�� ���Ⱦ ���ǹ� ����
            if (GetAsyncKeyState(midi.pianoKey[key]) & 0x8000) {
                //������ �� Ű�� ���� ���� ������
                if (midi.pianoKeyOnOff[key] == 0) {
                    midi.pianoKeyOnOff[key] = 1;

                    //���� ��ư�� ���� �� ���� �ð� üũ
                    finish = clock();
                    duration = (double)(finish - start) / CLOCKS_PER_SEC;

                    //���� �ð��� �� ���踶�� ���� ����
                    recordNote[key + midi.octave - 48].push_back(duration);

                    midi.Midi(midi.hDevice, 0x90, 0, (BYTE)(48 + key), 127);

                    //�� ����� Ű �Է��� �־����� üũ�Ͽ�, �Ŀ� ��� ��Ʈ��
                    AddInputTotalNum();

                    view.ShowDoReMi(key);
                }
            }
        }
        //Ű�� ������ ��
        for (key = 0; key < NKEY; key++) {
            //Ű�� �Էµ� ���� �ƴ϶��
            if (!(GetAsyncKeyState(midi.pianoKey[key]) & 0x8000)) {
                //������ �Էµ� ���� �ִ� Ű���
                if (midi.pianoKeyOnOff[key] != 0) {
                    midi.pianoKeyOnOff[key] = 0;

                    finish = clock();
                    duration = (double)(finish - start) / CLOCKS_PER_SEC;

                    //���� �ð��� �� ���踶�� ���� ����
                    recordNote[key + midi.octave - 48].push_back(duration);

                    midi.Midi(midi.hDevice, 0x80, 0, (BYTE)(48 + key), 127);
                }
            }
        }
        //ESC �Է½� ����
        if (GetAsyncKeyState(VK_ESCAPE))
            break;
    }
}