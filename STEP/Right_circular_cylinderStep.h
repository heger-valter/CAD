// Right_circular_cylinderStep.h: interface for the CRight_circular_cylinderStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RIGHT_CIRCULAR_CYLINDERSTEP_H__048C7923_2393_11D5_800E_0004AC6EEF35__INCLUDED_)
#define AFX_RIGHT_CIRCULAR_CYLINDERSTEP_H__048C7923_2393_11D5_800E_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Geometric_representation_itemStep.h"
class CCartesian_pointStep;

class CRight_circular_cylinderStep : public CGeometric_representation_itemStep  
{
public:
	CRight_circular_cylinderStep( CCartesian_pointStep& position,
                                double radius=0.0e0,
                                double height=0.0e0);
	virtual ~CRight_circular_cylinderStep();
  double m_radius;
  double m_height;
  CCartesian_pointStep& m_position;
  HRESULT backPtr( CBaseStep*& prBrep);
};

#endif // !defined(AFX_RIGHT_CIRCULAR_CYLINDERSTEP_H__048C7923_2393_11D5_800E_0004AC6EEF35__INCLUDED_)
