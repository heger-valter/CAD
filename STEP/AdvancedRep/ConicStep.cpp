// ConicStep.cpp: implementation of the CConicStep class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#ifdef _WINDOWS 
#include "scribble.h"
#endif

#include "ConicStep.h"
#include "PlacementStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CConicStep::CConicStep(CPlacementStep& rPosition)
: CCurveStep()
, m_rPosition(rPosition)
{
  nameClass("Conic");
}

CConicStep::~CConicStep()
{

}
HRESULT CConicStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  else {
    return E_FAIL;
  }
}
