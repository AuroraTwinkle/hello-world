#pragma once


// InputBoxDlg 对话框

class InputBoxDlg : public CDialogEx
{
	DECLARE_DYNAMIC(InputBoxDlg)

public:
	InputBoxDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~InputBoxDlg();


//成员变量
public:
	static CString musicList;//歌单名
	CEdit inputBox;//歌单名编辑框变量
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
