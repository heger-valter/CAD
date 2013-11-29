// parameterDataIges.h: interface for the parameterDataIges class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARAMETERDATAIGES_H__6CA86C70_930E_11D5_8CB5_00D00908C1A5__INCLUDED_)
#define AFX_PARAMETERDATAIGES_H__6CA86C70_930E_11D5_8CB5_00D00908C1A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//class CObject;
//class CArray ;
//class CPtrArray;
//class CObList;
#include <afx.h>// CString
#include <afxcoll.h>// CString

//typedef CTypedPtrListpd<CObList, CObject*>  CMyList;
//#include <Afxtempl.h>// CString

class igesArchive;

class parameterDataIges : public CObList  
{
public:
	parameterDataIges(int n = 0);
	virtual ~parameterDataIges();
//CObList m_data;
#ifdef  ENCAPSULATE
	void Serialize( igesArchive &rIgesArchive);
#endif//ENCAPSULATE
};

#endif // !defined(AFX_PARAMETERDATAIGES_H__6CA86C70_930E_11D5_8CB5_00D00908C1A5__INCLUDED_)
