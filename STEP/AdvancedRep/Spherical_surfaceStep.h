// Spherical_surfaceStep.h: interface for the CSpherical_surfaceStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPHERICAL_SURFACESTEP_H__5D5B1689_25FA_11D5_9EA8_E8C9DCC61937__INCLUDED_)
#define AFX_SPHERICAL_SURFACESTEP_H__5D5B1689_25FA_11D5_9EA8_E8C9DCC61937__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Elementary_surfaceStep.h"

class CSpherical_surfaceStep : public CElementary_surfaceStep  
{
public:
	CSpherical_surfaceStep();
	virtual ~CSpherical_surfaceStep();
  HRESULT backPtr( CBaseStep*& prBrep);

};

#endif // !defined(AFX_SPHERICAL_SURFACESTEP_H__5D5B1689_25FA_11D5_9EA8_E8C9DCC61937__INCLUDED_)
