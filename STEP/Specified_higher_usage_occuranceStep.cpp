// Specified_higher_usage_occurance.cpp: implementation of the CSpecified_higher_usage_occurance class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _WINDOWS
#include "stdafx.h"
#endif

#include "Specified_higher_usage_occuranceStep.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSpecified_higher_usage_occuranceStep::CSpecified_higher_usage_occuranceStep( CNext_assembly_usage_occuranceStep& rNext_usage,
                                                                              CAssembly_component_usageStep& rUpper_usage)
  :CAssembly_component_usageStep  ()
  , m_rNext_usage( rNext_usage)
  , m_rUpper_usage( rUpper_usage)
{
  nameClass("Specified_higher_usage_occurance");
}

CSpecified_higher_usage_occuranceStep::~CSpecified_higher_usage_occuranceStep()
{

}

HRESULT CSpecified_higher_usage_occuranceStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  return E_FAIL;
}

void CSpecified_higher_usage_occuranceStep::Serialize(stepArchive &ar)
{
#if 0
  try{
    if (!isSerialized()){
      setSerialized();
      writePre(ar);
      ar << "'',#";
      ar << m_pPRODUCT_DEFINITION0->getNum();
      ar << ",#";
      ar << m_pPRODUCT_DEFINITION1->getNum();
      ar << ",";
      if (NULL != m_pPRODUCT_DEFINITION2){
        ar << "#";
        ar << m_pPRODUCT_DEFINITION2->getNum();
      } else {
        ar << "$";
      }
      writePost(ar);

      m_pPRODUCT_DEFINITION0->Serialize( ar);
      m_pPRODUCT_DEFINITION1->Serialize( ar);
      if (NULL != m_pPRODUCT_DEFINITION2){
        m_pPRODUCT_DEFINITION2->Serialize( ar);
      }
    }
  }
  catch(...){
    ar << "\n/*Errors detected in ::Serialize #\n";
//  ar << getNum();
    ar <<   ", but continuing*/\n" ;    
  }
#endif
}

