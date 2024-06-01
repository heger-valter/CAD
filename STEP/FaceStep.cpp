// FaceStep.cpp: implementation of the CFaceStep class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#ifdef _WINDOWS 
#include "scribble.h"
#endif

#include "FaceStep.h"
#include "Face_boundStep.h"
#include "ScribVw.h"
#include "RepresentationStep.h"
#include "stepser.h"
#include "Poly_loopStep.h"// wh 10/17/01
#include "SurfaceStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFaceStep::CFaceStep( CBaseStep*        pIn, 
                      CFace_boundStep*  p_face_bound, 
                      int               iNumFB)
: CTopological_representation_itemStep(pIn)
{
  nameClass("Face");
  m_bounds.SetSize(iNumFB);
  m_bounds.SetAt( 0, p_face_bound);
  m_pSurfaceStep = (CSurfaceStep *) pIn;//CSurfaceStep
}

CFaceStep::~CFaceStep()
{ 
  ASSERT_VALID(m_pParent);
  m_pSurfaceStep ->release();// 
  //m_pParent->release();// release the CPlaneStep
  fin();

}

HRESULT CFaceStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  return E_FAIL;
}

void CFaceStep::Serialize(stepArchive &ar)
{
  try{
    if (!isSerialized()){
      setSerialized();
    }
  }
  catch(...){
    ar << "\n/*Errors detected in CPlacementStep::Serialize #\n";

    ar <<   ", but continuing*/\n" ;    
  }

}

int CFaceStep::Add(CFace_boundStep *p_face_bound)
{ 

  return  m_bounds.Add((CObject*)p_face_bound);
}

HRESULT CFaceStep::negate(void)
{
  for (int i = 0; i < m_bounds.GetSize(); i++){
    CFace_boundStep* pFB = (CFace_boundStep*) m_bounds.GetAt(i);
    ASSERT(SUCCEEDED(pFB->negate()));
  }
  return S_OK;
}

HRESULT CFaceStep::validate()
{
  for (int i = 0; i < m_bounds.GetSize(); i++){
    CFace_boundStep* pFB = (CFace_boundStep*) m_bounds.GetAt(i);
    ASSERT(SUCCEEDED(pFB->validate()));
  }
  return S_OK;
}

void CFaceStep::fin()
{
  for (int i=0; i< m_bounds.GetSize();i++) {
    CFace_boundStep* pB = (CFace_boundStep*) m_bounds.GetAt(i);
    pB->release();
  }
  m_bounds.SetSize(0);
}

int CFaceStep::GetSize()
{
  return m_bounds.GetSize();
}

CFace_boundStep* CFaceStep::GetAt(int i)
{
  ASSERT(i>0);
  CBaseStep* pBS = (CBaseStep* ) m_bounds.GetAt(i);
  CFace_boundStep* pFB = dynamic_cast<CFace_boundStep*>(pBS);
  return pFB ;
}

CFace_outer_boundStep* CFaceStep::GetFace_outer_bound()
{
  CBaseStep* pBS = (CBaseStep* ) m_bounds.GetAt(0);
  CFace_outer_boundStep* pFB = dynamic_cast<CFace_outer_boundStep*>(pBS);
//ASSERT(pFB->m_bOrientation);// 1/25/02
  return pFB ;
}

//////////////////////////////////////////////////////////
// who  date      history
// wh   10/22/01  face_surface::split does not return another face_surface




