#include "stdafx.h"
#include "WebExtract.h"
#include "SourceEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



CSourceEdit::CSourceEdit()
{
}

CSourceEdit::~CSourceEdit()
{
}


BEGIN_MESSAGE_MAP(CSourceEdit, CEdit)
	//{{AFX_MSG_MAP(CSourceEdit)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSourceEdit message handlers

BOOL CSourceEdit::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CEdit::PreTranslateMessage(pMsg);
}
