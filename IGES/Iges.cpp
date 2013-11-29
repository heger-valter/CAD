// Iges.cpp: implementation of the Iges class.
//
//////////////////////////////////////////////////////////////////////

// ref:
//
// "Graphics File Formats, Reference and Guide", Brown, shepherd, Prentice Hall/Manning
// NBSIR 88-3813, U. S. Dept of Commerce, National Technical Information Service, Springfield, VA  22161, tel (703) 487-4650, fax (703 321-8547
// ANS US PRO/IPO-100-1996  Initial Graphics Exchange Specification IGES 5.3, US PRO US Product Data Assocation, Trident Research Center, Suite 204 5300 International Blvd., N. Charleston, SC   29418 (from SUNY-Albany & Air Force CALS Lab)
//  http://www.iges5x.org/archives/version5x/v5chap2.htm#2.1
//

//#include "stdafx.h"
//#include "scribble.h"
#include "scribvw.h"
#include "Iges.h"
#include "igesArchive.h"
#include "VertexIges.h"
#include "Manifold_solid_b_rep_objectIges.h"
#include "sequenceNumberIges.h"

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

/*
unsigned int nLinesStartSection   = 0;
unsigned int nLinesGlobalSection  = 0;
unsigned int nLinesDirectoryEntry = 0;
unsigned int nLinesParameterData  = 0;
*/
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// inner classes of iges

igesStart::igesStart(char *pC, 
                  sequenceNumberIges &rSequenceNumber)
: m_cSectionType('S')
, m_szAsciiText( pC)
, m_rSequenceNum ( rSequenceNumber )
{

}

igesStart::~igesStart()
{
}


// since this is a new project, I was thinking of changing the design from that used in STEP.  
// Once I am happy with the new design, I will use it in STEP as well

CString format( LPCTSTR pFormat
                , CString& m_szAsciiText
                , char m_cSectionType
                , int& sequenceNumber_m_iSequenceStartNum)
{
  CString szAsciiText;
  szAsciiText.Empty();
  char* pC = strchr( pFormat, '%');
  if ( NULL == pC ){
    return szAsciiText;
  }
  int iSize = atoi(1+pC);
  for (int i=0; i<m_szAsciiText.GetLength(); i+=iSize){
    CString lszAsciiText;
    lszAsciiText += m_szAsciiText.Mid( i, iSize);
    szAsciiText += lszAsciiText;
    int j = i - m_szAsciiText.GetLength() - iSize ;
    if ( j > 0){
      CString blank( ' ', j);
      szAsciiText += blank;
    }
    char* pC1 = strchr( pC+1, '%');
    if ( NULL == pC1 ){
      break;
    }
    szAsciiText += m_cSectionType;

    char* pC2 = strchr( pC1+1, '%');
    if ( NULL == pC2 ){
      break;
    }
    CString szNum;
    szNum.Format(_T(pC2), ++sequenceNumber_m_iSequenceStartNum);

    szAsciiText += szNum;
    szAsciiText += "\n";
  }
  return szAsciiText;
}

void igesStart::Serialize( igesArchive &ar)
{  
  CString cFormat("%");
  CString num;
  num.Format("%d", iSizeTextIges);
  cFormat += num;
  cFormat += "s%c%7d";
  CString szAsciiText = format( cFormat,//"%72s%c%7d", 
                                m_szAsciiText, 
                                m_cSectionType, 
                                m_rSequenceNum.m_iSequenceStartNum);
  ar << szAsciiText;
  return;
}

HRESULT Iges::onFileSave(char* dlgpathname)
{
  HRESULT hr = S_OK;

//hr = TechDraw2Iges( ar );

  return hr;
}

HRESULT Iges::TechDraw2Iges( 
                             igesArchive&       ar, sequenceNumberIges &sequenceNumber)
{
  // boulitin board mechanism as seen in Mantlya's GWB
  try {

      buildVerticesAdvanced( ar, 
                             sequenceNumber);    

  }
  catch ( ... ) {
    bool bTechDraw2Iges = false;
    ASSERT( bTechDraw2Iges);
    TRACE0("Iges::TechDraw2Iges error encountered\n");
    return E_FAIL;  
  }

  return S_OK;
}

// build the verticies
HRESULT Iges::buildVerticesAdvanced( igesArchive &         ar   ,
                                     sequenceNumberIges &rSequenceNumber)
{
//#if     NOTIFICATION 
//  m_pOuter->Notify("(10%) step::buildVerticesAdvanced");
//#endif//NOTIFICATION 

//#ifdef  SHOWPROGRESS
//  m_pOuter->progressBarUpdate( 10);
//#pragma message("\nShowing progress bar  MSG FROM(" __FILE__ ")\n"
//#endif//SHOWPROGRESS

//  CBaseIges::m_iSequenceParamNum = 0;

  CString paramAr;

  for ( int iv =0; iv < m_pOuter->m_vertexarray.GetSize();iv++ ) {
    CVertex* pVertex= (CVertex*)m_pOuter->m_vertexarray[iv];
      
    CVertexIges* pVertexIges = 
      new CVertexIges(   pVertex->px - m_pOuter->XRotationAxis, 
                       -(pVertex->py - m_pOuter->YRotationAxis), 
                         pVertex->pz - m_pOuter->ZRotationAxis
                         , rSequenceNumber
                     );
#ifndef  ENCAPSULATE
    pVertexIges->SerializeDir( ar);
    pVertexIges->SerializeParam( paramAr);
#else  //ENCAPSULATE
    pVertexIges->Serialize( ar);
#endif //ENCAPSULATE

    delete pVertexIges;
  }//iv

  ar << paramAr;
  return S_OK;
}


Iges::Iges(CScribView *pOuter)
{
  m_pOuter = pOuter;
}

Iges::~Iges()
{
  m_pOuter = NULL;
}

HRESULT Iges::onFileSaveIges(char* dlgpathname)
{
  HRESULT hr = S_OK;

  hr = onArchive  ( dlgpathname);
  return hr;
}

HRESULT Iges::onArchive( char* dlgpathname)
{
  HRESULT hr = S_OK;

  sequenceNumberIges sequenceNumber;
  igesArchive aIgesArchive( dlgpathname);
	
  onArchiveStart    ( aIgesArchive, sequenceNumber);

	onArchiveGlobal   ( aIgesArchive, dlgpathname
      , sequenceNumber
    );
//onArchiveDirectory( aIgesArchive);
	onArchiveParameter( aIgesArchive, sequenceNumber);
	onArchiveTerminate( aIgesArchive, sequenceNumber);

  aIgesArchive.close();

  return hr;
}

HRESULT Iges::onArchiveStart ( igesArchive &rIgesArchive
                                , sequenceNumberIges &rsequenceNumber
                              )
{ 
  HRESULT hr = S_OK;
  char buf1[81] = 
"                                                                        S      1";
  char* buf2 = 
"                                                                        **  IGES FILE generated by Technadraw System **                                                                                                 ";
  char buf3[81] = 
"                                                                        S      3";
  igesStart is( buf2, 
    rsequenceNumber);
  is.Serialize( rIgesArchive);
  return hr;
}

  char gParameterDelimiterCharacter  = ',';
  char recordDelimiterCharacter     = ';';

HRESULT Iges::onArchiveGlobal ( igesArchive &rIgesArchive, char* dlgpathname
                                , sequenceNumberIges &rsequenceNumber
                               )
{
  HRESULT hr = S_OK;
  CString input;
  // 26 parameters

  input += "1H" ;
  input +=  gParameterDelimiterCharacter      ;
  input +=  gParameterDelimiterCharacter ;
  input += "1H" ;
  input +=  recordDelimiterCharacter          ;
  input +=  gParameterDelimiterCharacter ;
  input += "4H" ;
  input +=  "IGES"                            ;
  input +=  gParameterDelimiterCharacter ;
  int iLen = strlen(dlgpathname);

  CString len;
  len.Format("%d", iLen);
  input += len ;
  input += "H" ;
  input += dlgpathname               ;
  input += gParameterDelimiterCharacter ;
  
  char* systemId                      = "Technadraw 1.0.0.46";
  iLen = strlen( systemId);
  len.Format("%d", iLen);
  input += len ;
  input += "H" ;
  input +=  systemId;
  char* igesPreprocessorVersion       = "IGES 5.2";
  iLen = strlen(igesPreprocessorVersion);
  len.Format("%d", iLen);
  input += len ;
  input += "H" ;
  input +=  igesPreprocessorVersion;
  CString num;

  char buf4[81] = 
//"1H,,1H;,4HIGES,20Hinstrux jul 11 c.igs,10HTechnadraw,8HIGES 5.2,32,38,  G      2";
 "10HTechnadraw,8HIGES 5.2,32,38,                                         G      2";
//++rsequenceNumber.m_iSequenceGlobalNum;
//rIgesArchive << buf4 << endl;

  char buf5[81] = 
  "9,308,15,10HTechnadraw,1.0,2,2HMM,1,0.0,13H1010716.131844,0.001,        G      3";
//++rsequenceNumber.m_iSequenceGlobalNum;
//rIgesArchive << buf5 << endl;
  
  char buf6[81] = 
  "10.640000,4HWHRV,11HAgito      ,10,0,13H1010716.131844,;                G      4";
  
//rIgesArchive << buf6 ;
//rIgesArchive << endl;

  CString output;
  output = format( "%72s%c%7d", input, 'G', rsequenceNumber.m_iSequenceGlobalNum);
  rIgesArchive << output;  
  return hr;
}

HRESULT Iges::onArchiveParameter ( igesArchive &rIgesArchive, sequenceNumberIges &rSequenceNum)
{
  HRESULT hr = S_OK;
  hr = TechDraw2Iges( rIgesArchive, rSequenceNum);
  return hr;
}

HRESULT Iges::onArchiveTerminate( igesArchive &rIgesArchive, 
                                  sequenceNumberIges &rSequenceNum)
{
  HRESULT hr = S_OK;
    char buf0[81] = 
"S      3G      3D  16670P  28413                                        T      1";
//rIgesArchive << setw(7);
  rIgesArchive 
    << "S" << setw(7) << rSequenceNum.m_iSequenceStartNum 
    << "G" << setw(7) << rSequenceNum.m_iSequenceGlobalNum
    << "D" << setw(7) << rSequenceNum.m_iSequenceDirectoryNum 
    << "P" << setw(7) << rSequenceNum.m_iSequenceParameterNum;
  rIgesArchive << "                                        ";// 33, 71
  rIgesArchive 
    << "T" << setw(7) << ++rSequenceNum.m_iSequenceTerminateNum << endl;
  return hr;
}


//////////////////////////////////////////////////////////
// who  date      history
//-----------------------
// wh   09/18/01  rearrange functionality to move functionality of 
//                directoryEntry & parametryEntry into its own classes.

