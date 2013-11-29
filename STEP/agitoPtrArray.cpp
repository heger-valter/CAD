// agitoPtrArray.cpp: implementation of the agitoPtrArray class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BaseStep.h"
#include "scribble.h"
#include "agitoPtrArray.h"
#include <afxcoll.h>
#include <Afxwin.h> // HRESULT

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

agitoPtrArray::agitoPtrArray(
                            //CSurfaceStep& rSurfaceContainingLoop
                            )
: CPtrArray()
, m_bSearch(false)
, m_iLast(0)
//, m_rSurfaceContainingLoop (rSurfaceContainingLoop)
{

}

agitoPtrArray::~agitoPtrArray()
{

}

void agitoPtrArray::RemoveAt(int nIndex, int nCount)
{
  CPtrArray::RemoveAt( nIndex);

  for (int l=nIndex; l < GetSize(); l++) { 
    CBaseStep* pBaseStep = (CBaseStep*) GetAt(l);
    pBaseStep->m_g_ptrArrayIndex = l;
  }
  return;
}
 
int agitoPtrArray::Add(void* newElement)
{
  if (m_bSearch) {
    for (int i = m_iLast; i< GetSize(); i++) {
      if (NULL == GetAt(i)) {
        SetAt(i, newElement);
        m_iLast = i+1;
        return i;
      }
    }
    m_bSearch = false;
    m_iLast = 0;
  }
  return CPtrArray::Add( newElement);
}

HRESULT agitoPtrArray::SearchFromTheTop()
{
  m_bSearch = true;
  m_iLast = 0;
  return S_OK;
}

CrcPtrArray::CrcPtrArray()
:  CPtrArray()
{

}

CrcPtrArray::~CrcPtrArray()
{
  for (int i = 0; i<CPtrArray::GetSize();i++){
    CBaseStep* pBS = (CBaseStep*) CPtrArray::GetAt(i);
    if (NULL != pBS) {
      ASSERT_VALID( pBS);
      try{
        pBS->release();
      } catch(...){
        TRACE1("~CrcPtrArray %p\n", pBS);
        pBS=NULL;
      }
    }
  }
  SetSize(0);// wh 01/22/02
}

void CrcPtrArray::RemoveAt(int nIndex, int nCount)
{
  CObject* pO = (CObject*) CPtrArray::GetAt( nIndex);
  if (NULL != pO) { 
    ASSERT_VALID( pO);
    CBaseStep* pBS = dynamic_cast<CBaseStep*>( pO);
    ASSERT( NULL != pBS );
    if (NULL != pBS) { 
      for (int i=0; i<nCount; i++){
        pBS->release();// wh 10/20/01
      }
    }
  }
  CPtrArray::RemoveAt( nIndex, nCount);
  return;
}

int CrcPtrArray::Add(void* newElement)
{
  ASSERT_VALID( (CObject*)newElement);
  CBaseStep* pBS = dynamic_cast<CBaseStep*>((CObject*)(newElement));
  ASSERT( NULL != pBS );
  if (NULL != pBS) {
    pBS->addRef();
  }
  return CPtrArray::Add( newElement);
}

void CrcPtrArray::InsertAt(int nIndex, void* newElement, int nCount)
{
  ASSERT_VALID( (CObject*)newElement);
  CBaseStep* pBS = dynamic_cast<CBaseStep*>((CObject*)(newElement));
  ASSERT( NULL != pBS );
  if (NULL != pBS) { 
    for (int i=0; i<nCount; i++){
      pBS->addRef();
    }
  }
  CPtrArray::InsertAt(nIndex, newElement, nCount);
}
#if 0
void* CrcPtrArray::GetAt(int nIndex)
{
  CBaseStep* newElement = (CBaseStep*)
    CPtrArray::GetAt( nIndex);
  if (NULL != newElement){
    newElement->addRef();
  }
  return newElement; 
}
#endif
void CrcPtrArray::SetAt(int nIndex, void* newElement)
{
  CBaseStep* pBS = dynamic_cast<CBaseStep*>((CObject*)CPtrArray::GetAt(nIndex));
  if (NULL != pBS){
    pBS->release();
  }

  if (NULL != newElement){
    ASSERT_VALID( (CObject*)newElement);
    pBS = dynamic_cast<CBaseStep*>((CObject*)(newElement));
    ASSERT( NULL != pBS );
    pBS->addRef();
  }
  CPtrArray::SetAt(nIndex, newElement);
}

HRESULT paramPtrArray::simplify()
{
  CCartesian_pointStep* pPt = NULL;
  for ( int i = 0
        ; i< this->GetSize()
        ; i++){
    pPt = (CCartesian_pointStep* )GetAt(i);
    if (NULL == pPt) {
      RemoveAt(i);
      for (int k = i; k<GetSize(); k++){
        aParam.SetAt(k, aParam.GetAt(i+1));
      }
      i--;
    }
    else {
      break;
    }
  } 
  i++;
  for (  ; 
         i < this->GetSize()
           // wh 01/29/01
           ; 
         i++)
    {
      if (  (NULL== this->GetAt(i) ) ||
            ((CCartesian_pointStep*) pPt == (CCartesian_pointStep*)this->GetAt(i) )){
            RemoveAt(i);
            for (int k = i; k<GetSize(); k++){
              aParam.SetAt(k, aParam.GetAt(i+1));
            }
            i--;
      } else {
        if (NULL != GetAt(i) ){
          double dist2 = getLength2((CCartesian_pointStep*) pPt
            ,(CCartesian_pointStep*)this->GetAt(i) );
          if (withinTol2(dist2)) {
            pPt->release();
            RemoveAt(i);
            for (int k = i; k<GetSize()-1; k++){
              aParam.SetAt(k, aParam.GetAt(i+1));
            }
            i--;
          }
        }
      }

      if (i > -1){
        pPt = (CCartesian_pointStep* )GetAt(i);
      }
    }

  return S_OK;
}

// order them in increasing param w matter on the lhs
HRESULT paramPtrArray::orderByParam( CDirectionStep* pDirInc)
{ 
  if (GetSize() > 0){
    if ((double )aParam.GetAt(0) < 0.0e0){
      double dTemp = 0.e0 ;
      aParam.SetAt(0, (DWORD) dTemp );
    }
    for (int i =1; i< GetSize(); i++){
        if ( (double )aParam.GetAt(i) < 0.e0){
            CDirectionStep p0p1( NULL
              , *(CCartesian_pointStep*)this->GetAt(0) 
              , *(CCartesian_pointStep*)this->GetAt(i) );

            aParam.SetAt(i, (DWORD)p0p1.getLength());
            double dp = dotProduct( *pDirInc, p0p1);
            if (dp<0){
              double di = -(double)aParam.GetAt(i) ;
              aParam.SetAt(i, (DWORD) di);
            }
        }
        else {
          break;
        }
    }
    for (    i =0; i< GetSize(); i++){
      for (int j = i+1; j<GetSize(); j++){
        double temp = (double )aParam.GetAt(i);
        if (temp > (double) aParam.GetAt(j)){
          aParam.SetAt(i, aParam.GetAt(j));
          aParam.SetAt(j, (DWORD)temp);

          CBaseStep* iTemp = (CBaseStep*) CPtrArray::GetAt(i);//1
          CBaseStep* jTemp = (CBaseStep*) CPtrArray::GetAt(j);//1
          CPtrArray::SetAt( i, (LPVOID) jTemp);
          CPtrArray::SetAt( j, (LPVOID) iTemp);
        }
      }
    }
  }
  return S_OK;
}

paramPtrArray::paramPtrArray( int iSize)
: CrcPtrArray()
{
  aParam.SetSize( 2 * iSize);
  for (int i=0; i<2 * iSize;i++){
    aParam.SetAt( i, DWORD(-DBL_MAX));
  }
}

paramPtrArray::~paramPtrArray ()
{
  aParam.SetSize(0);
}

loopXPts::loopXPts()
: m_pSurfaceContainingLoop( NULL)
{

}

loopXPts::~loopXPts()
{

}

//////////////////////////////////////////////////////////
// who  date      history
//-----------------------
// wh 02/16/02    loopXPts added to track the surface which contains the intersection pts
