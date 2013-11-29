// VertexStep.h: interface for the CVertexStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VERTEXSTEP_H__9F9D4C74_0C2F_11D5_BFEF_0004AC6EEF35__INCLUDED_)
#define AFX_VERTEXSTEP_H__9F9D4C74_0C2F_11D5_BFEF_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stepArchive.h"
#include "Topological_representation_itemStep.h"
#include "PointStep.h"

class CVertexStep : public CTopological_representation_itemStep
{
public:
	void Serialize( stepArchive &ar);
	CVertexStep(CBaseStep * pFrom);
	virtual ~CVertexStep();
  HRESULT backPtr( CBaseStep*& prBrep);
};

// a vertex_point is a vertex with its geometry defined at a point
class CVertex_pointStep: public CVertexStep
{
public:
  CVertex_pointStep( 
      CPointStep& r_vertex_geometry
    );
	virtual ~CVertex_pointStep();
  
  CPointStep* m_p_vertex_geometry;

public:   
  void Serialize( stepArchive &ar);
  HRESULT backPtr( CBaseStep*& prBrep);
};

class CVertex_pointStepPtrArray : public CPtrArray
{
  friend step;
  friend class stepAdvanced;
  friend class stepFaceted;
  CCartesian_pointStepPtrArray& m_rCartesian_pointStepPtrArray;
public:   
  CVertex_pointStepPtrArray(CCartesian_pointStepPtrArray& rCartesian_pointStepPtrArray);
  virtual ~CVertex_pointStepPtrArray(void);
  int SetAt(int nIndex, CVertex_pointStep* newElement);
  CVertex_pointStep* GetAt(int nIndex);
	  CCartesian_pointStep* find(CPointStep* pPoint);
};


//////////////////////////////////////////////////////////
// who  date      history

#endif // !defined(AFX_VERTEXSTEP_H__9F9D4C74_0C2F_11D5_BFEF_0004AC6EEF35__INCLUDED_)
