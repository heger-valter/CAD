// BaseIges.h: interface for the BaseIges class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASEIGES_H__A352CAE2_8F52_11D5_8CB5_00D00908C1A5__INCLUDED_)
#define AFX_BASEIGES_H__A352CAE2_8F52_11D5_8CB5_00D00908C1A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define USE_PARENT 1  // are we using parent pointers

#include <afx.h>// MFC headers

extern const          int iFirstCountBase    ;
extern const unsigned int iSizeParamTextIges ;
extern const unsigned int iSizeTextIges      ;
extern const unsigned int iSizeOutlineIges   ;// including endl
                
extern char gParameterDelimiterCharacter;
extern char recordDelimiterCharacter;

#include "directoryEntryIges.h"
#include "parameterDataIges.h"
class sequenceNumberIges;  
class igesArchive;// forward declare the class
class CBaseIges;
class CBaseIges  : public CObject 
{
  __int32 m_iParameterLineCount;
  bool m_bSerialized;
protected:
//	CBaseIges( );
public:
#if 0
	CBaseIges( );
#endif 

#ifdef USE_PARENT
  CBaseIges(  void *pSeqNum);
#endif

  virtual ~CBaseIges();
  virtual void Serialize( igesArchive &ar)=0;// write out the manifestation of this class
  bool isSerialized(){// is this method already serialized
    return m_bSerialized;
  };
  bool setSerialized( );// set this class as already serialized, thus not to be written out twice in the file
	bool writePost( igesArchive &ar);// post-processing 
	bool writePre(  igesArchive &ar);// pre-processing
protected:
  friend class CVertexIges;
  friend class CVertexListIges;
  friend class CEdgeIges;
  friend class CLoopIges;
  friend class CShellIges;
  friend class CManifold_solid_b_rep_objectIges;
  friend directoryEntryIges;
  friend parameterDataIges;
  int m_iEntityTypeNum;
  int m_iSequenceParamNum;
//CString Format( LPCTSTR pFormat, CString &r_szAsciiText);// used to flow text into format
  CString m_params[26];
  CString m_directory ;
  char m_cSectionType;
public:
	void initParam();
	virtual void initDir();
  CBaseIges* m_pParent;
  // hack for now until you think of a better idea!
  sequenceNumberIges *m_pSequenceNum;
	void setSeq( sequenceNumberIges *pSeqNum);
  directoryEntryIges m_directoryEntry;
  parameterDataIges m_parameterData;
};

enum statusNumberBlankStatus{
  visible=0,
  blanked=1
};

enum statusNumberSubordinateEnititySwitchStatus{
  independent=0,
  physicallyDependent=1,
  logicallyDependent=2,
  bothDependent=3
};

enum statusNumberEntityUseStatus{
  geometry=0,
  annotation=1,
  definition=2,
  other=3,
  logical_positional=4,
  _2dParametric=5,
  constuctiveGeometry=6
};

enum statusNumberHierarchyStatus{
  globalTopDown=0,
  globalDefer=1,
  useHierarchyProperty
};

class  statusNumberEncoded{
  statusNumberSubordinateEnititySwitchStatus m_statusNumberSubordinateEnititySwitchStatus;
  statusNumberEncoded();
  virtual ~statusNumberEncoded();
  void format(LPCTSTR pFormat);
};

#endif // !defined(AFX_BASEIGES_H__A352CAE2_8F52_11D5_8CB5_00D00908C1A5__INCLUDED_)
