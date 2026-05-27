#include "lab2_1.h"
int Lab2_1() {
    system("cls");
    Info1();

    cout << "Задание 2.1\nДаны переменные d, f, g, h. Определить:\n";

    cout << "C = min{d, f, g, h} + max{d, f, g, h};\n";
    cout << "Если C < 0.7, то D = |d * f| - h\n";
    cout << "Если 0.7 <= C < 1, то D = sqrt(2C) + d\n";
    cout << "Если 1 <= C <= 5, то D = g^2\n";
    cout << "Если C >= 5, то h*sqrt(C)\n\n\n";
     
    float d, f, g, h;
    cout << "Ввод данных:\n";
    cout << "Введите d = "; d = cin_cond("d = ");
    cout << "Введите f = "; f = cin_cond("f = ");
    cout << "Введите g = "; g = cin_cond("g = ");
    cout << "Введите h = "; h = cin_cond("h = ");
    cout << "\nВведенные данные:\nd = " << d << ", f = " << f << ", g = " << g << ", h = " << h << ".\n\nРезультат:\n";

    float C = minn(d, f, g, h) + maxx(d, f, g, h);
    float D;
    if (C < 0.7) D = abs(d * f) - h;
    else if (0.7 <= C and C < 1) D = sqrt(2 * C) + d;
    else if (1 <= C and C < 5) D = g * g;
    else D = h * sqrt(C);
    cout << "C = " << C << endl << "D = " << D << "\n\n";
    system("pause");
    return 0;
}