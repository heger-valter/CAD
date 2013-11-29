// Faceted_brepStep.h: interface for the CBaseStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CFaceted_brepStep_H__177869E1_09A6_11D5_BFED_0004AC6EEF35__INCLUDED_)
#define AFX_CFaceted_brepStep_H__177869E1_09A6_11D5_BFED_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afx.h>
#include "stepArchive.h"
#include "Manifold_solid_brepStep.h"
#include "Representation_contextStep.h"
#include "Geometric_Representation_contextStep.h"
#include "shape_representationStep.h"
#include "EulerCntAgito.h"

extern const char* szEndl;
class step;

class CFaceted_brepStep : public CManifold_solid_brepStep
{
  friend class CBaseStep;
public:   
	HRESULT backPtr(CBaseStep *&prBrep);
	         CFaceted_brepStep(CClosed_shellStep*pIn);
	virtual ~CFaceted_brepStep();
      void Serialize( stepArchive &ar);
//  CEulerCntAgito eulerCnt;
};

//////////////////////////////////////////////////////////
// who  date      history


#endif // !defined(AFX_CFaceted_brepStep_H__177869E1_09A6_11D5_BFED_0004AC6EEF35__INCLUDED_)
