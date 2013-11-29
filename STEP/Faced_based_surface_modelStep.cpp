// Shell_based_surface_modelStep.cpp: implementation of the CShell_based_surface_modelStep class.
//
//////////////////////////////////////////////////////////////////////

////#include "stdafx.h"
//#include "scribble.h"
#include "Shell_based_surface_modelStep.h"
#include "Geometric_representation_itemStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShell_based_surface_modelStep::CShell_based_surface_modelStep()
:  CGeometric_representation_itemStep( NULL)
{
  nameClass("Shell_based_surface_model");
}

CShell_based_surface_modelStep::~CShell_based_surface_modelStep()
{

}
