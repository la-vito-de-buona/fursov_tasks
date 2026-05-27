#pragma once
#include "../header.h"

class CID {
protected:
	int nId;
	string sName;
public:
	CID() : nId(0), sName("Class *") {}
	CID(int pnid) :CID() { nId = pnid; }
	int GetId() { return nId; }
	void SetId(int pnid) { nId = pnid; }
	string GetName() { return sName; }
	void SetName(string pname) { sName = pname; }
	__declspec(property(get = GetId, put = SetId)) int id;
	__declspec(property(get = GetName, put = SetName)) string Name;
};

class CFigura {
protected:
	int nx, ny, nWidth, nHeight, nbrushcolor, npencolor;
public:
	int GetRight() { return nx + nWidth; }
	int GetBottom() { return ny + nHeight; }
	int GetX() { return nx; }
	void SetX(int pnx) { nx = pnx; }
	int GetY() { return ny; }
	void SetY(int pny) { ny = pny; }
	int GetWidth() { return nWidth; }
	void SetWidth(int pnWid) { nWidth = pnWid; }
	int GetHeight() { return nHeight; }
	void SetHeight(int pnHei) { nHeight = pnHei; }
	int GetBrushcolor() { return nbrushcolor; }
	void SetBrushcolor(int pnbrush) { nbrushcolor = pnbrush; }
	int GetPencolor() { return npencolor; }
	void SetPencolor(int pencolor) { npencolor = pencolor; }
	int GetMiddleX() { return nx + Width / 2; }
	int GetMiddleY() { return ny + Height / 2; }


	CFigura() : nx(0), ny(0), nWidth(40), nHeight(60), nbrushcolor(RGB(34, 34, 34)), npencolor(RGB(255, 255, 255)) {}
	CFigura(int pnx, int pny, int pnWid = 30, int pnHei = 60) : nx(pnx), ny(pny), nWidth(pnWid), nHeight(pnHei) {
		nbrushcolor = RGB(34, 34, 34);
		npencolor = RGB(255, 255, 255);
	}
	CFigura(int pnx, int pny, int pnWid, int pnHei, int pnbrush, int pnpen) :nx(pnx), ny(pny), nWidth(pnWid), nHeight(pnHei), nbrushcolor(pnbrush), npencolor(pnpen) {}

	__declspec(property(get = GetX, put = SetX)) int X;
	__declspec(property(get = GetY, put = SetY)) int Y;
	__declspec(property(get = GetWidth, put = SetWidth)) int Width;
	__declspec(property(get = GetHeight, put = SetHeight)) int Height;
	__declspec(property(get = GetBrushcolor, put = SetBrushcolor)) int BrushColor;
	__declspec(property(get = GetPencolor, put = SetPencolor)) int PenColor;
	__declspec(property(get = GetX, put = SetX)) int Left;
	__declspec(property(get = GetY, put = SetY)) int Top;
	__declspec(property(get = GetRight)) int Right;
	__declspec(property(get = GetBottom)) int Bottom;
	__declspec(property(get = GetMiddleX)) int MiddleX;
	__declspec(property(get = GetMiddleY)) int MiddleY;
	virtual void Draw() {};
};

class CRectangle : public CFigura, public CID {
public:
	CRectangle() : CFigura(0, 0, 40, 60, RGB(255, 134, 134), RGB(255, 255, 255)), CID() {Name = "Прямоугольник"; }
	CRectangle(int pnx, int pny, int pnWid = 30, int pnHei = 60) : CFigura(pnx, pny, pnWid, pnHei), CID() {
		nbrushcolor = RGB(rand() % 255, 134, 134);
		npencolor = RGB(255, 255, 255);
		Name = "Прямоугольник";
	}
	CRectangle(int pnx, int pny, int pnWid, int pnHei, int pnbrush, int pnpen) :CFigura(pnx, pny, pnWid, pnHei, pnbrush, pnpen), CID() { Name = "Прямоугольник"; }
	void Draw();
};

class CTriangle : public CFigura, public CID {
public:
	CTriangle() : CFigura(), CID() {
		nWidth = 70;
		nHeight = 50;
		nbrushcolor = RGB(134, 255, 134);
		npencolor = RGB(255, 255, 255);
		Name = "Треугольник";
	}
	CTriangle(int pnx, int pny, int pnWid = 30, int pnHei = 60) : CFigura(pnx, pny, pnWid, pnHei), CID() {
		nbrushcolor = RGB(134, 255, 134);
		npencolor = RGB(255, 255, 255);
		Name = "Треугольник";
	}
	CTriangle(int pnx, int pny, int pnWid, int pnHei, int pnbrush, int pnpen) :CFigura(pnx, pny, pnWid, pnHei, pnbrush, pnpen), CID() {
		Name = "Треугольник";
	}

	void Draw();
};

class CEllipse : public CFigura, public CID {
public:
	CEllipse() : CFigura(), CID() {
		nWidth = 60;
		nHeight = 60;
		nbrushcolor = RGB(134, 134, 255);
		npencolor = RGB(255, 255, 255);
		Name = "Эллипс";
	}
	CEllipse(int pnx, int pny, int pnWid = 30, int pnHei = 60) : CFigura(pnx, pny, pnWid, pnHei), CID() {
		nbrushcolor = RGB(134, 134, 255);
		npencolor = RGB(255, 255, 255);
		Name = "Эллипс";
	}
	CEllipse(int pnx, int pny, int pnWid, int pnHei, int pnbrush, int pnpen) :CFigura(pnx, pny, pnWid, pnHei, pnbrush, pnpen), CID() {Name = "Эллипс"; }


	void Draw();
};


void MenuClasses();
void AllShow();
CFigura* FindFigura(int pnid);