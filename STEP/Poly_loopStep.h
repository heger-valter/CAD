// Poly_loopStep.h: interface for the CPoly_loopStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POLYLOOPSTEP_H__9B2019D8_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_)
#define AFX_POLYLOOPSTEP_H__9B2019D8_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class     CFace_surfaceStep;
class     CDirectionStep;
class     CFace_outer_boundStep;
class     CPlaneStep;
class     CCartesian_pointStep;

#include "afxcoll.h"
#include "LoopStep.h"
#include "PointStep.h"
#include "agitoPtrArray.h"

enum      containment;

// classification of bounds intersection, need to cover the cases, {ieo, i}, where i=inside, e = edge, o = outside
enum boundsIntersectBounds { unknownBoundsIntersection, // initial state
                             disjointBounds,            // bounds are disjoint farther apart than restol and seperable (there is a infinite length boundary segment which seperates them) ie %
                             outsideBounds,             // bounds are outside farther apart than restol, but containted (not seperable) @ 
                             commonVertexOutside,       // two interior non-overlapping faces share a common vertex
                             edgeScrapesOutside,        // two interior non-overlapping faces share a common edge
                             intersectionBounds,        // bounds intersect and cross over
                             edgeScrapesInside,         // two overlapping faces share a common edge
                             commonVertexInside,        // two overlapping faces share a common vertx
                             insideBounds};             // [outer]bound are completely within inner_bounds
// really should use a bit mask here, bit 0  indicates outside, bit 1 indicates intersection of vertex, bit 2 indicates 2 consecutive edge intersections, bit 3 indicates inside

class CPoly_loopStep : public CLoopStep
{  
friend class step;
friend class CFace_boundStep;
friend class CFace_surfaceStep;// wh 10/17/01
friend class CPoly_loopStepEx;
  CrcPtrArray m_aPolygonVertices;// all verticies are inserted in CCW order!  face_bound.orientation determines CW orientation

public:   
	int Find( CCartesian_pointStep* pP);
  HRESULT weed(int i);// weed out unnecessary edges
  HRESULT halfqi( CCartesian_pointStep   *pPt                                  
                , containment            &rbContains 
                , CDirectionStep         *pFaceLeft//pFaceLeft
                , double                  dGreatRadius2
                );
	void fin();
	void init();
	HRESULT replace( CPoly_loopStep *pPL);// replace with this one
//HRESULT merge( CPoly_loopStep *pPL);// merge with this one
	int GetSize();
	HRESULT mod_neg_feature( CrcPtrArray* pEdgeIntersectionPoints, int& iv);


  // constructor needs three points to define a polygon
  CPoly_loopStep( CPointStep*pIn0, 
                  CPointStep*pIn1, 
                  CPointStep*pIn2, 
                  int iSize=3);

  CPoly_loopStep( void );
	virtual ~CPoly_loopStep();
	HRESULT convexContains( CDirectionStep         *pLeft      ,
                          CCartesian_pointStep   *pPt,    
                          CCartesian_pointStep   *pOuterPoint, // on the outer bdry
                          containment            &rbContains 
                        , double &rdParam                    
                        );

	HRESULT contains( 
                    CCartesian_pointStep   *pPt
                  , containment            &rbContains 
                  , CDirectionStep         *pLeft      
                  , double &rdParam
                  );
	
  HRESULT outerloopContainmentFaceted( CDirectionStep         *pFaceNormal
                                     , CPtrArray              *pInner_boundPoints
                                     , boundsIntersectBounds  &rBoundsXbounds
                                     );
	
  HRESULT split( CrcPtrArray*       pIntersectionPts, // wh 10/18/01
                 CPoly_loopStep*&   rpNewPoly_loopStep , 
                 CFace_surfaceStep* pFace_surfaceStepOnPosFeature
                 );
	
  HRESULT split( CrcPtrArray*           pIntersectionPts 
               , CDirectionStep*        pAxis
               , CPoly_loopStep*        pPL2  
               );
	
  HRESULT trim( CrcPtrArray*           pIntersectionPts 
              , CDirectionStep*        pAxis
              );
  HRESULT trimEdge( CrcPtrArray*           pIntersectionPts 
                  , paramPtrArray&         intersectionEdge
                  , CDirectionStep*        pAxis
                  , containment&           bContains
                  );
  HRESULT validate(void
    );
	HRESULT simplify(void
    );
	HRESULT negate(void
    );
	CPointStep* GetAt(int i);
	bool SetAt( int i, CPointStep* pP);
  void Serialize( stepArchive &ar);
	HRESULT mergeVertex( CPoly_loopStep *& pPoly_loopStep );
//HRESULT mergeEdge  ( CPoly_loopStep *& pPoly_loopStep );
  bool m_bGap;// diag message, if a gap was encountered
  HRESULT backPtr( CBaseStep*& prBrep);
  CObArray lines;
  bool m_bLinesInit;
  CByteArray m_aLinesInit;

  HRESULT split( CrcPtrArray*           pIntersectionPts 
               , CDirectionStep*        pAxis
               , CPoly_loopStep*        pPL2  
               , bool&                  bFlipFob
               , bool&                  bFlipFob2
               );
	
	HRESULT contains( CrcPtrArray*           pIntersectionPts
                  , unsigned char          &bitContainment
                  , CDirectionStep         *pFaceLeft
                  );
	
  HRESULT splitAdd( CrcPtrArray*           pIntersectionPts 
               , CDirectionStep*        pAxis
               , CPoly_loopStep*        pPL2  
               , bool&                  bFlipFob
               , bool&                  bFlipFob2
               );
	

};

enum make_polyloopStepEx {
  make_polyloopStepExUnknown= 0, 
  make_polyloopStepExAdd    = 1, 
  make_polyloopStepExInsert =-1};

// auxilary class to manage m_aPolygonVertices when it is unknown if the dp is pos or neg
class CPoly_loopStepEx : public CPoly_loopStep
{  
public:
  double m_dpPrev;// if >0 each pair pts is inserted into list in order, if <0 pts are inserted into list backwards
  CPoly_loopStepEx( void );
	virtual ~CPoly_loopStepEx();
//CTypedPtrArray<CPtrArray, CCartesian_pointStep*> ptsToBeAdded;//make it a member variable
	HRESULT sortIntersectionsCW( 
                                CrcPtrArray*      pLoopIntersectionPoints , 
                                CPlaneStep*       pPlaneStepOnNegFeature, 
                                CPlaneStep*       pPlaneStepOnPosFeature, 
                                bool & bBackward
                              , const bool bOrientation = true
                              );
	HRESULT sortIntersectionsCCW( 
                                CrcPtrArray*      pLoopIntersectionPoints , 
                                CPlaneStep*       pPlaneStepOnNegFeature, 
                                CPlaneStep*       pPlaneStepOnPosFeature, 
                                bool & bBackward
                              , const bool bOrientation = false
                              );

  void move( CCartesian_pointStep*      pLoopIntersectionPoint);// move pts from ptsToBeAdded to m_aPolygonVertices
  void movePrev( CCartesian_pointStep*      pLoopIntersectionPoint);// move pts from ptsToBeAdded to m_aPolygonVertices
  make_polyloopStepEx m_dp;// is the loop formed by adding, inserting, or unknown
  CCartesian_pointStep* m_pLastMidPoint;
};

//////////////////////////////////////////////////////////
// who  date      history
// wh   01/24/02  properly classify and discard exterior surface loops
// wh   02/24/02  problem with gaps due to intersections of coplanar surfaces

#endif // !defined(AFX_POLYLOOPSTEP_H__9B2019D8_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_)
