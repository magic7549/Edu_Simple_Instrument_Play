#pragma once
#include<vector>
#include<string>
#include<ctime>
#include "midi.h"
#include "view.h"
using namespace std;

class RecordNoteClass {
    //녹음 시작 후 몇번 입력이 있었는지 체크
    int inputTotalNum;

    //시간 측정을 위한 변수
    clock_t start, finish;
    double duration;

public:
    //녹음을 위한 벡터 배열, 각 음계마다 따로 저장
    //ex) recordNote[0] 에는 "도"에 해당하는 시간 값 저장
    vector<double> recordNote[NKEY];

    void ResetInputTotalNum();
    void AddInputTotalNum();
    void DivideInputTotalNum();
    int ReturnInputTotalNum();
    void ResetVector();

    void RecordNote(MidiClass& midi);
    void ReplayNote(MidiClass& midi);
};