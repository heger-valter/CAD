// CircleStep.cpp: implementation of the CCircleStep class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _WINDOWS
#include "stdafx.h"
#endif

#ifdef _WINDOWS 
#include "scribble.h"
#endif

#include "CircleStep.h"
//#include "Axis2_placement_2dStep.h"
#include "PlacementStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCircleStep::CCircleStep( CPlacementStep& rPosition, double dRadius)
: CConicStep( rPosition)
, m_dRadius (dRadius)
{
  nameClass("Circle");
}

CCircleStep::~CCircleStep()
{

}

HRESULT CCircleStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  else {
    return E_FAIL;
  }
}
void CCircleStep::Serialize(stepArchive &ar)
{
  try{
    if (!isSerialized()){
      setSerialized();
      writePre(ar);
      ar << "'',#";
      ar << m_rPosition.getNum();
      ar << ", ";
      ar << m_dRadius;
      writePost(ar);
      m_rPosition.m_pBack = this;
      m_rPosition.Serialize( ar);
    }
  }
  catch(...){
      setSerialized();
      ar << "\n/*Error caught in CCurveStep::Serialize!*/\n";
  }

}

//////////////////////////////////////////////////////////
// who  date      history
// wh   11/19/01  use CPlacementStep instead of select CAxis2_placement_Step


