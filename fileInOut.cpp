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
//������ ����
void FileInOut::WriteFile(RecordNoteClass& record, string fileName) {
    //������ �����ϴ��� üũ�ϱ� ���� �ּҰ� ����
    string address = fileName + ".txt";
    const char* c = address.c_str();
    if (_access(c, 0) != 0) {
        //���� �������� ���� ���
        //���� ���� �̾ ���� ���
        outFileList.open("save_list.txt", ios::app);
    }

    //���� �����
    fout.open(fileName + ".txt");

    if (fout.fail() || outFileList.fail()) {
        cout << "�����͸� �����ϴµ� �����Ͽ����ϴ�.";
    }
    else {
        for (int key = 0; key < NKEY; key++) {
            for (int i = 0; i < record.recordNote[key].size(); i++) {
                //�������� ���ʿ� ���ȴ��� ����
                //ex) 2:0.568  => "��" 0.568�ʿ� ����
                fout << key << ":" << record.recordNote[key][i] << endl;
            }
        }
        outFileList << fileName << endl;
        fout.close();
        outFileList.close();
    }
}
//������ �ҷ�����
void FileInOut::ReadFile(RecordNoteClass& record, string fileName) {
    //������ �ҷ����⸦ �����ؼ� �̹� ������ �����ִ�
    //���¶�� ������ �ݰ� �ٽ� ����
    if (fin.is_open()) {
        fin.close();
    }
    fin.open(fileName + ".txt");

    if (fin.fail()) {
        system("cls");
        cout << "����� �����Ͱ� �����ϴ�." << endl;
        Sleep(1000);
    }
    else {
        //txt���Ϸ� ����� �����͸� ��� ����
        string loadSaveFile;

        record.ResetVector();
        record.ResetInputTotalNum();
        //����� �����Ͱ� ���� �������� �ݺ�
        while (getline(fin, loadSaveFile)) {
            RoadRecordNote(record, loadSaveFile);
        }
        record.DivideInputTotalNum();

        system("cls");
        cout << "Success!!" << endl;
        Sleep(1000);

        fin.close();
    }
}
void FileInOut::RoadRecordNote(RecordNoteClass& record, string loadSaveFile) {
    //���� ������ �ľ�
    int index = loadSaveFile.find(':');
    int key = stoi(loadSaveFile.substr(0, index));

    //�� �ʿ� �ԷµǾ����� �ľ�
    double time = stod(loadSaveFile.substr(index + 1));

    //�Ǳ� ������ �ƴ� ��
    if (key < 13) {
        //�� ����� �Է��� �־����� �ľ�
        record.AddInputTotalNum();
    }


    //�ҷ��� ������ ���Ϳ� ����
    record.recordNote[key].push_back(time);
}
void FileInOut::PrintFileList() {
    //������ �ҷ����⸦ �����ؼ� �̹� ������ �����ִ�
    //���¶�� ������ �ݰ� �ٽ� ����
    if (inFileList.is_open()) {
        inFileList.close();
    }
    inFileList.open("save_list.txt");

    //���̺� ����Ʈ�� �����Ұ�� ���
    if (!inFileList.fail()) {
        string fileName;
        while (!inFileList.eof()) {
            getline(inFileList, fileName);
            cout << fileName << endl;
        }
        inFileList.close();
    }
}
void FileInOut::DataDelete(string fileName) {
    //������ �����ϴ��� üũ�ϱ� ���� �ּҰ� ����
    string address = fileName + ".txt";
    const char* c = address.c_str();
    //���� ������ ���
    if (_access(c, 0) == 0) {
        
        //���� ����
        int result = remove(c);
        if (result == 0) {
            cout << "���� ���� ����" << endl;
        }
        else if (result == -1) {
            cout << "���� ���� ����" << endl;
        }

        //������ �ҷ����⸦ �����ؼ� �̹� ������ �����ִ�
        //���¶�� ������ �ݰ� �ٽ� ����
        if (inFileList.is_open()) {
            inFileList.close();
        }
        inFileList.open("save_list.txt");

        //�ӽ� ����Ʈ
        vector<string> tempList;

        //���̺� ����Ʈ�� �����Ұ�� ����
        if (!inFileList.fail()) {
            string list;
            while (!inFileList.eof()) {
                getline(inFileList, list);
                //������ ������ �ƴ� ��� ���Ϳ� �߰�
                if (list != fileName)
                    tempList.push_back(list);
            }
            inFileList.close();
        }

        //�ӽ� ����Ʈ�� Ȯ���ϱ� ���� iterator
        vector<string>::iterator it = tempList.begin();

        //���̺� ����Ʈ�� ��� ���� �ƴϰų� enter�� �Էµ� ���� �ƴ� ���
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
    }
    else {
        system("cls");
        cout << "�������� �ʴ� �������Դϴ�." << endl;
        Sleep(1000);
    }
}