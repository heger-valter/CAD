// Edge_curveStep.cpp: implementation of the CEdge_curveStep class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _WINDOWS
#include "stdafx.h"
#endif

#include "baseStep.h"
#include "StepSer.h"
#include "ScribVw.h"
#include "RepresentationStep.h"
#include "Edge_curveStep.h"
#include "CurveStep.h"
#include "VertexStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEdge_curveStep::CEdge_curveStep( CVertexStep& rEdge_start, 
                                  CVertexStep& rEdge_end , 
                                  CCurveStep&  rEdge_geometry , 
                                  bool bSame_sense )
: CEdgeStep( NULL, rEdge_start, rEdge_end  )
, m_rEdge_geometry( rEdge_geometry)
, m_bSame_sense( bSame_sense)
{
  nameClass("Edge_curve");
  if(!bSame_sense)
  {
//    CEdgeStep::m_pEdge_start = pEdge_end   ;
//    CEdgeStep::m_pEdge_end   = pEdge_start ;
  }
}

CEdge_curveStep::~CEdge_curveStep()
{

}

void CEdge_curveStep::fin()
{
}

HRESULT CEdge_curveStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  else {
    return E_FAIL;
  }
}
void CEdge_curveStep::Serialize(stepArchive &ar)
{
  try{
    if (!isSerialized()){
      setSerialized();
      writePre(ar);
      ar << "'',#";
      if (m_bSame_sense){
        ar << m_pEdge_start->getNum();
      }
      else{
        ar << m_pEdge_end->getNum();
      }
      ar << " ,#";
      if (!m_bSame_sense){
        ar << m_pEdge_start->getNum();
      }
      else{
        ar << m_pEdge_end->getNum();
      }
      ar << ",#";
      ar << m_rEdge_geometry.getNum();
      ar << ",";
      ar << m_bSame_sense;
      writePost(ar);

      m_pEdge_start->m_pBack = this;
      m_pEdge_start->Serialize( ar);
      
      m_pEdge_end->m_pBack = this;
      m_pEdge_end->Serialize( ar);
      
      m_rEdge_geometry.m_pBack = this;
      m_rEdge_geometry.Serialize( ar);
    }
  }
  catch(...){
      setSerialized();
      ar << "\n/*Error caught in CEdge_curveStep::Serialize!*/\n";
  }

}

CPtrArray* CEdge_curveStep::m_pEdge_curveArray = NULL;
HRESULT CEdge_curveStep::split( CVertexStep&    rVertexStep // intersection vertex                              
                              , CEdge_loopStep* pEdge_loopStepCylinder
                              , CEdge_loopStep* pEdge_loopStep1// edge loop of endcap1
//                            , CEdge_curveStep*& pEdge_curveStepEndcaparc // newly split edgecurve
                              )
{
  //mev
  CEdge_curveStep *pEdge_curveStepEndcaparc = new 
    CEdge_curveStep( 
      rVertexStep, 
      *(this->m_pEdge_end), 
      this->m_rEdge_geometry, 
      this->m_bSame_sense);

  // tighten up the end to avoid overlap
  m_pEdge_end   = &rVertexStep;
  // add to list of all edge_curves
  m_pEdge_curveArray->Add( pEdge_curveStepEndcaparc);

  COriented_edgeStep *pOriented_edgeStep0 = new 
    COriented_edgeStep( pEdge_curveStepEndcaparc, false);
  pOriented_edgeStep0->m_szLabelName = "newly split cylinder";

  pEdge_loopStepCylinder->split( rVertexStep 
                               , pOriented_edgeStep0);

  // split the partner loop of the cylinder
  COriented_edgeStep *pOriented_edgeStep1 = new 
    COriented_edgeStep( pEdge_curveStepEndcaparc, true );
  pOriented_edgeStep1->m_szLabelName = "partner on far endcap";

  pEdge_loopStep1->split( rVertexStep 
                        , pOriented_edgeStep1);
//pEdge_loopStep1->m_aEdge_list.Add( pOriented_edgeStep1);
  
  return S_OK;
}

//////////////////////////////////////////////////////////
// who  date      history
// wh   11/16/01  serialize same_sense
// wh   12/16/01  split
// 

