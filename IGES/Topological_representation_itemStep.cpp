// Topological_representation_item.cpp: implementation of the CTopological_representation_item class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Topological_representation_itemStep.h"
#include "stepArchive.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTopological_representation_itemStep::CTopological_representation_itemStep( CBaseStep*pIn)
:CRepresentation_itemStep( )
{
  nameClass("Topological_representation_item");
  m_pParent = pIn;
//m_pParent->addRef();// not sure if you always have a parent
//pIn->m_pBack=this;
//CRepresentation_itemStep=pIn;
}

CTopological_representation_itemStep::~CTopological_representation_itemStep()
{
//m_pParent->release();// not sure if you always have a parent
}

void CTopological_representation_itemStep::Serialize(stepArchive &ar)
{
  if (!isSerialized()){
    setSerialized();
    try{
      writeChild(ar);
    }
    catch(...){
      ar << "\n/*Errors detected in CTopological_representation_itemStep::Serialize #\n";
      ar << getNum();
      ar <<   ", but continuing*/\n" ;    
      setSerialized();
    }
  }
}

HRESULT CTopological_representation_itemStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  return E_FAIL;
}

/*
template <int topologicalType> 
CDerivedTopological_representation_itemStep< topologicalType >::CDerivedTopological_representation_itemStep( CBaseStep*pIn)
: CTopological_representation_itemStep( pIn)
{
}
*/
//////////////////////////////////////////////////////////
// who  date      history

