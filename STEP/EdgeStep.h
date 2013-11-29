// EdgeStep.h: interface for the CEdgeStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EDGESTEP_H__F3ABC471_0EA0_11D5_BFF1_0004AC6EEF35__INCLUDED_)
#define AFX_EDGESTEP_H__F3ABC471_0EA0_11D5_BFF1_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Topological_representation_itemStep.h"
class CVertexStep;
class CEdgeStep : public CTopological_representation_itemStep  
{
public:
	CEdgeStep(CBaseStep * pFrom, CVertexStep& rEdge_start, CVertexStep& rEdge_end  );
	virtual ~CEdgeStep();
  HRESULT backPtr( CBaseStep*& prBrep);
	virtual CVertexStep* GetEdge_end();
	virtual CVertexStep* GetEdge_start();
	void Serialize(stepArchive &ar);
	CVertexStep* m_pEdge_start;
	CVertexStep* m_pEdge_end  ;

};

//////////////////////////////////////////////////////////
// who  date      history
// wh   03/30/02  getmethods

#endif // !defined(AFX_EDGESTEP_H__F3ABC471_0EA0_11D5_BFF1_0004AC6EEF35__INCLUDED_)
