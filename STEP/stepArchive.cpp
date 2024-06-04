#include "stepArchive.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#ifdef _WINDOWS
#include "stdafx.h"
#endif

#include "BaseStep.h"

extern const int iOUT_OF_BOUNDS;

iraroArchive::iraroArchive()
: CString()
, m_bIsStoring( false)
{ 
}

iraroArchive::~iraroArchive()
{
}


iraroArchive& iraroArchive::operator<<(const char *pC)
{
  CString* pString = dynamic_cast<CString*>(this);
  if ( NULL != pC ){
    *pString += (pC);
  }
  return *this;
}

iraroArchive& iraroArchive::operator<<(const double d)
{
  CString* pString = dynamic_cast<CString*>(this);
//ASSERT(!_isnan(d));
  if (_isnan(d)) {
    *pString += "$";
  }
  else {
    char buf[64];
    sprintf(buf, "%g", d);
    //problem with e-0  in expresso        //wh
    for (int i = 0; i< strlen(buf); i++){
      buf[i] = toupper(buf[i]);
    }

//  *pString += ( " ");// wh 3/08/02
    *pString += ( buf);
  }
  return *this;
}

iraroArchive& iraroArchive::operator<<(const float  d)
{
  CString* pString = dynamic_cast<CString*>(this);
//ASSERT(!_isnan(d));
  if (_isnan(d)) {
    *pString += "$";
  }
  else {
    char buf[64];
    sprintf(buf, "%f", d);
    //problem with e-0  in expresso        //wh
    for (int i = 0; i< strlen(buf); i++){
      buf[i] = toupper(buf[i]);
    }
//  *pString += ( " ");// wh 3/08/02
    *pString += ( buf);
  }
  return *this;
}

iraroArchive& iraroArchive::operator<<(const int i)
{
  CString* pString = dynamic_cast<CString*>(this);
  if (iOUT_OF_BOUNDS == i) {
    *pString += ( "$");
    return *this;
  }
  char buf[16];
  itoa(i, buf, 10);
  *pString += ( buf);
  return *this;
}

iraroArchive& iraroArchive::operator<<(const bool b)
{
  CString* pString = dynamic_cast<CString*>(this);
  if (b){
    *pString += ( ".T.");
  }
  else{
    *pString += ( ".F.");
  }
  return *this;
}

iraroArchive& iraroArchive::operator<<(const stepBool b)
{
  CString* pString = dynamic_cast<CString*>(this);
  if (stepFalse != b){
    *pString += ( ".T.");
  }
  else{
    *pString += ( ".F.");
  }
  return *this;
}

// this class writes out a file according to ISO-10303-21 spec
stepArchive::stepArchive()
:  
  m_iEntry(0)
{ 
  
  m_archives.SetSize(1);
  m_archives.SetAt(0, new iraroArchive);
}

stepArchive::~stepArchive()
{
  for (int i = 0; i< this->m_archives.GetSize(); i++){
    delete (this->m_archives.GetAt(i));
  }
  m_archives.SetSize(0);
}

/*
schemaArchive ::schemaArchive (): iraroArchive()
{ 
}

schemaArchive ::~schemaArchive ()
{
}
*/
//////////////////////////////////////////////////////////
// who  date      history
// wh   03/05/01  added support for schemaArchive 


int stepArchive::GetLength()
{ 
  iraroArchive* pString = GetAt(m_iEntry);
  return pString->GetLength();
}

int stepArchive::getEntry()
{
  int is = m_archives.GetSize();
  if (m_iEntry >= is){
    m_archives.SetSize( m_iEntry + 128 );
    for (int j = is; j< m_archives.GetSize(); j++){
      m_archives.SetAt(j, new iraroArchive);
    }
  }
  return m_iEntry;
}

iraroArchive& stepArchive::operator<<(const char *pC)
{
  iraroArchive* pString = (GetAt( this->getEntry() ) );
  iraroArchive& rString = (iraroArchive&) (*(pString));
  if ( NULL != pC ){
    *pString << (pC);
  }
  return rString;
}

iraroArchive& stepArchive::operator<<(const double pC)
{
  iraroArchive* pString = (GetAt( this->getEntry() ) );
  iraroArchive& rString = (iraroArchive&) (*(pString));
//if ( NULL != pC ){
    *pString << (pC);
//}
  return rString;
}

iraroArchive& stepArchive::operator<<(const int pC)
{
  iraroArchive* pString = (GetAt( this->getEntry() ) );
  iraroArchive& rString = (iraroArchive&) (*(pString));
//if ( NULL != pC ){
    *pString << (pC);
//}
  return rString;
}

iraroArchive& stepArchive::operator<<(const float pC)
{
  iraroArchive* pString = (GetAt( this->getEntry() ) );
  iraroArchive& rString = (iraroArchive&) (*(pString));
//if ( NULL != pC ){
    *pString << (pC);
//}
  return rString;
}

iraroArchive& stepArchive::operator<<(const bool pC)
{
  iraroArchive* pString = (GetAt( this->getEntry() ) );
  iraroArchive& rString = (iraroArchive&) (*(pString));
//if ( NULL != pC ){
    *pString << (pC);
//}
  return rString;
}

template <class T> 
iraroArchive& stepArchive::operator<<( class T)
{
  iraroArchive* pString = (GetAt( getEntry() ) );
  iraroArchive& rString = (iraroArchive&) (*(pString));
  if ( NULL != T ){
    *pString << (T);
  }
  return rString;
}

//stepArchive::operator<< <double> charStepArchive;

HRESULT stepArchive::setEntry( int iEntry)
{
  this->m_iEntry = iEntry;
  return S_OK;
}

HRESULT stepArchive::write(FILE *stream)
{
  for (int i =0; i < this->m_archives.GetSize(); i++){
    iraroArchive* pIAr = GetAt(i);
    {// added to trace memory leak complained about by bounds checker!
      CString* pString = dynamic_cast<CString*>(pIAr);

      if (NULL != pString){
        try{
          int iLen = pString->GetLength();
          if (0 < iLen){
            LPTSTR pC = pString->GetBuffer( iLen+1);// wh 02/03/02
            int numwrite=fputs( pC, stream); 
            pString->ReleaseBuffer( );// wh 02/08/02
          }
        } 
        catch(CMemoryException e){
          TRACE0("CMemoryException stepArchive::write\n");
#ifdef  EXPOSE      
          fprintf( g_errorLog, "CMemoryException \n" );
#endif//EXPOSE   
        }
      }
    }
  }// next i
  return S_OK;
}

iraroArchive* stepArchive::GetAt(int i)
{  
//ASSERT( i < m_iEntry);
  return (iraroArchive*) (m_archives.GetAt(i));
}
