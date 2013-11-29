// Right_circular_cylinderStep.cpp: implementation of the CRight_circular_cylinderStep class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PointStep.h"
#include "Right_circular_cylinderStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRight_circular_cylinderStep::CRight_circular_cylinderStep( CCartesian_pointStep& position,
                                                            double radius,
                                                            double height)
  : CGeometric_representation_itemStep( NULL)
  ,   m_radius(   radius)
  ,   m_height(   height)
  ,   m_position( position)
{
  nameClass("Right_circular_cylinder");
}

CRight_circular_cylinderStep::~CRight_circular_cylinderStep()
{

}

HRESULT CRight_circular_cylinderStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  return E_FAIL;
}
