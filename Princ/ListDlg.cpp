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

// 	LOGININFO log;
// 	memset(&log,0,sizeof(LOGININFO));
// 	log.bToken = 1;
// 	//memset(&log.IPAddress,0,sizeof(log.IPAddress));
// 	log.OsVerInfoEx.dwPlatformId = VER_PLATFORM_WIN32_NT;
// 	log.OsVerInfoEx.dwMajorVersion = 6;
// 	log.OsVerInfoEx.dwMinorVersion = 0;
// 	log.CPUClockMhz = 888;
// 	log.bIsWebCam = 1;
// 	log.dwSpeed = 1;
// 	char aa[50] = "test host name";
// 	//char * aa = "test host name";
// 	memcpy(&log.HostName,aa,sizeof(aa));
// 	//log.HostName = aa;
// 	m_cListCtrl.AddToList(log);

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
	LOGININFO*	LoginInfo;
	if (pContext == NULL)
		return -1;

	CString	strToolTipsText, strOS;
	try
	{
		int nCnt = m_cListCtrl.GetItemCount();
		// 不合法的数据包
		if (pContext->m_DeCompressionBuffer.GetBufferLen() != sizeof(LOGININFO))
			return -1;
		LoginInfo = (LOGININFO*)pContext->m_DeCompressionBuffer.GetBuffer();
		m_cListCtrl.AddToList(LoginInfo);
		
// 		
// 		// ID
// 		CString	str;
// 		str.Format(_T("%d"), m_ComputerCount++);	
// 		// IP地址
// 		int i = m_cListCtrl.InsertItem(nCnt, str);
// 		// 外网IP
// 		sockaddr_in  sockAddr;
// 		memset(&sockAddr, 0, sizeof(sockAddr));
// 		int nSockAddrLen = sizeof(sockAddr);
// 		BOOL bResult = getpeername(pContext->m_Socket,(SOCKADDR*)&sockAddr, &nSockAddrLen);
// 		
// 		CString IPAddress;
// 		if (INVALID_SOCKET != bResult)
// 			IPAddress = inet_ntoa(sockAddr.sin_addr); 
// 		else
// 			IPAddress = _T("");
// 		
// 		
// 		m_cListCtrl.SetItemText(i, 1, IPAddress);
// 
// 		// 内网IP
// 		m_cListCtrl.SetItemText(i, 2, inet_ntoa(LoginInfo->IPAddress));
// 
// 		// 主机名
// 		m_pListCtrl->SetItemText(i, 3, LoginInfo->HostName);
// 
// 		// 系统
// 
// 		////////////////////////////////////////////////////////////////////////////////////////
// 		// 显示输出信息
// 		char *pszOS = NULL;
// 		switch (LoginInfo->OsVerInfoEx.dwPlatformId)
// 		{
// 
// 		case VER_PLATFORM_WIN32_NT:
// 			if (LoginInfo->OsVerInfoEx.dwMajorVersion <= 4 )
// 				pszOS = "NT";
// 			if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 5 && LoginInfo->OsVerInfoEx.dwMinorVersion == 0 )
// 				pszOS = "2000";
// 			if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 5 && LoginInfo->OsVerInfoEx.dwMinorVersion == 1 )
// 				pszOS = "XP";
// 			if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 5 && LoginInfo->OsVerInfoEx.dwMinorVersion == 2 )
// 				pszOS = "2003";
// 			if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 6 && LoginInfo->OsVerInfoEx.dwMinorVersion == 0 )
// 				pszOS = "Vista";  // Just Joking
// 		}
// 		strOS.Format
// 			(
// 			"%s SP%d (Build %d)",
// 			//OsVerInfo.szCSDVersion,
// 			pszOS, 
// 			LoginInfo->OsVerInfoEx.wServicePackMajor, 
// 			LoginInfo->OsVerInfoEx.dwBuildNumber
// 			);
// 		m_pListCtrl->SetItemText(i, 4, strOS);
// 
// 		// CPU
// 		str.Format("%dMHz", LoginInfo->CPUClockMhz);
// 		m_pListCtrl->SetItemText(i, 5, str);
// 
// 		// Speed
// 		str.Format("%d", LoginInfo->dwSpeed);
// 		m_pListCtrl->SetItemText(i, 6, str);
// 
// 
// 		str = LoginInfo->bIsWebCam ? "有" : "--";
// 		m_pListCtrl->SetItemText(i, 7, str);
// 
// 		strToolTipsText.Format("New Connection Information:\nHost: %s\nIP  : %s\nOS  : Windows %s", LoginInfo->HostName, IPAddress, strOS);
// 
// 		if (((CGh0stApp *)AfxGetApp())->m_bIsQQwryExist)
// 		{
// 
// 			str = m_QQwry->IPtoAdd(IPAddress);
// 			m_pListCtrl->SetItemText(i, 8, str);
// 
// 			strToolTipsText += "\nArea: ";
// 			strToolTipsText += str;
// 		}
// 		// 指定唯一标识
// 		m_pListCtrl->SetItemData(i, (DWORD) pContext);
// 
// 		g_pFrame->ShowConnectionsNumber();
// 
// 		if (!((CGh0stApp *)AfxGetApp())->m_bIsDisablePopTips)
// 			g_pFrame->ShowToolTips(strToolTipsText);
	}catch(...){}

	return 0;
}