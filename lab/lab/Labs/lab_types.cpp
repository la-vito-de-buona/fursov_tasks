#include "lab_types.h"

int Lab_Types() {
    system("cls");
    Info2();

    cout << "Даны переменные a, b, c, d типов byte, short, int, long long соответственно. \nВывести информацию о каждом числе: десятичное и шестнадцатеричное представление, занимаемая память в байтах,\nстаршая и младшая половина в шестнадцатеричном виде, результат обмена старшей и младшей половины.\n\n";

    unsigned char a = 45;
    unsigned short b = 432165;
    unsigned int c = 543129035433;
    unsigned long long d = 6085492830948123;

    printf("Информация о числах:\n");
    printf("byte: %d(10-ная c.c.), %x(16-ная с.с.), память - %dбайт, High - %x, Low - %x, Swap - %x\n\n", a, a, sizeof(a), Hi(a), Lo(a), Swap(a));
    printf("short: %d(10-ная c.c.), %x(16-ная с.с.), память - %dбайт, High - %x, Low  - %x, Swap - %x\n\n", b, b, sizeof(b), Hi(b), Lo(b), Swap(b));
    printf("int: %d(10-ная c.c.), %x(16-ная с.с.), память - %dбайт, High - %x, Low  - %x, Swap - %x\n\n", c, c, sizeof(c), Hi(c), Lo(c), Swap(c));
    printf("long long: %llu(10-ная c.c.), %llx(16-ная с.с.), память - %dбайт, High - %llx, Low  - %llx, Swap - %llx\n\n", d, d, sizeof(d), Hi(d), Lo(d), Swap(d));


    system("pause");
    return 0;
}