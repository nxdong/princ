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
	{_T("Wan/Lan"),				0.2	},
	{_T("Hostname"),			0.2	},
	{_T("Version"),				0.2	},
	{_T("Relay"),				0.1	},
	{_T("Comment"),				0.3	},
};
// MyListCtrl

IMPLEMENT_DYNAMIC(MyListCtrl, CListCtrl)

MyListCtrl::MyListCtrl()
{
	
	m_Column_Count = 5;
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
BOOL MyListCtrl::AddToList(LOGININFO* loginfo)
{
	m_nItemCount++;
	return TRUE;
}