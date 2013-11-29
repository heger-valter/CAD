// Bounded_curveStep.h: interface for the CBounded_curveStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOUNDED_CURVESTEP_H__29D7A081_381A_11D5_8CAE_00D00908C1A5__INCLUDED_)
#define AFX_BOUNDED_CURVESTEP_H__29D7A081_381A_11D5_8CAE_00D00908C1A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CurveStep.h"
#include "stepArchive.h"

class CBounded_curveStep : public CCurveStep  
{
public:
	void Serialize(stepArchive &ar);
	CBounded_curveStep();
	virtual ~CBounded_curveStep();

};

#endif // !defined(AFX_BOUNDED_CURVESTEP_H__29D7A081_381A_11D5_8CAE_00D00908C1A5__INCLUDED_)
