// RepresentationStep.h: interface for the CRepresentationStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REPRESENTATIONSTEP_H__7F3EE8D3_1F20_11D5_8006_0004AC6EEF35__INCLUDED_)
#define AFX_REPRESENTATIONSTEP_H__7F3EE8D3_1F20_11D5_8006_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "baseStep.h"
class step;
class CRepresentation_contextStep;
class CRepresentation_itemStep;

class CRepresentationStep 
: public CBaseStep  
{
public:
	CRepresentationStep(step* pStep);
	virtual ~CRepresentationStep();
  static step* m_pStep;
  CString name;
  CRepresentation_contextStep * m_pContext_of_items;
  CRepresentation_contextStep ** m_pItems;
  HRESULT backPtr( CBaseStep*& prBrep);
};

#endif // !defined(AFX_REPRESENTATIONSTEP_H__7F3EE8D3_1F20_11D5_8006_0004AC6EEF35__INCLUDED_)
