// Conical_surfaceStep.h: interface for the CConical_surfaceStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONICAL_SURFACESTEP_H__B4CEED62_25EB_11D5_8CAE_00D00908C1A5__INCLUDED_)
#define AFX_CONICAL_SURFACESTEP_H__B4CEED62_25EB_11D5_8CAE_00D00908C1A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Elementary_surfaceStep.h"

class CConical_surfaceStep : public CElementary_surfaceStep  
{
public:
	CConical_surfaceStep( CAxis2_placement_3dStep& rPos,double semi_angle,
                        double radius);
	virtual ~CConical_surfaceStep();
  double m_dSemi_angle;
  double m_dRadius;
  HRESULT backPtr( CBaseStep*& prBrep);
};

#endif // !defined(AFX_CONICAL_SURFACESTEP_H__B4CEED62_25EB_11D5_8CAE_00D00908C1A5__INCLUDED_)
