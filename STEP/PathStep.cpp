// PathStep.cpp: implementation of the CPathStep class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _WINDOWS
#include "stdafx.h"
#endif

#include "PathStep.h"

#include "Oriented_EdgeStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPathStep::CPathStep( CBaseStep*pIn, int iNewSize=0 )
: CTopological_representation_itemStep( pIn)
//, m_aEdge_list(iNewSize)
{
  nameClass("Path");  
  m_aEdge_list.SetSize( iNewSize);
}

CPathStep::~CPathStep()
{
  m_aEdge_list.SetSize( 0);
}

HRESULT CPathStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  return E_FAIL;
}

#if 0
void* //PASCAL 
      CPathStep::operator new(unsigned int nSize, const char * lpszFileName,
int nLine)
{
  return CTopological_representation_itemStep::operator new( nSize, lpszFileName, nLine);
}

void  PASCAL CPathStep::operator delete(void* p)
{
  CTopological_representation_itemStep::operator delete( p);
}
#endif

HRESULT CPathStep::demote()
{
  // big noop
  return S_OK;
}

//////////////////////////////////////////////////////////
// who  date      history
