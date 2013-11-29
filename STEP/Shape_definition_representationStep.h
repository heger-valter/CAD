// Shape_representationStep.h: interface for the CShape_representationStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_Shape_definition_representationSTEP_H__7F3EE8D4_1F20_11D5_8006_0004AC6EEF35__INCLUDED_)
#define AFX_Shape_definition_representationSTEP_H__7F3EE8D4_1F20_11D5_8006_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Property_definition_representationStep.h"

class CShape_definition_representationStep : public CProperty_definition_representationStep
{
public:
	void Serialize(stepArchive &ar);
	CShape_definition_representationStep( );
	virtual ~CShape_definition_representationStep();
  HRESULT backPtr( CBaseStep*& prBrep);
};

#endif // !defined(AFX_Shape_definition_representationSTEP_H__7F3EE8D4_1F20_11D5_8006_0004AC6EEF35__INCLUDED_)
