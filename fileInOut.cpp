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
    //������ ������ �ʾ��� ��쿡�� �ڵ� ����
    if (!fout.is_open()) {
        //���� �����
        fout.open(".//test.txt");
        if (fout.fail()) {
            cout << "����";
        }
    }
}
//������ ����
void FileInOut::WriteFile(RecordNoteClass& record) {
    for (int key = 0; key < NKEY; key++) {
        for (int i = 0; i < record.recordNote[key].size(); i++) {
            //�������� ���ʿ� ���ȴ��� ����
            //ex) 2:0.568  => "��" 0.568�ʿ� ����
            fout << key << ":" << record.recordNote[key][i] << endl;
        }
    }
}
void FileInOut::ReadFile(RecordNoteClass& record) {
    //������ ������ �ʾ��� ��쿡�� �ڵ� ����
    if (!fin.is_open()) {
        fin.open(".//test.txt");
        if (fin.fail()) {
            cout << "����� �����Ͱ� �����ϴ�." << endl;
        }
        else {
            //txt���Ϸ� ����� �����͸� ��� ����
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
    //���� ������ �ľ�
    int index = loadSaveFile.find(':');
    int key = stoi(loadSaveFile.substr(0, index));

    //�� �ʿ� �ԷµǾ����� �ľ�
    double time = stod(loadSaveFile.substr(index + 1));

    //�� ����� �Է��� �־����� �ľ�
    record.AddInputTotalNum();

    //�ҷ��� ������ ���Ϳ� ����
    record.recordNote[key].push_back(time);
}