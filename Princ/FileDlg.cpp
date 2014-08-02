// FileDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Princ.h"
#include "FileDlg.h"
#include "afxdialogex.h"


// FileDlg 对话框

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


// FileDlg 消息处理程序


void FileDlg::OnReceiveComplete(void)
{
	AfxMessageBox(_T("File OnReceiveComplete"));
}
