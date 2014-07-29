#pragma once


// ShellDlg 对话框

class ShellDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ShellDlg)

public:
	ShellDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ShellDlg();

// 对话框数据
	enum { IDD = IDD_SHELLDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
