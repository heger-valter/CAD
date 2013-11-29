// PointStep.h: interface for the CPointStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POINTSTEP_H__9B2019DE_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_)
#define AFX_POINTSTEP_H__9B2019DE_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "Geometric_representation_itemStep.h"


class CPointStep : public CGeometric_representation_itemStep  
{
public:
	void Serialize( stepArchive &ar);
	CPointStep(CBaseStep*pIn);
	virtual ~CPointStep();
  HRESULT backPtr( CBaseStep*& prBrep);
};




#if 1
// deprecate it
template <class T> 
class CDerivedPtrArray : public CPtrArray
{
  CPtrArray* m_hash;// hash table on entries
public:   
  CDerivedPtrArray(void);
  virtual ~CDerivedPtrArray(void);
  int SetAt(int nIndex, T* newElement);
  T* GetAt(int nIndex);
};
#endif

//////////////////////////////////////////////////////////
// who  date      history

#endif // !defined(AFX_POINTSTEP_H__9B2019DE_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_)
