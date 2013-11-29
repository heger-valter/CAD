// DirectionStep.h: interface for the CDirection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIRECTION_H__9B2019D4_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_)
#define AFX_DIRECTION_H__9B2019D4_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Geometric_representation_itemStep.h"

//#pragma message("class CDirectionStep defined");
class CCartesian_pointStep;
class CDirectionStep : public CGeometric_representation_itemStep  
{
friend double dotProduct( CDirectionStep& rD0, CDirectionStep& rD1);
friend bool withinResdot( CDirectionStep &rD0, CDirectionStep &rD1);
friend CDirectionStep* crossProduct( CDirectionStep &rD0, CDirectionStep &rD1);
friend class CVectorStep;
friend class step;
  double m_direction_ratios[3];
  bool m_bGood;
public:
	HRESULT normalize(void);
	HRESULT negate(void);
	CDirectionStep(CDirectionStep&rhs);
	void fin();
  bool isGood(void);// nonZero
	bool withinTol();
	double getLength2();
	double getLength();
//	CDirectionStep& crossProd( CDirectionStep &lhs, CDirectionStep &rhs);
	double direction_ratios(int i);
	void Serialize( stepArchive &ar);
	CDirectionStep( CBaseStep*pIn, double x, double y = 0.0e0, double z = 0.0e0); // wh 10/04/01
	CDirectionStep( CBaseStep*pIn,
                  CCartesian_pointStep& rCartesian_pointStep0, 
                  CCartesian_pointStep& rCartesian_pointStep1); 
	CDirectionStep( CCartesian_pointStep& rCartesian_pointStep0); 
	virtual ~CDirectionStep();
  CDirectionStep& operator -=(CDirectionStep& rhs);
  HRESULT backPtr( CBaseStep*& prBrep);
};

	double dotProduct( CDirectionStep& rD0, CDirectionStep& rD1);

	CDirectionStep* crossProduct( CDirectionStep &lhs, CDirectionStep &rhs);

//////////////////////////////////////////////////////////
// who  date      history

#endif // !defined(AFX_DIRECTION_H__9B2019D4_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_)
