// EdgeIges.cpp: implementation of the CEdgeIges class.
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
//#include "scribble.h"
#include "EdgeIges.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEdgeIges::CEdgeIges()
: CBaseIges( (void*)NULL)
{
  m_iEntityTypeNum = 504;

}

CEdgeIges::~CEdgeIges()
{

}

void CEdgeIges::Serialize(igesArchive &ar)
{

}

CEdgeListIges::CEdgeListIges()
//: CBaseIges( (void*)NULL)
{
  m_iEntityTypeNum = 504;

}

CEdgeListIges::~CEdgeListIges()
{

}

void CEdgeListIges::Serialize(igesArchive &ar)
{

}
