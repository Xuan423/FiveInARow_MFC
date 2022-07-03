#pragma once
enum COLOR { BLACK, WHITE };
class CChess
{
	
	int m_Num;			//ĞòºÅ
	int m_x;
	int m_y;
	COLOR m_Color;
	
public:
	CChess();
	~CChess();
	
	void Set(int num, int x, int y, COLOR color);
	COLOR GetColor()
	{
		return m_Color;
	}
	int GetNum()
	{
		return m_Num;
	}
	int GetX()
	{
		return m_x;
	}
	int GetY()
	{
		return m_y;
	}
	void Show(CDC* pDC);
	static int m_dx;		//ÆåÅÌ×óÉÏ½ÇÆÁÄ»×ø±ê
	static int m_dy;		//ÆåÅÌ×óÉÏ½ÇÆÁÄ»×ø±êy
	static double m_d;		//Æå×Ó¼ä¾àÀë
};

