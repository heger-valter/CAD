// EdgeIges.h: interface for the CEdgeIges class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EDGEIGES_H__6CA86C62_930E_11D5_8CB5_00D00908C1A5__INCLUDED_)
#define AFX_EDGEIGES_H__6CA86C62_930E_11D5_8CB5_00D00908C1A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class igesArchive;
#include "BaseIges.h"

class CEdgeIges : public CBaseIges  
{
public:
	void Serialize( igesArchive &ar);
	CEdgeIges();
	virtual ~CEdgeIges();

};


class CEdgeListIges : public CEdgeIges 
{
public:
	void Serialize( igesArchive &ar);
	CEdgeListIges();
	virtual ~CEdgeListIges();

};


#endif // !defined(AFX_EDGEIGES_H__6CA86C62_930E_11D5_8CB5_00D00908C1A5__INCLUDED_)
