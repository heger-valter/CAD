// Product_definition_usageStep.cpp: implementation of the CProduct_definition_usageStep class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Product_definition_usageStep.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProduct_definition_usageStep::CProduct_definition_usageStep()
{
  nameClass("Product_definition_usage");

}

CProduct_definition_usageStep::~CProduct_definition_usageStep()
{

}

HRESULT CProduct_definition_usageStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  return E_FAIL;
}

void CProduct_definition_usageStep::Serialize(stepArchive &ar)
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

