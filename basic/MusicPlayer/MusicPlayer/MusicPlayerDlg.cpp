
// MusicPlayerDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MusicPlayer.h"
#include "MusicPlayerDlg.h"
#include "afxdialogex.h"
#include "resource.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMusicPlayerDlg 对话框



CMusicPlayerDlg::CMusicPlayerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MUSICPLAYER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMusicPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PLAYPROGRESS, playProgressBar);
	DDX_Control(pDX, IDC_VOL_BAR, volBar);
	DDX_Control(pDX, IDC_PLAY_MODE, myPlayMode);
}

BEGIN_MESSAGE_MAP(CMusicPlayerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PLAYPROGRESS, &CMusicPlayerDlg::OnNMCustomdrawPlayprogress)

	ON_NOTIFY(NM_CUSTOMDRAW, IDC_VOL_BAR, &CMusicPlayerDlg::OnNMCustomdrawVolBar)
	ON_BN_CLICKED(IDC_BTN_AHEAD, &CMusicPlayerDlg::OnBnClickedBtnAhead)
	ON_BN_CLICKED(IDC_BTN_DELETE, &CMusicPlayerDlg::OnBnClickedBtnDelete)
	ON_BN_CLICKED(IDC_BTN_LOADFILE, &CMusicPlayerDlg::OnBnClickedBtnLoadfile)
END_MESSAGE_MAP()


// CMusicPlayerDlg 消息处理程序

BOOL CMusicPlayerDlg::OnInitDialog()
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
	InitMenu();
	InitControls();
	InitComboxBoxPlayMode();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMusicPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMusicPlayerDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMusicPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




bool CMusicPlayerDlg::InitMenu(void)
{
	pMainMenu = new CMenu();
	pMainMenu->LoadMenu(IDR_MENU2);//IDR_MENU2为菜单ID
	SetMenu(pMainMenu);
	pMainMenu->Detach();
	return false;
}

bool CMusicPlayerDlg::InitControls(void)
{
	this->SetWindowTextW(TEXT("My Music Player"));
	this->SetDlgItemText(IDC_CURRENT_POS, TEXT("00:00"));
	this->SetDlgItemText(IDC_TOTAL_TIME, TEXT("00:00"));

	playProgressBar.SetPos(0);//播放进度初始值
	volBar.SetRange(0, 100);//音量范围
	volBar.SetPos(0);//音量进度条初始值

	return true;
}

bool CMusicPlayerDlg::InitComboxBoxPlayMode(void)
{
	myPlayMode.AddString(TEXT("随机播放"));
	myPlayMode.AddString(TEXT("单曲循环"));
	myPlayMode.AddString(TEXT("顺序播放"));
	myPlayMode.SetCurSel(1);
	return true;
}

bool CMusicPlayerDlg::loadFile()
{
	LPCTSTR szFilters = TEXT("支持的音频文件(*.wav;*.mp3)|*.wav;*.mp3|所有文件 (*.*)|*.*||");
	CFileDialog FileDlg(TRUE, TEXT("mp3"), NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, szFilters);

	if (IDCANCEL == FileDlg.DoModal())
	{
		return FALSE;
	}
	else
	{
		cstrFilePath = FileDlg.GetPathName();
		cstrFileName = FileDlg.GetFileTitle();
		this->SetWindowText(cstrFileName + TEXT("  状态：播放"));
		return TRUE;
	}
	return FALSE;
}


void CMusicPlayerDlg::OnNMCustomdrawPlayprogress(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}




void CMusicPlayerDlg::OnNMCustomdrawVolBar(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CMusicPlayerDlg::OnBnClickedBtnAhead()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMusicPlayerDlg::OnBnClickedBtnDelete()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMusicPlayerDlg::OnBnClickedBtnLoadfile()
{
	// TODO: 在此添加控件通知处理程序代码
	loadFile();
}
