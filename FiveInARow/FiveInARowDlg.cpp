
// FiveInARowDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "FiveInARow.h"
#include "FiveInARowDlg.h"
#include "afxdialogex.h"
#include <mmsystem.h>
#include <fstream>//用于保存文件
#pragma comment(lib, "winmm.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


int flag = 0;//是否开始新游戏
int musiccontrol = 0;//控制音乐
int stopcontrol = 0;//控制暂停继续
int openflag = 0,open_flag = 0;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()

void CAboutDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


// CFiveInARowDlg 对话框



CFiveInARowDlg::CFiveInARowDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FIVEINAROW_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFiveInARowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFiveInARowDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()	
END_MESSAGE_MAP()


// CFiveInARowDlg 消息处理程序

BOOL CFiveInARowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SetWindowPos(NULL, 0, 0, 1300, 900, SWP_NOZORDER | SWP_NOMOVE);
	m_FontTimer.CreatePointFont(250, _T("Segoe UI Semibold"), NULL);
	m_FontOver.CreatePointFont(350, _T("微软雅黑"), NULL);
	m_bState = false;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFiveInARowDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFiveInARowDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		if (flag == 0)//未开始新游戏状态
		{
			CBitmap bmp;
			BITMAP bm;
			bmp.LoadBitmap(IDB_BITMAP_BK);
			bmp.GetObject(sizeof(BITMAP), &bm);
			CDC MemDC;
			MemDC.CreateCompatibleDC(&dc);
			CBitmap* pOldBitmap = MemDC.SelectObject(&bmp);
			dc.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &MemDC, 0, 0, SRCCOPY);
			MemDC.SelectObject(pOldBitmap);
			m_Manager.Show(&dc);
		}
		if (flag == 1)//开始新游戏状态
		{
			CBitmap bmp2;
			BITMAP bm2;
			bmp2.LoadBitmap(IDB_BITMAP_BK2);
			bmp2.GetObject(sizeof(BITMAP), &bm2);
			CDC MemDC;
			MemDC.CreateCompatibleDC(&dc);
			CBitmap* pOldBitmap = MemDC.SelectObject(&bmp2);
			dc.BitBlt(0, 0, bm2.bmWidth, bm2.bmHeight, &MemDC, 0, 0, SRCCOPY);
			MemDC.SelectObject(pOldBitmap);
			m_Manager.Show(&dc);
		}
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFiveInARowDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CFiveInARowDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (NewGame(point.x, point.y))
	{
		return;
	}

	if (About(point.x, point.y))
	{
		return;
	}
	if (Exit(point.x,point.y))//退出程序
	{
		return;
	}
	if (BackToIndex(point.x, point.y))//退出程序
	{
		return;
	}
	if (PlayMusic(point.x,point.y))//主页面播放音乐
	{
		return;
	}
	if (PlayMusic_2(point.x, point.y))//对局页面播放音乐
	{
		return;
	}
	if (OpenGame(point.x,point.y)) //导入棋谱
	{
		return;
	}
	if (SaveGame(point.x, point.y))//导出棋谱
	{
		return;
	}
	if (BackChess(point.x,point.y))//悔棋
	{
		return;
	}
	if (Stop(point.x,point.y))//暂停
	{
		return;
	}
	if (!m_bState && !PlayMusic(point.x, point.y) && (openflag == 0 || open_flag == 0))
	{
		AfxMessageBox(_T("请选择“开始”按钮开始新的游戏,按Esc键退出游戏！"));
		return;
	}
	int r = m_Manager.Add(point.x, point.y);
	if (r == 0)
	{
		KillTimer(3);//下第一步之前，执黑在计时，因此在下了第一颗黑子之后，应停止计执黑时间，开始计执白时间
		number1++;
		if ((number1) % 2 == 1)//判断开始计执黑时间
		{
			m_iTime_black = 10; //初始化执黑时间
			KillTimer(3);//停止计执白时间
			SetTimer(2, 100, NULL);//触发执黑计时器
		}
		else//判断开始计执白时间
		{
			m_iTime_white = 10;//初始化执白时间
			KillTimer(2);//停止计执黑时间
			SetTimer(3, 100, NULL);//触发执白计时器
		}
		CClientDC dc(this);
		m_Manager.Show(&dc);
		if (m_Manager.GameOver())
		{
			KillTimer(1);//停止计时
			KillTimer(2);
			KillTimer(3);
			CString csTemp;
			if (m_Manager.GetWinner() == WHITE)
			{
				csTemp.Format(_T("白方胜!"));
			}
			else
			{
				csTemp.Format(_T("黑方胜!"));
			}
			m_bState = false;
			CClientDC dc(this);
			CFont* pOldFont = dc.SelectObject(&m_FontOver);
			int OldBkMode = dc.GetBkMode();
			COLORREF OldColor, NewColor1 = RGB(60, 60, 60), NewColor2 = RGB(250, 50, 50);
			dc.SetBkMode(TRANSPARENT);
			OldColor = dc.SetTextColor(NewColor1);
			dc.TextOut(152, 202, csTemp);
			dc.SetTextColor(NewColor2);
			dc.TextOut(150, 200, csTemp);
			dc.SetTextColor(OldColor);
			dc.SetBkMode(OldBkMode);
			dc.SelectObject(pOldFont);
		}
	}
	if (r == 1 && !PlayMusic(point.x, point.y) && !BackToIndex(point.x,point.y) && openflag == 0)
	{
		AfxMessageBox(_T("请在棋盘交叉点落子!"));
	}
	else if (r == 2)
	{
		AfxMessageBox(_T("不可以重复落子!"));
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}
bool CFiveInARowDlg::NewGame(int x, int y)
{
	int x0 = 910, y0 = 250, x1 = 1225, y1 = 318;
	if ((x >= x0 && x <= x1) && (y >= y0 && y <= y1) && (flag == 0))
	{
		m_Manager.NewGame();
		Invalidate();
		m_iTime = 0;
		m_iTime_black = 10;
		m_iTime_white = 10;
		SetTimer(1, 1000, NULL);
		m_bState = true;
		flag = 1;
		return true;
	}
	return false;
}

bool CFiveInARowDlg::About(int x, int y)
{
	int x0 = 910, y0 = 130, x1 = 1225, y1 = 196;
	if ((x >= x0 && x <= x1) && (y >= y0 && y <= y1) && (flag == 0))
	{
		CAboutDlg dlg;
		dlg.DoModal();
		return true;
	}
	return false;
}

void CFiveInARowDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case 1:
		{
			CClientDC dc(this);
			CFont* pOldFont;
			pOldFont = dc.SelectObject(&m_FontTimer);
			m_iTime++;
			CString csTemp;
			csTemp.Format(_T("时间:%04d "), m_iTime);
			COLORREF OldColor, NewColor = RGB(150, 50, 50);
			OldColor = dc.SetTextColor(NewColor);
			dc.TextOut(725, 20, csTemp);
			dc.SetTextColor(OldColor);
			dc.SelectObject(pOldFont);
			break;
		}
	case 2: {//控制计时器2（计执白时间，超时自动判负）
		CClientDC dc(this);
		CFont* pOldFont;
		pOldFont = dc.SelectObject(&m_FontTimer);
		m_iTime_white-=0.1;
		//
		if (m_iTime_white <= 0.1)//超时则停止计时，游戏状态未开始，判负
		{
			KillTimer(2);
			KillTimer(1);
			m_bState = false;
			CString csTemp1;
			csTemp1.Format(_T("黑方胜！"));
			CClientDC dc(this);
			CFont* pOldFont = dc.SelectObject(&m_FontOver);
			int OldBkMode = dc.GetBkMode();
			COLORREF OldColor, NewColor1 = RGB(60, 60, 60), NewColor2 = RGB(250, 50, 50);
			dc.SetBkMode(TRANSPARENT);
			OldColor = dc.SetTextColor(NewColor1);
			dc.TextOut(154, 204, csTemp1);
			dc.SetTextColor(NewColor2);
			dc.TextOut(150, 200, csTemp1);
			dc.SetTextColor(OldColor);
			dc.SetBkMode(OldBkMode);
			dc.SelectObject(pOldFont);
		};
		//
		CString csTemp1;
		csTemp1.Format(_T("白子： % 4.1f "), m_iTime_white);
		COLORREF OldColor, NewColor = RGB(150, 50, 50);
		OldColor = dc.SetTextColor(NewColor);
		dc.TextOut(970, 326, csTemp1);
		dc.SetTextColor(OldColor);
		dc.SelectObject(pOldFont);
		break;
	}
	case 3: {//控制计时器3（计执黑时间，超时自动判负）
		CClientDC dc(this);
		CFont* pOldFont;
		pOldFont = dc.SelectObject(&m_FontTimer);
		m_iTime_black-=0.1;
		//
		if (m_iTime_black <= 0.1)
		{
			KillTimer(3);
			KillTimer(1);
			m_bState = false;
			CString csTemp1;
			csTemp1.Format(_T("白方胜！"));
			CClientDC dc(this);
			CFont* pOldFont = dc.SelectObject(&m_FontOver);
			int OldBkMode = dc.GetBkMode();
			COLORREF OldColor, NewColor1 = RGB(60, 60, 60), NewColor2 = RGB(250, 50, 50);
			dc.SetBkMode(TRANSPARENT);
			OldColor = dc.SetTextColor(NewColor1);
			dc.TextOut(154, 204, csTemp1);
			dc.SetTextColor(NewColor2);
			dc.TextOut(150, 200, csTemp1);
			dc.SetTextColor(OldColor);
			dc.SetBkMode(OldBkMode);
			dc.SelectObject(pOldFont);
		};
		//
		CString csTemp2;
		csTemp2.Format(_T("黑子： % 4.1f "), m_iTime_black);
		COLORREF OldColor, NewColor = RGB(150, 50, 50);
		OldColor = dc.SetTextColor(NewColor);
		dc.TextOut(970, 387, csTemp2);
		dc.SetTextColor(OldColor);
		dc.SelectObject(pOldFont);
		break;
	}
	}
	CDialogEx::OnTimer(nIDEvent);
}

bool CFiveInARowDlg::Exit(int x, int y)
{
	int x0 = 910, y0 = 617, x1 = 1225, y1 = 686;
	if ((x >= x0 && x <= x1) && (y >= y0 && y <= y1) && (flag == 0))
	{
		exit(0);
	}
	return false;
}
bool CFiveInARowDlg::BackToIndex(int x, int y)
{
	int x0 = 1100, y0 = 635, x1 = 1242, y1 = 704;
	if ((x >= x0 && x <= x1) && (y >= y0 && y <= y1) && (flag == 1))
	{
		flag = 0;
		Invalidate();
		KillTimer(1);//停止计时
		KillTimer(2);
		KillTimer(3);
		m_bState = false;//判定为游戏未开始
		m_Manager.NewGame();//清除棋子
		return true;
	}
	return false;
}
bool CFiveInARowDlg::PlayMusic(int x, int y)
{
	int x0 = 910, y0 = 372, x1 = 1225, y1 = 441;
	if ((x >= x0 && x <= x1) && (y >= y0 && y <= y1) && (flag == 0))
	{
		musiccontrol++;
		if (musiccontrol % 2 == 1)
		{
			PlaySound(_T("E:/群星 - 望江南.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		}
		else
		{
			PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		}
		return true;
	}
	return false;
}
bool CFiveInARowDlg::PlayMusic_2(int x, int y)
{
	int x0 = 911, y0 = 635, x1 = 1057, y1 = 704;
	if ((x >= x0 && x <= x1) && (y >= y0 && y <= y1) && (flag == 1))
	{
		musiccontrol++;
		if (musiccontrol % 2 == 1)
		{
			PlaySound(_T("E:/群星 - 望江南.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		}
		else
		{
			PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		}
		return true;
	}
	return false;
}

bool CFiveInARowDlg::SaveGame(int x, int y)
{
	int x0 = 911, y0 = 124, x1 = 1236, y1 = 192;
	if ((x >= x0 && x <= x1) && (y >= y0 && y <= y1) && (flag == 1))
	{
		CFileDialog filedlg(false);
		filedlg.m_ofn.lpstrFilter = L"五子棋文件(*.gam)\0*.gam\0\0";
		if (filedlg.DoModal() != IDOK)
			return false;
		CString filename = filedlg.GetPathName();
		if (filedlg.GetFileExt() == L"")//如果用户没有输入扩展名
			filename += ".gam";
		std::ofstream outfile;
		outfile.open(CStringA(filename));
		if (!outfile)
		{
			AfxMessageBox(_T("保存失败!"));
			return false;
		}
		int n = m_Manager.Getn();
		for (int i = 0; i < n; i++)
		{
			outfile << m_Manager.pm_aChess->GetNum() << '\t' << m_Manager.pm_aChess->GetX() << '\t' << m_Manager.pm_aChess->GetY() << '\n';
			m_Manager.pm_aChess++;
		}
		outfile.close();
		return true;
	}
	return false;
}
bool CFiveInARowDlg::OpenGame(int x, int y)
{
	int x0 = 911, y0 = 495, x1 = 1236, y1 = 562;
	if ((x >= x0 && x <= x1) && (y >= y0 && y <= y1) && (flag == 0))//未开始新游戏
	{
		int i = 0;
		openflag = 1;
		CFileDialog filedlg(TRUE);
		filedlg.m_ofn.lpstrFilter = L"五子棋文件(*.gam)\0*.gam\0\0";
		if (filedlg.DoModal() != IDOK)
			return false;
		CString filename = filedlg.GetPathName();
		if (filedlg.GetFileExt() == L"")
			filename += ".gam";
		std::ifstream infile;
		infile.open(CStringA(filename));
		if (!infile)
		{
			AfxMessageBox(_T("打开失败!"));
			return false;
		}
		m_Manager.NewGame();
		for (i = 0; i < MAX_CHESS; i++)
		{
			int num_temp,x_temp, y_temp;
			infile >> num_temp;
			infile.seekg(infile.tellg().operator+(1));
			if (num_temp != i)
			{
				infile.close();
				break;
			}
			infile >> x_temp;
			infile.seekg(infile.tellg().operator+(1));
			infile >> y_temp;
			infile.seekg(infile.tellg().operator+(1));
			m_Manager.AddSave(x_temp, y_temp);
			open_flag = 1;
		}
		m_bState = true;//游戏状态为开始状态
		flag = 1;//游戏开始
		Invalidate();
		return true;
	}
	return false;
}
bool CFiveInARowDlg::BackChess(int x, int y)
{
	int x0 = 911, y0 = 535, x1 = 1057, y1 = 606;
	if ((x >= x0 && x <= x1) && (y >= y0 && y <= y1))
	{
		m_Manager.Back();
		Invalidate();
		if ((number1) % 2 == 1)
		{
			m_iTime_white = 10;
			KillTimer(2);
			SetTimer(3, 100, NULL);
			number1++;
		}
		else
		{
			m_iTime_black = 10;
			KillTimer(3);
			SetTimer(2, 100, NULL);
			number1++;
		}
		if (!m_bState)
		{
			m_bState = true;
		}
		return true;
	}
	return false;
}
bool CFiveInARowDlg::Stop(int x, int y)
{
	int x0 = 1100, y0 = 535, x1 = 1243, y1 = 606;
	if ((x >= x0 && x <= x1) && (y >= y0 && y <= y1))
	{
		stopcontrol++;
		if (stopcontrol % 2 == 1)//暂停状态
		{
			KillTimer(1);//停止计时
			KillTimer(2);
			KillTimer(3);
			m_bState = false;//游戏状态未开始
		}
		else
		{
			SetTimer(1, 1000, NULL);//创建计时器
			if ((number1) % 2 == 1)
			{
				SetTimer(2, 100, NULL);
			}
			else
			{
				SetTimer(3, 100, NULL);
			}
			m_bState = true;//设置游戏状态开始
		}
		return true;
	}
	return false;
}