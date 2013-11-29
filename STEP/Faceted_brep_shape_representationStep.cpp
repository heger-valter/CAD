// baseStep.cpp: implementation of the CBaseStep class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "Faceted_brep_shape_representationStep.h"
#include "Manifold_solid_brepStep.h"
#include "Connected_face_setStep.h"
#include "Geometric_Representation_contextStep.h"
#include "StepSer.h"
#include "ScribVw.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



CFaceted_brep_shape_representationStep::
    CFaceted_brep_shape_representationStep( CPtrArray& a_Faceted_brepStep, 
                                            CRepresentation_contextStep* pRepresentative_context, 
                                            step* pStep )  
: CShape_representationStep( pStep)
, m_pRepresentative_context(pRepresentative_context)
{
  m_pRepresentative_context->addRef();
  nameClass("FACETED_BREP_SHAPE_REPRESENTATION");  
  for (int i = 0; i < a_Faceted_brepStep.GetSize(); i++){
    CFaceted_brepStep* pS = (CFaceted_brepStep*)a_Faceted_brepStep.GetAt( i);
    m_a_Faceted_brepStep.Add( pS );// wh this must go away soon 3/22/01
    pS->addRef();
  }
}

CFaceted_brep_shape_representationStep::
  ~CFaceted_brep_shape_representationStep()
{
  for (int i = m_a_Faceted_brepStep.GetSize()-1; i >= 0; i--){
    CFaceted_brepStep* pS = (CFaceted_brepStep*)m_a_Faceted_brepStep.GetAt( i);
    pS->release();
    pS->release();
  }
  m_pRepresentative_context->release();

}
HRESULT CFaceted_brep_shape_representationStep::backPtr(CBaseStep *&prBrep)
{
  prBrep = NULL;  
  return S_OK;
}

void CFaceted_brep_shape_representationStep::Serialize(stepArchive &ar)
{
  char out[128] = "(51%) ";
  strcat(out, this->m_szTheClass);
#if     NOTIFICATION 
  CRepresentationStep::m_pStep->m_pScribView->Notify( out);
#endif//NOTIFICATION 

  try{
    if (!isSerialized()){
      setSerialized();
      writePre(ar);
      ar <<   "''," ;
      if (0 < m_a_Faceted_brepStep.GetSize()){
        writeNtuple( ar, &m_a_Faceted_brepStep, m_a_Faceted_brepStep.GetSize());
      }
      else{
        ar <<   "($)" ;
      }
      ar << ",#" ;
      ar << m_pRepresentative_context->getNum();
      writePost(ar);
      for (int i =0; i< m_a_Faceted_brepStep.GetSize(); i++){
        CFaceted_brepStep* p_Faceted_brepStep = (CFaceted_brepStep* ) m_a_Faceted_brepStep.GetAt(i);
        p_Faceted_brepStep->m_pBack = this;
        p_Faceted_brepStep->Serialize(ar);
      }
      m_pRepresentative_context->m_pBack = this ;
      m_pRepresentative_context->Serialize(ar);
    }
  }
  catch(...){
    ar << "\n/*Errors detected in CClosed_shellStep::Serialize #\n";
//  ar << getNum();
    ar <<   ", but continuing*/\n" ;    
  }

}

void CFaceted_brep_shape_representationStep::fin()
{
  m_pRepresentative_context->release();//p108
  m_pRepresentative_context=NULL;//
  CShape_representationStep::fin();
}

//////////////////////////////////////////////////////////
// who  date      history


