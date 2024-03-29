#include "fileInOut.h"

FileInOut::~FileInOut() {
    if (fout.is_open()) {
        fout.close();
    }
    if (outFileList.is_open()) {
        outFileList.close();
    }
    if (fin.is_open()) {
        fin.close();
    }
    if (inFileList.is_open()) {
        inFileList.close();
    }
}
//데이터 저장
void FileInOut::WriteFile(RecordNoteClass& record, string fileName, int isBase) {
    //파일이 존재하는지 체크하기 위해 주소값 설정
    string address = fileName + ".txt";
    const char* c = address.c_str();
    if (_access(c, 0) != 0) {
        //파일 존재하지 않을 경우
        //파일 끝에 이어서 쓰기 모드
        outFileList.open("save_list.txt", ios::app);

        //여러 개의 트랙이 저장되더라도 세이브 리스트에는
        //하나의 파일 이름만 저장
        if (isBase >= 0) {
            outFileList << fileName << endl;
        }
        outFileList.close();
    }

    //파일 입출력
    fout.open(fileName + ".txt");
    if (fout.fail()) {
        cout << "데이터를 저장하는데 실패하였습니다.";
        Sleep(333);
    }
    else {
        //악기 종류 저장
        fout << record.Return_Instrument() << endl;

        for (int key = 0; key < NKEY; key++) {
            for (int i = 0; i < (int)record.recordNote[key].size(); i++) {
                //무슨음이 몇초에 눌렸는지 저장
                //ex) 2:0.568  => "레" 0.568초에 눌림
                fout << key << ":" << record.recordNote[key][i] << endl;
            }
        }
        fout.close();

        system("cls");
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n " << endl;
        cout << "                                저장을 완료하였습니다." << endl;
        Sleep(333);
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
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n " << endl;
        cout << "                                저장된 데이터가 없습니다." << endl;
        Sleep(333);
    }
    else {
        //txt파일로 저장된 데이터를 담는 변수
        string loadSaveFile;

        record.ResetVector();
        record.ResetInputTotalNum();

        //악기 종류 불러오기
        getline(fin, loadSaveFile);
        if (loadSaveFile != "") {
            record.Set_Instrument(stoi(loadSaveFile));

            //저장된 데이터가 끝이 날때까지 반복
            while (getline(fin, loadSaveFile)) {
                RoadRecordNote(record, loadSaveFile);
            }
            record.DivideInputTotalNum();
        }

        system("cls");
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n " << endl;
        cout << "                         데이터를 불러오는데 성공하였습니다." << endl;
        Sleep(333);

        fin.close();
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
void FileInOut::PrintFileList() {
    //이전에 불러오기를 실행해서 이미 파일이 열려있는
    //상태라면 파일을 닫고 다시 오픈
    if (inFileList.is_open()) {
        inFileList.close();
    }
    inFileList.open("save_list.txt");

    //세이브 리스트가 존재할경우 출력
    if (!inFileList.fail()) {
        string fileName;
        while (!inFileList.eof()) {
            getline(inFileList, fileName);
            cout << "                               " << fileName << endl;
        }
        inFileList.close();
    }
}
void FileInOut::DataDelete(string fileName) {
    //파일이 존재하는지 체크하기 위해 주소값 설정
    string address = fileName + ".txt";
    const char* c = address.c_str();
    //파일 존재할 경우
    if (_access(c, 0) == 0) {
        
        //파일 삭제
        int result = remove(c);
        if (result == 0) {
            system("cls");
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n " << endl;
            cout << "                                    파일 삭제 성공" << endl;
            Sleep(1000);
        }
        else if (result == -1) {
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n " << endl;
            cout << "                                    파일 삭제 실패" << endl;
        }

        //이전에 불러오기를 실행해서 이미 파일이 열려있는
        //상태라면 파일을 닫고 다시 오픈
        if (inFileList.is_open()) {
            inFileList.close();
        }
        inFileList.open("save_list.txt");

        //임시 리스트
        vector<string> tempList;

        //세이브 리스트가 존재할경우 실행
        if (!inFileList.fail()) {
            string list;
            while (!inFileList.eof()) {
                getline(inFileList, list);
                //삭제할 파일이 아닐 경우 벡터에 추가
                if (list != fileName)
                    tempList.push_back(list);
            }
            inFileList.close();
        }

        //임시 리스트를 확인하기 위한 iterator
        vector<string>::iterator it = tempList.begin();

        //세이브 리스트를 열어서 끝이 아니거나 enter만 입력된 줄이 아닐 경우
        outFileList.open("save_list.txt");
        if (!outFileList.fail()) {
            while (it != tempList.end()) {
                if (*it != "\0") {
                    outFileList << *it << endl;
                }
                it++;
            }
            outFileList.close();
        }

        //나머지 트랙 파일도 삭제
        address = fileName + "_1.txt";
        c = address.c_str();
        remove(c);

        address = fileName + "_2.txt";
        c = address.c_str();
        remove(c);
    }
    else {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n " << endl;
        cout << "                                존재하지 않는 데이터입니다." << endl;
        Sleep(1000);
    }
}