// Product_definition_usageStep.h: interface for the CProduct_definition_usageStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRODUCT_DEFINITION_USAGESTEP_H__9A748E82_2893_11D5_8013_0004AC6EEF35__INCLUDED_)
#define AFX_PRODUCT_DEFINITION_USAGESTEP_H__9A748E82_2893_11D5_8013_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Product_definition_relationshipStep.h"

class CProduct_definition_usageStep : public CProduct_definition_relationshipStep  
{
public:
	CProduct_definition_usageStep();
	virtual ~CProduct_definition_usageStep();
  HRESULT backPtr( CBaseStep*& prBrep);
	void Serialize(stepArchive& ar);

};

#endif // !defined(AFX_PRODUCT_DEFINITION_USAGESTEP_H__9A748E82_2893_11D5_8013_0004AC6EEF35__INCLUDED_)
