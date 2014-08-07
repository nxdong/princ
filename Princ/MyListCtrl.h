#pragma once
#include "macros.h"
#include "IOCPServer.h"
#include "UnicodeChange.h"
struct ClientContext;
class MyListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(MyListCtrl)
public:
	//  Column count , changed by hand.
	int	m_Column_Count;
public:
	MyListCtrl();
	virtual ~MyListCtrl();
	
protected:
	DECLARE_MESSAGE_MAP()
public:
	
	int  m_nItemCount;					// the count of items
	BOOL init();					    // initialize the list . column set
	BOOL changeWidth(void);				// called when need redraw 
	BOOL AddToList(ClientContext* pContext);	// add promote computer info to list
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnListmenuTest();
};


