#if !defined(AFX_stepArchive_H__2F565CC4_3C23_43A4_AAA6_7775AA3AAA78__INCLUDED_)
#define      AFX_stepArchive_H__2F565CC4_3C23_43A4_AAA6_7775AA3AAA78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#pragma warning( disable : 4100)
#pragma warning( disable : 4663)
#pragma warning( disable : 4018)
#pragma warning( disable : 4146)
#pragma warning( disable : 4512)
#pragma warning( disable : 4244)

#include "afx.h"//CString
//class CString;

extern const char* szEndl;    
enum stepBool{ stepFalse, stepTrue};
// tbd derive it from MFC CArchive   // do not use CArchive because CArchive puts 0xff in prefix!
class iraroArchive : 
  public CString 
    //OMT is a relationship
{
  bool m_bIsStoring;
public:
  iraroArchive();
  virtual ~iraroArchive();
  iraroArchive& operator<<(const char*    pC);
  iraroArchive& operator<<(const int      i);
  iraroArchive& operator<<(const double   d);
  iraroArchive& operator<<(const float    d);
  iraroArchive& operator<<(const bool     b);// how is this differentiated from int or unsigned char
  iraroArchive& operator<<(const stepBool b);
};

// text encoding of wirth syntax notation  
class stepArchive 
{
  friend class step;
  friend class stepAdvanced;
  friend class stepFaceted;
  CPtrArray m_archives;
public:
	iraroArchive* GetAt(int i);
	HRESULT write( FILE* stream);
	HRESULT setEntry( int iEntry);
	int getEntry();
  int m_iEntry;
  stepArchive ();
  virtual ~stepArchive ();
	int GetLength();
  iraroArchive& operator<<(const char*    pC);
  iraroArchive& operator<<(const int      i);
  iraroArchive& operator<<(const double   d);
  iraroArchive& operator<<(const float    d);
  iraroArchive& operator<<(const bool     b);// how is this differentiated from int or unsigned char
  iraroArchive& operator<<(const stepBool b);
template <class T> 
  iraroArchive& operator<<(class T);
private:
	CPtrArray m_hashTable;
};

#if 0
// The schemaSerialize class reads in CONFIG_CONTROL_DESIGN and 
//  verifies that all the classes and interactions are in the current file!
// It does this using dynamic object serialization to allow different express modification.  
//  NB Unfortunately, this is not being done at this time.  
//  The big reason is that such a task is better done in LISP than C++!
//  Not only that, but the coding effort would be twice as great!

  class schemaArchive :  public  iraroArchive
{
public:
  schemaArchive ();
  virtual ~schemaArchive ();
};
#endif 

//////////////////////////////////////////////////////////
// who  date      history

#endif // !defined(AFX_stepArchive_H__2F565CC4_3C23_43A4_AAA6_7775AA3AAA78__INCLUDED_)
