#pragma once
#include<iostream>
#include<thread>
using namespace std;

#include "view.h"

//midi ���̺귯�� ����ϱ� ����
#include<Windows.h>
#pragma comment(lib, "winmm.lib")

//�ǾƳ� �ǹ����� �Ҵ��� Ű ����
//�� ��# �� ... ~ �� ��
#define NKEY 13

class MidiClass {
private:
    //bpm
    int bpm;
    //��Ʈ�γ� �����ִ���
    bool isMetronome;
    //��Ʈ�γ� �ٽ� �Լ�
    void Metronome();

public:
    //Ű���� ���� BYTE�������� ����
    BYTE pianoKey[NKEY];
    //���� Ű�� ���Ⱦ����� üũ
    BYTE pianoKeyOnOff[NKEY];
    //��Ÿ��
    BYTE octave;
    //�̵� ��ȣ�� ���� ����
    HMIDIOUT hDevice;
    //�Ǳ� ����
    int instrument;

    MidiClass();
    //�Ҹ��� ����ϱ� ���� �ٽ� �Լ�
    void Midi(HMIDIOUT device, int status, int channel, int note, int vol);
    //�̵� �Ҵ�
    void MidiAllo(HMIDIOUT& hDevice);
    void PlayMidi();
    //��Ʈ�γ� OnOff �Լ�
    void Metronome_OnOff();

    //BPM ����
    void SetBPM(int inputBPM);
    //BPM ��ȯ
    int ReturnBPM();
};