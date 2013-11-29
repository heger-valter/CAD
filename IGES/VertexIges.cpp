// VertexIges.cpp: implementation of the CVertexIges class.
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
//#include "scribble.h"
#include "VertexIges.h"
#include "igesArchive.h"
#include "Manifold_solid_b_rep_objectIges.h"
#include "sequenceNumberIges.h"
#include "Iges.h"
#include "directoryEntryIges.h"
#include "parameterDataIges.h"

#include "ostream.h"// endl
#include <afx.h>// CString
#include <iostream.h>
#include <iomanip.h>
#include <fstream.h>	// For file I/O
#include <stdlib.h>		// For exit()
#include <string.h>  //strcspn
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVertexIges::CVertexIges( float x, 
                          float y, 
                          float z
                          , sequenceNumberIges &rsequenceNum
                        )
                        : CBaseIges( &rsequenceNum)
//: m_pSequenceNum( &rsequenceNum)
//, m_pParentEdge( NULL)
{
  m_iEntityTypeNum = 502;
  pos[0] = x; 
  pos[1] = y; 
  pos[2] = z; 
  m_iParameterLineCount=1;
//m_directryEntry.SetAt(0, m_iEntityTypeNum );
}

CVertexIges::~CVertexIges()
{
}

void CVertexIges::Serialize( igesArchive &rIgesArchive)
{ 
#ifdef  ENCAPSULATE
  m_directoryEntry.Serialize( rIgesArchive);
  m_parameterData.Serialize( rIgesArchive);
#endif//ENCAPSULATE
}

void CVertexIges::SerializeDir( igesArchive &rIgesArchive)
{ 
  __int32 entityTypeNumber = m_iEntityTypeNum;
  __int32 pParameterData = m_pSequenceNum->m_iSequenceParameterNum+1;
  __int32 pStructure = 0;//m_pParentEdge->m_iSequenceParamNum;// parent edge
  __int32 LineFontPattern = 0;
  __int32 Level = 0;
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

  rIgesArchive << setw(8);
  rIgesArchive << entityTypeNumber;

  rIgesArchive << setw(8) << pParameterData ;
  rIgesArchive << setw(8) << pStructure;
  rIgesArchive << setw(8) << LineFontPattern ;
  rIgesArchive << setw(8) << Level ;
  rIgesArchive << setw(8) << pView ;
  rIgesArchive << setw(8) << pTransformationMatrix ;
  rIgesArchive << setw(8) << pLabelDisplayAssociativity ;
  CString statusNumber;
  statusNumber.Format( "%02d%02d%02d%02d", 
    statusNumberBlank , 
    statusNumberSubordinateEnititySwitch , 
    statusNumberEntityUse , 
    statusNumberHierarchy );
  rIgesArchive << statusNumber ;
  rIgesArchive << "D" << setw(7) << ++m_pSequenceNum->m_iSequenceDirectoryNum << endl;

  rIgesArchive << setw(8) << entityTypeNumber;
  rIgesArchive << setw(8) << lineWeightNumber ;
  rIgesArchive << setw(8) << colorNumber;
  rIgesArchive << setw(8) << m_iParameterLineCount;
  rIgesArchive << setw(8) << formNumber;
  rIgesArchive << setw(8) << reserved;
  rIgesArchive << setw(8) << reserved;
  rIgesArchive << setw(8) << entityLabel ;
  rIgesArchive << setw(8) << entitySubscriptNumber;
  rIgesArchive << "D" << setw(7) << ++m_pSequenceNum->m_iSequenceDirectoryNum << endl;
}

void CVertexIges::SerializeParam( CString &rparamAr)
{ 
  try{
    if (!isSerialized()){
      setSerialized();
      int iLen0 = rparamAr.GetLength();
      m_iSequenceParamNum = ++m_pSequenceNum->m_iSequenceParameterNum;
      CString aFloat;
//    writePre(rparamAr);
      aFloat.Format("%d", m_iEntityTypeNum);
      rparamAr +=  aFloat;// x1, 
      rparamAr                 += gParameterDelimiterCharacter;
      int iNumEntities= 1;// 
      aFloat.Format("%d", iNumEntities);
      rparamAr +=  aFloat;// x1, 
      rparamAr                 += gParameterDelimiterCharacter;
//    rparamAr << setprecision(6) ;
      aFloat.Format("%f", pos[0]);
      rparamAr +=  aFloat;// x1, 
      rparamAr += gParameterDelimiterCharacter;
      aFloat.Format("%f", pos[1]);
      rparamAr +=  aFloat;// x1, 
      rparamAr += gParameterDelimiterCharacter;
      aFloat.Format("%f", pos[2]);
      rparamAr +=  aFloat;// x1, 
      rparamAr += recordDelimiterCharacter;
      int iLen1 = rparamAr.GetLength();
      CString blank( ' ', iSizeTextIges-iLen1+iLen0-8);
      rparamAr += blank;
      rparamAr += " ";// col 65 unused
      aFloat.Format("%7d", m_pSequenceNum->m_iSequenceDirectoryNum-1);//66-72
      rparamAr +=  aFloat;// x1, 
      rparamAr += "P";// seq no
      aFloat.Format("%7d", m_pSequenceNum->m_iSequenceParameterNum);//?
      rparamAr +=  aFloat;// x1, 
      rparamAr += "\n";// seq no
//    writePost(rparamAr);
      m_iParameterLineCount = 1;
    }
  }
  catch(...){
      setSerialized();
      rparamAr += "\nError caught in CVertexIges::Serialize!\n";
  }
}

CVertexListIges::CVertexListIges( CVertexIges& p
                                 , sequenceNumberIges &rsequenceNum
                                )
:  CBaseIges( &rsequenceNum)
//: m_pSequenceNum( &rsequenceNum)
//, m_pParentEdge( NULL)
//, CArray()
{
  m_iEntityTypeNum = 502;
  pos.Add( &p); 
  m_iParameterLineCount=1;
}

CVertexListIges::~CVertexListIges()
{

}

void CVertexListIges::Serialize( igesArchive &rIgesArchive)
{ 
  __int32 entityTypeNumber = m_iEntityTypeNum;
  __int32 pParameterData = m_pSequenceNum->m_iSequenceParameterNum+1;
  __int32 pStructure = 0;//m_pParentEdge->m_iSequenceParamNum;// parent edge
  __int32 LineFontPattern = 0;
  __int32 Level = 0;
  __int32 pView = 0;
  __int32 pTransformationMatrix = 0;
  __int32 pLabelDisplayAssociativity = 0;

  __int8 statusNumberBlank                    = 00;
  __int8 statusNumberSubordinateEnititySwitch = 01;
  __int8 statusNumberEntityUse                = 00;
  __int8 statusNumberHierarchy                = 00;

  __int32 lineWeightNumber = 0;
  __int32 colorNumber = 0;
//__int32 parameterLineCount = 1;
  __int32 formNumber = 0;
  __int32 reserved = 0;
  __int32 entityLabel     = 0;
  __int32 entitySubscriptNumber = 0;

  rIgesArchive << setw(8);
  rIgesArchive << entityTypeNumber;

  rIgesArchive << setw(8) << pParameterData ;
  rIgesArchive << setw(8) << pStructure;
  rIgesArchive << setw(8) << LineFontPattern ;
  rIgesArchive << setw(8) << Level ;
  rIgesArchive << setw(8) << pView ;
  rIgesArchive << setw(8) << pTransformationMatrix ;
  rIgesArchive << setw(8) << pLabelDisplayAssociativity ;
  CString statusNumber;
  statusNumber.Format( "%02d%02d%02d%02d", 
    statusNumberBlank , 
    statusNumberSubordinateEnititySwitch , 
    statusNumberEntityUse , 
    statusNumberHierarchy );
  rIgesArchive << statusNumber ;
  rIgesArchive << "D" << setw(7) << ++m_pSequenceNum->m_iSequenceDirectoryNum << endl;

  rIgesArchive << setw(8) << entityTypeNumber;
  rIgesArchive << setw(8) << lineWeightNumber ;
  rIgesArchive << setw(8) << colorNumber;
  rIgesArchive << setw(8) << m_iParameterLineCount;
  rIgesArchive << setw(8) << formNumber;
  rIgesArchive << setw(8) << reserved;
  rIgesArchive << setw(8) << reserved;
  rIgesArchive << setw(8) << entityLabel ;
  rIgesArchive << setw(8) << entitySubscriptNumber;
  rIgesArchive << "D" << setw(7) << ++m_pSequenceNum->m_iSequenceDirectoryNum << endl;
}


void CVertexListIges::Add(CVertexIges& rp)
{
  pos.Add( &rp);
}
