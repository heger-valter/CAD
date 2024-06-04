// AssemblyStep.h: interface for the CAssemblyStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASSEMBLYSTEP_H__6B3F8743_195D_11D5_BFFA_0004AC6EEF35__INCLUDED_)
#define AFX_ASSEMBLYSTEP_H__6B3F8743_195D_11D5_BFFA_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Geometric_representation_itemStep.h"

class CModel;
class CAssemblyStep : public CGeometric_representation_itemStep  
{
  CPtrArray* mp_aModels;
public:
	bool SetAt( int im, CModel* pModel );
	CAssemblyStep(CModel* pModel, int iNumParts=1);
	virtual ~CAssemblyStep();

};

#endif // !defined(AFX_ASSEMBLYSTEP_H__6B3F8743_195D_11D5_BFFA_0004AC6EEF35__INCLUDED_)
