// Manifold_solid_rep.cpp: implementation of the CManifold_solid_rep class.
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
#ifdef _WINDOWS 
#include "scribble.h"
#endif

#include "Manifold_solid_repStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
is this really used
CManifold_solid_repStep::CManifold_solid_repStep(CBaseStep*pIn, CClosed_shellStep*p_outer)
  :  CSolid_modelStep( pIn)
{
  name=("Manifold_solid_repStep");
  mp_outer=p_outer;
}

CManifold_solid_repStep::~CManifold_solid_repStep()
{

}

void CManifold_solid_repStep::Serialize(stepArchive &ar)
{
  if (!isSerialized()){
    setSerialized();
  }

}
