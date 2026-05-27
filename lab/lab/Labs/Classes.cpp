#include "class.h"	

vector<CFigura*> figs;
void MenuClasses() {
	char ch = 0;
    CRectangle* objRectangle = NULL;
	CTriangle* objTriangle = NULL;
	CEllipse* objEllipse = NULL;
	CFigura* objFig = NULL;
    
	int nid = 0;
    int row = 25, col = 89;
    
	system("cls");
    cout << "Меню для работы с классами:\n";
    cout << "1 - Создать объект\"Прямоугольник\"\n";
    cout << "2 - Создать объект\"Треугольник\"\n";
    cout << "3 - Создать объект\"Эллипс\"\n";
    cout << "4 - Рисовать все объекты\n";
	cout << "5 - Перемещение объекта\n";
    cout << "ESC для выхода из программы\n\n";

    do {
        AllShow();

        ch = _getch();
        switch (ch) {
		case '5': system("cls");
            AllShow();
            cout << "Укажите идентификатор объекта: "; cin >> nid;
			objFig = FindFigura(nid);
            if (objFig == NULL) break;

			cout << "Для перемещения объекта используйте клавиши стрелок или выход клавиша ESC\n";
            do {
                ch = _getch();
                switch (ch) {
				case 0: case 224:
                    switch (_getch()){
                    case 75: cout << "left"; objFig->X = objFig->X - 2; break;
					case 77: cout << "right"; objFig->X = objFig->X + 2; break;
					case 72: cout << "up"; objFig->Y = objFig->Y - 2; break;
					case 80: cout << "down"; objFig->Y = objFig->Y + 2; break;
                    }
                    break;
                }
                objFig->Draw();
			} while (ch != 27);
			_getch(); break;
        case '1':
            objRectangle = new CRectangle(rand() % 1200, 100 + rand() % 950);
			figs.push_back(objRectangle);
            objRectangle->id = figs.size();
            figs.back()->Draw();
            _getch(); break;
		case '2':
            objTriangle = new CTriangle(150 + rand() % 1000, 270 + rand() % 700, 50, 25);
			figs.push_back(objTriangle);
            objTriangle->id = figs.size();
            figs.back()->Draw();
            _getch(); break;
		case '3':
            objEllipse = new CEllipse(120 + rand() % 1000, 330 + rand() % 700, 70, 45);
			figs.push_back(objEllipse);
            objEllipse->id = figs.size();
            figs.back()->Draw();
            _getch(); break;
        case '4':
			for (int i = 0; i < figs.size(); i++) {
				figs[i]->Draw();
			}
            _getch(); break;
        case 27: break;
        }
    } while (ch != 27);

	for (int i = 0; i < figs.size(); i++) {
		objFig = figs[i];
        delete(objFig);
	}
    figs.clear();   
}


void AllShow() {
    for (int i = 0; i < figs.size(); i++) {
        figs[i]->Draw();
    }
}

CFigura* FindFigura(int pnid)
{
	CID* cid = NULL;
	for (int i = 0; i < figs.size(); i++) {
		cid = (CRectangle*)figs[i]; 
		if (cid->id == pnid) return figs[i];
	}
	return NULL;
}