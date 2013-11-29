// Iges.h: interface for the Iges class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IGES_H__FDB42E42_8B31_11D5_8CB5_00D00908C1A5__INCLUDED_)
#define AFX_IGES_H__FDB42E42_8B31_11D5_8CB5_00D00908C1A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxwin.h> //CString

class igesArchive;
class sequenceNumberIges;

class igesStart
{
public:
	igesStart( char* pC, 
                  sequenceNumberIges &rsequenceNum);
  virtual ~igesStart();
	void Serialize( igesArchive &ar);
//private:
//	CString m_data;
	CString m_szAsciiText;
	char m_cSectionType;
  sequenceNumberIges &m_rSequenceNum ;
};

class CScribView ;
class igesArchive;
class igesFile;
class Iges  
{
  friend igesStart;
public:
//igesStart start;
	Iges(CScribView *pOuter);
	virtual ~Iges();
	HRESULT onFileSaveIges( char* dlgpathname);
  CScribView *m_pOuter;
private:
	HRESULT onArchive( char* dlgpathname);
	HRESULT onArchiveStart ( igesArchive &rIgesArchive, 
                              sequenceNumberIges &rsequenceNum);
	HRESULT onArchiveGlobal(  igesArchive &rIgesArchive, 
                            char* dlgpathname,
                            sequenceNumberIges &rsequenceNum);
	HRESULT onArchiveDirectory( igesArchive &rIgesArchive, 
                              sequenceNumberIges &rsequenceNum);
	HRESULT onArchiveParameter( igesArchive &rIgesArchive, 
                              sequenceNumberIges &rsequenceNum);
	HRESULT onArchiveTerminate( igesArchive &rIgesArchive, 
                              sequenceNumberIges &rsequenceNum);
  HRESULT onFileSave(char* dlgpathname);
  HRESULT buildVerticesAdvanced( 
                                 igesArchive&         ar, 
                              sequenceNumberIges &rsequenceNum);
  HRESULT TechDraw2Iges( 
                             igesArchive&       ar, 
                              sequenceNumberIges &rsequenceNum);

};


#endif // !defined(AFX_IGES_H__FDB42E42_8B31_11D5_8CB5_00D00908C1A5__INCLUDED_)
