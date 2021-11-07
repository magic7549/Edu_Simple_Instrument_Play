#include "fileInOut.h"

FileInOut::~FileInOut() {
    if (fout.is_open()) {
        fout.close();
        cout << "fout close" << endl;
    }

    if (fin.is_open()) {
        fin.close();
        cout << "fin close" << endl;
    }
}
void FileInOut::OpenFileOut() {
    //파일이 열리지 않았을 경우에만 코드 실행
    if (!fout.is_open()) {
        //파일 입출력
        fout.open(".//test.txt");
        if (fout.fail()) {
            cout << "실패";
        }
    }
}
//데이터 저장
void FileInOut::WriteFile(RecordNoteClass& record) {
    for (int key = 0; key < NKEY; key++) {
        for (int i = 0; i < record.recordNote[key].size(); i++) {
            //무슨음이 몇초에 눌렸는지 저장
            //ex) 2:0.568  => "레" 0.568초에 눌림
            fout << key << ":" << record.recordNote[key][i] << endl;
        }
    }
}
void FileInOut::ReadFile(RecordNoteClass& record) {
    //파일이 열리지 않았을 경우에만 코드 실행
    if (!fin.is_open()) {
        fin.open(".//test.txt");
        if (fin.fail()) {
            cout << "저장된 데이터가 없습니다." << endl;
        }
        else {
            //txt파일로 저장된 데이터를 담는 변수
            string loadSaveFile;

            record.ResetInputTotalNum();
            while (getline(fin, loadSaveFile)) {
                RoadRecordNote(record, loadSaveFile);
            }
            record.DivideInputTotalNum();
        }
    }
}
void FileInOut::RoadRecordNote(RecordNoteClass& record, string loadSaveFile) {
    //무슨 음인지 파악
    int index = loadSaveFile.find(':');
    int key = stoi(loadSaveFile.substr(0, index));

    //몇 초에 입력되었는지 파악
    double time = stod(loadSaveFile.substr(index + 1));

    //총 몇번의 입력이 있었는지 파악
    record.AddInputTotalNum();

    //불러온 데이터 벡터에 저장
    record.recordNote[key].push_back(time);
}