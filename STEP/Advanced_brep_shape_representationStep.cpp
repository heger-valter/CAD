// baseStep.cpp: implementation of the CBaseStep class.
//
//////////////////////////////////////////////////////////////////////

//#include <string>
//CString.h"

#include "stdafx.h"
#include "Advanced_brep_shape_representationStep.h"
#include "Manifold_solid_brepStep.h"
#include "Connected_face_setStep.h"
#include "Geometric_Representation_contextStep.h"
#include "StepSer.h"
#include "ScribVw.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAdvanced_brep_shape_representationStep::
    CAdvanced_brep_shape_representationStep( CManifold_solid_brepStep*    pManifold_solid_brepStep, 
                                             CRepresentation_contextStep* pRepresentative_context, 
                                             step*                        pStep)  
  : CShape_representationStep( pStep)
  , m_pRepresentative_context(pRepresentative_context)
{
  nameClass("ADVANCED_BREP_SHAPE_REPRESENTATION");  
  m_pParent = pManifold_solid_brepStep;
  m_pManifold_solid_brepStep = pManifold_solid_brepStep;
}

CAdvanced_brep_shape_representationStep::
    CAdvanced_brep_shape_representationStep( t_aManifold_solid_brepStep&  aManifold_solid_brepStep, 
                                             CRepresentation_contextStep* pRepresentative_context, 
                                             step*                        pStep)  
  : CShape_representationStep( pStep)
  , m_pRepresentative_context(pRepresentative_context)
{
  nameClass("ADVANCED_BREP_SHAPE_REPRESENTATION");  
  for (int i=0; i<aManifold_solid_brepStep.GetSize(); i++){
    m_aManifold_solid_brepStep.Add( aManifold_solid_brepStep.GetAt( i));
  }
}

CAdvanced_brep_shape_representationStep::~CAdvanced_brep_shape_representationStep()
{
  m_pRepresentative_context->release();
  m_pRepresentative_context = NULL;
}

HRESULT CAdvanced_brep_shape_representationStep::backPtr(CBaseStep *&prBrep)
{
  prBrep = m_pParent;  
  return S_OK;
}
void CAdvanced_brep_shape_representationStep::Serialize(stepArchive &ar)
{
  try{
    if (!isSerialized()){
      setSerialized();
      writePre(ar);
      ar <<   "''," ;
//    ar <<  m_aManifold_solid_brepStep.GetAt(0).getNum();
      if (0 < m_aManifold_solid_brepStep.GetSize()){
        writeNtuple( ar, &m_aManifold_solid_brepStep, m_aManifold_solid_brepStep.GetSize());
      }
      else{
        ar << "($)" ;
      }
      ar << ",#" ;
      ar << m_pRepresentative_context->getNum();
      writePost(ar);
//    ASSERT( this == m_pManifold_solid_brepStep->m_pBack)
//    m_aManifold_solid_brepStep.GetAt(0).Serialize(ar);
//    m_pManifold_solid_brepStep->Serialize(ar);
      for (int i =0; i< m_aManifold_solid_brepStep.GetSize(); i++){
        CManifold_solid_brepStep* p_Manifold_solid_brepStep = 
          (CManifold_solid_brepStep* ) m_aManifold_solid_brepStep.GetAt(i);
        p_Manifold_solid_brepStep->m_pBack = this;
        p_Manifold_solid_brepStep->Serialize(ar);
      }
      m_pRepresentative_context->Serialize(ar);
    }
  }
  catch(...){
    ar << "\n/*Errors detected in CAdvanced_brep_shape_representationStep::Serialize #\n";
//  ar << getNum();
    ar <<   ", but continuing*/\n" ;    
    setSerialized();
  }

}


//////////////////////////////////////////////////////////
// who  date      history

