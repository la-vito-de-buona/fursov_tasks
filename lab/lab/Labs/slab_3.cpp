#include "slab_3.h"

void filterFileTxt(const string& filename) {
    ifstream in(filename);
    ofstream out("temp.txt");

    if (!in.is_open() || !out.is_open()) {
        return;
    }

    string line;

    while (getline(in, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        if (line.empty()) continue;

        bool hasDigit = false;
        bool hasDot = false;
        bool wroteSomething = false;

        for (size_t i = 0; i < line.size(); i++) {
            char c = line[i];

            if (c >= '0' && c <= '9') {
                out << c;
                hasDigit = true;
                wroteSomething = true;
            }
            else if (c == '-' || c == '+') {
                if (i == 0) {
                    out << c;
                    wroteSomething = true;
                }
                else {
                    break;
                }
            }
            else if (c == '.' || c == ',') {
                if (!hasDot) {
                    out << '.';
                    hasDot = true;
                    wroteSomething = true;
                }
                else {
                    break;
                }
            }
            else {
                break;
            }
        }

        if (wroteSomething) {
            if (hasDigit) {
                out << "\n";
            }
        }
    }

    in.close();
    out.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());
}

int CreateBinFile() {
    system("cls");
    cout << "=== Создание файла .bin===\n\n";

    string fileName;

    while (true) {
        string name;
        cout << "Введите название файла: ";
        if (!inputString(name)) {
            emergencyExit();
            return 0;
        }

        fileName = name + ".bin";

        ifstream checkFile(fileName, ios::binary);
        if (checkFile.is_open()) {
            checkFile.close();

            cout << "\nФайл \"" << fileName << "\" уже существует!\n";
            cout << "Выберите действие:\n";
            cout << "1 - Перезаписать существующий файл\n";
            cout << "2 - Ввести другое название\n";
            cout << "ESC - выход\n";
            cout << "Ваш выбор: ";

            char choice = 0;
            cin >> choice;

            if (choice == '1') break;
            else if (choice == '2') {
                cout << endl;
                continue;
            }
            else {
                cout << "\nСоздание файла отменено!\n";
                system("pause");
                return 0;
            }
        }
        else break;
    }

    ClearCin;

    cout << "\nВведите числа через пробел в одну строку и нажмите Enter:\nВвод: ";
    string inputText;
    if (!inputString(inputText)) {
        emergencyExit();
        return 0;
    }

    int capacity = 4;
    int count = 0;
    double* arr = new double[capacity];

    stringstream ss(inputText);
    double num;

    while (ss >> num) {
        if (count >= capacity) {
            capacity *= 2;
            double* newArr = new double[capacity];
            for (int i = 0; i < count; i++) {
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
        }
        arr[count] = num;
        count++;
    }

    if (count == 0) {
        cout << "\nВы не ввели ни одного числа!\n";
        delete[] arr;
        system("pause");
        return 1;
    }

    cout << "\n--- Результат проверки ---";
    cout << "\nКоличество элементов: " << count;
    cout << "\nСодержимое массива: ";
    for (int i = 0; i < count; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n--------------------------\n";

    ofstream fout(fileName, ios::binary);
    if (!fout.is_open()) {
        cout << "Ошибка создания файла!\n";
        delete[] arr;
        system("pause");
        return 1;
    }

    fout.write((char*)&count, sizeof(count));
    fout.write((char*)arr, sizeof(double) * count);
    fout.close();

    cout << "\nФайл \"" << fileName << "\" успешно сохранен!\n";

    delete[] arr;
    system("pause");
    return 0;
}

void PrintFileTxt() {
    system("cls");
    cout << "Вывод содержимого TXT файла\n\n";

    string name;
    cout << "Введите название файла: ";
    if (!inputString(name)) {
        emergencyExit();
        return;
    }

    string fileName = name + ".txt";

    ifstream in(fileName);

    if (!in.is_open()) {
        cout << "Ошибка: Файл \"" << fileName << "\" не найден!\n";
        system("pause");
        return;
    }

    cout << "\n--- Содержимое файла \"" << fileName << "\" ---\n";

    string element;
    int count = 0;

    while (in >> element) {
        cout << element << " ";
        count++;
    }

    cout << "\nКоличество элементов: " << count << "\n\n";

    in.close();
    system("pause");
}

void PrintBinFile() {
    system("cls");
    cout << "Вывод содержимого BIN файла\n\n";

    string name;
    cout << "Введите название файла: ";
    if (!inputText(name)) {
        emergencyExit();
        return;
    }

    string fileName = name + ".bin";

    ifstream fin(fileName, ios::binary);

    if (!fin.is_open()) {
        cout << "Ошибка: Файл \"" << fileName << "\" не найден!\n";
        system("pause");
        return;
    }

    int count = 0;
    fin.read((char*)&count, sizeof(count));

    if (count <= 0) {
        cout << "Файл пуст\n";
        fin.close();
        system("pause");
        return;
    }

    double* arr = new double[count];

    fin.read((char*)arr, sizeof(double) * count);

    cout << "\n--- Содержимое файла \"" << fileName << "\" ---\n";
    cout << "Элементы массива: ";
    for (int i = 0; i < count; i++) {
        cout << arr[i] << " ";
    }
	cout << "\n";
    cout << "Количество элементов: " << count << "\n\n";

    fin.close();
    delete[] arr;

    system("pause");
}

void Dir() {
    system("cls");
    cout << "Содержимое директории (*.txt и *.bin):\n\n";

    system("dir *.txt *.bin /b /a-d");
	cout << "\n\n";
	system("pause");
}

void GetBinFileElementByIndex() {
    system("cls");
    cout << "Получение элемента BIN по индексу\n\n";

    string name;
    cout << "Введите название файла: ";
    if (!inputString(name)) {
        emergencyExit();
        return;
    }

    string fileName = name + ".bin";
    ifstream in(fileName, ios::binary);

    if (!in.is_open()) {
        cout << "Ошибка: Файл \"" << fileName << "\" не найден!\n";
        system("pause");
        return;
    }

    int count = 0;
    in.read((char*)&count, sizeof(count));

    if (count <= 0) {
        cout << "Ошибка: Файл пуст.\n";
        in.close();
        system("pause");
        return;
    }

    cout << "Всего элементов в файле: " << count << "\n";
    cout << "Введите индекс элемента (начиная с 1): ";

    int inputIdx = 0;
    if (!inputIntf(inputIdx, true, count)) {
        in.close();
        emergencyExit();
        return;
    }


    double currentElement = 0;
    int currentIndex = 0;

    while (in.read((char*)&currentElement, sizeof(double))) {
        currentIndex++;

        if (currentIndex == inputIdx) {
            break;
        }
    }

    in.close();

    cout << "\nЭлемент под индексом " << inputIdx << ": " << currentElement << "\n\n";
    system("pause");
}

void GetTxtFileElementByIndex() {
    system("cls");
    cout << "=== Получение элемента TXT по индексу ===\n\n";

    string name;
    cout << "Введите название файла: ";
    if (!inputString(name)) {
        emergencyExit();
        return;
    }

    string fileName = name + ".txt";
    ifstream fin(fileName);

    if (!fin.is_open()) {
        cout << "Ошибка: Файл \"" << fileName << "\" не найден!\n";
        system("pause");
        return;
    }

    string garbage;
    int count = 0;
    while (fin >> garbage) {
        count++;
    }

    if (count == 0) {
        cout << "Ошибка: Файл пуст!\n";
        fin.close();
        system("pause");
        return;
    }

    fin.clear();
    fin.seekg(0, ios::beg);

    cout << "Всего элементов в файле: " << count << "\n";
    cout << "Введите индекс элемента (начиная с 1): ";

    int inputIdx = 0;
    if (!inputIntf(inputIdx, true, count)) {
        fin.close();
        emergencyExit();
        return;
    }

    if (inputIdx < 1 || inputIdx > count) {
        cout << "Ошибка: Неверный индекс! Допустимый диапазон: от 1 до " << count << "\n";
        fin.close();
        system("pause");
        return;
    }

    string currentElement;
    int currentIndex = 0;

    while (fin >> currentElement) {
        currentIndex++;

        if (currentIndex == inputIdx) {
            break;
        }
    }

    fin.close();

    cout << "\nЭлемент под индексом " << inputIdx << ": " << currentElement << "\n\n";
    system("pause");
}

void SolveTaskTxt() {
    system("cls");
    cout << "Решение задачи для TXT\n";
    cout << "Условие: Определить количество xi с четными номерами,\n";
    cout << "меньшими x1 и xmax/2.\n\n";

    string name;
    cout << "Введите название файла: ";
    if (!inputString(name)) {
        emergencyExit();
        return;
    }

    string fileName = name + ".txt";
    ifstream fin(fileName);

    if (!fin.is_open()) {
        cout << "Ошибка: Файл \"" << fileName << "\" не найден!\n";
        system("pause");
        return;
    }

    double x1 = 0;
    double xMax = 0;
    double current = 0;
    int totalElements = 0;

    cout << "\nИсходные данные из файла:\n";

    if (fin >> current) {
        totalElements++;
        x1 = current;
        xMax = current;
        cout << current << " ";
    }
    else {
        cout << "Ошибка: Файл пуст!\n";
        fin.close();
        system("pause");
        return;
    }

    while (fin >> current) {
        totalElements++;
        cout << current << " ";
        if (current > xMax) {
            xMax = current;
        }
    }
    cout << "\n\n";

    fin.clear();
    fin.seekg(0, ios::beg);

    int currentIndex = 0;
    int matchCount = 0;
    double limit = xMax / 2.0;

    while (fin >> current) {
        currentIndex++;

        if (currentIndex % 2 == 0) {
            if (current < x1 && current < limit) {
                matchCount++;
            }
        }
    }

    fin.close();

    cout << "x1: " << x1 << "\n";
    cout << "xmax / 2: " << limit << "\n";
    cout << "Количество подходящих элементов: " << matchCount << "\n\n";

    system("pause");
}

void SolveTaskBin() {
    system("cls");
    cout << "Решение задачи для BIN\n";
    cout << "Условие: Определить количество xi с четными номерами,\n";
    cout << "меньшими x1 и xmax/2.\n\n";

    string name;
    cout << "Введите название файла: ";
    if (!inputString(name)) {
        emergencyExit();
        return;
    }

    string fileName = name + ".bin";
    ifstream fin(fileName, ios::binary);

    if (!fin.is_open()) {
        cout << "Ошибка: Файл \"" << fileName << "\" не найден!\n";
        system("pause");
        return;
    }

    int count = 0;
    fin.read((char*)&count, sizeof(count));

    if (count <= 0) {
        cout << "Ошибка: Файл пуст.\n";
        fin.close();
        system("pause");
        return;
    }

    double x1 = 0;
    double xMax = 0;
    double current = 0;
    int totalElements = 0;

    cout << "\nИсходные данные из файла:\n";

    if (fin.read((char*)&current, sizeof(double))) {
        totalElements++;
        x1 = current;
        xMax = current;
        cout << current << " ";
    }

    while (fin.read((char*)&current, sizeof(double))) {
        totalElements++;
        cout << current << " ";
        if (current > xMax) {
            xMax = current;
        }
    }
    cout << "\n\n";

    fin.clear();
    fin.seekg(sizeof(int), ios::beg);

    int currentIndex = 0;
    int matchCount = 0;
    double limit = xMax / 2.0;

    while (fin.read((char*)&current, sizeof(double))) {
        currentIndex++;

        if (currentIndex % 2 == 0) {
            if (current < x1 && current < limit) {
                matchCount++;
            }
        }
    }

    fin.close();

    cout << "x1: " << x1 << "\n";
    cout << "xmax / 2: " << limit << "\n";
    cout << "Количество подходящих элементов: " << matchCount << "\n\n";

    system("pause");
}

void EditTxtFileElementByIndex() {
    system("cls");
    cout << "Изменение элемента TXT по индексу\n\n";

    string name;
    cout << "Введите название файла: ";
    if (!inputString(name)) {
        emergencyExit();
        return;
    }

    string fileName = name + ".txt";
    ifstream in(fileName);

    if (!in .is_open()) {
        cout << "Ошибка: Файл \"" << fileName << "\" не найден!\n";
        system("pause");
        return;
    }

    string garbage;
    int count = 0;
    while (in >> garbage) {
        count++;
    }

    if (count == 0) {
        cout << "Ошибка: Файл пуст!\n";
        in.close();
        system("pause");
        return;
    }

    in.clear();
    in.seekg(0, ios::beg);

    cout << "Всего элементов в файле: " << count << "\n";
    cout << "Введите индекс элемента для изменения (начиная с 1): ";

    int inputIdx = 0;
    if (!inputIntf(inputIdx, true, count)) {
        in.close();
        emergencyExit();
        return;
    }

    string tempFileName = "temp.txt";
    ofstream out(tempFileName);

    if (!out.is_open()) {
        cout << "Ошибка при создании временного файла!\n";
        in.close();
        system("pause");
        return;
    }

    string currentElement;
    int currentIndex = 0;

    while (in >> currentElement) {
        currentIndex++;

        if (currentIndex == inputIdx) {
            cout << "Старое значение элемента: " << currentElement << "\n";
            cout << "Введите новое значение: ";

            float newValue;
            if (!inputFloat(newValue, 0)) {
                in.close();
                out.close();
                remove(tempFileName.c_str());
                emergencyExit();
                return;
            }
            out << newValue << " ";
        }
        else {
            out << currentElement << " ";
        }
    }
    in.close();
    out.close();

    remove(fileName.c_str());
    rename(tempFileName.c_str(), fileName.c_str());

    cout << "\nЭлемент успешно изменен!\n\n";
    system("pause");
}

void EditBinFileElementByIndex() {
    system("cls");
    cout << "Изменение элемента BIN по индексу\n\n";

    string name;
    cout << "Введите название файла: ";
    if (!inputString(name)) {
        emergencyExit();
        return;
    }

    string fileName = name + ".bin";

    fstream file(fileName, ios::binary | ios::in | ios::out);

    if (!file.is_open()) {
        cout << "Ошибка: Файл \"" << fileName << "\" не найден!\n";
        system("pause");
        return;
    }

    int count = 0;
    file.read((char*)&count, sizeof(count));

    if (count <= 0) {
        cout << "Ошибка: Файл пуст.\n";
        file.close();
        system("pause");
        return;
    }

    cout << "Всего элементов в файле: " << count << "\n";
    cout << "Введите индекс элемента для изменения (начиная с 1): ";

    int inputIdx = 0;
    if (!inputIntf(inputIdx, true, count)) {
        file.close();
        emergencyExit();
        return;
    }

    double tempElement = 0;
    int currentIndex = 0;

    while (file.read((char*)&tempElement, sizeof(double))) {
        currentIndex++;

        if (currentIndex == inputIdx) {
            cout << "Старое значение элемента: " << tempElement << "\n";
            cout << "Введите новое значение (double): ";

            float newValue = 0;
            if (!inputFloat(newValue, false)) {
                file.close();
                emergencyExit();
                return;
            }

            double finalValue = (double)newValue;


            file.seekp(-(int)sizeof(double), ios::cur);

            file.write((char*)&finalValue, sizeof(double));
            break;
        }
    }

    file.close();
    cout << "\n[Успех] Элемент успешно изменен!\n\n";
    system("pause");
}

int sLab_3() {
    system("cls");
    Info2();
    filterFileTxt("SmallNumbers.txt");
    filterFileTxt("BigNumbers.txt");

    char ch = 0;
    do{
        system("cls");
        Info2();

        cout << "1 - Показать содержимое директории\n";
        cout << "2 - Создать бинарный файл из ввода\n";
        cout << "3 - Вывести содержимое TXT файла\n";
        cout << "4 - Вывести содержимое BIN файла\n";
		cout << "5 - Получить элемент TXT файла по индексу\n";
		cout << "6 - Получить элемент BIN файла по индексу\n";
        cout << "7 - Изменить элемент TXT файла по индексу\n";
		cout << "8 - Изменить элемент BIN файла по индексу\n";
		cout << "9 - Решение задачи для TXT файла\n";
		cout << "0 - Решение задачи для BIN файла\n";
        cout << "ESC - выход\n\n";

        ch = _getch();
        switch (ch) {
		case '1': Dir(); break;
		case '2': CreateBinFile(); break;
		case '3': PrintFileTxt(); break;
		case '4': PrintBinFile(); break;
		case '5': GetTxtFileElementByIndex(); break;
		case '6': GetBinFileElementByIndex(); break;
		case '7': EditTxtFileElementByIndex(); break;
		case '8': EditBinFileElementByIndex(); break;
		case '9': SolveTaskTxt(); break;
		case '0': SolveTaskBin(); break;
        }
    } while (ch != 27);


	system("pause");
	return 0;
}