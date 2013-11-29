// OrganizationStep.cpp: implementation of the COrganizationStep class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "scribble.h"
#include "OrganizationStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COrganizationStep::COrganizationStep()
{

}

COrganizationStep::~COrganizationStep()
{

}

HRESULT COrganizationStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  else {
    return E_FAIL;
  }
}

void COrganizationStep::Serialize(stepArchive &ar)
{
  try{
   if (!isSerialized()){
      setSerialized();
      writePre(ar);
      ar <<   "'', " ;
      writePost(ar);
    }
  }
  catch(...){
    ar << "\n/*Errors detected in ::Serialize #\n";
//  ar << getNum();
    ar <<   ", but continuing*/\n" ;    
  }
}

