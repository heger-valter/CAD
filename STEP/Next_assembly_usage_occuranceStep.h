// Next_assembly_usage_occuranceStep.h: interface for the CNext_assembly_usage_occuranceStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEXT_ASSEMBLY_USAGE_OCCURANCE_H__9A748E87_2893_11D5_8013_0004AC6EEF35__INCLUDED_)
#define AFX_NEXT_ASSEMBLY_USAGE_OCCURANCE_H__9A748E87_2893_11D5_8013_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Assembly_component_usageStep.h"

class CNext_assembly_usage_occuranceStep : public CAssembly_component_usageStep    
{
public:
	void Serialize(stepArchive &ar);
	CNext_assembly_usage_occuranceStep();
	virtual ~CNext_assembly_usage_occuranceStep();
  HRESULT backPtr( CBaseStep*& prBrep);

};

#endif // !defined(AFX_NEXT_ASSEMBLY_USAGE_OCCURANCE_H__9A748E87_2893_11D5_8013_0004AC6EEF35__INCLUDED_)
