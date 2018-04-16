
// MusicPlayerDlg.h: 头文件
//



typedef enum columnWidth//列表中每列宽度
{
	TURNWIDTH = 60,//序号
	FILENAMEWIDTH = 150,//文件名
	FILETIMEWIDTH = 100//文件时长

}COLUMNWIDTH;

typedef enum _tagColumnIndex//列表控件中各列索引值
{
	ID_TURN = 0,//序号
	ID_FILENAME = 1,//文件名
	ID_FILETIME = 2	//文件时长
}COLUMNINDEX;

const int ID_PLAYERTIMER = 1;

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "NiceSlider.h"
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include <Digitalv.h>

// CMusicPlayerDlg 对话框
class CMusicPlayerDlg : public CDialogEx
{
// 构造
public:
	CMusicPlayerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MUSICPLAYER_DIALOG };
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
	DECLARE_MESSAGE_MAP()

//成员变量
protected:
	CMenu * pMainMenu;
	CNiceSliderCtrl playProgressBar;//播放进度条
	CNiceSliderCtrl volBar;//音量进度条
	CComboBox myPlayMode;//播放模式组合框
	CString cstrFilePath;//文件路径
	CString cstrFileName;//文件名
	CListCtrl myPlayList;//播放列表
	bool bePlay;//播放标记
	TCHAR	strMciError[300];//用于存放MCI错误信息
	WORD m_wDeviceID;//MCI设备ID
	DWORD	m_Length;//音频文件长度（毫秒）
	CString m_strTotalLength;//文件总时长
	int m_PlayMode;//播放模式索引
public:


//功能函数
public:
	bool InitMenu(void);//初始化菜单栏
	bool InitControls(void);//初始化控件
	bool InitComboxBoxPlayMode(void);//初始化播放模式组合框
	bool loadFile();//加载文件
	bool InitPlayList(void);//初始化播放列表
	bool PlayFile(CString filePath);//播放文件
	void SetVolume(int Vol);//设置音量
	CString ConvertTimeToString(int);//将文件毫秒数转换为分钟和秒
	void setWindowTitle(CString fileName, bool playFlag);//设置窗口标题
	void musicPause();//暂停播放

//按钮映射函数
public:
	afx_msg void OnNMCustomdrawPlayprogress(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawVolBar(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnAhead();
	afx_msg void OnBnClickedBtnDelete();
	afx_msg void OnBnClickedBtnLoadfile();
	afx_msg void OnBnClickedBtnPause();
};
