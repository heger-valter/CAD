#if !defined(AFX_REFOBJ_H__D6AD4799_4FD5_4BF3_B9E4_8E0678F39AC7__INCLUDED_)
#define AFX_REFOBJ_H__D6AD4799_4FD5_4BF3_B9E4_8E0678F39AC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RefObj.h : header file
//

#include "afx.h"

/////////////////////////////////////////////////////////////////////////////
// CRefObj window

class CRefObj : public CObject
{
	  ULONG m_iRef;// a count of how many objects have a reference to me// make me private
  public:
	  virtual ULONG release();// release the reference to me
	  virtual ULONG addRef(); // add a reference to me
    ULONG getRefCnt();
	  virtual void fin( void);// finish up
// Construction
public:
	CRefObj();

// Attributes
public:

// Operations
public:


// Implementation
public:
	virtual ~CRefObj();

};

/////////////////////////////////////////////////////////////////////////////


#endif // !defined(AFX_REFOBJ_H__D6AD4799_4FD5_4BF3_B9E4_8E0678F39AC7__INCLUDED_)
