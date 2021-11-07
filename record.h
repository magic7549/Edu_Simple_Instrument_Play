#pragma once
#include<vector>
#include<string>
#include<ctime>
#include "midi.h"
#include "view.h"
using namespace std;

class RecordNoteClass {
    //���� ���� �� ��� �Է��� �־����� üũ
    int inputTotalNum;

    //�ð� ������ ���� ����
    clock_t start, finish;
    double duration;

public:
    //������ ���� ���� �迭, �� ���踶�� ���� ����
    //ex) recordNote[0] ���� "��"�� �ش��ϴ� �ð� �� ����
    vector<double> recordNote[NKEY];

    void ResetInputTotalNum();
    void AddInputTotalNum();
    void DivideInputTotalNum();
    int ReturnInputTotalNum();
    void ResetVector();

    void RecordNote(MidiClass& midi);
    void ReplayNote(MidiClass& midi);
};