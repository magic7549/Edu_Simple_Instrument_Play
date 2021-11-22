#include "view.h"

//생성자를 통해 멤버 변수(배열) 초기화
View::View() : instrumentText{
    "그랜드 피아노", "브라이트 피아노", "전자 그랜드 피아노", "홍키통크 피아노", "전자 피아노 1", "전자 피아노 2", 
    "하프시코드", "클라비넷", "첼레스타","글로켄슈필","뮤직박스","비브라폰","마림바","실로폰",
    "튜블러 벨","덜시머","드로우바 오르간","퍼커시브 오르간","록 오르간","파이프 오르간","풍금","아코디언",
    "하모니카","탱고 아코디언","어쿠스틱 기타(나일론 줄)","어쿠스틱 기타(금속 줄)","전기 기타(재즈)","전기 기타(클린)","전기 기타(음소거)","전기 기타(오버드라이브)",
    "전기 기타(디스토션)","기타 배음","어쿠스틱 베이스","베이스 기타(손가락)","베이스 기타(피크)","무프렛 베이스 기타","슬랩 베이스 1","슬랩 베이스 2",
    "신스 베이스 1","신스 베이스 2","바이올린","비올라","첼로","더블 베이스","트레몰로","피치카토","하프","팀파니","현악기 앙상블 1",
    "현악기 앙상블 2","신스 현악기 1","신스 현악기 2","목소리 아~","목소리 오~","신스 목소리","오케스트라 히트","트럼펫","트럼본","튜바",
    "뮤트 트럼펫","호른","금관 섹션","신스 금관 1","신스 금관 2","소프라노 색소폰","알토 색소폰","테너 색소폰","바리톤 색소폰",
    "오보에","잉글리시 호른","바순","클라리넷","피콜로","플루트","리코더","팬플루트","병 부는 소리","샤쿠하치","휘파람","오카리나",
    "리드 1 (구형파)","리드 2 (톱니파)","리드 3 (칼리오페)","리드 4 (치프)","리드 5 (챠랑)","리드 6 (목소리)","리드 7 (5도)","리드 8 (베이스 + 리드)",
    "패드 1 (뉴에이지)","패드 2 (따뜻한)","패드 3 (폴리신스)","패드 4 (합창)","패드 5 (굽은)","패드 6 (메탈)","패드 7 (후광)","패드 8 (쓸어내림)",
    "음향효과 1 (비)","음향효과 2 (사운드트랙)","음향효과 3 (크리스털)","음향효과 4 (분위기)","음향효과 5 (밝음)","음향효과 6 (고블린)","음향효과 7 (메아리)","음향효과 8 (사이파이)",
    "시타르","밴조","샤미센","고토","칼림바","백파이프","피들","샤나이","팅클 벨","아고고","스틸 드럼","우드블록","태고",
    "멜로딕 톰","신스 드럼","역방향 심벌즈","기타 프렛 노이즈","브레스 노이즈","해변","새소리","전화 벨","헬리콥터","박수","총소리"
} {
    //생성자 내부 코드 작성란
    x = 0, y = 0;
}
void View::ConsoleSetting() {
    system("mode con: cols=87 lines=50");  //창 크기 변경
    system("color 00");     //배경 색 설정
    system("title Composition");  //콘솔창 타이틀 설정
}
void View::Piano() {
    system("cls");
    cout << "　　│  │  │  │  │  │  │  │  │  │  │  │ │       " << endl;
    cout << "　　│  │  │  │  │  │  │  │  │  │  │  │ │       " << endl;
    cout << "　　│  │  │  │  │  │  │  │  │  │  │  │ │       " << endl;
    cout << "　　│  │  │  │  │  │  │  │  │  │  │  │ │       " << endl;
    cout << "　　│  │  │  │  │  │  │  │  │  │  │  │ │       " << endl;
    cout << "　　│　│　│  │  │  │  │  │  │  │  │  │ │       " << endl;
    cout << "　　│  └ㅡ┘  └ㅡ┘  │  └ㅡ┘  └ㅡ┘  └ㅡ┘ │       " << endl;
    cout << "　　│    │　　│　　│    │　  │    │    │            " << endl;
    cout << "　　│    │　　│　　│    │　  │    │    │            " << endl;
    cout << "　　│    │　　│　　│    │　  │    │    │            " << endl;
    cout << "　　│　　│　　│　　│    │　  │    │    │            " << endl;
    cout << "　　└ㅡㅡ┴ㅡㅡ┴ㅡㅡ┴ㅡㅡ┴ㅡㅡ┴ㅡㅡ┴ㅡㅡ┘            " << endl;
    cout << endl << endl << endl;
}
void View::DisplayInput(int key, bool isPush) {
    NowCursorPosition(x, y);
    switch (key)
    {
    case 0: //도
        Gotoxy(7, 10);
        break;
    case 1: //도#
        Gotoxy(8, 5);
        break;
    case 2: //레
        Gotoxy(12, 10);
        break;
    case 3: //레#
        Gotoxy(14, 5);
        break;
    case 4: //미
        Gotoxy(17, 10);
        break;
    case 5: //파
        Gotoxy(22, 10);
        break;
    case 6: //파#
        Gotoxy(23, 5);
        break;
    case 7: //솔
        Gotoxy(27, 10);
        break;
    case 8: //솔#
        Gotoxy(29, 5);
        break;
    case 9: //라
        Gotoxy(32, 10);
        break;
    case 10: //라#
        Gotoxy(35, 5);
        break;
    case 11: //시
        Gotoxy(37, 10);
        break;
    case 12: //도
        Gotoxy(44, 10);
        break;
    default:
        break;
    }
    if (isPush) {
        cout << "★";
    }
    else {
        cout << "　";
    }
    Gotoxy(0, 0);  //없을 경우 피아노 일부분 지워짐
    Gotoxy(x, y);
}
void View::Home() {
	system("cls");

    cout << "Start" << endl;
	cout << "1. Free Play" << endl;
	cout << "2. Record" << endl;
	cout << "3. Save / Load" << endl;
	cout << "4. Exit" << endl;
    cout << "input number : ";
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
}
bool View::Reset() {
    char choice;
    while (true)
    {
        system("cls");
        cout << "데이터를 초기화 하겠습니까?" << endl;
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
    cout << "3. Data Delete" << endl;
    cout << "4. <--" << endl;
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
    BitBlt(hDC, x, y, 692, 430, hMemDC, 0, 0, SRCCOPY);

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
    NowCursorPosition(x, y);
    Gotoxy(0, 13);
    cout << "                                                 ";    //이전 문자열 지우기 위함
    Gotoxy(0, 13);
    cout << "Instrument : " << instrumentText[instrument];
    Gotoxy(x, y);
}
void View::ViewMetronomeBPM(int bpm) {
    NowCursorPosition(x, y);
    Gotoxy(0, 14);
    cout << "                                                 ";    //이전 문자열 지우기 위함
    Gotoxy(0, 14);
    cout << "메트로놈 BPM : " << bpm;
    Gotoxy(x, y);
}