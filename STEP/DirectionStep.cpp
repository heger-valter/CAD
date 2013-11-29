// Direction.cpp: implementation of the CDirection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DirectionStep.h"
#include "stepArchive.h"
#include "PointStep.h"
#include "Cartesian_pointStep.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDirectionStep::CDirectionStep(CBaseStep*pIn, double x, double y, double z )
  : CGeometric_representation_itemStep(pIn)
  , m_bGood(true)
{
  nameClass("Direction");
  m_bGood = ((0.e0!=x) || (0.e0!=y) || (0.e0!=z));// are you sure that these should not be compared against restol //wh 07/17/01
  m_direction_ratios[0] = x;
  m_direction_ratios[1] = y;
  m_direction_ratios[2] = z;
}

CDirectionStep::CDirectionStep( CBaseStep*pIn, 
                                CCartesian_pointStep& rCartesian_pointStep0, 
                                CCartesian_pointStep& rCartesian_pointStep1 )
  : CGeometric_representation_itemStep(pIn)
  , m_bGood(true)
{  
  ASSERT( &rCartesian_pointStep0 != NULL);
  ASSERT( &rCartesian_pointStep1 != NULL);
  nameClass("Direction");
  m_direction_ratios[0] = rCartesian_pointStep1.coordinates[0] - rCartesian_pointStep0.coordinates[0] ; 
  m_direction_ratios[1] = rCartesian_pointStep1.coordinates[1] - rCartesian_pointStep0.coordinates[1] ;
  m_direction_ratios[2] = rCartesian_pointStep1.coordinates[2] - rCartesian_pointStep0.coordinates[2] ;
  isGood();
}

CDirectionStep::CDirectionStep( CCartesian_pointStep& rCartesian_pointStep0 )
  : CGeometric_representation_itemStep(NULL)
  , m_bGood(true)
{
  ASSERT( &rCartesian_pointStep0 != NULL);
  nameClass("Direction");
  m_direction_ratios[0] = rCartesian_pointStep0.coordinates[0] ;  // wh changed 05/11/01
  m_direction_ratios[1] = rCartesian_pointStep0.coordinates[1] ;
  m_direction_ratios[2] = rCartesian_pointStep0.coordinates[2] ;
  isGood();
}

CDirectionStep::~CDirectionStep()
{ 
  ASSERT_VALID(this);
}

double CDirectionStep::direction_ratios(int i)
{ 
  return m_direction_ratios[i];
}

HRESULT CDirectionStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  else {
    return E_FAIL;
  }
}

void CDirectionStep::Serialize(stepArchive &ar)
{
  if (!isSerialized()){
    setSerialized();
    try{  //ack move it inside
        writePre( ar);
        ar <<  "'" << m_szLabelName << "',";
        ASSERT( m_bGood);
        if(!m_bGood){
//        ar <<  "( 1.0, 1.0, 1.0)";// wh 03/12/02
          ar <<  "( ";
          ar <<  restol;
          ar <<       ", ";
          ar <<  restol;
          ar <<            ", ";
          ar <<  restol;
          ar <<                 ")";
          ar << "\n/* Danger, zero length vector changed to dummy value!*/\n";
        } else {
          writeDouble(ar, m_direction_ratios, sizeof(m_direction_ratios )/sizeof(m_direction_ratios[0]));
        }
        writePost( ar);
    }
    catch(...){
      ar << "\n/*Errors detected in CPlacementStep::Serialize #\n";
  //  ar << getNum();
      ar <<   ", but continuing*/\n" ;    
    }
  }

}
/*
CDirectionStep& CDirectionStep::crossProd(CDirectionStep &lhs, CDirectionStep &rhs)
{
  m_direction_ratios[0] = lhs.m_direction_ratios[1] * rhs.m_direction_ratios[2] - lhs.m_direction_ratios[2] * rhs.m_direction_ratios[1];
  m_direction_ratios[1] =-lhs.m_direction_ratios[0] * rhs.m_direction_ratios[2] + lhs.m_direction_ratios[2] * rhs.m_direction_ratios[0];
  m_direction_ratios[2] = lhs.m_direction_ratios[0] * rhs.m_direction_ratios[1] - lhs.m_direction_ratios[1] * rhs.m_direction_ratios[0];
  return *this;
}
*/
//////////////////////////////////////////////////////////
// who  date      history

double CDirectionStep::getLength2()// remove me
{
  double dLen  = m_direction_ratios[0] * m_direction_ratios[0] ;
         dLen += m_direction_ratios[1] * m_direction_ratios[1] ;
         dLen += m_direction_ratios[2] * m_direction_ratios[2] ;
  return dLen;
}

double CDirectionStep::getLength()// remove me
{
  double dLen  = getLength2();
  return sqrt(dLen);
}

bool CDirectionStep::withinTol()// remove me
{
  return getLength2() < restol2;
}

void CDirectionStep::fin()
{
  CGeometric_representation_itemStep::fin();
}

CDirectionStep& CDirectionStep::operator -=(CDirectionStep &rhs)// remove me
{
  m_direction_ratios[0]  -= rhs.m_direction_ratios[0];
  m_direction_ratios[1]  -= rhs.m_direction_ratios[1];
  m_direction_ratios[2]  -= rhs.m_direction_ratios[2];

  return *this;
}

CDirectionStep::CDirectionStep(CDirectionStep &rhs)
  : CGeometric_representation_itemStep(this)
  , m_bGood(rhs.m_bGood)
{
  m_direction_ratios[0] = rhs.m_direction_ratios[0];
  m_direction_ratios[1] = rhs.m_direction_ratios[1];
  m_direction_ratios[2] = rhs.m_direction_ratios[2];

}

double dotProduct( CDirectionStep &rD0, CDirectionStep &rD1)// rename isParallel
{
  double dResult  = rD0.m_direction_ratios[0] * rD1.m_direction_ratios[0];
         dResult += rD0.m_direction_ratios[1] * rD1.m_direction_ratios[1];
         dResult += rD0.m_direction_ratios[2] * rD1.m_direction_ratios[2];
  return dResult;
}

bool withinResdot( CDirectionStep &rD0, CDirectionStep &rD1)// remove me
{
  return false;
}

CDirectionStep* crossProduct( CDirectionStep &lhs, CDirectionStep &rhs)
{
  CDirectionStep* pDirectionStep  = new  CDirectionStep (NULL, 0.0e0);
  if (NULL != pDirectionStep  ) {
    pDirectionStep->m_direction_ratios[0] =
       lhs.m_direction_ratios[1] * rhs.m_direction_ratios[2] - 
       lhs.m_direction_ratios[2] * rhs.m_direction_ratios[1];
    pDirectionStep->m_direction_ratios[1] =
      -lhs.m_direction_ratios[0] * rhs.m_direction_ratios[2] + 
       lhs.m_direction_ratios[2] * rhs.m_direction_ratios[0];
    pDirectionStep->m_direction_ratios[2] = 
       lhs.m_direction_ratios[0] * rhs.m_direction_ratios[1] - 
       lhs.m_direction_ratios[1] * rhs.m_direction_ratios[0];
    pDirectionStep->isGood();
  }
  return pDirectionStep  ;
}

bool CDirectionStep::isGood( void)
{// using Linf norm here
  m_bGood=((restol < fabs(m_direction_ratios[0])) || 
           (restol < fabs(m_direction_ratios[1])) || 
           (restol < fabs(m_direction_ratios[2]))
        );
  return m_bGood;
}

HRESULT CDirectionStep::negate()
{
  m_direction_ratios[0] =-m_direction_ratios[0] ;
  m_direction_ratios[1] =-m_direction_ratios[1] ;
  m_direction_ratios[2] =-m_direction_ratios[2] ;
  return S_OK;
}

HRESULT CDirectionStep::normalize()
{
  double dLen = getLength();
  if (!withinTol()) {
    m_direction_ratios[0] /= dLen ;
    m_direction_ratios[1] /= dLen ;
    m_direction_ratios[2] /= dLen ;
  }
  else {
    m_direction_ratios[0] = 0.e0 ;
    m_direction_ratios[1] = 0.e0 ;
    m_direction_ratios[2] = 0.e0 ;
  }
  return S_OK;
}
