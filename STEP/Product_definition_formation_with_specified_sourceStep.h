// Product_definition_formation_with_specified_sourceStep.h: interface for the CProduct_definition_formation_with_specified_sourceStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRODUCT_DEFINITION_FORMATION_WITH_SPECIFIED_SOURCESTEP_H__CAD4385D_54AF_42CF_8454_66087848C174__INCLUDED_)
#define AFX_PRODUCT_DEFINITION_FORMATION_WITH_SPECIFIED_SOURCESTEP_H__CAD4385D_54AF_42CF_8454_66087848C174__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Product_definition_formationStep.h"

class CProduct_definition_formation_with_specified_sourceStep 
: public CProduct_definition_formationStep  
{
public:
	HRESULT backPtr(CBaseStep *&prBrep);
	CProduct_definition_formation_with_specified_sourceStep();
	virtual ~CProduct_definition_formation_with_specified_sourceStep();
	void Serialize(stepArchive& ar);

};

#endif // !defined(AFX_PRODUCT_DEFINITION_FORMATION_WITH_SPECIFIED_SOURCESTEP_H__CAD4385D_54AF_42CF_8454_66087848C174__INCLUDED_)
