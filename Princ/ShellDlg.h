#pragma once
#include "afxwin.h"
#include "stdafx.h"

// ShellDlg �Ի���

class ShellDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ShellDlg)

public:
	ShellDlg(CWnd* pParent = NULL,CIOCPServer* pIOCPServer = NULL, ClientContext *pContext = NULL);   // ��׼���캯��
	virtual ~ShellDlg();

// �Ի�������
	enum { IDD = IDD_SHELLDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
