#include "view.h"
using namespace std;

View::View() {
    *(instrumentText) = "그랜드 피아노";
    *(instrumentText + 1) = "브라이트 피아노";
    *(instrumentText + 2) = "그랜드 피아노";
    *(instrumentText + 3) = "브라이트 피아노";
    *(instrumentText + 4) = "전자 그랜드 피아노";
    *(instrumentText + 5) = "홍키통크 피아노";
    *(instrumentText + 6) = "전자 피아노 1";
    *(instrumentText + 7) = "전자 피아노 2";
    *(instrumentText + 8) = "하프시코드";
    *(instrumentText + 9) = "클라비넷";
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
	//커서 이동 시키기
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
    cout << "시작!" << endl;
    Sleep(300);
    system("cls");
    cout << "Finish : ESC" << endl;
}
bool View::Reset() {
    char choice;
    while (true)
    {
        system("cls");
        cout << "데이터를 초기화 하시겠습니까?" << endl;
        cout << "(Y / N)" << endl;

        cin >> choice;
        if (choice == 'y' || choice == 'Y')
            return true;
        else if (choice == 'n' || choice == 'N')
            return false;
        else {
            cout << "입력이 잘못되었습니다." << endl;
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
        cout << "도 ";
        break;
    case 1:
        cout << "도# ";
        break;
    case 2:
        cout << "레 ";
        break;
    case 3:
        cout << "레# ";
        break;
    case 4:
        cout << "미 ";
        break;
    case 5:
        cout << "파 ";
        break;
    case 6:
        cout << "파# ";
        break;
    case 7:
        cout << "솔 ";
        break;
    case 8:
        cout << "솔# ";
        break;
    case 9:
        cout << "라 ";
        break;
    case 10:
        cout << "라# ";
        break;
    case 11:
        cout << "시 ";
        break;
    case 12:
        cout << "도 ";
        break;
    default:
        break;
    }
}
void View::RenderImage(int x, int y) {
    //콘솔에서 사용하는 창 핸들을 검색하여 저장
    HWND hWnd = GetConsoleWindow();

    HBITMAP hImage, hOldBitmap;

    HDC hDC = GetDC(hWnd);
    HDC hMemDC = CreateCompatibleDC(hDC);

    //비트맵 이미지 불러와서 저장
    hImage = (HBITMAP)LoadImage(NULL, TEXT("piano.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

    hOldBitmap = (HBITMAP)SelectObject(hMemDC, hImage);
    //비트맵 이미지 사이즈 및 좌표 설정
    BitBlt(hDC, x, y, 600, 300, hMemDC, 0, 0, SRCCOPY);

    SelectObject(hMemDC, hOldBitmap);
    DeleteObject(hImage);
    DeleteDC(hMemDC);
    ReleaseDC(hWnd, hDC);
}
void View::Gotoxy(int x, int y) {
    //좌표 설정
    COORD pos = { x,y };
    //커서 설정
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void View::NowCursorPosition(int& x, int& y) {
    //콘솔 출력창의 정보를 담기 위해서 정의한 구조체
    CONSOLE_SCREEN_BUFFER_INFO presentCur;

    //현재 커서의 위치 정보를 저장하는 함수
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
    x = presentCur.dwCursorPosition.X;
    y = presentCur.dwCursorPosition.Y;
}
void View::RemoveScrollbar() {
    //콘솔 스크롤바 제거
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
    //악기 종류 배열 생성하기
    int x, y;
    NowCursorPosition(x, y);
    Gotoxy(0, 18);
    cout << "                          ";    //이전 문자열 지우기 위함
    Gotoxy(0, 18);
    cout << instrumentText[instrument];
    Gotoxy(x, y);
}