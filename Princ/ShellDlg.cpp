// ShellDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Princ.h"
#include "ShellDlg.h"
#include "afxdialogex.h"


// ShellDlg �Ի���

IMPLEMENT_DYNAMIC(ShellDlg, CDialogEx)

ShellDlg::ShellDlg(CWnd* pParent)
	: CDialogEx(ShellDlg::IDD, pParent)
{
	
}

ShellDlg::~ShellDlg()
{
}

void ShellDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT, m_edit);
}


BEGIN_MESSAGE_MAP(ShellDlg, CDialogEx)
	ON_WM_SIZE()
	ON_EN_CHANGE(IDC_EDIT, OnChangeEdit)
	ON_WM_CTLCOLOR()

END_MESSAGE_MAP()


// ShellDlg ��Ϣ�������


void ShellDlg::OnReceiveComplete(void)
{
	AddKeyBoardData();
	m_nReceiveLength = m_edit.GetWindowTextLength();
}


void ShellDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if (this->m_hWnd == NULL)
		return;
	RECT	rectClient;
	RECT	rectEdit;
	GetClientRect(&rectClient);
	rectEdit.left = 0;
	rectEdit.top = 0;
	rectEdit.right = rectClient.right;
	rectEdit.bottom = rectClient.bottom;
	if (m_edit.m_hWnd == NULL)
		return;
	m_edit.MoveWindow(&rectEdit);
}


BOOL ShellDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	

	m_edit.SetLimitText(MAXDWORD); // ������󳤶�

	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


HBRUSH ShellDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if ((pWnd->GetDlgCtrlID() == IDC_EDIT) && (nCtlColor == CTLCOLOR_EDIT))
	{
		COLORREF clr = RGB(255, 255, 255);
		pDC->SetTextColor(clr);   //���ð�ɫ���ı�
		clr = RGB(0,0,0);
		pDC->SetBkColor(clr);     //���ú�ɫ�ı���
		return CreateSolidBrush(clr);  //��ΪԼ�������ر���ɫ��Ӧ��ˢ�Ӿ��
	}
	else
	{
		return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


BOOL ShellDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN)
	{
		// ����VK_ESCAPE��VK_DELETE
		if (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_DELETE)
			return true;

		if (pMsg->wParam == VK_RETURN && pMsg->hwnd == m_edit.m_hWnd)
		{
			int	len = m_edit.GetWindowTextLength();
			CString str;
			m_edit.GetWindowText(str);
			str += "\r\n";
			m_iocpServer->Send(m_pContext, (LPBYTE)str.GetBuffer(0) + m_nCurSel, str.GetLength() - m_nCurSel);
			m_nCurSel = m_edit.GetWindowTextLength();
		}
		// ����VK_BACK
		if (pMsg->wParam == VK_BACK && pMsg->hwnd == m_edit.m_hWnd)
		{
			if (m_edit.GetWindowTextLength() <= m_nReceiveLength)
				return true;
		}
	}
	// Ctrlû����
	if (pMsg->message == WM_CHAR && GetKeyState(VK_CONTROL) >= 0)
	{
		int	len = m_edit.GetWindowTextLength();
		m_edit.SetSel(len, len);
		// �û�ɾ���˲������ݣ��ı�m_nCurSel
		if (len < m_nCurSel)
			m_nCurSel = len;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
void ShellDlg::AddKeyBoardData()
{
	// �������0
	m_pContext->m_DeCompressionBuffer.Write((LPBYTE)"", 1);
	CString strResult;
	strResult = m_pContext->m_DeCompressionBuffer.GetBuffer(0);
	

	strResult.Replace(_T("\n"), _T("\r\n"));
	int	len = m_edit.GetWindowTextLength();
	m_edit.SetSel(len, len);
	m_edit.ReplaceSel(strResult);
	m_nCurSel = m_edit.GetWindowTextLength();
}
void ShellDlg::OnChangeEdit() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	// �û�ɾ���˲������ݣ��ı�m_nCurSel
	int len = m_edit.GetWindowTextLength();
	if (len < m_nCurSel)
		m_nCurSel = len;
}

BOOL ShellDlg::SetClient(CIOCPServer* pIOCPServer , ClientContext *pContext )
{
	m_iocpServer	= pIOCPServer;
	m_pContext		= pContext;
	m_nCurSel = 0;

	m_nCurSel = m_edit.GetWindowTextLength();

	CString str;
	sockaddr_in  sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	int nSockAddrLen = sizeof(sockAddr);
	BOOL bResult = getpeername(m_pContext->m_Socket, (SOCKADDR*)&sockAddr, &nSockAddrLen);
	str.Format(_T("\\\\%s - Զ���ն�"), bResult != INVALID_SOCKET ? inet_ntoa(sockAddr.sin_addr) : "");
	SetWindowText(str);


	// ֪ͨԶ�̿��ƶ˶Ի����Ѿ���
	BYTE bToken = COMMAND_NEXT;
	m_iocpServer->Send(m_pContext, &bToken, sizeof(BYTE));
	return TRUE;
}