// RepresentationStep.cpp: implementation of the CRepresentationStep class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _WINDOWS
#include "stdafx.h"
#endif

#ifdef _WINDOWS 
#include "scribble.h"
#endif

#include "RepresentationStep.h"
#include "Representation_contextStep.h"
#include "Representation_itemStep.h"

class step;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRepresentationStep::CRepresentationStep(step* pStep)
{
  nameClass("Representation");
  m_pStep=pStep;
}

CRepresentationStep::~CRepresentationStep()
{

}

HRESULT CRepresentationStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  return E_FAIL;
}

step* CRepresentationStep::m_pStep=NULL;
