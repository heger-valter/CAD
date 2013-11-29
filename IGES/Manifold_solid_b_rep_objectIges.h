// Manifold_solid_b_rep_objectIges.h: interface for the Manifold_solid_b_rep_objectIges class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MANIFOLD_SOLID_B_REP_OBJECTIGES_H__A352CAE4_8F52_11D5_8CB5_00D00908C1A5__INCLUDED_)
#define AFX_MANIFOLD_SOLID_B_REP_OBJECTIGES_H__A352CAE4_8F52_11D5_8CB5_00D00908C1A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CString;
#include "BaseIges.h"
class sequenceNumberIges;

class CManifold_solid_b_rep_objectIges : public CBaseIges  
{
public:
	void Serialize( igesArchive &ar);
	CManifold_solid_b_rep_objectIges( sequenceNumberIges& rSequenceNum);
	virtual ~CManifold_solid_b_rep_objectIges();
  sequenceNumberIges& m_SequenceNum;
  void SerializeParam( CString& paramAr);
};

#endif // !defined(AFX_MANIFOLD_SOLID_B_REP_OBJECTIGES_H__A352CAE4_8F52_11D5_8CB5_00D00908C1A5__INCLUDED_)
