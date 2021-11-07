#include "view.h"
using namespace std;

View::View() {
    *(instrumentText) = "�׷��� �ǾƳ�";
    *(instrumentText + 1) = "�����Ʈ �ǾƳ�";
    *(instrumentText + 2) = "�׷��� �ǾƳ�";
    *(instrumentText + 3) = "�����Ʈ �ǾƳ�";
    *(instrumentText + 4) = "���� �׷��� �ǾƳ�";
    *(instrumentText + 5) = "ȫŰ��ũ �ǾƳ�";
    *(instrumentText + 6) = "���� �ǾƳ� 1";
    *(instrumentText + 7) = "���� �ǾƳ� 2";
    *(instrumentText + 8) = "�������ڵ�";
    *(instrumentText + 9) = "Ŭ����";
}
void View::Home() {
	system("cls");
	cout << "1. Free Play" << endl;
	cout << "2. Record" << endl;
	cout << "3. Save / Load" << endl;
	cout << "4. Exit" << endl;
    cout << "input number : ";
}
void View::Free_Play() {
	system("cls");
	//Ŀ�� �̵� ��Ű��
    Gotoxy(0, 20);
}
void View::Record_Select() {
    system("cls");
    cout << "1. Record" << endl;
    cout << "2. Play Back" << endl;
    cout << "3. Reset" << endl;
    cout << "4. <--" << endl;
    cout << "input number : ";
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
    cout << "Finish : ESC" << endl;
}
bool View::Reset() {
    char choice;
    while (true)
    {
        system("cls");
        cout << "�����͸� �ʱ�ȭ �Ͻðڽ��ϱ�?" << endl;
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
    cout << "1. Data Save" << endl;
    cout << "2. Data Load" << endl;
    cout << "3. <--" << endl;
    cout << "input number : ";
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
    default:
        break;
    }
}
void View::RenderImage(int x, int y) {
    //�ֿܼ��� ����ϴ� â �ڵ��� �˻��Ͽ� ����
    HWND hWnd = GetConsoleWindow();

    HBITMAP hImage, hOldBitmap;

    HDC hDC = GetDC(hWnd);
    HDC hMemDC = CreateCompatibleDC(hDC);

    //��Ʈ�� �̹��� �ҷ��ͼ� ����
    hImage = (HBITMAP)LoadImage(NULL, TEXT("piano.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

    hOldBitmap = (HBITMAP)SelectObject(hMemDC, hImage);
    //��Ʈ�� �̹��� ������ �� ��ǥ ����
    BitBlt(hDC, x, y, 600, 300, hMemDC, 0, 0, SRCCOPY);

    SelectObject(hMemDC, hOldBitmap);
    DeleteObject(hImage);
    DeleteDC(hMemDC);
    ReleaseDC(hWnd, hDC);
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
void View::ViewInstrument(int instrument) {
    //�Ǳ� ���� �迭 �����ϱ�
    int x, y;
    NowCursorPosition(x, y);
    Gotoxy(0, 18);
    cout << "                          ";    //���� ���ڿ� ����� ����
    Gotoxy(0, 18);
    cout << instrumentText[instrument];
    Gotoxy(x, y);
}