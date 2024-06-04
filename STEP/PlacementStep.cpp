// Placement.cpp: implementation of the CPlacement class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _WINDOWS
#include "stdafx.h"
#endif

#include "afx.h"
#include "PlacementStep.h"
#include "Cartesian_pointStep.h"
#include "stepArchive.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPlacementStep::CPlacementStep( CCartesian_pointStep* pLocation)
: CGeometric_representation_itemStep(this)
, m_pLocation(pLocation)
{
  nameClass("Placement");
  m_pLocation->addRef();
}

CPlacementStep::~CPlacementStep()
{
  ASSERT_VALID( m_pLocation);
  m_pLocation->release();
}

void CPlacementStep::Serialize(stepArchive &ar)
{
  try{
    if (!isSerialized()){
      setSerialized();
    }
  }
  catch(...){
    ar << "\n/*Errors detected in CPlacementStep::Serialize #\n";
//  ar << getNum();
    ar <<   ", but continuing*/\n" ;    
  }

}
//////////////////////////////////////////////////////////
// who  date      history

void CPlacementStep::fin()
{
}

HRESULT CPlacementStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  return E_FAIL;
}
