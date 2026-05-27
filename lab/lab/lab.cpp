#include "header.h"

int main() {
    SetConsoleTitle(L"Учебная программа по дисциплине \"Информатика\"");
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    unsigned char ch = 0;
    do {
        system("cls");
        cout << "Меню программы\n";
        cout << "1 - Первый семестр\n";
        cout << "2 - Второй семестр\n";
        cout << "ESC для выхода из программы\n\n";

        ch = _getch();
        switch (ch) {
        case '1': firstMenu(); break;
        case '2': secondMenu(); break;
        case 27: break;
        }
    } while (ch != 27);
    return 0;
}