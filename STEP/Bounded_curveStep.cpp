// Bounded_curveStep.cpp: implementation of the CBounded_curveStep class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#ifdef _WINDOWS 
#include "scribble.h"
#endif

#include "Bounded_curveStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBounded_curveStep::CBounded_curveStep()
{
  nameClass("Bounded_curve");
}

CBounded_curveStep::~CBounded_curveStep()
{

}

void CBounded_curveStep::Serialize(stepArchive &ar)
{

}
