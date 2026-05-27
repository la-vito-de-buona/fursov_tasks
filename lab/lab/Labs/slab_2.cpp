#include "slab_2.h"

int sLab_2() {
    system("cls");
    Info2();

    cout << "Даны x1, x2,..., xn...\nОпределить количество xi с четными номерами, меньшими x1 и xmax/2.\n\n";

    int size;
    cout << "Введите размер массива mass (не менее 2): ";
    if (!inputInt(size, true)) {
        return emergencyExit();
    }

    float* x = new float[size];
    int N = 0;

    cout << "Введите значения массива mas:\n";

    COORD coord = GetCursorPosition();
    bool prz = 0;
    for (int i = 0; i < size; i++) {
        SetCursorPosition(coord.Y, coord.X);
        SPACEBACK(20);
        cout << "mas[" << i + 1 << "] = ";
        if (!inputFloat(x[i], false)) {
            delete[]x;
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

    delete[]x;
    system("pause");

    return 0;
}