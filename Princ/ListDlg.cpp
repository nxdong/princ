// ListDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Princ.h"
#include "ListDlg.h"
#include "afxdialogex.h"

// ListDlg 对话框

IMPLEMENT_DYNAMIC(ListDlg, CDialogEx)

ListDlg::ListDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ListDlg::IDD, pParent)
{
	m_ComputerCount = 0;
}

ListDlg::~ListDlg()
{
}

void ListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTCTRL, m_cListCtrl);
}


BEGIN_MESSAGE_MAP(ListDlg, CDialogEx)
	ON_WM_SIZE()
	ON_MESSAGE(WM_ADDTOLIST, OnAddToList)
END_MESSAGE_MAP()


// ListDlg 消息处理程序


BOOL ListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rect;
	m_cListCtrl.GetClientRect(&rect);
	m_cListCtrl.MoveWindow(&rect);
	m_cListCtrl.init();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void ListDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if(m_cListCtrl.m_hWnd == NULL)
		return;      // Return if window is not created yet.
	CRect rect;
	this->GetWindowRect(&rect);
	ScreenToClient(&rect);  
	m_cListCtrl.MoveWindow(&rect);
	m_cListCtrl.changeWidth();
}
LRESULT ListDlg::OnAddToList(WPARAM wParam, LPARAM lParam)
{
	ClientContext	*pContext = (ClientContext *)lParam;
	
	m_cListCtrl.AddToList(pContext);
	m_ComputerCount++;
	return 0;
}