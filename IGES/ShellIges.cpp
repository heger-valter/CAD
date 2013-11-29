// ShellIges.cpp: implementation of the CShellIges class.
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
//#include "scribble.h"
#include "ShellIges.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShellIges::CShellIges()
: CBaseIges( (void*)NULL)
{
  m_iEntityTypeNum = 514;

}

CShellIges::~CShellIges()
{

}

void CShellIges::Serialize(igesArchive &ar)
{

}
