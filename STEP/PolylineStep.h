// PolylineStep.h: interface for the CPolylineStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POLYLINESTEP_H__29D7A082_381A_11D5_8CAE_00D00908C1A5__INCLUDED_)
#define AFX_POLYLINESTEP_H__29D7A082_381A_11D5_8CAE_00D00908C1A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Bounded_curveStep.h"
#include "afxcoll.h"

class CPolylineStep : public CBounded_curveStep  
{
public:
	bool Add(CPoint x);
	void Serialize(stepArchive &ar);
	CPolylineStep();
	virtual ~CPolylineStep();
  CPtrArray points;
  HRESULT backPtr( CBaseStep*& prBrep);
};

#endif // !defined(AFX_POLYLINESTEP_H__29D7A082_381A_11D5_8CAE_00D00908C1A5__INCLUDED_)
