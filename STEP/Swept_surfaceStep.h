// Swept_surfaceStep.h: interface for the CSwept_surfaceStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SWEPT_SURFACESTEP_H__5D5B168B_25FA_11D5_9EA8_E8C9DCC61937__INCLUDED_)
#define AFX_SWEPT_SURFACESTEP_H__5D5B168B_25FA_11D5_9EA8_E8C9DCC61937__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSwept_surfaceStep  
: public CBaseStep
{
public:
	CSwept_surfaceStep();
	virtual ~CSwept_surfaceStep();
  HRESULT backPtr( CBaseStep*& prBrep);

};

#endif // !defined(AFX_SWEPT_SURFACESTEP_H__5D5B168B_25FA_11D5_9EA8_E8C9DCC61937__INCLUDED_)
