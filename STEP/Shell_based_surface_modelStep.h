// Faced_based_surface_modelStep.h: interface for the CShell_based_surface_modelStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_Shell_based_surface_modelStep_H__75FF9A63_19A9_11D5_BFFB_0004AC6EEF35__INCLUDED_)
#define AFX_Shell_based_surface_modelStep_H__75FF9A63_19A9_11D5_BFFB_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Geometric_representation_itemStep.h"

class CShell_based_surface_modelStep : public CGeometric_representation_itemStep  
{
public:
	CShell_based_surface_modelStep();
	virtual ~CShell_based_surface_modelStep();
  HRESULT backPtr( CBaseStep*& prBrep);

};

#endif // !defined(AFX_Shell_based_surface_modelStep_H__75FF9A63_19A9_11D5_BFFB_0004AC6EEF35__INCLUDED_)
