#pragma once


// ShellDlg �Ի���

class ShellDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ShellDlg)

public:
	ShellDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ShellDlg();

// �Ի�������
	enum { IDD = IDD_SHELLDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
