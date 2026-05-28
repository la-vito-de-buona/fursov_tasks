#pragma once
#include "header.h"

class CID {
protected:
    int nId;
    string sName;
public:
    CID() { nId = 0; sName = "CID"; }
    CID(int pId) { nId = pId; }
    CID(int pId, string ps) { nId = pId; sName = ps; }
    int GetID() { return nId; }
    string GetName() { return sName; }
    void SetID(int pId) { nId = pId; }
    string SetName(string ps) { sName = ps; }
    __declspec(property(get = GetID, put = SetID)) int ID;
    __declspec(property(get = GetName, put = SetName)) string Name;
};

class CFigura : public CID {
protected:
    int nX, nY, nWidth, nHeight;
    int nColorPen, nColorBrush;
    int nWidthPen;

    int nRight, nBottom;
public:
    int GetRight() { return nX + nWidth; }
    int GetBottom() { return nY + nHeight; }

    int Getx() { return nX; }
    int Gety() { return nY; }
    int GetWidth() { return nWidth; }
    int GetHeight() { return nHeight; }
    int GetPenColor() { return nColorPen; }
    int GetBrushColor() { return nColorBrush; }
    int GetMiddleX() { return Width / 2; }
    int GetMiddleY() { return Height / 2; }

    void Setx(int px) { nX = px; }
    void Sety(int py) { nY = py; }
    void SetWidth(int w) { nWidth = w; }
    void SetHeight(int h) { nHeight = h; }
    void SetPenColor(int c) { nColorPen = c; }
    void SetBrushColor(int c) { nColorBrush = c; }
public:
    CFigura() :CID() {
        nX = nY = 0;
        nWidth = 100;
        nHeight = 40;
        nColorPen = 225;
        nColorBrush = RGB(0, 0, 255);
        nWidthPen = 3;
        nId = 0;
    }

    CFigura(int pId) :CID(pId) { nId = pId; }

    CFigura(int pId, string ps) :CID(pId, ps) { nId = pId; sName = ps; }

    CFigura(int px, int py) {
        nX = px;
        nY = py;
    }

    CFigura(int pWidth, short pHeight) {
        nWidth = pWidth;
        nHeight = pHeight;
    }

    CFigura(int px, int py, int w, int h, int cp, int cb, int wp) : CID() {
        nX = px;
        nY = py;
        nWidth = w;
        nHeight = h;
        nColorPen = cp;
        nColorBrush = cb;
        nWidthPen = wp;
    }


    __declspec(property(get = Getx, put = Setx)) int x;
    __declspec(property(get = Gety, put = Sety)) int y;
    __declspec(property(get = GetWidth, put = SetWidth)) int Width;
    __declspec(property(get = GetHeight, put = SetHeight)) int Height;
    __declspec(property(get = GetPenColor, put = SetPenColor)) int ColorPen;
    __declspec(property(get = GetBrushColor, put = SetBrushColor)) int ColorBrush;

    __declspec(property(get = Getx, put = Setx)) int Left;
    __declspec(property(get = Gety, put = Sety)) int Top;
    __declspec(property(get = GetRight)) int Right;
    __declspec(property(get = GetBottom)) int Bottom;
    __declspec(property(get = GetMiddleX)) int MiddleX;
    __declspec(property(get = GetMiddleY)) int MiddleY;

    virtual void Draw(bool pclear = false) = 0;

    virtual ~CFigura() = default;
};

class CRectangle : public CFigura {
public:
    CRectangle() : CFigura() {};

    CRectangle(int px, int py) : CFigura(px, py) {};

    CRectangle(int w, short h) : CFigura(w, h) {};

    CRectangle(int pId) :CFigura(pId) {};

    CRectangle(int pId, string ps) :CFigura(pId, ps) {};

    CRectangle(int px, int py, int w, int h, int cp, int cb, int wp) : CFigura(px, py, w, h, cp, cb, wp) {};

    void Draw(bool pclear = false) {
        HDC hdc = GetDC(GetConsoleWindow());

        LOGBRUSH lbBrush;
        lbBrush.lbStyle = BS_SOLID;
        lbBrush.lbColor = pclear ? 0 : GetBrushColor();

        HBRUSH hbrush = CreateBrushIndirect(&lbBrush);
        SelectObject(hdc, hbrush);

        HPEN hpen = pclear
            ? CreatePen(PS_SOLID, 2, 0)
            : CreatePen(PS_SOLID, 2, nColorPen);
        SelectObject(hdc, hpen);

        int Left = nX;
        int Top = nY;

        Rectangle(hdc, Left, Top, Right, Bottom);

        string sid = to_string(nId);

        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, pclear ? 0 : RGB(255, 255, 255));

        SIZE sz{};
        GetTextExtentPoint32A(hdc, sid.c_str(), (int)sid.size(), &sz);

        TextOutA(hdc,
            nX + MiddleX - sz.cx / 2,
            nY + MiddleY - sz.cy / 2,
            sid.c_str(),
            sid.size());

        DeleteObject(hpen);
        DeleteObject(hbrush);
        ReleaseDC(GetConsoleWindow(), hdc);

        SetBkMode(hdc, TRANSPARENT);

        GetTextExtentPoint32A(hdc, sid.c_str(), (int)sid.size(), &sz);
        int textX = nX + MiddleX - sz.cx / 2;
        int textY = nY + MiddleY - sz.cy / 2;
        int len = (int)sid.size();

        DeleteObject(hpen);
        DeleteObject(hbrush);
        ReleaseDC(GetConsoleWindow(), hdc);
    }
};

class CTriangle : public CFigura {
public:
    CTriangle() : CFigura() {};

    CTriangle(int px, int py) : CFigura(px, py) {};

    CTriangle(int w, short h) : CFigura(w, h) {};

    CTriangle(int px, int py, int w, int h, int cp, int cb, int wp) : CFigura(px, py, w, h, cp, cb, wp) {};

    void Draw(bool pclear = false) {
        HDC hdc = GetDC(GetConsoleWindow());

        LOGBRUSH lbBrush;
        lbBrush.lbStyle = BS_SOLID;
        lbBrush.lbColor = pclear ? 0 : GetBrushColor();
        HBRUSH hbrush = CreateBrushIndirect(&lbBrush);
        SelectObject(hdc, hbrush);

        HPEN hpen = (pclear) ? CreatePen(PS_SOLID, 2, 0) : CreatePen(PS_SOLID, 2, nColorPen);
        SelectObject(hdc, hpen);


        POINT pt[4]{};
        pt[0].x = nX + nWidth / 2; pt[0].y = Top;
        pt[1].x = this->Right; pt[1].y = Bottom;
        pt[2].x = Left; pt[2].y = Bottom;
        pt[3].x = pt[0].x; pt[3].y = pt->y;
        Polygon(hdc, pt, 4);
        string sid = to_string(nId);

        int MiddleX = nWidth / 2;
        int MiddleY = nHeight / 2;

        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, (pclear) ? 0 : RGB(255, 255, 255));
        SIZE sz{};
        GetTextExtentPoint32A(hdc, sid.c_str(), (int)sid.size(), &sz);
        TextOutA(hdc, nX + MiddleX - sz.cx / 2, nY + MiddleY - sz.cy / 2, sid.c_str(),
            (int)sid.size());

        DeleteObject(hpen);
        DeleteObject(hbrush);
        ReleaseDC(GetConsoleWindow(), hdc);

        SetBkMode(hdc, TRANSPARENT);

        GetTextExtentPoint32A(hdc, sid.c_str(), (int)sid.size(), &sz);
        int textX = nX + MiddleX - sz.cx / 2;
        int textY = nY + MiddleY - sz.cy / 2;
        int len = (int)sid.size();

        SetTextColor(hdc, RGB(0, 0, 0));
        TextOutA(hdc, textX + 1, textY, sid.c_str(), len);
        TextOutA(hdc, textX - 1, textY, sid.c_str(), len);
        TextOutA(hdc, textX, textY + 1, sid.c_str(), len);
        TextOutA(hdc, textX, textY - 1, sid.c_str(), len);
        TextOutA(hdc, textX + 1, textY + 1, sid.c_str(), len);
        TextOutA(hdc, textX - 1, textY - 1, sid.c_str(), len);
        TextOutA(hdc, textX + 1, textY - 1, sid.c_str(), len);
        TextOutA(hdc, textX - 1, textY + 1, sid.c_str(), len);

        SetTextColor(hdc, RGB(255, 255, 255));
        TextOutA(hdc, textX, textY, sid.c_str(), len);

        DeleteObject(hpen);
        DeleteObject(hbrush);
        ReleaseDC(GetConsoleWindow(), hdc);
    }
};

class CEllipse : public CFigura {
public:
    CEllipse() : CFigura() {};

    CEllipse(int px, int py) : CFigura(px, py) {};

    CEllipse(int w, short h) : CFigura(w, h) {};

    CEllipse(int px, int py, int w, int h, int cp, int cb, int wp) : CFigura(px, py, w, h, cp, cb, wp) {};

    void Draw(bool pclear = false) {
        HDC hdc = GetDC(GetConsoleWindow());

        LOGBRUSH lbBrush;
        lbBrush.lbStyle = BS_SOLID;
        lbBrush.lbColor = pclear ? 0 : GetBrushColor();
        HBRUSH hbrush = CreateBrushIndirect(&lbBrush);
        SelectObject(hdc, hbrush);

        HPEN hpen = (pclear) ? CreatePen(PS_SOLID, 2, 0) : CreatePen(PS_SOLID, 2, nColorPen);
        SelectObject(hdc, hpen);

        Ellipse(hdc, Left, Top, Right, Bottom);
        string sid = to_string(nId);

        int MiddleX = nWidth / 2;
        int MiddleY = nHeight / 2;

        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, (pclear) ? 0 : RGB(255, 255, 255));
        SIZE sz{};
        GetTextExtentPoint32A(hdc, sid.c_str(), (int)sid.size(), &sz);
        TextOutA(hdc, nX + MiddleX - sz.cx / 2, nY + MiddleY - sz.cy / 2, sid.c_str(),
            (int)sid.size());

        DeleteObject(hpen);
        DeleteObject(hbrush);
        ReleaseDC(GetConsoleWindow(), hdc);

        SetBkMode(hdc, TRANSPARENT);

        GetTextExtentPoint32A(hdc, sid.c_str(), (int)sid.size(), &sz);
        int textX = nX + MiddleX - sz.cx / 2;
        int textY = nY + MiddleY - sz.cy / 2;
        int len = (int)sid.size();

        SetTextColor(hdc, RGB(0, 0, 0));
        TextOutA(hdc, textX + 1, textY, sid.c_str(), len);
        TextOutA(hdc, textX - 1, textY, sid.c_str(), len);
        TextOutA(hdc, textX, textY + 1, sid.c_str(), len);
        TextOutA(hdc, textX, textY - 1, sid.c_str(), len);
        TextOutA(hdc, textX + 1, textY + 1, sid.c_str(), len);
        TextOutA(hdc, textX - 1, textY - 1, sid.c_str(), len);
        TextOutA(hdc, textX + 1, textY - 1, sid.c_str(), len);
        TextOutA(hdc, textX - 1, textY + 1, sid.c_str(), len);

        SetTextColor(hdc, RGB(255, 255, 255));
        TextOutA(hdc, textX, textY, sid.c_str(), len);

        DeleteObject(hpen);
        DeleteObject(hbrush);
        ReleaseDC(GetConsoleWindow(), hdc);
    }
};

class CManager {
    CFigura** objfigura;
    int ncount;

public:
    CManager() : objfigura(NULL), ncount(0) {}

    ~CManager() { Clear(); }

    int Add(CFigura* pfig) {
        if (pfig == NULL) return -1;
        objfigura = (CFigura**)realloc(objfigura, sizeof(CFigura*) * (++ncount));
        objfigura[ncount - 1] = pfig;
        return ncount - 1;
    }

    int Delete(CFigura* pfig) {
        if (pfig == NULL || ncount == 0) return -1;

        for (int i = 0; i < ncount; i++) {
            if (objfigura[i] == pfig) {
                delete objfigura[i];

                for (int j = i; j < ncount - 1; j++) {
                    objfigura[j] = objfigura[j + 1];
                }

                ncount--;

                if (ncount > 0) {
                    objfigura = (CFigura**)realloc(objfigura, sizeof(CFigura*) * ncount);
                }
                else {
                    free(objfigura);
                    objfigura = NULL;
                }

                return 0;
            }
        }

        return -1;
    }

    int Delete(int pindex) {
        if (pindex < 0 || pindex >= ncount || ncount == 0) return -1;

        delete objfigura[pindex];

        for (int i = pindex; i < ncount - 1; i++) {
            objfigura[i] = objfigura[i + 1];
        }

        ncount--;

        if (ncount > 0) {
            objfigura = (CFigura**)realloc(objfigura, sizeof(CFigura*) * ncount);
        }
        else {
            free(objfigura);
            objfigura = NULL;
        }

        return 0;
    }

    int Delete(short pid) {
        if (ncount == 0) return -1;

        for (int i = 0; i < ncount; i++) {
            if (((CRectangle*)objfigura[i])->ID == pid) {

                delete objfigura[i];

                for (int j = i; j < ncount - 1; j++) {
                    objfigura[j] = objfigura[j + 1];
                }

                ncount--;

                if (ncount > 0) {
                    objfigura = (CFigura**)realloc(objfigura, sizeof(CFigura*) * ncount);
                }
                else {
                    free(objfigura);
                    objfigura = NULL;
                }

                return 0;
            }
        }

        return -1;
    }

    void Clear() {
        for (int i = 0; i < ncount; i++) {
            delete objfigura[i];
        }
        objfigura = (CFigura**)realloc(objfigura, 0);
        ncount = 0;
    }

    CFigura* GetFigura(int pid) {
        for (int i = 0; i < ncount; i++) {
            if (((CRectangle*)objfigura[i])->ID == pid) {
                return objfigura[i];
            }
        }
        return NULL;
    }


    int GetCount() {
        return ncount;
    }

    __declspec(property(get = GetCount)) int count;

    void Draw() {
        for (int i = 0; i < ncount; i++) {
            objfigura[i]->Draw();
        }
    }

    void Draw(int pid) {
        for (int i = 0; i < ncount; i++) {
            if (((CRectangle*)objfigura[i])->ID == pid) {
                objfigura[i]->Draw();
            }
        }
    }

    void Draw(string pclass) {}

    CFigura* operator[](int index) {
        if (index < 0 || index >= ncount) return NULL;
        return objfigura[index];
    }

    CFigura* operator[](short pid) {
        return GetFigura(pid);
    }
};
bool ReadStringWithESC(string& out);
bool ReadShortWithESC(short& val);