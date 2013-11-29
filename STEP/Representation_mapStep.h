// Representation_mapStep.h: interface for the CRepresentation_mapStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REPRESENTATION_MAPSTEP_H__6F4F79DA_8757_4A8E_846E_59A96A0E2DBF__INCLUDED_)
#define AFX_REPRESENTATION_MAPSTEP_H__6F4F79DA_8757_4A8E_846E_59A96A0E2DBF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMapped_itemStep;
class CRepresentationStep;
class CRepresentation_itemStep;
#include "baseStep.h"

class CRepresentation_mapStep : public CBaseStep  
{
public:
	CRepresentation_mapStep();
	virtual ~CRepresentation_mapStep();
  CTypedPtrArray <CPtrArray, CMapped_itemStep*> aMap_usage;
  CRepresentationStep* m_pMapped_representation;
  CRepresentation_itemStep* m_pMapping_origin;
	void Serialize(stepArchive& ar);
};

#endif // !defined(AFX_REPRESENTATION_MAPSTEP_H__6F4F79DA_8757_4A8E_846E_59A96A0E2DBF__INCLUDED_)
