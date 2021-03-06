
// MusicPlayerDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MusicPlayer.h"
#include "MusicPlayerDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "InputBoxDlg.h"
#include <locale> 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CListCtrl CMusicPlayerDlg::myMusicList;

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
	, m_Length(0)
	, bePlay(false)
	,beLoadAndPlay(true)
	,cstrFileName(TEXT(""))
	,cstrFilePath(TEXT(""))
	,pMainMenu(NULL)
	,m_PlayMode(1)
	,BEOPENPLAYERFIRST(TRUE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMusicPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PLAYPROGRESS, playProgressBar);
	DDX_Control(pDX, IDC_VOL_BAR, volBar);
	DDX_Control(pDX, IDC_PLAY_MODE, myPlayMode);
	DDX_Control(pDX, IDC_PLAY_LIST, myPlayList);
	DDX_Control(pDX, IDC_LIST_MUSICLIST, myMusicList);
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
	ON_BN_CLICKED(IDC_BTN_PAUSE, &CMusicPlayerDlg::OnBnClickedBtnPause)
	ON_WM_TIMER()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BTN_PREVIOUS_ONE, &CMusicPlayerDlg::OnBnClickedBtnPreviousOne)
	ON_BN_CLICKED(IDC_BTN_NEXT_ONE, &CMusicPlayerDlg::OnBnClickedBtnNextOne)
	ON_BN_CLICKED(IDC_BTN_BACK, &CMusicPlayerDlg::OnBnClickedBtnBack)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_PLAY_LIST, &CMusicPlayerDlg::OnLvnItemchangedPlayList)
	ON_CBN_SELCHANGE(IDC_PLAY_MODE, &CMusicPlayerDlg::OnCbnSelchangePlayMode)
	ON_BN_CLICKED(IDC_BTN_ADD, &CMusicPlayerDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_ADD_MUSIC_LIST, &CMusicPlayerDlg::OnBnClickedAddMusicList)
	ON_NOTIFY(NM_DBLCLK, IDC_PLAY_LIST, &CMusicPlayerDlg::OnDblclkPlayList)
	ON_NOTIFY(NM_RCLICK, IDC_PLAY_LIST, &CMusicPlayerDlg::OnRclickPlayList)
	ON_COMMAND(ID_MENU_OPEN, &CMusicPlayerDlg::OnMenuOpen)
	ON_COMMAND(ID_EXIT, &CMusicPlayerDlg::OnExit)
	ON_COMMAND(ID_MENU_PLAY1, &CMusicPlayerDlg::OnMenuPlay1)
	ON_COMMAND(ID_MENU_PAUSE1, &CMusicPlayerDlg::OnMenuPause1)
	ON_COMMAND(ID_MENU_PREVIOUS, &CMusicPlayerDlg::OnMenuPrevious)
	ON_COMMAND(ID_MENU_AHEAD, &CMusicPlayerDlg::OnMenuAhead)
	ON_COMMAND(ID_MENU_BACK, &CMusicPlayerDlg::OnMenuBack)
	ON_COMMAND(ID_MENU_NEXT, &CMusicPlayerDlg::OnMenuNext)
	ON_COMMAND(ID_MENU_RAND, &CMusicPlayerDlg::OnMenuRand)
	ON_COMMAND(ID_MENU_SINGLE, &CMusicPlayerDlg::OnMenuSingle)
	ON_COMMAND(ID_MENU_TURN, &CMusicPlayerDlg::OnMenuTurn)
	
	
	ON_COMMAND(ID_MENU_PLAY, &CMusicPlayerDlg::OnMenuPlay)
	ON_COMMAND(ID_MENU_PAUSE, &CMusicPlayerDlg::OnMenuPause)
	ON_COMMAND(ID_MENU_NEXTOE, &CMusicPlayerDlg::OnMenuNextoe)
	ON_COMMAND(ID_MENU_LAST, &CMusicPlayerDlg::OnMenuLast)
	ON_COMMAND(ID_MENU_DELETE, &CMusicPlayerDlg::OnMenuDelete)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_MUSICLIST, &CMusicPlayerDlg::OnDblclkListMusiclist)
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
	InitPlayList();
	volBar.SetPos(0);//音量进度条初始值
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



//初始化菜单
bool CMusicPlayerDlg::InitMenu(void)
{
	pMainMenu = new CMenu();
	pMainMenu->LoadMenu(IDR_MENU2);//IDR_MENU2为菜单ID
	playMenu = pMainMenu->GetSubMenu(1);
	SetMenu(pMainMenu);
	pMainMenu->Detach();
	return false;
}

//初始化控件
bool CMusicPlayerDlg::InitControls(void)
{
	this->SetWindowTextW(TEXT("My Music Player"));
	this->SetDlgItemText(IDC_CURRENT_POS, TEXT("00:00"));
	this->SetDlgItemText(IDC_TOTAL_TIME, TEXT("00:00"));

	playProgressBar.SetPos(0);//播放进度初始值
	volBar.SetRange(0, 100);//音量范围
	UpdateData(false);

	return true;
}

//初始化播放模式组合框
bool CMusicPlayerDlg::InitComboxBoxPlayMode(void)
{
	myPlayMode.AddString(TEXT("随机播放"));
	myPlayMode.AddString(TEXT("单曲循环"));
	myPlayMode.AddString(TEXT("顺序播放"));
	myPlayMode.SetCurSel(1);
	return true;
}

//加载文件
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
		filePathMap.insert(pair<CString, CString>(cstrFileName, cstrFilePath));
		if (beLoadAndPlay)
		{
			this->SetWindowText(cstrFileName + TEXT("  状态：播放"));
		}
		return TRUE;
	}
	return FALSE;
}



//初始化列表
bool CMusicPlayerDlg::InitPlayList(void)
{
	myPlayList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);//显示网格线，点击某一行改行全部选中
	myPlayList.ModifyStyle(0, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL);
	myMusicList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);//显示网格线，点击某一行改行全部选中
	myMusicList.ModifyStyle(0, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL);

	LVCOLUMN lvc;

	lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt = LVCFMT_CENTER;
	lvc.cx = TURNWIDTH;
	lvc.pszText = _T("序号");

	myMusicList.InsertColumn(ID_TURN, &lvc);

	lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt = LVCFMT_CENTER;
	lvc.cx = MUSICLISTNAME;
	lvc.pszText = _T("歌单名");

	myMusicList.InsertColumn(ID_MUSICLISTNAME, &lvc);

	lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt = LVCFMT_CENTER;
	lvc.cx = TURNWIDTH;
	lvc.pszText = _T("序号");

	myPlayList.InsertColumn(ID_TURN, &lvc);

	lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt = LVCFMT_CENTER;
	lvc.cx = FILENAMEWIDTH;
	lvc.pszText = _T("歌曲名");

	myPlayList.InsertColumn(ID_FILENAME, &lvc);

/*	lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt = LVCFMT_CENTER;
	lvc.cx = FILETIMEWIDTH;
	lvc.pszText = _T("歌曲时长");

	myPlayList.InsertColumn(ID_FILETIME, &lvc);
*/

	LVITEM item;
	int index;
	CString strTmp;

	item.mask = LVIF_TEXT;
	item.iSubItem = 0;

	item.iItem = (myMusicList.GetItemCount() <= 0) ? 0 : myMusicList.GetItemCount();
	strTmp.Format(TEXT("%d"), ++item.iItem);
	item.pszText = strTmp.GetBuffer(strTmp.GetLength());
	index = myMusicList.InsertItem(&item);

	CFile fp;
	fp.Open(L"历史播放.txt", CFile::modeCreate,NULL);
	fp.Close();

	myMusicList.SetItemText(index, ID_MUSICLISTNAME, TEXT("历史播放"));
	myMusicList.SetItemState(index, LVIS_SELECTED, LVIS_SELECTED);

	return false;
}

//播放文件
bool CMusicPlayerDlg::PlayFile(CString filePath)
{
	bePlay = false;
	SetTimer(ID_PLAYERTIMER, 1000, NULL);
	mciSendCommand(m_wDeviceID, MCI_CLOSE, 0, NULL);

	MCI_OPEN_PARMS mciOpen; //打开参数
	MCI_PLAY_PARMS mciPlay; //播放参数
	mciOpen.lpstrElementName = filePath.GetBuffer(filePath.GetLength());
	filePath.ReleaseBuffer(filePath.GetLength());

	MCIERROR err= mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&mciOpen);

	if (err)
	{
		mciGetErrorString(err, strMciError, sizeof(strMciError));
		if (IDOK == AfxMessageBox(strMciError, MB_OK | MB_ICONERROR))
		{
			return false;
		}

	}

	else
	{
		m_wDeviceID = mciOpen.wDeviceID;
		MCI_STATUS_PARMS mciStatus;
		mciStatus.dwItem = MCI_STATUS_LENGTH;
		mciSendCommand(m_wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciStatus);
		m_Length = mciStatus.dwReturn;
		mciSendCommand(m_wDeviceID, MCI_PLAY, 0,(DWORD)(LPVOID)&mciPlay);

		//写入历史播放歌单
		//设置CStdioFile可读入中文字体   (以下两行)    
		TCHAR* old_locale = _tcsdup(_tsetlocale(LC_CTYPE, NULL));
		_tsetlocale(LC_CTYPE, _T("chs"));

		CStdioFile fp;
		CString str;
		fp.Open(L"历史播放.txt", CFile::modeWrite);
		fp.Seek(0, CFile::end);
		str.Format(TEXT("%s\n"), cstrFileName);
		fp.WriteString(str);
		fp.Close();
		//操作完文件后要释放    
		_tsetlocale(LC_CTYPE, old_locale);
		free(old_locale);

		playProgressBar.SetRange(0, m_Length);
		playProgressBar.SetPos(0);
		

		if (BEOPENPLAYERFIRST)
		{
			CString strVolume;
			strVolume.Format(TEXT("%d"), 50);
			this->SetDlgItemText(IDC_VOL_EDIT, strVolume);
			SetVolume(50);
			volBar.SetPos(50);
			BEOPENPLAYERFIRST = FALSE;
		}
		
		getCurrentSelect();
		m_CurrentPlayIndex = m_CurrentSelect;
		m_strTotalLength= ConvertTimeToString(m_Length);
		this->SetDlgItemText(IDC_TOTAL_TIME, m_strTotalLength);
		myPlayList.SetItemText(m_CurrentSelect, ID_FILETIME, m_strTotalLength);

		UpdateData(false);
		bePlay = true;
		return true;
	}
	return false;
}

//调节音量
void CMusicPlayerDlg::SetVolume(int Vol)
{
	MCI_DGV_SETAUDIO_PARMS mciSetAudioPara;//音量参数

	mciSetAudioPara.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	mciSetAudioPara.dwCallback = (DWORD_PTR)this->GetSafeHwnd();
	mciSetAudioPara.dwValue = Vol * 10;//设置音量
	mciSendCommand(m_wDeviceID, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD)(LPVOID)&mciSetAudioPara);//发送设置音量指令
}


//转换时间
CString CMusicPlayerDlg::ConvertTimeToString(int time)
{
	CString strTTS;
	int Second = 0;
	int Minute = 0;

	Second = time / 1000; //将毫秒转换为秒

	if (Second < 60)
	{
		Minute = 0;
		strTTS.Format(TEXT("%02d:%02d"), Minute, Second);
		return strTTS;
	}
	else {
		Minute = Second / 60;
		Second = Second % 60; 
		strTTS.Format(TEXT("%02d:%02d"), Minute,Second);
		return strTTS;
	};
}


//设置窗口标题
void CMusicPlayerDlg::setWindowTitle(CString fileName, bool playFlag)
{
	if (playFlag)
	{
		this->SetWindowText(fileName + TEXT("  状态：播放"));
		return;
	}
	else
	{
		this->SetWindowText(fileName + TEXT("  状态：暂停"));
		return;
	}
}


//暂停播放
void CMusicPlayerDlg::musicPause()
{
	if (bePlay)
	{
		bePlay = false;
		setWindowTitle(cstrFileName, bePlay);
		MCI_GENERIC_PARMS mciPause;//MCI暂停参数
		mciSendCommand(m_wDeviceID, MCI_PAUSE, 0, (DWORD)(LPVOID)&mciPause);//发送暂停命令
		SetDlgItemText(IDC_BTN_PAUSE, TEXT("播放"));
	}
	else
	{
		bePlay = true;
		setWindowTitle(cstrFileName, bePlay);
		MCI_PLAY_PARMS mciPlay;//MCI播放参数
		mciSendCommand(m_wDeviceID, MCI_PLAY, 0, (DWORD)(LPVOID)&mciPlay);//发送播放命令
		SetDlgItemText(IDC_BTN_PAUSE, TEXT("暂停"));
	}
}

//更新播放时间
void CMusicPlayerDlg::updateCurrentPosText()
{
	MCI_STATUS_PARMS mciStatus;
	mciStatus.dwItem = MCI_STATUS_POSITION;
	mciSendCommand(m_wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciStatus);

	int dCurrentPos = mciStatus.dwReturn;
	m_strCurrentLength = ConvertTimeToString(dCurrentPos);	//将得到的毫秒转换为分钟和秒
	SetDlgItemText(IDC_CURRENT_POS, m_strCurrentLength);
}

//添加歌曲到列表
void CMusicPlayerDlg::addFileToPlayList()
{
	LVITEM item;
	int index;
	CString strTmp;

	item.mask = LVIF_TEXT;
	item.iSubItem = 0;

	item.iItem = (myPlayList.GetItemCount() <= 0) ? 0 :myPlayList.GetItemCount();
	strTmp.Format(TEXT("%d"), ++item.iItem);
	item.pszText = strTmp.GetBuffer(strTmp.GetLength());
	index = myPlayList.InsertItem(&item);


	myPlayList.SetItemText(index, ID_FILENAME, cstrFileName);
	//myPlayList.SetItemText(index, ID_FILETIME, m_strTotalLength);
	//myPlayList.SetItemState(index, LVIS_SELECTED, LVIS_SELECTED);
}

void CMusicPlayerDlg::deleteMusic()
{
	CString str;
	getCurrentSelect();
	int temp = m_CurrentSelect;
	str = myPlayList.GetItemText(m_CurrentSelect, ID_TURN);
	if (_ttoi(str)-1 == m_CurrentPlayIndex)
	{
		myPlayList.DeleteItem(m_CurrentSelect);
		mciSendCommand(m_wDeviceID, MCI_CLOSE, 0, 0);
		InitControls();
	}
	else
	{
		myPlayList.DeleteItem(m_CurrentSelect);
		m_CurrentSelect--;
		myPlayList.SetFocus();
		myPlayList.SetItemState(m_CurrentSelect, LVIS_SELECTED, LVIS_SELECTED);
	}
	int i = myPlayList.GetItemCount() - m_CurrentSelect;
	CString b;
	for (i; i > 0; i--)
	{
		b.Format(TEXT("%d"),temp+1);
		myPlayList.SetItemText(temp++,ID_TURN,b);
	}
}

//上一曲
void CMusicPlayerDlg::goPrevious()
{
	if (0 == myPlayList.GetItemCount())
	{
		mciSendCommand(NULL, MCI_CLOSE, 0, 0);
		return;
	}
	else if(1== myPlayList.GetItemCount())
	{
		return;
	}
	else
	{
		getCurrentSelect();
		if (m_CurrentSelect == 0)
		{
			m_CurrentSelect = myPlayList.GetItemCount()-1;
		}
		else
		{
			m_CurrentSelect -= 1;
		}
		myPlayList.SetFocus();
		myPlayList.SetItemState(m_CurrentSelect, LVIS_SELECTED, LVIS_SELECTED);
		cstrFileName = myPlayList.GetItemText(m_CurrentSelect, ID_FILENAME);
		cstrFilePath = filePathMap[cstrFileName];
		PlayFile(cstrFilePath);
		setWindowTitle(cstrFileName, bePlay);
	}
}

//下一曲
void CMusicPlayerDlg::goNext()
{
	if (0 == myPlayList.GetItemCount())
	{
		mciSendCommand(NULL, MCI_CLOSE, 0, 0);
		return;
	}
	else if (1 == myPlayList.GetItemCount())
	{
		return;
	}
	else
	{
		getCurrentSelect();
		if (m_CurrentSelect == myPlayList.GetItemCount() - 1)
		{
			m_CurrentSelect = 0;
		}
		else
		{
			m_CurrentSelect += 1;
		}
		myPlayList.SetFocus();
		myPlayList.SetItemState(m_CurrentSelect, LVIS_SELECTED, LVIS_SELECTED);
		cstrFileName = myPlayList.GetItemText(m_CurrentSelect, ID_FILENAME);
		cstrFilePath = filePathMap[cstrFileName];
		PlayFile(cstrFilePath);
		setWindowTitle(cstrFileName, bePlay);
	}

}

//快进
void CMusicPlayerDlg::goAhead()
{
	int pos = playProgressBar.GetPos();//得到进度条位置

	MCI_SEEK_PARMS mciSeek;//MCI设备查找参数
	MCI_PLAY_PARMS mciPlay;

	mciSeek.dwTo = pos;
	mciSeek.dwTo += 10000;
	mciPlay.dwFrom = mciSeek.dwTo;
	mciSendCommand(m_wDeviceID, MCI_SEEK, MCI_TO, (DWORD)(LPVOID)&mciSeek);
	mciSendCommand(m_wDeviceID, MCI_PLAY, MCI_FROM | MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
	playProgressBar.SetPos(mciPlay.dwFrom);
}


//快退
void CMusicPlayerDlg::goBack()
{
	int pos = playProgressBar.GetPos();//得到进度条位置

	MCI_SEEK_PARMS mciSeek;//MCI设备查找参数
	MCI_PLAY_PARMS mciPlay;

	mciSeek.dwTo = pos;
	mciSeek.dwTo -= 10000;
	mciPlay.dwFrom = mciSeek.dwTo;
	mciSendCommand(m_wDeviceID, MCI_SEEK, MCI_TO, (DWORD)(LPVOID)&mciSeek);
	mciSendCommand(m_wDeviceID, MCI_PLAY, MCI_FROM | MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
	playProgressBar.SetPos(mciPlay.dwFrom);
}

//获得当前选中的歌曲索引
void CMusicPlayerDlg::getCurrentSelect()
{
	int index = 0;
	POSITION pos = myPlayList.GetFirstSelectedItemPosition();
	index = myPlayList.GetNextSelectedItem(pos);
	m_CurrentSelect = index;
}

void CMusicPlayerDlg::getCurrentSelect1()
{
	int index = 0;
	POSITION pos = myMusicList.GetFirstSelectedItemPosition();
	index = myPlayList.GetNextSelectedItem(pos);
	m_CurrentSelect1 = index;
}

//设置播放模式
void CMusicPlayerDlg::setPlayMode()
{
	srand((unsigned int)time(NULL));

	int randNum=0;
	int nowSelect;
	switch (m_PlayMode)
	{
	case ORDER_MODE:
		goNext();
		break;
	case RAND_MODE:
		randNum = rand() % myPlayList.GetItemCount();
		myPlayList.SetFocus();
		myPlayList.SetItemState(randNum, LVIS_SELECTED, LVIS_SELECTED);
		nowSelect=myPlayList.GetNextItem(-1, LVNI_SELECTED);
		cstrFileName = myPlayList.GetItemText(nowSelect, ID_FILENAME);
		cstrFilePath = filePathMap[cstrFileName];
		PlayFile(cstrFilePath);
		setWindowTitle(cstrFileName, bePlay);
		break;
	case SINGLE_MODE:
		getCurrentSelect();
		cstrFileName = myPlayList.GetItemText(m_CurrentSelect, ID_FILENAME);
		cstrFilePath = filePathMap[cstrFileName];
		PlayFile(cstrFilePath);
		setWindowTitle(cstrFileName, bePlay);
	default:
		break;
	}
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
	goAhead();
}


void CMusicPlayerDlg::OnBnClickedBtnDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	
	getCurrentSelect();
	getCurrentSelect1();
	cstrMusicList = myMusicList.GetItemText(m_CurrentSelect1, ID_MUSICLISTNAME);

	TCHAR* old_locale = _tcsdup(_tsetlocale(LC_CTYPE, NULL));
	_tsetlocale(LC_CTYPE, _T("chs"));

	CStdioFile fp,fp1;
	CString str;
	CString cstrFileName1;
	fp.Open(cstrMusicList + L".txt", CFile::modeRead);
	fp1.Open(L"11.txt", CFile::modeCreate);
	fp1.Close();
	fp1.Open(L"11.txt", CFile::modeWrite);
	cstrFileName1 = myPlayList.GetItemText(m_CurrentSelect, ID_FILENAME);
	while (fp.ReadString(str))
	{
		if (str != cstrFileName1)
		{
			str += "\n";
			fp1.WriteString(str);
			str = "";
		}
	}
	fp.Close();
	fp1.Close();

	_tsetlocale(LC_CTYPE, old_locale);
	free(old_locale);

	CFile::Remove(cstrMusicList + L".txt");
	CFile::Rename(L"11.txt", cstrMusicList + L".txt");
	deleteMusic();
}


void CMusicPlayerDlg::OnBnClickedBtnLoadfile()
{
	// TODO: 在此添加控件通知处理程序代码
	beLoadAndPlay = true;
	if (loadFile())
	{
		PlayFile(cstrFilePath);
		ConvertTimeToString(m_Length);
		addFileToPlayList();
	}
	else
	{
		return;
	}
}




void CMusicPlayerDlg::OnBnClickedBtnPause()
{
	// TODO: 在此添加控件通知处理程序代码
	musicPause();
}


void CMusicPlayerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	MCI_STATUS_PARMS mciStatus;
	mciStatus.dwItem = MCI_STATUS_POSITION;

	mciSendCommand(m_wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, ((DWORD)(LPVOID)&mciStatus));
	currentPos = mciStatus.dwReturn; //获得当前播放位置
	playProgressBar.SetPos(currentPos);	  //更新进度条位置
	if (!BEOPENPLAYERFIRST)
	{
		updateCurrentPosText();
	}
	if (playProgressBar.GetPos() == m_Length)
	{
		setPlayMode();
	}
	/*if (InputBoxDlg::beAddList == true)
	{
		LVITEM item;
		int index;
		CString strTmp;

		item.mask = LVIF_TEXT;
		item.iSubItem = 0;

		item.iItem = (myMusicList.GetItemCount() <= 0) ? 0 : myMusicList.GetItemCount();
		strTmp.Format(TEXT("%d"), ++item.iItem);
		item.pszText = strTmp.GetBuffer(strTmp.GetLength());
		index = myMusicList.InsertItem(&item);

		
		myMusicList.SetItemText(index, ID_MUSICLISTNAME, InputBoxDlg::musicList);
		myMusicList.SetItemState(index, LVIS_SELECTED, LVIS_SELECTED);
		InputBoxDlg::beAddList = false;
		
	}*/
	CDialogEx::OnTimer(nIDEvent);
}

//处理播放进度条和音量进度条
void CMusicPlayerDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (*pScrollBar == volBar)
	{
		int vol = volBar.GetPos();
		SetVolume(vol);
		CString temp;
		temp.Format(TEXT("%d"), vol);
		this->SetDlgItemText(IDC_VOL_EDIT, temp);
	}
	int pos = playProgressBar.GetPos();

	MCI_SEEK_PARMS mciSeek; 
	MCI_PLAY_PARMS mciPlay;
	mciSeek.dwTo = pos; //设置跳转后的位置
	mciPlay.dwFrom = mciSeek.dwTo; //设置播放位置

	mciSendCommand(m_wDeviceID, MCI_SEEK, MCI_TO, (DWORD)(LPVOID)&mciSeek);
	mciSendCommand(m_wDeviceID, MCI_PLAY, MCI_FROM | MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
	playProgressBar.SetPos(mciPlay.dwFrom);
	bePlay = true;

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CMusicPlayerDlg::OnBnClickedBtnPreviousOne()
{
	// TODO: 在此添加控件通知处理程序代码
	goPrevious();
}


void CMusicPlayerDlg::OnBnClickedBtnNextOne()
{
	// TODO: 在此添加控件通知处理程序代码
	goNext();
}


void CMusicPlayerDlg::OnBnClickedBtnBack()
{
	// TODO: 在此添加控件通知处理程序代码
	goBack();
}



void CMusicPlayerDlg::OnLvnItemchangedPlayList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	CString str;
	int counter;

	counter = myPlayList.GetItemCount();
	str.Format(TEXT("播放列表(共: %d 首)"), counter);
	GetDlgItem(IDC_GROUPLIST)->SetWindowText(str);

	*pResult = 0;

}


void CMusicPlayerDlg::OnCbnSelchangePlayMode()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = myPlayMode.GetCurSel();
	m_PlayMode = index;
}


void CMusicPlayerDlg::OnBnClickedBtnAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	beLoadAndPlay = false;
	if (loadFile())
	{
		getCurrentSelect();
		myPlayList.SetItemState(m_CurrentSelect, LVNI_FOCUSED | LVIS_SELECTED, LVNI_FOCUSED | LVIS_SELECTED);
		addFileToPlayList();

		getCurrentSelect1();
		cstrMusicList = myMusicList.GetItemText(m_CurrentSelect1, ID_MUSICLISTNAME);

		//设置CStdioFile可读入中文字体  
		TCHAR* old_locale = _tcsdup(_tsetlocale(LC_CTYPE, NULL));
		_tsetlocale(LC_CTYPE, _T("chs"));


		CStdioFile fp;
		CString str;
		fp.Open(cstrMusicList + L".txt", CFile::modeWrite);
		fp.Seek(0, CFile::end);
		str.Format(TEXT("%s\n"), cstrFileName);
		fp.WriteString(str);
		fp.Close();

		//操作完文件后要释放    
		_tsetlocale(LC_CTYPE, old_locale);
		free(old_locale);

		return;
	}
	else
	{
		return;
	}
}


void CMusicPlayerDlg::OnBnClickedAddMusicList()
{
	// TODO: 在此添加控件通知处理程序代码
	InputBoxDlg inputBox;
	inputBox.DoModal();
}



//双击播放
void CMusicPlayerDlg::OnDblclkPlayList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	getCurrentSelect();
	if (-1 != m_CurrentSelect)
	{
		cstrFileName = myPlayList.GetItemText(m_CurrentSelect, ID_FILENAME);
		cstrFilePath = filePathMap[cstrFileName];
		PlayFile(cstrFilePath);
		setWindowTitle(cstrFileName, bePlay);
	}
	*pResult = 0;
}

//单击鼠标右键显示下拉菜单
void CMusicPlayerDlg::OnRclickPlayList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	getCurrentSelect();
	if (m_CurrentSelect != -1)
	{
		CMenu menu;
		DWORD dwPos = GetMessagePos();
		CPoint point(LOWORD(dwPos), HIWORD(dwPos));
		VERIFY(menu.LoadMenu(IDR_MENU1));
		CMenu* popupMenu = menu.GetSubMenu(0);
		if (bePlay)
		{
			popupMenu->CheckMenuItem(ID_MENU_PLAY, MF_CHECKED);
		}
		else
		{
			popupMenu->CheckMenuItem(ID_MENU_PAUSE, MF_CHECKED);
		}

		ASSERT(popupMenu != NULL);
		popupMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
	}
	*pResult = 0;
}


void CMusicPlayerDlg::OnMenuOpen()
{
	// TODO: 在此添加命令处理程序代码
	CMusicPlayerDlg::OnBnClickedBtnLoadfile();
	
}


void CMusicPlayerDlg::OnExit()//退出应用程序
{
	// TODO: 在此添加命令处理程序代码
	SendMessage(WM_CLOSE, 0, 0);
}


void CMusicPlayerDlg::OnMenuPlay1()
{
	// TODO: 在此添加命令处理程序代码
	bePlay = true;
	MCI_PLAY_PARMS mciPlay;
	mciSendCommand(m_wDeviceID, MCI_PLAY, 0, (DWORD)(LPVOID)&mciPlay);

	this->SetWindowText(cstrFileName + TEXT(" 状态：播放"));
	this->SetDlgItemText(IDC_BTN_PAUSE, TEXT("暂停"));
	playMenu->CheckMenuItem(ID_MENU_PLAY1, MF_CHECKED);
	playMenu->CheckMenuItem(ID_MENU_PAUSE1, MF_UNCHECKED);
}


void CMusicPlayerDlg::OnMenuPause1()
{
	// TODO: 在此添加命令处理程序代码
	musicPause();
	this->SetDlgItemText(IDC_BTN_PAUSE, TEXT("播放"));
	playMenu->CheckMenuItem(ID_MENU_PLAY1, MF_UNCHECKED);
	playMenu->CheckMenuItem(ID_MENU_PAUSE1, MF_CHECKED);
}


void CMusicPlayerDlg::OnMenuPrevious()
{
	// TODO: 在此添加命令处理程序代码
	goPrevious();
}




void CMusicPlayerDlg::OnMenuAhead()
{
	// TODO: 在此添加命令处理程序代码
	goAhead();
}


void CMusicPlayerDlg::OnMenuBack()
{
	// TODO: 在此添加命令处理程序代码
	goBack();
}


void CMusicPlayerDlg::OnMenuNext()
{
	// TODO: 在此添加命令处理程序代码
	goNext();
}


void CMusicPlayerDlg::OnMenuRand()
{
	// TODO: 在此添加命令处理程序代码
	m_PlayMode = RAND_MODE;
	myPlayMode.SetCurSel(RAND_MODE);
}


void CMusicPlayerDlg::OnMenuSingle()
{
	// TODO: 在此添加命令处理程序代码
	m_PlayMode = SINGLE_MODE;
	myPlayMode.SetCurSel(SINGLE_MODE);
}


void CMusicPlayerDlg::OnMenuTurn()
{
	// TODO: 在此添加命令处理程序代码
	m_PlayMode = ORDER_MODE;
	myPlayMode.SetCurSel(ORDER_MODE);
}






void CMusicPlayerDlg::OnMenuPlay()
{
	// TODO: 在此添加命令处理程序代码
	getCurrentSelect();
	cstrFileName = myPlayList.GetItemText(m_CurrentSelect, ID_FILENAME);
	cstrFilePath = filePathMap[cstrFileName];
	PlayFile(cstrFilePath);
	this->SetWindowText(cstrFileName + TEXT("  状态：播放"));
	SetDlgItemText(IDC_BTN_PAUSE, TEXT("播放"));
}


void CMusicPlayerDlg::OnMenuPause()
{
	// TODO: 在此添加命令处理程序代码
	musicPause();
	this->SetWindowText(cstrFileName + TEXT("  状态：暂停"));
	SetDlgItemText(IDC_BTN_PAUSE, TEXT("暂停"));
}


void CMusicPlayerDlg::OnMenuNextoe()
{
	// TODO: 在此添加命令处理程序代码
	goNext();
}


void CMusicPlayerDlg::OnMenuLast()
{
	// TODO: 在此添加命令处理程序代码
	goPrevious();
}


void CMusicPlayerDlg::OnMenuDelete()
{
	// TODO: 在此添加命令处理程序代码
	deleteMusic();

}

//双击展示歌单
void CMusicPlayerDlg::OnDblclkListMusiclist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	myPlayList.DeleteAllItems();
	getCurrentSelect1();
	cstrMusicList = myMusicList.GetItemText(m_CurrentSelect1, ID_MUSICLISTNAME);

	TCHAR* old_locale = _tcsdup(_tsetlocale(LC_CTYPE, NULL));
	_tsetlocale(LC_CTYPE, _T("chs"));

	CStdioFile fp;
	fp.Open(cstrMusicList+L".txt", CFile::modeRead);
	CString szLine = TEXT( "");
	while (fp.ReadString(szLine))
	{
		cstrFileName = szLine;
		addFileToPlayList();
	}
	fp.Close();

	_tsetlocale(LC_CTYPE, old_locale);
	free(old_locale);

	CString str;
	int counter;

	counter = myPlayList.GetItemCount();
	str.Format(TEXT("播放列表(共: %d 首)"), counter);
	GetDlgItem(IDC_GROUPLIST)->SetWindowText(str);
	*pResult = 0;
}
