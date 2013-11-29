// Oriented_EdgeStep.h: interface for the COriented_EdgeStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ORIENTED_EDGESTEP_H__4E6E78C1_123F_11D5_9387_00D00908C1A5__INCLUDED_)
#define AFX_ORIENTED_EDGESTEP_H__4E6E78C1_123F_11D5_9387_00D00908C1A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EdgeStep.h"
#include "CurveStep.h"
class CEdge_curveStep;
class CVertexStep;

class   COriented_edgeStep : public CEdgeStep  
{
public:
	void Serialize(stepArchive &ar);
	bool m_bOrientation;

	virtual ~COriented_edgeStep();
	COriented_edgeStep(
            CEdge_curveStep* pCurveStep, 
            bool bOrientation        = true, 
            CVertexStep *pPointStep0 = NULL, // edge use 0
            CVertexStep *pPointStep1 = NULL);// edge use 1
  CEdgeStep* m_pEdge_element;
  HRESULT backPtr( CBaseStep*& prBrep);
	virtual CVertexStep* GetEdge_end();
	virtual CVertexStep* GetEdge_start();
};

class COriented_edgeStepPtrArray : public CPtrArray
{
public:   
  CPtrArray* m_hash;
  COriented_edgeStepPtrArray( int i);
  virtual ~COriented_edgeStepPtrArray( void);
  void SetAt( int nIndex, COriented_edgeStep* newElement);
  COriented_edgeStep* GetAt( int nIndex, bool bOrientation);
};


#endif // !defined(AFX_ORIENTED_EDGESTEP_H__4E6E78C1_123F_11D5_9387_00D00908C1A5__INCLUDED_)
