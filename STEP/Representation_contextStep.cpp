// Representation_context.cpp: implementation of the CRepresentation_context class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _WINDOWS
#include "stdafx.h"
#endif

//#ifdef _WINDOWS 
#include "scribble.h"
#endif

#include "Representation_contextStep.h"
#include "BaseStep.h"
#include "stepArchive.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRepresentation_contextStep::CRepresentation_contextStep(CBaseStep*pIn)
: CBaseStep(pIn)
{
  nameClass("Representation_context");
}

CRepresentation_contextStep::~CRepresentation_contextStep()
{

}

void CRepresentation_contextStep::Serialize(stepArchive &ar)
{
  try{
    if (!isSerialized()){
      setSerialized();
    }
  }
  catch(...){
    ar << "\n/*Errors detected in CPlacementStep::Serialize #\n";
//  ar << getNum();
    ar <<   ", but continuing*/\n" ;    
  }
}

HRESULT CRepresentation_contextStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  return E_FAIL;
}

//////////////////////////////////////////////////////////
// who  date      history
