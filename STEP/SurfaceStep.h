// SurfaceStep.h: interface for the CSurfaceStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SURFACESTEP_H__9B2019DF_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_)
#define AFX_SURFACESTEP_H__9B2019DF_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Geometric_representation_itemStep.h"

class CSurfaceStep : public CGeometric_representation_itemStep  
{
public:
	void Serialize( stepArchive &ar);
	CSurfaceStep(CBaseStep*pIn);
	virtual ~CSurfaceStep();
  HRESULT backPtr( CBaseStep*& prBrep);
  virtual HRESULT normal( CCartesian_pointStep *pCartesian_pointStep
    , CDirectionStep*& pNormalDirection);
  // not a part of Step, just a necessary attribute!!!
//	CPtrArray aCoincidentCollection;// keep a list of those Surfaces which are coincident to you!!
};
//////////////////////////////////////////////////////////
// who  date      history

#endif // !defined(AFX_SURFACESTEP_H__9B2019DF_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_)
