// VectorStep.cpp: implementation of the CVectorStep class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VectorStep.h"
#include "stepArchive.h"
#include "VectorStep.h"
#include "DirectionStep.h"
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

CVectorStep::CVectorStep( CCartesian_pointStep& p0
                        , CCartesian_pointStep& p1
                        )
: CGeometric_representation_itemStep(this), bAssertDestructor(false)
{
  nameClass("Vector");
  coordinates[0] = p1.coordinates[0]  - p0.coordinates[0] ;
  coordinates[1] = p1.coordinates[1]  - p0.coordinates[1] ;
  coordinates[2] = p1.coordinates[2]  - p0.coordinates[2] ;
  m_dMagnitude = getLength();
  m_pOrientation= new CDirectionStep (NULL, p0,  p1);
//if (NULL==m_pOrientation){ 
//  throw CMemoryException;// thrown by new!
//}
}

CVectorStep::CVectorStep( CCartesian_pointStep& p0)
: CGeometric_representation_itemStep(this), bAssertDestructor(false)
{
  nameClass("Vector");
  coordinates[0] = p0.coordinates[0] ;// are you sure this is right//changed wh 05/11/01
  coordinates[1] = p0.coordinates[1] ;
  coordinates[2] = p0.coordinates[2] ;
  m_dMagnitude = getLength();
  m_pOrientation= new CDirectionStep (p0);
//m_pOrientation->addRef();
}

// constuctor to make a vector from a direction
CVectorStep::CVectorStep(CDirectionStep &rDirectionStep)
  :  CGeometric_representation_itemStep( NULL), bAssertDestructor(false)
{
  nameClass("Vector");
  coordinates[0] = rDirectionStep.m_direction_ratios[0];
  coordinates[1] = rDirectionStep.m_direction_ratios[1] ;
  coordinates[2] = rDirectionStep.m_direction_ratios[2] ;
  m_dMagnitude = getLength();
//m_pOrientation= &rDirectionStep;
  m_pOrientation= new CDirectionStep (rDirectionStep);
//m_pOrientation->addRef();
}

CVectorStep::~CVectorStep()
{
  if ( !bAssertDestructor){
    ASSERT_VALID(m_pOrientation);
    bAssertDestructor=true;
  }
  try{
    m_pOrientation->release();
  }
  catch(...){
    TRACE2("~CVectorStep, for CVectorStep #%d m_pOrientation=%p\n", this->getNum(), m_pOrientation);
  }
  m_pOrientation=NULL;
}

void CVectorStep::Serialize(stepArchive &ar)
{
  try{
    if (!isSerialized()){
      setSerialized();
      writePre( ar);
      ar << "'',#";
      ar << m_pOrientation->getNum();
      ar << ",";
      ar << m_pOrientation->getLength( );
//    writeDouble( ar, coordinates,sizeof(coordinates )/sizeof(coordinates[0]));
      writePost( ar);

#ifdef  _DEBUG
      ASSERT( getLength2( )>restol2);
      if( getLength2( )< restol2){
        ar << "/* Danger, zero length vector!*/\n";
      }
#endif//_DEBUG

      m_pOrientation->Serialize( ar);
    }
  }
  catch(...){
    ar << "\n/*Errors detected in CVectorStep::Serialize #\n";
    ar <<   ", but continuing*/\n" ;    
    setSerialized();
  }
}


double getLength2( CVectorStep* pVectorStep0, 
                   CVectorStep* pVectorStep1 )
{
  CVectorStep vectorStep(*pVectorStep0);
  vectorStep -= *pVectorStep1;  
  double len2  = vectorStep.coordinates[0] * vectorStep.coordinates[0] ;
  
  for (int i = 1; i<
    3//CRepresentation_contextStep::m_iDim
    ;i++){
         len2 += vectorStep.coordinates[i] * vectorStep.coordinates[i] ;
  }
  return len2 ;
//return vectorStep.m_pOrientation->getLength2();//wh 03/30/02
}


CVectorStep::CVectorStep(CVectorStep &rVectorStep)
:  CGeometric_representation_itemStep(this)
, m_dMagnitude(rVectorStep.m_dMagnitude)
, m_pOrientation(rVectorStep.m_pOrientation)
, bAssertDestructor(false)
{
  nameClass("Vector");
  coordinates[0]=rVectorStep.coordinates[0];
  coordinates[1]=rVectorStep.coordinates[1];
  coordinates[2]=rVectorStep.coordinates[2];
  m_pOrientation= new 
    CDirectionStep( rVectorStep.m_pOrientation
    , rVectorStep.m_pOrientation->m_direction_ratios[0]
    , rVectorStep.m_pOrientation->m_direction_ratios[1]
    , rVectorStep.m_pOrientation->m_direction_ratios[2]
    );
}

CVectorStep& CVectorStep::operator -=(CVectorStep &rhs)
{
  *m_pOrientation -= *rhs.m_pOrientation;
  coordinates[0]  -= rhs.coordinates[0];
  coordinates[1]  -= rhs.coordinates[1];
  coordinates[2]  -= rhs.coordinates[2];
  m_dMagnitude = getLength();
  return *this;
}

CVectorStep& CVectorStep::operator *=(double d)
{
  m_dMagnitude    *= d;
  coordinates[0]  *= d;
  coordinates[1]  *= d;
  coordinates[2]  *= d;
  return *this;
}

double dotProduct( CVectorStep &rD0, CVectorStep &rD1)
{ 
  double dResult  = rD0.coordinates[0] * rD1.coordinates[0];
         dResult += rD0.coordinates[1] * rD1.coordinates[1];
         dResult += rD0.coordinates[2] * rD1.coordinates[2];
  if (restol2 > fabs( dResult)){
    dResult = 0.;
  }
  return dResult;
}

bool withinResdot( CVectorStep &rD0, CVectorStep &rD1)
{
  return false;
}

CVectorStep* crossProduct( CVectorStep &rD0, CVectorStep &rD1)
{
  CVectorStep* pCp = new CVectorStep;
  pCp->coordinates[0] = rD0.coordinates[1] * rD1.coordinates[2] 
                      - rD0.coordinates[2] * rD1.coordinates[1];
  pCp->coordinates[1] =-rD0.coordinates[0] * rD1.coordinates[2] 
                      + rD0.coordinates[2] * rD1.coordinates[0];
  pCp->coordinates[2] = rD0.coordinates[0] * rD1.coordinates[1] 
                      - rD0.coordinates[1] * rD1.coordinates[0];
  pCp->getLength();
  return pCp;
}


bool CVectorStep::normalize()
{
  m_dMagnitude = getLength2();
  if (m_dMagnitude >restol2){
    m_dMagnitude = sqrt( m_dMagnitude );
    for (int i=0; i<3; i++){// wh 7/17/01
      coordinates[i] /= m_dMagnitude ;
    }
    m_dMagnitude = 1.;
  }
  else{
    for (int i=0; i<3; i++){// wh 7/17/01
      coordinates[i] = 0.e0;
    }
    m_dMagnitude = 0.e0;
  }
  return false;
}

double CVectorStep::getLength2( void )
{
  double dist = coordinates[0]  * coordinates[0]  ;
  dist       += coordinates[1]  * coordinates[1]  ;
  dist       += coordinates[2]  * coordinates[2]  ;
  return dist;
}


double CVectorStep::getLength( void )
{
  m_dMagnitude = getLength2();
  if (m_dMagnitude > restol2 ){
    m_dMagnitude = sqrt(m_dMagnitude);
  }
  else {
    m_dMagnitude = 0.e0;
  }
  return m_dMagnitude;
}

CVectorStep::CVectorStep()
  :  CGeometric_representation_itemStep( NULL), bAssertDestructor(false)
{
  nameClass("Vector");
  m_pOrientation= new CDirectionStep( NULL, coordinates[0]
    , coordinates[1], coordinates[2]);// wh 10/27/01  0 0 0 ??
}

HRESULT CVectorStep::negate(void )
{
  coordinates[0] = -coordinates[0];
  coordinates[1] = -coordinates[1];
  coordinates[2] = -coordinates[2];
  return m_pOrientation->negate();
//S_OK;
}

HRESULT CVectorStep::withinTol( bool &bWithinTol )
{
  bWithinTol = getLength2() < restol2;
  return S_OK;
}

HRESULT CVectorStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  return E_FAIL;
}
