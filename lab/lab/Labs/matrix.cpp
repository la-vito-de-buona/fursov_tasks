#include "matrix.h"

int _MATRIX::InputMatrFromKb(int pindx, int pindy)
{
    printf("Введите данные матрицы %dx%d\n", MROW, MCOL);

    CONSOLE_SCREEN_BUFFER_INFO crd;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &crd);

    unsigned char ch = 0;
    char sText[64]{}, sTitle[64] = "Матрица";

    OutputMatrixGraf(sTitle, pindx, pindy);

    for (int r = 0; r < MROW; r++) {
        for (int c = 0; c < MCOL; c++) {
            int temp;
            SetCursorPosition(8, crd.dwCursorPosition.X);
            SPACEBACK(100);
            sprintf_s(sText, "Matr[%i][%i] = ", r + 1, c + 1);
            printf(sText);
            cin >> temp;
            if (cin.fail() || temp <= 0) {
                cout << " Ошибка! Введите положительное целое число.";
                ClearCin;
                ch = _getch();
                if (ch == 27) return -1;
                c--;
                continue;
            }
            nMatrix[r][c] = temp;
            OutputMatrixGraf(sTitle, pindx, pindy);
        }
    }
    return 0;
}

void _MATRIX::OutputMatrixGraf(std::string pstitle, int pindx, int pindy) {
    HWND hwnd = (HWND)GetStdHandle(STD_OUTPUT_HANDLE);
    HDC hdc = GetDC(GetConsoleWindow());

    CONSOLE_FONT_INFO conf{};
    GetCurrentConsoleFont(hwnd, false, &conf);
    CONSOLE_SCREEN_BUFFER_INFO cxy;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cxy);

    int indentY = (pindy < 0) ? conf.dwFontSize.Y * (cxy.dwCursorPosition.Y + 1) : pindy;
    int indentX = (pindx < 0) ? conf.dwFontSize.X * (cxy.dwCursorPosition.X + 5) : pindx;

    HFONT hfont = CreateFontA(34, 0, 0, 0, FW_NORMAL, false, false, false, RUSSIAN_CHARSET,
        OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH,
        "Times New Roman");
    HFONT holdfont = (HFONT)SelectObject(hdc, hfont);
    SetTextColor(hdc, RGB(0, 255, 255));
    SetBkColor(hdc, RGB(0, 0, 0));
    TextOutA(hdc, indentX, indentY, pstitle.c_str(), pstitle.length());
    SelectObject(hdc, holdfont);
    DeleteObject(hfont);

    indentY += 34;

    HPEN hpen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
    LOGBRUSH lgbr{ PS_SOLID, RGB(54,54,54), 0 };
    HBRUSH hbrush = CreateBrushIndirect(&lgbr);
    HANDLE oldbrush = SelectObject(hdc, hbrush),
        oldpen = SelectObject(hdc, hpen);
    Rectangle(hdc, indentX, indentY, indentX + (MCOL + 1) * 5 * conf.dwFontSize.X,
        indentY + (2 * conf.dwFontSize.Y) * (MROW + 1));
    char txt[30]{};
    SetBkColor(hdc, RGB(54, 54, 54));
    for (int i = 0; i <= MCOL; i++) {
        int nx3 = indentX + (i + 1) * 5 * conf.dwFontSize.X,
            ny = indentY;
        int nx = indentX;
        MoveToEx(hdc, nx3, ny, NULL);
        LineTo(hdc, nx3, ny + (2 * conf.dwFontSize.Y) * (MROW + 1));
        sprintf_s(txt, "C%d", i + 1);
        SIZE sz{};
        GetTextExtentPointA(hdc, txt, strlen(txt), &sz);
        SetTextColor(hdc, RGB(0, 255, 255));
        if ((i + 1) <= MCOL)
            TextOutA(hdc, nx + (i + 1) * 5 * conf.dwFontSize.X + (5 * conf.dwFontSize.X - sz.cx) / 2,
                ny + (2 * conf.dwFontSize.Y - sz.cy) / 2, txt, strlen(txt));
    }
    for (int i = 0; i < MROW; i++) {
        SIZE sz{};
        sprintf_s(txt, "R%d", i + 1);
        GetTextExtentPointA(hdc, txt, strlen(txt), &sz);
        int nx = indentX + (MCOL + 1) * 5 * conf.dwFontSize.X,
            nx2 = indentX + (MCOL + 1) * 5 * conf.dwFontSize.X,
            ny = indentY,
            nY2 = indentY + (i + 1) * 2 * conf.dwFontSize.Y + (2 * conf.dwFontSize.Y - sz.cy) / 2;
        MoveToEx(hdc, indentX, indentY + (i + 1) * 2 * conf.dwFontSize.Y, NULL);
        LineTo(hdc, nx2, indentY + (i + 1) * 2 * conf.dwFontSize.Y);
        SetTextColor(hdc, RGB(0, 255, 255));
        if ((i + 1) <= MROW)
            TextOutA(hdc, indentX + (5 * conf.dwFontSize.X - sz.cx) / 2,
                nY2, txt, strlen(txt));
        char txt[30]{};
        for (int j = 0; j < MCOL; j++) {
            int nx = indentX + (j + 1) * 5 * conf.dwFontSize.X;
            sprintf_s(txt, "%5.1f", nMatrix[i][j]);
            SIZE sz{};
            GetTextExtentPoint32A(hdc, txt, strlen(txt), &sz);
            SetTextColor(hdc, RGB(255, 255, 255));
            TextOutA(hdc, nx + (5 * conf.dwFontSize.X - sz.cx) / 2, ny + (i + 1) * (conf.dwFontSize.Y * 2) + (2 * conf.dwFontSize.Y - sz.cy) / 2, txt, strlen(txt));
        }
    }
}