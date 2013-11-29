// product_definition_shapestep.h: interface for the CProduct_definition_shapeStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_Product_definition_shapeSTEP_H__230B85FA_A82F_4B38_9304_7128DF42BAC4__INCLUDED_)
#define AFX_Product_definition_shapeSTEP_H__230B85FA_A82F_4B38_9304_7128DF42BAC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Property_definition_representationStep.h"

class CProduct_definition_shapeStep : public CProperty_definition_representationStep
{
public:
	CProduct_definition_shapeStep();
	virtual ~CProduct_definition_shapeStep();
	void Serialize(stepArchive& ar);
  HRESULT backPtr( CBaseStep*& prBrep);
};

#endif // !defined(AFX_Product_definition_shapeSTEP_H__230B85FA_A82F_4B38_9304_7128DF42BAC4__INCLUDED_)
