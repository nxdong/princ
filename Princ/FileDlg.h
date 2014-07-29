#pragma once


// FileDlg 对话框

class FileDlg : public CDialogEx
{
	DECLARE_DYNAMIC(FileDlg)

public:
	FileDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~FileDlg();

// 对话框数据
	enum { IDD = IDD_FILEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
