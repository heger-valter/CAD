// Cylindrical_surfaceStep.h: interface for the CCylindrical_surfaceStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CYLINDRICAL_SURFACESTEP_H__9830F383_26A2_11D5_8CAE_00D00908C1A5__INCLUDED_)
#define AFX_CYLINDRICAL_SURFACESTEP_H__9830F383_26A2_11D5_8CAE_00D00908C1A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Elementary_surfaceStep.h"

class CCylindrical_surfaceStep : public CElementary_surfaceStep  
{
public:
	HRESULT split(CVertexStep &rVertexStep0, CVertexStep &rVertexStep1);
	void Serialize( stepArchive &ar);
	CCylindrical_surfaceStep(double dRadius, CAxis2_placement_3dStep& rPos);
	virtual ~CCylindrical_surfaceStep();
  double m_dRadius;
  HRESULT backPtr( CBaseStep*& prBrep);
  HRESULT normal( CCartesian_pointStep *pCartesian_pointStep
    , CDirectionStep*& pNormalDirection);
};

#endif // !defined(AFX_CYLINDRICAL_SURFACESTEP_H__9830F383_26A2_11D5_8CAE_00D00908C1A5__INCLUDED_)
