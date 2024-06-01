// CircleStepPtrArray.cpp: implementation of the CCircleStepPtrArray class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#ifdef _WINDOWS 
#include "scribble.h"
#endif

#include "CircleStepPtrArray.h"
#include "CircleStep.h"
#include "agitoPtrArray.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCircleStepPtrArray::CCircleStepPtrArray()
{

}

CCircleStepPtrArray::~CCircleStepPtrArray()
{

}

int CCircleStepPtrArray::Add( CCircleStep* newElement)
{
  m_hash.Add( (void*)GetSize() );
  return CrcPtrArray::Add( newElement);
}

CCircleStep* CCircleStepPtrArray::GetAt(int  nIndex)
{
  int nNewIndex = (int)m_hash.GetAt(nIndex);
  return (CCircleStep*)CrcPtrArray::GetAt( nNewIndex);
}

int CCircleStepPtrArray::SetAt(int nIndex, CCircleStep* pCircleStep, bool& rbOrient )
{
  int nNewIndex = nIndex;
  m_hash.SetAt( nIndex, (void*)nIndex );
  CrcPtrArray::SetAt( nIndex, pCircleStep);
  return nIndex;
}