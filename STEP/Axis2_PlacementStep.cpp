// Axis2_PlacementStep.cpp: implementation of the CAxis2_PlacementStep class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "scribble.h"
#include "Axis2_PlacementStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

this file should be deleted
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAxis2_PlacementStep::CAxis2_PlacementStep(CCartesian_pointStep* pLocation)
: CPlacementStep()
{
  nameClass("Axis2_Placement");
}

CAxis2_PlacementStep::~CAxis2_PlacementStep()
{

}
