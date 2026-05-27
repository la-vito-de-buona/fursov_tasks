#include "maska.h"

int Lab_Maska() {
    system("cls");
    Info2();
    cout << "ƒан массив целочисленных данных (short), заполненный случайными числами.\n»з этих чисел вывести на экран те, у которых биты в позици€х 3, 5, 7 наход€тс€ а состо€нии единицы.\n\n";
    cout << "ћаска: 84(дес€тичный формат) / 54(шестандцатеричный формат) / 0101 0100(двоичный формат).\n\n";

    const int size = 20;
    short mas[size]{}, maska = 0x54;

    mt19937 gen(std::random_device{}());
    uniform_int_distribution<int> dist(500, 32000);

    for (int i = 0; i < size; i++) {
        mas[i] = static_cast<short>(dist(gen));
    }
    cout << "\n»сходный массив:\n{ ";
    for (int i = 0; i < size; i++) {
        cout << mas[i] << " ";
    }
    cout << "}\n\n";

    cout << "„исла удволетвор€ющие условию (позици€ в массиве и значение):\n";
    int n = false;
    for (int i = 0; i < size; i++) {
        if ((mas[i] & maska) == maska) {
            printf("mas[%d] = %d\n", i + 1, mas[i]);
            n++;
        }
    }
    if (n == 0) cout << "“акие числа отстутствуют";
    cout << "\n\n";

    system("pause");
    return 0;
}