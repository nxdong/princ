// FileDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Princ.h"
#include "FileDlg.h"
#include "afxdialogex.h"


// FileDlg �Ի���

IMPLEMENT_DYNAMIC(FileDlg, CDialogEx)

FileDlg::FileDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(FileDlg::IDD, pParent)
{

}

FileDlg::~FileDlg()
{
}

void FileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(FileDlg, CDialogEx)
END_MESSAGE_MAP()


// FileDlg ��Ϣ�������


void FileDlg::OnReceiveComplete(void)
{
	AfxMessageBox(_T("File OnReceiveComplete"));
}
