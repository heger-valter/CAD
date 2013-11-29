// vector.h: interface for the vector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VECTOR_H__924E7AE1_4327_11D5_8CAE_00D00908C1A5__INCLUDED_)
#define AFX_VECTOR_H__924E7AE1_4327_11D5_8CAE_00D00908C1A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class vector  
{
  double coordinates[3];
public:
	bool withinTol();
	double getLength2();
	vector();
	virtual ~vector();
  vector& crossProduct( double* lhs, double* rhs);
};

#endif // !defined(AFX_VECTOR_H__924E7AE1_4327_11D5_8CAE_00D00908C1A5__INCLUDED_)
