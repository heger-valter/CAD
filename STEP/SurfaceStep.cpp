// SurfaceStep.cpp: implementation of the CSurfaceStep class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _WINDOWS
#include "stdafx.h"
#endif

#include "SurfaceStep.h"
#include "stepArchive.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSurfaceStep::CSurfaceStep(CBaseStep*pIn)
:CGeometric_representation_itemStep(pIn)
{
  nameClass("Surface");

}

CSurfaceStep::~CSurfaceStep()
{

}

HRESULT CSurfaceStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  return E_FAIL;
}

void CSurfaceStep::Serialize(stepArchive &ar)
{
  try{
    if (!isSerialized()){
      setSerialized();
      writeChild(ar);
    }
  }
  catch(...){
    setSerialized();
    ar << "\n/*Errors detected in CPlacementStep::Serialize #\n";
//  ar << getNum();
    ar <<   ", but continuing*/\n" ;    
  }
}

HRESULT CSurfaceStep::normal( CCartesian_pointStep *pCartesian_pointStep
    , CDirectionStep*& pNormalDirection)
{
  return S_OK;
}

//////////////////////////////////////////////////////////
// who  date      history
