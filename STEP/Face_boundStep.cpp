// Face_boundStep.cpp: implementation of the Face_boundStep class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _WINDOWS
#include "stdafx.h"
#endif

#include "ScribVw.h"
#include "Face_boundStep.h"
#include "loopStep.h"
#include "Edge_loopStep.h"

#include "stepArchive.h"
#include "stepSer.h"

#include "RepresentationStep.h"
#include "Poly_loopStep.h"
#include "Cartesian_pointStep.h"
#include "Topological_representation_itemStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFace_boundStep::CFace_boundStep( CBaseStep * pFrom, 
                                  CLoopStep* pBound, 
                                  bool bOrientation
                              //, CEdge_loopStep *pEdge_loopStep
                                )
: CTopological_representation_itemStep(pFrom)
, m_bound(pBound)
, m_bOrientation(bOrientation)
, m_bEnabled(true)
{
  nameClass("FACE_BOUND");
//m_bound->m_pBack=this;
}

CFace_boundStep::~CFace_boundStep()
{
  m_bound->release();
  m_bound=NULL;// wh 02/23/01
}

HRESULT CFace_boundStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  else {
    return E_FAIL;
  }
}

void CFace_boundStep::Serialize(stepArchive &ar)
{
  bool bBoundNotNull = (NULL != m_bound);
  ASSERT( bBoundNotNull );
  try{
    if (!isSerialized()){
      setSerialized();

      char out[128] = "(56%) ";
      strcat(out, this->m_szTheClass);
#if     NOTIFICATION 
      CRepresentationStep::m_pStep->m_pScribView->Notify( out);
#endif//NOTIFICATION 

      writePre(ar);
      ar <<   "'',#" ;
      if (m_bound){
        ar << m_bound->getNum();
      }
      else {
        ar <<   "$\n" ;
      }
      ar <<   "," ;
      ar <<       m_bOrientation;
      writePost(ar);
  
#ifdef   WRITEEULER
      CBaseStep* pBaseStep=NULL;
      backPtr( pBaseStep);
      if (NULL!=pBaseStep){
        CManifold_solid_brepStep* pManifold_solid_brepStep=(CManifold_solid_brepStep*) pBaseStep;
        pManifold_solid_brepStep->eulerCnt.m_numRings++;
      }
#endif//WRITEEULER
    }
    if (m_bound){
      m_bound->Serialize(ar);
    }
  }
  catch(...){
    ar << "\n/*Errors detected in ";
    ar << "CFace_boundStep";
    ar << "::Serialize #\n";
//  ar << getNum();
    ar <<   ", but continuing*/\n" ;    
    setSerialized();
  }
  char buf[32] = "(75%) ";
  strcat (buf, m_szTheClass);
  strcat (buf, "::Serialize");
#if     NOTIFICATION 
  CRepresentationStep::m_pStep->m_pScribView->Notify(buf);
#endif//NOTIFICATION 
}

CFace_outer_boundStep::CFace_outer_boundStep( CBaseStep * pFrom, 
                                              CLoopStep* pLoopStep, 
                                              bool bOrientation
                                          //, CEdge_loopStep *pEdge_loopStep
                                            )
:  CFace_boundStep( pFrom, pLoopStep, bOrientation//, pEdge_loopStep
                  )
//,  m_pEdge_loopStep( pEdge_loopStep)
{
  nameClass("FACE_OUTER_BOUND");
//ASSERT(NULL!=pEdge_loopStep);
//if(NULL!= m_pEdge_loopStep){
//  m_pEdge_loopStep->addRef();
//}
//pLoopStep->m_pBack = this;
//pEdge_loopStep->m_pBack = this;
}

CFace_outer_boundStep::~CFace_outer_boundStep()
{
//m_pEdge_loopStep->release();//not used wh 8/23/01
}

HRESULT CFace_outer_boundStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  return E_FAIL;
}

void CFace_outer_boundStep::Serialize(stepArchive &ar)
{
  try{
    if (!isSerialized()){
      setSerialized();
      writePre(ar);
      ar <<   "'',#" ;
      if (m_bound){
        ar << m_bound->getNum();
      }else{
        ar <<   "$\n" ;
      }
      ar <<   "," ;
      ar <<       m_bOrientation;
      writePost(ar);
    }
    
    if (m_bound){
      m_bound->m_pBack=this ;
      m_bound->Serialize(ar);
    }
  }
  catch(...){
    ar << "\n/*Errors detected in CFace_outer_boundStep::Serialize #\n";
    ar <<   ", but continuing*/\n" ;    
    setSerialized();
  }
  
  char buf[64] = "(75%) ";
  strcat (buf, m_szTheClass);
  strcat (buf, "::Serialize");
#if     NOTIFICATION 
  CRepresentationStep::m_pStep->m_pScribView->Notify(buf);
#endif//NOTIFICATION 
}

void CFace_outer_boundStep::fin()
{ 
  if (NULL != m_bound) {
    if (1 == m_bound->getRefCnt()){//????
      delete m_bound;
      m_bound=NULL;
    }
    else {
      m_bound->release();
    }
  }
}

CFace_boundStep::CFace_boundStep(CFace_outer_boundStep &rFace_outer_boundStep)
: CTopological_representation_itemStep(NULL)
, m_bound(rFace_outer_boundStep.m_bound)
, m_bOrientation(rFace_outer_boundStep.m_bOrientation)
, m_bEnabled(true)
{
  m_bound->addRef();
  nameClass("FACE_BOUND");
//  ((CTopological_representation_itemStep*)this) = & ((CTopological_representation_itemStep&)rFace_outer_boundStep);
}

HRESULT CFace_boundStep::negate()
{
//CPoly_loopStep* pPoly_loopStep = dynamic_cast<CPoly_loopStep*>(m_bound);
//if (NULL != pPoly_loopStep) {
//  pPoly_loopStep->negate();
//}
  m_bound->negate();
  return S_OK;
}

HRESULT CFace_boundStep::validate()
{
//CPoly_loopStep* pPoly_loopStep = dynamic_cast<CPoly_loopStep*>(m_bound);
//if (NULL != pPoly_loopStep) {
//  pPoly_loopStep->validate();
//}
  m_bound->validate();
  return S_OK;
}

// DEPRECATE
HRESULT CFace_boundStep::split( CrcPtrArray *pIntersectionPts, 
                                CPoly_loopStep *&pNewPoly_loopStep, 
                                CFace_surfaceStep *pFace_surfaceStepOnPosFeature)
{
  m_bound->split( pIntersectionPts, pNewPoly_loopStep);
  return S_OK;
}

// for some reason, we missed the fact that you really are an outer bound
HRESULT CFace_boundStep::promote()
{
  nameClass("FACE_OUTER_BOUND");
  if (!this->m_bOrientation){
    ASSERT( false);
    m_bound->negate();
  }
  return S_OK;
}

// this algorithm only works when the polygons are convex,
// if they are concave, the algorithm has to change
HRESULT CFace_boundStep::convexContains( 
                                   CCartesian_pointStep *pPt, 
                                   containment &rszContains, 
                                   CDirectionStep* pFaceNormal
                                , double &rdParam
                                   )
{
 
  CPoly_loopStep* pPLoop = ((CPoly_loopStep*)m_bound);
  int ivm1 = pPLoop->m_aPolygonVertices.GetSize()-1;     
    for (int iv = 0; iv < pPLoop->m_aPolygonVertices.GetSize(); iv++){
      CCartesian_pointStep* pPointStep0 = dynamic_cast<CCartesian_pointStep*>((CObject* )
        (pPLoop->m_aPolygonVertices.GetAt(ivm1)));
      CCartesian_pointStep* pPointStep1 = dynamic_cast<CCartesian_pointStep*>((CObject* )
        (pPLoop->m_aPolygonVertices.GetAt(iv  )));

      // intersect this edge with the line
      if( (NULL != pPointStep0) && (NULL != pPointStep1)){
        CDirectionStep outerEdge( NULL, *pPointStep0, *pPointStep1);   
        if (!outerEdge.withinTol()) {
          CDirectionStep* pLeft = NULL; 
          if (m_bOrientation) {
            pLeft = crossProduct( *pFaceNormal , outerEdge ); 
          } else {
            pLeft = crossProduct( outerEdge , *pFaceNormal ); 
          }
          pLeft->normalize();
          if (!pLeft->withinTol()){
            containment bContains = out;
            pPLoop->convexContains (pLeft, pPt, pPointStep0, bContains 
                                 , rdParam                    
              );

            if ( out == bContains ){
              rszContains = bContains;
              delete pLeft;
              return S_OK;
            }
            // if a pt is on bdry, don't demote it to in
            if ( unknownContainment == rszContains ) {
              rszContains = bContains;
            } 
            // else if ( in == bContains) { if (in == rszContains ){ rszContains = bContains;} 
            //                              else if ( on == rszContains ) {} // dont change it
            //}
            else if ( on == bContains) {
              rszContains = bContains;
            } 

          }
          delete pLeft;
        }
        ivm1 = iv;
      }//fi
    }
  return S_OK;
}

HRESULT CFace_boundStep::contains( 
                                   CCartesian_pointStep*  pPt 
                                 , containment&           rszContains 
                                 , CDirectionStep*        pFaceUp
                                 , double&                rdParam
                                 )
{ 
  CPoly_loopStep* pPLoop = dynamic_cast<CPoly_loopStep*>(m_bound);
  if (NULL != pPLoop) {
    pPLoop->simplify();// wh 01/05/02
    int ivm1 = pPLoop->m_aPolygonVertices.GetSize()-1;     
    for (int iv = 0; iv < pPLoop->m_aPolygonVertices.GetSize(); iv++){
      CCartesian_pointStep* pPointStep0 = dynamic_cast<CCartesian_pointStep*>((CObject* )
        (pPLoop->m_aPolygonVertices.GetAt(ivm1)));
      CCartesian_pointStep* pPointStep1 = dynamic_cast<CCartesian_pointStep*>((CObject* )
        (pPLoop->m_aPolygonVertices.GetAt(iv  )));

      // intersect this edge with the line
      if( (NULL != pPointStep0) && (NULL != pPointStep1)){
        CDirectionStep outerEdge( NULL, *pPointStep0, *pPointStep1);   
        if (!outerEdge.withinTol()) {
            containment bContains = unknownContainment;// wh 12/30/01
            pPLoop->contains ( pPt, bContains, pFaceUp 
               , rdParam
              );

            if ( out == bContains ){
              rszContains = bContains;
              return S_OK;
            }
            // if a pt is on bdry, don't demote it to an inside pt
            if ( unknownContainment == rszContains ) {
              rszContains = bContains;
            } 
            if ( on == bContains) {// wh 01/25/01
              rszContains = bContains;
              return S_OK;// 01/04/02
            } 

        }
        ivm1 = iv;
      }//fi
    }
  } else {
    CEdge_loopStep* pELoop = dynamic_cast<CEdge_loopStep*>(m_bound);
    if (NULL != pELoop) {
#if 1
      pELoop->simplify();// wh 01/05/02
      int ivm1 = pELoop->GetSize()-1;     
      for (int iv = 0; iv < pELoop->GetSize(); iv++){
        COriented_edgeStep* pOriented_edgeStep = pELoop->GetAt(iv  );
        CVertex_pointStep* pVertex_pointStep0 = dynamic_cast<CVertex_pointStep*>
          (pOriented_edgeStep->GetEdge_start()) ;
        CCartesian_pointStep* pPointStep0 = dynamic_cast<CCartesian_pointStep*>
          (pVertex_pointStep0->m_p_vertex_geometry);
        
        CVertex_pointStep* pVertex_pointStep1 = dynamic_cast<CVertex_pointStep*>
          (pOriented_edgeStep->GetEdge_end()) ;
        CCartesian_pointStep* pPointStep1 = dynamic_cast<CCartesian_pointStep*>
          (pVertex_pointStep1->m_p_vertex_geometry);

        // intersect this edge with the line
        if( (NULL != pPointStep0) && (NULL != pPointStep1)){
          CEdge_curveStep *pEdge_curveStep = dynamic_cast<CEdge_curveStep*>
            (pOriented_edgeStep->m_pEdge_element);
          CLineStep *pLineStep = dynamic_cast<CLineStep*>
            (&(pEdge_curveStep->m_rEdge_geometry));
          CDirectionStep& outerEdge = *(pLineStep->m_pDir->m_pOrientation);   
          if (!outerEdge.withinTol()) {
              containment bContains = unknownContainment;
              unsigned char uContains;
              pELoop->contains ( pPt, uContains , pFaceUp 
                //, rdParam
                );

              if (out == uContains){
                rszContains = out ;
                return S_OK;
              }
              // if a pt is on bdry, don't demote it to an inside pt
              if ( on == uContains) {
                rszContains = on;
                return S_OK;
              } 
              if ( unknownContainment == rszContains ) {
                rszContains = in;
              } 

          }
          ivm1 = iv;
        }//fi
      }
    }
#endif
  }
  return S_OK;
}

HRESULT CFace_boundStep::trim( CrcPtrArray*            pIntersectionPts // list of intersection points
                             , CDirectionStep*         pAxis            // need to know which way is the surface normal
                             )           // the newly created fob
{
  HRESULT hr = S_OK;
  // be careful to take the orientation into account
  if (!m_bOrientation){
    CDirectionStep newAxis( *pAxis); 
    // point in the other direction
    newAxis.negate();

    // split the CLoopStep
    hr = m_bound->trim( pIntersectionPts
                      , &newAxis // cast the CLoopStep into a CPoly_loopStep
                      );
  }
  else{
    hr = m_bound->trim( pIntersectionPts
                      , pAxis );
  }
  return hr;

}

HRESULT CFace_boundStep::trimEdge( CrcPtrArray*            pIntersectionPts // list of intersection points
                                 , paramPtrArray&          intersectionEdge
                                 , CDirectionStep*         pAxis            // need to know which way is the surface normal
                                 , containment& bContains
                                 )           // the newly created fob
{
  HRESULT hr = S_OK;
  // be careful to take the orientation into account
  if (!m_bOrientation){
    CDirectionStep newAxis( *pAxis); 
    // point in the other direction
    newAxis.negate();

    // split the CLoopStep
    hr = m_bound->trimEdge( pIntersectionPts
                          , intersectionEdge
                          , &newAxis // cast the CLoopStep into a CPoly_loopStep
                          , bContains
                          );
  }
  else{
    hr = m_bound->trimEdge( pIntersectionPts
                          , intersectionEdge
                          , pAxis 
                          , bContains
                          );
  }
  return hr;

}

/*
// here the face bound is split, thus its underlying entity, m_bound aka CLoopStep, also needs to be split
HRESULT CFace_boundStep::split( 
                                CrcPtrArray*            pIntersectionPts, // list of intersection points
                                CDirectionStep*         pAxis,            // need to know which way is the surface normal
                                CFace_boundStep*  pFOB2 )           // the newly created fob
{
  HRESULT hr = S_OK;

  // be careful to take the orientation into account
  if (!m_bOrientation){
    CDirectionStep newAxis( *pAxis); 
    // point in the other direction
    newAxis.negate();

    // split the CLoopStep
    hr = m_bound->split( pIntersectionPts, &newAxis, 
                           dynamic_cast<CPoly_loopStep*>(pFOB2->m_bound ) // cast the CLoopStep into a CPoly_loopStep
                       );
  }
  else{
    hr = m_bound->split( pIntersectionPts, pAxis, 
                          dynamic_cast<CPoly_loopStep*>(pFOB2->m_bound ) 
      );
  }

  return hr;
}
*/
HRESULT CFace_boundStep::split//attach
                              ( CrcPtrArray*      pIntersectionPts, // list of intersection points
                                CDirectionStep*   pAxis,            // need to know which way is the surface normal
                                CFace_boundStep*  pFOB2            // the newly created fob
                               )
{
  HRESULT hr = S_OK;

  // negate fob in front of surface

  // be careful to take the orientation into account
  if (!m_bOrientation){
    CDirectionStep newAxis( *pAxis); 
    // point in the other direction
    newAxis.negate();

    // split the CLoopStep
    hr = m_bound->split( pIntersectionPts, &newAxis, 
                           dynamic_cast<CPoly_loopStep*>(pFOB2->m_bound ) // cast the CLoopStep into a CPoly_loopStep
                         , this->m_bEnabled
                         , pFOB2->m_bEnabled// wh 2/10/01
                       );
  }
  else{
    hr = m_bound->split( pIntersectionPts, pAxis, 
                          dynamic_cast<CPoly_loopStep*>(pFOB2->m_bound ) 
                        , this->m_bEnabled
                        , pFOB2->m_bEnabled// wh 2/10/01
      );
  }

  return hr;
}

HRESULT CFace_boundStep::splitAdd//attach
                              ( CrcPtrArray*      pIntersectionPts, // list of intersection points
                                CDirectionStep*   pAxis,            // need to know which way is the surface normal
                                CFace_boundStep*  pFOB2            // the newly created fob
                               )
{
  HRESULT hr = S_OK;

  // negate fob in front of surface

  // be careful to take the orientation into account
  if (!m_bOrientation){
    CDirectionStep newAxis( *pAxis); 
    // point in the other direction
    newAxis.negate();

    // split the CLoopStep
    hr = m_bound->splitAdd( pIntersectionPts
      , &newAxis, 
                           dynamic_cast<CPoly_loopStep*>(pFOB2->m_bound ) // cast the CLoopStep into a CPoly_loopStep
                         , this->m_bEnabled
                         , pFOB2->m_bEnabled// wh 2/10/02
                       );
  }
  else{
    hr = m_bound->splitAdd( pIntersectionPts
      , pAxis, 
                          dynamic_cast<CPoly_loopStep*>(pFOB2->m_bound ) 
                        , this->m_bEnabled
                        , pFOB2->m_bEnabled// wh 2/10/02
      );
  }

  return hr;
}


//////////////////////////////////////////////////////////
// who  date      history
// wh   03/15/01  try/catch in serialize
// wh   01/24/02  properly classify and discard exterior surface loops
// wh   02/05/02  remove bounds which are redundent
// wh   02/10/02  use Face_boundStep.m_bEnabled (rather than Face_boundStep.m_bOrientation) as a indicator that face has been split and discarded
