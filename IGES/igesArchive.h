// igesArchive.h: interface for the igesArchive class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IGESARCHIVE_H__FDB42E43_8B31_11D5_8CB5_00D00908C1A5__INCLUDED_)
#define AFX_IGESARCHIVE_H__FDB42E43_8B31_11D5_8CB5_00D00908C1A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afx.h>// CArchive
#include <fstream.h>//ofstream
class CIntegerIges;

class igesFile : public CFile 
{
public:
	igesFile();
	virtual ~igesFile();

};

// I don't want to use CString here because I want to write directly into a file, as opposed to storing in CString, and then to file
// not using CArchive because CArchive puts 0xff in prefix and has a limit of 4K!
class igesArchive : public ofstream  
{
public:
	igesArchive( const char* szName, int nMode = ios::out, int nProt = filebuf::openprot );
	virtual ~igesArchive();
  
//igesArchive& operator<<(const CIntegerIges  i);
  igesArchive& operator<<(const __int32       i);
  igesArchive& operator<<(const CString       s);
  igesArchive& operator<<(const char          c);
  igesArchive& operator<<(const char*         pC);
  igesArchive& operator<<( CIntegerIges  i);

};

#endif // !defined(AFX_IGESARCHIVE_H__FDB42E43_8B31_11D5_8CB5_00D00908C1A5__INCLUDED_)
