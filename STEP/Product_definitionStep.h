// Product_definitionStep.h: interface for the CProduct_definitionStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRODUCT_DEFINITIONSTEP_H__230B85FA_A82F_4B38_9304_7128DF42BAC4__INCLUDED_)
#define AFX_PRODUCT_DEFINITIONSTEP_H__230B85FA_A82F_4B38_9304_7128DF42BAC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "baseStep.h"
//class CProduct_definition_formationStep;
class CProduct_definition_contextStep;

//#include "Product_definition_contextStep.h"
#include "Product_definition_formationStep.h"

class CProduct_definitionStep : public CBaseStep  
{
public:
	HRESULT backPtr(CBaseStep *&prBrep);
	CProduct_definitionStep();
	virtual ~CProduct_definitionStep();
  int                                id                    ; 
  CString                            description           ; 
  CProduct_definition_formationStep* m_pFormation          ; 
  CProduct_definition_contextStep*   m_pFrame_of_reference ; 
	void Serialize(stepArchive& ar);
};

#endif // !defined(AFX_PRODUCT_DEFINITIONSTEP_H__230B85FA_A82F_4B38_9304_7128DF42BAC4__INCLUDED_)
