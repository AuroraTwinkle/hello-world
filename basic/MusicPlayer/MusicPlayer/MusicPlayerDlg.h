
// MusicPlayerDlg.h: 头文件
//



typedef enum columnWidth//列表中每列宽度
{
	TURNWIDTH = 60,//序号
	FILENAMEWIDTH = 150,//文件名
	FILETIMEWIDTH = 100,//文件时长
	MUSICLISTNAME=130 //歌单名
}COLUMNWIDTH;

typedef enum _tagColumnIndex//列表控件中各列索引值
{
	ID_TURN = 0,//序号
	ID_FILENAME = 1,//文件名
	ID_FILETIME = 2,	//文件时长
	ID_MUSICLISTNAME=1//歌单名
}COLUMNINDEX;

typedef enum _tagPlayMode//播放模式索引
{
	SINGLE_MODE = 0,//单曲循环
	ORDER_MODE = 1,//顺序播放
	RAND_MODE = 2,//随机播放

}PLAYMODE;

const int ID_PLAYERTIMER = 1;

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "NiceSlider.h"
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include <Digitalv.h>
#include <map>
using namespace std;
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
	bool BEOPENPLAYERFIRST;//用来标记是否是第一次打开软件
	bool beLoadAndPlay;
	CMenu * pMainMenu;
	CMenu * playMenu;//更新菜单项
	CNiceSliderCtrl playProgressBar;//播放进度条
	CNiceSliderCtrl volBar;//音量进度条
	CComboBox myPlayMode;//播放模式组合框
	CString cstrFilePath;//文件路径
	CString cstrFileName;//文件名
	CString cstrMusicList;//歌单名
	CListCtrl myPlayList;//播放列表
	bool bePlay;//播放标记
	TCHAR	strMciError[300];//用于存放MCI错误信息
	WORD m_wDeviceID;//MCI设备ID
	DWORD	m_Length;//音频文件长度（毫秒）
	DWORD	currentPos;//当前播放位置
	CString m_strTotalLength;//文件总时长
	CString m_strCurrentLength;//当前播放时间
	int m_PlayMode;//播放模式索引
	int m_CurrentSelect;//播放列表控件当前索引
	int m_CurrentSelect1;//歌单列表控件当前索引
	int m_CurrentPlayIndex;//当前播放索引
	map <CString,CString> filePathMap;//存放文件路径
public:
	static CListCtrl myMusicList;//歌单列表

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
	void updateCurrentPosText();//更新当前播放时间
	void addFileToPlayList();//添加歌曲到列表
	void deleteMusic();//删除列表中的歌曲
	void goPrevious();//上一曲
	void goNext();//下一曲
	void goAhead();//快进
	void goBack();//快退
	void getCurrentSelect();//当前播放列表控件选中位置的索引
	void getCurrentSelect1(); //当前歌单列表控件选中位置的索引
	void setPlayMode();//设置播放模式
		
//按钮映射函数
public:
	afx_msg void OnNMCustomdrawPlayprogress(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawVolBar(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnAhead();
	afx_msg void OnBnClickedBtnDelete();
	afx_msg void OnBnClickedBtnLoadfile();
	afx_msg void OnBnClickedBtnPause();

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedBtnPreviousOne();
	afx_msg void OnBnClickedBtnNextOne();
	afx_msg void OnBnClickedBtnBack();
	afx_msg void OnLvnItemchangedPlayList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangePlayMode();
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedAddMusicList();
	afx_msg void OnDblclkPlayList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRclickPlayList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMenuOpen();
	afx_msg void OnExit();
	afx_msg void OnMenuPlay1();
	afx_msg void OnMenuPause1();
	afx_msg void OnMenuPrevious();
	afx_msg void OnMenuAhead();
	afx_msg void OnMenuBack();
	afx_msg void OnMenuNext();
	afx_msg void OnMenuRand();
	afx_msg void OnMenuSingle();
	afx_msg void OnMenuTurn();
	afx_msg void OnMenuPlay();
	afx_msg void OnMenuPause();
	afx_msg void OnMenuNextoe();
	afx_msg void OnMenuLast();
	afx_msg void OnMenuDelete();
	afx_msg void OnDblclkListMusiclist(NMHDR *pNMHDR, LRESULT *pResult);
};
