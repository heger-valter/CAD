// Advanced_faceStep.h: interface for the CFace_surfaceStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_Advanced_faceStepStep_H__9F9D4C73_0C2F_11D5_BFEF_0004AC6EEF35__INCLUDED_)
#define AFX_Advanced_faceStepStep_H__9F9D4C73_0C2F_11D5_BFEF_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "afx.h"
#include "FaceStep.h"
#include "Topological_representation_itemStep.h"
#include "SurfaceStep.h"

#include "stepArchive.h"


class CFace_boundStep;
class CFace_outer_boundStep;
class CCartesian_pointStep;

class CAdvanced_faceStep : public CFaceStep 
{
public:
	CAdvanced_faceStep (CBaseStep * pFrom, 
                      CFace_boundStep* p_face_bound, 
                      bool same_sense=true
                      , int iNumFB=1
                      );
	virtual ~CAdvanced_faceStep ();
	void Serialize( stepArchive &ar);
  bool m_bSame_sense;
  CSurfaceStep* m_pFace_geometry;
  HRESULT backPtr( CBaseStep*& prBrep);
	HRESULT AddFB( CFace_boundStep *p_face_bound
    , int &ri);
  virtual HRESULT contains( CCartesian_pointStep* pPoint
                          , containment& bContains
                          , double &              rdParam
                          );
	HRESULT trimEdge( CrcPtrArray *pIntersectionPts 
    , paramPtrArray& intersectionEdge
    , containment& bContains
    );
};

//////////////////////////////////////////////////////////
// who  date      history
// wh   10/22/01  face_surface::split does not return another face_surface
	
#endif // !defined(AFX_Advanced_faceStepStep_H__9F9D4C73_0C2F_11D5_BFEF_0004AC6EEF35__INCLUDED_)
