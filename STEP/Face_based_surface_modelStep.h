// Face_based_surface_modelStep.h: interface for the CFace_based_surface_modelStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FACE_BASED_SURFACE_MODELSTEP_H__B4CEED61_25EB_11D5_8CAE_00D00908C1A5__INCLUDED_)
#define AFX_FACE_BASED_SURFACE_MODELSTEP_H__B4CEED61_25EB_11D5_8CAE_00D00908C1A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Geometric_representation_itemStep.h"

class CFace_based_surface_modelStep : public CGeometric_representation_itemStep  
{
public:
	CFace_based_surface_modelStep();
	virtual ~CFace_based_surface_modelStep();
//  HRESULT backPtr( CBaseStep*& prBrep);

};

#endif // !defined(AFX_FACE_BASED_SURFACE_MODELSTEP_H__B4CEED61_25EB_11D5_8CAE_00D00908C1A5__INCLUDED_)
