// Shape_representationStep.cpp: implementation of the CShape_representationStep class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _WINDOWS
#include "stdafx.h"
#endif

#ifdef _WINDOWS 
#include "scribble.h"
#endif

#include "Shape_representationStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShape_representationStep::CShape_representationStep(step* pStep)
: CRepresentationStep(  pStep)
{
  nameClass("Shape_representation");
}

CShape_representationStep::~CShape_representationStep()
{

}

HRESULT CShape_representationStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  return E_FAIL;
}

void CShape_representationStep::Serialize(stepArchive &ar)
{

}