// Poly_loopStep.cpp: implementation of the CPoly_loopStep class.
//
//////////////////////////////////////////////////////////////////////

#include "assert.h"  //rv
#ifdef _WINDOWS
#include "stdafx.h"
#endif

#include "afxcoll.h"
//#include "windef.h"  //max
#include "math.h"  // fabs
#include "Poly_loopStep.h"
#include "stepArchive.h"
#include "ScribVw.h"
#include "RepresentationStep.h"
#include "stepSer.h"
#include "FaceStep.h"
#include "LineStep.h"
#include "DirectionStep.h"
#include "Face_boundStep.h"
#include "Cartesian_pointStep.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPoly_loopStep::CPoly_loopStep( CPointStep*pIn0, 
                                CPointStep*pIn1, 
                                CPointStep*pIn2, 
                                int iSize)
: CLoopStep(this)
, m_bGap(false)
, m_bLinesInit(false)
{
  m_aLinesInit.SetSize(0);
  nameClass("POLY_LOOP");
  ASSERT( 2 < iSize);

  m_aPolygonVertices.SetSize( iSize, 16);
  for (int i=0; i<iSize; i++){// wh 01/23/01
    SetAt( i, NULL); 
  } 
  ASSERT(NULL != pIn0);
  ASSERT_VALID(pIn0);
  SetAt(0, pIn0);

  ASSERT(NULL != pIn1);
  ASSERT_VALID(pIn1);
  SetAt(1, pIn1);

  ASSERT(NULL != pIn2);
  ASSERT_VALID(pIn2);
  SetAt(2, pIn2);

  for ( i=iSize; i<3; i++){// wh 10/19/01
    SetAt( i, NULL); 
    ASSERT( false);
  } 
}

CPoly_loopStep::CPoly_loopStep( void)
: CLoopStep(this)
, m_bGap(false)
, m_bLinesInit(false)
{
  m_aLinesInit.SetSize(0);
  m_aPolygonVertices.SetSize( 0, 16);
  nameClass("POLY_LOOP");
}

CPoly_loopStep::~CPoly_loopStep()
{
  fin( );
}
//void// wh 10/19/01
bool CPoly_loopStep::SetAt( int i, CPointStep *pP)
{

  m_aPolygonVertices.SetAt(i, pP);
  if (NULL != pP) {
    TRACE2( "\tCPoly_loopStep.m_aPolygonVertices[ %d ] = (#%d )\n", i, pP->getNum());
#ifdef  EXPOSE      
    fprintf( g_errorLog, "\tCPoly_loopStep.m_aPolygonVertices[ %d ] = (#%d )\n"
                                                              , i , pP->getNum());
#endif//EXPOSE   
    pP->m_pBack = this;// wh 11/24/01
  }
  return false;
}

void CPoly_loopStep::Serialize(stepArchive &ar)
{
  try{
    if (!isSerialized()){
      setSerialized();
      simplify();
      int is = m_aPolygonVertices.GetSize() ;
#ifdef   WRITEEULER
      if (m_bGap){
        CBaseStep* pBaseStep=NULL;
        backPtr( pBaseStep);
        if (NULL!=pBaseStep){
          CManifold_solid_brepStep* pManifold_solid_brepStep=
            (CManifold_solid_brepStep*) pBaseStep;
          pManifold_solid_brepStep->eulerCnt.m_numGaps++;
        }
      }
#endif//WRITEEULER

      char out[128] = "(57%) ";
      strcat(out, this->m_szTheClass);
#if     NOTIFICATION 
      CRepresentationStep::m_pStep->m_pScribView->Notify( out);
#endif//NOTIFICATION 

      writePre (ar);
      ar << "'";
      ar << m_szLabelName;
      ar << "', ";

      writeNtuple(ar, (CPtrArray*)(&m_aPolygonVertices), is );
      writePost(ar);

#ifdef   WRITEEULER
      CBaseStep* pBaseStep=NULL;
      backPtr( pBaseStep);
      if (NULL!=pBaseStep){
        CManifold_solid_brepStep* pManifold_solid_brepStep=(CManifold_solid_brepStep*) pBaseStep;
        pManifold_solid_brepStep->eulerCnt.m_numHalfedges += m_aPolygonVertices.GetSize();
      }
#endif//WRITEEULER

#ifdef _DEBUG
      // checking
      CCartesian_pointStep* pVP = (CCartesian_pointStep* )m_aPolygonVertices.GetAt(is-1);
#endif// _DEBUG
      for (int i = 0; i < is; i++){
        ((CPointStep*)(m_aPolygonVertices.GetAt(i)))->m_pBack = this;
        ((CPointStep*)(m_aPolygonVertices.GetAt(i)))->Serialize( ar);

#ifdef _DEBUG
        CCartesian_pointStep* pVS = (CCartesian_pointStep* )m_aPolygonVertices.GetAt(i);
        if ((i+1) < is){
          ASSERT(!withinTol( pVS , pVP ));
          pVP = pVS;
        }
#endif// _DEBUG
      }
    }
    
  }
  catch(...){
    setSerialized();
    ar << "\n/*Errors detected in CPoly_loopStep::Serialize #\n";
//  ar << getNum();
    ar <<   ", but continuing*/\n" ;    
  }
}

// rename to polygons or GetPoint()
CPointStep* CPoly_loopStep::GetAt(int i)
{
//you should do your own modulo arithmatic here
//  i += m_aPolygonVertices.GetSize();
//  i = i%m_aPolygonVertices.GetSize();
  return (CPointStep*) m_aPolygonVertices.GetAt( i);
}

HRESULT CPoly_loopStep::negate()
{
  int numVerticies = this->m_aPolygonVertices.GetSize();
  for (int k=0; k < numVerticies/2; k++){
    CPointStep* pv0 = (CPointStep*) this->GetAt(k);
    CPointStep* pv1 = (CPointStep*) this->GetAt(numVerticies - k - 1);
    this->SetAt(numVerticies - k - 1, pv0);
    this->SetAt(k, pv1);
  }

  return S_OK;
}

// problem in Tasdraw in that some verticies are added twice, add a check for that!
HRESULT CPoly_loopStep::simplify()
{
  int numVerticies = this->m_aPolygonVertices.GetSize();

  if (numVerticies>1){ 
    int km1 = numVerticies-1;
    CCartesian_pointStep* pv0 = NULL;

    for ( ; km1 >= 0; km1--) {
      pv0 = (CCartesian_pointStep*) this->GetAt(km1 );
      if (NULL != pv0){
        ASSERT_VALID( pv0);
        break;
      }
      else {
        m_aPolygonVertices.SetSize( km1);
      }
    }

    for (int k=0; k < km1; ){
      CCartesian_pointStep* pv1 = (CCartesian_pointStep*) this->GetAt(k  );
      ASSERT_VALID( pv1);
      if ( NULL != pv0 ) {
       if ( NULL != pv1 ) {
        if ( ( pv1 == pv0 ) || 
             (withinTol( pv0, pv1))
           ){
          m_aPolygonVertices.RemoveAt(k);
          km1--;
        }
        else {
          pv0 = pv1;
          k++;
        }
       }else {
          m_aPolygonVertices.RemoveAt(k);// wh 3/08/02
          km1--;
       }
     }
    }

  }
  return S_OK;
}

// go around the loop an make sure that all the entities are valid
// check if brep represents void or antimatter
HRESULT CPoly_loopStep::validate()
{
  return S_OK;
}

// Danger, Danger, the only correct way to split a face is to do it geometrically  // wh 7/15/01
// use these two intersection points to split up the poly Loop
// note that poly loop must have the points already in its list
// DEPRECATE ME
HRESULT CPoly_loopStep::split( CrcPtrArray*         pIntersectionPts, 
                               CPoly_loopStep*&   pNewPoly_loopStep, 
                               CFace_surfaceStep* pFace_surfaceStepOnPosFeature)// find the intersection edge along this face!
{
  HRESULT hr = S_OK;
  return hr;// wh 7/15/01
  pNewPoly_loopStep = pNewPoly_loopStep = new 
    CPoly_loopStep( (CPointStep*)pIntersectionPts->GetAt(0), 
                    (CPointStep*)pIntersectionPts->GetAt(1),   //1 wh ??
                    (CPointStep*)pIntersectionPts->GetAt(0) ); //0 wh ??

  for (int i = 0; i < this->m_aPolygonVertices.GetSize(); i++){
    bool bClose0 = false;
    CCartesian_pointStep* pPoint0 = (CCartesian_pointStep*) pIntersectionPts->GetAt(1);
    CCartesian_pointStep* pPoint1 = (CCartesian_pointStep*) m_aPolygonVertices.GetAt(i);
    
    if (pIntersectionPts->GetAt(0) == this->m_aPolygonVertices.GetAt(i)){
      bClose0 = true;
    }

    else {
      if ( withinTol( pPoint0, pPoint1 )) {
        bClose0 = true;
      } 
    }

    if (bClose0){

      for (int j = i+1; j < this->m_aPolygonVertices.GetSize(); j++){
        bool bClose1 = false;
        if (pIntersectionPts->GetAt(1) == this->m_aPolygonVertices.GetAt(j)){
          bClose1 = true;
        } 

        else {
          CCartesian_pointStep* pPoint2 = (CCartesian_pointStep*) m_aPolygonVertices.GetAt(j);

          if ( withinTol( pPoint0, pPoint2)) {
            bClose1 = true;
          } 

        }

        if (bClose1){
          pNewPoly_loopStep->m_aPolygonVertices.RemoveAt(0);
          ASSERT(2 < pNewPoly_loopStep->m_aPolygonVertices.GetSize() );
          return S_OK;
        }
        pNewPoly_loopStep->m_aPolygonVertices.InsertAt( 2, this->m_aPolygonVertices.GetAt(j));
        this->m_aPolygonVertices.RemoveAt(j);
      }
      hr = E_FAIL;
      return hr;
    }
  }
  return E_FAIL;
}

// how did I get here???
// the call stack bringing us to this point is
//    CPoly_loopStep::split
//    CFace_boundStep::split
//    CFace_surfaceStep::split
//    step::faceXfaceFaceted

// here we split the loop at the intersection points, 
//  making sure that the orientation is determined by the axis
//  also make sure that you don't miss the points by restol
//  and make sure that you don't intersect a poly on the edge, making a degenerate PL2

// convex_contais algorithm only works for convex polys??
// new contains works for any 

// A poly_loop is defined as a list of cartesian_points in a polygon.
// It is split by finding all points on one side of the intersection and putting them into one poly_loop
//  and putting the verticies on the other side of the intersection into another poly_loop
HRESULT CPoly_loopStep::split( CrcPtrArray*           pIntersectionPts  // list of the intersection pts
                             , CDirectionStep*        pAxis             // need the surface normal
                             , CPoly_loopStep*        pPL2              // the newly formed complementary loop on the other side of the intersection
                             )// find the intersection edge along this face!
{
  HRESULT hr = S_OK; 
  try {
    // wrap condition
    int iPrev = m_aPolygonVertices.GetSize()-1;
    
    for (int i = 0; i < m_aPolygonVertices.GetSize(); i++){
    
      if ( m_aPolygonVertices.GetAt(i) == pIntersectionPts->GetAt(0)){
		    // i denotes the index of the first time you met the intersection point
        pPL2->m_aPolygonVertices.Add( m_aPolygonVertices.GetAt(i));
        // direction of intersection edge
        CDirectionStep cDirIntersection( NULL, 
                                  *((CCartesian_pointStep*)pIntersectionPts->GetAt(0)), 
                                  *((CCartesian_pointStep*)pIntersectionPts->GetAt(1)));
        ASSERT( cDirIntersection.getLength2() >= restol2);
        if ( cDirIntersection.getLength2() < restol2) { 
          continue;
        }
        // direction of poly
        CDirectionStep cDirPoly( NULL, 
                                 *((CCartesian_pointStep*)m_aPolygonVertices.GetAt(iPrev)), 
                                 *((CCartesian_pointStep*)m_aPolygonVertices.GetAt(i)));
        ASSERT( cDirPoly.getLength2() >= restol2);
        if (  cDirPoly.getLength2() < restol2) { 
          continue;
        }
        // the cross product edge
        CDirectionStep* pCPEdge = crossProduct( (cDirPoly), (cDirIntersection));

        // make sure its length is not less than tolerance
        pCPEdge->normalize();
        double dp = dotProduct( *(pCPEdge), *pAxis);
        // which way to traverse the list of verticies is based on the the loop direction in the plane
        if (dp < -restol2){// wh 01/24/02
          // wrap on next
          int iNext = (i+1) % (m_aPolygonVertices.GetSize());
          for (int k = iNext; k!=i; ){
            
            if (NULL != m_aPolygonVertices.GetAt( k) ){              
              if (m_aPolygonVertices.GetAt( k) != pIntersectionPts->GetAt(1)){              
                pPL2->m_aPolygonVertices.Add( m_aPolygonVertices.GetAt(k));
                m_aPolygonVertices.SetAt( k, NULL);// wh 11/13/01
              }
              else {
                break;
              }
            }
            k++;
            k= (k) % (m_aPolygonVertices.GetSize());
          }// next k
          pPL2->m_aPolygonVertices.Add( pIntersectionPts->GetAt(1));
          pCPEdge->release();
          this->simplify();// wh 2/24/01
          return hr;
        }
        else 
          if (dp > restol2){
          
          // you have to go backwards throught the loop
          int iNext = (i-1+m_aPolygonVertices.GetSize()) % (m_aPolygonVertices.GetSize());
          for (int k = iNext; k!=i; ){
            
            if ( NULL != m_aPolygonVertices.GetAt( k) ){
              if (m_aPolygonVertices.GetAt( k) != pIntersectionPts->GetAt(1)){
                pPL2->m_aPolygonVertices.InsertAt( 0, m_aPolygonVertices.GetAt(k));
                m_aPolygonVertices.SetAt(k, NULL);
              }
              else {
                break;
              }
            }
            k--;
            if(k<0){
              k += (m_aPolygonVertices.GetSize());
            }
          }// next k
          pPL2->m_aPolygonVertices.InsertAt( 0, pIntersectionPts->GetAt(1));
          pCPEdge->release();
          this->simplify();// wh 2/24/01
          return hr;
        }
        else { 
          ASSERT(false);
          pCPEdge->release();
          return E_FAIL;
        }
        pCPEdge->release();
      }// fi
      iPrev = i;
    }// next i 
  } 
  catch(...) {
    return E_FAIL;
  }
  return E_FAIL;
}

// Another problem is that this algorithm assumes convex loops!
HRESULT CPoly_loopStep::split( CrcPtrArray*           pIntersectionPts  // list of the intersection pts
                             , CDirectionStep*        pAxis             // need the surface normal
                             , CPoly_loopStep*        pPL2              // the newly formed complementary loop on the other side of the intersection
                                                                        // find the intersection edge along this face!
                             , bool &                 bFlipFob          // flag which indicates if bound is active
                             , bool &                 bFlipFob2         // flag which indicates if bound is active
                             )
{
  HRESULT hr = S_OK; 
  try {
    CDirectionStep cDirIntersection( NULL, 
                              *((CCartesian_pointStep*)pIntersectionPts->GetAt(0)), 
                              *((CCartesian_pointStep*)pIntersectionPts->GetAt(1)));

    if ( cDirIntersection.getLength2() < restol2) { 
      return S_OK;
    }
    // wrap condition
    int iPrev = m_aPolygonVertices.GetSize()-1;
    
    for (int i = 0; i < m_aPolygonVertices.GetSize(); i++){
    
      if ( m_aPolygonVertices.GetAt(i) == pIntersectionPts->GetAt(0)){
        double dp = 0.e0;
        CDirectionStep* pCPEdge = NULL;
		    // i denotes the index of the first time you met the intersection point
        pPL2->m_aPolygonVertices.Add( m_aPolygonVertices.GetAt(i));
        CTypedPtrArray<CPtrArray, CCartesian_pointStep*> ptsToBeAdded;
        do {
          // direction of intersection edge
          // direction of poly
          CDirectionStep cDirPoly( NULL, 
                                   *((CCartesian_pointStep*)m_aPolygonVertices.GetAt(iPrev)), 
                                   *((CCartesian_pointStep*)m_aPolygonVertices.GetAt(i)));
          ASSERT( cDirPoly.getLength2() >= restol2);
          if (  cDirPoly.getLength2() < restol2) { 
            continue;
          }
          if (NULL != pCPEdge) {
            pCPEdge->release();
          }
          // the cross product edge
          pCPEdge = crossProduct( (cDirPoly), (cDirIntersection));

          // make sure its length is not less than tolerance
          pCPEdge->normalize();
          dp = dotProduct( *(pCPEdge), *pAxis);

          if (fabs(dp)<restol2){
            iPrev = i;
            i++;
            ptsToBeAdded.Add( (CCartesian_pointStep*)m_aPolygonVertices.GetAt(i));

            ASSERT( i < m_aPolygonVertices.GetSize());
            if (i >= m_aPolygonVertices.GetSize()){
              return E_FAIL;
            }
          }
          else {
            break;
          }
        } while (true);

        // which way to traverse the list of verticies 
        //  is based on the loop direction in the plane
        if (dp < -restol2){// wh 01/24/02
          for (int o=0; o<ptsToBeAdded.GetSize(); o++){
            pPL2->m_aPolygonVertices.InsertAt( 0, ptsToBeAdded.GetAt(o));// wh 02/13/02
          }
          ptsToBeAdded.SetSize(0);

          // wrap on next
          int iNext = (i+1) % (m_aPolygonVertices.GetSize());
          for (int k = iNext; k!=i; ){
            
            if (NULL != m_aPolygonVertices.GetAt( k) ){              
              if (m_aPolygonVertices.GetAt( k) != pIntersectionPts->GetAt(1)){              
                pPL2->m_aPolygonVertices.InsertAt( 0, m_aPolygonVertices.GetAt(k));// wh 02/13/02
                m_aPolygonVertices.SetAt( k, NULL);// wh 11/13/01
              }
              else {
                // negate fob because it is in front of surface
                bFlipFob2 = !bFlipFob2;
                break;
              }
            }
            k++;
            k= (k) % (m_aPolygonVertices.GetSize());
          }// next k
          pPL2->m_aPolygonVertices.InsertAt( 0, pIntersectionPts->GetAt(1));// wh 02/13/02
          
          pCPEdge->release();
          this->simplify();// wh 2/24/01
          return hr;
        }
        else 
          if (dp > restol2){
            for (int o = 0; o < ptsToBeAdded.GetSize(); o++){
              pPL2->m_aPolygonVertices.Add(ptsToBeAdded.GetAt(o));
            }
          ptsToBeAdded.SetSize(0);
          // you have to go backwards throught the loop
          int iNext = (i-1+m_aPolygonVertices.GetSize()) % (m_aPolygonVertices.GetSize());
          for (int k = iNext; k!=i; ){
            
            if ( NULL != m_aPolygonVertices.GetAt( k) ){
              if (m_aPolygonVertices.GetAt( k) != pIntersectionPts->GetAt(1)){
                pPL2->m_aPolygonVertices.Add( m_aPolygonVertices.GetAt(k));// wh 02/13/02
                m_aPolygonVertices.SetAt(k, NULL);
              }
              else {

                // negate fob because it is in front of surface
                bFlipFob = !bFlipFob;

                break;
              }
            }
            k--;
            if(k<0){
              k += (m_aPolygonVertices.GetSize());
            }
          }// next k
          pPL2->m_aPolygonVertices.Add( pIntersectionPts->GetAt(1));// wh 02/13/02

          pCPEdge->release();
          this->simplify();// wh 2/24/01
          return hr;
        }
        else { 
          ASSERT(false);
          pCPEdge->release();
          return E_FAIL;
        }
        pCPEdge->release();
      }// fi
      iPrev = i;
    }// next i 
  } 
  catch(...) {
    return E_FAIL;
  }
  return E_FAIL;
}

// As opposed to the the split method
//  (which assumes that the intersection pts are in 
//  the list already, it just a matter of finding them),
//  splitAdd adds the intersection points to the list 
//  even if they are not there initially!

// Another problem is that this algorithm assumes convex loops!
HRESULT CPoly_loopStep::splitAdd( CrcPtrArray*        pIntersectionPts  // list of the intersection pts
                                , CDirectionStep*        pAxis             // need the surface normal
                                , CPoly_loopStep*        pPL2              // the newly formed complementary loop on the other side of the intersection
                                                                           // find the intersection edge along this face!
                                , bool &                 bFlipFob          // flag which indicates if bound is active
                                , bool &                 bFlipFob2         // flag which indicates if bound is active
                                )
{
  HRESULT hr = S_OK; 
  try {
    CDirectionStep cDirIntersection( NULL, 
                              *((CCartesian_pointStep*)pIntersectionPts->GetAt(0)), 
                              *((CCartesian_pointStep*)pIntersectionPts->GetAt(1)));

    if ( cDirIntersection.getLength2() < restol2) { 
      return S_OK;
    }
    // wrap condition
    int iPrev = m_aPolygonVertices.GetSize()-1;
    
    for (int i = 0; i < m_aPolygonVertices.GetSize(); i++){
      int ip1 = (i+1) % (m_aPolygonVertices.GetSize());
      CDirectionStep* pDirPoly = new CDirectionStep( NULL, 
                               *((CCartesian_pointStep*)m_aPolygonVertices.GetAt(i)), 
                               *((CCartesian_pointStep*)m_aPolygonVertices.GetAt(ip1)));
      ASSERT( pDirPoly->getLength2() >= restol2);
      if (  pDirPoly->getLength2() < restol2) { 
            pDirPoly->release();
        continue;
      }
      CVectorStep *pVecPoly = new CVectorStep( *pDirPoly);
      CLineStep* pLine  = new CLineStep
                    ( *((CCartesian_pointStep*)m_aPolygonVertices.GetAt(i)) 
                    , *pVecPoly 
                    ,  ((CCartesian_pointStep*)m_aPolygonVertices.GetAt(ip1)));

      intersectionType eIntersect0 = unknownSegmentIntersection;
      double dParam;
      pLine->contains( *((CCartesian_pointStep*)pIntersectionPts->GetAt(0)), eIntersect0 , dParam);

//    double dpPrev = 0.e0;
      
      //m_aPolygonVertices.GetAt(i) == pIntersectionPts->GetAt(0)
      if ( (startpointIntersection == eIntersect0) ||
           (interiorIntersection   == eIntersect0)  
//      || (endpointIntersection   == eIntersect0) 
         ){ 
//        ASSERT(interiorIntersection == eIntersect0);
		    // i denotes the index of the first time you met the intersection point
        CTypedPtrArray<CPtrArray, CCartesian_pointStep*> ptsToBeAdded;
        if (startpointIntersection == eIntersect0){
//        ptsToBeAdded.Add((CCartesian_pointStep*)m_aPolygonVertices.GetAt(i));
          ASSERT_VALID( (CCartesian_pointStep*)pIntersectionPts->GetAt(0));
          ptsToBeAdded.Add((CCartesian_pointStep*)pIntersectionPts->GetAt(0));
        }
        else {
          ASSERT_VALID( (CCartesian_pointStep*)m_aPolygonVertices.GetAt(i));
          ptsToBeAdded.Add((CCartesian_pointStep*)m_aPolygonVertices.GetAt(i));
          ASSERT_VALID( (CCartesian_pointStep*)pIntersectionPts->GetAt(0));
          ptsToBeAdded.Add((CCartesian_pointStep*)pIntersectionPts->GetAt(0));
        }
//      pPL2->m_aPolygonVertices.Add( pIntersectionPts->GetAt(0));// wh 2/11/02
        // direction of intersection edge
        // direction of poly
        // the cross product edge
        CDirectionStep* pCPEdge = crossProduct( (*pDirPoly), (cDirIntersection));

        // make sure its length is not less than tolerance
        pCPEdge->normalize();
        double dp = dotProduct( *(pCPEdge), *pAxis);
        while (fabs(dp) < restol2){
          i = ip1;//(i+1) % (m_aPolygonVertices.GetSize());
          ip1 = (ip1+1) % (m_aPolygonVertices.GetSize());
          CDirectionStep *pDirPolyAgain = new CDirectionStep ( NULL, 
                                   *((CCartesian_pointStep*)m_aPolygonVertices.GetAt(i)), 
                                   *((CCartesian_pointStep*)m_aPolygonVertices.GetAt(ip1)));
          ASSERT( pDirPolyAgain->getLength2() >= restol2);
          if (  pDirPolyAgain->getLength2() < restol2) { 
            pDirPolyAgain->release();
            continue;
          }
          CVectorStep* pVecPolyAgain = new CVectorStep ( *pDirPolyAgain);
          CLineStep* pLineAgain = new CLineStep
                         ( *((CCartesian_pointStep*)m_aPolygonVertices.GetAt(i)) 
                        , *pVecPolyAgain
                        ,  ((CCartesian_pointStep*)m_aPolygonVertices.GetAt(ip1)));
          pLine->release();
          pVecPoly->release();
          pDirPoly->release();

          pLine    = pLineAgain;
          pVecPoly = pVecPolyAgain;
          pDirPoly = pDirPolyAgain;
          pCPEdge->release(); 
          pCPEdge = crossProduct( (*pDirPoly), (cDirIntersection));

          // make sure its length is not less than tolerance
          pCPEdge->normalize();
          dp = dotProduct( *(pCPEdge), *pAxis);
          if (fabs(dp) < restol2) {
            ASSERT_VALID( (CCartesian_pointStep*)m_aPolygonVertices.GetAt(ip1));
            ptsToBeAdded.Add((CCartesian_pointStep*)m_aPolygonVertices.GetAt(ip1));
          }
        }
        // which way to traverse the list of verticies is based on the loop direction in the plane
        if (dp < -restol2){// wh 01/24/02
          for (int o = 0; o < ptsToBeAdded.GetSize(); o++) {
            pPL2->m_aPolygonVertices.InsertAt( 0, ptsToBeAdded.GetAt(o));// wh 02/13/02
          }
          ptsToBeAdded.SetSize(0);
          // wrap on next
          int iNext = (i+1) % (m_aPolygonVertices.GetSize());

          for (int k = iNext; k!=i; ){
            
            if (NULL != m_aPolygonVertices.GetAt( k) ){              
              int kp1 = (k+1) % (m_aPolygonVertices.GetSize());
              CDirectionStep cDirPoly2( NULL, 
                                       *((CCartesian_pointStep*)m_aPolygonVertices.GetAt(k)), 
                                       *((CCartesian_pointStep*)m_aPolygonVertices.GetAt(kp1)));
              ASSERT( cDirPoly2.getLength2() >= restol2);
              if (  cDirPoly2.getLength2() < restol2) { 
                continue;
              }
              CVectorStep vDirPoly2( *pDirPoly);
              CLineStep line2  
                            ( *((CCartesian_pointStep*)m_aPolygonVertices.GetAt(k)) 
                            , vDirPoly2
                            ,  ((CCartesian_pointStep*)m_aPolygonVertices.GetAt(kp1)));

              intersectionType eIntersect2= unknownSegmentIntersection;
              double dParam2;
              pLine->contains( *((CCartesian_pointStep*)pIntersectionPts->GetAt(1)), eIntersect2, dParam2);
              if (   (startpointIntersection == eIntersect2)                   
                 ){
                // negate fob because it is in front of surface
                bFlipFob2 = !bFlipFob2;
                break;
              }
              else if ( interiorIntersection == eIntersect2) {
//              pPL2->m_aPolygonVertices.InsertAt( 0, m_aPolygonVertices.GetAt(k));
//              m_aPolygonVertices.SetAt( k, NULL);// wh 11/13/01

                // negate fob because it is in front of surface
                bFlipFob2 = !bFlipFob2;
                break;
              } 
              else if (  endpointIntersection == eIntersect2) {
                pPL2->m_aPolygonVertices.InsertAt( 0, m_aPolygonVertices.GetAt(k));// wh 02/13/02
                m_aPolygonVertices.SetAt( k, NULL);// wh 11/13/01
                k++;// wh 02/13/02
                // negate fob because it is in front of surface
                bFlipFob2 = !bFlipFob2;
                break;
              } 
              else {
//              m_aPolygonVertices.GetAt( k) != pIntersectionPts->GetAt(1)
                pPL2->m_aPolygonVertices.InsertAt( 0, m_aPolygonVertices.GetAt(k));// wh 02/13/02
                m_aPolygonVertices.SetAt( k, NULL);// wh 11/13/01
              }
            }
            k++;
            k= (k) % (m_aPolygonVertices.GetSize());
          }// next k
          pPL2->m_aPolygonVertices.InsertAt( 0, pIntersectionPts->GetAt(1));
          
          pCPEdge->release();
          this->simplify();// wh 2/24/01
          return hr;
        }
        else 
          if (dp > restol2){
          
          for (int o = 0; o < ptsToBeAdded.GetSize(); o++) {
            pPL2->m_aPolygonVertices.Add(ptsToBeAdded.GetAt(o));// wh 02/13/02
          }
          ptsToBeAdded.SetSize(0);

          // you have to go backwards throught the loop
          int iNext = (i-1+m_aPolygonVertices.GetSize()) % (m_aPolygonVertices.GetSize());

          for (int k = iNext; k!=i; ){
            
            if ( NULL != m_aPolygonVertices.GetAt( k) ){

              int kp1 = (k-1);
              if (kp1<0){
                kp1 += (m_aPolygonVertices.GetSize());
              }
              CDirectionStep cDirPoly2( NULL, 
                                       *((CCartesian_pointStep*)m_aPolygonVertices.GetAt(k)), 
                                       *((CCartesian_pointStep*)m_aPolygonVertices.GetAt(kp1)));
              ASSERT( cDirPoly2.getLength2() >= restol2);
              if (  cDirPoly2.getLength2() < restol2) { 
                continue;
              }
              CVectorStep vDirPoly2( *pDirPoly);
              CLineStep line2  
                            ( *((CCartesian_pointStep*)m_aPolygonVertices.GetAt(k)) 
                            , vDirPoly2
                            ,  ((CCartesian_pointStep*)m_aPolygonVertices.GetAt(kp1)));

              intersectionType eIntersect2 = unknownSegmentIntersection;
              double dParam2;
              pLine->contains( *((CCartesian_pointStep*)pIntersectionPts->GetAt(1)), eIntersect2, dParam2);
              if (   (startpointIntersection == eIntersect2)                   
                 ){
                // negate fob because it is in front of surface
                bFlipFob = !bFlipFob;
                break;
              }
              else if (  interiorIntersection == eIntersect2) {
                // negate fob because it is in front of surface
//              pPL2->m_aPolygonVertices.Add( m_aPolygonVertices.GetAt(k));
//              m_aPolygonVertices.SetAt(k, NULL);

                bFlipFob = !bFlipFob;
                break;
              }
              else if (  endpointIntersection == eIntersect2) {
                // negate fob because it is in front of surface
                pPL2->m_aPolygonVertices.Add( m_aPolygonVertices.GetAt(k));// wh 02/13/02
                m_aPolygonVertices.SetAt(k, NULL);
                k--;// wh 02/13/02
//                if(k<0){
//                  k += (m_aPolygonVertices.GetSize());
//                }
                bFlipFob = !bFlipFob;
                break;
              }
              else {
              //if m_aPolygonVertices.GetAt( k) != pIntersectionPts->GetAt(1)

                pPL2->m_aPolygonVertices.Add( m_aPolygonVertices.GetAt(k));// wh 02/13/02
                m_aPolygonVertices.SetAt(k, NULL);
              }
            }
//          kPrev = k;
            k--;
            if(k<0){
              k += (m_aPolygonVertices.GetSize());
            }
          }// next k
          pPL2->m_aPolygonVertices.Add( pIntersectionPts->GetAt(1)); // wh 02/13/02

          pCPEdge->release();
          this->simplify();// wh 2/24/01
          return hr;
        }
        else { 
//        TRACE0("colinear vectors, now what\n");
          ASSERT(false);
          pCPEdge->release();
          return E_FAIL;
        }
        pCPEdge->release();
      }// fi
      iPrev = i;
      pLine->release();
      pVecPoly->release();
      pDirPoly->release();
    }// next i 
  } 
  catch(...) {
    return E_FAIL;
  }
  return E_FAIL;
}

HRESULT CPoly_loopStep::trim( CrcPtrArray*           pIntersectionPts  // list of the intersection pts
                            , CDirectionStep*        pAxis             // need the surface normal
                            )// find the intersection edge along this face!
{
  HRESULT hr = S_OK; 
  try {
    // wrap condition
    int iPrev = m_aPolygonVertices.GetSize()-1;
    
    for (int i = 0; i < m_aPolygonVertices.GetSize(); i++){
    
      if ( m_aPolygonVertices.GetAt(i) == pIntersectionPts->GetAt(0)){
		    // i denotes the index of the first time you met the intersection point
        // direction of intersection edge
        CDirectionStep cDirIntersection( NULL, 
                                  *((CCartesian_pointStep*)pIntersectionPts->GetAt(0)), 
                                  *((CCartesian_pointStep*)pIntersectionPts->GetAt(1)));
        ASSERT( cDirIntersection.getLength2() >= restol2);
        if ( cDirIntersection.getLength2() < restol2) { 
          continue;
        }
        // direction of poly
        CDirectionStep cDirPoly( NULL, 
                                 *((CCartesian_pointStep*)m_aPolygonVertices.GetAt(iPrev)), 
                                 *((CCartesian_pointStep*)m_aPolygonVertices.GetAt(i)));
        ASSERT( cDirPoly.getLength2() >= restol2);
        if (  cDirPoly.getLength2() < restol2) { 
          continue;
        }
        // the cross product edge
        CDirectionStep* pCPEdge = crossProduct( (cDirPoly), (cDirIntersection));

        // make sure its length is not less than tolerance
        pCPEdge->normalize();
        double dp = dotProduct( *(pCPEdge), *pAxis);
        // which way to traverse the list of verticies is based on the the loop direction in the plane
        if (dp < restol2){
          // wrap on next
          int iNext = (i+1) % (m_aPolygonVertices.GetSize());
          for (int k = iNext; k!=i; ){
            
            if (NULL != m_aPolygonVertices.GetAt( k) ){              
              if (m_aPolygonVertices.GetAt( k) != pIntersectionPts->GetAt(1)){              
                m_aPolygonVertices.SetAt( k, NULL);// wh 11/13/01
              }
              else {
                break;
              }
            }
            k++;
            k= (k) % (m_aPolygonVertices.GetSize());
          }// next k
          pCPEdge->release();
          return hr;
        }
        else 
          if (dp > restol2){
          
          // you have to go backwards throught the loop
          int iNext = (i-1+m_aPolygonVertices.GetSize()) % (m_aPolygonVertices.GetSize());
          for (int k = iNext; k!=i; ){
            
            if ( NULL != m_aPolygonVertices.GetAt( k) ){
              if (m_aPolygonVertices.GetAt( k) != pIntersectionPts->GetAt(1)){
                m_aPolygonVertices.SetAt(k, NULL);
              }
              else {
                break;
              }
            }
            k--;//k += m_aPolygonVertices.GetSize()-1;// k--//wh 11/06/01
            if(k<0){
              k += (m_aPolygonVertices.GetSize());
            }
          }// next k
          pCPEdge->release();
          simplify();
          return hr;
        }
        else {
          pCPEdge->release();
          return E_FAIL;
        }
        pCPEdge->release();
      }// fi
      iPrev = i;
    }// next i 
  } 
  catch(...) {
    return E_FAIL;
  }
  return E_FAIL;
}

enum derivative { none = 0, //000 111 fff
                  spike , // 010 // 0f0
                  hump  ,//011 // 0ff
                  slope ,// 01f f01
                  strange // f10
                };

// incomplete wh 7/18/01  need to be more thourough, intersecting bound case occurs more often then you think
// tbd should be a method of poly_loop
// test if each point is to the left
// calculate the distance between the outer_loop and the [inner]bound's vertex
HRESULT CPoly_loopStep::outerloopContainmentFaceted( CDirectionStep         *pFaceNormal 
                                                   , CPtrArray              *pInner_boundPoints    
                                                   , boundsIntersectBounds  &rBoundsXbounds
                                                   )
{
  int jvm1 = pInner_boundPoints->GetSize() - 1;
  char bitContainment = unknownContainment;
  containment bContainsPrev = unknownContainment;

  // intersect this edge with the line

  for (int jv = 0; jv < pInner_boundPoints->GetSize(); jv++){

    CCartesian_pointStep* pPointStep0 = dynamic_cast<CCartesian_pointStep*>((CObject*)
      (pInner_boundPoints->GetAt( jvm1)));
    CCartesian_pointStep* pPointStep1 = dynamic_cast<CCartesian_pointStep*>((CObject*)
      (pInner_boundPoints->GetAt( jv  )));

    // intersect this edge with the line
    if( (NULL != pPointStep0) && (NULL != pPointStep1)){
      CDirectionStep outerEdge( NULL, *pPointStep0, *pPointStep1);   
      CDirectionStep* pLeft = crossProduct( *pFaceNormal , outerEdge ); 
      pLeft->normalize();
      if (!pLeft->withinTol()){

        containment bContains = unknownContainment;
        double dParam = -DBL_MAX;

        this->contains( (CCartesian_pointStep* )pInner_boundPoints->GetAt(jv)
          , bContains
          , pLeft
          , dParam
          );

        bitContainment |= bContains;
        bContainsPrev = bContains;
      }

      }
      jvm1 = jv;
    }

  if (unknownContainment == bitContainment ){
    rBoundsXbounds = unknownBoundsIntersection;
  } else if (in == bitContainment ) {
    rBoundsXbounds = insideBounds;
  } else if (on == bitContainment ) {
    rBoundsXbounds = edgeScrapesInside;
  } else if (out == bitContainment ) {
    rBoundsXbounds = outsideBounds;
  } else if ((in | on) == bitContainment ) {
    rBoundsXbounds = edgeScrapesInside;
  } else if ((on | out) == bitContainment ) {
    rBoundsXbounds = edgeScrapesOutside;
  } else if ((in | out) == bitContainment ) {
    rBoundsXbounds = intersectionBounds;
  } else {
    rBoundsXbounds = intersectionBounds;
  }
  
  return S_OK;
}

HRESULT CPoly_loopStep::convexContains( CDirectionStep         *pLeft      ,
                                        CCartesian_pointStep   *pPt,    
                                        CCartesian_pointStep   *pOuterPoint, 
                                        containment            &rbContains 
                   , double &rdParam                    
                                      )
{// what about passing in orientation 
  
    CDirectionStep 
      vectorIn( NULL, 
                *pOuterPoint, 
                *pPt);
    double dp = dotProduct( *pLeft, vectorIn);
    if (dp > restol) {
      rbContains = in;
    }
    else if (dp < -restol) {
      rbContains = out;
    }
    else {
      rbContains = on;
    }
  
  return S_OK;
}


HRESULT CPoly_loopStep::trimEdge( CrcPtrArray*           pIntersectionPts  // list of the intersection pts
                                , paramPtrArray&         intersectionEdge   // those pIntersectionPts which are within bounds
                                , CDirectionStep*        pAxis             // need the surface normal
                                , containment&           bContains
                                )// find the intersection edge along this face!
{
  HRESULT hr = S_OK; 
  simplify();//wh 01/07/02

  int iPrev = this->m_aPolygonVertices.GetSize(); 
  init();
  iPrev--;

  for ( int i = 0; 
        i < this->m_aPolygonVertices.GetSize(); 
        i++)
  {
    if (NULL == this->m_aPolygonVertices.GetAt(iPrev)) {
      continue;
    }
    if (NULL == this->m_aPolygonVertices.GetAt(i)) {
      continue;
    }

    CLineStep* pLine = NULL;
    if (!m_aLinesInit.GetAt(iPrev)){
      CVectorStep *pVector = new 
        CVectorStep( *((CCartesian_pointStep*)this->m_aPolygonVertices.GetAt(iPrev)) 
                   , *((CCartesian_pointStep*)this->m_aPolygonVertices.GetAt(i)    )
                   );
      pLine = new 
        CLineStep( *((CCartesian_pointStep*)this->m_aPolygonVertices.GetAt(iPrev) )
                 , *pVector
                 ,  ((CCartesian_pointStep*)this->m_aPolygonVertices.GetAt(i) ));
      lines.SetAt( iPrev, (CObject *)pLine); 
      m_aLinesInit.SetAt(iPrev, true);
    }
    else {
      pLine = (CLineStep*) lines.GetAt(iPrev);
    }
    intersectionType  onLine0 = unknownSegmentIntersection;// wh 12/30/01
    double dParam;
    pLine->contains( *(CCartesian_pointStep*) pIntersectionPts->GetAt(0)
      , onLine0
      , dParam);

    if ( (interiorIntersection   == onLine0)    ){// 
      int p = intersectionEdge.Add(pIntersectionPts->GetAt(0) );
      double dtemp = 0.e0;
      intersectionEdge.aParam.SetAt(p, (DWORD) dtemp);
    }
    intersectionType  onLine1 = unknownSegmentIntersection;// wh 12/30/01
    pLine->contains( *(CCartesian_pointStep*) pIntersectionPts->GetAt(1)
      , onLine1
      , dParam);

    if ( (interiorIntersection   == onLine1)    ){// 
      int p = intersectionEdge.Add(pIntersectionPts->GetAt(1) );
      intersectionEdge.aParam.SetAt(p, (DWORD)DBL_MAX);
    }
    iPrev = i;
  }

  CCartesian_pointStep farAwayPt( NULL, *(CCartesian_pointStep*) pIntersectionPts->GetAt(1));//  ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipp))->py[1]
  CVectorStep farAwayVec( *(CCartesian_pointStep*) pIntersectionPts->GetAt(0)
                        , *(CCartesian_pointStep*) pIntersectionPts->GetAt(1));
  if ( farAwayVec.getLength2() < restol2){

  CLineStep veryLongHorizontalLine
    ( *(CCartesian_pointStep*) pIntersectionPts->GetAt(0)
    , farAwayVec
    , &farAwayPt);

  iPrev = this->m_aPolygonVertices.GetSize()-1;
  for ( i = 0; 
        i < this->m_aPolygonVertices.GetSize(); 
        i++)
  {
    CLineStep* pLine = (CLineStep*) lines.GetAt(iPrev);
    if (NULL == pLine ) {
      iPrev = i;
      continue;
    }

    intersectionType  eIntersect1;
    double            lamda0;
    double            lamda1; 
    intersectionType  eIntersect0;
    CPtrArray         pointXs ;
// do this in uv space instead of xyz
    pLine->intersect( veryLongHorizontalLine, 
                      eIntersect1, 
                      &pointXs ,
                      lamda0, // param on pLine
                      lamda1, 
                      eIntersect0);

    if (interiorIntersection == eIntersect0){//??
      if (interiorIntersection == eIntersect1){
        int q = intersectionEdge.Add(pointXs.GetAt(0) );
        intersectionEdge.aParam.SetAt(q, (DWORD) lamda1);
      }
    }
    iPrev = i;
  }
  } else {
//  pIntersectionPts->RemoveAt(1);
//  return E_FAIL;
  }
  return S_OK;
}

HRESULT CPoly_loopStep::contains( CrcPtrArray*    pIntersectionPts 
                                , unsigned char&           rBitContainment
                                , CDirectionStep* pFaceLeft
                                )
{
  double dParam;
  for ( int i = 0; 
        i < pIntersectionPts->GetSize(); 
        i++)
  {
    containment            bContains = unknownContainment;
    this->contains( 
      ( CCartesian_pointStep*) pIntersectionPts->GetAt(i)
      , bContains
      , pFaceLeft
      , dParam
      );
    rBitContainment |= bContains;
  }
  return S_OK;
}

HRESULT CPoly_loopStep::contains( CCartesian_pointStep*   pPt       // must be in the plane of this CPoly_loopStep!!!
                                , containment&            rbContains 
                                , CDirectionStep*         pFaceLeft
                                , double&                 rdParam
                                )
{
  double dGreatRadius2 = 1.e0;// x^2 < x for 0 < x < 1
  for ( int i = 0; 
        i < this->m_aPolygonVertices.GetSize(); 
        i++)
  {
    if (  (CCartesian_pointStep*) pPt == 
          (CCartesian_pointStep*)this->m_aPolygonVertices.GetAt(i) ){
      rbContains = on;
      return S_OK;
    } else {
      if (NULL != m_aPolygonVertices.GetAt(i) ){
        double dist2 = getLength2( (CCartesian_pointStep*) pPt
                                 , (CCartesian_pointStep*)this->m_aPolygonVertices.GetAt(i) );
        if (withinTol2( dist2)) {
          rbContains = on;
          return S_OK;
        }
        if (dGreatRadius2 < dist2) {
          dGreatRadius2 = dist2;
        }
      }
    }
  }

  int iPrev = this->m_aPolygonVertices.GetSize(); 
  init();
  iPrev--;

  for ( i = 0; 
        i < this->m_aPolygonVertices.GetSize(); 
        i++)
  {
    if (NULL == this->m_aPolygonVertices.GetAt(iPrev)) {
      ASSERT(false);
      iPrev = i;
      continue;
    }
    if (NULL == this->m_aPolygonVertices.GetAt(i    )) {
      continue;
    }

    CLineStep* pLine = NULL;
    if (!m_aLinesInit.GetAt(iPrev)){
      CVectorStep *pVector = new 
        CVectorStep( *((CCartesian_pointStep*)this->m_aPolygonVertices.GetAt(iPrev) ) 
                   , *((CCartesian_pointStep*)this->m_aPolygonVertices.GetAt(i    ) )
                   );

      pLine = new 
        CLineStep( *((CCartesian_pointStep*)this->m_aPolygonVertices.GetAt(iPrev) )
                 , *pVector
                 ,  ((CCartesian_pointStep*)this->m_aPolygonVertices.GetAt(i    ) )
                 );
      lines.SetAt( iPrev, (CObject *)pLine); 
      m_aLinesInit.SetAt(iPrev,true);
    }
    else {
      pLine = (CLineStep* ) lines.GetAt( iPrev); 
    }
    intersectionType  onLine = unknownSegmentIntersection;// wh 12/30/01
    pLine->contains( *pPt
                   , onLine 
                   , rdParam
                   );

    if ( (startpointIntersection == onLine) || // safer
         (interiorIntersection   == onLine) ||
         (endpointIntersection   == onLine)    ){// safer
//    ASSERT(interiorIntersection == onLine);
      rbContains = on;
      fin( );
      return S_OK;
    }
    iPrev = i;
  }

   halfqi( pPt                                  
         , rbContains 
         , pFaceLeft
         , dGreatRadius2
         );

  return S_OK;
}
/*
HRESULT CPoly_loopStep::qi( CCartesian_pointStep   *pPt                                  
                           , containment            &rbContains 
                           , CDirectionStep         *pFaceLeft//pFaceLeft
                           , double dGreatRadius2
                           )
{

  m_bLinesInit = true;
  int numIntersections = 0;
  CCartesian_pointStep farAwayPt( NULL, *pPt);
 
  CVectorStep farAwayVec(*pFaceLeft);
  farAwayVec.normalize();
  dGreatRadius2 += restol;
  farAwayVec *= 8.e0 * dGreatRadius2;
  farAwayPt += farAwayVec;
  CLineStep veryLongHorizontalLine( *pPt, farAwayVec, &farAwayPt);

  iPrev = this->m_aPolygonVertices.GetSize()-1; 

  for ( i = 0; 
        i < this->m_aPolygonVertices.GetSize(); 
        i++)
  {
    CLineStep* pLine = (CLineStep*) lines.GetAt(iPrev);
    if (NULL == pLine ) {
      iPrev = i;
      continue;
    }

    intersectionType  eIntersect1;
    CPtrArray         pointXs ;
    double            lamda0;
    double            lamda1; 
    intersectionType  eIntersect0;

    pLine->intersect( veryLongHorizontalLine, 
                      eIntersect1, 
                      &pointXs ,
                      lamda0, 
                      lamda1, 
                      eIntersect0);

    if (interiorIntersection == eIntersect0){
      if (interiorIntersection == eIntersect1){
        numIntersections++;
      }
    }
    iPrev = i;
  }

  if (0 == numIntersections%2){
    // outside
    rbContains = out;
  }
  else {
    rbContains = in;
  }

//fin( );

  return S_OK;
}
*/ // count the halves of quantatitive intersections of the number of encountered edges.
HRESULT CPoly_loopStep::halfqi( CCartesian_pointStep   *pPt                                  
                           , containment            &rbContains 
                           , CDirectionStep         *pFaceLeft//pFaceLeft
                           , double dGreatRadius2
                           )
{ 
  m_bLinesInit = true;
  int numFullIntersections  = 0;// endpoint intersections are counted in halves, so that both edges won't be counted twice. 
  int numStartIntersections = 0;
  int numStartIntersections0= 0;
  int numEndIntersections   = 0;
  CCartesian_pointStep farAwayPt( NULL, *pPt);
 
  CVectorStep farAwayVec(*pFaceLeft);
  farAwayVec.normalize();
  dGreatRadius2 += restol;
  farAwayVec *= 8.e0 * dGreatRadius2;
  farAwayPt += farAwayVec;
  CLineStep veryLongHorizontalLine( *pPt
                                  , farAwayVec
                                  , &farAwayPt
                                  );

  int iPrev = this->m_aPolygonVertices.GetSize()-1; 

  for (int  i = 0; 
        i < this->m_aPolygonVertices.GetSize(); 
        i++)
  {
    CLineStep* pLine = (CLineStep*) lines.GetAt(iPrev);
    if (NULL == pLine ) {
      iPrev = i;
      continue;
    }

    intersectionType  eIntersect1 = unknownSegmentIntersection;
    CPtrArray         pointXs ;
    double            lamda0;
    double            lamda1; 
    intersectionType  eIntersect0 = unknownSegmentIntersection;

    pLine->intersect( veryLongHorizontalLine, 
                      eIntersect1, 
                      &pointXs ,
                      lamda0, 
                      lamda1, 
                      eIntersect0);

    if (interiorIntersection == eIntersect1){
      if (interiorIntersection    == eIntersect0){
        numFullIntersections += 1;
        numStartIntersections = 0;
        numEndIntersections   = 0;
      } else 
      if (startpointIntersection  == eIntersect0){

        if ((0==numStartIntersections) && (1==numEndIntersections)){// wh 03/06/02
          numFullIntersections += 1;
          numStartIntersections = 0;
          numEndIntersections   = 0;
        } else if (1<numStartIntersections){
          TRACE1(" numStartIntersections= %d\n", numStartIntersections);
          numStartIntersections = 0;
          numEndIntersections   = 0;
        } else if (1<numEndIntersections){
          TRACE1(" numEndIntersections= %d\n", numEndIntersections);
          numStartIntersections = 0;
          numEndIntersections   = 0;
        } else {
          if (0 == i){
            numStartIntersections0++;
          } else {
            numStartIntersections++;
          }
        }

      } else 
      if (endpointIntersection    == eIntersect0){
        numEndIntersections++;
        if ((1==numStartIntersections) && (1==numEndIntersections)){
          numFullIntersections += 1;
          numStartIntersections = 0;
          numEndIntersections   = 0;
        } else if (1<numStartIntersections){
          TRACE1(" numStartIntersections= %d\n", numStartIntersections);
          numStartIntersections = 0;
          numEndIntersections   = 0;
        } else if (1<numEndIntersections){
          TRACE1(" numEndIntersections= %d\n", numEndIntersections);
          numStartIntersections = 0;
          numEndIntersections   = 0;
        } else if ((this->m_aPolygonVertices.GetSize()-1)==i){
          if ((1==numStartIntersections0) && (1==numEndIntersections)){
            numFullIntersections += 1;
            numStartIntersections0 = 0;
            numEndIntersections   = 0;
          }
        }
      } 
    } else if (coincidentIntersection == eIntersect1){
      rbContains = out;// on; //wh 02/04/02
      return S_OK;
    }
    else {
      ASSERT( startpointIntersection != eIntersect1 );
      ASSERT( endpointIntersection   != eIntersect1 );
      numStartIntersections = 0;
      numEndIntersections   = 0;
    }   
    iPrev = i;
  }

  ASSERT( numEndIntersections == numStartIntersections);// wh 02/12/02

  if (0 == numFullIntersections){
    // outside
    rbContains = out;
  }
  else {
    rbContains = in;
  }

//fin( );

  return S_OK;
}

HRESULT CPoly_loopStep::weed(int i){
  // see if more verticies cannot be removed
  int ip1 = i+1;
  ip1 = ip1%(this->m_aPolygonVertices.GetSize());
  int im1 = this->m_aPolygonVertices.GetSize()+ i-1;
  im1 = im1%(this->m_aPolygonVertices.GetSize());
  bool bRemoved = false;
  bool bWeeded = false;
  do {
    bRemoved = false;
    CPointStep* p0 = (CPointStep*) this->GetAt( ip1);
    CPointStep* p1 = (CPointStep*) this->GetAt( im1);
    if (p0==p1){
      this->m_aPolygonVertices.RemoveAt(ip1);

      ip1 = this->m_aPolygonVertices.GetSize()+ ip1-1;
      ip1 = ip1%(this->m_aPolygonVertices.GetSize());

      im1 = this->m_aPolygonVertices.GetSize()+ im1-1;
      im1 = im1%(this->m_aPolygonVertices.GetSize());
      bRemoved=true;
      bWeeded=true;
    }
  } while (bRemoved);
  if (bWeeded){
    this->m_aPolygonVertices.RemoveAt(i);
    ip1--;
  }
  return S_OK;
}

HRESULT CPoly_loopStep::mergeVertex( CPoly_loopStep*& pPoly_loopStep )
{
  int iCom = -1;// index of the common point on this CPoly_loopStep
  for ( int i = 0; 
        i < this->m_aPolygonVertices.GetSize(); 
        i++)
  {

    int jCom = -1;// index of the common point on pPoly_loopStep
    int jPrev = pPoly_loopStep->m_aPolygonVertices.GetSize()-1;
    for ( int j = 0;
          j < pPoly_loopStep->m_aPolygonVertices.GetSize();
          j++){
            if (  (CPointStep*) pPoly_loopStep->GetAt(j) == 
                  (CPointStep*)this->m_aPolygonVertices.GetAt(i) ){
              if (-1 == iCom){
                iCom = i;
              }
              if (-1 == jCom){
                jCom = j;
              }
              //we merge the boundary's loops
              for ( int jj = j; 
                    jj != jPrev ;
                    ) {
                this->m_aPolygonVertices.InsertAt( i, 
                  pPoly_loopStep->GetAt(jj));
                pPoly_loopStep->SetAt( jj, NULL);
                j++;
                j = j%(pPoly_loopStep->m_aPolygonVertices.GetSize());
              }
              weed(i);
              pPoly_loopStep->release();
              pPoly_loopStep = NULL;
              return S_OK;
              break;
            }
            jPrev = j;
    }
    if (-1 != iCom) {
      break;
    }  
    ASSERT(-1 == jCom);                          
  } 
  //ASSERT(-1 != iCom);

  return S_OK;
}
/*
HRESULT CPoly_loopStep::mergeEdge( CPoly_loopStep*& pPoly_loopStep )
{
  this->mergeVertex( pPoly_loopStep );
  //now remove the entire edge

//  break islands out into separate loops
  return S_OK;
}
*/

// 1. Need to trim the endpoints of N to be within the loop on P.  
// 2.  The fact that N stops on P means that it does not penetrate it!
// sort the intersections clockwise
// all outer loops on bound have to be oriented CCW
// Right now, the pPolyIntersectionPoints are added in in the order in which they are encountered, 
//  and then the loop is formed to preserve the orientation

// sort the intersections clockwise
// all loops on (CFace_boundStep.m_bOrientation==true) have to be oriented CCW
// TBD. fix this wh 11/01/01

// intersection is calculated on positive surfaces, as made by collection of negative surfaces
HRESULT CPoly_loopStepEx::sortIntersectionsCCW( 
                                              CrcPtrArray*      pLoopIntersectionPoints , 
                                              CPlaneStep*       pPlaneStepOnNegFeature, 
                                              CPlaneStep*       pPlaneStepOnPosFeature, 
                                              bool&             bBackward // indication that loop is backwards 
                                                                          //  because it does not agree with the previous entry 
                                                                          //  inserted into the list
                                            , const bool        bOrientation   // CFace_boundStep.m_bOrientation
                                            )
{
    int jPrev = 0;


    for (int j = 1; j < pLoopIntersectionPoints->GetSize(); j+=2){
      // not necessary since it is done in CPolyLoopStep.simplify

      // check if the (negFeaturesurface_normal × intersection_traversel_edge) 
      // dot posFeatureSurfaceNormal 
      //  is pos add at end, else add at front

      bool bClose = false;
      CDirectionStep * pEdgeNeg = NULL;// the edge as calculated wrt negative surface

      if ( pLoopIntersectionPoints->GetAt( jPrev ) == 
           pLoopIntersectionPoints->GetAt( j )) {
        bClose = true;
      }
      else{
        pEdgeNeg = new 
         CDirectionStep( NULL, 
           *(CCartesian_pointStep*)pLoopIntersectionPoints->GetAt( jPrev ),
           *(CCartesian_pointStep*)pLoopIntersectionPoints->GetAt( j));
        if (NULL == pEdgeNeg ) {
          return E_OUTOFMEMORY;
        }
        if (pEdgeNeg->withinTol() ) {
          bClose = true;
        }
      }

      if ((!bClose) && (NULL != pEdgeNeg)){
        CDirectionStep * pInsideNeg = // inside direction wrt the neg surface
          crossProduct( 
                        *pEdgeNeg 
                      , *pPlaneStepOnPosFeature->m_pPosition->m_pAxis
                      );
        if (NULL == pInsideNeg) {
          return E_OUTOFMEMORY;
        }
        double dp = dotProduct( *pInsideNeg
          , *pPlaneStepOnNegFeature->m_pPosition->m_pAxis);
        ASSERT_VALID(pInsideNeg); 
        delete pInsideNeg;// wh 10/6/01

        if (dp > restol2){
          // traversal neg edge point in cw direction 
          if (0 == m_aPolygonVertices.GetSize()){
          
            // are you sure this is the order in which these points should be added
            // all intersections have to be ordered CW, 
//            for ( int ix = 0; ix < ptsToBeAdded.GetSize() ; ix++) {
//              m_aPolygonVertices.Add( ptsToBeAdded.GetAt( ix));
//            }
//            ptsToBeAdded.SetSize(0);

              m_aPolygonVertices.Add( pLoopIntersectionPoints->GetAt( jPrev));
              m_aPolygonVertices.Add( pLoopIntersectionPoints->GetAt( j));
/*
              if (NULL != m_pLastMidPoint) {
                delete m_pLastMidPoint;
              }
              m_pLastMidPoint = mid( *(CCartesian_pointStep*)pLoopIntersectionPoints->GetAt( jPrev)
                                   , *(CCartesian_pointStep*)pLoopIntersectionPoints->GetAt( j    )
                                   );
*/
          }
          else {// check the end of the list against the previous endpoint
            CVectorStep diff( *(CCartesian_pointStep*)m_aPolygonVertices.GetAt(
                                                        m_aPolygonVertices.GetSize()-1),  // end of list
                              *(CCartesian_pointStep*)pLoopIntersectionPoints->GetAt( jPrev));
            if (diff.getLength2() < restol2 ){
//            for ( int ix = 0; ix < ptsToBeAdded.GetSize() ; ix++) {
//              ASSERT_VALID( (CCartesian_pointStep*)ptsToBeAdded.GetAt( ix));
//              m_aPolygonVertices.Add( ptsToBeAdded.GetAt( ix));
//            }
//            ptsToBeAdded.SetSize(0);

              m_aPolygonVertices.Add( pLoopIntersectionPoints->GetAt( j));    // wh 10/14/01
              m_dp=make_polyloopStepExAdd;
            }
            else{// check the beginning of the list against the current endpoint
              /*
              if (m_aPolygonVertices.GetSize()>2){
                CVectorStep dif3( *(CCartesian_pointStep*)m_aPolygonVertices.GetAt(
                                                            m_aPolygonVertices.GetSize()-2)   // end of list
                                , *(CCartesian_pointStep*)pLoopIntersectionPoints->GetAt( jPrev)
                                );
              }
              */
              CVectorStep dif2( *(CCartesian_pointStep*)m_aPolygonVertices.GetAt( 0 ), // not pLoopIntersectionPoints// beginning of list
                                *(CCartesian_pointStep*)pLoopIntersectionPoints->GetAt( j ));

              if (dif2.getLength2() < restol2 ){
//              for ( int ix = 0; ix < ptsToBeAdded.GetSize() ; ix++) {
//                m_aPolygonVertices.InsertAt(0, ptsToBeAdded.GetAt( ix));
//              }
//              ptsToBeAdded.SetSize(0);
                m_aPolygonVertices.InsertAt( 0, pLoopIntersectionPoints->GetAt( jPrev));
                m_dp=make_polyloopStepExInsert;
              }
              else { 
/*
              if (m_aPolygonVertices.GetSize() >2) {
                CVectorStep dif4( *(CCartesian_pointStep*)m_aPolygonVertices.GetAt( 1 )  // not pLoopIntersectionPoints// beginning of list
                                , *(CCartesian_pointStep*)pLoopIntersectionPoints->GetAt( j )
                                );
              }
*/
  #ifdef   WRITEEULER
                char buf[32] = "loop ";
                itoa(j, &buf[strlen(buf)], 10); 
                strcat(buf, " gaps, #");

                CBaseStep* pBaseStep=NULL;
                backPtr( pBaseStep);
                if (NULL!=pBaseStep){
                  CManifold_solid_brepStep* pManifold_solid_brepStep=(CManifold_solid_brepStep*) pBaseStep;
                  itoa(pManifold_solid_brepStep->eulerCnt.m_numGaps, &buf[strlen(buf)], 10); 
                }
  #endif// WRITEEULER
  #if     NOTIFICATION 
                this->GetScribView()->Notify(buf); 
  #endif//NOTIFICATION 
  #if 1
                //gap exists between two verticies in polygon_loop, problem in that the next orientation is unknown!
                TRACE0("Gap exists\n");
//              ASSERT( 0);
  #endif
                if (make_polyloopStepExAdd == m_dp){
//                for ( int ix = 0; ix < ptsToBeAdded.GetSize() ; ix++) {
//                  m_aPolygonVertices.Add( ptsToBeAdded.GetAt( ix));
//                }
//                ptsToBeAdded.SetSize(0);

                  m_aPolygonVertices.Add( pLoopIntersectionPoints->GetAt( jPrev));
                  m_aPolygonVertices.Add( pLoopIntersectionPoints->GetAt( j));
                }
                else 
                if (make_polyloopStepExInsert == m_dp){
//                for ( int ix = 0; ix < ptsToBeAdded.GetSize() ; ix++) {
//                  m_aPolygonVertices.InsertAt(0, ptsToBeAdded.GetAt( ix));
//                }
//                ptsToBeAdded.SetSize(0);

                  m_aPolygonVertices.InsertAt( 0, pLoopIntersectionPoints->GetAt( jPrev));
                  m_aPolygonVertices.InsertAt( 0, pLoopIntersectionPoints->GetAt( j));
                }
                else 
                {
//                for ( int ix = 0; ix < ptsToBeAdded.GetSize() ; ix++) {
//                  m_aPolygonVertices.Add( ptsToBeAdded.GetAt( ix));
//                }
//                ptsToBeAdded.SetSize(0);

//                ptsToBeAdded.Add( (CCartesian_pointStep*)pLoopIntersectionPoints->GetAt( jPrev));
//                ptsToBeAdded.Add( (CCartesian_pointStep*)pLoopIntersectionPoints->GetAt( j));
                }
  #ifdef   WRITEEULER
  //            pManifold_solid_brepStep->eulerCnt.m_numBackwardsLoops++;
  #endif//WRITEEULER
  //            bBackward = true;
              }
            }
          }
          m_dpPrev = dp;
        }
        else if (dp < -restol2){  // fix this to match the previous clause
        // traversal neg edge points in ccw dir
          if (0 == m_aPolygonVertices.GetSize()){
//              for ( int ix = 0; ix < ptsToBeAdded.GetSize() ; ix++) {
//                m_aPolygonVertices.InsertAt(0, ptsToBeAdded.GetAt( ix));
//              }
//              ptsToBeAdded.SetSize(0);
            // big problems all intersections have to be ordered CW
            m_aPolygonVertices.InsertAt(0, pLoopIntersectionPoints->GetAt( jPrev));
            m_aPolygonVertices.InsertAt(0, pLoopIntersectionPoints->GetAt( j));
          }
          else {// check the beginning of the list against the endpoint
              CVectorStep dif2( *(CCartesian_pointStep*)m_aPolygonVertices.GetAt( 0 ), // beginning of list
                                *(CCartesian_pointStep*)pLoopIntersectionPoints->GetAt( jPrev ));

              if (dif2.getLength2() < restol2 ){
//              for ( int ix = 0; ix < ptsToBeAdded.GetSize() ; ix++) {
//                m_aPolygonVertices.InsertAt(0, ptsToBeAdded.GetAt( ix));
//              }
//              ptsToBeAdded.SetSize(0);

                m_aPolygonVertices.InsertAt( 0, pLoopIntersectionPoints->GetAt( j));
                m_dp=make_polyloopStepExInsert;
              }
              else{// check the end of the list against the endpoint 
                CVectorStep diff( *(CCartesian_pointStep*)m_aPolygonVertices.GetAt(
                  m_aPolygonVertices.GetSize()-1), // end of list
                                  *(CCartesian_pointStep*)pLoopIntersectionPoints->GetAt( j));
                if (diff.getLength2() < restol2 ){
//                for ( int ix = 0; ix < ptsToBeAdded.GetSize() ; ix++) {
//                  m_aPolygonVertices.Add( ptsToBeAdded.GetAt( ix));
//                }
//                ptsToBeAdded.SetSize(0);

                  m_aPolygonVertices.Add( pLoopIntersectionPoints->GetAt( jPrev));
                  m_dp=make_polyloopStepExAdd;
                }
                else { 
             
    #ifdef   WRITEEULER
                  char buf[32] = "loop ";
                  itoa(j, &buf[strlen(buf)], 10); 
                  strcat(buf, " backwards, #");

                  CBaseStep* pPoly = ((CBaseStep*)pLoopIntersectionPoints->GetAt( j));
                  if (NULL!=pPoly){
                    CBaseStep* pBaseStep=NULL;
                    pPoly->backPtr( pBaseStep);

                    if (NULL!=pBaseStep){
                      CManifold_solid_brepStep* pManifold_solid_brepStep=(CManifold_solid_brepStep*) pBaseStep;
                      itoa(pManifold_solid_brepStep->eulerCnt.m_numGaps, &buf[strlen(buf)], 10); 
                    }      
                  }
    #endif//WRITEEULER
    #if     NOTIFICATION 
                  this->GetScribView()->Notify(buf); 
    #endif//NOTIFICATION 

                  // write ("gap encountered") ;//need to make a note of this in the error log//gap exists
                TRACE0("Gap exists\n");
    #if 1                            
                  ASSERT( 0);
    #endif// 0
                if (make_polyloopStepExAdd == m_dp){
//                for ( int ix = 0; ix < ptsToBeAdded.GetSize() ; ix++) {
//                  m_aPolygonVertices.Add( ptsToBeAdded.GetAt( ix));
//                }
//                ptsToBeAdded.SetSize(0);

                  m_aPolygonVertices.Add( pLoopIntersectionPoints->GetAt( jPrev));
                  m_aPolygonVertices.Add( pLoopIntersectionPoints->GetAt( j));
                } else              
                if (make_polyloopStepExInsert == m_dp){
//                for ( int ix = 0; ix < ptsToBeAdded.GetSize() ; ix++) {
//                  m_aPolygonVertices.InsertAt(0, ptsToBeAdded.GetAt( ix));
//                }
//                ptsToBeAdded.SetSize(0);

                  m_aPolygonVertices.InsertAt( 0, pLoopIntersectionPoints->GetAt( jPrev));
                  m_aPolygonVertices.InsertAt( 0, pLoopIntersectionPoints->GetAt( j));
                } else              
                {
//                for ( int ix = 0; ix < ptsToBeAdded.GetSize() ; ix++) {
//                  m_aPolygonVertices.InsertAt(0, ptsToBeAdded.GetAt( ix));
//                }
//                ptsToBeAdded.SetSize(0);

//                ptsToBeAdded.Add( (CCartesian_pointStep*)pLoopIntersectionPoints->GetAt( jPrev));
//                ptsToBeAdded.Add( (CCartesian_pointStep*)pLoopIntersectionPoints->GetAt( j));
                } 
    #ifdef   WRITEEULER
    //            pManifold_solid_brepStep->eulerCnt.m_numBackwardsLoops++;
    #endif//WRITEEULER
    //            bBackward = true;
                  }
              }
            }
          m_dpPrev = dp;
        }// if dp
        else{
  #if     NOTIFICATION 
          this->GetScribView()->Notify("colinear encountered"); // colinear
  #endif//NOTIFICATION 

          TRACE0("Gap exists\n");
          ASSERT( 0);
//        ptsToBeAdded.Add( (CCartesian_pointStep*)pLoopIntersectionPoints->GetAt( jPrev));// wh 02/25/02
//        ptsToBeAdded.Add( (CCartesian_pointStep*)pLoopIntersectionPoints->GetAt( j    ));// wh 02/25/02
        }  
      }// NULL == pEdgeNeg // wh 6/8/01
      else {
        // These newly added loops sometimes fall outside of the outer bounds and 
        //   because they are not connected (thought to be splits), are not weeded 
        //   out in the mergeBounds code.
#ifdef MERGE_BOUNDS_INTERSECTION
//        move( (CCartesian_pointStep*)pLoopIntersectionPoints->GetAt( j));// wh 03/03/02
#else
        TRACE0("throwing away pLoopIntersectionPoints[j]\n");
#endif
      }
      jPrev = j+1;
      if (pEdgeNeg){
        ASSERT_VALID( pEdgeNeg);
        delete pEdgeNeg;// wh 10/06/01
      }
    }// next j
    if (1 == pLoopIntersectionPoints->GetSize()){
      ASSERT(0);
      if (NULL != pLoopIntersectionPoints->GetAt( 0)) {
//      for ( int ix = 0; ix < ptsToBeAdded.GetSize() ; ix++) {
//        m_aPolygonVertices.Add( ptsToBeAdded.GetAt( ix));
//      }
//      ptsToBeAdded.SetSize(0);

        m_aPolygonVertices.Add( pLoopIntersectionPoints->GetAt( 0));
      }
    }
/*
  TRACE1("ptsToBeAdded.m_nSize=%d\n", ptsToBeAdded.GetSize());
  if (m_dpPrev>restol2){
    for ( int ix = 0; ix < ptsToBeAdded.GetSize() ; ix++) {
      m_aPolygonVertices.Add( ptsToBeAdded.GetAt( ix));
    }
    ptsToBeAdded.SetSize(0);
  }
  else if (m_dpPrev<-restol2){
    for ( int ix = 0; ix < ptsToBeAdded.GetSize() ; ix++) {
      m_aPolygonVertices.InsertAt(0, ptsToBeAdded.GetAt( ix));
    }
    ptsToBeAdded.SetSize(0);
  }
*/
  return S_OK;
}

HRESULT CPoly_loopStepEx::sortIntersectionsCW( 
                                              CrcPtrArray*      pLoopIntersectionPoints , 
                                              CPlaneStep*       pPlaneStepOnNegFeature, 
                                              CPlaneStep*       pPlaneStepOnPosFeature, 
                                              bool&             bBackward // indication that loop is backwards 
                                                                          //  because it does not agree with the previous entry 
                                                                          //  inserted into the list
                                            , const bool        bOrientation   // CFace_boundStep.m_bOrientation
                                            )
{
//double dpPrev = 0.0;
//CTypedPtrArray<CPtrArray, CCartesian_pointStep*> ptsToBeAdded;

    // sort the intersection point wrt start/end

    int jPrev = 0;


    for (int j = 1; j < pLoopIntersectionPoints->GetSize(); j+=2){
      // not necessary since it is done in CPolyLoopStep.simplify

      // check if the (negFeaturesurface_normal × intersection_traversel_edge) 
      // dot posFeatureSurfaceNormal 
      //  is pos add at end, else add at front

      bool bClose = false;
      CDirectionStep * pEdgeNeg = NULL;// the edge as calculated wrt negative surface

      if ( pLoopIntersectionPoints->GetAt( jPrev ) == 
           pLoopIntersectionPoints->GetAt( j )) {
        bClose = true;
      }
      else{
        pEdgeNeg = new 
         CDirectionStep( NULL, 
           *(CCartesian_pointStep*)pLoopIntersectionPoints->GetAt( jPrev ),
           *(CCartesian_pointStep*)pLoopIntersectionPoints->GetAt( j));
        if (NULL == pEdgeNeg ) {
          return E_OUTOFMEMORY;
        }
        if (pEdgeNeg->withinTol() ) {
          bClose = true;
        }
      }

      if ((!bClose) && (NULL != pEdgeNeg)){
        CDirectionStep * pInsideNeg = // inside direction wrt the neg surface
          crossProduct( *pEdgeNeg 
                      , *pPlaneStepOnPosFeature->m_pPosition->m_pAxis
                      );
        if (NULL == pInsideNeg) {
          return E_OUTOFMEMORY;
        }
        double dp = dotProduct( *pInsideNeg
                    , *pPlaneStepOnNegFeature->m_pPosition->m_pAxis);
        ASSERT_VALID(pInsideNeg); 
        delete pInsideNeg;// wh 10/6/01

        if (dp > restol2){
          // traversal neg edge point in cw direction 
          
          // are you sure this is the order in which these points should be added
          // all intersections have to be ordered CW, 
//        for ( int ix = 0; ix < ptsToBeAdded.GetSize() ; ix++) {
//          m_aPolygonVertices.Add( ptsToBeAdded.GetAt( ix));
//        }
//        ptsToBeAdded.SetSize(0);

          m_aPolygonVertices.Add( pLoopIntersectionPoints->GetAt( jPrev));
          m_aPolygonVertices.Add( pLoopIntersectionPoints->GetAt( j));
          ASSERT(m_dpPrev > -restol);
          m_dpPrev = dp;
        }
        else if (dp < -restol2){  // fix this to match the previous clause
          // traversal neg edge points in ccw dir
//        for ( int ix = 0; ix < ptsToBeAdded.GetSize() ; ix++) {
//          m_aPolygonVertices.InsertAt(0, ptsToBeAdded.GetAt( ix));
//        }
//        ptsToBeAdded.SetSize(0);

          // big problems all intersections have to be ordered CW
          m_aPolygonVertices.InsertAt(0, pLoopIntersectionPoints->GetAt( jPrev));
          m_aPolygonVertices.InsertAt(0, pLoopIntersectionPoints->GetAt( j));
          ASSERT(m_dpPrev < restol);
          m_dpPrev = dp;
        }// if dp
        else{
  #if     NOTIFICATION 
          this->GetScribView()->Notify("colinear encountered"); // colinear
  #endif//NOTIFICATION 

          ASSERT( 0);
//        ptsToBeAdded.Add( (CCartesian_pointStep*)pLoopIntersectionPoints->GetAt( jPrev));// wh 02/25/02
//        ptsToBeAdded.Add( (CCartesian_pointStep*)pLoopIntersectionPoints->GetAt( j));// wh 02/25/02
        }  
      }// NULL == pEdgeNeg // wh 6/8/01
      else { 
          if (m_dpPrev>restol2){
//          for ( int ix = 0; ix < ptsToBeAdded.GetSize() ; ix++) {
//            m_aPolygonVertices.Add( ptsToBeAdded.GetAt( ix));
//          }
//          ptsToBeAdded.SetSize(0);

            m_aPolygonVertices.Add( pLoopIntersectionPoints->GetAt( j));
          }
          else if (m_dpPrev<-restol2){
//          for ( int ix = 0; ix < ptsToBeAdded.GetSize() ; ix++) {
//            m_aPolygonVertices.InsertAt(0, ptsToBeAdded.GetAt( ix));
//          }
//          ptsToBeAdded.SetSize(0);

            m_aPolygonVertices.InsertAt(0, pLoopIntersectionPoints->GetAt( j));
          }
          else{
              TRACE0("need to take direction into account\n");
//            ptsToBeAdded.Add((CCartesian_pointStep*)pLoopIntersectionPoints->GetAt( j));
          }
      }
      jPrev = j+1;
      if (pEdgeNeg){
        ASSERT_VALID( pEdgeNeg);
        delete pEdgeNeg;// wh 10/06/01
      }
    }// next j
    if (1 == pLoopIntersectionPoints->GetSize()){
      ASSERT(0);
      if (NULL != pLoopIntersectionPoints->GetAt( 0)) {
//      for ( int ix = 0; ix < ptsToBeAdded.GetSize() ; ix++) {
//        m_aPolygonVertices.Add( ptsToBeAdded.GetAt( ix));
//      }
//      ptsToBeAdded.SetSize(0);

        m_aPolygonVertices.Add( pLoopIntersectionPoints->GetAt( 0));
      }
    }

//TRACE1("ptsToBeAdded.GetSize() %d\n", ptsToBeAdded.GetSize());
/*
  if (m_dpPrev>restol2){
    for ( int ix = 0; ix < ptsToBeAdded.GetSize() ; ix++) {
      m_aPolygonVertices.Add( ptsToBeAdded.GetAt( ix));
    }
    ptsToBeAdded.SetSize(0);
  }
  else if (m_dpPrev<-restol2){
    for ( int ix = 0; ix < ptsToBeAdded.GetSize() ; ix++) {
      m_aPolygonVertices.InsertAt(0, ptsToBeAdded.GetAt( ix));
    }
    ptsToBeAdded.SetSize(0);
  }
*/
  return S_OK;
}

HRESULT CPoly_loopStep::mod_neg_feature( CrcPtrArray* pEdgeIntersectionPoints, int& rIv)
{
  int ivm1 = rIv-1;
  ivm1 = ivm1 % (m_aPolygonVertices.GetSize());

  if (0 != rIv){ 
    if ((this->m_aPolygonVertices.GetAt(rIv  ) != pEdgeIntersectionPoints->GetAt(0)) && 
        (this->m_aPolygonVertices.GetAt(ivm1) != pEdgeIntersectionPoints->GetAt(0)) ){
      // also double check that this isn't an endpoint

      this->m_aPolygonVertices.InsertAt( rIv,(void*)pEdgeIntersectionPoints->GetAt(0));
      rIv++;
    }
  }
  else {
    if ((this->m_aPolygonVertices.GetAt(rIv  ) != pEdgeIntersectionPoints->GetAt(0)) && 
        (this->m_aPolygonVertices.GetAt(ivm1) != pEdgeIntersectionPoints->GetAt(0)) ){
      // do as above

      this->m_aPolygonVertices.Add( (void*)pEdgeIntersectionPoints->GetAt(0));
    }
  }

  return S_OK;
}

HRESULT CPoly_loopStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  return E_FAIL;
}

int CPoly_loopStep::GetSize()
{
  return m_aPolygonVertices.GetSize( );
}

HRESULT CPoly_loopStep::replace( CPoly_loopStep *pPoly_loopStepIntersection)
{
  for (int i= 0; i<this->GetSize(); i++){
    GetAt(i)->release();
  }
  this->m_aPolygonVertices.SetSize( 0);

  for ( i= 0; i<pPoly_loopStepIntersection->GetSize(); i++){
    this->m_aPolygonVertices.Add( pPoly_loopStepIntersection->GetAt(i));
  }
  pPoly_loopStepIntersection->m_aPolygonVertices.SetSize(0);// wh 02/13/02
  return S_OK;
}
/*
HRESULT CPoly_loopStep::merge( CPoly_loopStep *pPoly_loopStepIntersection)
{
  for (int j= 0; j<this->GetSize(); j++){
    for ( i= 0; i<pPoly_loopStepIntersection->GetSize(); i++){
      if (GetAt(j) == pPoly_loopStepIntersection->GetAt(i)){
        for ( k= 1; k < pPoly_loopStepIntersection->GetSize(); k++){
          int ik = (i+k) % (pPoly_loopStepIntersection->GetSize()-1);
          this->m_aPolygonVertices.InsertAt( j, pPoly_loopStepIntersection->GetAt(ik));
        }
        return S_OK;
      }
    }
  }
  return E_FAIL;
}
*/



void CPoly_loopStep::fin( 
                         )
{
  for ( int i = 0; i < lines.GetSize(); i++){
    CLineStep* pLine = (CLineStep*) lines.GetAt(i);
    if (NULL != pLine){
      ASSERT_VALID(pLine);
      ASSERT_VALID(pLine->m_pDir);
      pLine->m_pDir->release();
      pLine->release();
      lines.SetAt(i, NULL);
    }
  }
  lines.SetSize(0);

  m_aLinesInit.SetSize(0);
  m_bLinesInit = false;
}

void CPoly_loopStep::init( )
{
  int iPrev = this->m_aPolygonVertices.GetSize(); 
  if (!m_bLinesInit){
    lines.SetSize( iPrev );
    m_aLinesInit.SetSize( iPrev);
    for ( int i = 0; 
          i < iPrev ; 
          i++)
    {
      m_aLinesInit.SetAt(i,false);
    }
  }
}

CPoly_loopStepEx::CPoly_loopStepEx( void)
: CPoly_loopStep( )
, m_dpPrev(         0.0e0)
, m_dp(           make_polyloopStepExUnknown)
, m_pLastMidPoint( NULL)
{
}

CPoly_loopStepEx::~CPoly_loopStepEx()
{/*
  if (0<ptsToBeAdded.GetSize() ){
    TRACE1("ptsToBeAdded.m_nSize =%d  ", ptsToBeAdded.GetSize() );
    TRACE1("ptsToBeAdded.m_dp =%d  ", this->m_dp );
    TRACE1("ptsToBeAdded.m_dpPrev =%f\n", this->m_dpPrev );
  }*/
//ASSERT(0==ptsToBeAdded.GetSize() ); 
}

void CPoly_loopStepEx::move( CCartesian_pointStep*      pLoopIntersectionPoint)
{
  if (m_dpPrev>restol2){
    if (make_polyloopStepExAdd == m_dp){
//    for ( int ix = 0; ix < ptsToBeAdded.GetSize() ; ix++) {
//      m_aPolygonVertices.Add( ptsToBeAdded.GetAt( ix));
//    }
//    ptsToBeAdded.SetSize(0);
      if (NULL!=pLoopIntersectionPoint){
        m_aPolygonVertices.Add( pLoopIntersectionPoint);
      }
    } else if(make_polyloopStepExInsert == m_dp) {
//    for ( int ix = 0; ix < ptsToBeAdded.GetSize() ; ix++) {
//      m_aPolygonVertices.InsertAt(0, ptsToBeAdded.GetAt( ix));
//    }
//    ptsToBeAdded.SetSize(0);
      if (NULL!=pLoopIntersectionPoint){
        m_aPolygonVertices.InsertAt( 0, pLoopIntersectionPoint);
      }
    }
    else {
      if (NULL!=pLoopIntersectionPoint){
//      ptsToBeAdded.Add(pLoopIntersectionPoint);
      }
    }
  }
  else if (m_dpPrev<-restol2){
    if (make_polyloopStepExAdd == m_dp){
//    for ( int ix = 0; ix < ptsToBeAdded.GetSize() ; ) {
//      m_aPolygonVertices.Add( ptsToBeAdded.GetAt( ix+1));
//      m_aPolygonVertices.Add( ptsToBeAdded.GetAt( ix));
//      ix+=2;
//    }
//    ptsToBeAdded.SetSize(0);
      if (NULL!=pLoopIntersectionPoint){
        m_aPolygonVertices.Add( pLoopIntersectionPoint);
      }
      
    } else if(make_polyloopStepExInsert == m_dp) {
//    for ( int ix = 0; ix < ptsToBeAdded.GetSize() ; ) {
//      m_aPolygonVertices.InsertAt(0, ptsToBeAdded.GetAt( ix+1));
//      m_aPolygonVertices.InsertAt(0, ptsToBeAdded.GetAt( ix));
//      ix+=2;
//    }
//    ptsToBeAdded.SetSize(0);
      if (NULL!=pLoopIntersectionPoint){
        m_aPolygonVertices.InsertAt(0, pLoopIntersectionPoint);
      }
    } else {
      if (NULL!=pLoopIntersectionPoint){
//      ptsToBeAdded.Add(pLoopIntersectionPoint);
      }
    }

  }
  else{
//  if (NULL != pLoopIntersectionPoints->GetAt( j)) {
//    ASSERT(0);
    TRACE0("need to take direction into account\n");
    if (NULL!=pLoopIntersectionPoint){
//    ptsToBeAdded.Add( pLoopIntersectionPoint);
    }
//  }
  }
}

void CPoly_loopStepEx::movePrev( CCartesian_pointStep*      pLoopIntersectionPoint)
{
  if (m_dpPrev>restol2){
//  for ( int ix = 0; ix < ptsToBeAdded.GetSize() ; ix++) {
//    m_aPolygonVertices.Add( ptsToBeAdded.GetAt( ix));
//  }
//  ptsToBeAdded.SetSize(0);

    if (NULL!=pLoopIntersectionPoint){
      m_aPolygonVertices.Add( pLoopIntersectionPoint-1);
      m_aPolygonVertices.Add( pLoopIntersectionPoint);
    }
  }
  else if (m_dpPrev<-restol2){
//  for ( int ix = 0; ix < ptsToBeAdded.GetSize() ; ix++) {
//    m_aPolygonVertices.InsertAt(0, ptsToBeAdded.GetAt( ix));
//  }
//  ptsToBeAdded.SetSize(0);

    if (NULL!=pLoopIntersectionPoint){
      m_aPolygonVertices.InsertAt(0, pLoopIntersectionPoint-1);
      m_aPolygonVertices.InsertAt(0, pLoopIntersectionPoint);
    }
  }
  else{
//  if (NULL != pLoopIntersectionPoints->GetAt( j)) {
//    ASSERT(0);

      TRACE0("need to take direction into account\n");
//    if (NULL!=pLoopIntersectionPoint){
//      ptsToBeAdded.Add( pLoopIntersectionPoint);
//    }

//  }
  }
}

int CPoly_loopStep::Find(CCartesian_pointStep *pP)
{
  for (int i=0; i<m_aPolygonVertices.GetSize();i++){
    if (m_aPolygonVertices.GetAt(i) == pP){
      return i;
    }
  }
  return INT_MAX;
}

//////////////////////////////////////////////////////////
// who  date      history
//-----------------------
// wh   11/01/01  CPoly_loopStep::split needs the intersection points 
// wh   11/01/01  CPoly_loopStep::split error in orientation 
// wh   12/23/01  replace
// wh   01/24/02  properly classify and discard exterior surface loops
// wh   01/27/02  remove multiple redundent pts on loops
// wh   01/28/02  break islands out into separate loops
// wh   02/05/02  remove bounds which are redundent
// wh   02/13/02  if using CFace_boundStep.m_Enabled instead of CFace_boundStep.m_bOrientation then make sure that loops are oriented in proper direction
// wh   02/15/02  fixed sortIntersectionsCCW so that face-surface_neg is correctly extracted

