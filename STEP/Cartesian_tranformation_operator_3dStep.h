// Cartesian_tranformation_operator_3dStep.h: interface for the CCartesian_tranformation_operator_3dStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CARTESIAN_TRANFORMATION_OPERATOR_3DSTEP_H__CAEC3FB7_14EC_11D5_BFF6_0004AC6EEF35__INCLUDED_)
#define AFX_CARTESIAN_TRANFORMATION_OPERATOR_3DSTEP_H__CAEC3FB7_14EC_11D5_BFF6_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Cartesian_tranformation_operatorStep.h"
#include "transformationMatrix.h"

class CCartesian_tranformation_operator_3dStep : public CCartesian_tranformation_operatorStep  
{
friend class CCartesian_pointStep;
  // TBD change to float
  transformationMatrix3d transform;// transformation matrix

public:
	CCartesian_tranformation_operator_3dStep(double Xmove, 
                                           double Ymove, 
                                           double Zmove);
	virtual ~CCartesian_tranformation_operator_3dStep();

	bool translate(                          double Xmove, 
                                           double Ymove, 
                                           double Zmove);
	bool rotate(double theta, double phi, double psi);
  HRESULT backPtr( CBaseStep*& prBrep);
};

#endif // !defined(AFX_CARTESIAN_TRANFORMATION_OPERATOR_3DSTEP_H__CAEC3FB7_14EC_11D5_BFF6_0004AC6EEF35__INCLUDED_)
