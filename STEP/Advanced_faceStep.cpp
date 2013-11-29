// Advanced_faceStep.cpp: implementation of the CFaceStep class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "scribble.h"
#include "Advanced_faceStep.h"
#include "Face_boundStep.h"
#include "ScribVw.h"
#include "RepresentationStep.h"
#include "stepser.h"
#include "Edge_loopStep.h"// wh 10/17/01
#include "SurfaceStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAdvanced_faceStep ::CAdvanced_faceStep (CBaseStep*pIn,
                                         CFace_boundStep* p_face_bound, 
                                         bool same_sense
                                         ,int iNumFB
                                         )
: CFaceStep( pIn, p_face_bound, iNumFB)
{
  nameClass("Advanced_face");
  m_bSame_sense = same_sense;
  m_pFace_geometry = dynamic_cast< CSurfaceStep*> (pIn);
  p_face_bound->m_pBack = this;
}

CAdvanced_faceStep::~CAdvanced_faceStep ()
{

}

HRESULT CAdvanced_faceStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  else {
    return E_FAIL;
  }
}

void CAdvanced_faceStep::Serialize(stepArchive &ar)
{
  try{
   if (!isSerialized()){
      setSerialized();
      writePre(ar);
      ar <<   "'', " ;
      writeNtuple(ar, &m_bounds, m_bounds.GetSize());
      ar <<        ",#" ;
      ar << m_pFace_geometry->getNum();// face outer bound
      ar <<   ", " ;
      ar << m_bSame_sense ;
      writePost(ar);

#ifdef  WRITEEULER
      CBaseStep* pBaseStep=NULL;
      backPtr( pBaseStep);
      if (NULL!=pBaseStep){
        CManifold_solid_brepStep* pManifold_solid_brepStep=(CManifold_solid_brepStep*) pBaseStep;
        pManifold_solid_brepStep->eulerCnt.m_numFaces++;
      }
#endif//WRITEEULER

      for (int i = 0; i < m_bounds.GetSize(); i++){
        CFace_boundStep* pFB = (CFace_boundStep*) m_bounds.GetAt(i);
        ASSERT( this == pFB->m_pBack);
        pFB->Serialize(ar);
      }
      m_pFace_geometry->m_pBack = this;
      m_pFace_geometry->Serialize(ar);
    }
  }
  catch(...){
    ar << "\n/*Errors detected in CAdvanced_faceStep ::Serialize #\n";
//  ar << getNum();
    ar <<   ", but continuing*/\n" ;    
  }
}

HRESULT CAdvanced_faceStep::AddFB( CFace_boundStep *p_face_bound
                              , int &ri
                              )
{
  HRESULT hr = S_OK;
#if 0
  // before adding a ring, we must 
  //  first check if this ring is contained by another ring. 
  //  second, we must check if it contains another ring

  CPlaneStep* pPlaneStep = dynamic_cast<CPlaneStep*>
    (this->m_pFace_geometry);

  if (NULL != pPlaneStep ){
    CDirectionStep* pFaceLeft = pPlaneStep->m_pPosition->m_pRef_direction;

    for (int i = 1; i < m_bounds.GetSize(); i++){
      CFace_boundStep* pFBThis = (CFace_boundStep*) m_bounds.GetAt(i);
      if (pFBThis->m_bOrientation && pFBThis->m_bEnabled){
        CEdge_loopStep * pPLStepIn = dynamic_cast<CEdge_loopStep *>(p_face_bound->m_bound);
      
        boundsIntersectBounds rBoundsXbounds = unknownBoundsIntersection;
        CEdge_loopStep * pPLStepThis = dynamic_cast<CEdge_loopStep *>(pFBThis->m_bound);

        unsigned char bitContainmentO = unknownContainment;
        pPLStepThis->contains                                         
          ( (pPLStepIn->GetEdge_list())
          , bitContainmentO 
          , pFaceLeft
          );
        if (in == bitContainmentO ) {
          m_bounds.InsertAt( i, (CObject*)p_face_bound);
          CFace_boundStep *p_fb = (CFace_boundStep *)m_bounds.GetAt( i + 1);
//          p_fb->m_bEnabled = false;
          ri = i;
          return hr;
        }

        unsigned char bitContainmentI = unknownContainment;
        pPLStepIn->contains
          ( (pPLStepThis->GetEdge_list())
          , bitContainmentI
          , pFaceLeft
          );
        if (in == bitContainmentI) {// to really be safe
          // don't add it because it is in a hole unless there is a surrounding ring
          p_face_bound->m_bEnabled = false;
          m_bounds.InsertAt( i, (CObject*)p_face_bound);
          ri = -1;
          return hr;
        }
      }// fi m_bOrientation
    }// next i
  }
  ri = m_bounds.Add((CObject*)p_face_bound);
#endif
  return hr;
}

HRESULT CAdvanced_faceStep::trimEdge( CrcPtrArray *pIntersectionPts  // edge w/ matter on LHS
                                   , paramPtrArray& intersectionEdge  // those points of pIntersectionPts which are within bounds
                                   , containment& bContains  // is this pt contained
                                   )
{
  HRESULT hr = S_OK;
//  ASSERT(pIntersectionPts->GetSize() > 1);
  // make sure that the intersection is more than just a nick
  if (pIntersectionPts->GetSize() > 1){

    // hold onto this because list of face bounds will grow!
    int numFBs = this->m_bounds.GetSize();
//  numFBs = 1;// hard set until the code is all working
    for (int i = 0; i < numFBs; i++)
    {
      // the first FB is an FOB
      CFace_boundStep* pFB = ((CFace_boundStep*) this->m_bounds.GetAt(i));
      CFace_outer_boundStep* pFOB = dynamic_cast<CFace_outer_boundStep*> (pFB );
      if (NULL == pFOB ) {
        continue;
      }
      // create a new fob which will be the other side of the split
      CFace_outer_boundStep*  pFOB2 = 
        new CFace_outer_boundStep( NULL, 
                                   NULL,
                                   true // wh 02/07/02
                               //, NULL
                                 );
//    pFOB2->m_bEnabled = false;
      pFOB2->m_bound = new CEdge_loopStep();// wh 11/05/01

      // now we split the original fob
      hr = pFOB->trimEdge( pIntersectionPts
                         , intersectionEdge
                         , ((CPlaneStep*)m_pFace_geometry)->m_pPosition->m_pAxis 
                         , bContains
                         );

      if (NULL == pFOB2 ){
        hr = E_OUTOFMEMORY;// not really needed since CMemoryException will be thrown
      }
      else {
        if ( 0 < ((CEdge_loopStep*)(pFOB2->m_bound))->GetEdge_list().GetSize()){
          // add the new fob to the list of face bounds for this surface
          this->m_bounds.Add( pFOB2);// this->m_bounds.InsertAt( i++, pFOB2);
          pFOB2->demote(); // wh 02/07/02
          pFB->demote(); // wh 02/07/02
          ASSERT(pFB->m_bEnabled == true);// wh 02/10/02
        } else {
          // degenenate case
          // we really don't need it, so get rid of it
          pFOB2->release();
        }
      }// fi FOB
  
    }// next i
  }// fi
  return hr;
}
// determine if the point is contained within the bounds
HRESULT CAdvanced_faceStep::contains( CCartesian_pointStep*  pPoint
                                    , containment&           bContains
                                    , double&                rdParam
                                    )
{
#if 1
  CDirectionStep* pFaceNormal = NULL;
  this->m_pFace_geometry->normal( NULL, pFaceNormal );
  this->GetFace_outer_bound()->contains( pPoint, bContains, pFaceNormal
     , rdParam
    );
#endif
  return S_OK;
}

//////////////////////////////////////////////////////////
// who  date      history
// wh   12/23/01  Advanced_face moved to its own file

