// ShellDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Princ.h"
#include "ShellDlg.h"
#include "afxdialogex.h"


// ShellDlg 对话框

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


// ShellDlg 消息处理程序


void ShellDlg::OnReceiveComplete(void)
{
	AfxMessageBox(_T("shell dlg OnReceiveComplete"));
}
