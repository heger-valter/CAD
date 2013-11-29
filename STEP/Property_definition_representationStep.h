// Property_definition_representationStep.h: interface for the CProperty_definition_representationStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROPERTY_DEFINITION_REPRESENTATIONSTEP_H__9B1A6B40_BEE9_4A22_8B3B_83DCDBBE138D__INCLUDED_)
#define AFX_PROPERTY_DEFINITION_REPRESENTATIONSTEP_H__9B1A6B40_BEE9_4A22_8B3B_83DCDBBE138D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CProperty_definitionStep;
class CRepresentationStep;

#include "baseStep.h"

class CProperty_definition_representationStep : public CBaseStep  
{
public:
	CProperty_definition_representationStep();
	virtual ~CProperty_definition_representationStep();
  CProperty_definitionStep*     m_pDefinition         ;
  CRepresentationStep*          m_pUsed_representation;
  HRESULT backPtr( CBaseStep*& prBrep);
	void Serialize(stepArchive& ar);
};

#endif // !defined(AFX_PROPERTY_DEFINITION_REPRESENTATIONSTEP_H__9B1A6B40_BEE9_4A22_8B3B_83DCDBBE138D__INCLUDED_)
