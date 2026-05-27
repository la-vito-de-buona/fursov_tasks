#include "io.h"

float cin_cond(string b, float ex) {
    float a;
    while (true) {
        cin >> a;
        if (cin.fail()) {
            ClearCin;
            cout << "Ошибка ввода!\nПовторите ввод\n";
            cout << b;
            continue;
        }
        if (ex != INFINITE and a == ex) {
            cout << "Ошибка ввода!\nПовторите ввод\n";
            cout << b;
            continue;
        }
        break;
    }
    return(a);
}

bool inputFloat(float& value, bool con) {
    string buffer;
    char ch;
    bool error = false;
    COORD startPos = GetCursorPosition();

    while (true) {
        ch = _getch();
        if (ch == 27) return false;
        if (ch == 13) {
            try {
                size_t pos;
                float temp = stof(buffer, &pos);
                if (con && temp <= 1) {
                    cout << "Ошибка, введите число больше или равно 2: ";
                    buffer.clear();
                    error = true;
                }
                if (error) {
                    SetCursorPosition(startPos.Y + 1, startPos.X);
                    cout << "\x1b[2K\r";
                    SetCursorPosition(startPos.Y, 0);
                }
                if (pos != buffer.length()) {
                    throw runtime_error("");
                }
                value = stof(buffer);
                cout << "\n";
                return true;
            }
            catch (...) {
                cout << "\nОшибка! Повторите ввод: ";
                buffer.clear();
                error = true;
            }
        }
        else if (ch == 8) {
            if (!buffer.empty()) {
                buffer.pop_back();
                cout << "\b \b";
            }
        }
        else if (ch == 46) {
            ch = 44;
            buffer += ch;
            cout << ch;
        }
        else {
            buffer += ch;
            cout << ch;
        }
    }
}

bool inputInt(int& value, bool con) {
    string buffer;
    char ch;
    bool error = false;
    COORD startPos = GetCursorPosition();

    while (true) {
        ch = _getch();
        if (ch == 27) return false;
        if (ch == 13) {
            try {
                size_t pos;
                int temp = stoi(buffer, &pos);
                if (con && temp <= 1) {
                    buffer.clear();
                    error = true;
                }
                if (error) {
                    SetCursorPosition(startPos.Y + 1, startPos.X);
                    cout << "\x1b[2K\r";
                    SetCursorPosition(startPos.Y, 0);
                }
                if (pos != buffer.length()) {
                    throw runtime_error("");
                }
                value = stoi(buffer);
                cout << "\n";
                return true;
            }
            catch (...) {
                cout << "\nОшибка! Повторите ввод: ";
                buffer.clear();
                error = true;
            }
        }
        else if (ch == 8) {
            if (!buffer.empty()) {
                buffer.pop_back();
                cout << "\b \b";
            }
        }
        else {
            buffer += ch;
            cout << ch;
        }
    }
}

bool inputIntf(int& value, bool con, int c) {
    string buffer;
    char ch;
    bool error = false;
    COORD startPos = GetCursorPosition();

    while (true) {
        ch = _getch();
        if (ch == 27) return false;
        if (ch == 13) {
            try {
                size_t pos;
                int temp = stoi(buffer, &pos);
                if (con && (temp < 1 || temp > c)) {
                    buffer.clear();
                    error = true;
                }
                if (error) {
                    SetCursorPosition(startPos.Y + 1, startPos.X);
                    cout << "\x1b[2K\r";
                    SetCursorPosition(startPos.Y, 0);
                }
                if (pos != buffer.length()) {
                    throw runtime_error("");
                }
                value = stoi(buffer);
                cout << "\n";
                return true;
            }
            catch (...) {
                cout << "\nОшибка! Индекс вне допустимого диапазона!\nПовторите ввод: ";
                buffer.clear();
                error = true;
            }
        }
        else if (ch == 8) {
            if (!buffer.empty()) {
                buffer.pop_back();
                cout << "\b \b";
            }
        }
        else {
            buffer += ch;
            cout << ch;
        }
    }
}


bool inputText(string& value) {
    string buffer;
    char ch;

    while (true) {
        ch = _getch();

        if (ch == 27) return false;

        if (ch == 13) {
            if (buffer.empty()) {
                cout << "\nОшибка! Пустая строка.\n";
                continue;
            }

            if (!isValidText(buffer)) {
                cout << "\nОшибка! Только русские/английские буквы, цифры и пробел.\n";
                buffer.clear();
                continue;
            }

            value = buffer;
            cout << "\n";

            return true;
        }
        else if (ch == 8) {
            if (!buffer.empty()) {
                buffer.pop_back();
                cout << "\b \b";
            }
        }
        else {
            buffer += ch;
            cout << ch;
        }
    }
}

bool inputString(string& value) {
    value.clear();
    char ch;

    while (true) {
        ch = _getch();

        if (ch == 27) {
            return false;
        }
        if (ch == 13) {
            cout << "\n";
            return true;
        }
        if (ch == 8) {
            if (!value.empty()) {
                value.pop_back();
                cout << "\b \b";
            }
        }
        else {
            value += ch;
            cout << ch;
        }
    }
}