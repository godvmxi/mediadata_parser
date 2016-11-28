/* 
 * AAC������
 * AAC Analysis
 *
 * ������ Lei Xiaohua
 * leixiaohua1020@126.com
 * �й���ý��ѧ/���ֵ��Ӽ���
 * Communication University of China / Digital TV Technology
 * http://blog.csdn.net/leixiaohua1020
 *
 */
#include "stdafx.h"
#include "SpecialAAAC.h"
#include "SpecialAAACDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CSpecialAAACDlg �Ի���




CSpecialAAACDlg::CSpecialAAACDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSpecialAAACDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSpecialAAACDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_A_AAC_BASICINFO, m_aaacbasicinfo);
	DDX_Control(pDX, IDC_A_AAC_INPUTURL, m_aaacinputurl);
	DDX_Control(pDX, IDC_A_AAC_CONSOLE, m_aaacconsole);
	DDX_Control(pDX, IDC_A_AAC_OUTPUT_FMT, m_aaacoutputfmt);
	DDX_Control(pDX, IDC_A_AAC_OUTPUT_SR, m_aaacoutputsr);
	DDX_Control(pDX, IDC_A_AAC_LANG, m_aaaclang);
	DDX_Control(pDX, IDC_A_AAC_PROGRESS, m_aaacprogress);
	DDX_Control(pDX, IDC_A_AAC_PROGRESS_TEXT, m_aaacprogresstext);
}

BEGIN_MESSAGE_MAP(CSpecialAAACDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_A_AAC_INPUTURL_OPEN, &CSpecialAAACDlg::OnBnClickedAAacInputurlOpen)
	ON_BN_CLICKED(IDC_A_AAC_ABOUT, &CSpecialAAACDlg::OnBnClickedAAacAbout)
	ON_WM_DROPFILES()
	ON_CBN_SELCHANGE(IDC_A_AAC_LANG, &CSpecialAAACDlg::OnSelchangeAAacLang)
END_MESSAGE_MAP()

//�����߳�
UINT Thread_Process(LPVOID lpParam){
	
	CSpecialAAACDlg *dlg=(CSpecialAAACDlg *)lpParam;

	int argc=6;
	char **argv=(char **)malloc(MAX_URL_LENGTH);
	argv[0]=(char *)malloc(MAX_URL_LENGTH);
	argv[1]=(char *)malloc(MAX_URL_LENGTH);
	argv[2]=(char *)malloc(MAX_URL_LENGTH);
	argv[3]=(char *)malloc(MAX_URL_LENGTH);
	argv[4]=(char *)malloc(MAX_URL_LENGTH);
	argv[5]=(char *)malloc(MAX_URL_LENGTH);

	strcpy(argv[0],"dummy");

	strcpy(argv[1],"-f");
	
	switch(dlg->m_aaacoutputfmt.GetCurSel()){
	case 0:strcpy(argv[2],"1");break;
	case 1:strcpy(argv[2],"2");break;
	default:strcpy(argv[2],"1");break;
	}
	strcpy(argv[3],"-b");
	switch(dlg->m_aaacoutputsr.GetCurSel()){
	case 0:strcpy(argv[4],"1");break;
	case 1:strcpy(argv[4],"2");break;
	case 2:strcpy(argv[4],"3");break;
	case 3:strcpy(argv[4],"4");break;
	case 4:strcpy(argv[4],"5");break;
	default:strcpy(argv[4],"1");break;
	}
	strcpy(argv[5],dlg->fileurl);
	aac_decode(dlg,argc,argv);
	free(argv[0]);
	free(argv[1]);
	free(argv[2]);
	free(argv[3]);
	free(argv[4]);
	free(argv[5]);
	free(argv);
	dlg->ShowBInfo();
	//FIX:100%
	dlg->m_aaacprogress.SetPos(100);
	CString progresstext(_T("100%"));
	dlg->m_aaacprogresstext.SetWindowText(progresstext);


	return 0;
}


// CSpecialAAACDlg ��Ϣ�������

BOOL CSpecialAAACDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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
	//----------
	m_aaacbasicinfo.EnableHeaderCtrl(FALSE);
	m_aaacbasicinfo.SetVSDotNetLook();
	//�ѵ�һ�е�����һЩ-----------------------
	HDITEM item; 
	item.cxy=120; 
	item.mask=HDI_WIDTH; 
	m_aaacbasicinfo.GetHeaderCtrl().SetItem(0, new HDITEM(item)); 
	text.LoadString(IDS_INFO_FRAMEINFO);
	FrameInfogroup=new CMFCPropertyGridProperty(text);
	text.LoadString(IDS_INFO_CONTAINERINFO);
	Containergroup=new CMFCPropertyGridProperty(text);
	text.LoadString(IDS_INFO_METAINFO);
	MetaDatagroup=new CMFCPropertyGridProperty(text);
	cinfo.Format(_T(""));
	UpdateData(FALSE);
	//------------
	m_aaacoutputfmt.InsertString(0,_T("Microsoft WAV format"));
	m_aaacoutputfmt.InsertString(1,_T("RAW PCM data"));

	m_aaacoutputsr.InsertString(0,_T("16 bit PCM data"));
	m_aaacoutputsr.InsertString(1,_T("24 bit PCM data"));
	m_aaacoutputsr.InsertString(2,_T("32 bit PCM data"));
	m_aaacoutputsr.InsertString(3,_T("32 bit floating point data"));
	m_aaacoutputsr.InsertString(4,_T("64 bit floating point data"));

	m_aaacoutputfmt.SetCurSel(0);
	m_aaacoutputsr.SetCurSel(0);
	//--------------------
	m_aaacinputurl.EnableFileBrowseButton(
		NULL,
		_T("AAC Raw Files (*.aac)|*.aac|M4A Files (*.m4a)|*.m4a|All Files (*.*)|*.*||")
		);
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_aaaclang.InsertString(0,_T("Chinese"));
	m_aaaclang.InsertString(1,_T("English"));
	//---------
	m_aaacprogress.SetRange(0,100);
	m_aaacprogress.SetPos(0);
	m_aaacprogresstext.SetWindowText(_T("0%"));

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSpecialAAACDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSpecialAAACDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
	//���Ի���Ӧ����ӵ�OnInitDialog�У�����û��Ч��
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSpecialAAACDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// SpecialAAAC ��Ϣ�������


void CSpecialAAACDlg::OnBnClickedAAacInputurlOpen()
{

	//---------
	SystemClear();
	CString strFilePath;
	//m_aaacinputurl.GetWindowText(fileurl,MAX_URL_LENGTH);
	m_aaacinputurl.GetWindowText(strFilePath);

	if(strFilePath.IsEmpty()==TRUE){
		text.LoadString(IDS_INPUTURL_ERROR);
		AfxMessageBox(text);
		return ;
	}

#ifdef _UNICODE
	USES_CONVERSION;
	strcpy(fileurl,W2A(strFilePath));
#else
	strcpy(fileurl,strFilePath);
#endif
	UpdateData(TRUE);

	m_aaacprogress.SetPos(0);

	pThreadProcess=AfxBeginThread(Thread_Process,this);//�����߳�
	
}

int CSpecialAAACDlg::AppendBInfo(CString dst_group,CString property_name,CString value,CString remark){
	if(dst_group.Compare(_T("FrameInfo"))==0){
		FrameInfogroup->AddSubItem(new CMFCPropertyGridProperty(property_name,(variant_t)value, remark));
	}else if(dst_group.Compare(_T("Container"))==0){
		Containergroup->AddSubItem(new CMFCPropertyGridProperty(property_name, (variant_t)value, remark));
	}else if(dst_group.Compare(_T("MetaData"))==0){
		MetaDatagroup->AddSubItem(new CMFCPropertyGridProperty(property_name, (variant_t)value, remark));
	}
	return 0;
}

int CSpecialAAACDlg::ShowBInfo(){
	m_aaacbasicinfo.AddProperty(FrameInfogroup);
	m_aaacbasicinfo.AddProperty(Containergroup);
	m_aaacbasicinfo.AddProperty(MetaDatagroup);
	return TRUE;
}

//����CInfo
int CSpecialAAACDlg::AppendCInfo(CString str){
	
	m_aaacconsole.AddString(str);
	m_aaacconsole.Invalidate();
	return 0;
}

void CSpecialAAACDlg::SystemClear(){
	cinfo.Format(_T(""));
	m_aaacbasicinfo.RemoveAll();
	m_aaacconsole.ResetContent();

	text.LoadString(IDS_INFO_FRAMEINFO);
	FrameInfogroup=new CMFCPropertyGridProperty(text);
	text.LoadString(IDS_INFO_CONTAINERINFO);
	Containergroup=new CMFCPropertyGridProperty(text);
	text.LoadString(IDS_INFO_METAINFO);
	MetaDatagroup=new CMFCPropertyGridProperty(text);

}

void CSpecialAAACDlg::OnBnClickedAAacAbout()
{
	CAboutDlg dlg;
	dlg.DoModal();
}


void CSpecialAAACDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnDropFiles(hDropInfo);
	LPTSTR pFilePathName =(LPTSTR)malloc(MAX_URL_LENGTH);
	::DragQueryFile(hDropInfo, 0, pFilePathName,MAX_URL_LENGTH);  // ��ȡ�Ϸ��ļ��������ļ�������ؼ���
	m_aaacinputurl.SetWindowText(pFilePathName);
	::DragFinish(hDropInfo);   // ע����������٣��������ͷ�Windows Ϊ�����ļ��ϷŶ�������ڴ�
	free(pFilePathName);
}


void CSpecialAAACDlg::OnSelchangeAAacLang()
{
	//�����ļ�·��
	char conf_path[300]={0};
	//���exe����·��
	GetModuleFileNameA(NULL,(LPSTR)conf_path,300);//
	//���exe�ļҼ�·��
	strrchr( conf_path, '\\')[0]= '\0';//
	//_getcwd(realpath,MYSQL_S_LENGTH);
	printf("%s",conf_path);
	strcat(conf_path,"\\configure.ini");
	//д�������ļ�
	switch(m_aaaclang.GetCurSel()){
	case 0:WritePrivateProfileStringA("Settings","language","Chinese",conf_path);break;
	case 1:WritePrivateProfileStringA("Settings","language","English",conf_path);break;
	default:break;
	}
	//�������
	char exe_path[300]={0};
	//���exe����·��
	GetModuleFileNameA(NULL,(LPSTR)exe_path,300);
	ShellExecuteA( NULL,"open",exe_path,NULL,NULL,SW_SHOWNORMAL);
	exit(0);
}
