#include "slab_1.h"

int sLab_1() {
    system("cls");
    Info2();

    cout << "Даны x1, x2,..., x8...\nОпределить количество xi с четными номерами, меньшими x1 и xmax/2.\n\n";

    const int size = 8;
    float x[size];
    int N = 0;

    cout << "Введите значения массива mas:\n";

    COORD coord = GetCursorPosition();
    bool prz = 0;
    for (int i = 0; i < size; i++) {
        SetCursorPosition(coord.Y, coord.X);
        SPACEBACK(20);
        cout << "mas[" << i + 1 << "] = ";
        if (!inputFloat(x[i], false)) {
            return emergencyExit();
        }
    }

    cout << "\nПолученный массив: { ";
    for (int i = 0; i < size; i++) {
        cout << x[i] << " ";
    }
    cout << "}\n\n";

    float xmax = arr_max(x, size);

    for (int i = 0; i < size; i++) {
        if ((i + 1) % 2 == 0 && x[i] < x[0] && x[i] < xmax / 2)
            N++;
    }

    cout << "Итого " << N << " элементов, удовлетворяющих условию.\n\n";
    system("pause");

    return 0;
}