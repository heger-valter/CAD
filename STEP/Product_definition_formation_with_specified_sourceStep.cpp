// Product_definition_formation_with_specified_sourceStep.cpp: implementation of the CProduct_definition_formation_with_specified_sourceStep class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "scribble.h"
#include "Product_definition_formation_with_specified_sourceStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProduct_definition_formation_with_specified_sourceStep::CProduct_definition_formation_with_specified_sourceStep()
{
  nameClass("PRODUCT_DEFINITION_FORMATION_WITH_SPECIFIED_SOURCE");
}

CProduct_definition_formation_with_specified_sourceStep::~CProduct_definition_formation_with_specified_sourceStep()
{

}
void CProduct_definition_formation_with_specified_sourceStep::Serialize(stepArchive &ar)
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


HRESULT CProduct_definition_formation_with_specified_sourceStep::backPtr(CBaseStep *&prBrep)
{
  return S_OK;

}
