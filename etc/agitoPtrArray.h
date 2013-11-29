// agitoPtrArray.h: interface for the agitoPtrArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AGITOPTRARRAY_H__6C17A082_7532_11D5_8CB2_00D00908C1A5__INCLUDED_)
#define AFX_AGITOPTRARRAY_H__6C17A082_7532_11D5_8CB2_00D00908C1A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPtrArray;
class CObArray;
class CSurfaceStep;

//CTypedPtrArray<CObArray, CBaseStep*> stepArray;
// manage your hash better
class agitoPtrArray : public CPtrArray //CObArray//
{
public:
	agitoPtrArray();
	virtual ~agitoPtrArray();
	void RemoveAt(int nIndex, int nCount=1);
	int Add( void* newElement);
  bool m_bSearch;// search for a null entry before adding 
	HRESULT SearchFromTheTop( void);// start searching for a null entry in hash table from the top
private:
	int m_iLast;// what was the last entry from which you searched?
};

// a version of CPtrArray which uses reference counting !
class CrcPtrArray : public CPtrArray //CObArray
{
public:
	CrcPtrArray();
	virtual ~CrcPtrArray();
	void RemoveAt(int nIndex, int nCount=1);
	int Add( void* newElement);
	void InsertAt(int nIndex, void* newElement, int nCount = 1);
	void SetAt(int nIndex, void* newElement);
#if 0
  void* GetAt(int nIndex);
#endif
};

class paramPtrArray : public CrcPtrArray 
{
public:
  CDWordArray aParam;
	HRESULT orderByParam( CDirectionStep* pDirInc);
	HRESULT simplify( );
  paramPtrArray(int );
  virtual ~paramPtrArray();
};
// collection of loop intersection points for a given surface
class loopXPts 
{
public:
  CSurfaceStep* m_pSurfaceContainingLoop;
//CPlaneStep* m_pPlaneStepOnNegFeature;
  CrcPtrArray loopIntersectionPoints;
  loopXPts( //CSurfaceStep& rSurfaceContainingLoop
          );
  virtual ~loopXPts( );
};

typedef CTypedPtrArray<CPtrArray, loopXPts*> loopXPointArray;

//////////////////////////////////////////////////////////
// who  date      history
//-----------------------
// wh 02/16/02    loopXPts added to track the surface which contains the intersection pts

#endif // !defined(AFX_AGITOPTRARRAY_H__6C17A082_7532_11D5_8CB2_00D00908C1A5__INCLUDED_)
