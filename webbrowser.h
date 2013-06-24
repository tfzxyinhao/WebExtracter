#if !defined(AFX_WEBBROWSER_H__85DC17D5_08A4_4023_95AA_B5FA064EC98B__INCLUDED_)
#define AFX_WEBBROWSER_H__85DC17D5_08A4_4023_95AA_B5FA064EC98B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWebBrowser : public CWnd
{
protected:
	DECLARE_DYNCREATE(CWebBrowser)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x8856f961, 0x340a, 0x11d0, { 0xa9, 0x6b, 0x0, 0xc0, 0x4f, 0xd7, 0x5, 0xa2 } };
		return clsid;
	}

	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); }

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); }

// Attributes
public:

// Operations
public:
	void Navigate(LPCTSTR URL, VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers);
	LPDISPATCH GetDocument();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WEBBROWSER_H__85DC17D5_08A4_4023_95AA_B5FA064EC98B__INCLUDED_)
