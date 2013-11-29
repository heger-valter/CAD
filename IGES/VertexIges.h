// VertexIges.h: interface for the CVertexIges class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VERTEXIGES_H__A352CAE3_8F52_11D5_8CB5_00D00908C1A5__INCLUDED_)
#define AFX_VERTEXIGES_H__A352CAE3_8F52_11D5_8CB5_00D00908C1A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CString;
class sequenceNumberIges;

#include "BaseIges.h"

class CVertexIges : public CBaseIges  
{
  float pos[3]; 
public:
	CVertexIges( float x, float y, float z
               , sequenceNumberIges &rsequenceNum 
               );
	virtual ~CVertexIges();
  void Serialize( igesArchive &ar);
  void SerializeDir( igesArchive &ar);
  void SerializeParam( CString& paramAr);
};

class CObArray;
class CVertexListIges : public CBaseIges  
{
  CObArray pos; 
public:
	void Add( CVertexIges& p);
	CVertexListIges( CVertexIges& p
               , sequenceNumberIges &rsequenceNum 
               );
	virtual ~CVertexListIges();
  void Serialize( igesArchive &ar);
  void SerializeParam( CString& paramAr);
//CBaseIges* m_pParentEdge;
  // hack for now until you think of a better idea!
//sequenceNumberIges *m_pSequenceNum;
};

#endif // !defined(AFX_VERTEXIGES_H__A352CAE3_8F52_11D5_8CB5_00D00908C1A5__INCLUDED_)
