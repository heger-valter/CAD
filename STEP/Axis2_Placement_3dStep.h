// Axis2_Placement_3dStep.h: interface for the CAxis2_Placement_3d class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AXIS2_PLACEMENT_3D_H__9B2019D6_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_)
#define AFX_AXIS2_PLACEMENT_3D_H__9B2019D6_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "PlacementStep.h"
#include "DirectionStep.h"

//#pragma message("class AXIS2_PLACEMENT_3D defined");

class CAxis2_placement_3dStep : public CPlacementStep  
{
  friend class step;
public:
   CDirectionStep* m_pAxis; 

   CDirectionStep* m_pRef_direction;// defines the up direction

	HRESULT negate(void);
	void fin();
	double p(unsigned int i);
//virtual 
    CDirectionStep* axis();
//virtual 
    CDirectionStep* ref_direction();
	void Serialize( stepArchive &ar);
	CAxis2_placement_3dStep( CCartesian_pointStep*  pLocation, 
                           CDirectionStep*        pAxis           = NULL, 
                           CDirectionStep*        pRef_direction  = NULL);
	virtual ~CAxis2_placement_3dStep();
  HRESULT backPtr( CBaseStep*& prBrep);

};
//////////////////////////////////////////////////////////
// who  date      history
// wh   01/01/02  

#endif // !defined(AFX_AXIS2_PLACEMENT_3D_H__9B2019D6_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_)
