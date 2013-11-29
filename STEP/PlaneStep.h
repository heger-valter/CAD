// PlaneStep.h: interface for the CPlaneStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_Plane_SURFACE_H__9B2019DD_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_)
#define AFX_Plane_SURFACE_H__9B2019DD_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Elementary_surfaceStep.h"
#include "SurfaceStep.h"
#include "stepArchive.h"
#include "Axis2_Placement_3dStep.h"


class CPlaneStep: public CElementary_surfaceStep
{
public:   
  CPlaneStep(CAxis2_placement_3dStep* pPos);
	virtual ~CPlaneStep();
	HRESULT validate(void);
	HRESULT negate(void);
	HRESULT intersect( CLineStep*         pLine,
                     intersectionType&  eIntersect, // out, classification of the type of intersection, endpoint intersections are relative to l1
                     CrcPtrArray*       pPointXs ,         // out, intersection points
                     double&            paramU,               // out, intersection u parameter on plane
                     double&            paramV,               // out, intersection v parameter on plane
                     double             paramT[2]);

	bool onSurface( CCartesian_pointStep& rPoint);
	void fin();
  void Serialize( stepArchive &ar);
  HRESULT backPtr( CBaseStep*& prBrep);
  virtual HRESULT normal( CCartesian_pointStep *pCartesian_pointStep
    , CDirectionStep*& pNormalDirection);
};

//////////////////////////////////////////////////////////
// who  date      history

#endif // !defined(AFX_Plane_SURFACE_H__9B2019DD_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_)
