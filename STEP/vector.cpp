// vector.cpp: implementation of the vector class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _WINDOWS
#include "stdafx.h"
#endif

#ifdef _WINDOWS 
#include "scribble.h"
#endif

#include "vector.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

vector::vector()
{

}

vector::~vector()
{

}

vector& vector::crossProduct( double* lhs, double* rhs)
{
  coordinates[0] = lhs[1] * rhs[2] - lhs[2] * rhs[1];
  coordinates[1] =-lhs[0] * rhs[2] + lhs[2] * rhs[0];
  coordinates[2] = lhs[0] * rhs[1] - lhs[1] * rhs[0];

  return *this;
}

double vector::getLength2()
{
  double len2  = coordinates[0] * coordinates[0] ;
         len2 += coordinates[1] * coordinates[1] ;
         len2 += coordinates[2] * coordinates[2] ;
  return len2 ;
}

bool vector::withinTol()
{
  return ( getLength2()< tol2);
}
