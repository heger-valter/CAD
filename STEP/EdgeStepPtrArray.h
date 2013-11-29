// EdgeStepPtrArray.h: interface for the CEdgeStepPtrArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EDGESTEPPTRARRAY_H__D056D061_34AB_11D5_9EA8_CB61934FE736__INCLUDED_)
#define AFX_EDGESTEPPTRARRAY_H__D056D061_34AB_11D5_9EA8_CB61934FE736__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Afxcoll.h"
class CEdgeStep;

class CEdgeStepPtrArray : public CPtrArray  
{
public:
	CEdgeStep* GetAt(int nIndex);
	void SetAt(int i, CEdgeStep* pEdgeStep);
	CEdgeStepPtrArray(int iNewSize);
	virtual ~CEdgeStepPtrArray();
    CPtrArray* m_hash;
};

#endif // !defined(AFX_EDGESTEPPTRARRAY_H__D056D061_34AB_11D5_9EA8_CB61934FE736__INCLUDED_)
