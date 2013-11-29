// BaseIges.cpp: implementation of the BaseIges class.
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
//#include "scribble.h"
#include "afx.h"
#include "BaseIges.h"
#include "Manifold_solid_b_rep_objectIges.h"
#include "sequenceNumberIges.h"
#include "parameterDataIges.h"
#include "directoryEntryIges.h"
//#include "PointerIges.h"
#include "IntegerIges.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
 
const          int iFirstCountBase    = 1;
const unsigned int iSizeParamTextIges = 64;
const unsigned int iSizeTextIges      = 72;
const unsigned int iSizeOutlineIges   = 81;// including endl

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#if 0
CBaseIges::CBaseIges( )
: m_bSerialized(false)
, m_pParentEdge( NULL)
{
//  m_iSequenceParamNum = 0;
}
#endif 

CBaseIges::CBaseIges( void *pSeqNum)
//: parameterDataIges(0)
: m_bSerialized(false)
, m_pParent( NULL)
, m_pSequenceNum( (sequenceNumberIges *)pSeqNum)
, m_directoryEntry(*this)
{
  initDir();
  initParam();
}

CBaseIges::~CBaseIges()
{

}

void CBaseIges::setSeq(sequenceNumberIges *pSeqNum)
{
  m_pSequenceNum = pSeqNum;
}


bool CBaseIges::setSerialized()
{
  if ( !isSerialized() ) {
    m_bSerialized = true;
    return true;
  }
  return false;
}

void CBaseIges::initDir()
{
  /*
  CIntegerIges* pDE01 = new CIntegerIges( m_iEntityTypeNum );
  m_directoryEntry.AddTail( pDE01);

  CIntegerIges* pDE02 = new CIntegerIges( m_pSequenceNum->m_iSequenceParameterNum+1 );
  m_directoryEntry.AddTail( pDE02);

  __int32 pStructure = 0;//m_pParentEdge->m_iSequenceParamNum;// parent edge
  CIntegerIges* pDE03  = new CIntegerIges( pStructure );
  m_directoryEntry.AddTail( pDE03 );

  __int32 LineFontPattern = 0;
  CIntegerIges* pDE04  = new CIntegerIges( LineFontPattern );
  m_directoryEntry.AddTail( pDE04 );

  __int32 Level = 0;
  CIntegerIges* pDE05  = new CIntegerIges(  );
  m_directoryEntry.AddTail( pDE05 );

  CIntegerIges* pDE06  = new CIntegerIges(  );
  m_directoryEntry.AddTail( pDE06 );

  CIntegerIges* pDE07  = new CIntegerIges(  );
  m_directoryEntry.AddTail( pDE07 );

  CIntegerIges* pDE08  = new CIntegerIges(  );
  m_directoryEntry.AddTail( pDE08 );

  CIntegerIges* pDE09  = new CIntegerIges(  );
  m_directoryEntry.AddTail( pDE09 );

  CIntegerIges* pDE10  = new CIntegerIges(  );
  m_directoryEntry.AddTail( pDE10 );

  CIntegerIges* pDE11  = new CIntegerIges(  );
  m_directoryEntry.AddTail( pDE11 );

  CIntegerIges* pDE12  = new CIntegerIges(  );
  m_directoryEntry.AddTail( pDE12 );

  CIntegerIges* pDE13  = new CIntegerIges(  );
  m_directoryEntry.AddTail( pDE13 );

  CIntegerIges* pDE14  = new CIntegerIges(  );
  m_directoryEntry.AddTail( pDE14 );

  CIntegerIges* pDE15  = new CIntegerIges(  );
  m_directoryEntry.AddTail( pDE15 );

  CIntegerIges* pDE16  = new CIntegerIges(  );
  m_directoryEntry.AddTail( pDE16 );

  CIntegerIges* pDE17  = new CIntegerIges(  );
  m_directoryEntry.AddTail( pDE17 );

  CIntegerIges* pDE18  = new CIntegerIges(  );
  m_directoryEntry.AddTail( pDE18 );

  CIntegerIges* pDE19  = new CIntegerIges(  );
  m_directoryEntry.AddTail( pDE19 );

  CIntegerIges* pDE20  = new CIntegerIges(  );
  m_directoryEntry.AddTail( pDE20 );


  __int32 pView = 0;
  __int32 pTransformationMatrix = 0;
  __int32 pLabelDisplayAssociativity = 0;

  __int8 statusNumberBlank                    = 00;
  statusNumberSubordinateEnititySwitchStatus statusNumberSubordinateEnititySwitch = independent;
  if (NULL != pStructure){  
    statusNumberSubordinateEnititySwitch = physicallyDependent;
  }
  __int8 statusNumberEntityUse                = 00;
  __int8 statusNumberHierarchy                = 00;

  __int32 lineWeightNumber = 0;
  __int32 colorNumber = 0;
//__int32 parameterLineCount = 1;
  __int32 formNumber = 0;
  __int32 reserved = 0;
  __int32 entityLabel     = 0;
  __int32 entitySubscriptNumber = 0;
*/
}

void CBaseIges::initParam()
{
  CIntegerIges* pDE = 
    new CIntegerIges( m_pSequenceNum->m_iSequenceDirectoryNum);
  this->m_parameterData.AddTail(pDE);
}
