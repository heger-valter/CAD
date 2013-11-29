// GeometricRepresentation_contextStep.cpp: implementation of the CGeometricRepresentation_contextStep class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stepArchive.h"
#include "Geometric_representation_contextStep.h"
#include "baseStep.h"//extern enum shellStepSelect;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//int CGeometric_representation_contextStep::m_iDim;

CGeometric_representation_contextStep::CGeometric_representation_contextStep( CBaseStep*pIn)
: CRepresentation_contextStep(pIn)
{
  m_iDim=3;
  nameClass("GEOMETRIC_REPRESENTATION_CONTEXT");
}

CGeometric_representation_contextStep::~CGeometric_representation_contextStep()
{

}

bool CGeometric_representation_contextStep::writeDim( stepArchive &ar)
{
  ar << m_iDim;
  return false;
}

HRESULT CGeometric_representation_contextStep::backPtr(CBaseStep *&prBrep)
{
  prBrep = NULL;  
  return S_OK;
}
void CGeometric_representation_contextStep::Serialize( stepArchive &ar)
{
  try{
    if (!isSerialized()){
      setSerialized();
      ar.setEntry( getNum());
#if 0
      writePre( ar);
#else
      ar << "#" ;
      ar << getNum();
      ar <<   " = (";
      ar << m_szTheClass;
#endif

      ar <<   " (" ;
      writeDim( ar);
      ar <<   ")" ;

      ar << szEndl;
        ar <<   "   GLOBAL_UNCERTAINTY_ASSIGNED_CONTEXT ((#300)) " ;
        ar << szEndl;
        ar <<   "   GLOBAL_UNIT_ASSIGNED_CONTEXT ((#240, #280, #290)) " ;
        ar << szEndl;
      ar <<   "   REPRESENTATION_CONTEXT ('', '') " ;
      ar << szEndl;

      writePost( ar);
    }
  }
  catch(...){
    ar << "\n/*Errors detected in CGeometric_representation_contextStep::Serialize #\n";
    ar << getNum();
    ar <<   ", but continuing*/\n" ;    
    setSerialized();
  }
}

bool CGeometric_representation_contextStep::writePre(stepArchive &ar)
{
  ar.setEntry( getNum());
  ar << "#" ;
  ar << getNum();
  ar <<   " = (";
  ar << m_szTheClass;
  return false;
}
