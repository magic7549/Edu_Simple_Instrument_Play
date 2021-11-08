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
void FileInOut::WriteFile(RecordNoteClass& record, string fileName) {
    //���� �����
    fout.open(fileName + ".txt");
    if (fout.fail()) {
        cout << "�����͸� �ҷ����µ� �����Ͽ����ϴ�.";
    }
    else {
        for (int key = 0; key < NKEY; key++) {
            for (int i = 0; i < record.recordNote[key].size(); i++) {
                //�������� ���ʿ� ���ȴ��� ����
                //ex) 2:0.568  => "��" 0.568�ʿ� ����
                fout << key << ":" << record.recordNote[key][i] << endl;
            }
        }
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