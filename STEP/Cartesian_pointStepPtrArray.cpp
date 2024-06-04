// Cartesian_pointStepPtrArray.cpp: implementation of the CCartesian_pointStepPtrArray0 class.
//
//////////////////////////////////////////////////////////////////////

#include "afx.h"
#ifdef _WINDOWS
#include "stdafx.h"
#endif

#ifdef _WINDOWS 
#include "scribble.h"
#endif

#include "Cartesian_pointStep.h"
#include "Cartesian_pointStepPtrArray.h"

// equality tolerance as called by expresso
double  restol   = 1.e-3;// resolution tolerance, the farthest two points can be apart and still considered to be the same point.
double  restol2  = 1.e-6;// restol2 = restol * restol ;// save a couple of flops

//double& r_restol = restol;
double  fourRestol   = 4.e-2;
double  sixteenRestol2  = 16.e-6;// allow a neighborhood this big to trap round off errors


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//CPtrArray CCartesian_pointStepPtrArray::m_hash;

CCartesian_pointStepPtrArray::CCartesian_pointStepPtrArray( int iSize)
: CPtrArray()
{
  ASSERT(iSize > 0);

  ASSERT(0 == m_hash.GetSize());
  if (0 != m_hash.GetSize()){
    fin();
  }
  m_hash.SetSize( iSize, 128 + iSize/2);
}

CCartesian_pointStepPtrArray::~CCartesian_pointStepPtrArray()
{ 
  fin();
}

HRESULT CCartesian_pointStepPtrArray::fin()
{
  bool bCartesian_pointStep = false;
#ifdef  EXPOSE      
  fprintf( g_errorLog, "\n\n");
#endif//EXPOSE   
  for (int i = m_hash.GetSize()-1; i>=0; i--){
    int j = (int) m_hash.GetAt(i);
    CCartesian_pointStep* pCartesian_pointStep = (CCartesian_pointStep*)(CPtrArray::GetAt( j));
    
    if (!bCartesian_pointStep ) {
      ASSERT_VALID( pCartesian_pointStep);
    }
#ifdef  EXPOSE      
      fprintf( g_errorLog, "\t releasing CCartesian_pointStepPtrArray[ %d ].\n", i);
#endif//EXPOSE   
      try{ 
        if (NULL != pCartesian_pointStep){
          pCartesian_pointStep->release();
        } else {
      bCartesian_pointStep = true;
#ifdef  EXPOSE      
      fprintf( g_errorLog, "\t CCartesian_pointStepPtrArray[ %d ] released too often.\n", i);
#endif//EXPOSE           
        }
    }
    catch(...){
      bCartesian_pointStep = true;
#ifdef  EXPOSE      
      fprintf( g_errorLog, "\t CCartesian_pointStepPtrArray[ %d ] released too often.\n", i);
#endif//EXPOSE   
    }
  }
  m_hash.SetSize(0) ;
//m_hash = NULL;
#ifdef  EXPOSE      
  fprintf( g_errorLog, "\n");
#endif//EXPOSE   
  return S_OK;
}


// be careful, if restol is too small, lots of computations needed to make system stable.
// if restol is too large, features will disappear (congeal into one point).
// maybe this system variable should be overridedable from an instrux file.  
// sort of like how to define pi=3.14 or pi=3.141592654

int CCartesian_pointStepPtrArray::SetAt( int nIndex, 
                                         CCartesian_pointStep*& pNewElement 
                                        )
{
  CCartesian_pointStep* pCartesian_pointElement = (CCartesian_pointStep*) pNewElement;
  int nNewIndex = nIndex;

#if 1
  for (int i = 0; i< nIndex; i++){
    int j = (int) m_hash.GetAt(i);
    CCartesian_pointStep* pCartesian_pointElement1 = (CCartesian_pointStep*)(CPtrArray::GetAt( j));
    ASSERT( NULL != pCartesian_pointElement1);
    if ( NULL == pCartesian_pointElement1){// hack!!
      pCartesian_pointElement1 = (CCartesian_pointStep*)(CPtrArray::GetAt( i));
    }
    double dDist2 = DBL_MAX;
    try{
      dDist2 = getLength2( pCartesian_pointElement, pCartesian_pointElement1);
    }
    catch(...){
//      return -1;
      throw;
    }
    if (dDist2 < restol2) {
      nNewIndex = i;
      m_hash.SetAt( nIndex, (void*)nNewIndex);
      ASSERT_VALID(pNewElement);
      ASSERT(1 == pNewElement->getRefCnt());
      delete pNewElement;// throw the old one away 
      pNewElement=NULL;
      TRACE2("set CCartesian_pointStepPtrArray[%d] is (#%d ) \n", nIndex, pCartesian_pointElement1->getNum());
#ifdef  EXPOSE      
      fprintf( g_errorLog, "\t    set CCartesian_pointStepPtrArray[%d] is (#%d ) \n", nIndex, pCartesian_pointElement1->getNum());
#endif//EXPOSE   
      pCartesian_pointElement1->addRef();// move the ref count here
//    pNewElement->m_pTechnadrawEntity = pCartesian_pointElement1->m_pTechnadrawEntity;
      return nNewIndex;
      break;
    }
  }
#else
//  if (-1 != iDupe){
//    nNewIndex = iDupe;
//  }
#endif

  m_hash.SetAt(nIndex, (void*)nNewIndex);

  if (nNewIndex == nIndex) {
    CCartesian_pointStep* pOldElement = (CCartesian_pointStep*)CPtrArray::GetAt( nNewIndex);
    if( NULL != pOldElement){
      pOldElement->release();
    }
    CPtrArray::SetAt( nNewIndex, pNewElement);
#ifdef  EXPOSE      
    fprintf( g_errorLog, "\t    set CCartesian_pointStepPtrArray[%d] is (#%d ) \n", nIndex, pNewElement->getNum());
#endif//EXPOSE   
    pNewElement->addRef();// wh 10/09/01
  }
  else {
//  CCartesian_pointStep* pOldElement = (CCartesian_pointStep*)CPtrArray::GetAt( nNewIndex);
//  pNewElement->m_pTechnadrawEntity = pOldElement->m_pTechnadrawEntity ;
    delete pNewElement;
    pNewElement=NULL;
  }
  return nIndex;
}

//CPointStep::
CCartesian_pointStep* CCartesian_pointStepPtrArray::GetAt(int nIndex)
{ 
  ASSERT( nIndex < m_hash.GetSize());
  if (nIndex >= m_hash.GetSize()) { 
#ifdef   EXPOSE
    fprintf( g_errorLog, "CCartesian_pointStepPtrArray[ %d ] out of range.\n", nIndex);
#endif //EXPOSE
    return NULL;// wh 9/19/01
  }
  int nNewIndex = (int)m_hash.GetAt(nIndex);
  return (CCartesian_pointStep* ) CPtrArray::GetAt( nNewIndex);
}

/*
CPointStepPtrArray::CPointStepPtrArray()
: CPtrArray()
{
  m_hash = new CPtrArray();
}

CPointStepPtrArray::~CPointStepPtrArray()
{
  delete m_hash ;
}

int CPointStepPtrArray::SetAt(int nIndex, void* newElement)
{
  CPointStep* pCartesian_pointElement = (CPointStep*) newElement;
  int nNewIndex = nIndex;

#if 1
  for (int i = 0; i< GetSize(); i++){
    int j = m_hash->GetAt(i);
    CPointStep* pCartesian_pointElement1 = (CPointStep*)CPtrArray::GetAt( j);
    double dDist = pCartesian_pointElement->coordinates[0] - pCartesian_pointElement1->coordinates[0];
    double dDist2 = dDist * dDist ;
           dDist = pCartesian_pointElement->coordinates[1] - pCartesian_pointElement1->coordinates[1];
           dDist2 +=dDist * dDist ;
           dDist = pCartesian_pointElement->coordinates[2] - pCartesian_pointElement1->coordinates[2];
           dDist2 +=dDist * dDist ;

    if (dDist2 < restol2) {
      nNewIndex = i;
      return nNewIndex;
      break;
    }
  }
#endif

  if (nNewIndex == nIndex) {
    CPtrArray::SetAt( nNewIndex, newElement);
  }
  return nIndex;
}
//CPointStep::
void* CPointStepPtrArray::GetAt(int nIndex)
{
  unsigned int nNewIndex = m_hash->GetAt(nIndex);
  return CPtrArray::GetAt( nNewIndex);
}
*/

// find the point in the collection, 
//  if it is there, delete & return it as old, 
// else set it as old 
HRESULT CCartesian_pointStepPtrArray::Find( CCartesian_pointStep*&pCartesian_pointNew, 
                                            CCartesian_pointStep*&pCartesian_pointOld)
{
  for (int i = 0; i< m_hash.GetSize(); i++){
    int j = (int) m_hash.GetAt(i);
    if (j == i){
    pCartesian_pointOld = (CCartesian_pointStep*)(CPtrArray::GetAt( j));
    ASSERT( NULL != pCartesian_pointOld);
    if ( NULL == pCartesian_pointOld){// hack!!
      pCartesian_pointOld = (CCartesian_pointStep*)(CPtrArray::GetAt( i));
    }
    double dDist2 = DBL_MAX;
    try{
      dDist2 = getLength2( pCartesian_pointNew, pCartesian_pointOld);
    }
    catch(...){
      throw;
    }
    if (dDist2 < restol2) {
      delete pCartesian_pointNew;// throw the old one away 
      pCartesian_pointNew=NULL;
      return S_OK;
    }
    }
  }// next i
  pCartesian_pointOld =  pCartesian_pointNew;
  return S_OK;
}

int CCartesian_pointStepPtrArray::Add( void *newElement)
{
  CBaseStep* pB = (CBaseStep* ) newElement;
  ASSERT_VALID(pB );
  pB->addRef();
  m_hash.Add( (void*) (m_hash.GetSize()-1));
  return CPtrArray::Add(newElement);
}

