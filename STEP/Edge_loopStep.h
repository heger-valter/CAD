// Edge_loopStep.h: interface for the CEdge_loopStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EDGE_LOOPSTEP_H__D5082341_1258_11D5_8CAE_00D00908C1A5__INCLUDED_)
#define AFX_EDGE_LOOPSTEP_H__D5082341_1258_11D5_8CAE_00D00908C1A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include <STDDEF.H>

#undef string

//class CPathStep;
//class CLoopStep;
#include "PathStep.h"
#include "loopStep.h"

class CEdge_loopStep :    
                                  public CLoopStep
//                              ,
//                                public CPathStep
{
  CPathStep m_pathStep;// modeled has-a relationship until I get my mind back
public:
	void AddPoint(CCartesian_pointStep *newElement);
	void InsertAtPoint(int nIndex, CCartesian_pointStep *newElement, int nCount = 1);
	t_aEdge_list& GetEdge_list(void);
	CEdge_loopStep(  );
	virtual ~CEdge_loopStep();
	int Add(COriented_edgeStep* newElement);
	void SetSize(int nNewSize, int nGrowBy = -1);
	void InsertAt(int nIndex, COriented_edgeStep* newElement, int nCount = 1);
	void RemoveAt(int nIndex, int nCount = 1);
	HRESULT split(CVertexStep& rVertexStep
    , COriented_edgeStep*  pOriented_edgeStep0
    );
	void fin();
	void Serialize( stepArchive &ar);
	void* ne();
  HRESULT backPtr( CBaseStep*& prBrep);
	
//void PASCAL operator delete(unsigned int nSize, const char * pszFileName, int nLine);
//void PASCAL operator delete(void* p);

//void* __stdcall operator new(unsigned int nSize, const char * pszFileName, int nLine);
//void* PASCAL operator new(unsigned int nSize, const char * pszFileName, int nLine);
//void* __stdcall operator new(size_t nSize, LPCSTR lpszFileName, int nLine);
	int GetSize();

  // hack for now
	COriented_edgeStep* GetAt(int i);
  HRESULT outerloopContainment( CDirectionStep         *pFaceNormal 
                                     , CEdge_loopStep         *pInner_boundPoints    
                                     , boundsIntersectBounds  &rBoundsXbounds
                                     );
  bool m_bGap;
	void SetAt( int i, COriented_edgeStep *pP);
	HRESULT simplify();
	HRESULT contains( CCartesian_pointStep*   pIntersectionPts 
                  , unsigned char          &bitContainment
                  , CDirectionStep         *pFaceLeft
                  );
};

class CEdge_loopStepEx : public CEdge_loopStep
{
public:
	CEdge_loopStepEx();
	virtual ~CEdge_loopStepEx();
	void move( COriented_edgeStep*      pLoopIntersectionPoint);
	HRESULT sortIntersectionsCCW( 
                                CrcPtrArray*      pLoopIntersectionPoints , 
                                CPlaneStep*       pPlaneStepOnNegFeature, 
                                CPlaneStep*       pPlaneStepOnPosFeature, 
                                bool&             bBackward
                              , const bool        bOrientation = false
    );
};

#endif // !defined(AFX_EDGE_LOOPSTEP_H__D5082341_1258_11D5_8CAE_00D00908C1A5__INCLUDED_)

//////////////////////////////////////////////////////////
// who  date      history
// wh   10/08/01  problems with multiple inheritance
// 
//////////////////////////////////////////////////////////

