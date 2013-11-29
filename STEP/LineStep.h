// LineStep.h: interface for the CLineStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINESTEP_H__0C5C1022_13EB_11D5_9387_0004AC6EEF35__INCLUDED_)
#define AFX_LINESTEP_H__0C5C1022_13EB_11D5_9387_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CurveStep.h"
#include "PointStep.h"	// Added by ClassView
#include "VectorStep.h"


class CLineStep : public CCurveStep  
{
public:
	void fin();
	HRESULT contains(  CCartesian_pointStep& rPos, intersectionType& eIntersect1
    , double& rdParam);
	CLineStep( CCartesian_pointStep& rPos, CVectorStep& rDir, CCartesian_pointStep* pPos1);
//CLineStep( CCartesian_pointStep& rPos0, CCartesian_pointStep& rPos1);
	virtual ~CLineStep();
	void Serialize(stepArchive &ar);
	CCartesian_pointStep* m_pPos;
	CVectorStep* m_pDir;

  HRESULT intersect( //const CLineStep& l0 , 
                  const CLineStep& l1, 
                  intersectionType& eIntersect1, 
                  CPtrArray* pPointXs ,
                  double& lamda0, 
                  double& lamda1, 
                  intersectionType& eIntersect0);

#if 0
  HRESULT minDistance(
                  const CLineStep& l1, 
                  intersectionType& eIntersect, 
                  CPtrArray* pPointXs ,
                  double& lamda0, 
                  double& lamda1);
#endif
  // optional, added to speed up calculations
	CCartesian_pointStep* m_pPos1;// the far endpoint
  HRESULT backPtr( CBaseStep*& prBrep);
};



class CLineStepPtrArray : public CPtrArray
{
  CPtrArray m_hash ;
public:   
  CLineStepPtrArray(int iSize);
  virtual ~CLineStepPtrArray(void);
  int SetAt(int nIndex, CLineStep* newElement, bool& rbOrient);
  CLineStep* GetAt(int nIndex);
  int Add( CLineStep* newElement);
};

#endif // !defined(AFX_LINESTEP_H__0C5C1022_13EB_11D5_9387_0004AC6EEF35__INCLUDED_)
