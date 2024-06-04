// Oriented_closed_shellStep.cpp: implementation of the COriented_closed_shellStep class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _WINDOWS
#include "stdafx.h"
#endif

#ifdef _WINDOWS 
#include "scribble.h"
#endif

#include "Oriented_closed_shellStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COriented_closed_shellStep::COriented_closed_shellStep()
:CClosed_shellStep( NULL, NULL)
{
  nameClass("Oriented_closed_shell");
}

COriented_closed_shellStep::~COriented_closed_shellStep()
{

}
