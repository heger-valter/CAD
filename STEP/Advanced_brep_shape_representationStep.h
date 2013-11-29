// Advanced_brep_shape_representationStep.h: interface for the CAdvanced_brep_shape_representationStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAdvanced_brep_shape_representationStep_H__177869E1_09A6_11D5_BFED_0004AC6EEF35__INCLUDED_)
#define AFX_CAdvanced_brep_shape_representationStep_H__177869E1_09A6_11D5_BFED_0004AC6EEF35__INCLUDED_

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

typedef CTypedPtrArray<CPtrArray, CManifold_solid_brepStep*> t_aManifold_solid_brepStep;

class CAdvanced_brep_shape_representationStep: 
    public CShape_representationStep
{
private:
  CRepresentation_contextStep* m_pRepresentative_context;//p108
  CManifold_solid_brepStep*    m_pManifold_solid_brepStep;
  t_aManifold_solid_brepStep m_aManifold_solid_brepStep;
public:
           CAdvanced_brep_shape_representationStep( CManifold_solid_brepStep*        p_Manifold_solid_brepStep, 
                                                    CRepresentation_contextStep*     pRepresentative_context=NULL, 
                                                    step *                           pStep=NULL);

           CAdvanced_brep_shape_representationStep( t_aManifold_solid_brepStep&      aManifold_solid_brepStep, 
                                                    CRepresentation_contextStep*     pRepresentative_context=NULL, 
                                                    step *                           pStep=NULL);

	virtual ~CAdvanced_brep_shape_representationStep();
          void Serialize( stepArchive &ar);
  HRESULT backPtr( CBaseStep*& prBrep);
};

//////////////////////////////////////////////////////////
// who  date      history


#endif // !defined(AFX_CAdvanced_brep_shape_representationStep_H__177869E1_09A6_11D5_BFED_0004AC6EEF35__INCLUDED_)
