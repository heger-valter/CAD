// transformationMatrix.h: interface for the transformationMatrix class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSFORMATIONMATRIX_H__E99F0E53_29E8_11D5_8019_0004AC6EEF35__INCLUDED_)
#define AFX_TRANSFORMATIONMATRIX_H__E99F0E53_29E8_11D5_8019_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class transformationMatrix2d
// : public matrix2x2
{
    double m_Transformation[3][3];// transformation matrix
public:
	bool rotate( double x=0.e0, double y=0.e0);
	bool move( double x=0.e0, double y=0.e0);
	transformationMatrix2d( double x=0.e0, double y=0.e0);
	virtual ~transformationMatrix2d();
};

class transformationMatrix3d;

class pos3d{
public:
  pos3d(){};
  virtual ~pos3d(){};
  double coordinates[3];
  pos3d& operator +=(transformationMatrix3d &rLhs);
	bool withinTol();
	double getLength2();
  pos3d& crossProduct( double* lhs, double* rhs);
};

class transformationMatrix3d
// : public matrix3x3
{
  friend class CCartesian_pointStep;
  friend class CPointStep;
  friend class pos3d;
  
    double m_Transformation[4][4];// transformation matrix
public:
	bool rotate(double x=0.e0, double y=0.e0, double z=0.e0);
	bool move(double x=0.e0, double y=0.e0, double z=0.e0);
	transformationMatrix3d(double x=0.e0, double y=0.e0, double z=0.e0);
	virtual ~transformationMatrix3d();
};

#endif // !defined(AFX_TRANSFORMATIONMATRIX_H__E99F0E53_29E8_11D5_8019_0004AC6EEF35__INCLUDED_)
