// parameterDataIges.cpp: implementation of the parameterDataIges class.
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
#include <afx.h>// CString
#include "parameterDataIges.h"
#include "IntegerIges.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

parameterDataIges::parameterDataIges(int n)
: CObList(3)
{
/*  
  m_data.SetSize(3+2*n);
//  m_data.SetAt(3, (void*)n);
  CString* pO1 = new CString(',');
  m_data.AddTail( (CObject*)pO1);
  CString* pO2 = new CString(';');
  m_data.AddTail( (CObject*)pO2);
  CIntegerIges* pO3 = new CIntegerIges(n);
  m_data.AddTail( (CObject*)pO3);
  */
}

parameterDataIges::~parameterDataIges()
{
  /*
  CObject* pO = m_data.GetHead();
  CIntegerIges* pI= dynamic_cast< CIntegerIges*>( pO );
  if (NULL != pI){
    delete pI;
  }
  else {
    CString* pS= dynamic_cast< CString*>( pO );
    delete pS;
  }
  */
}

#ifdef  ENCAPSULATE
void parameterDataIges::Serialize( igesArchive &rIgesArchive )
{

}
#endif//ENCAPSULATE
