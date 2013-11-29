// CMechanical_contextStep.cpp: implementation of the CMechanical_contextStep class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "scribble.h"
#include "Mechanical_contextStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMechanical_contextStep::CMechanical_contextStep()
{
  nameClass("MECHANICAL_CONTEXT");

}

CMechanical_contextStep::~CMechanical_contextStep()
{

}

void CMechanical_contextStep::Serialize(stepArchive &ar)
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


HRESULT CMechanical_contextStep::backPtr(CBaseStep *&prBrep)
{
  return S_OK;
}
