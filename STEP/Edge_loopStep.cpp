// Edge_loopStep.cpp: implementation of the CEdge_loopStep class.
//
//////////////////////////////////////////////////////////////////////
//#include <STDDEF.H>

#include "stdafx.h"
#include "stepArchive.h"
#include "Edge_loopStep.h"
#include "loopStep.h"
#include "PathStep.h"

#include "Oriented_EdgeStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEdge_loopStep::CEdge_loopStep(void)
               : CLoopStep(NULL)
               , m_pathStep(NULL, 0)
//             : CPathStep(NULL, 0)
//             , aLoopStep(NULL)// hack it to "has-a" realationship
{
  CLoopStep::nameClass("Edge_loop");
}

//DEL CEdge_loopStep::CEdge_loopStep( CVertex_pointStep *pVertex_pointStep0
//DEL                               , CVertex_pointStep *pVertex_pointStep1
//DEL                               , CVertex_pointStep *pVertex_pointStep2
//DEL                               , int nSize
//DEL                               )
//DEL                 : CPathStep(NULL, 0)
//DEL //              , CLoopStep(NULL)
//DEL                 , aLoopStep(NULL)// hack it to "has-a" realationship
//DEL {
//DEL   nameClass("Edge_loop");
//DEL }

CEdge_loopStep::~CEdge_loopStep()
{

}

void* CEdge_loopStep::ne()
{
  return NULL;
}

HRESULT CEdge_loopStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  else {
    return E_FAIL;
  }
}
void CEdge_loopStep::Serialize(stepArchive &ar)
{
  try{
    if (!CLoopStep::isSerialized()){
      CLoopStep::setSerialized();
      CLoopStep::writePre( ar);
      CLoopStep::writeLabel( ar);
      // slight problems in that vertices can be duplicated, 
      // if so, need to remove them as well as the edges
      CLoopStep::writeNtuple( ar, 
                              &(m_pathStep.m_aEdge_list), 
                              m_pathStep.m_aEdge_list.GetSize());
      CLoopStep::writePost( ar);

      for (int i =0; i< m_pathStep.m_aEdge_list.GetSize(); i++){
        try {
          COriented_edgeStep *pOriented_edgeStep= (COriented_edgeStep *) 
              m_pathStep.m_aEdge_list.GetAt(i);

          if (NULL != pOriented_edgeStep){
            pOriented_edgeStep->m_pBack = this ;
            pOriented_edgeStep->Serialize(ar);
          }
        }
        catch(...){
          ar << "\n/*  error caught in CEdge_loopStep::Serialize*/\n";
        }
      }
    }
  }
  catch(...){
    ar << "\n/*Errors detected in CEdge_loopStep::Serialize #\n";
    ar << CLoopStep::getNum();
    ar <<   ", but continuing*/\n" ;    
  }

  CLoopStep::setSerialized();
}

void CEdge_loopStep::fin()
{
  //m_pEdge_loopStep=NULL;
}


HRESULT CEdge_loopStep::split( CVertexStep&         rVertexStep
                             , COriented_edgeStep*  pOriented_edgeStep0)
{
  COriented_edgeStep *pOriented_edgeStepI = NULL;
  for (int i = 0; i< 
    this->m_pathStep.m_aEdge_list.GetSize()-1
    ; i++){

      pOriented_edgeStepI = 
        (COriented_edgeStep *) this->m_pathStep.m_aEdge_list.GetAt( i);
      CEdge_curveStep *pEdge_curveStepI = (CEdge_curveStep *)
        pOriented_edgeStepI->m_pEdge_element;
      CEdge_curveStep *pEdge_curveStep0 = (CEdge_curveStep *)
        pOriented_edgeStep0->m_pEdge_element;
    
      if ( &(pEdge_curveStepI->m_rEdge_geometry) == 
           &(pEdge_curveStep0->m_rEdge_geometry)){

        if ( (pEdge_curveStepI->m_pEdge_end  ) == 
             &(rVertexStep )){
          this->m_pathStep.m_aEdge_list.InsertAt( i+1, pOriented_edgeStep0);
          return S_OK;
        }
      }
    }

  this->m_pathStep.m_aEdge_list.Add( pOriented_edgeStep0);

  return S_OK;
}

//void* __cdecl operator new
//void* PASCAL CEdge_loopStep::operator new(size_t nSize, LPCSTR lpszFileName, int nLine)
/*
void* PASCAL CEdge_loopStep::operator new(unsigned int nSize, const char * lpszFileName, int nLine)
{
//return CPathStep::operator new( nSize, lpszFileName, nLine);
  return CLoopStep::operator new( nSize, lpszFileName, nLine);
//return ::operator new(nSize, _CLIENT_BLOCK, lpszFileName, nLine);
}

void PASCAL CEdge_loopStep::operator delete(void *p)
{
  CLoopStep::operator delete( p);
//CPathStep::operator delete( p);
}
*/

HRESULT CEdge_loopStep::outerloopContainment( CDirectionStep         *pFaceNormal 
                                                   , CEdge_loopStep         *pInner_boundPoints    
                                                   , boundsIntersectBounds  &rBoundsXbounds
                                                   )
{
  return E_FAIL;
}

HRESULT CEdge_loopStep::simplify()
{
  return E_FAIL;
}

int CEdge_loopStep::GetSize()
{
  return m_pathStep.m_aEdge_list.GetSize();
}


COriented_edgeStep* CEdge_loopStep::GetAt(int i)
{
  return (COriented_edgeStep*) m_pathStep.m_aEdge_list.GetAt( i);
}

void CEdge_loopStep::SetAt(int i, COriented_edgeStep *pP)
{
  m_pathStep.m_aEdge_list.SetAt( i, pP);
}


void CEdge_loopStep::RemoveAt(int nIndex, int nCount)
{
  m_pathStep.m_aEdge_list.RemoveAt( nIndex,  nCount);
}

void CEdge_loopStep::InsertAt(int nIndex, COriented_edgeStep *newElement, int nCount)
{
  m_pathStep.m_aEdge_list.InsertAt(nIndex, newElement, nCount);
}

void CEdge_loopStep::SetSize(int nNewSize, int nGrowBy)
{
  m_pathStep.m_aEdge_list.SetSize( nNewSize, nGrowBy);
}

int CEdge_loopStep::Add(COriented_edgeStep *newElement)
{
  return m_pathStep.m_aEdge_list.Add( newElement);
}

HRESULT CEdge_loopStep::contains( CCartesian_pointStep*   pIntersectionPts 
                                , unsigned char&          rBitContainment
                                , CDirectionStep*         pFaceLeft
                                )
{
/*
  double dParam;
  for ( int i = 0; 
        i < rIntersectionPts.GetSize(); 
        i++)
  {
    containment            bContains = unknownContainment;
    this->m_pathStep->contains( 
      ( CCartesian_pointStep*) intersectionPts.GetAt(i)->m_pEdge_start
      , bContains
      , pFaceLeft
      , dParam
      );
    rBitContainment |= bContains;
  }
*/
  return S_OK;
}


CEdge_loopStepEx::CEdge_loopStepEx(void)
                : CEdge_loopStep()
{
}

CEdge_loopStepEx::~CEdge_loopStepEx()
{
}

HRESULT CEdge_loopStepEx::sortIntersectionsCCW( 
                                              CrcPtrArray*      pLoopIntersectionPoints , 
                                              CPlaneStep*       pPlaneStepOnNegFeature, 
                                              CPlaneStep*       pPlaneStepOnPosFeature, 
                                              bool&             bBackward // indication that loop is backwards 
                                                                          //  because it does not agree with the previous entry 
                                                                          //  inserted into the list
                                            , const bool        bOrientation   // CFace_boundStep.m_bOrientation
                              )
{
#if 0
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
        if (0 == GetSize()){
        
          // are you sure this is the order in which these points should be added
          // all intersections have to be ordered CW, 

            this->Add( pLoopIntersectionPoints->GetAt( jPrev));
            this->Add( pLoopIntersectionPoints->GetAt( j));
        }
        else {// check the end of the list against the previous endpoint
          CVectorStep diff( *(CCartesian_pointStep*)this->GetAt(
                                                      this->GetSize()-1),  // end of list
                            *(CCartesian_pointStep*)pLoopIntersectionPoints->GetAt( jPrev));
          if (diff.getLength2() < restol2 ){

            this->Add( pLoopIntersectionPoints->GetAt( j));    // wh 10/14/01
            m_dp=make_polyloopStepExAdd;
          }
          else{// check the beginning of the list against the current endpoint
            CVectorStep dif2( *(CCartesian_pointStep*)this->GetAt( 0 ), // not pLoopIntersectionPoints// beginning of list
                              *(CCartesian_pointStep*)pLoopIntersectionPoints->GetAt( j ));

            if (dif2.getLength2() < restol2 ){
              this->InsertAt( 0, pLoopIntersectionPoints->GetAt( jPrev));
              m_dp=make_polyloopStepExInsert;
            }
            else { 
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
#endif
              if (make_polyloopStepExAdd == m_dp){

                this->Add( pLoopIntersectionPoints->GetAt( jPrev));
                this->Add( pLoopIntersectionPoints->GetAt( j));
              }
              else 
              if (make_polyloopStepExInsert == m_dp){

                this->InsertAt( 0, pLoopIntersectionPoints->GetAt( jPrev));
                this->InsertAt( 0, pLoopIntersectionPoints->GetAt( j));
              }
              else 
              {
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
        if (0 == this->GetSize()){
          this->InsertAt(0, pLoopIntersectionPoints->GetAt( jPrev));
          this->InsertAt(0, pLoopIntersectionPoints->GetAt( j));
        }
        else {// check the beginning of the list against the endpoint
            CVectorStep dif2( *(CCartesian_pointStep*)this->GetAt( 0 ), // beginning of list
                              *(CCartesian_pointStep*)pLoopIntersectionPoints->GetAt( jPrev ));

            if (dif2.getLength2() < restol2 ){

              this->InsertAt( 0, pLoopIntersectionPoints->GetAt( j));
              m_dp=make_polyloopStepExInsert;
            }
            else{// check the end of the list against the endpoint 
              CVectorStep diff( *(CCartesian_pointStep*)this->GetAt(
                this->GetSize()-1), // end of list
                                *(CCartesian_pointStep*)pLoopIntersectionPoints->GetAt( j));
              if (diff.getLength2() < restol2 ){

                this->Add( pLoopIntersectionPoints->GetAt( jPrev));
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

                this->Add( pLoopIntersectionPoints->GetAt( jPrev));
                this->Add( pLoopIntersectionPoints->GetAt( j));
              } else              
              if (make_polyloopStepExInsert == m_dp){

                this->InsertAt( 0, pLoopIntersectionPoints->GetAt( jPrev));
                this->InsertAt( 0, pLoopIntersectionPoints->GetAt( j));
              } else              
              {
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
      }  
    }// NULL == pEdgeNeg // wh 6/8/01
    else {
      // These newly added loops sometimes fall outside of the outer bounds and 
      //   because they are not connected (thought to be splits), are not weeded 
      //   out in the mergeBounds code.
#ifdef MERGE_BOUNDS_INTERSECTION
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

      this->Add( pLoopIntersectionPoints->GetAt( 0));
    }
  }

#endif
  return S_OK;
}

void CEdge_loopStepEx::move(COriented_edgeStep *pLoopIntersectionPoint)
{
#if 0
  if (m_dpPrev>restol2){
    if (make_polyloopStepExAdd == m_dp){
      if (NULL!=pLoopIntersectionPoint){
        this->Add( pLoopIntersectionPoint);
      }
    } else if(make_polyloopStepExInsert == m_dp) {

      if (NULL!=pLoopIntersectionPoint){
        this->InsertAt( 0, pLoopIntersectionPoint);
      }
    }
    else {
      if (NULL!=pLoopIntersectionPoint){

      }
    }
  }
  else if (m_dpPrev<-restol2){
    if (make_polyloopStepExAdd == m_dp){

      if (NULL!=pLoopIntersectionPoint){
        this->Add( pLoopIntersectionPoint);
      }
      
    } else if(make_polyloopStepExInsert == m_dp) {
      if (NULL!=pLoopIntersectionPoint){
        this->InsertAt(0, pLoopIntersectionPoint);
      }
    } else {
      if (NULL!=pLoopIntersectionPoint){

      }
    }

  }
  else{
    TRACE0("need to take direction into account\n");
    if (NULL!=pLoopIntersectionPoint){

    }
  }
#endif
}


t_aEdge_list& CEdge_loopStep::GetEdge_list()
{
  return this->m_pathStep.m_aEdge_list;
}

//////////////////////////////////////////////////////////
// who  date      history
// wh   03/08/01  resolved problems with multiple inheritance
// wh   12/18/01  split
// wh   03/26/02  add
//////////////////////////////////////////////////////////


void CEdge_loopStep::InsertAtPoint(int nIndex, CCartesian_pointStep *newElement, int nCount)
{
  InsertAt( nIndex, this->GetEdge_list().GetAt(nIndex) );
}

void CEdge_loopStep::AddPoint(CCartesian_pointStep *newElement)
{
//  this->GetEdge_list().GetAt(this->GetEdge_list().GetSize()-1)->m_pEdge_element->split();
}
