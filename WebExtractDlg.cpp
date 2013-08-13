#include "stdafx.h"
#include "WebExtract.h"
#include "WebExtractDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWebExtractDlg::CWebExtractDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWebExtractDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWebExtractDlg)
		m_bRun = FALSE;
		m_hThread = NULL;
		m_bWeb = TRUE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CWebExtractDlg::~CWebExtractDlg()
{
	
}

void CWebExtractDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWebExtractDlg)
	DDX_Control(pDX, IDC_STATIC_INFO, m_resultinfo);
	DDX_Control(pDX, IDC_REGEX, m_regx);
	DDX_Control(pDX, IDC_WEB, m_web);
	DDX_Control(pDX, IDC_TREE, m_tree);
	DDX_Control(pDX, IDC_SOURCE, m_source);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWebExtractDlg, CDialog)
	//{{AFX_MSG_MAP(CWebExtractDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_GETSOUCRCE, OnGetsoucrce)
	ON_BN_CLICKED(IDC_GETRESULT, OnGetresult)
	ON_BN_CLICKED(IDC_CHECK_SETTOP, OnCheckSettop)
	ON_WM_CLOSE()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, OnSelchangedTree)
	ON_NOTIFY(SPN_SIZED, IDC_SPLITBAR, OnResizeTree)
	ON_WM_SIZE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CWebExtractDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_source.SetLimitText(-1);
	curl_global_init(CURL_GLOBAL_ALL);

	SetButtonCheck(IDC_CHECK_SETTOP);
	SetControlText(IDC_URL,_T("http://sc.hkex.com.hk/TuniS/www.hkex.com.hk/chi/market/sec_tradinfo/stockcode/eisdeqty_c.htm"));

	m_wndSplitter.Create(WS_CHILD | WS_VISIBLE,CRect(0,0,1,1), this, IDC_SPLITBAR);
	m_wndSplitter.SetStyle();
	m_wndSplitter.SetRange(0,1500, -1);
	
	relayout();
	SetTimer(TIMER_STARTUP,TIMER_STARTUP_TIMEOUR,NULL);
	return TRUE;
}
void CWebExtractDlg::OnClose() 
{
	curl_global_cleanup();
	Serialize(FALSE);
	CDialog::OnClose();
}

void CWebExtractDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CWebExtractDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWebExtractDlg::OnGetsoucrce() 
{
	UpdateParam();
	if(m_bWeb)
		m_web.Navigate(m_strUrl,0,0,0,0);
	else
		StartThread(m_hThread,m_bRun,WorkThread);


	m_RecentList.Add(m_strUrl);

	EnableControl(IDC_GETSOUCRCE,FALSE);
}

void CWebExtractDlg::OnGetresult() 
{
	LPCTSTR lpstr;
	HTREEITEM hRoot,hItem;
	size_t nGroup,size,i;
	match_results results;
	CString strInfo,strSource;
	DWORD dwTime,dwStart,dwEnd;
	match_results::backref_type br;

	UpdateParam();
	m_source.GetWindowText(strSource);
	if(strSource.GetLength() < 1)
		return;

	EnableControl(IDC_GETRESULT,FALSE);
	
	size = 0;
	nGroup = 0;
	m_tree.DeleteAllItems();
	dwTime = GetTickCount();
	lpstr = strSource.GetBuffer(0);

	try{
		rpattern patStock(m_strRegex.GetBuffer(0),ALLBACKREFS | GLOBAL);
		br = patStock.match(lpstr,results);
		
		if (br.matched){
			match_results::backref_vector vec = results.all_backrefs();
			match_results::backref_vector::iterator Iter = vec.begin();
			nGroup = patStock.cgroups();
			size = vec.size();
			while (Iter != vec.end()){
				hRoot = m_tree.InsertItem(Iter->str().c_str());
				dwStart = (Iter->begin() - lpstr);
				dwEnd = (Iter->end() - lpstr);
				m_tree.SetItemData(hRoot,MAKEDWORD(dwStart,dwEnd));
				++Iter;
				
				for (i=1;i<nGroup;i++){
					hItem = m_tree.InsertItem(Iter->str().c_str(),hRoot);
					dwStart = (Iter->begin() - lpstr);
					dwEnd = (Iter->end() - lpstr);
					m_tree.SetItemData(hItem,MAKEDWORD(dwStart,dwEnd));
					++Iter;
				}
			}
		}
	}catch(CException* e){
		TCHAR szError[MAX_PATH];
		e->GetErrorMessage(szError,_MAX_PATH);
		e->Delete();
		MessageBox(szError,_T("异常"),MB_OK|MB_ICONERROR);
	}

	strInfo.Format(_T("group:%d,result:%d,TimeCose:%dms"),nGroup,size,GetTickCount()-dwTime);
	SetControlText(IDC_STATIC_INFO,strInfo);
	EnableControl(IDC_GETRESULT);
}

UINT __stdcall CWebExtractDlg::WorkThread( void* arg )
{
	CWebExtractDlg* pThis = reinterpret_cast<CWebExtractDlg*>(arg);
	if(pThis)
		pThis->DownloadSource();

	CloseHandle(pThis->m_hThread);
	pThis->m_hThread = NULL;
	
	return 1;
}


size_t CWebExtractDlg::SaveTmpWebPage( void *ptr, size_t size, size_t nmemb, void *param )
{
	std::string *pStr = (std::string *)param;
	pStr->append((const char*)ptr);
	return nmemb*size;
}

int CWebExtractDlg::StopThread( HANDLE& hThread,BOOL& bRun )
{
	MSG msg;
	bRun = FALSE;
	
	if(!hThread)
		return 1;
	
	while (1)
	{
		if(MsgWaitForMultipleObjects(1,&hThread,FALSE,INFINITE,QS_ALLINPUT) == WAIT_OBJECT_0){
			CloseHandle(hThread);
			hThread = NULL;
			break;
		}
		
		while(PeekMessage(&msg,0,0,0,PM_REMOVE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	
	return 1;
}

int CWebExtractDlg::StartThread( HANDLE& hThread,BOOL& bRun,pfnWorkThread pfn )
{
	bRun = TRUE;
	if(hThread)
		return 1;
	
	hThread = (HANDLE)_beginthreadex(0,0,pfn,this,0,0);
	if(hThread == NULL)
		return 0;
	
	return 1;
}

int CWebExtractDlg::DownloadSource()
{
	CURL *curl;
	CFile file;
	CURLcode ret;
	long nRespCode;
	CString strError;
	string strContent;

	curl = curl_easy_init();
	if(curl == NULL)
		return 0;

	//公共设置
	curl_easy_setopt(curl,CURLOPT_URL,m_strUrl);
	curl_easy_setopt(curl,CURLOPT_REFERER,m_strUrl);
	curl_easy_setopt(curl,CURLOPT_USERAGENT,"Mozilla/5.0 (Linux; N; Android 2.3.5; zh-cn; HTC_IncredibleS_S710e Build/GRJ90) AppleWebKit/533.1 (KHTML, like Gecko) Version/4.0 Mobile Safari/533.1");
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
	curl_easy_setopt(curl,CURLOPT_WRITEDATA,&strContent);
	curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,SaveTmpWebPage);
	curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "c:\\cookie.txt");
	curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "c:\\cookie.txt");
	
	ret = curl_easy_perform(curl);
	if(ret == CURLE_OK){
		curl_easy_getinfo(curl,CURLINFO_RESPONSE_CODE,&nRespCode);
		if(nRespCode != 200){
			strError.Format(_T("[+下载错误] 响应代码:%d"),nRespCode);
			MessageBox(strError,_T("提示"),MB_OK|MB_ICONERROR);
		}else{
			EnableControl(IDC_GETSOUCRCE);
			SetControlText(IDC_SOURCE,strContent.c_str());

			if(file.Open(_T("tmp.html"),CFile::modeCreate|CFile::modeWrite)){
				file.Write(strContent.c_str(),strContent.size());
				file.Close();
			}
		}
	}
	curl_easy_cleanup(curl);
	return 1;
}

void CWebExtractDlg::EnableControl( UINT nId,BOOL bEnable /*= TRUE*/ )
{
	CWnd* pWnd = GetDlgItem(nId);
	if(pWnd && pWnd->GetSafeHwnd()){
		pWnd->EnableWindow(bEnable);
	}
}

void CWebExtractDlg::UpdateParam()
{
	CWnd* pWnd;

	pWnd = GetDlgItem(IDC_URL);
	if(pWnd && pWnd->GetSafeHwnd()){
		pWnd->GetWindowText(m_strUrl);
	}

	pWnd = GetDlgItem(IDC_REGEX);
	if(pWnd && pWnd->GetSafeHwnd()){
		pWnd->GetWindowText(m_strRegex);
	}
}

void CWebExtractDlg::SetControlText(UINT nId, LPCTSTR lpstrText )
{
	if(lpstrText == NULL)
		return;

	CWnd* pWnd = GetDlgItem(nId);
	if(pWnd && pWnd->GetSafeHwnd()){
		pWnd->SetWindowText(lpstrText);
	}
}

void CWebExtractDlg::OnCheckSettop() 
{
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_SETTOP);
	if(pBtn && pBtn->GetSafeHwnd()){
		m_bWeb = pBtn->GetCheck();
	}
}


BEGIN_EVENTSINK_MAP(CWebExtractDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CWebExtractDlg)
	ON_EVENT(CWebExtractDlg, IDC_WEB, 259 /* DocumentComplete */, OnDocumentCompleteWeb, VTS_DISPATCH VTS_PVARIANT)
	ON_EVENT(CWebExtractDlg, IDC_WEB, 102 /* StatusTextChange */, OnStatusTextChangeWeb, VTS_BSTR)
	ON_EVENT(CWebExtractDlg, IDC_WEB, 250 /* BeforeNavigate2 */, OnBeforeNavigate2Web, VTS_DISPATCH VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PBOOL)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

char* CWebExtractDlg::SaveToMem( IDispatch* pDisp )
{
	HRESULT hr;
	HGLOBAL hMem;
	CComPtr<IStream> spStream; 
	CComPtr<IPersistStreamInit> spPersistStreamInit;

	if(pDisp == NULL)
		return 0;
	
	CComPtr<IDispatch> spDoc(pDisp);
	
	hr = spDoc->QueryInterface(IID_IPersistStreamInit,(void**)&spPersistStreamInit);
	if(!SUCCEEDED(hr))
		return 0;
	
	hr = CreateStreamOnHGlobal(NULL,FALSE,&spStream);
	if(!SUCCEEDED(hr))
		return 0;
	
	hr = spPersistStreamInit->Save(spStream,FALSE);

	hr = GetHGlobalFromStream(spStream,&hMem);
	LPTSTR pstr = (LPTSTR)GlobalLock(hMem);
	SetControlText(IDC_SOURCE,pstr);
	GlobalUnlock(hMem);
	GlobalFree(hMem);

	return 0;
}

void CWebExtractDlg::OnDocumentCompleteWeb(LPDISPATCH pDisp, VARIANT FAR* URL) 
{
	SaveToMem(m_web.GetDocument());
	EnableControl(IDC_GETSOUCRCE);
}

void CWebExtractDlg::OnResizeTree( NMHDR* pNMHDR, LRESULT* pResult )
{
	*pResult = 0;
	SPC_NMHDR *pSPC = (SPC_NMHDR*)pNMHDR;
	if(pSPC == NULL)
		return;
	
	int delta = pSPC->delta;
	CSplitterControl::ChangeWidth(&m_source, delta);
	CSplitterControl::ChangeWidth(&m_tree, -delta, CW_RIGHTALIGN);

	CSplitterControl::ChangeWidth(&m_regx, -delta, CW_RIGHTALIGN);
	CSplitterControl::ChangeWidth(&m_resultinfo, -delta, CW_RIGHTALIGN);

	Invalidate();
	UpdateWindow();
}

void CWebExtractDlg::OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HTREEITEM hItem;
	DWORD dwData,dwStart,dwEnd;

	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	*pResult = 0;

	hItem = m_tree.GetSelectedItem();
	if(hItem && pNMTreeView->action){
		dwData = m_tree.GetItemData(hItem);
		
		dwEnd = LOWORD(dwData);
		dwStart = HIDWORD(dwData);
		m_source.SetSel(dwStart,dwEnd,FALSE);
	}
	
}

void CWebExtractDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	if(IsWindow(GetSafeHwnd()) && cx > 0 && cy > 0)
		relayout();
}

int CWebExtractDlg::relayout()
{
	CWnd* pWnd;
	CRect rtClient,rtItem;
	int nColumn,nTextHeight,nButtonWidth,nButtonHeight,nGap,nBorder,nLeft;

	nGap = 5;
	nBorder = 2;
	nButtonWidth = 70;
	nButtonHeight = 22;
	nTextHeight = 28;

	GetClientRect(rtClient);
	nColumn = rtClient.Width()/10;

	//移动源码
	rtItem.left = rtClient.left+nBorder;
	rtItem.top = rtClient.top + nTextHeight+nBorder;
	rtItem.right = rtClient.left + nColumn*5;
	rtItem.bottom = rtClient.bottom - nBorder;
	pWnd = GetDlgItem(IDC_SOURCE);
	if(pWnd)
		pWnd->MoveWindow(rtItem);

	nLeft = rtClient.left + nColumn*5 + nBorder*3;

	//移动分割条
	rtItem.left = rtItem.right;
	rtItem.right = nLeft - nBorder;
	if(IsWindow(m_wndSplitter.GetSafeHwnd()))
		m_wndSplitter.MoveWindow(rtItem);

	//移动结果显示控件
	rtItem.left = nLeft;
	rtItem.right = rtClient.right - nBorder;
	rtItem.top = rtClient.top + nTextHeight*2+nBorder+120;
	rtItem.bottom = rtClient.bottom - nBorder;
	pWnd = GetDlgItem(IDC_TREE);
	if(pWnd)
		pWnd->MoveWindow(rtItem);

	//移动正则控件
	rtItem.left = nLeft;
	rtItem.right = rtClient.right - nBorder;
	rtItem.top = rtClient.top + nTextHeight*2;
	rtItem.bottom = rtItem.top + 120 - nGap;
	pWnd = GetDlgItem(IDC_REGEX);
	if(pWnd)
		pWnd->MoveWindow(rtItem);

	//移动结果信息控件
	rtItem.left = nLeft;
	rtItem.top = rtClient.top + nTextHeight+nBorder;
	rtItem.right = rtClient.right - nButtonWidth*2 - nBorder*2;
	rtItem.bottom = rtItem.top + nButtonHeight;
	pWnd = GetDlgItem(IDC_STATIC_INFO);
	if(pWnd)
		pWnd->MoveWindow(rtItem);

	//移动置顶控件
	rtItem.OffsetRect(rtItem.Width()+nGap,0);
	rtItem.right = rtItem.left + nButtonWidth;
	pWnd = GetDlgItem(IDC_CHECK_SETTOP);
	if(pWnd)
		pWnd->MoveWindow(rtItem);

	//移动web控件
	rtItem.OffsetRect(rtItem.Width()+nGap,nGap);
	rtItem.right = rtItem.left + 15;
	rtItem.bottom = rtItem.top + 15;
	if(IsWindow(m_web.GetSafeHwnd()))
		m_web.MoveWindow(rtItem);

	//移动正则匹配按钮
	rtItem.right = rtClient.right - nBorder;
	rtItem.top = rtClient.top + nBorder;
	rtItem.left = rtItem.right - nButtonWidth;
	rtItem.bottom = rtItem.top + nButtonHeight;
	pWnd = GetDlgItem(IDC_GETRESULT);
	if(pWnd)
		pWnd->MoveWindow(rtItem);

	//移动下载源码控件
	rtItem.OffsetRect(0-nButtonWidth-nGap,0);
	pWnd = GetDlgItem(IDC_GETSOUCRCE);
	if(pWnd)
		pWnd->MoveWindow(rtItem);

	//移动地址输入控件
	rtItem.OffsetRect(0-nButtonWidth-nGap,0);
	rtItem.left = rtClient.left + nBorder + nTextHeight;
	pWnd = GetDlgItem(IDC_URL);
	if(pWnd)
		pWnd->MoveWindow(rtItem);

	return 1;
}

void CWebExtractDlg::OnStatusTextChangeWeb(LPCTSTR Text) 
{
	SetWindowText(Text);
}

void CWebExtractDlg::SetButtonCheck( UINT nID,int nCheck )
{
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_SETTOP);
	if(pBtn && pBtn->GetSafeHwnd()){
		pBtn->SetCheck(nCheck);
	}
}

void CWebExtractDlg::OnTimer(UINT nIDEvent) 
{
	if(TIMER_STARTUP_TIMEOUR == nIDEvent){
		KillTimer(nIDEvent);
		Serialize();
	}
	CDialog::OnTimer(nIDEvent);
}


int CWebExtractDlg::Serialize( BOOL bLoad /*= TRUE*/ )
{
	CFile file;
	UINT uflags,uMode;
	CString strPath,strConfig;
	CFilePath::GetModulePath(strPath);
	strConfig.Format(_T("%s\\sesssion.dat"));
	
	if(!CFilePath::IsFileExists(strConfig))
		return 0;

	if(bLoad){
		uMode = CArchive::load;
		uflags = CFile::modeRead;
	}else{
		uMode = CArchive::store;
		uflags = CFile::modeWrite|CFile::modeCreate;
	}

	
	if(file.Open(strConfig,uflags)){
		CArchive ar(&file,uMode);

		m_RecentList.Serialize(ar);
		m_regx.Serialize(ar);
		m_source.Serialize(ar);
			
		ar.Close();
		file.Close();
	}
	return 1;
}

void CWebExtractDlg::OnOK()
{
	DownloadSource();
}

void CWebExtractDlg::OnCancel()
{
	CDialog::OnCancel();
}

void CWebExtractDlg::OnBeforeNavigate2Web(LPDISPATCH pDisp, VARIANT FAR* URL, VARIANT FAR* Flags, VARIANT FAR* TargetFrameName, VARIANT FAR* PostData, VARIANT FAR* Headers, BOOL FAR* Cancel) 
{
	CString strUrl(URL->bstrVal);
	OutputDebugString(strUrl);OutputDebugString(_T("\r\n"));
}

