#pragma once
#include<fstream>
#include "record.h"

class FileInOut {
    ifstream fin;
    ofstream fout;
public:
    ~FileInOut();
    void OpenFileOut(string fileName);
    void WriteFile(RecordNoteClass& record, string fileName);
    void ReadFile(RecordNoteClass& record, string fileName);
    void RoadRecordNote(RecordNoteClass& record, string loadSaveFile);
};