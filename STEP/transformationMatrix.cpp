// transformationMatrix.cpp: implementation of the transformationMatrix class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "transformationMatrix.h"
#include <math.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

transformationMatrix2d::transformationMatrix2d(double x, double y)
{
  m_Transformation[0][0] = 0;
  m_Transformation[0][1] = 0;
  m_Transformation[0][2] = x;

  m_Transformation[1][0] = 0;
  m_Transformation[1][1] = 0;
  m_Transformation[1][2] = y;
  
  m_Transformation[2][0] = 0;
  m_Transformation[2][1] = 0;
  m_Transformation[2][2] = 0;
}

transformationMatrix2d::~transformationMatrix2d()
{

}


bool transformationMatrix2d::move(double x, double y)
{
  return false;
}

bool transformationMatrix2d::rotate(double theta, double rho)
{
  return false;
}

transformationMatrix3d::transformationMatrix3d(double x, double y, double z)
{
  m_Transformation[0][0] = 0;
  m_Transformation[0][1] = 0;
  m_Transformation[0][2] = 0;
  m_Transformation[0][3] = x;

  m_Transformation[1][0] = 0;
  m_Transformation[1][1] = 0;
  m_Transformation[1][2] = 0;
  m_Transformation[1][3] = y;
  
  m_Transformation[2][0] = 0;
  m_Transformation[2][1] = 0;
  m_Transformation[2][2] = 0;
  m_Transformation[2][3] = z;

  m_Transformation[3][0] = 0;
  m_Transformation[3][1] = 0;
  m_Transformation[3][2] = 0;
  m_Transformation[3][3] = 0;
}

transformationMatrix3d::~transformationMatrix3d()
{

}



bool transformationMatrix3d::move(double x, double y, double z)
{
  m_Transformation[0][3] += x;
  m_Transformation[1][3] += y;
  m_Transformation[2][3] += z;

  return false;
}

bool transformationMatrix3d::rotate(double theta, double rho, double phi)
{
  m_Transformation[1][1] += cos(theta);
  m_Transformation[2][2] += cos(theta);
  m_Transformation[1][2] +=-sin(theta);
  m_Transformation[2][1] += sin(theta);

  m_Transformation[0][0] += cos(rho);
  m_Transformation[2][2] += cos(rho);
  m_Transformation[2][0] +=-sin(rho);
  m_Transformation[0][2] += sin(rho);

  m_Transformation[0][0] += cos(phi);
  m_Transformation[1][1] += cos(phi);
  m_Transformation[0][1] +=-sin(phi);
  m_Transformation[1][0] += sin(phi);

return false;

}


pos3d& pos3d::operator +=(transformationMatrix3d &rLhs)
{
  coordinates[0]= coordinates[0] * rLhs.m_Transformation[0][0] +coordinates[1] * rLhs.m_Transformation[0][1] +coordinates[2] * rLhs.m_Transformation[0][2];
  coordinates[1]= coordinates[0] * rLhs.m_Transformation[1][0] +coordinates[1] * rLhs.m_Transformation[1][1] +coordinates[2] * rLhs.m_Transformation[1][2];
  coordinates[2]= coordinates[0] * rLhs.m_Transformation[2][0] +coordinates[1] * rLhs.m_Transformation[2][1] +coordinates[2] * rLhs.m_Transformation[2][2];
  return *this;
}

pos3d& pos3d::crossProduct( double* lhs, double* rhs)
{
  coordinates[0] = lhs[1] * rhs[2] - lhs[2] * rhs[1];
  coordinates[1] =-lhs[0] * rhs[2] + lhs[2] * rhs[0];
  coordinates[2] = lhs[0] * rhs[1] - lhs[1] * rhs[0];

  return *this;
}

double pos3d::getLength2()
{
  double len2  = coordinates[0] * coordinates[0] ;
         len2 += coordinates[1] * coordinates[1] ;
         len2 += coordinates[2] * coordinates[2] ;
  return len2 ;
}

bool pos3d::withinTol()
{
  return ( getLength2()< (8.e0 * restol2));//eightRestol2// wh 02/02/02 
}

//////////////////////////////////////////////////////////
// who  date      history
// wh   02/02/02  make the tolerance for being within tol (therefore coincident) much loose as encountered in otwoport example

