
// PrincDlg.h : ͷ�ļ�
//

#pragma once
#include "stdafx.h"
#include "resource.h"
#include "mytabctrl.h"
#include "ListDlg.h"
#include "ShellDlg.h"
#include "FileDlg.h"

// CPrincDlg �Ի���
class CPrincDlg : public CDialogEx
{
// ����
public:
	CPrincDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PRINC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	MyTabCtrl	 m_cTabCtrl;
	ListDlg		 m_ListDlg;
	ShellDlg	 m_ShellDlg;
	FileDlg		 m_FileDlg;		
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
