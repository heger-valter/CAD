// Specified_higher_usage_occuranceStep.h: interface for the CSpecified_higher_usage_occurance class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPECIFIED_HIGHER_USAGE_OCCURANCE_H__9A748E84_2893_11D5_8013_0004AC6EEF35__INCLUDED_)
#define AFX_SPECIFIED_HIGHER_USAGE_OCCURANCE_H__9A748E84_2893_11D5_8013_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Assembly_component_usageStep.h"
#include "Next_assembly_usage_occuranceStep.h"

class CSpecified_higher_usage_occuranceStep : public CAssembly_component_usageStep  
{
public:
	CNext_assembly_usage_occuranceStep& m_rNext_usage;
  CAssembly_component_usageStep& m_rUpper_usage;
  CSpecified_higher_usage_occuranceStep(CNext_assembly_usage_occuranceStep& rNext_usage,
  CAssembly_component_usageStep& rUpper_usage);
	virtual ~CSpecified_higher_usage_occuranceStep();
  HRESULT backPtr( CBaseStep*& prBrep);
	void Serialize(stepArchive& ar);

};

#endif // !defined(AFX_SPECIFIED_HIGHER_USAGE_OCCURANCE_H__9A748E84_2893_11D5_8013_0004AC6EEF35__INCLUDED_)
