
// PrincDlg.h : 头文件
//

#pragma once
#include "stdafx.h"
#include "resource.h"
#include "mytabctrl.h"
#include "ListDlg.h"
#include "ShellDlg.h"
#include "FileDlg.h"
#include "IOCPServer.h"
// CPrincDlg 对话框
class CIOCPServer;
struct ClientContext;
class CPrincDlg : public CDialogEx
{
// 构造
public:
	CPrincDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PRINC_DIALOG };

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
public:
	MyTabCtrl	 m_cTabCtrl;
	ListDlg		 m_ListDlg;
	ShellDlg	 m_ShellDlg;
	FileDlg		 m_FileDlg;	
	CIOCPServer* m_ServerPrincDlg;
	CPrincDlg*   m_pPrincDlg;
	//CIOCPServer  m_Server;
	void Activate(UINT nPort, UINT nMaxConnections);
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	static void CALLBACK NotifyProc(LPVOID lpParam, ClientContext* pContext, UINT nCode);
	static void ProcessReceiveComplete(ClientContext *pContext);
	static void ProcessReceive(ClientContext *pContext);
	afx_msg LRESULT OnAddToList(WPARAM, LPARAM);
	afx_msg LRESULT OnRemoveFromList(WPARAM, LPARAM);



};
