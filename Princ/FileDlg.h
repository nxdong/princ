#pragma once


// FileDlg �Ի���

class FileDlg : public CDialogEx
{
	DECLARE_DYNAMIC(FileDlg)

public:
	FileDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~FileDlg();

// �Ի�������
	enum { IDD = IDD_FILEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
