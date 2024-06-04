// loopStep.cpp: implementation of the CLoop class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _WINDOWS
#include "stdafx.h"
#endif

#include "loopStep.h"
//#include "Poly_loopStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#include "PointStep.h"
#include "stepArchive.h"

CLoopStep::CLoopStep(CBaseStep *In)
:  CTopological_representation_itemStep(In)
{
  nameClass("LOOP");
}

CLoopStep::~CLoopStep()
{

}

HRESULT CLoopStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  else {
    return E_FAIL;
  }
}

void CLoopStep::Serialize(stepArchive &ar)
{
  try{
    if (!isSerialized()){
      setSerialized();
      writeChild(ar);
    }
  }
  catch(...){
    ar << "\n/*Errors detected in CPlacementStep::Serialize #\n";
//  ar << getNum();
    ar <<   ", but continuing*/\n" ;    
  }
}


HRESULT CLoopStep::negate()
{
  return S_OK;
}

// check if brep represents void or antimatter
HRESULT CLoopStep::validate()
{
  return S_OK;
}

HRESULT CLoopStep::split( CrcPtrArray *       pIntersectionPts, 
                          CPoly_loopStep *&   rpNewPoly_loopStep)
{
  return S_OK;
}


HRESULT CLoopStep::split(  CrcPtrArray*           pIntersectionPts 
                         , CDirectionStep*        pAxis
                         , CPoly_loopStep*        pFOB2 )
{
  return S_OK;
}

HRESULT CLoopStep::split( CrcPtrArray*     pIntersectionPts 
                         , CDirectionStep* pAxis
                         , CPoly_loopStep* pFOB2 
                         , bool&           bFlipFob
                         , bool&           bFlipFob2
                         )
{
  return S_OK;
}

HRESULT CLoopStep::trim( CrcPtrArray*           pIntersectionPts 
                       , CDirectionStep*        pAxis
                       )
{
  return S_OK;
}

HRESULT CLoopStep::trimEdge( CrcPtrArray*           pIntersectionPts 
                           , paramPtrArray&         intersectionEdge
                           , CDirectionStep*        pAxis
                           , containment&           bContains
                           )
{
  return S_OK;
}

HRESULT CLoopStep::splitAdd( CrcPtrArray*     pIntersectionPts 
                           , CDirectionStep* pAxis
                           , CPoly_loopStep* pFOB2 
                           , bool&           bFlipFob
                           , bool&           bFlipFob2
                           )
{
  return S_OK;
}

//////////////////////////////////////////////////////////
// who  date      history
// wh   01/24/02  properly classify and discard exterior surface loops
