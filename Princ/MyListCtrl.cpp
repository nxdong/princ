// MyListCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyListCtrl.h"
#include "IOCPServer.h"
typedef struct
{
	CString	title;
	double		nWidth;
}COLUMNSTRUCT;
COLUMNSTRUCT m_Column_Data[] = 
{
	{_T("ID")	 ,				0.05	},
	{_T("Wan/Lan"),				0.15	},
	{_T("Hostname"),			0.15	},
	{_T("Version"),				0.35	},
	{_T("Relay"),				0.1		},
	{_T("Comment"),				0.2		},
};
// MyListCtrl

IMPLEMENT_DYNAMIC(MyListCtrl, CListCtrl)

MyListCtrl::MyListCtrl()
{
	
	m_Column_Count = 6;
	m_nItemCount = 0;

}

MyListCtrl::~MyListCtrl()
{
}


BEGIN_MESSAGE_MAP(MyListCtrl, CListCtrl)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_LISTMENU_TEST, &MyListCtrl::OnListmenuTest)
END_MESSAGE_MAP()



// MyListCtrl ��Ϣ�������


BOOL MyListCtrl::init()
{
	DWORD dwStyle = GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	SetExtendedStyle(dwStyle); //������չ���
	
	CRect rect;
	this->GetClientRect(&rect);
	int width = rect.Width();
	for (int i=0;i<m_Column_Count;i++)
	{
		InsertColumn(i,m_Column_Data[i].title,LVCFMT_LEFT,(int)width*m_Column_Data[i].nWidth);
	}
	return TRUE;
}


BOOL MyListCtrl::changeWidth(void)
{
	CRect rect;
	this->GetClientRect(&rect);
	int width = rect.Width();
	for (int i=0;i<m_Column_Count;i++)
	{
		SetColumnWidth(i,(int)width*m_Column_Data[i].nWidth);
	}
	return TRUE;
}
BOOL MyListCtrl::AddToList(ClientContext * pContext)
{
	LOGININFO*	LoginInfo;
	if (pContext == NULL)
		return FALSE;
 	CString	strToolTipsText, strOS;
	try
	{
		int nCnt = GetItemCount();
		// ���Ϸ������ݰ�
		if (pContext->m_DeCompressionBuffer.GetBufferLen() != sizeof(LOGININFO))
			return -1;
		LoginInfo = (LOGININFO*)pContext->m_DeCompressionBuffer.GetBuffer();
		// ID
		CString	str;
		str.Format(_T("%d"),m_nItemCount++);	
		int i = InsertItem(nCnt, str);

		//  Ip  wan/lan ��ʾ
		// ����IP
		sockaddr_in  sockAddr;
		memset(&sockAddr, 0, sizeof(sockAddr));
		int nSockAddrLen = sizeof(sockAddr);
		BOOL bResult = getpeername(pContext->m_Socket,(SOCKADDR*)&sockAddr, &nSockAddrLen);

		CString IPAddress;
		if (INVALID_SOCKET != bResult)
			IPAddress = inet_ntoa(sockAddr.sin_addr); 
		else
			IPAddress = _T("");
		// ����IP
		CString LanIPstr;
		LanIPstr = ANSIToUnicode(inet_ntoa((LoginInfo->IPAddress)));
		IPAddress += _T("'\'") + LanIPstr ;
		SetItemText(i, 1, IPAddress);

		// ������
		CString HostNameStr;
		HostNameStr = ANSIToUnicode(LoginInfo->HostName);
		SetItemText(i, 2, HostNameStr);
		// ϵͳ
		// ��ʾ�����Ϣ
		CString pszOS;

		if (LoginInfo->OsVerInfoEx.dwMajorVersion <= 4 )
			pszOS = "NT";
		else if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 5 && LoginInfo->OsVerInfoEx.dwMinorVersion == 0 )
			pszOS = "Windows 2000";
		else if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 5 && LoginInfo->OsVerInfoEx.dwMinorVersion == 1 )
			pszOS = "Windows XP";
		else if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 5 && LoginInfo->OsVerInfoEx.dwMinorVersion == 2 && (LoginInfo->OsVerInfoEx.wSuiteMask & VER_SUITE_WH_SERVER))
			pszOS = "Windows Home Server ";
		else if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 6 && LoginInfo->OsVerInfoEx.dwMinorVersion == 0 && (LoginInfo->OsVerInfoEx.wProductType == VER_NT_WORKSTATION))
			pszOS = "Windows Vista";  
		else if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 6 && LoginInfo->OsVerInfoEx.dwMinorVersion == 0 && (LoginInfo->OsVerInfoEx.wProductType != VER_NT_WORKSTATION))
			pszOS = "Windows Server 2008";  
		else if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 6 && LoginInfo->OsVerInfoEx.dwMinorVersion == 1 && (LoginInfo->OsVerInfoEx.wProductType == VER_NT_WORKSTATION))
			pszOS = "Windows 7";  
		else if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 6 && LoginInfo->OsVerInfoEx.dwMinorVersion == 1 && (LoginInfo->OsVerInfoEx.wProductType != VER_NT_WORKSTATION))
			pszOS = "Windows Server 2008 R2";  
		else if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 6 && LoginInfo->OsVerInfoEx.dwMinorVersion == 2 && (LoginInfo->OsVerInfoEx.wProductType == VER_NT_WORKSTATION))
			pszOS = "Windows 8";  
		else if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 6 && LoginInfo->OsVerInfoEx.dwMinorVersion == 2 && (LoginInfo->OsVerInfoEx.wProductType != VER_NT_WORKSTATION))
			pszOS = "Windows Server 2012";  
		else if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 6 && LoginInfo->OsVerInfoEx.dwMinorVersion == 3 && (LoginInfo->OsVerInfoEx.wProductType == VER_NT_WORKSTATION))
			pszOS = "Windows 8.1";  
		else if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 6 && LoginInfo->OsVerInfoEx.dwMinorVersion == 3 && (LoginInfo->OsVerInfoEx.wProductType != VER_NT_WORKSTATION))
			pszOS = "Windows Server 2012 R2";
		else
		{pszOS = "unknown";}

		strOS.Format
			(
			_T("%s SP%d (Build %d)'/' %dMHz"),
			//OsVerInfo.szCSDVersion,
			pszOS, 
			LoginInfo->OsVerInfoEx.wServicePackMajor, 
			LoginInfo->OsVerInfoEx.dwBuildNumber,
			LoginInfo->CPUClockMhz
			);
		SetItemText(i, 3, strOS);
		// Speed
		str.Format(_T("%d"), LoginInfo->dwSpeed);
		SetItemText(i, 4, str);

		str = LoginInfo->bIsWebCam ? "camera" : "--";
		SetItemText(i, 5, str);
		// ָ��Ψһ��ʶ
		SetItemData(i, (DWORD) pContext);
	}catch(...){}

	return TRUE;
}

void MyListCtrl::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: �ڴ˴������Ϣ����������
	HWND hWnd = AfxGetMainWnd()->m_hWnd;
	CWnd* pCWnd = FromHandle(hWnd);
	if (GetSelectedCount() <= 0)
	{
		CMenu menu;
		CMenu* pPopup;
		menu.LoadMenu (IDR_LISTMENU);
		pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);	
		pPopup->EnableMenuItem(ID_LISTMENU_SHELL,MF_GRAYED);
		pPopup->EnableMenuItem(ID_LISTMENU_FILEMANAGER,MF_GRAYED);
		pPopup->EnableMenuItem(ID_LISTMENU_DISCONNECT,MF_GRAYED);

		pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON, 
			point.x, point.y, pCWnd);	
		return;
	}
	CMenu menu;
	CMenu* pPopup;
	menu.LoadMenu (IDR_LISTMENU);
	pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);	
	pPopup->EnableMenuItem(ID_LISTMENU_SHELL,MF_ENABLED);
	pPopup->EnableMenuItem(ID_LISTMENU_FILEMANAGER,MF_ENABLED);
	pPopup->EnableMenuItem(ID_LISTMENU_DISCONNECT,MF_ENABLED);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON, 
		point.x, point.y, pCWnd);	
}


void MyListCtrl::OnListmenuTest()
{
	AfxMessageBox(_T("Test"));
	// TODO: �ڴ���������������
}
