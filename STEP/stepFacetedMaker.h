// stepFacetedMaker.h: interface for the stepFacetedMaker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STEPFACETEDMAKER_H__F3409234_0D92_49CF_9BBA_E51A873919F9__INCLUDED_)
#define AFX_STEPFACETEDMAKER_H__F3409234_0D92_49CF_9BBA_E51A873919F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StepSer.h"

class stepFacetedMaker : public step  
{
public:
	stepFacetedMaker(CScribView *pOuter);
	virtual ~stepFacetedMaker();

};

#endif // !defined(AFX_STEPFACETEDMAKER_H__F3409234_0D92_49CF_9BBA_E51A873919F9__INCLUDED_)
