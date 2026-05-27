#include "shifr.h"


string caesar(const string& text, int shift) {
    string res = "";

    for (char c : text) {
        size_t pos;

        if ((pos = engAlphabet.find(c)) != string::npos) {
            int n = engAlphabet.size();
            res += engAlphabet[(pos + shift + n) % n];
        }
        else if ((pos = rusAlphabet.find(c)) != string::npos) {
            int n = rusAlphabet.size();
            res += rusAlphabet[(pos + shift + n) % n];
        }
        else if ((pos = numAlphabet.find(c)) != string::npos) {
            int n = numAlphabet.size();
            res += numAlphabet[(pos + shift + n) % n];
        }
        else {
            res += c;
        }
    }

    return res;
}

string dynamicCipher(const string& text) {
    string res = "";

    for (int i = 0; i < text.size(); i++) {
        char c = text[i];
        int shift = i + 1;

        size_t pos;

        if ((pos = engAlphabet.find(c)) != string::npos) {
            int n = engAlphabet.size();
            res += engAlphabet[(pos + shift) % n];
        }
        else if ((pos = rusAlphabet.find(c)) != string::npos) {
            int n = rusAlphabet.size();
            res += rusAlphabet[(pos + shift) % n];
        }
        else if ((pos = numAlphabet.find(c)) != string::npos) {
            int n = numAlphabet.size();
            res += numAlphabet[(pos + shift) % n];
        }
        else {
            res += c;
        }
    }

    return res;
}

string dynamicDecipher(const string& text) {
    string res = "";

    for (int i = 0; i < text.size(); i++) {
        char c = text[i];
        int shift = i + 1;

        size_t pos;

        if ((pos = engAlphabet.find(c)) != string::npos) {
            int n = engAlphabet.size();
            res += engAlphabet[(pos - shift + n) % n];
        }
        else if ((pos = rusAlphabet.find(c)) != string::npos) {
            int n = rusAlphabet.size();
            res += rusAlphabet[(pos - shift + n) % n];
        }
        else if ((pos = numAlphabet.find(c)) != string::npos) {
            int n = numAlphabet.size();
            res += numAlphabet[(pos - shift + n) % n];
        }
        else {
            res += c;
        }
    }

    return res;
}


const int MAX_BITS = 2048;

string bitShifr(const string& s, int k) {
    int bits[MAX_BITS];
    int shifted[MAX_BITS];
    int n = 0;
    for (int i = 0; i < s.size(); i++) {
        unsigned char c = s[i];
        for (int j = 7; j >= 0; j--) {
            bits[n++] = (c >> j) & 1;
        }
    }
    if (n == 0) return "";
    k %= n;
    if (k < 0) k += n;
    for (int i = 0; i < n; i++) {
        shifted[(i + k) % n] = bits[i];
    }
    string res = "";
    for (int i = 0; i < n; i += 8) {
        unsigned char c = 0;
        for (int j = 0; j < 8; j++) {
            c = (c << 1) | shifted[i + j];
        }
        res += c;
    }
    return res;
}

int EncryptMenu() {
    system("cls");
    Info2();

    cout << "Введите текст для шифрования:\n";
    string text;

    if (!inputText(text)) return emergencyExit();

    string result = text;

    unsigned char ch = 0;

    do {
        system("cls");
        cout << "Меню шифрования\n";
        cout << "Текущий текст: " << result << "\n\n";

        cout << "1 - Шифрование Цезаря\n";
        cout << "2 - Дешифрование Цезаря\n";
        cout << "3 - Динамическое шифрование\n";
        cout << "4 - Динамическое дешифрование\n";
        cout << "5 - Побитовое шифрование\n";
        cout << "6 - Побитовое дешифрование\n";
        cout << "7 - Вернуть исходный текст\n";
        cout << "ESC - выход\n\n";

        ch = _getch();

        switch (ch) {
        case '1': result = caesar(result, 1); break;
        case '2': result = caesar(result, -1); break;
        case '3': result = dynamicCipher(result); break;
        case '4': result = dynamicDecipher(result); break;
        case '5': result = bitShifr(result, 1); break;
        case '6': result = bitShifr(result, -1); break;
        case '7': result = text; break;
        }

    } while (ch != 27);

    system("cls");
    Info2();
    cout << "Аварийный выход.\n\n";

    system("pause");
    return 0;
}