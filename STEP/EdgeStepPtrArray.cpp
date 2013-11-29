// EdgeStepPtrArray.cpp: implementation of the CEdgeStepPtrArray class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "scribble.h"
#include "EdgeStepPtrArray.h"
#include "EdgeStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEdgeStepPtrArray::CEdgeStepPtrArray(int iNewSize)
{
  SetSize( iNewSize);
  m_hash = new CPtrArray();
  m_hash->SetSize(iNewSize);
}

CEdgeStepPtrArray::~CEdgeStepPtrArray()
{
  delete m_hash ;
}

void CEdgeStepPtrArray::SetAt(int nIndex, CEdgeStep *pEdgeStep)
{
  int nNewIndex = nIndex;
  m_hash->SetAt(nIndex, (void*)nNewIndex);

  if (nNewIndex == nIndex) {
    CPtrArray::SetAt(  nNewIndex , pEdgeStep);
  }
  return;
}

CEdgeStep* CEdgeStepPtrArray::GetAt(int nIndex)
{
  int nNewIndex = (int) m_hash->GetAt( nIndex);
  return (CEdgeStep*)CPtrArray::GetAt( nNewIndex);
}
