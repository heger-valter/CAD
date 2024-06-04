// Property_definition_representationStep.cpp: implementation of the CProperty_definition_representationStep class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _WINDOWS
#include "stdafx.h"
#endif

#ifdef _WINDOWS 
#include "scribble.h"
#endif

#include "Property_definition_representationStep.h"
#include "Property_definitionStep.h"
#include "RepresentationStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProperty_definition_representationStep::CProperty_definition_representationStep()
: m_pDefinition(NULL)
, m_pUsed_representation(NULL)
{

}

CProperty_definition_representationStep::~CProperty_definition_representationStep()
{

}

void CProperty_definition_representationStep::Serialize(stepArchive &ar)
{
  try{
    if (!isSerialized()){
      setSerialized();
      writePre(ar);
      ar << "'',";
      if (NULL != m_pDefinition){
        ar << "#" << m_pDefinition->getNum();
      }
      ar << ",";
      if (NULL != m_pUsed_representation){
        ar << "#" << m_pUsed_representation->getNum();
      }
      writePost(ar);

      m_pDefinition->Serialize( ar);
      m_pUsed_representation->Serialize( ar);
    }
  }
  catch(...){
    ar << "\n/*Errors detected in ::Serialize #\n";
//  ar << getNum();
    ar <<   ", but continuing*/\n" ;    
  }
}
