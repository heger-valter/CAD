// OrganizationStep.h: interface for the COrganizationStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ORGANIZATIONSTEP_H__97E73DFE_2CE1_405A_A725_D5A09A7ACE18__INCLUDED_)
#define AFX_ORGANIZATIONSTEP_H__97E73DFE_2CE1_405A_A725_D5A09A7ACE18__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "baseStep.h"

class COrganizationStep : public CBaseStep  
{
public:
	COrganizationStep();
	virtual ~COrganizationStep();
  CString     m_szId               ;//OPTIONAL 
  CString     m_szName             ;
  CString     m_szDescription      ;
  void Serialize(stepArchive &ar);
  HRESULT backPtr(CBaseStep *&prBrep);
};

#endif // !defined(AFX_ORGANIZATIONSTEP_H__97E73DFE_2CE1_405A_A725_D5A09A7ACE18__INCLUDED_)
