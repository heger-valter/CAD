// LineStep.cpp: implementation of the CLineStep class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _WINDOWS
#include "stdafx.h"
#endif

#include "baseStep.h"
#ifdef _WINDOWS 
#include "scribble.h"
#endif

#include "LineStep.h"
#include "PointStep.h"
#include "Cartesian_pointStep.h"
#include "stepArchive.h"
#include "VectorStep.h"
#include "matrix2x2.h"
#include "transformationMatrix.h"
#include "math.h" 
#include <float.h>//dbl_MAX 
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CLineStep::CLineStep( CCartesian_pointStep& rPos, 
                      CVectorStep& rDir, 
                      CCartesian_pointStep* pPos1)
  : CCurveStep( )
  , m_pPos( &rPos)
  , m_pDir( &rDir)
//, CCartesian_pointStep( this, NULL)
  , m_pPos1( pPos1)
{
  nameClass("Line");
  /*
  m_pPos->addRef();
  m_pDir->addRef();
  if ( NULL != m_pPos1) {
    m_pPos1->addRef();
    }
  */
}

#if 0
CLineStep::CLineStep( CCartesian_pointStep& rPos0, 
                      CCartesian_pointStep& rPos1)
  : CCurveStep( )
  , *m_pPos( rPos0)
  , *m_pDir( NULL )
{
  nameClass("Line");
  memset( *m_pDir ,  (*( new CVectorStep((CCartesian_pointStep)rPos1, (CCartesian_pointStep)rPos0))), 4);
}

#endif
CLineStep::~CLineStep()
{
  ASSERT_VALID(this);
/*if (NULL != m_pPos1) {    
    m_pPos->release();  
  }
  m_pDir->release();
  m_pPos->release();
  */
}

CLineStep* CLineStepPtrArray::GetAt(int  nIndex)
{
  int nNewIndex = (int)m_hash.GetAt(nIndex);
  return (CLineStep*)CPtrArray::GetAt( nNewIndex);
}


void CLineStep::Serialize(stepArchive &ar)
{
  try{
    if (!isSerialized()){
      setSerialized();
      writePre(ar);
      ar << "'',#";
      ar << m_pPos->getNum();
      ar << ",#";
      ar << m_pDir->getNum();
      writePost(ar);

      m_pPos->Serialize( ar);
      m_pDir->Serialize( ar);
    }
  }
  catch(...){
      setSerialized();
      ar << "\n/*Error caught in CCurveStep::Serialize!*/\n";
  }

}

// calculate the intersection point of the two lines, return point, and params
HRESULT  CLineStep::intersect( 
                    const CLineStep&  l1,           // in, line, pass byref to avoid copying 
                    intersectionType& eIntersect1,  // out, classification of the type of intersection, endpoint intersections are relative to l1
                    CPtrArray*        pPointXs ,    // out, intersection points
                    double&           param0,       // out, intersection parameter on this 
                    double&           param1,       // out, intersection parameter on l1
                    intersectionType& eIntersect0)  // out, classification of the type of intersection, endpoint intersections are relative to this
  // lines parameterized from 0 to length
{
  // no this is not how to do it, 
  // calculate the closest distanced between the two segments and 
  //  see if it is within tolerance!
  // change this to allocate off heap rather than stack as CPlaneStep // wh 6/7/01
  CVectorStep p1mp0 ( *m_pPos, *l1.m_pPos);
  matrix2x3 A;
  // get intersection using x & y coord
  for (int j = 0; j < 3; j++){
    A.coordinates[j][0] = this->m_pDir->coordinates[j];
    A.coordinates[j][1] =   -l1.m_pDir->coordinates[j];
    A.rhs[j] = p1mp0.coordinates[j] ;
  }

  double x[3] = { 0.e0, 0.e0, 0.e0};// why 3, this should be 2
  int iSoln=0;
  if ((false != A.solve(x, iSoln)) || (0==iSoln)){
    eIntersect0 = noIntersection;  
    eIntersect1 = noIntersection;  
  }
  else {
    // calculate the residual
    double r[3];// residual
    double residualSum = 0.0e0;
    for ( j = 0; j < 3; j++){
      r[j]       = this->m_pDir->coordinates[j] * x[0];
      r[j]      -=    l1.m_pDir->coordinates[j] * x[1];
      r[j]      -=         p1mp0.coordinates[j] ;
      residualSum += fabs(r[j] ) ;
    }
    if (residualSum > (3.e0* restol )){
      eIntersect0 = noIntersection;  
      eIntersect1 = noIntersection;  
    }
    else 
    {

      double l1_len = l1.m_pDir->getLength();// not needed
      double l1_tolrel = restol / l1_len;// not needed

      double l0_len = this->m_pDir->getLength();// not needed
      double l0_tolrel = restol / l0_len;// not needed
      
      // if the x & z coords agree, then we have an intersection in 3D
      
      bool inside0 = (-l0_tolrel < x[0]) && (x[0] < (1.0e0  + l0_tolrel));// wh 03/06/02
      bool inside1 = (-l1_tolrel < x[1]) && (x[1] < (1.0e0  + l1_tolrel));// wh 03/06/02

      if (inside0  && inside1 ){      
      
        CCartesian_pointStep *pPointX = NULL;

        eIntersect0 = interiorIntersection;  
        eIntersect1 = interiorIntersection;  

        bool bStart0 = false;
        bool bEnd0   = false;
        bool bStart1 = false;
        bool bEnd1   = false;

        bStart0 = (        - l0_tolrel  < x[0]) && (x[0] <           l0_tolrel);
        if (bStart0) {
          eIntersect0 = startpointIntersection;  
          pPointX = this->m_pPos;
          pPointXs->Add((void*) pPointX );// wh 03/06/02  moved inside
        } else {
        
          bEnd0   = ((1.0e0 - l0_tolrel) < x[0]) && (x[0] < (1.0e0  + l0_tolrel));// wh 03/06/02
          if (bEnd0) {
            eIntersect0 = endpointIntersection;  
            pPointX = this->m_pPos1;
            pPointXs->Add((void*) pPointX );// wh 03/06/02  moved inside
          } 
        }

        bStart1 = (        - l1_tolrel  < x[1]) && (x[1] < (         l1_tolrel));

        if (bStart1) {
          eIntersect1 = startpointIntersection;  
          pPointX =  l1.m_pPos;
          if (interiorIntersection == eIntersect0 ) {
            pPointXs->Add((void*) pPointX );// wh 03/06/02  moved inside
          }
        } else {
          bEnd1   = ((1.0e0  - l1_tolrel) < x[1]) && (x[1] < (1.0e0  + l1_tolrel));// wh 03/06/02
          if (bEnd1){
            eIntersect1 = endpointIntersection;  
            pPointX = l1.m_pPos1;
            if (interiorIntersection == eIntersect0 ) {
              pPointXs->Add((void*) pPointX );// wh 03/06/02  moved inside
            }
          }
        }

        param0 = x[0] * l0_len;
        param1 = x[1] * l1_len;

        pos3d cp;
        cp.crossProduct( this->m_pDir->coordinates, l1.m_pDir->coordinates);
        if (cp.withinTol()){
          // need to verify if range is correct!
          eIntersect0 = coincidentIntersection;  
          eIntersect1 = coincidentIntersection;  
//        pPointX = m_pPos;
          // if the intersections are at previous endpoints, return those preview endpoints
        }
        else //{
          if ((interiorIntersection == eIntersect0 ) && 
              (interiorIntersection == eIntersect1 )
             ) {

            pPointX = new 
              CCartesian_pointStep ( NULL, *this->m_pPos);
            if (NULL==pPointX ){
              return E_OUTOFMEMORY;
            }

            CVectorStep* pv0 = new CVectorStep(*this->m_pDir );
            if (NULL==pv0){
              return E_OUTOFMEMORY;
            }
            *pv0 *= x[0];
            *pPointX  += *pv0; 
            delete pv0;// wh 10/04/01
            pPointXs->Add((void*) pPointX );// wh 10/04/01  moved inside
          } 
//        else if () {
//        }

        //}
      }
      else 
      {
        eIntersect0 = exteriorIntersection;  
        eIntersect1 = exteriorIntersection;  
      }
    }
  }
  return S_OK;  // rv indicates success in completing execuation of function, not intersection
}
/*
HRESULT  CLineStep::intersect( 
                    const CLineStep& l1,           // in, line, pass byref to avoid copying 
                    intersectionType& eIntersect1, // out, classification of the type of intersection, endpoint intersections are relative to l1
                    CPtrArray* pPointXs ,          // out, intersection points
                    double& param0,                // out, intersection parameter on this 
                    double& param1,                // out, intersection parameter on l1
                    intersectionType& eIntersect0) // out, classification of the type of intersection, endpoint intersections are relative to l1
  // lines parameterized from 0 to 1
{
  // no this is not how to do it, 
  // calculate the closest distanced between the two segments and 
  //  see if it is within tolerance!
  // change this to allocate off heap rather than stack as CPlaneStep // wh 6/7/01
  CVectorStep p1mp0 ( *m_pPos, *l1.m_pPos);
  matrix2x2 A;
  // get intersection using x & y coord
  A.coordinates[0][0] = this->m_pDir->coordinates[0];
  A.coordinates[0][1] =   -l1.m_pDir->coordinates[0];
  A.coordinates[1][0] = this->m_pDir->coordinates[1];
  A.coordinates[1][1] =   -l1.m_pDir->coordinates[1];

  A.rhs[0] = p1mp0.coordinates[0] ;
  A.rhs[1] = p1mp0.coordinates[1] ;
  double x[3] = { 0.e0, 0.e0};
  int iSoln=0;
  if ((false != A.solve(x, iSoln)) || (0==iSoln)){
    eIntersect0 = noIntersection;  
    eIntersect1 = noIntersection;  
  }
  else {
    // confirm intersection in the z coord
    x[2]  = this->m_pDir->coordinates[2] * x[0];
    x[2] -=    l1.m_pDir->coordinates[2] * x[1];
    x[2] -=        p1mp0.coordinates[2] ;

    if (fabs(x[2] ) > restol ){
      eIntersect0 = noIntersection;  
      eIntersect1 = noIntersection;  
    }
    else {
      double l1_len = l1.m_pDir->getLength();// not needed
      double l1_tolrel = restol / l1_len;// not needed

      double l0_len = this->m_pDir->getLength();// not needed
      double l0_tolrel = restol / l0_len;// not needed
      
      // if the x & z coords agree, then we have an intersection in 3D
      
      bool inside0 = (-l0_tolrel < x[0]) && (x[0] < (l0_len + l0_tolrel));
      bool inside1 = (-l1_tolrel < x[1]) && (x[1] < (l1_len + l1_tolrel));

      if (inside0  && inside1 ){      
      
        CCartesian_pointStep *pPointX = NULL;

        eIntersect0 = interiorIntersection;  
        eIntersect1 = interiorIntersection;  

        bool bStart0 = false;
        bool bEnd0   = false;
        bool bStart1 = false;
        bool bEnd1   = false;

        bStart0 = (        - l0_tolrel  < x[0]) && (x[0] <           l0_tolrel);
        if (bStart0) {
          eIntersect0 = startpointIntersection;  
          pPointX = this->m_pPos;
        } else {
        
          bEnd0   = ((l0_len - l0_tolrel) < x[0]) && (x[0] < (l0_len + l0_tolrel));
          if (bEnd0) {
            eIntersect0 = endpointIntersection;  
            pPointX = this->m_pPos1;
          } 
        }

        bStart1 = (        - l1_tolrel  < x[1]) && (x[1] < (         l1_tolrel));

        if (bStart1) {
          eIntersect1 = startpointIntersection;  
          pPointX =  l1.m_pPos;
        } else {
          bEnd1   = ((l1_len - l1_tolrel) < x[1]) && (x[1] < (l1_len + l1_tolrel));
          if (bEnd1){
            eIntersect1 = endpointIntersection;  
            pPointX = l1.m_pPos1;
          }
        }

        param0 = x[0];
        param1 = x[1];

        pos3d cp;
        cp.crossProduct( this->m_pDir->coordinates, l1.m_pDir->coordinates);
        if (cp.withinTol()){
          // need to verify if range is correct!
          eIntersect0 = coincidentIntersection;  
          eIntersect1 = coincidentIntersection;  
//        pPointX = m_pPos;
          // if the intersections are at previous endpoints, return those preview endpoints
        }
        else //{
          if (interiorIntersection == eIntersect1 ) {

            pPointX = new 
              CCartesian_pointStep ( l1.m_pPos, *l1.m_pPos);
            if (NULL==pPointX ){
              return E_OUTOFMEMORY;
            }

            CVectorStep* pv1 = new CVectorStep(*l1.m_pDir);
            if (NULL==pv1){
              return E_OUTOFMEMORY;
            }
            *pv1 *= param1;
            *pPointX  += *pv1; 
            delete pv1;// wh 10/04/01
          pPointXs->Add((void*) pPointX );// wh 10/04/01  moved inside
          }
        
        //}
      }
      else 
      {
        eIntersect0 = exteriorIntersection;  
        eIntersect1 = exteriorIntersection;  
      }
    }
  }
  return S_OK;  // rv indicates success in completing execuation of function, not intersection
}
*/
const double const_pi      = 3.1415926535897932384626433832795;//3.1415926535
const double const_half_pi = 1.5707963267948966192313216916398;
//double acos_restol = acos(restol);
HRESULT CLineStep::contains( CCartesian_pointStep&  rPos
                           , intersectionType&      eIntersect0
                           , double&                rdParam
                           )
{
  CVectorStep lineToPt( *m_pPos, rPos);
  double dLenLine = lineToPt.getLength();
  if (dLenLine < restol){
    rdParam = 0.0e0;
    eIntersect0 = startpointIntersection;      
    return S_OK;
  }
 
  CVectorStep lineThis( *m_pPos, *(this->m_pPos1));// wh 01/28/01
  double dp = dotProduct( lineToPt, lineThis);
  double dDirLength = lineThis.getLength();
  double dCosLenline = dp / dDirLength;

  double dAngle = const_half_pi;
  if (dLenLine > restol){
    double div = dCosLenline/dLenLine; 
//  ASSERT( fabs(div) <= 1.e0); 
    if (div<=-1.e0){
      dAngle = const_pi; 
    } 
    else if (div>=1.e0){
      dAngle = 0.e0;
    } else {
      dAngle = acos( div);
    }
  }  else {
    eIntersect0 = noIntersection; 
    rdParam= DBL_MAX;
    return S_OK;
  }
  if (fabs(dAngle)< (fourRestol)){

    lineThis.normalize();
    rdParam = dotProduct( lineThis, lineToPt);
    if (rdParam < -restol){
      eIntersect0 = noIntersection;  
    }
    else if (rdParam < restol){
      eIntersect0 = startpointIntersection;      
    }
    else if (rdParam < (dDirLength - restol)){
      eIntersect0 = interiorIntersection;  
    }
    else if (rdParam < (dDirLength + restol)){
      eIntersect0 = endpointIntersection;  
    }
    else {
      eIntersect0 = exteriorIntersection;  
    }
    
  }
  else if (
          (fabs(dAngle-const_pi)< (fourRestol   )) || 
          (fabs(dAngle+const_pi)< (fourRestol   )) 
          )
  {
    if (dLenLine < restol){
      rdParam = 0.0e0;
      eIntersect0 = startpointIntersection;      
    }
    else {
      rdParam = -dLenLine ;
      eIntersect0 = exteriorIntersection;  
    }
  }
/*
  else { 
    double dPerpDir2 = lenLine2 - (dAngleLenline * dAngleLenline);
    if (dPerpDir2 > restol2){
      eIntersect0= noIntersection;
    }
    else {
      if (dp < -restol){
        eIntersect0 = noIntersection;  
        rdParam= -DBL_MIN;
      } else if (dp < restol){
          eIntersect0 = startpointIntersection;  
          rdParam= 0.0e0;
      } else {  
        ASSERT(lenLine2 >= 0.0e0);
        double lenLine = 0.0e0;
        if(lenLine2 > 0.0e0){
          lenLine = sqrt( lenLine2);//wh 01/04/02
        }
        if (dp < lenLine - restol){
            eIntersect0 = interiorIntersection;  
            rdParam= lenLine - dp ;
        } else if (dp < lenLine + restol){
            eIntersect0 = endpointIntersection;  
            rdParam= lenLine ;
        } else {
            eIntersect0 = exteriorIntersection;  
            rdParam= DBL_MAX;
        }
      }
    }
  }
*/
  else {
    eIntersect0 = exteriorIntersection;  
  }
  return S_OK;
}

#if 0
// calculate the min distace between the lines
HRESULT  CLineStep::minDistance( 
                    const CLineStep& l1,          // in, line, pass byref to avoid copying 
                    intersectionType& eIntersect, // out, classification of the type of intersection, endpoint intersections are relative to l1
                    CPtrArray* pPointXs ,         // out, intersection points
                    double& param0,               // out, intersection parameter on l0
                    double& param1)               // out, intersection parameter on l1
  // lines parameterized from 0 to 1
{
  CVectorStep p1mp0 ( *m_pPos, *l1.m_pPos);
  matrix2x3 A;

  // get intersection using x & y coord
  A.coordinates[0][0] = this->m_pDir->coordinates[0];
  A.coordinates[0][1] =   -l1.m_pDir->coordinates[0];
  A.coordinates[1][0] = this->m_pDir->coordinates[1];
  A.coordinates[1][1] =   -l1.m_pDir->coordinates[1];
  A.coordinates[2][0] = this->m_pDir->coordinates[2];
  A.coordinates[2][1] =   -l1.m_pDir->coordinates[2];

  A.rhs[0] = p1mp0.coordinates[0] ;
  A.rhs[1] = p1mp0.coordinates[1] ;
  A.rhs[2] = p1mp0.coordinates[2] ;
  return S_OK;  // rv indicates success in completing execuation of function, not intersection
}
#endif
// why do I think there is a problem here wh 7/23/01  are you sure of the formulation
// calculate the least mean squares intersection using Moore Penrose method
//DEL HRESULT  CLineStep::intersectLMS( 
//DEL                     const CLineStep& l1,          // in, line, pass byref to avoid copying 
//DEL                     intersectionType& eIntersect, // out, classification of the type of intersection, endpoint intersections are relative to l1
//DEL                     CPtrArray* pPointXs ,         // out, intersection points
//DEL                     double& param0,               // out, intersection parameter on l0
//DEL                     double& param1)               // out, intersection parameter on l1
//DEL   // lines parameterized from 0 to 1
//DEL {
//DEL   // no this is not how to do it, calculate the closest distanced between the two segments and see if it is within tolerance!
//DEL   CVectorStep p1mp0 ( *m_pPos, *l1.m_pPos);
//DEL 
//DEL   matrix2x3 A;
//DEL   // get intersection using x & y coord
//DEL   A.coordinates[0][0] = this->m_pDir->coordinates[0];
//DEL   A.coordinates[0][1] =   -l1.m_pDir->coordinates[0];
//DEL   A.coordinates[1][0] = this->m_pDir->coordinates[1];
//DEL   A.coordinates[1][1] =   -l1.m_pDir->coordinates[1];
//DEL   A.coordinates[2][0] = this->m_pDir->coordinates[2];
//DEL   A.coordinates[2][1] =   -l1.m_pDir->coordinates[2];
//DEL 
//DEL   A.rhs[0] = p1mp0.coordinates[0] ;
//DEL   A.rhs[1] = p1mp0.coordinates[1] ;
//DEL   A.rhs[2] = p1mp0.coordinates[2] ;
//DEL 
//DEL   double x[3];
//DEL   int iSoln=0;
//DEL   if ((A.solve(x, iSoln)) || (0==iSoln)){
//DEL     eIntersect = noIntersection;  
//DEL   }
//DEL   else {
//DEL     // confirm intersection in the z coord
//DEL     x[2]  = this->m_pDir->coordinates[2] * x[0];
//DEL     x[2] -=    l1.m_pDir->coordinates[2] * x[1];
//DEL     x[2] -=      p1mp0.coordinates[2] ;
//DEL 
//DEL     double len2 = l1.m_pDir->getLength2();
//DEL     double tolrel2 = restol2 / len2;
//DEL     if ((x[2] * x[2] ) > tolrel2 ){
//DEL       eIntersect = noIntersection;  
//DEL     }
//DEL     else {
//DEL       // if the x & z coords agree, then we have an intersection in 3D
//DEL       double x0x0 = x[0] * x[0] ;
//DEL       double x1x1 = x[1] * x[1] ;
//DEL       
//DEL       if (
//DEL            ((x0x0            < tolrel2 )  && (x1x1            < tolrel2) )
//DEL         || ((fabs(len2-x0x0) < tolrel2)   && (    (x1x1)      < tolrel2) )
//DEL         || ((    (x0x0)      < tolrel2)   && (fabs(len2-x1x1) < tolrel2) )
//DEL         || ((fabs(len2-x0x0) < tolrel2)   && (fabs(len2-x1x1) < tolrel2) )
//DEL         )
//DEL 
//DEL       {
//DEL         eIntersect = interiorIntersection;  
//DEL         param0 = x[0];
//DEL         param1 = x[1];
//DEL         CCartesian_pointStep *pPointX = new 
//DEL           CCartesian_pointStep ( l1.*m_pPos);
//DEL         if (NULL==pPointX ){
//DEL           return E_OUTOFMEMORY;
//DEL         }
//DEL         pPointXs->Add((void*) pPointX );
//DEL         if (fabs(param1 ) < restol){
//DEL           eIntersect = startpointIntersection;  
//DEL         }
//DEL         else {
//DEL           CVectorStep* pv1 = new CVectorStep(*l1.m_pDir);
//DEL           if (NULL==pv1 ){
//DEL             return E_OUTOFMEMORY;
//DEL           }
//DEL           *pv1 *= param1;
//DEL           *pPointX  += *pv1; 
//DEL           CVectorStep* pDiff = new CVectorStep ( l1.*m_pPos, *pPointX );
//DEL           if (NULL==pDiff ){
//DEL             return E_OUTOFMEMORY;
//DEL           }
//DEL           if (fabs(pDiff->getLength2()-param1) < restol2){
//DEL             eIntersect = endpointIntersection;  
//DEL             delete pDiff;
//DEL             delete pv1 ;
//DEL           }
//DEL         }
//DEL 
//DEL         pos3d cp;
//DEL         cp.crossProduct( this->m_pDir->coordinates, l1.m_pDir->coordinates);
//DEL         if (cp.withinTol()){
//DEL           // need to verify if range is correct!
//DEL           eIntersect = coincidentIntersection;  
//DEL         }
//DEL         else{
//DEL           double len2 = p1mp0.getLength2();
//DEL           if ((-restol < param1)  && 
//DEL               (param1 < (len2+restol2))){
//DEL             eIntersect = interiorIntersection;        
//DEL           }
//DEL           else {
//DEL             eIntersect = exteriorIntersection;        
//DEL           }
//DEL         }
//DEL       }
//DEL       else 
//DEL       {
//DEL         eIntersect = noIntersection;  
//DEL       }
//DEL     }
//DEL   }
//DEL   // lines parameterized as a function of arc length
//DEL   return S_OK;  // rv indicates success in completing execuation of function, not intersection
//DEL }

CLineStepPtrArray::CLineStepPtrArray(int iNewSize=0)
: CPtrArray()
{
    m_hash.SetSize(iNewSize, 128+iNewSize/2);
    CPtrArray::SetSize(iNewSize, 128+iNewSize/2);
}
CLineStepPtrArray::~CLineStepPtrArray()
{
}

int CLineStepPtrArray::Add( CLineStep* pLineStepIn)
{
//  bool bOrient;
//  return SetAt( GetSize()-1, pLineStep, bOrient);
//  ASSERT( bOrient);

  // really should list to see if it is not there already!
  int nIndex = m_hash.GetSize();
/*
  for (int i = 0; i< nIndex; i++){
    if (i == m_hash.GetAt(i)){
      CLineStep* pLineStep = (CLineStep*)GetAt(i);
      intersection _intersection;
      pLineStep->intersect(pLineStepIn, _intersection);
      if (coincident == _intersection){
        return i;
      }
    }
  }
*/
  m_hash.Add( (void*)nIndex);
  return CPtrArray::Add( pLineStepIn);
}

int CLineStepPtrArray::SetAt(int nIndex, CLineStep* pLineStep, bool& rbOrient )
{
  int nNewIndex = nIndex;
#if 1
  for (int i = 0; i< nIndex; i++){
    int j = (int) m_hash.GetAt(i);
    CLineStep* pLineStep1 = (CLineStep*)(CPtrArray::GetAt( j));
    ASSERT( NULL != pLineStep1);
    double dDist2 = DBL_MAX;//
    try{
      dDist2 = getLength2(  (pLineStep->m_pPos),   (pLineStep1->m_pPos));
      dDist2+= getLength2(  (pLineStep->m_pDir),   (pLineStep1->m_pDir));
    }
    catch(...){
//      return -1;
      throw;
    }
    if (dDist2 < restol2) {
      nNewIndex = i;
      m_hash.SetAt(nIndex, (void*)nNewIndex);
      rbOrient = true;
      return nNewIndex;
      break;
    }


    // try the other ends as well
    try{
      CCartesian_pointStep aCartesian_pointStep3( pLineStep1->m_pPos, *pLineStep1->m_pPos);
      aCartesian_pointStep3+= *pLineStep1->m_pDir;
      dDist2 = getLength2( (pLineStep->m_pPos),   (&aCartesian_pointStep3));
      CCartesian_pointStep aCartesian_pointStep4( pLineStep->m_pPos, *pLineStep->m_pPos);
      aCartesian_pointStep4+= *pLineStep->m_pDir;
      dDist2+= getLength2( &aCartesian_pointStep4, (pLineStep1->m_pPos));
    }
    catch(...){
//      return -1;
      throw;
    }
    if (dDist2 < restol2 * 4) {
      nNewIndex = i;
      m_hash.SetAt(nIndex, (void*)nNewIndex);
      rbOrient = false;
      return nNewIndex;
      break;
    }

  }
#endif
  m_hash.SetAt(nIndex, (void*)nNewIndex);

  if (nNewIndex == nIndex) {
    CPtrArray::SetAt( nNewIndex, pLineStep);
    rbOrient = true;
  }
  return nIndex;
}

HRESULT CLineStep::backPtr(CBaseStep *&prBrep)
{  
  ASSERT( this != m_pBack );
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  else {
    return E_FAIL;
  }
}

void CLineStep::fin()
{

}

//////////////////////////////////////////////////////////
// who  date      history
// wh   12/05/01  CLineStepPtrArray::Add
// wh   01/04/01  bug


