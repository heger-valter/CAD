// ConicStep.h: interface for the CConicStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONICSTEP_H__28EC6D61_1BA3_11D5_9EA8_CE11C5190036__INCLUDED_)
#define AFX_CONICSTEP_H__28EC6D61_1BA3_11D5_9EA8_CE11C5190036__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CurveStep.h"
#include "PlacementStep.h"

class CConicStep : public CCurveStep  
{
public:
	CConicStep( CPlacementStep& m_rPosition);
	virtual ~CConicStep();
	CPlacementStep& m_rPosition;
  HRESULT backPtr( CBaseStep*& prBrep);
};

#endif // !defined(AFX_CONICSTEP_H__28EC6D61_1BA3_11D5_9EA8_CE11C5190036__INCLUDED_)
