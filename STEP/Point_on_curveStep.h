// Point_on_curveStep.h: interface for the CPoint_on_curveStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POINT_ON_CURVESTEP_H__5D5B1681_25FA_11D5_9EA8_E8C9DCC61937__INCLUDED_)
#define AFX_POINT_ON_CURVESTEP_H__5D5B1681_25FA_11D5_9EA8_E8C9DCC61937__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PointStep.h"

class CPoint_on_curveStep : public CPointStep  
{
public:
	CPoint_on_curveStep();
	virtual ~CPoint_on_curveStep();
  HRESULT backPtr( CBaseStep*& prBrep);

};

#endif // !defined(AFX_POINT_ON_CURVESTEP_H__5D5B1681_25FA_11D5_9EA8_E8C9DCC61937__INCLUDED_)
