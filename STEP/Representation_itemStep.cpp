// Representation_item.cpp: implementation of the CRepresentation_item class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _WINDOWS
#include "stdafx.h"
#endif

#include "Representation_itemStep.h"
#include "stepArchive.h"
#include "StepSer.h"
#include "ScribVw.h"// for Notify
#include "RepresentationStep.h"
//#include "EulerCntStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CRepresentation_itemStep::CRepresentation_itemStep()
{
  nameClass("Representation_item");
}

CRepresentation_itemStep::~CRepresentation_itemStep()
{
}

//CRepresentation_itemStep::m_rStep;


/**
 * <brief description>
 *
 * <full description>
 * <directive>
 * <directive>
 * .
 * .
 * <directive>
 */
void CRepresentation_itemStep::Serialize(stepArchive &ar)
{
  try{
    if (!isSerialized()){
      setSerialized();
      writeChild( ar); // left over ,
      ar << "''";
    }
  }
  catch(...){
    setSerialized();
    ar << "\n/*Errors detected in CPlacementStep::Serialize #\n";
//  ar << getNum();
    ar <<   ", but continuing*/\n" ;    
  }
#if     NOTIFICATION 
  CRepresentationStep::m_pStep->m_pScribView->Notify("(85%) CRepresentation_itemStep::buildShellsFaceted");
#endif//NOTIFICATION 
}

HRESULT CRepresentation_itemStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  return E_FAIL;
}

//////////////////////////////////////////////////////////
// who  date      history

