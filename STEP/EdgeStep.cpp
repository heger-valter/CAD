// EdgeStep.cpp: implementation of the CEdgeStep class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#ifdef _WINDOWS 
#include "scribble.h"
#endif

#include "EdgeStep.h"
#include "BaseStep.h"
#include "VertexStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEdgeStep::CEdgeStep(CBaseStep * pFrom, CVertexStep& rEdge_start, CVertexStep& rEdge_end//,CurveStep&   
                     )
  :CTopological_representation_itemStep(pFrom)
  , m_pEdge_start(&rEdge_start)
  , m_pEdge_end  (&rEdge_end)
{
  nameClass("Edge");
}

CEdgeStep::~CEdgeStep()
{
  /*
//fin();
  try{
    delete &m_pEdge_start&;
    delete &m_pEdge_end&  ;
  }
  catch(...){
    bool bCEdgeStepGood = false;
//  ASSERT( bCEdgeStepGood );
//  Notify("vertices not set!");
  }
*/
}

HRESULT CEdgeStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  else {
    return E_FAIL;
  }
}
void CEdgeStep::Serialize(stepArchive &ar)
{
  if (!isSerialized()){
    setSerialized();
    try{
      writeChild( ar, m_pEdge_start->getNum(), m_pEdge_end->getNum());
      m_pEdge_start->Serialize(ar);
      m_pEdge_end->Serialize(ar);
    }
    catch(...){
      bool bCEdgeStepGood = false;
  //  ASSERT( bCEdgeStepGood );
  //  Notify("verticies not set!");
      ar << "\nError caught in CEdgeStep::Serialize!\n";
  //  throw;
    }
  }
}

CVertexStep* CEdgeStep::GetEdge_end()
{
  return m_pEdge_end  ;
}


CVertexStep* CEdgeStep::GetEdge_start()
{
  return m_pEdge_start;
}

//////////////////////////////////////////////////////////
// who  date      history
// wh   03/30/02  getmethods

