// Solid_model.cpp: implementation of the CSolid_model class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#ifdef _WINDOWS 
#include "scribble.h"
#endif

#include "Solid_modelStep.h"
#include "stepArchive.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSolid_modelStep::CSolid_modelStep(CBaseStep * pFrom)
:CGeometric_representation_itemStep(pFrom)
{
  nameClass("Solid_model");
}

CSolid_modelStep::~CSolid_modelStep()
{

}

void CSolid_modelStep::Serialize(stepArchive &ar)
{
  try{
    if (!isSerialized()){
      setSerialized();
    }
  }
  catch(...){
    ar << "\n/*Errors detected in CPlacementStep::Serialize #\n";
//  ar << getNum();
    ar <<   ", but continuing*/\n" ;    
      setSerialized();
  }
}

HRESULT CSolid_modelStep::backPtr(CBaseStep *&prBrep)
{
  prBrep = NULL;  
  return S_OK;
}

//////////////////////////////////////////////////////////
// who  date      history

bool CSolid_modelStep::CountReset()
{
  return   CBaseStep::CountReset();
}
