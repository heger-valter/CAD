// Spherical_surfaceStep.cpp: implementation of the CSpherical_surfaceStep class.
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
#include "scribble.h"
#include "Spherical_surfaceStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSpherical_surfaceStep::CSpherical_surfaceStep()
{
  nameClass("Spherical_surfac");
}

CSpherical_surfaceStep::~CSpherical_surfaceStep()
{

}

HRESULT CSpherical_surfaceStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  return E_FAIL;
}
