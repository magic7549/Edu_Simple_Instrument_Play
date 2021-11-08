#include "fileInOut.h"

FileInOut::~FileInOut() {
    if (fout.is_open()) {
        fout.close();
        //cout << "fout close" << endl;
    }

    if (fin.is_open()) {
        fin.close();
        //cout << "fin close" << endl;
    }
}
void FileInOut::OpenFileOut(string fileName) {
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
void FileInOut::WriteFile(RecordNoteClass& record, string fileName) {
    //파일 입출력
    fout.open(fileName + ".txt");
    if (fout.fail()) {
        cout << "데이터를 불러오는데 실패하였습니다.";
    }
    else {
        for (int key = 0; key < NKEY; key++) {
            for (int i = 0; i < record.recordNote[key].size(); i++) {
                //무슨음이 몇초에 눌렸는지 저장
                //ex) 2:0.568  => "레" 0.568초에 눌림
                fout << key << ":" << record.recordNote[key][i] << endl;
            }
        }
    }
}
//데이터 불러오기
void FileInOut::ReadFile(RecordNoteClass& record, string fileName) {
    //이전에 불러오기를 실행해서 이미 파일이 열려있는
    //상태라면 파일을 닫고 다시 오픈
    if (fin.is_open()) {
        fin.close();
    }
    fin.open(fileName + ".txt");

    if (fin.fail()) {
        system("cls");
        cout << "저장된 데이터가 없습니다." << endl;
        Sleep(1000);
    }
    else {
        //txt파일로 저장된 데이터를 담는 변수
        string loadSaveFile;

        record.ResetVector();
        record.ResetInputTotalNum();
        //저장된 데이터가 끝이 날때까지 반복
        while (getline(fin, loadSaveFile)) {
            RoadRecordNote(record, loadSaveFile);
        }
        record.DivideInputTotalNum();

        system("cls");
        cout << "Success!!" << endl;
        Sleep(1000);
    }
}
void FileInOut::RoadRecordNote(RecordNoteClass& record, string loadSaveFile) {
    //무슨 음인지 파악
    int index = loadSaveFile.find(':');
    int key = stoi(loadSaveFile.substr(0, index));

    //몇 초에 입력되었는지 파악
    double time = stod(loadSaveFile.substr(index + 1));

    //악기 변경이 아닐 때
    if (key < 13) {
        //총 몇번의 입력이 있었는지 파악
        record.AddInputTotalNum();
    }


    //불러온 데이터 벡터에 저장
    record.recordNote[key].push_back(time);
}