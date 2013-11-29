// Application_context.h: interface for the CApplication_context class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_APPLICATION_CONTEXT_H__79E4B1CB_DB68_4C22_9A2E_468A7AFAA286__INCLUDED_)
#define AFX_APPLICATION_CONTEXT_H__79E4B1CB_DB68_4C22_9A2E_468A7AFAA286__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "baseStep.h"

class CApplication_context : public CBaseStep  
{
public:
	HRESULT backPtr(CBaseStep *&prBrep);
	void Serialize(stepArchive &ar);
	CApplication_context();
	virtual ~CApplication_context();

};

#endif // !defined(AFX_APPLICATION_CONTEXT_H__79E4B1CB_DB68_4C22_9A2E_468A7AFAA286__INCLUDED_)
