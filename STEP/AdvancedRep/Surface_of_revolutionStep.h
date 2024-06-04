// Surface_of_revolutionStep.h: interface for the CSurface_of_revolutionStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SURFACE_OF_REVOLUTIONSTEP_H__D0F09602_261E_11D5_9EA8_E8C9DCC61937__INCLUDED_)
#define AFX_SURFACE_OF_REVOLUTIONSTEP_H__D0F09602_261E_11D5_9EA8_E8C9DCC61937__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Swept_surfaceStep.h"

class CSurface_of_revolutionStep : public CSwept_surfaceStep  
{
public:
	CSurface_of_revolutionStep();
	virtual ~CSurface_of_revolutionStep();
  HRESULT backPtr( CBaseStep*& prBrep );

};

#endif // !defined(AFX_SURFACE_OF_REVOLUTIONSTEP_H__D0F09602_261E_11D5_9EA8_E8C9DCC61937__INCLUDED_)
