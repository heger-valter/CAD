// application_context.h: interface for the CAPPLICATION_CONTEXT class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAPPLICATION_CONTEXT_H__355FF2DE_6350_4C03_8C95_E05D53A4EAAB__INCLUDED_)
#define AFX_CAPPLICATION_CONTEXT_H__355FF2DE_6350_4C03_8C95_E05D53A4EAAB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "baseStep.h"

class CApplication_contextStep : public CBaseStep  
{
public:
	CApplication_contextStep();
	virtual ~CApplication_contextStep();
	void Serialize(stepArchive& ar);
};

#endif // !defined(AFX_CAPPLICATION_CONTEXT_H__355FF2DE_6350_4C03_8C95_E05D53A4EAAB__INCLUDED_)
