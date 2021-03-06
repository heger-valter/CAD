// AssemblyStep.cpp: implementation of the CAssemblyStep class.
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
#include "scribble.h"
#include "AssemblyStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAssemblyStep::CAssemblyStep(CModel* pModel, int iNumParts)
: CGeometric_representation_itemStep(NULL)
{
  nameClass("next_assembly_usage_occurance");
  mp_aModels = new CPtrArray();
  mp_aModels->SetSize(iNumParts);
  mp_aModels->SetAt(0, pModel);
}

CAssemblyStep::~CAssemblyStep()
{
  delete mp_aModels;
  mp_aModels=NULL;
}

bool CAssemblyStep::SetAt(int im, CModel *pModel)
{
  mp_aModels->SetAt(im, pModel);
  return false;
}
