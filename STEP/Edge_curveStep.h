// Edge_curveStep.h: interface for the CEdge_curveStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EDGE_CURVESTEP_H__4831C901_205C_11D5_8CAE_00D00908C1A5__INCLUDED_)
#define AFX_EDGE_CURVESTEP_H__4831C901_205C_11D5_8CAE_00D00908C1A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EdgeStep.h"

class CCurveStep;
class COriented_edgeStep ;

class CEdge_curveStep : public CEdgeStep  
{
public:
	HRESULT split( CVertexStep&    rVertexStep
//             , CEdge_curveStep* pEdge_curveStep1
               , CEdge_loopStep* pEdge_loopStepCylinder
               , CEdge_loopStep* pEdge_loopStep1
               );
	void Serialize(stepArchive &ar);
	void fin();
	CEdge_curveStep(  CVertexStep& rEdge_start, 
                    CVertexStep& rEdge_end , 
                    CCurveStep&  rEdge_geometry, 
                    bool         bSame_sense =1);
	virtual ~CEdge_curveStep();
	CCurveStep& m_rEdge_geometry;
	bool m_bSame_sense;
  COriented_edgeStep *pOriented_edgeStep0;
  COriented_edgeStep *pOriented_edgeStep1;
  HRESULT backPtr( CBaseStep*& prBrep);
static  CPtrArray* m_pEdge_curveArray;
};

#endif // !defined(AFX_EDGE_CURVESTEP_H__4831C901_205C_11D5_8CAE_00D00908C1A5__INCLUDED_)
