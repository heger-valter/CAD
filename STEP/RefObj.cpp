// RefObj.cpp : implementation file
//

#include "afx.h"
#include "stdafx.h"
#include "scribble.h"
#include "RefObj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRefObj

// this class handles the reference counting for an object
CRefObj::CRefObj()
: m_iRef(1L)
{
}

CRefObj::~CRefObj()
{
}

ULONG CRefObj::addRef()
{
  ASSERT( m_iRef > 0);
  m_iRef++;

#ifdef  EXPOSE      
  TRACE3("\tC%sStep::addRef(), (#%d ), m_iRef=%u\n", m_szTheClass.GetBuffer(m_szTheClass.GetLength()), getNum(), m_iRef);
  m_szTheClass.ReleaseBuffer();

  fprintf( g_errorLog, "\tC%sStep::addRef(), (#%d ), m_iRef=%u\n", m_szTheClass.GetBuffer(m_szTheClass.GetLength()), getNum(), m_iRef);
  m_szTheClass.ReleaseBuffer();
#endif//EXPOSE   

  return m_iRef;
}

ULONG CRefObj::release()
{ 
  ASSERT_VALID( this );
  ASSERT( 0 != m_iRef);
  m_iRef--;
#ifdef  EXPOSE      
  TRACE3("\tC%sStep::release(), (#%d ), m_iRef=%u\n", m_szTheClass.GetBuffer(m_szTheClass.GetLength()), getNum(), m_iRef);
  m_szTheClass.ReleaseBuffer();

  fprintf( g_errorLog, "\tC%sStep::release(), (#%d ), m_iRef=%u\n", m_szTheClass.GetBuffer(m_szTheClass.GetLength()), getNum(), m_iRef);
  m_szTheClass.ReleaseBuffer();
#endif//EXPOSE   

#ifdef GARBAGE_COLLECTION
  if (0 == m_iRef){ 
    delete this;
    return 0;
  }
  else if (0xFFFFFFFF == m_iRef){
    return 0xFFFFFFFF;// since this->m_iRef has been returned to the heap
  }
#endif //GARBAGE_COLLECTION

  return m_iRef;
}

ULONG CRefObj::getRefCnt()
{    
  return m_iRef;  
}


/////////////////////////////////////////////////////////////////////////////
