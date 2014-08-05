// ListDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Princ.h"
#include "ListDlg.h"
#include "afxdialogex.h"

// ListDlg �Ի���

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
END_MESSAGE_MAP()


// ListDlg ��Ϣ�������


BOOL ListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rect;
	m_cListCtrl.GetClientRect(&rect);
	m_cListCtrl.MoveWindow(&rect);
	m_cListCtrl.init();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
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
BOOL ListDlg::AddToList(ClientContext *pContext)
{
	//ClientContext	*pContext = (ClientContext *)lParam;
	m_cListCtrl.AddToList(pContext);
	m_ComputerCount++;
	return TRUE;
}
BOOL ListDlg::RemoveFromList(ClientContext *pContext)
{
	if (pContext == NULL)
		return -1;
	// ɾ����������п��ܻ�ɾ��Context
	try
	{
		int nCnt = m_cListCtrl.GetItemCount();
		for (int i=0; i < nCnt; i++)
		{
			if (pContext == (ClientContext *)m_cListCtrl.GetItemData(i))
			{
				m_cListCtrl.DeleteItem(i);
				break;
			}		
		}

		// �ر���ش���

		switch (pContext->m_Dialog[0])
		{
		case FILEMANAGER_DLG:
		case SHELL_DLG:
			((CDialog*)pContext->m_Dialog[1])->SendMessage(WM_CLOSE);
			/*((CDialog*)pContext->m_Dialog[1])->DestroyWindow();*/
			break;
		default:
			break;
		}
	}catch(...){}

	return 0;
}