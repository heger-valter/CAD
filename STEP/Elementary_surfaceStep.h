// Elementary_surfaceStep.h: interface for the CElementary_surface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ELEMENTARY_SURFACE_H__9B2019DD_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_)
#define AFX_ELEMENTARY_SURFACE_H__9B2019DD_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SurfaceStep.h"
#include "stepArchive.h"
#include "Axis2_Placement_3dStep.h"
//class Axis2_Placement_3dStep;

class CElementary_surfaceStep : public CSurfaceStep  
{
public:
	CElementary_surfaceStep( CAxis2_placement_3dStep* pPos);
	virtual ~CElementary_surfaceStep();
	HRESULT validate(void);
	HRESULT negate(void);
	void fin();
	CAxis2_placement_3dStep* m_pPosition;
  HRESULT backPtr( CBaseStep*& prBrep);
};

//////////////////////////////////////////////////////////
// who  date      history

#endif // !defined(AFX_ELEMENTARY_SURFACE_H__9B2019DD_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_)
