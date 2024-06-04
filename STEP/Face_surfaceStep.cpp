// Face_surface.cpp: implementation of the CFaceStep class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _WINDOWS
#include "stdafx.h"
#endif

#ifdef _WINDOWS 
#include "scribble.h"
#endif

#include "Face_surfaceStep.h"
#include "Face_boundStep.h"
#include "ScribVw.h"
#include "RepresentationStep.h"
#include "stepser.h"
#include "Poly_loopStep.h"// wh 10/17/01
#include "SurfaceStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CFace_surfaceStep::CFace_surfaceStep( CSurfaceStep*     pIn, 
                                      CFace_boundStep*  p_face_bound, 
                                      bool              same_sense)
: CFaceStep (pIn, p_face_bound)
{
  nameClass("FACE_SURFACE");
  m_bSame_sense = same_sense;
  m_pFace_geometry = pIn;
  p_face_bound->m_pBack = this;
  m_pFace_geometry->m_pBack=this;
}

CFace_surfaceStep::~CFace_surfaceStep()
{
  if (0) {//  REMOVEINNERLOOP
    for (int i=1; i< m_bounds.GetSize();i++) {// wh 10/17/01
      CFace_boundStep* pB = (CFace_boundStep*) m_bounds.GetAt(i);// wh 10/17/01
      CPoly_loopStep* pPoly_loopStep = dynamic_cast<CPoly_loopStep*> (pB->m_bound);// wh 10/17/01
      if (NULL != pPoly_loopStep ) {// wh 10/17/01
        for (int j=0; j < pPoly_loopStep->m_aPolygonVertices.GetSize(); j++){// wh 10/17/01
          CBaseStep* pBS = (CBaseStep*)pPoly_loopStep->m_aPolygonVertices.GetAt(j);// wh 10/17/01
          pBS->release();// wh 10/17/01
        }
      }
  //  pB->release();// wh 10/17/01
    }
  }//REMOVEINNERLOOP// wh 10/22/01
}

HRESULT CFace_surfaceStep::backPtr(CBaseStep *&prBrep)
{ 
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  return E_FAIL;
}

HRESULT CFace_surfaceStep::contains( CCartesian_pointStep*  pPoint
                                   , containment&           bContains
                                   , double &              rdParam
                                   )
{
  CDirectionStep* pFaceNormal = NULL;
  this->m_pFace_geometry->normal( NULL, pFaceNormal );
  this->contains( pPoint, bContains, pFaceNormal
     , rdParam
    );
  return S_OK;
}

bool CFace_surfaceStep::writeNtuple(stepArchive &ar, CPtrArray*pList, int iSize )
{
  try{
    int iLen = ar.GetLength()+26;

    ar << "(";
    char szNext[2] = {NULL, NULL};
    if ( iSize > 0 ) {
      for ( int i = 0; i<iSize ; i++ ) {
        CFace_boundStep* pFB = (CFace_boundStep* ) pList->GetAt(i);

        CFace_outer_boundStep* pFOB = dynamic_cast<CFace_outer_boundStep*>(pFB) ;
        if (NULL != pFOB ){
          if (pFOB->m_bOrientation){
            if (pFOB->m_bEnabled)
            pFOB->write1tuple(ar, iLen,szNext);
          }else{
#if 0//_DEBUG
            // comment it out in debug
            ar << "\n\t\t/*";
            ar << "*/\n";
#endif
          }
        } else {
          if (NULL != pFB){
            if (pFB->m_bEnabled)
            pFB->write1tuple(ar, iLen,szNext);
          }
        }

        
      }
      
      ASSERT(NULL != szNext[0]);
      if (NULL == szNext[0]){
//      ar << "$";
      }
      ar << ")";
    }
    else{
//    ar << "($)";    
    }
  }
  catch(...){
    ar << "\n/*Errors detected in CBaseStep::writeNtuple #\n";
    ar << getNum();
    ar <<   ", but continuing*/\n" ;   
    ar << ")";
  }
  return false;
}

void CFace_surfaceStep::Serialize(stepArchive &ar)
{
  try{
   if (!isSerialized()){
      setSerialized();
      
      char out[128] = "(54%) ";
      strcat(out, this->m_szTheClass);
  #if     NOTIFICATION 
      CRepresentationStep::m_pStep->m_pScribView->Notify( out);
  #endif//NOTIFICATION 

      writePre(ar);
      ar <<   "''," ;
      writeNtuple(ar, &m_bounds, m_bounds.GetSize());
      ar <<        ",#" ;
      ar << m_pFace_geometry->getNum();// face outer bound
      ar <<   "," ;
      ar << m_bSame_sense ;
      writePost(ar);

#ifdef   WRITEEULER
      CBaseStep* pBaseStep=NULL;
      backPtr( pBaseStep);
      if (NULL!=pBaseStep){
        CManifold_solid_brepStep* pManifold_solid_brepStep=(CManifold_solid_brepStep*) pBaseStep;
        pManifold_solid_brepStep->eulerCnt.m_numFaces++;
      }
#endif//WRITEEULER

      for (int i = 0; i < m_bounds.GetSize(); i++){
        CFace_boundStep* pFB = (CFace_boundStep*) m_bounds.GetAt(i);
        pFB->m_pBack = this ;
        // dont serialize CW FOB
        CFace_outer_boundStep* pFOB = dynamic_cast<CFace_outer_boundStep*>(pFB) ;
        if (NULL != pFOB ){
          if (pFOB->m_bOrientation){
            if (pFOB->m_bEnabled){
              pFOB->Serialize(ar);  
            }
          }else{
            // comment it out in debug
          }
        } else {
          if (pFB->m_bEnabled)
            pFB->Serialize(ar);
        }
      }
      m_pFace_geometry->Serialize(ar);
    }
  }
  catch(...){
    ar << "\n/*Errors detected in CFace_surfaceStep::Serialize #\n";
//  ar << getNum();
    ar <<   ", but continuing*/\n" ;    
  }

}
/*
HRESULT CFace_surfaceStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  return E_FAIL;
}
*/
void CFace_surfaceStep::fin()
{
  m_pFace_geometry->release();
  m_pFace_geometry=NULL;
  release();
}

HRESULT CFace_surfaceStep::negate(void)
{
  for (int i = 0; i < m_bounds.GetSize(); i++){
    CFace_boundStep* pFB = (CFace_boundStep*) m_bounds.GetAt(i);
    pFB->negate();
  }
  
  return m_pFace_geometry->negate();
}

HRESULT CFace_surfaceStep::validate()
{
  for (int i = 0; i < m_bounds.GetSize(); i++){
    CFace_boundStep* pFB = (CFace_boundStep*) m_bounds.GetAt(i);
    pFB->validate();
  }
  m_pFace_geometry->validate();
  return S_OK;
}

HRESULT CFace_surfaceStep::split( CrcPtrArray *pIntersectionPts, 
                                  CFace_surfaceStep*& rpFace_surfaceStep2,// returned new split face 
                                  CFace_surfaceStep *pFace_surfaceStepOnPosFeature)
{
  HRESULT hr = S_OK;
  ASSERT(pIntersectionPts->GetSize() > 1);
  if (pIntersectionPts->GetSize() > 1){
    CFace_outer_boundStep* pFOB = (CFace_outer_boundStep*) this->m_bounds.GetAt(0);
    CFace_boundStep*  p_face_bound2 = new CFace_boundStep( *pFOB );
    if (NULL != p_face_bound2 ){
      CPoly_loopStep *pNewPoly_loopStep=NULL;
      p_face_bound2->split( pIntersectionPts, pNewPoly_loopStep, pFace_surfaceStepOnPosFeature);
      rpFace_surfaceStep2 = new 
        CFace_surfaceStep( m_pFace_geometry, 
                           p_face_bound2,
                           m_bSame_sense);
      if (NULL == rpFace_surfaceStep2 ) {
        hr = E_OUTOFMEMORY;
      }
    }
    else {
      hr = E_OUTOFMEMORY;
    }
  //pFOB = (CFace_outer_boundStep*) rpFace_surfaceStep->m_bounds.GetAt( 0);
  //pFOB->m_pEdge_loopStep = pNewPoly_loopStep;
    }
  return hr;
}

// determine if the point is contained within the bounds
HRESULT CFace_surfaceStep::contains( CCartesian_pointStep*  pPt
                                   , containment&           bContains 
                                   , CDirectionStep*        pFaceUp
                                   , double &               rdParam
                                   )
{
  HRESULT hr = S_OK;
  // first do a bb check
  // then do the check against the [outer] bound
  int i = 0;
  //for (int i=0; i < m_bounds.GetSize(); i++)
  {
    CObject* pO                 = (CObject*) m_bounds.GetAt(i);
    CFace_boundStep* pFB        = dynamic_cast<CFace_boundStep*>(pO);
    CFace_outer_boundStep* pFOB = dynamic_cast<CFace_outer_boundStep*>(pFB);
    if (pFOB){
      pFOB->contains( pPt, bContains, pFaceUp 
        , rdParam
        );
      if (false 
        //bContains
        ){
    // then do a check against the inner bound
        for (int j=i+1; j < m_bounds.GetSize(); j++){
          i++;
          pO         = (CObject*) m_bounds.GetAt(j);

          pFB        = dynamic_cast<CFace_boundStep*>(pO);
          pFOB = dynamic_cast<CFace_outer_boundStep*>(pFB);
          if (NULL == pFOB) {
            return hr;
          }
          if (NULL != pFB) {
            pFB->contains( pPt, bContains, pFaceUp 
              , rdParam
              );
          }
        }
      }
    }
  }
//ASSERTMSG("finish me!", false);
  return hr;
}

HRESULT CFace_surfaceStep::convexContains( CCartesian_pointStep*  pPt, 
                                     containment&           bContains, 
                                     CDirectionStep*        pFaceNormal
                                   , double &rdParam
                                     )
{
  HRESULT hr = S_OK;
  // first do a bb check
  // then do the check against the [outer] bound
  int i = 0;
  //for (int i=0; i < m_bounds.GetSize(); i++)
  {
    CObject* pO                 = (CObject*) m_bounds.GetAt(i);
    CFace_boundStep* pFB        = dynamic_cast<CFace_boundStep*>(pO);
    CFace_outer_boundStep* pFOB = dynamic_cast<CFace_outer_boundStep*>(pFB);
    if (pFOB){
      pFOB->contains( pPt, bContains, pFaceNormal, rdParam);
      if (false 
        //bContains
        ){
    // then do a check against the inner bound
        for (int j=i+1; j < m_bounds.GetSize(); j++){
          i++;
          pO         = (CObject*) m_bounds.GetAt(j);

          pFB        = dynamic_cast<CFace_boundStep*>(pO);
          pFOB = dynamic_cast<CFace_outer_boundStep*>(pFB);
          if (NULL == pFOB) {
            return hr;
          }
          if (NULL != pFB) {
            pFB->contains( pPt, bContains, pFaceNormal 
                                , rdParam
              );
          }
        }
      }
    }
  }
//ASSERTMSG("finish me!", false);
  return hr;
}

// this code splits a face_surface
// It does this by splitting the entities (face bounds) which it references
HRESULT CFace_surfaceStep::split( CrcPtrArray *pIntersectionPts // the intersection points define the line which does the splitting
                                )
{
  HRESULT hr = S_OK;
  ASSERT(pIntersectionPts->GetSize() > 1);
  // make sure that the intersection is more than just a nick
  if (pIntersectionPts->GetSize() > 1){

    // hold onto this because list of face bounds will grow!
    int numFBs = this->m_bounds.GetSize();
//  numFBs = 1;// hard set until the code is all working// wh 02/06/02
    for (int i = 0; i < numFBs; i++){

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
                                   true 
                                  //, NULL
                                  );
      pFOB2->m_bound = new CPoly_loopStep();// wh 11/05/01

      // now we split the original fob
      hr = pFOB->split( pIntersectionPts
                        , ((CPlaneStep*)m_pFace_geometry)->m_pPosition->m_pAxis
                        , pFOB2
                        );

      if (NULL == pFOB2 ){
        hr = E_OUTOFMEMORY;// not really needed since CMemoryException will be thrown
      }
      else {
        if ( 0 < ((CPoly_loopStep*)(pFOB2->m_bound))->m_aPolygonVertices.GetSize()){
          // add the new fob to the list of face bounds for this surface 
          //   if it is behind the surface, otherwise throw it away (or negate it)
          this->m_bounds.Add( pFOB2);// this->m_bounds.InsertAt( i++, pFOB2);
          pFOB2->demote(); // wh 02/07/02
          pFB->demote(); // wh 02/07/02
//        ASSERT(pFB->m_bEnabled == true);// wh 02/06/02
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
// this code splits a face_surface
// It does this by splitting the entities (face bounds) which it references
HRESULT CFace_surfaceStep::splitAdd( CrcPtrArray *pIntersectionPts // the intersection points define the line which does the splitting
                                   )
{
  HRESULT hr = S_OK;
  ASSERT(pIntersectionPts->GetSize() > 1);
  // make sure that the intersection is more than just a nick
  if (pIntersectionPts->GetSize() > 1){

    // hold onto this because list of face bounds will grow!
    int numFBs = this->m_bounds.GetSize();
//  numFBs = 1;// hard set until the code is all working// wh 02/06/02
    for (int i = 0; i < numFBs; i++){

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
                                   true 
                               //, NULL
                                 );
      pFOB2->m_bound = new CPoly_loopStep();// wh 11/05/01

      // now we split the original fob
      hr = pFOB->splitAdd( pIntersectionPts
                        , ((CPlaneStep*)m_pFace_geometry)->m_pPosition->m_pAxis
                        , pFOB2
                        );

      if (NULL == pFOB2 ){
        hr = E_OUTOFMEMORY;// not really needed since CMemoryException will be thrown
      }
      else {
        if ( 0 < ((CPoly_loopStep*)(pFOB2->m_bound))->m_aPolygonVertices.GetSize()){
          // add the new fob to the list of face bounds for this surface 
          //   if it is behind the surface, otherwise throw it away (or negate it)
          this->m_bounds.Add( pFOB2);// this->m_bounds.InsertAt( i++, pFOB2);
          pFOB2->demote(); // wh 02/07/02
          pFB->demote(); // wh 02/07/02
          pFB->m_bEnabled = true;// wh 02/06/02
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

HRESULT CFace_surfaceStep::mod_neg_feature( CrcPtrArray* pEdgeIntersectionPoints, 
                                            int& iv, 
                                            CPoly_loopStep*  pPLoop )
{
  // check if the point is within the [outer]bound
  
  CPlaneStep* pPlaneStepOnPosFeature = dynamic_cast<CPlaneStep*>
    (this->m_pFace_geometry);
 
  CDirectionStep* pFaceNormal = pPlaneStepOnPosFeature->m_pPosition->m_pAxis;
  containment bContains = unknownContainment; 
  double dParam;
  this->contains( 
    (CCartesian_pointStep*) pEdgeIntersectionPoints->GetAt(0), 
    bContains, 
    pFaceNormal 
    , dParam
    ); 
  if ( out != bContains )
  {
    CFace_boundStep* pfbs = (CFace_boundStep* )this->m_bounds.GetAt(0);

    return pPLoop->mod_neg_feature( pEdgeIntersectionPoints, iv);
  }
  return S_OK;
}

HRESULT CFace_surfaceStep::trim( CrcPtrArray *pIntersectionPts  // edge w/ matter on LHS
                                )
{
  HRESULT hr = S_OK;
  ASSERT(pIntersectionPts->GetSize() > 1);
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
                                   true // wh 01/05/02
                                 //, NULL
                                 );
//      pFOB2->m_bEnabled = false;
      pFOB2->m_bound = new CPoly_loopStep();// wh 11/05/01

      // now we split the original fob
      hr = pFOB->trim( pIntersectionPts, 
                        ((CPlaneStep*)m_pFace_geometry)->m_pPosition->m_pAxis 
                        );

      if (NULL == pFOB2 ){
        hr = E_OUTOFMEMORY;// not really needed since CMemoryException will be thrown
      }
      else {
        if ( 0 < ((CPoly_loopStep*)(pFOB2->m_bound))->m_aPolygonVertices.GetSize()){
          // add the new fob to the list of face bounds for this surface
          this->m_bounds.Add( pFOB2);// this->m_bounds.InsertAt( i++, pFOB2);
          pFOB2->demote(); // wh 02/07/02
          pFB->demote(); // wh 02/07/02
          pFB->m_bEnabled = true;// wh 02/06/02
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

HRESULT CFace_surfaceStep::trimEdge( CrcPtrArray *pIntersectionPts  // edge w/ matter on LHS
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
      pFOB2->m_bound = new CPoly_loopStep();// wh 11/05/01

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
        if ( 0 < ((CPoly_loopStep*)(pFOB2->m_bound))->m_aPolygonVertices.GetSize()){
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

HRESULT CFace_surfaceStep::makeIslands( CPoly_loopStep*& pPoly_loopStepIntersection )
{
  CFace_outer_boundStep* pFace_boundStep = 
    (this)->GetFace_outer_bound( );
  CLoopStep* pLoopStep = pFace_boundStep->m_bound;
  CPoly_loopStep *pPoly_loopStep = dynamic_cast<CPoly_loopStep*>( pLoopStep);
  HRESULT hr = pPoly_loopStep->mergeVertex( pPoly_loopStepIntersection);

  return hr;
}

HRESULT CFace_surfaceStep::AddFB( CFace_boundStep *p_face_bound
                              , int &ri
                              )
{
  HRESULT hr = S_OK;
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
        CPoly_loopStep * pPLStepIn = dynamic_cast<CPoly_loopStep *>(p_face_bound->m_bound);
      
        boundsIntersectBounds rBoundsXbounds = unknownBoundsIntersection;
        CPoly_loopStep * pPLStepThis = dynamic_cast<CPoly_loopStep *>(pFBThis->m_bound);

        unsigned char bitContainmentO = unknownContainment;
        pPLStepThis->contains                                         
          ( &(pPLStepIn->m_aPolygonVertices)
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
          ( 
            &(pPLStepThis->m_aPolygonVertices)
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
  return hr;
}

//////////////////////////////////////////////////////////
// who  date      history
// wh   12/23/01  Advanced_face moved to its own file
// wh   01/05/02  trim
// wh   02/05/02  remove bounds which are redundent

