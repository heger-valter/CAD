// Product_definition_relationshipStep.h: interface for the CProduct_definition_relationshipStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRODUCT_DEFINITION_RELATIONSHIPSTEP_H__9A748E81_2893_11D5_8013_0004AC6EEF35__INCLUDED_)
#define AFX_PRODUCT_DEFINITION_RELATIONSHIPSTEP_H__9A748E81_2893_11D5_8013_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Representation_itemStep.h"

class CProduct_definition_relationshipStep : public CRepresentation_itemStep  
{
public:
	CProduct_definition_relationshipStep();
	virtual ~CProduct_definition_relationshipStep();
  HRESULT backPtr( CBaseStep*& prBrep);
	void Serialize(stepArchive& ar);

};

#endif // !defined(AFX_PRODUCT_DEFINITION_RELATIONSHIPSTEP_H__9A748E81_2893_11D5_8013_0004AC6EEF35__INCLUDED_)
