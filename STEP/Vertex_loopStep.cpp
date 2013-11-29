// Vertex_loopStep.cpp: implementation of the CVertex_loopStep class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Vertex_loopStep.h"
#include "loopStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVertex_loopStep::CVertex_loopStep( CVertex_pointStep* pVertex_pointStep)
: CLoopStep(this)
{
  nameClass("Vertex_loop");
}


CVertex_loopStep::~CVertex_loopStep()
{

}

HRESULT CVertex_loopStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  return E_FAIL;
}

CVertexStep* CVertex_loopStep::loop_vertex()
{ 
  ASSERT(false);
  return NULL;
}

