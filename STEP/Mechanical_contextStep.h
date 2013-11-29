// Mechanical_contextStep.h: interface for the CMechanical_contextStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMECHANICAL_CONTEXT_H__355FF2DE_6350_4C03_8C95_E05D53A4EAAB__INCLUDED_)
#define AFX_CMECHANICAL_CONTEXT_H__355FF2DE_6350_4C03_8C95_E05D53A4EAAB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "baseStep.h"

class CMechanical_contextStep : public CBaseStep  
{
public:
	HRESULT backPtr(CBaseStep *&prBrep);
	CMechanical_contextStep();
	virtual ~CMechanical_contextStep();
	void Serialize(stepArchive& ar);
};

#endif // !defined(AFX_CMECHANICAL_CONTEXT_H__355FF2DE_6350_4C03_8C95_E05D53A4EAAB__INCLUDED_)
