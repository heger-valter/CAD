// Surface_of_linear_extrusionStep.cpp: implementation of the CSurface_of_linear_extrusionStep class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#ifdef _WINDOWS 
#include "scribble.h"
#endif

#include "Surface_of_linear_extrusionStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSurface_of_linear_extrusionStep::CSurface_of_linear_extrusionStep()
{
  nameClass("Surface_of_linear_extrusion");

}

CSurface_of_linear_extrusionStep::~CSurface_of_linear_extrusionStep()
{

}

HRESULT CSurface_of_linear_extrusionStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  return E_FAIL;
}
