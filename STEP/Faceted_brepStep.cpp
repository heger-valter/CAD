// baseStep.cpp: implementation of the CBaseStep class.
//
//////////////////////////////////////////////////////////////////////

//#include <string>
//CString.h"

#ifdef _WINDOWS
#include "stdafx.h"
#endif

#include "Faceted_brepStep.h"
#include "Manifold_solid_brepStep.h"
#include "Connected_face_setStep.h"
#include "Geometric_Representation_contextStep.h"
#include "StepSer.h"
#include "ScribVw.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CFaceted_brepStep::CFaceted_brepStep( CClosed_shellStep* pShell)  
  : CManifold_solid_brepStep( NULL, pShell)// wh 8/23/01
{
  nameClass("FACETED_BREP");
  m_pShell=pShell;
  pShell->addRef();
//m_pShell->m_pBack=this;
}

CFaceted_brepStep::~CFaceted_brepStep()
{
  m_pShell->release();
}
HRESULT CFaceted_brepStep::backPtr(CBaseStep *&prBrep)
{
  prBrep = this;  
  return S_OK;
}

void CFaceted_brepStep::Serialize( stepArchive &ar)
{
  char out[128] = "(52%) ";
  strcat(out, this->m_szTheClass);
#if     NOTIFICATION 
  CRepresentationStep::m_pStep->m_pScribView->Notify( out);
#endif//NOTIFICATION 
  try{
    if (!isSerialized()){
      setSerialized();
      writePre(ar);
      ar << "'',#";
      ar << m_pShell->getNum();  
      writePost(ar);
      m_pShell->m_pBack = this;
      m_pShell->Serialize(ar);
      eulerCnt.writeEulerCount(ar);
    }
  }
  catch(...){
    ar << "\n/*Errors detected in CPlacementStep::Serialize #\n";
//  ar << getNum();
    ar <<   ", but continuing*/\n" ;    
    setSerialized();
  }
}


//////////////////////////////////////////////////////////
// who  date      history

