#include "slab_3.h"

void printAllElements(const string& filename, bool binaryMode) {
    system("cls");
    Info2();

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка: Не удалось открыть файл " << filename << "\n\n";
        system("pause");
        return;
    }

    cout << "--- Содержимое файла " << filename << " ---\n\n";

    string str;
    int k = 1;
    bool isEmpty = true;

    while (file >> str) {
        isEmpty = false;
        if (binaryMode) {
            try {
                int decimalValue = stoi(str, nullptr, 2);
                cout << "[" << k << "] " << str << " (в десятичной: " << decimalValue << ")\n";
            }
            catch (const exception&) {
                cout << "[" << k << "] " << str << " (Ошибка дешифрации бинарного числа)\n";
            }
        }
        else {
            cout << "[" << k << "] " << str << "\n";
        }
        k++;
    }

    if (isEmpty) cout << "Файл пуст.\n";
    cout << "\n-----------------------------------\n\n";

    file.close();
    system("pause");
}

void printElementByIndex(const string& filename, bool binaryMode) {
    system("cls");
    Info2();
    int index;
    cout << "Введите индекс: ";
    if (!inputInt(index, false)) {
        emergencyExit();
        return;
    }

    ifstream file(filename);
    string str;
    int k = 1;
    bool found = false;

    while (file >> str) {
        if (k == index) {
            if (binaryMode) {
                cout << "\nЧисло: " << stoi(str, nullptr, 2) << " (bin: " << str << ")";
            }
            else {
                cout << "\nЧисло: " << str;
            }
            found = true;
            break;
        }
        k++;
    }

    if (!found) cout << "\nИндекс вне диапазона";
    cout << "\n\n";

    file.close();
    system("pause");
}

void changeElementByIndex(const string& filename, bool binaryMode) {
    system("cls");
    Info2();
    int index;
    cout << "Введите индекс: ";
    if (!inputInt(index, false)) {
        emergencyExit();
        return;
    }

    ifstream in(filename);
    ofstream out("temp.txt");
    string str;
    int k = 1;

    if (binaryMode) {
        string newValue;
        cout << "Введите новое бинарное число: ";
        if (!inputBinary(newValue)) {
            in.close(); out.close();
            emergencyExit();
            return;
        }
        while (in >> str) {
            out << (k == index ? newValue : str) << "\n";
            k++;
        }
    }
    else {
        float newValue;
        cout << "Введите новое число: ";
        if (!inputFloat(newValue, false)) {
            in.close(); out.close();
            emergencyExit();
            return;
        }
        while (in >> str) {
            if (k == index) out << newValue << "\n";
            else out << str << "\n";
            k++;
        }
    }

    in.close();
    out.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());

    cout << "\nЧисло изменено\n\n";
    system("pause");
}

void solveTask(const string& filename, bool binaryMode) {
    system("cls");
    Info2();
    cout << "Даны x1, x2,..., xn...\nОпределить количество xi с четными номерами, меньшими x1 и xmax/2.\n\n";

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка: Не удалось открыть файл " << filename << "\n\n";
        system("pause");
        return;
    }

    string str;
    float x;
    float first;
    float max;
    bool firstElement = true;

    while (file >> str) {
        x = binaryMode ? (float)stoi(str, nullptr, 2) : stof(str);
        if (firstElement) {
            first = x;
            max = x;
            firstElement = false;
        }
        if (x > max) max = x;
    }

    file.clear();
    file.seekg(0);

    int k = 1;
    int N = 0;
    cout << "Исходные данные: ";

    while (file >> str) {
        if (binaryMode) {
            x = (float)stoi(str, nullptr, 2);
            cout << str << " ";
        }
        else {
            x = stof(str);
            cout << x << " ";
        }

        if (k % 2 == 0 && x < first && x < max / 2) N++;
        k++;
    }

    if (firstElement) cout << "(файл пуст)";
    cout << "\n\nКоличество элементов: " << N << "\n\n";

    file.close();
    system("pause");
}

void fileSubMenu(const string& filename, bool binaryMode) {
    while (true) {
        system("cls");
        Info2();
        cout << "Текущий файл: " << filename << "\n\n";
        cout << "1 - Вывод числа по индексу\n";
        cout << "2 - Изменение числа по индексу\n";
        cout << "3 - Решение задачи\n";
        cout << "4 - Вывод всех элементов файла\n";
        cout << "ESC - Назад\n\n";

        char cm = _getch();
        if (cm == 27) break;

        switch (cm) {
        case '1': printElementByIndex(filename, binaryMode); break;
        case '2': changeElementByIndex(filename, binaryMode); break;
        case '3': solveTask(filename, binaryMode); break;
        case '4': printAllElements(filename, binaryMode); break;
        }
    }
}

void filterFile(const string& filename, bool binaryMode) {
    ifstream in(filename);
    ofstream out("temp.txt");

    if (!in.is_open()) {
        return;
    }

    string line;

    while (getline(in, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        bool valid = true;
        string token = "";
        bool hasDigit = false;
        bool hasDot = false;

        int n = (int)line.size();

        for (int i = 0; i <= n; i++) {
            char c;
            if (i < n) {
                c = line[i];
            }
            else {
                c = ' ';
            }
            if (c == ' ' || c == '\t') {
                if (!token.empty()) {
                    if (!hasDigit) {
                        valid = false;
                        break;
                    }
                    token = "";
                    hasDigit = false;
                    hasDot = false;
                }
                continue;
            }
            token += c;

            if (binaryMode) {
                if (c != '0' && c != '1') {
                    valid = false;
                    break;
                }
                hasDigit = true;
            }
            else {
                if (c >= '0' && c <= '9') {
                    hasDigit = true;
                }
                else if (c == '.' || c == ',') {
                    if (hasDot) {
                        valid = false;
                        break;
                    }
                    hasDot = true;
                }
                else if (c == '-') {
                    if (token.size() != 1) {
                        valid = false;
                        break;
                    }
                }
                else {
                    valid = false;
                    break;
                }
            }
        }

        if (valid && !line.empty()) {
            out << line << "\n";
        }
    }

    in.close();
    out.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());
}

int sLab_3() {

    filterFile("Data/small.txt", 0);
    filterFile("Data/small_bin.txt", 1);
    filterFile("Data/big.txt", 0);
    filterFile("Data/big_bin.txt", 1);

    while (true) {
        system("cls");
        Info2();

        cout << "Выберите файл:\n\n";
        cout << "1 - small.txt\n";
        cout << "2 - small_bin.txt\n";
        cout << "3 - big.txt\n";
        cout << "4 - big_bin.txt\n";
        cout << "ESC - выход\n\n";

        char ch = _getch();
        if (ch == 27) return 0;

        string filename;
        bool binaryMode = false;

        switch (ch) {
        case '1': filename = "Data/small.txt"; break;
        case '2': filename = "Data/small_bin.txt"; binaryMode = true; break;
        case '3': filename = "Data/big.txt"; break;
        case '4': filename = "Data/big_bin.txt"; binaryMode = true; break;
        default: continue;
        }


        fileSubMenu(filename, binaryMode);
    }

    return 0;
}