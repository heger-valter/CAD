// igesArchive.cpp: implementation of the igesArchive class.
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
//#include "scribble.h"
#include "igesArchive.h"
#include "IntegerIges.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


igesFile::igesFile( )
{

}

igesFile::~igesFile()
{

}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

igesArchive::igesArchive( const char* szName, int nMode , int nProt )
: ofstream( szName, nMode, nProt )
{

}

igesArchive::~igesArchive()
{

}
/*
igesArchive& igesArchive::operator <<( const CIntegerIges i)
{
  *this << i.m_i;
  return *this;
}
*/
igesArchive& igesArchive::operator <<( const __int32 i )
{
  (ofstream)(*this) << i;
  return *this;
}

igesArchive& igesArchive::operator <<( const CString s )
{
//  *this << *(s.GetBufferSetLength(s.GetLength()+1));
//  s.ReleaseBuffer();
  (ofstream)(*this) << s;
  return *this;
}

igesArchive& igesArchive::operator <<( const char c)
{
  (ofstream)*this << c;
  return *this;
}

igesArchive& igesArchive::operator <<( const char* pc)
{
  (ofstream)*this << pc;
  return *this;
}

igesArchive& igesArchive::operator <<( CIntegerIges i)
{
  (ofstream)*this << i.m_i;
  return *this;
}

