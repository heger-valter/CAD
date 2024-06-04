// Cartesian_tranformation_operator_3dStep.cpp: implementation of the CCartesian_tranformation_operator_3dStep class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _WINDOWS
#include "stdafx.h"
#endif

#include "Cartesian_tranformation_operator_3dStep.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCartesian_tranformation_operator_3dStep::CCartesian_tranformation_operator_3dStep( double Xmove, 
                                                                                    double Ymove, 
                                                                                    double Zmove)
:transform( Xmove, Ymove, Zmove)
{
  nameClass("Cartesian_tranformation_operator_3d");
}
CCartesian_tranformation_operator_3dStep::~CCartesian_tranformation_operator_3dStep()
{

}

HRESULT CCartesian_tranformation_operator_3dStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  else {
    return E_FAIL;
  }
}
bool CCartesian_tranformation_operator_3dStep::rotate(double theta, double psi, double phi)
{
  return 
    transform.rotate(theta,   psi,   phi);
}

bool CCartesian_tranformation_operator_3dStep::translate( double Xmove, 
                                                          double Ymove, 
                                                          double Zmove)
{
  transform.move( Xmove, Ymove, Zmove);
  return false;
}
