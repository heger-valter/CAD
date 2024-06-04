// HyperbolaStep.h: interface for the CHyperbolaStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HYPERBOLASTEP_H__5D5B1685_25FA_11D5_9EA8_E8C9DCC61937__INCLUDED_)
#define AFX_HYPERBOLASTEP_H__5D5B1685_25FA_11D5_9EA8_E8C9DCC61937__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ConicStep.h"

class CHyperbolaStep : public CConicStep  
{
public:
	CHyperbolaStep();
	virtual ~CHyperbolaStep();
  HRESULT backPtr( CBaseStep*& prBrep);

};

#endif // !defined(AFX_HYPERBOLASTEP_H__5D5B1685_25FA_11D5_9EA8_E8C9DCC61937__INCLUDED_)
