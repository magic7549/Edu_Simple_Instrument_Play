#include "view.h"

//�����ڸ� ���� ��� ����(�迭) �ʱ�ȭ
View::View() : instrumentText{
    "�׷��� �ǾƳ�", "�����Ʈ �ǾƳ�", "���� �׷��� �ǾƳ�", "ȫŰ��ũ �ǾƳ�", "���� �ǾƳ� 1", "���� �ǾƳ� 2", 
    "�������ڵ�", "Ŭ����", "ÿ����Ÿ","�۷��˽���","�����ڽ�","������","������","�Ƿ���",
    "Ʃ�� ��","���ø�","��ο�� ������","��Ŀ�ú� ������","�� ������","������ ������","ǳ��","���ڵ��",
    "�ϸ��ī","�ʰ� ���ڵ��","����ƽ ��Ÿ(���Ϸ� ��)","����ƽ ��Ÿ(�ݼ� ��)","���� ��Ÿ(����)","���� ��Ÿ(Ŭ��)","���� ��Ÿ(���Ұ�)","���� ��Ÿ(��������̺�)",
    "���� ��Ÿ(�����)","��Ÿ ����","����ƽ ���̽�","���̽� ��Ÿ(�հ���)","���̽� ��Ÿ(��ũ)","������ ���̽� ��Ÿ","���� ���̽� 1","���� ���̽� 2",
    "�Ž� ���̽� 1","�Ž� ���̽� 2","���̿ø�","��ö�","ÿ��","���� ���̽�","Ʈ������","��ġī��","����","���Ĵ�","���Ǳ� �ӻ�� 1",
    "���Ǳ� �ӻ�� 2","�Ž� ���Ǳ� 1","�Ž� ���Ǳ� 2","��Ҹ� ��~","��Ҹ� ��~","�Ž� ��Ҹ�","���ɽ�Ʈ�� ��Ʈ","Ʈ����","Ʈ����","Ʃ��",
    "��Ʈ Ʈ����","ȣ��","�ݰ� ����","�Ž� �ݰ� 1","�Ž� �ݰ� 2","������� ������","���� ������","�׳� ������","�ٸ��� ������",
    "������","�ױ۸��� ȣ��","�ټ�","Ŭ�󸮳�","���ݷ�","�÷�Ʈ","���ڴ�","���÷�Ʈ","�� �δ� �Ҹ�","������ġ","���Ķ�","��ī����",
    "���� 1 (������)","���� 2 (�����)","���� 3 (Į������)","���� 4 (ġ��)","���� 5 (í��)","���� 6 (��Ҹ�)","���� 7 (5��)","���� 8 (���̽� + ����)",
    "�е� 1 (��������)","�е� 2 (������)","�е� 3 (�����Ž�)","�е� 4 (��â)","�е� 5 (����)","�е� 6 (��Ż)","�е� 7 (�ı�)","�е� 8 (�����)",
    "����ȿ�� 1 (��)","����ȿ�� 2 (����Ʈ��)","����ȿ�� 3 (ũ������)","����ȿ�� 4 (������)","����ȿ�� 5 (����)","����ȿ�� 6 (���)","����ȿ�� 7 (�޾Ƹ�)","����ȿ�� 8 (��������)",
    "��Ÿ��","����","���̼�","����","Į����","��������","�ǵ�","������","��Ŭ ��","�ư��","��ƿ �巳","�����","�°�",
    "��ε� ��","�Ž� �巳","������ �ɹ���","��Ÿ ���� ������","�극�� ������","�غ�","���Ҹ�","��ȭ ��","�︮����","�ڼ�","�ѼҸ�"
} {
    //������ ���� �ڵ� �ۼ���
    x = 0, y = 0;
}
void View::ConsoleSetting() {
    system("mode con: cols=87 lines=50");  //â ũ�� ����
    system("color 00");     //��� �� ����
    system("title Composition");  //�ܼ�â Ÿ��Ʋ ����
}
void View::RemoveScrollbar() {
    //�ܼ� ��ũ�ѹ� ����
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(handle, &info);
    COORD new_size =
    {
        info.srWindow.Right - info.srWindow.Left + 1,
        info.srWindow.Bottom - info.srWindow.Top + 1
    };
    SetConsoleScreenBufferSize(handle, new_size);
}
void View::Piano() {
    system("cls");
    cout << "������  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  �� ��  ��  ��  ��  ��  ��       " << endl;
    cout << "������  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  �� ��  ��  ��  ��  ��  ��       " << endl;
    cout << "������  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  �� ��  ��  ��  ��  ��  ��       " << endl;
    cout << "������  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  �� ��  ��  ��  ��  ��  ��       " << endl;
    cout << "������  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  �� ��  ��  ��  ��  ��  ��       " << endl;
    cout << "��������������  ��  ��  ��  ��  ��  ��  ��  ��  �� ����������  ��  ��  ��       " << endl;
    cout << "������  ���Ѧ�  ���Ѧ�  ��  ���Ѧ�  ���Ѧ�  ���Ѧ� ��  ���Ѧ�  ���Ѧ�  ��       " << endl;
    cout << "������    ��������������    ����  ��    ��    ��    ��������������            " << endl;
    cout << "������    ��������������    ����  ��    ��    ��    ��������������            " << endl;
    cout << "������    ��������������    ����  ��    ��    ��    ��������������            " << endl;
    cout << "������������������������    ����  ��    ��    ��������������������            " << endl;
    cout << "�������ѤѦ��ѤѦ��ѤѦ��ѤѦ��ѤѦ��ѤѦ��ѤѦ��ѤѦ��ѤѦ��ѤѦ�            " << endl;
    cout << endl << endl << endl;
}
void View::DisplayInput(int key, bool isPush) {
    NowCursorPosition(x, y);
    switch (key)
    {
    case 0: //��
        Gotoxy(7, 10);
        break;
    case 1: //��#
        Gotoxy(8, 5);
        break;
    case 2: //��
        Gotoxy(12, 10);
        break;
    case 3: //��#
        Gotoxy(14, 5);
        break;
    case 4: //��
        Gotoxy(17, 10);
        break;
    case 5: //��
        Gotoxy(22, 10);
        break;
    case 6: //��#
        Gotoxy(23, 5);
        break;
    case 7: //��
        Gotoxy(27, 10);
        break;
    case 8: //��#
        Gotoxy(29, 5);
        break;
    case 9: //��
        Gotoxy(32, 10);
        break;
    case 10: //��#
        Gotoxy(35, 5);
        break;
    case 11: //��
        Gotoxy(37, 10);
        break;
    case 12: //��
        Gotoxy(42, 10);
        break;
    case 13: //��#
        Gotoxy(43, 5);
        break;
    case 14: //��
        Gotoxy(47, 10);
        break;
    case 15: //��#
        Gotoxy(49, 5);
        break;
    case 16: //��
        Gotoxy(52, 10);
        break;
    default:
        break;
    }
    if (isPush) {
        cout << "��";
    }
    else {
        cout << "��";
    }
    Gotoxy(0, 0);  //���� ��� �ǾƳ� �Ϻκ� ������
    Gotoxy(x, y);
}
void View::ShowDoReMi(BYTE key) {
    switch (key) {
    case 0:
        cout << "�� ";
        break;
    case 1:
        cout << "��# ";
        break;
    case 2:
        cout << "�� ";
        break;
    case 3:
        cout << "��# ";
        break;
    case 4:
        cout << "�� ";
        break;
    case 5:
        cout << "�� ";
        break;
    case 6:
        cout << "��# ";
        break;
    case 7:
        cout << "�� ";
        break;
    case 8:
        cout << "��# ";
        break;
    case 9:
        cout << "�� ";
        break;
    case 10:
        cout << "��# ";
        break;
    case 11:
        cout << "�� ";
        break;
    case 12:
        cout << "�� ";
        break;
    case 13:
        cout << "��# ";
        break;
    case 14:
        cout << "�� ";
        break;
    case 15:
        cout << "��# ";
        break;
    case 16:
        cout << "�� ";
        break;
    default:
        break;
    }
}
void View::Home() {
	system("cls");
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n " << endl;
    cout << "                                       ��Start��\n" << endl;
    cout << "                                    1. Free Play��\n" << endl;
    cout << "                                    2. Record��\n" << endl;
    cout << "                                    3. Save / Load��\n" << endl;
    cout << "                                    4. Exit��\n\n" << endl;
    cout << "                                    input number : ";
}
void View::Record_Select() {
    system("cls");
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n " << endl;
    cout << "                                    1. Record��\n" << endl;
    cout << "                                    2. Play Back��\n" << endl;
    cout << "                                    3. Reset��\n" << endl;
    cout << "                                    4. <--\n\n" << endl;
    cout << "                                    input number : ";
}
void View::Record() {
    system("cls");
    cout << "3..." << " ";
    Sleep(1000);
    cout << "2..." << " ";
    Sleep(1000);
    cout << "1..." << " ";
    Sleep(1000);
    cout << "����!" << endl;
    Sleep(300);
    system("cls");
}
bool View::Reset() {
    char choice;
    while (true)
    {
        system("cls");
        cout << "�����͸� �ʱ�ȭ �ϰڽ��ϱ�?" << endl;
        cout << "(Y / N)" << endl;

        cin >> choice;
        if (choice == 'y' || choice == 'Y')
            return true;
        else if (choice == 'n' || choice == 'N')
            return false;
        else {
            cout << "�Է��� �߸��Ǿ����ϴ�." << endl;
            Sleep(1000);
        }
    }
}
void View::FileRelation() {
    system("cls");
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n " << endl;
    cout << "                                   1. Data Save��\n" << endl;
    cout << "                                   2. Data Load��\n" << endl;
    cout << "                                   3. Data Delete��\n" << endl;
    cout << "                                   4. <--\n\n" << endl;
    cout << "                                   input number : ";
}

void View::Gotoxy(int x, int y) {
    //��ǥ ����
    COORD pos = { x,y };
    //Ŀ�� ����
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void View::NowCursorPosition(int& x, int& y) {
    //�ܼ� ���â�� ������ ��� ���ؼ� ������ ����ü
    CONSOLE_SCREEN_BUFFER_INFO presentCur;

    //���� Ŀ���� ��ġ ������ �����ϴ� �Լ�
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
    x = presentCur.dwCursorPosition.X;
    y = presentCur.dwCursorPosition.Y;
}
void View::ViewInstrument(int instrument) {
    //�Ǳ� ���� �迭 �����ϱ�
    NowCursorPosition(x, y);
    Gotoxy(0, 13);
    cout << "                                                 ";    //���� ���ڿ� ����� ����
    Gotoxy(0, 13);
    cout << "Instrument : " << instrumentText[instrument];
    Gotoxy(x, y);
}
void View::ViewMetronomeBPM(int bpm) {
    NowCursorPosition(x, y);
    Gotoxy(0, 14);
    cout << "                                                 ";    //���� ���ڿ� ����� ����
    Gotoxy(0, 14);
    cout << "��Ʈ�γ� BPM : " << bpm;
    Gotoxy(x, y);
}