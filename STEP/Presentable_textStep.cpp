// Presentable_textStep.cpp: implementation of the CPresentable_textStep class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _WINDOWS
#include "stdafx.h"
#endif

#include "stepArchive.h"
#include "Presentable_textStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPresentable_textStep::CPresentable_textStep(char*szText)
: CBaseStep()
, m_text(szText)
{
  nameClass("Presentable_text");
}

CPresentable_textStep::~CPresentable_textStep()
{

}
HRESULT CPresentable_textStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  return E_FAIL;
}

void CPresentable_textStep::Serialize(stepArchive &ar)
{
  try{
    if (!isSerialized()){
      setSerialized();
      writePre( ar);
      writeLabel( ar); 
      m_text.Replace("'","\"");
      ar << "'" << m_text << "'";
      writePost( ar);
    }
  }
  catch(...){
    ar << "\n/*Errors detected in CPresentable_textStep::Serialize #\n";
    ar << getNum();
    ar <<   ", but continuing*/\n" ;    
  }
//return false;
}
