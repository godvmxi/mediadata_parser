/* 
 * AAC分析器
 * AAC Analysis
 *
 * 雷霄骅 Lei Xiaohua
 * leixiaohua1020@126.com
 * 中国传媒大学/数字电视技术
 * Communication University of China / Digital TV Technology
 * http://blog.csdn.net/leixiaohua1020
 *
 */
#pragma once
#include "resource.h"
#include "stdafx.h"
#include "aac_decode.h"

// CSpecialAAACDlg 对话框
class CSpecialAAACDlg : public CDialogEx
{
// 构造
public:
	CSpecialAAACDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SPECIAL_A_AAC };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	//加载字符串
	CString text;
	CComboBox m_aaaclang;
	afx_msg void OnSelchangeAAacLang();
	CProgressCtrl m_aaacprogress;

	CWinThread *pThreadProcess;
	CEdit m_aaacprogresstext;
};
