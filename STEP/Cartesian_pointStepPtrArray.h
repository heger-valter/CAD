// Cartesian_pointStepPtrArray.h: interface for the CCartesian_pointStepPtrArray0 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CARTESIAN_POINTSTEPPTRARRAY_H__01A08CB7_172B_4F52_8D1E_7725619EEF61__INCLUDED_)
#define AFX_CARTESIAN_POINTSTEPPTRARRAY_H__01A08CB7_172B_4F52_8D1E_7725619EEF61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCartesian_pointStepPtrArray : public CPtrArray
{
public:   
	int Add(void*);
	HRESULT Find( CCartesian_pointStep*&pCartesian_pointNew, 
                CCartesian_pointStep*&pCartesian_pointOld);
  CPtrArray m_hash;// hash table on entries
  CCartesian_pointStepPtrArray(int iSize=100);
  virtual ~CCartesian_pointStepPtrArray(void);
  int SetAt(int nIndex, CCartesian_pointStep*& newElement);
  CCartesian_pointStep* GetAt(int nIndex);
private:
	HRESULT fin();
};

#endif // !defined(AFX_CARTESIAN_POINTSTEPPTRARRAY_H__01A08CB7_172B_4F52_8D1E_7725619EEF61__INCLUDED_)
