// ShellDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Princ.h"
#include "ShellDlg.h"
#include "afxdialogex.h"


// ShellDlg �Ի���

IMPLEMENT_DYNAMIC(ShellDlg, CDialogEx)

ShellDlg::ShellDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ShellDlg::IDD, pParent)
{

}

ShellDlg::~ShellDlg()
{
}

void ShellDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ShellDlg, CDialogEx)
END_MESSAGE_MAP()


// ShellDlg ��Ϣ�������


void ShellDlg::OnReceiveComplete(void)
{
	AfxMessageBox(_T("shell dlg OnReceiveComplete"));
}
