// Property_definitionStep.h: interface for the CProperty_definitionStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROPERTY_DEFINITIONSTEP_H__1536FBB7_ED96_41B4_99E3_C449823AD162__INCLUDED_)
#define AFX_PROPERTY_DEFINITIONSTEP_H__1536FBB7_ED96_41B4_99E3_C449823AD162__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "baseStep.h"
class CCharacterized_definitionStep;

class CProperty_definitionStep : public CBaseStep  
{
public:
	CProperty_definitionStep();
	virtual ~CProperty_definitionStep();
  CString                    name                         ;
  CString                    description                  ;
//CCharacterized_definitionStep* m_pDefinition            ;  
};

#endif // !defined(AFX_PROPERTY_DEFINITIONSTEP_H__1536FBB7_ED96_41B4_99E3_C449823AD162__INCLUDED_)
