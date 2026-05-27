#include "Labs/class.h"
void CTriangle::Draw()
{
	HDC hdc = GetDC(GetConsoleWindow());
	LOGBRUSH lbBrush;
	lbBrush.lbColor = BrushColor;
	lbBrush.lbStyle = BS_SOLID;

	HBRUSH hbrush = CreateBrushIndirect(&lbBrush);
	SelectObject(hdc, hbrush);

	HPEN hpen = CreatePen(PS_SOLID, 2, PenColor);
	SelectObject(hdc, hpen);

	
	POINT pt[4];
	pt[0].x = X + nWidth / 2; pt[0].y = Top;
	pt[1].x = this->Right; pt[1].y = Bottom;
	pt[2].x = Left; pt[2].y = Bottom; 
	pt[3].x = pt[0].x; pt[3].y = pt[0].y;
	Polygon(hdc, pt, 4);

	string sid = to_string(id);
	TextOutA(hdc, MiddleX, MiddleY, sid.c_str(), sid.size());

	DeleteObject(hpen);
	DeleteObject(hbrush);
	ReleaseDC(GetConsoleWindow(), hdc);
}