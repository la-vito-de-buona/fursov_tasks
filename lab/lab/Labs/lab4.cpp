#include "lab4.h"

int Lab4() {
    system("cls");
    Info1();

    cout << "Задание 4.\nВ положительной целочисленной матрице имеется несколько столбцов, состоящих только из единиц.\nЗаменить элементы этих столбцов полусуммой элементов всех остальных столбцов\n\n";

    bool prz = false;

    COORD coord = GetCursorPosition();
    MATRIX matrix;
    MATRIX newMatrix;
    if (matrix.InputMatrFromKb(200, 200) < 0) {
        cout << "Ошибка ввода данных матрицы.\n";
        cout << "Расчет задания прерван!\n";
    }

    bool allOnesCol[MCOL]{ false };
    for (int j = 0; j < MCOL; j++) {
        allOnesCol[j] = true;
        for (int i = 0; i < MROW; i++) {
            if (matrix.nMatrix[i][j] != 1) {
                allOnesCol[j] = false;
                break;
            }
        }
    }

    for (int i = 0; i < MROW; i++) {
        for (int j = 0; j < MCOL; j++) {
            newMatrix.nMatrix[i][j] = matrix.nMatrix[i][j];
        }
    }

    for (int j = 0; j < MCOL; j++) {
        if (isAllOnes(matrix.nMatrix, MROW, j)) {
            for (int i = 0; i < MROW; i++) {
                float sum = 0;
                for (int k = 0; k < MCOL; k++) {
                    if (!allOnesCol[k]) sum += matrix.nMatrix[i][k];
                }
                newMatrix.nMatrix[i][j] = sum / 2;
            }
        }
    }


    newMatrix.OutputMatrixGraf("Результат", 600, 200);
    cout << "Для продолжения нажмите на любую кнопку . . . ";
    _getch();
    return 0;
}