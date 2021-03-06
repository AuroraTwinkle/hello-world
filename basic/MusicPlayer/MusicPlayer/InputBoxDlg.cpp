// InputBoxDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MusicPlayer.h"
#include "InputBoxDlg.h"
#include "afxdialogex.h"
#include "MusicPlayerDlg.h"
CString InputBoxDlg::musicList;
// InputBoxDlg 对话框

IMPLEMENT_DYNAMIC(InputBoxDlg, CDialogEx)

InputBoxDlg::InputBoxDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

InputBoxDlg::~InputBoxDlg()
{
}

void InputBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_INPUT, inputBox);
}


BEGIN_MESSAGE_MAP(InputBoxDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &InputBoxDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// InputBoxDlg 消息处理程序
BOOL InputBoxDlg::OnInitDialog()
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
	this->SetWindowText(TEXT("新建歌单"));
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void InputBoxDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	
	//UpdateData(true);
	CDialogEx::OnOK();
	inputBox.GetWindowText(musicList);
	CFile fp;
	fp.Open(musicList + L".txt", CFile::modeCreate, NULL);
	fp.Close();
	LVITEM item;
	int index;
	CString strTmp;

	item.mask = LVIF_TEXT;
	item.iSubItem = 0;

	item.iItem = (CMusicPlayerDlg::myMusicList.GetItemCount() <= 0) ? 0 : CMusicPlayerDlg::myMusicList.GetItemCount();
	strTmp.Format(TEXT("%d"), ++item.iItem);
	item.pszText = strTmp.GetBuffer(strTmp.GetLength());
	index = CMusicPlayerDlg::myMusicList.InsertItem(&item);


	CMusicPlayerDlg::myMusicList.SetItemText(index, ID_MUSICLISTNAME, InputBoxDlg::musicList);
	CMusicPlayerDlg::myMusicList.SetItemState(index, LVIS_SELECTED, LVIS_SELECTED);
}
