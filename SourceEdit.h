#if !defined(AFX_SOURCEEDIT_H__638DFCA7_F73E_463E_AD8A_08589E3D1932__INCLUDED_)
#define AFX_SOURCEEDIT_H__638DFCA7_F73E_463E_AD8A_08589E3D1932__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSourceEdit : public CEdit
{
// Construction
public:
	CSourceEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSourceEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSourceEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSourceEdit)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOURCEEDIT_H__638DFCA7_F73E_463E_AD8A_08589E3D1932__INCLUDED_)
