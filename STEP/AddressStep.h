// AddressStep.h: interface for the CAddressStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADDRESSSTEP_H__956A29FB_1616_494A_9C40_1B963BCE00C0__INCLUDED_)
#define AFX_ADDRESSSTEP_H__956A29FB_1616_494A_9C40_1B963BCE00C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "baseStep.h"

class CAddressStep : public CBaseStep  
{
public:
	void Serialize(stepArchive &ar);
	HRESULT backPtr( CBaseStep*& prBrep);
	CAddressStep();
	virtual ~CAddressStep();
  CString     m_szInternal_location       ;
  CString     m_szStreet_number           ;
  CString     m_szStreet                  ;
  CString     m_szPostal_box              ;
  CString     m_szTown                    ;
  CString     m_szRegion                  ;
  CString     m_szPostal_code             ;
  CString     m_szCountry                 ;
  CString     m_szFacsimile_number        ;
  CString     m_szTelephone_number        ;
  CString     m_szElectronic_mail_address ;
  CString     m_szTelex_number            ;
};

#endif // !defined(AFX_ADDRESSSTEP_H__956A29FB_1616_494A_9C40_1B963BCE00C0__INCLUDED_)

