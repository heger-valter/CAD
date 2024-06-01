// Cylindrical_surfaceStep.cpp: implementation of the CCylindrical_surfaceStep class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#ifdef _WINDOWS 
#include "scribble.h"
#endif

#include "Cylindrical_surfaceStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCylindrical_surfaceStep::CCylindrical_surfaceStep(double dRadius, CAxis2_placement_3dStep& rPos)
:CElementary_surfaceStep(&rPos)
,m_dRadius(dRadius)
{
  nameClass("Cylindrical_surface");
}

CCylindrical_surfaceStep::~CCylindrical_surfaceStep()
{

}

HRESULT CCylindrical_surfaceStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  return E_FAIL;
}
void CCylindrical_surfaceStep::Serialize(stepArchive &ar)
{

  try{
    if (!isSerialized()){
      setSerialized();
      writePre( ar);
      ar << "'',#";
      ar << m_pPosition->getNum();
      ar << ",";
      ar << m_dRadius;
      writePost( ar);
      m_pPosition->m_pBack = this;
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

HRESULT CCylindrical_surfaceStep::split( CVertexStep &rVertexStep0
                                       , CVertexStep &rVertexStep1
                                       )
{
  return S_OK;
}

HRESULT CCylindrical_surfaceStep::normal( CCartesian_pointStep *pCartesian_pointStep
    , CDirectionStep*& pNormalDirection)
{
  return S_OK;
}
