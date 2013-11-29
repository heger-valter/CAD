// IntegerIges.h: interface for the CIntegerIges class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INTEGERIGES_H__2D853F43_941C_11D5_8CB5_00D00908C1A5__INCLUDED_)
#define AFX_INTEGERIGES_H__2D853F43_941C_11D5_8CB5_00D00908C1A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class igesArchive;
// These classes are needed to store a collection of CObject in CObList 
// I really was thinking of using stl collection, but with C# on the horizon, decided not
// Besides, I was driven crazy with stl and std namespace problems from <string> when I tried that!

class CDataIges : public CObject  
{
public:
	CDataIges (int i);
	virtual ~CDataIges ();
  virtual void Serialize( igesArchive &rIgesArchive);
//protected:
//  friend igesArchive;
	__int32 m_i;
};

class CIntegerIges : public CDataIges
{
public:
	CIntegerIges(int i);
	virtual ~CIntegerIges();

//protected:
//  friend igesArchive;
	__int32 m_i;
};

class CFloatIges : public CObject  
{
public:
	CFloatIges( float f);
	virtual ~CFloatIges();

//protected:
//  friend igesArchive;
	float m_f;
};

class CStringIges : public CObject  
{
public:
	CStringIges ( float f);
	virtual ~CStringIges ();

//protected:
//  friend igesArchive;
	CString m_szString;
};

#endif // !defined(AFX_INTEGERIGES_H__2D853F43_941C_11D5_8CB5_00D00908C1A5__INCLUDED_)
