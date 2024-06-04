// Cartesian_tranformation_operatorStep.cpp: implementation of the CCartesian_tranformation_operatorStep class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _WINDOWS
#include "stdafx.h"
#endif

#ifdef _WINDOWS 
#include "scribble.h"
#endif

#include "Cartesian_tranformation_operatorStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCartesian_tranformation_operatorStep::CCartesian_tranformation_operatorStep()
{
    nameClass("Cartesian_tranformation_operator");
}

CCartesian_tranformation_operatorStep::~CCartesian_tranformation_operatorStep()
{

}
HRESULT CCartesian_tranformation_operatorStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  else {
    return E_FAIL;
  }
}
