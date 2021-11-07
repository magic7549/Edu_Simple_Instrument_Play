#pragma once
#include<fstream>
#include "record.h"

class FileInOut {
    ifstream fin;
    ofstream fout;
public:
    ~FileInOut();
    void OpenFileOut();
    void WriteFile(RecordNoteClass& record);
    void ReadFile(RecordNoteClass& record);
    void RoadRecordNote(RecordNoteClass& record, string loadSaveFile);
};