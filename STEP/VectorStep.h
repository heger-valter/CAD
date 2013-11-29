// VectorStep.h: interface for the CVectorStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VECTORSTEP_H__0C5C1023_13EB_11D5_9387_0004AC6EEF35__INCLUDED_)
#define AFX_VECTORSTEP_H__0C5C1023_13EB_11D5_9387_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Geometric_representation_itemStep.h"
#include "PointStep.h"

class CDirectionStep ;
class CVectorStep : public CGeometric_representation_itemStep  
{
  friend class CDirectionStep ;
  friend class CCartesian_pointStep ;
  friend class step;
public:
	HRESULT withinTol(bool &withinTol);
	HRESULT negate(void);
	CVectorStep( CDirectionStep& rDirectionStep);
    double coordinates[3];
	bool normalize();
	CVectorStep(CVectorStep& rVectorStep);
	double m_dMagnitude;
	CVectorStep(CCartesian_pointStep&p0, CCartesian_pointStep&p1);
	CVectorStep(CCartesian_pointStep&p0);
	virtual ~CVectorStep();
	void Serialize(stepArchive &ar);
  CDirectionStep * m_pOrientation;
  CVectorStep& operator -=(CVectorStep &rhs);
  CVectorStep& operator *=(double d);
  double getLength2();
//CVectorStep* crossProd( CVectorStep& rD0, CVectorStep& rD1);
  double getLength();
private:
friend CVectorStep* crossProduct( CVectorStep &rD0, CVectorStep &rD1);
  CVectorStep(void);
  HRESULT backPtr( CBaseStep*& prBrep);

public: 
  bool bAssertDestructor;// wh 01/23/-2
};
	double dotProduct( CVectorStep& rD0, CVectorStep& rD1);
	CVectorStep* crossProduct( CVectorStep& rD0, CVectorStep& rD1);

  double getLength2( CVectorStep* pVectorStep0, 
                     CVectorStep* pVectorStep1 );

#endif // !defined(AFX_VECTORSTEP_H__0C5C1023_13EB_11D5_9387_0004AC6EEF35__INCLUDED_)
