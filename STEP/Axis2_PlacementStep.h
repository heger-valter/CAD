// Axis2_PlacementStep.h: interface for the CAxis2_PlacementStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AXIS2_PLACEMENTSTEP_H__2FAC22A3_17EA_11D5_BFF9_0004AC6EEF35__INCLUDED_)
#define AFX_AXIS2_PLACEMENTSTEP_H__2FAC22A3_17EA_11D5_BFF9_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PlacementStep.h"

// finish doing this class

class CAxis2_PlacementStep 
: public CPlacementStep
{
  CCartesian_pointStep& m_rLocation;
public:
	CAxis2_PlacementStep(CCartesian_pointStep* pLocation);
	virtual ~CAxis2_PlacementStep();

};

#endif // !defined(AFX_AXIS2_PLACEMENTSTEP_H__2FAC22A3_17EA_11D5_BFF9_0004AC6EEF35__INCLUDED_)
