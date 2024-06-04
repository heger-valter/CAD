// Manifold_solid_rep.cpp: implementation of the CManifold_solid_rep class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _WINDOWS
#include "stdafx.h"
#endif

//#ifdef _WINDOWS 
#include "scribble.h"
#endif

#include "Manifold_solid_brepStep.h"
#include "stepArchive.h"
#include "Connected_face_setStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CManifold_solid_brepStep::CManifold_solid_brepStep( CBaseStep*pIn, CClosed_shellStep* pShell)// is this last arg always used??
  :  CSolid_modelStep( pIn)
{
  nameClass("Manifold_solid_brep"); 
  m_pShell = pShell;
  m_pShell->addRef();
}

CManifold_solid_brepStep::~CManifold_solid_brepStep()
{
  m_pShell->release();
}

void CManifold_solid_brepStep::Serialize(stepArchive &ar)
{
  try{
    if (!isSerialized()){
      setSerialized();
      writePre( ar);
      ar << "#";
      ar <<  m_pShell->getNum();
      writePost( ar);
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
HRESULT CManifold_solid_brepStep::backPtr(CBaseStep *&prBrep)
{
  prBrep = this;  
  return S_OK;
}

//////////////////////////////////////////////////////////
// who  date      history
