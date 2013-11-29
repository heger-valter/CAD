// CurveStep.h: interface for the CCurveStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CURVESTEP_H__0C5C1021_13EB_11D5_9387_0004AC6EEF35__INCLUDED_)
#define AFX_CURVESTEP_H__0C5C1021_13EB_11D5_9387_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Geometric_representation_itemStep.h"

class CCurveStep : public CGeometric_representation_itemStep  
{
public:
	void Serialize(stepArchive &ar);
	CCurveStep();
	virtual ~CCurveStep();
  HRESULT backPtr( CBaseStep*& prBrep);

};

class CCurveStepPtrArray : public CPtrArray
{
public:   
  CPtrArray* m_hash;
  CCurveStepPtrArray (void);
  virtual ~CCurveStepPtrArray (void);
  int SetAt(int nIndex, CCurveStep* newElement);
  CCurveStep* GetAt(int nIndex);
};


#endif // !defined(AFX_CURVESTEP_H__0C5C1021_13EB_11D5_9387_0004AC6EEF35__INCLUDED_)
