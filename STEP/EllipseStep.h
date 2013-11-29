// EllipseStep.h: interface for the CEllipseStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ELLIPSESTEP_H__5D5B1684_25FA_11D5_9EA8_E8C9DCC61937__INCLUDED_)
#define AFX_ELLIPSESTEP_H__5D5B1684_25FA_11D5_9EA8_E8C9DCC61937__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ConicStep.h"

class CEllipseStep : public CConicStep  
{
public:
	CEllipseStep();
	virtual ~CEllipseStep();
  HRESULT backPtr( CBaseStep*& prBrep);

};

#endif // !defined(AFX_ELLIPSESTEP_H__5D5B1684_25FA_11D5_9EA8_E8C9DCC61937__INCLUDED_)
