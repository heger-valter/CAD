// Face_surfaceStep.h: interface for the CFace_surfaceStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_Face_surfaceStep_H__9F9D4C73_0C2F_11D5_BFEF_0004AC6EEF35__INCLUDED_)
#define AFX_Face_surfaceStep_H__9F9D4C73_0C2F_11D5_BFEF_0004AC6EEF35__INCLUDED_

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

class CFace_surfaceStep: public CFaceStep 
{
public:
  CFace_surfaceStep( CSurfaceStep*pIn, 
                     CFace_boundStep* p_face_bound, 
                     bool same_sense);
	virtual ~CFace_surfaceStep();
  bool m_bSame_sense;
  CSurfaceStep* m_pFace_geometry;
public:   
	HRESULT trim( CrcPtrArray *pIntersectionPts );
	HRESULT trimEdge( CrcPtrArray *pIntersectionPts 
    , paramPtrArray& intersectionEdge
    , containment& bContains
    );
	HRESULT mod_neg_feature( CrcPtrArray*    pEdgeIntersectionPoints
    , int& rIv
    , CPoly_loopStep*  pPLoop 
    );
  virtual HRESULT contains( CCartesian_pointStep* pPoint
                          , containment& bContains
                          , double &              rdParam
                          );
	HRESULT contains( CCartesian_pointStep* pPt
                  , containment &         bContains
                  , CDirectionStep*       pFaceUp
                  , double &              rdParam
                  );
	HRESULT convexContains( CCartesian_pointStep* pPt
                        , containment &         bContains
                        , CDirectionStep*       pFaceNormal
                        , double &              rdParam                    
                        );
	HRESULT split( CrcPtrArray *        pIntersectionPts, 
                 CFace_surfaceStep*&  rpFace_surfaceStep, 
                 CFace_surfaceStep *  pFace_surfaceStepOnPosFeature);
	HRESULT validate( void);
	void fin( );
  void Serialize( stepArchive &ar);
	HRESULT negate( void);
	HRESULT split( CrcPtrArray *         pIntersectionPts);
  HRESULT backPtr( CBaseStep*& prBrep);
  bool writeNtuple( stepArchive &ar, CPtrArray*pList
    , int iSize );
	HRESULT makeIslands( CPoly_loopStep*& pPoly_loopStep );
	HRESULT AddFB( CFace_boundStep *p_face_bound
    , int &ri);
	HRESULT splitAdd( CrcPtrArray *         pIntersectionPts
    );
};

//////////////////////////////////////////////////////////
// who  date      history
// wh   10/22/01  face_surface::split does not return another face_surface
	
#endif // !defined(AFX_Face_surfaceStep_H__9F9D4C73_0C2F_11D5_BFEF_0004AC6EEF35__INCLUDED_)
