
// FiveInARowDlg.h: 头文件
//

#pragma once
#include"CChessManager.h"

// CFiveInARowDlg 对话框
class CFiveInARowDlg : public CDialogEx
{
// 构造
	CChessManager m_Manager;
	CChess m_Chess;
	CFont m_FontTimer;
	CFont m_FontOver;
	int m_iTime;
	double m_iTime_black = 10;
	double m_iTime_white = 10;
	int number1 = 0;
	bool m_bState;
public:
	CFiveInARowDlg(CWnd* pParent = nullptr);	// 标准构造函数
	
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FIVEINAROW_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	void OnLButtonUp(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUP(UINT nFlags, CPoint point);
	bool NewGame(int x, int y);
	bool About(int x, int y);
	bool Exit(int x, int y);	//退出程序
	bool BackToIndex(int x, int y);	//返回主页面
	bool PlayMusic(int x, int y);	//播放音乐
	bool PlayMusic_2(int x, int y);	//新页面播放音乐
	bool SaveGame(int x, int y);//保存棋谱功能
	bool OpenGame(int x, int y);//导入棋谱功能
	bool BackChess(int x, int y);//悔棋功能
	bool Stop(int x, int y);//暂停功能
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
