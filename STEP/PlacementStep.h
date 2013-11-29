// PlacementStep.h: interface for the CPlacement class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLACEMENT_H__9B2019D5_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_)
#define AFX_PLACEMENT_H__9B2019D5_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Geometric_representation_itemStep.h"
#include "pointStep.h"

class CPlacementStep : public CGeometric_representation_itemStep  
{
public:
	void fin();
	CCartesian_pointStep* m_pLocation;
	void Serialize( stepArchive &ar);
	CPlacementStep( CCartesian_pointStep* pLocation);
	virtual ~CPlacementStep();
  HRESULT backPtr( CBaseStep*& prBrep);

};
//////////////////////////////////////////////////////////
// who  date      history

#endif // !defined(AFX_PLACEMENT_H__9B2019D5_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_)
