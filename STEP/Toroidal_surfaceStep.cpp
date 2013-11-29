// Toroidal_surfaceStep.cpp: implementation of the CToroidal_surfaceStep class.
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
#include "scribble.h"
#include "Toroidal_surfaceStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CToroidal_surfaceStep::CToroidal_surfaceStep()
{
  nameClass("Toroidal_surface");

}

CToroidal_surfaceStep::~CToroidal_surfaceStep()
{

}

HRESULT CToroidal_surfaceStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  return E_FAIL;
}
