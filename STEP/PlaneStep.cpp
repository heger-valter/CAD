// Plane_surface.cpp: implementation of the CPlane_surface class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _WINDOWS
#include "stdafx.h"
#endif

#ifdef _WINDOWS 
#include "scribble.h"
#endif

#include "Elementary_surfaceStep.h"
#include "PlaneStep.h"
#include "VectorStep.h"
#include "LineStep.h"
#include "pointStep.h"
#include "Cartesian_pointStep.h"
#include "math.h" 
#include "agitoPtrArray.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CPlaneStep::CPlaneStep( CAxis2_placement_3dStep*pPos)
: CElementary_surfaceStep(pPos)
{
  nameClass("PLANE" );
  pPos->m_pBack = this;
}

CPlaneStep::~CPlaneStep()
{
  fin();
}

HRESULT CPlaneStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  else {
    return E_FAIL;
  }
}

void CPlaneStep::Serialize( stepArchive &ar){
  try{
    if (!isSerialized()){
      setSerialized();
      writePre( ar);
      ar << "'',#";
      ar << m_pPosition->getNum();
      writePost( ar);
      ASSERT( this == m_pPosition->m_pBack );
      m_pPosition->Serialize(ar);
    }
  }
  catch(...){
    ar << "\n/*Errors detected in ";
    ar << m_szTheClass;
    ar << "::Serialize  #\n";
//  ar << getNum();
    ar <<   ", but continuing*/\n" ;    
  }
}




// remove all references to other external objects
void CPlaneStep::fin()
{
  CElementary_surfaceStep::fin();
}

// determine if the point is on the surface
bool CPlaneStep::onSurface( CCartesian_pointStep &rPoint)
{
  CVectorStep distFromOrigin( *(m_pPosition->m_pLocation), rPoint );
  if ( fabs(distFromOrigin.m_dMagnitude) < restol){
    return true;
  }
  CVectorStep axis(* m_pPosition->m_pAxis );
  double dDist= dotProduct( distFromOrigin, axis);
  return (fabs(dDist) < restol)? true : false;// wh 07/10/01
}
// Plane is P(u, w) = A + u B + w C ;
// problem here, both line & plane's loop must intersect on the interior // wh 7/18/01, p321
HRESULT CPlaneStep::intersect( CLineStep *pLine,             // in,  line to be intersected.// Q(t) = D + t E;
                               intersectionType& eIntersect, // out, classification of the type of intersection, endpoint intersections are relative to l1
                               CrcPtrArray* pPointXs ,       // out, intersection points
                               double& paramU,               // out, intersection u parameter on plane
                               double& paramV,               // out, intersection v parameter on plane
                               double  paramT[2])            // out, intersection parameter on line
{
  CVectorStep axis ( *(m_pPosition->m_pAxis)); 
  bool bWithinTol = false; 
  axis.withinTol( bWithinTol ); 
  ASSERT( !bWithinTol );
  CVectorStep *pAxis = &axis;
  CVectorStep loc  ( *(m_pPosition->m_pLocation));
  loc.withinTol( bWithinTol ); 
  ASSERT( !bWithinTol );
  CVectorStep *pLoc  = &loc;
  double bxc_a = dotProduct( *pAxis, *pLoc);
  CVectorStep D  ( *pLine->m_pPos);
  D.withinTol( bWithinTol ); 
  ASSERT( !bWithinTol );
  CVectorStep *pD  = &D;
  double bxc_d = dotProduct( *pAxis, *pD);
  paramT[0] = bxc_a - bxc_d;// 7.7
  CVectorStep E  ( *pLine->m_pDir);
  CVectorStep *pE  = &E;
  double bxc_e = dotProduct( *pAxis, *pE);
//ASSERT(fabs(paramT[0]) > restol );
  if (restol2 < fabs(bxc_e)) {
    paramT[0] /= bxc_e;//(7.7)

    CCartesian_pointStep* pIntersectionPoint = new
      CCartesian_pointStep ( NULL, *pLine->m_pPos);
    CVectorStep Ei(*pE);
    CVectorStep *pEi = &Ei;
    *pEi *= paramT[0];
    *pIntersectionPoint += *pEi;
    double endparam = 1.0;// endparam of line
    double len = pLine->m_pDir->getLength();
    ASSERT(len>restol);
    if (len<restol) {
      return E_FAIL; 
    } // wh 11/04/01
    double tolRel = restol/len;
    if ( paramT[0] < -tolRel ){
      eIntersect = noIntersection;  
    }
    else if ( paramT[0] <  tolRel ){
      eIntersect = startpointIntersection;    
      pPointXs->Add( (void*) pLine->m_pPos);
    }
    else if ( paramT[0] <  endparam - tolRel ){
      eIntersect = interiorIntersection;    
      pPointXs->Add( (void*)pIntersectionPoint );
    }
    else if ( paramT[0] <  endparam + tolRel ){
      eIntersect = endpointIntersection;    
      pPointXs->Add( (void*) pLine->m_pPos1);
    }
    else {
      eIntersect = noIntersection;//hiIntersection;// wh 10/18/01
    }    
    pIntersectionPoint->release();// wh 10/20/01 
  }
  else {
    if (this->onSurface( *pLine->m_pPos)){
      eIntersect = coincidentIntersection;  
  //  still need to find out if within bounds
      pPointXs->Add( (void*) pLine->m_pPos);
      
      pPointXs->Add( (void*) pLine->m_pPos1);
    }
    else {
      eIntersect = noIntersection;  
    }

  }
  return S_OK;
}
 
HRESULT CPlaneStep::negate()
{  
  return m_pPosition->negate();
}

HRESULT CPlaneStep::validate()
{
//m_pPosition->validate();
  return S_OK;
}

HRESULT CPlaneStep::normal( CCartesian_pointStep *pCartesian_pointStep
    , CDirectionStep*& pNormalDirection)
{
  pNormalDirection = this->m_pPosition->m_pAxis;
  return S_OK;
}

//////////////////////////////////////////////////////////
// who  date      history
// wh   11/04/01  len < tol return E_FAIL