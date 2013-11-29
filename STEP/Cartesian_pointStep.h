// Cartesian_pointStep.h: interface for the CCartesian_pointStep0 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CARTESIAN_POINTSTEP_H__7C3E2FFB_6672_4F63_BB14_ED0D102308E3__INCLUDED_)
#define AFX_CARTESIAN_POINTSTEP_H__7C3E2FFB_6672_4F63_BB14_ED0D102308E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PointStep.h"

class CBaseStep;
class CVertex;
class CCartesian_tranformation_operator_3dStep;
class CVectorStep;

class CCartesian_pointStep: public CPointStep
{
  friend 	CCartesian_pointStep* mid(CCartesian_pointStep& p0, CCartesian_pointStep& p1);
  int m_dim;// really should use CGeometric_representation_contextStep::m_iDim;
public:
  CCartesian_pointStep( CBaseStep*pIn, double x, double y=0.0, double z=0.0, int dim=3);
	virtual ~CCartesian_pointStep();
  void Serialize( stepArchive &ar);
public:   
	HRESULT Rehash(int i, CCartesian_pointStepPtrArray *pCartesian_pointStepPtrArray);// in case the entity gets moved, need to update the hash table entry
	CCartesian_pointStep(CBaseStep* pBaseStep, CCartesian_pointStep& rhs);
//private:
  double coordinates[3];
public:   
  CCartesian_pointStep& operator +=(CCartesian_tranformation_operator_3dStep &rLhs);
  CCartesian_pointStep& operator *=(CCartesian_tranformation_operator_3dStep &rLhs);
  CCartesian_pointStep& operator +=(CCartesian_pointStep &rLhs);
  CCartesian_pointStep& operator -=(CCartesian_pointStep &rLhs);
  CCartesian_pointStep& operator +=(CVectorStep &rLhs);
//bool operator ==(CCartesian_pointStep& rhs);
  CCartesian_pointStep& operator=(CCartesian_pointStep &rLhs);
  HRESULT backPtr( CBaseStep *&prBrep);
  CCartesian_pointStep& operator /=(float  fDivisor);
};

	double getLength2( CCartesian_pointStep* pExistingCartesian_pointElement0, 
                     CCartesian_pointStep* pExistingCartesian_pointElement1 );
	double getLength ( CCartesian_pointStep* pExistingCartesian_pointElement0, 
                     CCartesian_pointStep* pExistingCartesian_pointElement1 );
	bool withinTol(    CCartesian_pointStep* pExistingCartesian_pointElement0, 
                     CCartesian_pointStep* pExistingCartesian_pointElement1 );
//inline 
  bool withinTol2(double dDist2);

//	CCartesian_pointStep* mid(CCartesian_pointStep& p0, CCartesian_pointStep& p1);


//////////////////////////////////////////////////////////
// who  date      history
// wh   11/24/01  set parent 
// wh   01/12/02  inline fails in release 

#endif // !defined(AFX_CARTESIAN_POINTSTEP_H__7C3E2FFB_6672_4F63_BB14_ED0D102308E3__INCLUDED_)
