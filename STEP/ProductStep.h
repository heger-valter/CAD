// ProductStep.h: interface for the CProductStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CProductStep_H__355FF2DE_6350_4C03_8C95_E05D53A4EAAB__INCLUDED_)
#define AFX_CProductStep_H__355FF2DE_6350_4C03_8C95_E05D53A4EAAB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "baseStep.h"

class CProductStep : public CBaseStep  
{
public:
	HRESULT backPtr(CBaseStep *&prBrep);
	CProductStep();
	virtual ~CProductStep();
	void Serialize(stepArchive& ar);
};

#endif // !defined(AFX_CProductStep_H__355FF2DE_6350_4C03_8C95_E05D53A4EAAB__INCLUDED_)
