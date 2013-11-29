// ShellIges.h: interface for the CShellIges class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHELLIGES_H__6CA86C65_930E_11D5_8CB5_00D00908C1A5__INCLUDED_)
#define AFX_SHELLIGES_H__6CA86C65_930E_11D5_8CB5_00D00908C1A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CString;
#include "BaseIges.h"
#include <afx.h>// MFC headers

class CShellIges : public CBaseIges  
{
public:
	void Serialize( igesArchive &ar);
	CShellIges();
	virtual ~CShellIges();

};

#endif // !defined(AFX_SHELLIGES_H__6CA86C65_930E_11D5_8CB5_00D00908C1A5__INCLUDED_)
