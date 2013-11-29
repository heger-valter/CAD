// Face_boundStep.h: interface for the Face_boundStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FACE_BOUNDSTEP_H__D02DC4C4_0C3B_11D5_BFEF_0004AC6EEF35__INCLUDED_)
#define AFX_FACE_BOUNDSTEP_H__D02DC4C4_0C3B_11D5_BFEF_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLoopStep;
class CEdge_loopStep;
class CFace_outer_boundStep;// need for demotion
class CPoly_loopStep;
class CLoopStep;
class stepArchive;
enum containment;

#include "Topological_representation_itemStep.h"

// a face_bound is a loop whic is intended to be used for bounding a face
class CFace_boundStep : public CTopological_representation_itemStep  
{
public:
	CFace_boundStep( CBaseStep*       pFrom, // spawning entity
                   CLoopStep*       pBound=NULL, //
                   bool             bOrientation  = true// CCW
                   //, CEdge_loopStep*  pEdge_loopStep = NULL
                 );//
	virtual ~CFace_boundStep();

	HRESULT trim( CrcPtrArray*            pIntersectionPts, // list of intersection points
                CDirectionStep*         pAxis            // need to know which way is the surface normal
              );
	HRESULT trimEdge( CrcPtrArray*            pIntersectionPts // list of intersection points
                  , paramPtrArray&          intersectionEdge
                  , CDirectionStep*         pAxis            // need to know which way is the surface normal
                  , containment&            bContains
              );
	HRESULT convexContains( CCartesian_pointStep* pPt,    // in,  pt being tested for containment
                          containment &         bContains,       // out, classification of containment
                          CDirectionStep*       pFaceNormal
                        , double&               rdParam                    
                        ); // in,  face normal of which face
	HRESULT contains( CCartesian_pointStep *pPt,    // in,  pt being tested for containment
                    containment &         bContains,       // out, classification of containment
                    CDirectionStep*       pFaceUp
                  , double &              rdParam                    
                  ); // in,  face normal of which face
	HRESULT promote( void);
	virtual HRESULT split( CrcPtrArray *      pIntersectionPts, 
                         CPoly_loopStep *&  pNewPoly_loopStep, 
                         CFace_surfaceStep *pFace_surfaceStepOnPosFeature);
	HRESULT validate( void);
	HRESULT negate( void);
	CFace_boundStep( CFace_outer_boundStep& rFace_outer_boundStep);
	CLoopStep* m_bound;

  // when assigning the orientation do it so that matter is always on the left, void on the right
	bool m_bOrientation;// CCW=true
	void Serialize( stepArchive &ar);
  CLoopStep* GetBound(int i){
    return m_bound;
  };
	virtual HRESULT split(  CrcPtrArray *     pIntersectionPts, 
                          CDirectionStep*   pAxis,
                          CFace_boundStep*  pFOB2
                        );
  HRESULT backPtr( CBaseStep*& prBrep);
/*
	virtual HRESULT split( CrcPtrArray *pIntersectionPts
                        , CDirectionStep* pAxis
                        , CFace_boundStep*  pFOB2
                        );
*/
  bool m_bEnabled;// is bound currently not suppressed (because brep represents void or antimatter)
	virtual HRESULT splitAdd(  CrcPtrArray *     pIntersectionPts, 
                          CDirectionStep*   pAxis,
                          CFace_boundStep*  pFOB2
                        );
};

// a face_outer_loop is a special subtype of face_bound which 
//  carries the additional semanitcs of defining an outer boundary on the face.  
// No more than one boundary of a face shall be of this type
class CFace_outer_boundStep: public CFace_boundStep
{
  
public:   
	void fin(
    );
  CFace_outer_boundStep( CBaseStep*       pIn, 
                         CLoopStep*       pLoopStep      = NULL, 
                         bool             bOrientation   = true
                    // , CEdge_loopStep * pEdge_loopStep = NULL
                       ); 
	virtual ~CFace_outer_boundStep();
  void Serialize( stepArchive &ar);
  HRESULT backPtr( CBaseStep*& prBrep);
};

//////////////////////////////////////////////////////////
// who  date      history
// wh   01/24/02  properly classify and discard exterior surface loops
// wh   02/06/02  m_bEnabled added to allow suppressing of irrelavant bounds



#endif // !defined(AFX_FACE_BOUNDSTEP_H__D02DC4C4_0C3B_11D5_BFEF_0004AC6EEF35__INCLUDED_)
