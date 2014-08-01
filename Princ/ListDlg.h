#pragma once
#include "stdafx.h"
#include "MyListCtrl.h"

// ListDlg �Ի���
class CIOCPServer;
struct ClientContext;
class ListDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ListDlg)

public:
	ListDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ListDlg();
	MyListCtrl m_cListCtrl;
	ClientContext* m_serverListDlg;
	int m_ComputerCount;
// �Ի�������
	enum { IDD = IDD_LISTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnAddToList(WPARAM, LPARAM);
};
