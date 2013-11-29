// Vertex_loopStep.h: interface for the CVertex_loopStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VERTEX_LOOPSTEP_H__0D58ADC1_1329_11D5_9387_0004AC6EEF35__INCLUDED_)
#define AFX_VERTEX_LOOPSTEP_H__0D58ADC1_1329_11D5_9387_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "loopStep.h"

class CVertexStep;
class CVertex_pointStep;
class CVertex_loopStep : public CLoopStep  
{
public:
	CVertex_loopStep( CVertex_pointStep* pVertex_pointStep);
	virtual ~CVertex_loopStep();
	CVertexStep* loop_vertex( void);
// IMPORTANT: dont forget to make sure that the edge about this 
  //vertex loop form a collection of CCW oriented entities
  HRESULT backPtr( CBaseStep*& prBrep);

};

#endif // !defined(AFX_VERTEX_LOOPSTEP_H__0D58ADC1_1329_11D5_9387_0004AC6EEF35__INCLUDED_)
