// Plane_surfaceIges.cpp: implementation of the CPlane_surfaceIges class.
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
//#ifdef _WINDOWS 
#include "scribble.h"
#endif

#include "Plane_surfaceIges.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPlane_surfaceIges::CPlane_surfaceIges()
: CBaseIges( (void*)NULL)
{
  m_iEntityTypeNum = 190;
}

CPlane_surfaceIges::~CPlane_surfaceIges()
{

}
