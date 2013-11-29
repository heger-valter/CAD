// Product_definition_contextStep.h: interface for the Product_definition_contextStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRODUCT_DEFINITION_CONTEXTSTEP_H__05038DDD_0101_4EDC_9203_D5F92361D082__INCLUDED_)
#define AFX_PRODUCT_DEFINITION_CONTEXTSTEP_H__05038DDD_0101_4EDC_9203_D5F92361D082__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "baseStep.h"

class CProduct_definition_contextStep : public CBaseStep  
{
public:
	CProduct_definition_contextStep();
	virtual ~CProduct_definition_contextStep();
	void Serialize(stepArchive& ar);
  HRESULT backPtr( CBaseStep*& prBrep);

};

#endif // !defined(AFX_PRODUCT_DEFINITION_CONTEXTSTEP_H__05038DDD_0101_4EDC_9203_D5F92361D082__INCLUDED_)
