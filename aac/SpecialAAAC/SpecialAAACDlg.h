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
#pragma once
#include "resource.h"
#include "stdafx.h"
#include "aac_decode.h"

// CSpecialAAACDlg �Ի���
class CSpecialAAACDlg : public CDialogEx
{
// ����
public:
	CSpecialAAACDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SPECIAL_A_AAC };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	CMFCPropertyGridCtrl m_aaacbasicinfo;
	char fileurl[MAX_URL_LENGTH];
	afx_msg void OnBnClickedAAacInputurlOpen();
	CMFCEditBrowseCtrl m_aaacinputurl;
//	CEdit m_aaacconsole;
	int AppendBInfo(CString dst_group,CString property_name,CString value,CString remark);
	int ShowBInfo();
	CString cinfo;
	int AppendCInfo(CString str);
	CMFCPropertyGridProperty *Containergroup;
	CMFCPropertyGridProperty *FrameInfogroup;
	CMFCPropertyGridProperty *MetaDatagroup;
//	int m_aaacoutputfmt;
//	int m_aaacoutputsr;
	void SystemClear();
	afx_msg void OnBnClickedAAacAbout();
	CListBox m_aaacconsole;
	//-----
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CComboBox m_aaacoutputfmt;
	CComboBox m_aaacoutputsr;
	//�����ַ���
	CString text;
	CComboBox m_aaaclang;
	afx_msg void OnSelchangeAAacLang();
	CProgressCtrl m_aaacprogress;

	CWinThread *pThreadProcess;
	CEdit m_aaacprogresstext;
};
