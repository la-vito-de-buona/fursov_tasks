#include "lab3.h"

int Lab3() {
    system("cls");
    Info1();

    cout << "Задание 3.2\nДаны массивы R1, ..., R7; d1, ..., d7 и число N. Построить новый массив S по формуле:\nSi = Ri/P * произведение элементов массива D, где если 1 < di < 2, то P = N - di, в противном случае P = 1/N.\n\n\n";

    int max_index, min_index;
    const int size = 7;
    float R[size]{};
    float d[size]{};
    float s[size]{};
    bool prz = false;


    cout << "Ввод данных:\nВведите N = ";
    float N = cin_cond("N = ", 0);

    cout << "\nМассив R:\n";
    COORD coord = GetCursorPosition();
    for (int i = 0; i < size; i++) {
        SetCursorPosition(coord.Y, coord.X);
        SPACEBACK(20);
        cout << "R[" << i + 1 << "] = ";
        while (!(cin >> R[i])) {
            cout << "Ошибка ввода!\n";
            cout << "Повторите ввод: "; SPACEBACK(20);
            ClearCin;
            prz = true;
        }
        if (prz) {
            SetCursorPosition(coord.Y + 1, 0);

            SPACEBACK(30);
            SetCursorPosition(coord.Y + 2, 0); SPACEBACK(30);
            prz = false;
        }
    }

    SetCursorPosition(coord.Y - 1, 0); SPACEBACK(30);
    SetCursorPosition(coord.Y, 0); SPACEBACK(30);
    SetCursorPosition(coord.Y - 1, 0);

    cout << "Массив d:\n";
    prz = false;
    for (int i = 0; i < size; i++) {
        float tmp;
        SetCursorPosition(coord.Y, coord.X);
        SPACEBACK(20);
        cout << "d[" << i + 1 << "] = ";
        while (true) {
            if (!(cin >> tmp)) {
                cout << "Ошибка ввода!\n";
                cout << "Повторите ввод: "; SPACEBACK(20);
                ClearCin;
                prz = true;
                continue;
            }
            if (N > 1 && N < 2 && tmp == N) {
                cout << "Ошибка ввода!\n";
                cout << "Повторите ввод: "; SPACEBACK(20);
                ClearCin;
                prz = true;
                continue;
            }
            break;
        }
        d[i] = tmp;

        if (prz) {
            SetCursorPosition(coord.Y + 1, 0); SPACEBACK(30);
            SetCursorPosition(coord.Y + 2, 0); SPACEBACK(30);
            prz = false;
        }
    }

    SetCursorPosition(coord.Y - 1, 0); SPACEBACK(30);
    SetCursorPosition(coord.Y, 0); SPACEBACK(30);
    SetCursorPosition(coord.Y - 1, 0);

    float P = 1;
    for (int j = 0; j < size; j++) P = P * d[j];

    for (int i = 0; i < size; i++) {
        float p;
        if (1 < d[i] and d[i] < 2) p = N - d[i];
        else p = 1 / N;
        s[i] = R[i] / p * P;
    }

    for (int i = 0; i < size; i++) {
        if (s[i] == arr_max(s, size)) max_index = i;
        else if (s[i] == arr_min(s, size)) min_index = i;
    }

    cout << "\n\nВведенные данные:\nN = " << N << "\nМассив R : { ";
    for (int i = 0; i < size; i++) {
        cout << R[i] << " ";
    }
    cout << "}";

    cout << "\nМассив d: { ";
    for (int i = 0; i < size; i++) {
        cout << d[i] << " ";
    }
    cout << "}";

    cout << "\nМассив s: { ";
    for (int i = 0; i < size; i++) {
        cout << s[i] << " ";
    }
    cout << "}";

    cout << "\n\nРезультат:\nКоличество элементов между максимальным и минимальным значениями нового массива s: " << abs(max_index - min_index - 1) << "\n\n";

    system("pause");
    return 0;
}