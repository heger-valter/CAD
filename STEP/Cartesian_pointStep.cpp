// Cartesian_pointStep.cpp: implementation of the CCartesian_pointStep0 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#ifdef _WINDOWS 
#include "scribble.h"
#endif

#include "Cartesian_pointStep.h"
#include "math.h"//large
#include "Cartesian_tranformation_operator_3dStep.h"
#include "VectorStep.h"
#include "Cartesian_pointStepPtrArray.h"
#include <FLOAT.H>// DBL_MAX, FLT_MAX


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCartesian_pointStep::CCartesian_pointStep(CBaseStep*pIn, double x, double y, double z, int dim)
: CPointStep(pIn)
, m_dim(dim)
{
  nameClass("CARTESIAN_POINT");
  coordinates[0] = x;
  coordinates[1] = y;
  coordinates[2] = z;
#ifdef  EXPOSE      
  fprintf( g_errorLog, " CCartesian_pointStep (#%d ), m_iRef=%u\n", getNum(), getRefCnt());
#endif//EXPOSE   
}

CCartesian_pointStep::~CCartesian_pointStep()
{
#ifdef  EXPOSE      
  fprintf( g_errorLog, "~CCartesian_pointStep (#%d ), m_iRef=%u\n", getNum(), getRefCnt());
#endif//EXPOSE   
}

HRESULT CCartesian_pointStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  else {
    return E_FAIL;
  }
}
void CCartesian_pointStep::Serialize(stepArchive &ar)
{
  try{
    if (!isSerialized()){
      setSerialized();
      writePre(ar);
      writeLabel(ar);
      writeDouble(ar, coordinates, m_dim);
      writePost(ar);

  #ifdef   WRITEEULER
      CBaseStep* pBaseStep=NULL;
      backPtr( pBaseStep);
      if (NULL != pBaseStep){
        CManifold_solid_brepStep* pManifold_solid_brepStep=(CManifold_solid_brepStep*) pBaseStep;
        pManifold_solid_brepStep->eulerCnt.m_numVertices++;
      }
  #endif//WRITEEULER
    }
  }
  catch(...){
    setSerialized();
    ar << "\n/*Errors detected in "<< this->m_szTheClass <<"::Serialize #\n";
//  ar << getNum();
    ar <<   ", but continuing*/\n" ;    
  }
}


double getLength2( CCartesian_pointStep* pCartesian_pointElement0, 
                   CCartesian_pointStep* pCartesian_pointElement1 )
{
    double dDist = pCartesian_pointElement0->coordinates[0] - pCartesian_pointElement1->coordinates[0];
    double dDist2  = dDist * dDist ;
           dDist = pCartesian_pointElement0->coordinates[1] - pCartesian_pointElement1->coordinates[1];
           dDist2 += dDist * dDist ;
           dDist = pCartesian_pointElement0->coordinates[2] - pCartesian_pointElement1->coordinates[2];
           dDist2 += dDist * dDist ;
  return dDist2  ;
}

//inline 
bool withinTol2(double dDist2)
{
  return (dDist2 < restol2);
}

bool withinTol(   CCartesian_pointStep* pCartesian_pointElement0, 
                  CCartesian_pointStep* pCartesian_pointElement1 )
{
  double dDist2 = getLength2( pCartesian_pointElement0, pCartesian_pointElement1 );
  return withinTol2(dDist2);
}

double getLength( CCartesian_pointStep* pCartesian_pointElement0, 
                  CCartesian_pointStep* pCartesian_pointElement1 )
{
  double dDist2 = getLength2( pCartesian_pointElement0, 
                              pCartesian_pointElement1);
  if (restol2 < dDist2 ){
    dDist2  = sqrt( dDist2  );
  }
  else {
    dDist2  = 0.0e0;
  }
  return dDist2  ;
}

CCartesian_pointStep& CCartesian_pointStep::operator +=(CCartesian_tranformation_operator_3dStep &rLhs)
{
  
#if 0
  coordinates[0] = coordinates[0] * rLhs.m_Transformation[0][0] +coordinates[1] * rLhs.m_Transformation[0][1] +coordinates[2] * rLhs.m_Transformation[0][2];
  coordinates[1] = coordinates[0] * rLhs.m_Transformation[1][0] +coordinates[1] * rLhs.m_Transformation[1][1] +coordinates[2] * rLhs.m_Transformation[1][2];
  coordinates[2] = coordinates[0] * rLhs.m_Transformation[2][0] +coordinates[1] * rLhs.m_Transformation[2][1] +coordinates[2] * rLhs.m_Transformation[2][2];
#else
  coordinates[0] = coordinates[0] * rLhs.transform.m_Transformation[0][0] +coordinates[1] * rLhs.transform.m_Transformation[0][1] +coordinates[2] * rLhs.transform.m_Transformation[0][2];
  coordinates[1] = coordinates[0] * rLhs.transform.m_Transformation[1][0] +coordinates[1] * rLhs.transform.m_Transformation[1][1] +coordinates[2] * rLhs.transform.m_Transformation[1][2];
  coordinates[2] = coordinates[0] * rLhs.transform.m_Transformation[2][0] +coordinates[1] * rLhs.transform.m_Transformation[2][1] +coordinates[2] * rLhs.transform.m_Transformation[2][2];
#endif 
  return *this;
}

CCartesian_pointStep& CCartesian_pointStep::operator *=(CCartesian_tranformation_operator_3dStep &rLhs)
{
  
  coordinates[0] = coordinates[0] * rLhs.transform.m_Transformation[0][0] +coordinates[1] * rLhs.transform.m_Transformation[0][1] +coordinates[2] * rLhs.transform.m_Transformation[0][2];
  coordinates[1] = coordinates[0] * rLhs.transform.m_Transformation[1][0] +coordinates[1] * rLhs.transform.m_Transformation[1][1] +coordinates[2] * rLhs.transform.m_Transformation[1][2];
  coordinates[2] = coordinates[0] * rLhs.transform.m_Transformation[2][0] +coordinates[1] * rLhs.transform.m_Transformation[2][1] +coordinates[2] * rLhs.transform.m_Transformation[2][2];
  return *this;
}

CCartesian_pointStep& CCartesian_pointStep::operator +=(CCartesian_pointStep &rLhs)
{
  coordinates[0] += rLhs.coordinates[0];
  coordinates[1] += rLhs.coordinates[1];
  coordinates[2] += rLhs.coordinates[2];
  return *this;
}

CCartesian_pointStep& CCartesian_pointStep::operator -=(CCartesian_pointStep &rLhs)
{
  //m_dim = min(m_dim, rhs.m_dim); for (int i =0; i < m_dim; i++) {  coordinates[i] -= rLhs.coordinates[i];}
  coordinates[0] -= rLhs.coordinates[0];
  coordinates[1] -= rLhs.coordinates[1];
  coordinates[2] -= rLhs.coordinates[2];
  return *this;
}


CCartesian_pointStep& CCartesian_pointStep::operator +=(CVectorStep &rLhs)
{  
  //m_dim = min(m_dim, rhs.m_dim); for (int i =0; i < m_dim; i++) {  coordinates[i] += rLhs.coordinates[i];}
  coordinates[0] += rLhs.coordinates[0];
  coordinates[1] += rLhs.coordinates[1];
  coordinates[2] += rLhs.coordinates[2];
  return *this;
}

CCartesian_pointStep::CCartesian_pointStep( CBaseStep* pBaseStep, CCartesian_pointStep &rhs)
: CPointStep( this)
{
  m_pParent = pBaseStep;
  nameClass("CARTESIAN_POINT");
  coordinates[0] = rhs.coordinates[0];
  coordinates[1] = rhs.coordinates[1];
  coordinates[2] = rhs.coordinates[2];
  m_dim = rhs.m_dim;//CGeometric_representation_contextStep::m_iDim;
#ifdef  EXPOSE      
  fprintf( g_errorLog, " CCartesian_pointStep (#%d ), m_iRef=%u\n", getNum(), getRefCnt());
#endif//EXPOSE   
}

/*
bool CCartesian_pointStep::operator ==(CCartesian_pointStep& rhs)
{  
//return ( CPointStep(*this) ==(rhs));
  double dist =0.e0;
  dist = fabs(coordinates[0] - rhs.coordinates[0]);
  if (dist>restol){
    return false;
  }
  dist = fabs(coordinates[1] - rhs.coordinates[1]);
  if (dist>restol){
    return false;
  }
  dist = fabs(coordinates[2] - rhs.coordinates[2]);
  if (dist>restol){
    return false;
  }
  return true;
}
*/
CCartesian_pointStep& CCartesian_pointStep::operator=(CCartesian_pointStep& rhs)
{
  coordinates[0]= rhs.coordinates[0];
  coordinates[1]= rhs.coordinates[1];
  coordinates[2]= rhs.coordinates[2];
  return *this;
}

CCartesian_pointStep& CCartesian_pointStep::operator /=(float  fDivisor)
{ 
  ASSERT( fDivisor > restol);
  coordinates[0] /= fDivisor;
  coordinates[1] /= fDivisor;
  coordinates[2] /= fDivisor;
  return *this;
}

// use a template here
// the purpose of this function is to move their entries in the hash table
HRESULT CCartesian_pointStep::Rehash( int i
                                    , CCartesian_pointStepPtrArray *pCartesian_pointStepPtrArray)
{
  void* j = pCartesian_pointStepPtrArray->m_hash.GetAt(this->m_g_ptrArrayIndex);
  for ( int k=0; k < pCartesian_pointStepPtrArray->m_hash.GetSize(); k++) {
    if (pCartesian_pointStepPtrArray->m_hash.GetAt( k ) == j) {
      pCartesian_pointStepPtrArray->m_hash.SetAt( m_g_ptrArrayIndex, (void*)i);
    }
  }
  return S_OK;
}
/*
CCartesian_pointStep* mid(CCartesian_pointStep &p0, CCartesian_pointStep &p1)
{
  CCartesian_pointStep* me = new CCartesian_pointStep( NULL, p0);
  me->coordinates[0]+=p1.coordinates[0];
  me->coordinates[1]+=p1.coordinates[1];
  me->coordinates[2]+=p1.coordinates[2];
  me->coordinates[0]/=2.e0;
  me->coordinates[1]/=2.e0;
  me->coordinates[2]/=2.e0;
  return me;
}
*/
//////////////////////////////////////////////////////////
// who  date      history
// wh   11/24/01  set parent 
//
