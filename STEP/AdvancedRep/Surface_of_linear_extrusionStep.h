// Surface_of_linear_extrusionStep.h: interface for the CSurface_of_linear_extrusionStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SURFACE_OF_LINEAR_EXTRUSIONSTEP_H__D0F09601_261E_11D5_9EA8_E8C9DCC61937__INCLUDED_)
#define AFX_SURFACE_OF_LINEAR_EXTRUSIONSTEP_H__D0F09601_261E_11D5_9EA8_E8C9DCC61937__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Swept_surfaceStep.h"

class CSurface_of_linear_extrusionStep : public CSwept_surfaceStep  
{
public:
	CSurface_of_linear_extrusionStep();
	virtual ~CSurface_of_linear_extrusionStep();
  HRESULT backPtr( CBaseStep*& prBrep);

};

#endif // !defined(AFX_SURFACE_OF_LINEAR_EXTRUSIONSTEP_H__D0F09601_261E_11D5_9EA8_E8C9DCC61937__INCLUDED_)
