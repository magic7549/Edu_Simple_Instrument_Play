#pragma once
#include<iostream>
using namespace std;

#include "view.h"

//midi 라이브러리 사용하기 위함
#include<Windows.h>
#pragma comment(lib, "winmm.lib")

//피아노 건반으로 할당할 키 개수
#define NKEY 15

class MidiClass {
public:
    //키보드 값을 BYTE형식으로 저장
    BYTE pianoKey[NKEY];
    //각각 키가 눌렸었는지 체크
    BYTE pianoKeyOnOff[NKEY];
    //옥타브
    BYTE octave;
    //미디 신호를 담을 변수
    HMIDIOUT hDevice;
    //악기 종류
    int instrument;

    MidiClass();
    //소리를 출력하기 위한 핵심 함수
    void Midi(HMIDIOUT device, int status, int channel, int note, int vol);
    //미디 할당
    void MidiAllo(HMIDIOUT& hDevice);
    void PlayMidi();
};