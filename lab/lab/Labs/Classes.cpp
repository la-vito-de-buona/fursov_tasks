#include "class.h"	

void AllShow(CManager& figs) {
    figs.Draw();
}

CFigura* FindFigura(CManager& figs, int pnid) {
    return figs.GetFigura(pnid);
}

void MenuClasses() {
    unsigned char ch = 0;
    CRectangle* objRectangle = nullptr;
    CTriangle* objTriangle = nullptr;
    CEllipse* objEllipse = nullptr;
    CFigura* objFig = nullptr;
    _eButton keybutton = eb_None;
    string scolor = "";
    int ncolor = 0, nstep = 0,
        nred = 0, ngreen = 0, nblue = 0;

    short nid = 0, dn = 1, count = 0;

    CManager figs;

    srand((UINT)time(NULL));

    do {
        system("cls");
        cout << "Меню для работы с классами : \n";
        cout << "1 - Создать объекты\n";
        cout << "2 - Изменить размер объекта\n";
        cout << "3 - Изменить цвет объекта\n";
        cout << "4 - Перемещение объекта\n";
        cout << "5 - Удалить объект\n";
        cout << "Esc - Выход из программы\n\n";
        cout << "Выберите пункт меню\n";
        AllShow(figs);

        ch = _getch();
        switch (ch) {
        case '3':
            system("cls");
            AllShow(figs);
            std::cout << "Укажите идентификатор объекта: "; if (!ReadShortWithESC(nid)) break;;
            objFig = FindFigura(figs, nid);
            if (objFig == NULL) {
                cout << "\n\nОшибка: Объект с ID " << nid << " не найден!\n";
                system("pause");
                break;
            }
            system("cls");
            objFig->Draw();
            std::cout << "Объект :" << objFig->Name << " id= " << objFig->ID;
            LINES(3);
            std::cout << "Введите цветовую палитру цвета RGB\n";
            std::cout << "  для заливки\n";
            std::cout << "  красный=> ";
            nstep = 0;
            do {
                ch = _getch();
                switch (ch) {
                case '0': case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
                    scolor += ch;
                    std::cout << ch;
                    break;
                case 13:
                    if (scolor.empty()) {
                        switch (nstep) {
                        case 0:case 1: case 2:
                            nstep = 3;
                            std::cout << "\nдля контура\n  красный => ";
                            break;
                        case 3: case 4:case 5:
                            nstep = 0;
                            ch = 27;
                            break;
                        }
                    }
                    else {
                        ncolor = stoi(scolor) % 256;
                        scolor.clear();
                        switch (nstep) {
                        case 0:
                            nred = ncolor;
                            std::cout << "\n  зеленый => ";
                            break;
                        case 1:
                            ngreen = ncolor;
                            std::cout << "\n  синий => ";
                            break;
                        case 2:
                            nblue = ncolor;
                            objFig->ColorBrush = RGB(nred, ngreen, nblue);
                            std::cout << "\nдля контура\n  красный => ";
                            break;
                        case 3:
                            nred = ncolor;
                            std::cout << "\n  зеленый => ";
                            break;
                        case 4:
                            ngreen = ncolor;
                            std::cout << "\n  синий => ";
                            break;
                        case 5:
                            nblue = ncolor;
                            objFig->ColorPen = RGB(nred, ngreen, nblue);
                            ch = 27;
                            break;
                        }
                        nstep++;
                    }
                    break;
                }
            } while (ch != 27);

            if (ch == 27) {
                cout << "Аварийный выход через ESC!";
            }
            ch = 0;
            break;

        case '4':
			system("cls");
            AllShow(figs);
            std::cout << "Укажите идентификатор объекта: "; if (!ReadShortWithESC(nid)) break;;
            objFig = figs[nid];
            if (objFig == NULL) {
                cout << "\n\nОшибка: Объект с ID " << nid << " не найден!\n";
                system("pause");
                break;
            }


            cout << "Объект :" << objFig->Name << " id= " << objFig->ID << endl;
            cout << " для перемещения объекта используйте клавиши стрелки или выход клавиша ESC";
            do {
                ch = _getch();
                switch (ch) {
                case 0:case 224:
                    objFig->Draw(true);
                    switch (_getch()) {
                    case 75:
                        dn = (keybutton == eb_Left) ? dn + 1 : 2;
                        objFig->x = objFig->x - dn;
                        keybutton = eb_Left;
                        break;
                    case 77:
                        dn = (keybutton == eb_Right) ? dn + 1 : 2;
                        objFig->x = objFig->x + dn;
                        keybutton = eb_Right;
                        break;
                    case 72:
                        dn = (keybutton == eb_Up) ? dn + 1 : 2;
                        objFig->y = objFig->y - dn;
                        keybutton = eb_Up;
                        break;
                    case 80:
                        dn = (keybutton == eb_Down) ? dn + 1 : 2;
                        objFig->y = objFig->y + dn;
                        keybutton = eb_Down;
                        break;
                    }
                    AllShow(figs);
                    break;
                }
            } while (ch != 27);
            ch = 0;
            break;

        case '1':
            do {
                system("cls");
                cout << "     Меню для создания объектов:\n";
                cout << "1 - Создать объект \"Прямоугольник\"\n";
                cout << "2 - Создать объект \"Треугольник\"\n";
                cout << "3 - Создать объект \"Эллипс\"\n";
                cout << "Esc - Выход из программы\n\n";
                cout << "Выберите пункт меню\n";
                AllShow(figs);

                ch = _getch();
                switch (ch) {
                case '1':
                    objRectangle = new CRectangle(rand() % 1200, rand() % 950, rand() % 100, rand() % 100, rand() % 255, RGB(rand() % 255, rand() % 255, 255), rand() % 5);
                    objRectangle->ID = count;
                    count += 1;
                    figs.Add(objRectangle);
                    objRectangle->Draw(false);
                    break;
                case '2':
                    objTriangle = new CTriangle(rand() % 1200, rand() % 950, rand() % 100, rand() % 100, rand() % 255, RGB(rand() % 255, rand() % 255, 255), rand() % 5);
                    objTriangle->Width = 50;
                    objTriangle->Height = 25;
                    objTriangle->ID = count;
                    count += 1;
                    figs.Add(objTriangle);
                    objTriangle->Draw(false);
                    break;
                case '3':
                    objEllipse = new CEllipse(rand() % 1200, rand() % 950, rand() % 100, rand() % 100, rand() % 255, RGB(rand() % 255, rand() % 255, 255), rand() % 5);
                    objEllipse->Width = 70;
                    objEllipse->Height = 45;
                    objEllipse->ID = count;
                    count += 1;
                    figs.Add(objEllipse);
                    objEllipse->Draw(false);
                    break;
                }
            } while (ch != 27);
            ch = 0;
            break;

        case '2':
            system("cls");
            AllShow(figs);
            cout << "Укажите идентификатор объекта: "; if (!ReadShortWithESC(nid)) break;;
            objFig = FindFigura(figs, nid);
            if (objFig == NULL) {
                cout << "\n\nОшибка: Объект с ID " << nid << " не найден!\n";
                break;
            }
            cout << "Объект :" << objFig->Name << " id= " << objFig->ID << endl;
            cout << " Стрелки влево-вправо -> ширина; вверх-вниз -> высота объекта или выход клавиша ESC";
            do {
                ch = _getch();
                switch (ch) {
                case 0:case 224:
                    objFig->Draw(true);
                    switch (_getch()) {
                    case 75:
                        objFig->Width = objFig->Width - dn;
                        break;
                    case 77:
                        objFig->Width = objFig->Width + dn;
                        break;
                    case 72:
                        objFig->Height = objFig->Height - dn;
                        break;
                    case 80:
                        objFig->Height = objFig->Height + dn;
                        break;
                    }
                    AllShow(figs);
                    break;
                }
            } while (ch != 27);
            ch = 0;
            break;
        case '5':
            system("cls");
            AllShow(figs);
            cout << "Введите ID объекта для удаления: ";
            if (!ReadShortWithESC(nid)) break;

            if (figs.Delete(nid) == 0) {
                system("cls");
                AllShow(figs);
                cout << "\nОбъект с ID " << nid << " успешно удален!\n";
            }
            else {
                cout << "\nОшибка: Объект с ID " << nid << " не найден!\n";
            }

            system("pause");
            break;
        }
    } while (ch != 27);

	system("cls");
    figs.Clear();
}