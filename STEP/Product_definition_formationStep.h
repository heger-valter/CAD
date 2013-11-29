// Product_definition_formationStep.h: interface for the CProduct_definition_formationStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRODUCT_DEFINITION_FORMATIONSTEP_H__355FF2DE_6350_4C03_8C95_E05D53A4EAAB__INCLUDED_)
#define AFX_PRODUCT_DEFINITION_FORMATIONSTEP_H__355FF2DE_6350_4C03_8C95_E05D53A4EAAB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "baseStep.h"

class CProduct_definition_formationStep : public CBaseStep  
{
public:
	CProduct_definition_formationStep();
	virtual ~CProduct_definition_formationStep();
//      id          : identifier;
//      description : text;
//      of_product  : product;
//    UNIQUE
//      ur1 : id, of_product;
	void Serialize(stepArchive& ar);
};

#endif // !defined(AFX_PRODUCT_DEFINITION_FORMATIONSTEP_H__355FF2DE_6350_4C03_8C95_E05D53A4EAAB__INCLUDED_)
