// Toroidal_surfaceStep.h: interface for the CToroidal_surfaceStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOROIDAL_SURFACESTEP_H__5D5B168A_25FA_11D5_9EA8_E8C9DCC61937__INCLUDED_)
#define AFX_TOROIDAL_SURFACESTEP_H__5D5B168A_25FA_11D5_9EA8_E8C9DCC61937__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Elementary_surfaceStep.h"

class CToroidal_surfaceStep : public CElementary_surfaceStep  
{
public:
	CToroidal_surfaceStep();
	virtual ~CToroidal_surfaceStep();
  HRESULT backPtr( CBaseStep*& prBrep);

};

#endif // !defined(AFX_TOROIDAL_SURFACESTEP_H__5D5B168A_25FA_11D5_9EA8_E8C9DCC61937__INCLUDED_)
