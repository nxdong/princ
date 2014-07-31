#pragma once
#include "IOCPServer.h"
#include "stdafx.h"
#include "macros.h"
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
	BOOL AddToList(LOGININFO* loginfo);	// add promote computer info to list
};


