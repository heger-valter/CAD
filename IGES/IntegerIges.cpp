// IntegerIges.cpp: implementation of the CIntegerIges class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "scribble.h"
#include "IntegerIges.h"
#include "igesArchive.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDataIges::CDataIges(int i)
: m_i(i)
{

}

CDataIges::~CDataIges()
{

}

void CDataIges::Serialize(igesArchive &rIgesArchive)
{

}

CIntegerIges::CIntegerIges(int i)
: m_i(i)
, CDataIges(i)
{

}

CIntegerIges::~CIntegerIges()
{

}

CFloatIges::CFloatIges(float f)
: m_f( f)
{

}

CFloatIges::~CFloatIges()
{

}
