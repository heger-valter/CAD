// Oriented_EdgeStep.cpp: implementation of the COriented_EdgeStep class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Oriented_EdgeStep.h"
#include "stepArchive.h"
#include "Edge_curveStep.h"
#include "PointStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


COriented_edgeStep::~COriented_edgeStep()
{

}

COriented_edgeStep::COriented_edgeStep(  //CEdgeStep&  rEdge_element, 
                                         CEdge_curveStep* pEdge_curveStep, 
                                         bool        bOrientation,//use 1 for unknown
                                         CVertexStep *pVertexStep0, 
                                         CVertexStep *pVertexStep1
                                      )
  : m_bOrientation(  bOrientation)
//  , m_rEdge_element( rEdge_element)
  , m_pEdge_element(pEdge_curveStep)
  , CEdgeStep(this, *(pEdge_curveStep->m_pEdge_start), *(pEdge_curveStep->m_pEdge_end) )
{
  nameClass("Oriented_edge");
  if (!m_bOrientation){
    // flip them
//  CEdgeStep::m_pEdge_start = rEdge_element.m_pEdge_end ;
//  CEdgeStep::m_pEdge_end   = rEdge_element.m_pEdge_start;
  }
}

CVertexStep* COriented_edgeStep::GetEdge_end()
{
  return m_bOrientation?m_pEdge_end : m_pEdge_start;
}


CVertexStep* COriented_edgeStep::GetEdge_start()
{
  return m_bOrientation? m_pEdge_start: m_pEdge_end;
}

void COriented_edgeStep::Serialize(stepArchive &ar)
{
  try{
    if (!isSerialized()){
      setSerialized();
      writeChild( ar, m_pEdge_element->getNum(), m_bOrientation);
      m_pEdge_element->m_pBack = this;
      m_pEdge_element->Serialize(ar);

#ifdef   WRITEEULER
      CBaseStep* pBaseStep=NULL;
      backPtr( pBaseStep);
      if (NULL!=pBaseStep){
        CManifold_solid_brepStep* pManifold_solid_brepStep=(CManifold_solid_brepStep*) pBaseStep;
        pManifold_solid_brepStep->eulerCnt.m_numHalfedges++;
      }
#endif//WRITEEULER
    }

  }
  catch(...){
    ar << "\n/*Errors detected in COriented_edgeStep::Serialize #\n";
    ar <<   ", but continuing*/\n" ;    
    setSerialized();
  }
}


COriented_edgeStepPtrArray::COriented_edgeStepPtrArray(int iSize)
: CPtrArray()
{
  SetSize( iSize*4);
  m_hash = new CPtrArray();
  m_hash->SetSize(4*iSize);
}

COriented_edgeStepPtrArray::~COriented_edgeStepPtrArray()
{
  delete m_hash ;
}

void COriented_edgeStepPtrArray::SetAt( int nIndex, 
                                       COriented_edgeStep* pOriented_edgeElement )
{
  int nNewIndex = nIndex;
  m_hash->SetAt(2*nIndex+pOriented_edgeElement->m_bOrientation, (void*)nNewIndex);

  if (nNewIndex == nIndex) {
    CPtrArray::SetAt( 2*nNewIndex+pOriented_edgeElement->m_bOrientation, 
      pOriented_edgeElement);
  }
//return nIndex;
}

COriented_edgeStep* COriented_edgeStepPtrArray::GetAt(int nIndex, bool bOrientation=true)
{
  int nNewIndex = (int) m_hash->GetAt(2+nIndex+1);
  return (COriented_edgeStep*)CPtrArray::GetAt( nNewIndex);
}

HRESULT COriented_edgeStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  else {
    return E_FAIL;
  }
}

//////////////////////////////////////////////////////////
// who  date      history
// wh   11/24/01  fixed
