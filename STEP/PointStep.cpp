// PointStep.cpp: implementation of the CPointStep class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "scribVw.h"
#include "PointStep.h"
#include "stepArchive.h"
#include "math.h"//large
#include "Cartesian_tranformation_operator_3dStep.h"
#include "VectorStep.h"
#include <FLOAT.H>// DBL_MAX, FLT_MAX

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPointStep::CPointStep(CBaseStep*pIn)
: CGeometric_representation_itemStep(pIn)
{
  nameClass("POINT");
}

CPointStep::~CPointStep()
{

}

HRESULT CPointStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  return E_FAIL;
}

void CPointStep::Serialize(stepArchive &ar)
{
  try{
    if (!isSerialized()){
      setSerialized();
      writePre(ar);
  //  ar <<"'', ";
      writePost(ar);
    }
  }
  catch(...){
      setSerialized();
    ar << "\n/*Errors detected in CPointStep::Serialize #\n";
//  ar << getNum();
    ar <<   ", but continuing*/\n" ;    
  }
}

//////////////////////////////////////////////////////////
// who  date      history
// wh   09/17/01  assert only once
// wh   11/13/01  CCartesian_pointStepPtrArray::Find, Add

