// Shape_definition_representationStep.cpp: implementation of the CShape_definition_representationStep class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "scribble.h"
#include "Shape_definition_representationStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShape_definition_representationStep::CShape_definition_representationStep( )
: CProperty_definition_representationStep()
{
  nameClass("Shape_definition_representation");
}

CShape_definition_representationStep::~CShape_definition_representationStep()
{

}

HRESULT CShape_definition_representationStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  return E_FAIL;
}

void CShape_definition_representationStep::Serialize(stepArchive &ar)
{
  try{
    if (!isSerialized()){
      setSerialized();
      writePre(ar);
      ar << "'',#";
//    ar << m_pDefinition->getNum();
      ar << ",#";
//    ar << m_pUsed_representation->getNum();
      writePost(ar);

//    m_pDefinition->Serialize( ar);
//    m_pUsed_representation->Serialize( ar);
    }
  }
  catch(...){
    ar << "\n/*Errors detected in ::Serialize #\n";
//  ar << getNum();
    ar <<   ", but continuing*/\n" ;    
  }
}


