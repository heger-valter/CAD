// Representation_contextStep.h: interface for the CRepresentation_context class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REPRESENTATION_CONTEXT_H__9B2019DC_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_)
#define AFX_REPRESENTATION_CONTEXT_H__9B2019DC_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseStep.h"

class CRepresentation_contextStep : public CBaseStep  
{
public:
	void Serialize( stepArchive &ar);
	CRepresentation_contextStep(CBaseStep * pFrom);
	virtual ~CRepresentation_contextStep();
  HRESULT backPtr( CBaseStep*& prBrep);

};

//////////////////////////////////////////////////////////
// who  date      history

#endif // !defined(AFX_REPRESENTATION_CONTEXT_H__9B2019DC_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_)
