// Face_based_surface_modelStep.cpp: implementation of the CFace_based_surface_modelStep class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "scribble.h"
#include "Face_based_surface_modelStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFace_based_surface_modelStep::CFace_based_surface_modelStep()
: CGeometric_representation_itemStep( NULL)
{
  nameClass("Face_based_surface_model");
}

CFace_based_surface_modelStep::~CFace_based_surface_modelStep()
{

}
