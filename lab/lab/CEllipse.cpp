#include "Labs/class.h"
void CEllipse::Draw()
{
	HDC hdc = GetDC(GetConsoleWindow());
	LOGBRUSH lbBrush;
	lbBrush.lbColor = BrushColor;
	lbBrush.lbStyle = BS_SOLID;

	HBRUSH hbrush = CreateBrushIndirect(&lbBrush);
	SelectObject(hdc, hbrush);

	HPEN hpen = CreatePen(PS_SOLID, 2, PenColor);
	SelectObject(hdc, hpen);

	Ellipse(hdc, Left, Top, Right, Bottom);

	string sid = to_string(id);
	TextOutA(hdc, MiddleX, MiddleY, sid.c_str(), sid.size());

	DeleteObject(hpen);
	DeleteObject(hbrush);
	ReleaseDC(GetConsoleWindow(), hdc);
}