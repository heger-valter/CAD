// Product_definitionStep.cpp: implementation of the CProduct_definitionStep class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#ifdef _WINDOWS 
#include "scribble.h"
#endif

#include "Product_definitionStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProduct_definitionStep::CProduct_definitionStep()
{
  nameClass("Product_definition");

}

CProduct_definitionStep::~CProduct_definitionStep()
{

}
void CProduct_definitionStep::Serialize(stepArchive &ar)
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


HRESULT CProduct_definitionStep::backPtr(CBaseStep *&prBrep)
{
  return S_OK;

}
