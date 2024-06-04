// stepAdvancedMaker.cpp: implementation of the stepAdvancedMaker class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _WINDOWS
#include "stdafx.h"
#endif

#ifdef _WINDOWS 
#include "scribble.h"
#endif

#include "stepAdvancedMaker.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

stepAdvancedMaker::stepAdvancedMaker(CScribView *pOuter)
: step( pOuter)
{

}

stepAdvancedMaker::~stepAdvancedMaker()
{

}
