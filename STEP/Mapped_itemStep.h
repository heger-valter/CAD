// Mapped_itemStep.h: interface for the CMapped_itemStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPPED_ITEMSTEP_H__317C8A95_031F_4FAC_9B3B_C8168DA8AFE1__INCLUDED_)
#define AFX_MAPPED_ITEMSTEP_H__317C8A95_031F_4FAC_9B3B_C8168DA8AFE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Representation_itemStep.h"
#include "Representation_mapStep.h"

class CMapped_itemStep : public CRepresentation_itemStep  
{
public:
	CRepresentation_itemStep* m_pMapping_target;
	CMapped_itemStep();
	virtual ~CMapped_itemStep();
  CRepresentation_mapStep* m_pMapping_source;
	void Serialize(stepArchive& ar);
};

#endif // !defined(AFX_MAPPED_ITEMSTEP_H__317C8A95_031F_4FAC_9B3B_C8168DA8AFE1__INCLUDED_)
