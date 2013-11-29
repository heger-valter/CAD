// PathStep.h: interface for the CPathStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PATHSTEP_H__8F9606E1_122D_11D5_9387_00D00908C1A5__INCLUDED_)
#define AFX_PATHSTEP_H__8F9606E1_122D_11D5_9387_00D00908C1A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Topological_representation_itemStep.h"
#include "afxcoll.h"
//#include "Oriented_EdgeStep.h"
class COriented_edgeStep;

#undef string

typedef  CTypedPtrArray <CrcPtrArray, COriented_edgeStep*> t_aEdge_list;

class CPathStep : public CTopological_representation_itemStep  
{
public:
  t_aEdge_list m_aEdge_list;
//COriented_edgeStep** ppEdge_list;
	CPathStep(CBaseStep*pIn , int iNewSize );
	virtual ~CPathStep();
  HRESULT backPtr( CBaseStep*& prBrep);
  HRESULT demote();

#if 0
	void PASCAL operator delete(void* p);
  void* //PASCAL 
    operator new(unsigned int nSize, const char * pszFileName, int nLine); // line 31
#endif

};
//////////////////////////////////////////////////////////
// who  date      history

#endif // !defined(AFX_PATHSTEP_H__8F9606E1_122D_11D5_9387_00D00908C1A5__INCLUDED_)
