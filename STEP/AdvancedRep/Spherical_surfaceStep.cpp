// Spherical_surfaceStep.cpp: implementation of the CSpherical_surfaceStep class.
//
//////////////////////////////////////////////////////////////////////

//#ifdef _WINDOWS
#ifdef _WINDOWS
#ifdef _WINDOWS
#include "stdafx.h"
#endif

#endif
"
#endif
"
#ifdef _WINDOWS 
#include "scribble.h"
#endif

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
