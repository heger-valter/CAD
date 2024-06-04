// Surface_of_revolutionStep.cpp: implementation of the CSurface_of_revolutionStep class.
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
#ifdef _WINDOWS 
#include "scribble.h"
#endif

#include "Surface_of_revolutionStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSurface_of_revolutionStep::CSurface_of_revolutionStep()
{
  nameClass("Surface_of_revolution");

}

CSurface_of_revolutionStep::~CSurface_of_revolutionStep()
{

}

HRESULT CSurface_of_revolutionStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  return E_FAIL;
}
