#pragma once
#include<fstream>   //파일 입출력
#include<io.h>  //파일 존재 유무 체크
#include "record.h"

class FileInOut {
    ifstream fin;
    ifstream inFileList;
    ofstream fout;
    ofstream outFileList;
public:
    ~FileInOut();
    void WriteFile(RecordNoteClass& record, string fileName, int isBase);
    void ReadFile(RecordNoteClass& record, string fileName);
    void RoadRecordNote(RecordNoteClass& record, string loadSaveFile);
    void PrintFileList();
    void DataDelete(string fileName);
};