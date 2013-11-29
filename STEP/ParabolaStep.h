// ParabolaStep.h: interface for the CParabolaStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARABOLASTEP_H__5D5B1686_25FA_11D5_9EA8_E8C9DCC61937__INCLUDED_)
#define AFX_PARABOLASTEP_H__5D5B1686_25FA_11D5_9EA8_E8C9DCC61937__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ConicStep.h"

class CParabolaStep : public CConicStep  
{
public:
	CParabolaStep();
	virtual ~CParabolaStep();
  HRESULT backPtr( CBaseStep*& prBrep);

};

#endif // !defined(AFX_PARABOLASTEP_H__5D5B1686_25FA_11D5_9EA8_E8C9DCC61937__INCLUDED_)
