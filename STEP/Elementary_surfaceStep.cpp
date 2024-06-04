// Elementary_surface.cpp: implementation of the CElementary_surface class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _WINDOWS
#include "stdafx.h"
#endif

#ifdef _WINDOWS 
#include "scribble.h"
#endif

#include "Elementary_surfaceStep.h"
#include "VectorStep.h"
#include "LineStep.h"
#include "pointStep.h"
#include "Cartesian_pointStep.h"
#include "math.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CElementary_surfaceStep::CElementary_surfaceStep( CAxis2_placement_3dStep*pPos)
:  CSurfaceStep( this)
,  m_pPosition(pPos)
{
  nameClass("Elementary_surface");
#ifdef  EXPOSE      
  fprintf( g_errorLog, "CElementary_surfaceStep = (#%d )\n", m_pPosition->getNum());
#endif//EXPOSE   
  m_pPosition->addRef();
}

CElementary_surfaceStep::~CElementary_surfaceStep()
{
  fin();
}

HRESULT CElementary_surfaceStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  return E_FAIL;
}

// remove all references to other external objects
void CElementary_surfaceStep::fin()
{
  m_pPosition->release();
}

 
HRESULT CElementary_surfaceStep::negate(void)
{
  
  return m_pPosition->negate();
}

HRESULT CElementary_surfaceStep::validate()
{
  return S_OK;
}

//////////////////////////////////////////////////////////
// who  date      history
// wh   11/04/01  len < tol return E_FAIL