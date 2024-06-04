// Next_assembly_usage_occurance.cpp: implementation of the CNext_assembly_usage_occurance class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Next_assembly_usage_occuranceStep.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNext_assembly_usage_occuranceStep::CNext_assembly_usage_occuranceStep()
{
  nameClass("next_assembly_usage_occurance");

}

CNext_assembly_usage_occuranceStep::~CNext_assembly_usage_occuranceStep()
{

}

HRESULT CNext_assembly_usage_occuranceStep::backPtr(CBaseStep *&prBrep)
{
  prBrep = m_pBack;  
  return S_OK;
}

void CNext_assembly_usage_occuranceStep::Serialize(stepArchive &ar)
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
    ar << "\n/*Errors detected in "<< m_szTheClass.GetBufferSetLength(m_szTheClass.GetLength()+1) <<"::Serialize #\n";
//  ar << getNum();
    ar <<   ", but continuing*/\n" ;    
    m_szTheClass.ReleaseBuffer();
  }
#endif
}
