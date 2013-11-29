// CircleStepPtrArray.h: interface for the CCircleStepPtrArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CIRCLESTEPPTRARRAY_H__2E6544C2_DBAE_4793_8630_9F05E278C26E__INCLUDED_)
#define AFX_CIRCLESTEPPTRARRAY_H__2E6544C2_DBAE_4793_8630_9F05E278C26E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCircleStep;
#include "baseStep.h"
#include "agitoPtrArray.h"

class CCircleStepPtrArray : public CrcPtrArray  
{
  CPtrArray m_hash;
public:
	CCircleStepPtrArray();
	virtual ~CCircleStepPtrArray();
  int SetAt( int nIndex, CCircleStep* newElement, bool& rbOrient);
  int Add( CCircleStep* newElement);
  CCircleStep* GetAt( int nIndex);
};

#endif // !defined(AFX_CIRCLESTEPPTRARRAY_H__2E6544C2_DBAE_4793_8630_9F05E278C26E__INCLUDED_)
