// Axis2_Placement_3d.cpp: implementation of the CAxis2_Placement_3d class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _WINDOWS
#include "stdafx.h"
#endif

#include "Axis2_Placement_3dStep.h"
#include "Cartesian_pointStep.h"
#include "stepArchive.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAxis2_placement_3dStep::CAxis2_placement_3dStep( CCartesian_pointStep* pLocation, // hw 03/18/01 renamed 
                                                  CDirectionStep*       pAxis, 
                                                  CDirectionStep*       pRef_direction)
  : CPlacementStep(pLocation)
{
  nameClass("Axis2_Placement_3d");
  m_pAxis = pAxis;
  m_pRef_direction =pRef_direction;
}

CAxis2_placement_3dStep::~CAxis2_placement_3dStep() // hw 03/18/01 renamed 
{ 
  // wh 9/29/01
  try {
    ASSERT_VALID( m_pAxis);
    m_pAxis->release();
  } 
  catch(...) {
    TRACE1("~CAxis2_placement_3dStep #%d m_pAxis has already been deleted\n", this->getNum());
  }  

  try {
    ASSERT_VALID( m_pRef_direction);
    m_pRef_direction->release();
  } 
  catch(...){
    TRACE1("~CAxis2_placement_3dStep #%d m_pRef_direction has already been deleted\n", this->getNum());
  }
}

HRESULT CAxis2_placement_3dStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  else {
    return E_FAIL;
  }
}
void CAxis2_placement_3dStep::Serialize(stepArchive &ar) // hw 03/18/01 renamed 
{
  try {
    bool bUp=true; 
    bool bLeft=true;
    if (!isSerialized()){
      setSerialized();
      writePre( ar); 
      ar << "'',#";
      ar << m_pLocation->getNum();
      {
        if (NULL != m_pAxis) {
          ar <<   ",#" ;
          ar << axis()->getNum();
        }
        else{
          // ignore      
          ar << ",$";
          bUp = false;
        }
        if (NULL != m_pRef_direction) {
          ar <<   ",#" ;
          ar << ref_direction()->getNum();
        }
        else {
          ar << ",$";
          bLeft = false;
        }
      }
      writePost( ar);
      m_pLocation->m_pBack=this;
      m_pLocation->Serialize(ar);
      if (bUp  ){
        axis()->m_pBack = this;
        axis()->Serialize(ar);
      }
      if (bLeft){
        ref_direction()->m_pBack = this;
        ref_direction()->Serialize(ar);
      }
    }
  }
  catch(...){
    ar << "\n/*Errors detected in CAxis2_placement_3dStep::Serialize #\n"; // hw 03/18/01 renamed 
    ar << getNum();
    ar <<   ", but continuing*/\n" ;    
    setSerialized();
  }

}

// the up direction
CDirectionStep* CAxis2_placement_3dStep::axis() // hw 03/18/01 renamed 
{
  return  m_pAxis;
}

// the left direction
CDirectionStep* CAxis2_placement_3dStep::ref_direction() // hw 03/18/01 renamed 
{
  return  m_pRef_direction;
}

//////////////////////////////////////////////////////////
// who  date      history

double CAxis2_placement_3dStep::p(unsigned int i)
{
  ASSERT(i<3//CRepresentation_contextStep::m_iDim
    );
  return m_pAxis->direction_ratios(i);
}

void CAxis2_placement_3dStep::fin()
{
   m_pAxis=NULL; 
   m_pRef_direction=NULL;
   CPlacementStep::fin();
}

HRESULT CAxis2_placement_3dStep::negate()
{ 
  // negate the axis rather than the ref_direction 
  // because you point the surface in the opposite direction
  return m_pAxis->negate();
}
