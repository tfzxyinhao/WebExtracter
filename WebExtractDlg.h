//{{AFX_INCLUDES()
#include "webbrowser.h"
//}}AFX_INCLUDES
#if !defined(AFX_WEBEXTRACTDLG_H__ED497468_4E42_4202_A1DA_0CE66705CA30__INCLUDED_)
#define AFX_WEBEXTRACTDLG_H__ED497468_4E42_4202_A1DA_0CE66705CA30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <curl.h>
#include <string>
#include <atlbase.h>
#include <process.h>

#include "FilePath.h"
#include "SourceEdit.h"
#include "DispatchImpl.h"
#include "SplitterControl.h"
#include "greta/regexpr2.h"

using namespace regex;
#pragma comment(lib,"libcurl.lib")

#define TIMER_STARTUP			1
#define TIMER_STARTUP_TIMEOUR	3000

#define HIDWORD(x) (x>>16)
#define LODWORD(x) (x&0x0000ffff)
#define MAKEDWORD(h,l) ((((h)&0x0000ffff)<<16)|((l)&0x0000ffff))

typedef std::basic_string<TCHAR> string;
typedef UINT (__stdcall *pfnWorkThread)(void *);

class CWebExtractDlg : public CDialog
{
// Construction
public:
	CWebExtractDlg(CWnd* pParent = NULL);	// standard constructor
	~CWebExtractDlg();

	BOOL			m_bRun;
	BOOL			m_bWeb;
	HANDLE			m_hThread;

	static UINT __stdcall WorkThread(void* arg);		//¹ÉÆ±Ïß³Ì
	static size_t SaveTmpWebPage(void *ptr, size_t size, size_t nmemb, void *param);

	void	UpdateParam();
	void	SetButtonCheck(UINT nID,int nCheck = 1);
	void	SetControlText(UINT nId,LPCTSTR lpstrText);
	void	EnableControl(UINT nId,BOOL bEnable = TRUE);

	int		Serialize(BOOL bLoad = TRUE);

	int		DownloadSource();
	int		StopThread(HANDLE& hThread,BOOL& bRun);
	int		StartThread(HANDLE& hThread,BOOL& bRun,pfnWorkThread pfn);

	char*	SaveToMem(IDispatch* pDisp);
	int		relayout();

	CString	m_strUrl,m_strRegex;
	CStringArray		m_RecentList;

	CDispatchImpl	m_Disp;
// Dialog Data
	//{{AFX_DATA(CWebExtractDlg)
	enum { IDD = IDD_WEBEXTRACT_DIALOG };
	CStatic	m_resultinfo;
	CEdit	m_regx;
	CWebBrowser	m_web;
	CTreeCtrl	m_tree;
	CSourceEdit	m_source;
	CSplitterControl m_wndSplitter;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWebExtractDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWebExtractDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnGetsoucrce();
	afx_msg void OnGetresult();
	afx_msg void OnCheckSettop();
	afx_msg void OnClose();
	afx_msg void OnDocumentCompleteWeb(LPDISPATCH pDisp, VARIANT FAR* URL);
	afx_msg void OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnResizeTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnStatusTextChangeWeb(LPCTSTR Text);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBeforeNavigate2Web(LPDISPATCH pDisp, VARIANT FAR* URL, VARIANT FAR* Flags, VARIANT FAR* TargetFrameName, VARIANT FAR* PostData, VARIANT FAR* Headers, BOOL FAR* Cancel);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WEBEXTRACTDLG_H__ED497468_4E42_4202_A1DA_0CE66705CA30__INCLUDED_)
