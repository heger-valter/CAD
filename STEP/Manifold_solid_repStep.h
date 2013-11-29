// Manifold_solid_repStep.h: interface for the CManifold_solid_rep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MANIFOLD_SOLID_REP_H__9B2019D9_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_)
#define AFX_MANIFOLD_SOLID_REP_H__9B2019D9_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Solid_modelStep.h"
//#include "Faceted_brepStep.h"	// Added by ClassView
class CClosed_shellStep;

class CManifold_solid_repStep: public CSolid_modelStep 
{
public:
	CClosed_shellStep* mp_outer;
	void Serialize( stepArchive &ar);
	CManifold_solid_repStep(CBaseStep*pIn, CClosed_shellStep*p_outer);
	virtual ~CManifold_solid_repStep();

};

#endif // !defined(AFX_MANIFOLD_SOLID_REP_H__9B2019D9_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_)
