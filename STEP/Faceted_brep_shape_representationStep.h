// Faceted_brep_shape_representationStep.h: interface for the CBaseStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CFaceted_brep_shape_representationStep_H__177869E1_09A6_11D5_BFED_0004AC6EEF35__INCLUDED_)
#define AFX_CFaceted_brep_shape_representationStep_H__177869E1_09A6_11D5_BFED_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afx.h>
#include "stepArchive.h"
#include "Manifold_solid_brepStep.h"
#include "Representation_contextStep.h"
#include "Geometric_Representation_contextStep.h"
#include "shape_representationStep.h"

extern const char* szEndl;
class step;

class CFaceStep;
class CFaceted_brep_shape_representationStep:
    public CShape_representationStep
{
public:
           CFaceted_brep_shape_representationStep( CPtrArray&                    a_Faceted_brepStep,
                                                   CRepresentation_contextStep*  pRepresentative_context=NULL, 
                                                   step*                         pStep=NULL);
	virtual ~CFaceted_brep_shape_representationStep();
  CPtrArray m_a_Faceted_brepStep;
private:
  CRepresentation_contextStep* m_pRepresentative_context;//p108
public:   
	void fin();
  void Serialize( stepArchive &ar);
  HRESULT backPtr( CBaseStep*& prBrep);

};

//////////////////////////////////////////////////////////
// who  date      history


#endif // !defined(AFX_CFaceted_brep_shape_representationStep_H__177869E1_09A6_11D5_BFED_0004AC6EEF35__INCLUDED_)
