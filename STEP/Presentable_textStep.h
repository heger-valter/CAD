// Presentable_textStep.h: interface for the CPresentable_textStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRESENTABLE_TEXTSTEP_H__9830F381_26A2_11D5_8CAE_00D00908C1A5__INCLUDED_)
#define AFX_PRESENTABLE_TEXTSTEP_H__9830F381_26A2_11D5_8CAE_00D00908C1A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "baseStep.h"

class CPresentable_textStep : public CBaseStep  
{
public:
	void Serialize(stepArchive &ar);
	CPresentable_textStep(char* szText);
	virtual ~CPresentable_textStep();
  CString m_text;
  HRESULT backPtr( CBaseStep*& prBrep);
};

#endif // !defined(AFX_PRESENTABLE_TEXTSTEP_H__9830F381_26A2_11D5_8CAE_00D00908C1A5__INCLUDED_)
