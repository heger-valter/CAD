// CircleStep.h: interface for the CCircleStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CIRCLESTEP_H__5D5B1683_25FA_11D5_9EA8_E8C9DCC61937__INCLUDED_)
#define AFX_CIRCLESTEP_H__5D5B1683_25FA_11D5_9EA8_E8C9DCC61937__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPlacementStep;

#include "ConicStep.h"

class CCircleStep : public CConicStep  
{
  double m_dRadius;
public:
	CCircleStep( CPlacementStep& rPosition, double dRadius);
	virtual ~CCircleStep();
	void Serialize(stepArchive &ar);
  HRESULT backPtr( CBaseStep*& prBrep);
};

//////////////////////////////////////////////////////////
// who  date      history
// wh   11/19/01  use CPlacementStep instead of select CAxis2_placement_Step

#endif // !defined(AFX_CIRCLESTEP_H__5D5B1683_25FA_11D5_9EA8_E8C9DCC61937__INCLUDED_)
