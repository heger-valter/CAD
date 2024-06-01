// Conical_surfaceStep.cpp: implementation of the CConical_surfaceStep class.
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
#ifdef _WINDOWS 
#include "scribble.h"
#endif

#include "Conical_surfaceStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CConical_surfaceStep::CConical_surfaceStep( CAxis2_placement_3dStep& rPos,
                                           double semi_angle,
  double radius)
    : CElementary_surfaceStep  (&rPos)
    , m_dSemi_angle(semi_angle)
    , m_dRadius(radius)
{
  nameClass("Conical_surface");
}

CConical_surfaceStep::~CConical_surfaceStep()
{

}
