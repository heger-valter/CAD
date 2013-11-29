// FaceStep.h: interface for the CFaceStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FACESTEP_H__9F9D4C73_0C2F_11D5_BFEF_0004AC6EEF35__INCLUDED_)
#define AFX_FACESTEP_H__9F9D4C73_0C2F_11D5_BFEF_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "afx.h"
#include "Topological_representation_itemStep.h"
#include "SurfaceStep.h"

#include "stepArchive.h"


class CFace_boundStep;
class CFace_outer_boundStep;
class CCartesian_pointStep;
//class CSurfaceStep;//CSurfaceStep

class CFaceStep : public CTopological_representation_itemStep  
{
protected:
//should have used an stl template as the data structure 
  CPtrArray m_bounds;//collection of CFace_boundStep and are ordered to be nested, 
public:
	int GetSize();
	CFace_outer_boundStep* GetFace_outer_bound();
	CFace_boundStep* GetAt(int i);
	HRESULT validate(void);
	HRESULT negate(void);
	void fin();
	CFaceStep(CBaseStep * pFrom, 
            CFace_boundStep* p_face_bound, 
            int iNumFB=1);
	virtual ~CFaceStep();
	int Add(CFace_boundStep* pfb);
	void Serialize( stepArchive &ar);
  CSurfaceStep* m_pSurfaceStep;//used instead of m_pParent 
  HRESULT backPtr(CBaseStep *&prBrep);
};

//////////////////////////////////////////////////////////
// who  date      history
// wh   10/22/01  face_surface::split does not return another face_surface
	
#endif // !defined(AFX_FACESTEP_H__9F9D4C73_0C2F_11D5_BFEF_0004AC6EEF35__INCLUDED_)
