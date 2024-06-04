// Swept_surfaceStep.cpp: implementation of the CSwept_surfaceStep class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _WINDOWS
#ifdef _WINDOWS
#ifdef _WINDOWS
#include "stdafx.h"
#endif

#endif
"
#endif
"
#include "scribble.h"
#include "Swept_surfaceStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSwept_surfaceStep::CSwept_surfaceStep()
{
  nameClass("Swept_surface");

}

CSwept_surfaceStep::~CSwept_surfaceStep()
{

}

HRESULT CSwept_surfaceStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  return E_FAIL;
}
