// Manifold_solid_brepStep.h: interface for the CManifold_solid_rep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MANIFOLD_SOLID_bREP_H__9B2019D9_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_)
#define AFX_MANIFOLD_SOLID_bREP_H__9B2019D9_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CClosed_shellStep;
#include "Solid_modelStep.h"
#include "EulerCntAgito.h"

class CManifold_solid_brepStep: public CSolid_modelStep 
{
public:
	CManifold_solid_brepStep( CBaseStep*pIn, CClosed_shellStep*p_outer);
	virtual ~CManifold_solid_brepStep();
	CClosed_shellStep* m_pShell;// not used wh 6/23/01
	void Serialize( stepArchive &ar);
//  virtual 
    CEulerCntAgito eulerCnt;
  HRESULT backPtr( CBaseStep*& prBrep);
};
//////////////////////////////////////////////////////////
// who  date      history

#endif // !defined(AFX_MANIFOLD_SOLID_bREP_H__9B2019D9_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_)
