// Shape_representationStep.h: interface for the CShape_representationStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHAPE_REPRESENTATIONSTEP_H__7F3EE8D4_1F20_11D5_8006_0004AC6EEF35__INCLUDED_)
#define AFX_SHAPE_REPRESENTATIONSTEP_H__7F3EE8D4_1F20_11D5_8006_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RepresentationStep.h"

class CShape_representationStep : public CRepresentationStep  
{
public:
	CShape_representationStep(step* pStep);
	virtual ~CShape_representationStep();
  HRESULT backPtr( CBaseStep*& prBrep);
	void Serialize(stepArchive& ar);
};

#endif // !defined(AFX_SHAPE_REPRESENTATIONSTEP_H__7F3EE8D4_1F20_11D5_8006_0004AC6EEF35__INCLUDED_)
