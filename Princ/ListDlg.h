#pragma once

#include "MyListCtrl.h"

// ListDlg 对话框

class ListDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ListDlg)

public:
	ListDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ListDlg();
	MyListCtrl m_cListCtrl;
// 对话框数据
	enum { IDD = IDD_LISTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
