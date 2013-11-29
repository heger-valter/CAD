// agito.cpp: implementation of the agito class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "scribble.h"
#include "agito.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

agitoFeature::agitoFeature() 
: m_bNegated(false)
{

}

agitoFeature::~agitoFeature()
{// wh 8/24/01
  for (int i = 0; i< GetSize(); i++){
    CConnected_face_setStep* pCFS = (CConnected_face_setStep* ) this->GetAt(i);
    if (NULL != pCFS){
      pCFS->release();
    }
  }
}

HRESULT agitoFeature::negate(void )
{
  if (!m_bNegated)// wh 09/10/01
  {
    for (int i = 0; i< GetSize(); i++){
      CConnected_face_setStep* pCFS = (CConnected_face_setStep* ) this->GetAt(i);
      pCFS->negate();
    }
  }
  m_bNegated = true;
  return S_OK;
}

HRESULT agitoFeature::validate()
{
  for (int i = 0; i< GetSize(); i++){
    CConnected_face_setStep* pCFS = (CConnected_face_setStep* ) this->GetAt(i);
    pCFS->validate();
  }
  return S_OK;
}

int agitoFeature::Add( void *pConnected_face_setStep)
{
  CObject* pO = (CObject* ) pConnected_face_setStep;
  ASSERT(NULL !=  dynamic_cast<CConnected_face_setStep*>(pO));
//((CConnected_face_setStep*)pConnected_face_setStep)->addRef();
  
  return CPtrArray::Add( (void*)pConnected_face_setStep);
}

void * agitoFeature::GetAt(int iIndex) const
{
  void* pV = CPtrArray::GetAt(iIndex);
  CObject* pO = (CObject* )pV;
//ASSERT(NULL !=  dynamic_cast<CConnected_face_setStep*>(pO));
  return pV;
}

// merge the connect face sets 
HRESULT agitoFeature::mergeCFSFacetted( int                       is, 
                                      //agitoFeature*             pFeature, 
                                        CConnected_face_setStep*  pShellStep)
{
  CConnected_face_setStep* pShellStep2 = (CConnected_face_setStep* )
    this->GetAt( is);
  for (int  ic = 0; 
            ic < pShellStep2->m_pCFS_faces->GetSize(); 
            ic++){
    // weed out null faces here
    CBaseStep* pB = (CBaseStep*) pShellStep2->m_pCFS_faces->GetAt(ic);
    if (NULL != pB){
      CFaceStep*pF = dynamic_cast<CFaceStep*>(pB);
      ASSERT( NULL != pF);
      pShellStep->m_pCFS_faces->Add( pB );

//    ASSERT( NULL != pB->m_pTechnadrawEntitites);
      if (NULL != pB->m_pTechnadrawEntitites){

          pB->m_pTechnadrawEntitites->AddStep(  pShellStep);
        
      }


      pShellStep2->m_pCFS_faces->SetAt(ic, NULL);
      if (pShellStep2->m_bOpen){// wh 7/15/01
        pShellStep->demote();
      }
    }
  }//ic
  pShellStep2->m_pTechnadrawEntitites->AddStep(  pShellStep);
  pShellStep2->m_pCFS_faces->SetSize(0); 
  pShellStep2->release();
  SetAt(is, NULL);

  return S_OK;
}

// remove the connected face sets in facetted represention
HRESULT agitoFeature::removeCFSFacetted(  int                       is, // index of current shell being manuipulated
                                          CConnected_face_setStep*  pShellStep) // shell
{

  // find the intersection of the bound boxes of the features, 
  //  then find the intersection of the polygons
  //  reverse topology, make a [inner]bound, not an outer_bound

  CConnected_face_setStep* pShellStep2 = (CConnected_face_setStep* )
    this->GetAt( is);

//kfmrh(s, f1, f2);
  for (int ic = 0; ic< pShellStep2->m_pCFS_faces->GetSize(); ic++){

    pShellStep->m_pCFS_faces->
      Add((LPVOID) pShellStep2->m_pCFS_faces->GetAt(ic));
    CFaceStep* pFS = (CFaceStep*) pShellStep2->m_pCFS_faces->GetAt(ic);
//  CConnected_face_setStep::map_surface.SetAt( ic, (void*) ic);
    pFS->release();// wh 12/10/01
    pShellStep2->m_pCFS_faces->SetAt( ic, NULL);// wh 12/10/01
  }//ic
  pShellStep2->m_pTechnadrawEntitites->AddStep(  pShellStep);
  pShellStep2->m_pCFS_faces->SetSize(0);// wh 12/10/01
  pShellStep2->release();
  SetAt(is, NULL);
  return S_OK;
}

agitoComponent::agitoComponent() 
{

}

agitoComponent::~agitoComponent()
{
//for (int iP=0; iP<this->GetSize();iP++){
//  agitoFeature* pFeature = (agitoFeature* )this->GetAt(iP);
//  delete pFeature;
//}
}

HRESULT agitoComponent::negate(void )
{
  for (int i = 0; i < GetSize(); i++){
    agitoFeature* pFeature = (agitoFeature*) GetAt(i);
    pFeature->negate();
  }
  return S_OK;
}


agitoPart::agitoPart() 
: m_pCartesian_tranformation_operator_3dStep( NULL)
, m_pCartesian_pointStepPtrArray( NULL)
, m_pVertex_pointStepPtrArray( NULL)
{

}

agitoPart::~agitoPart()
{ 
  if (NULL != m_pCartesian_tranformation_operator_3dStep ){
    m_pCartesian_tranformation_operator_3dStep->release();
  }
  m_pCartesian_tranformation_operator_3dStep = NULL;
}

HRESULT agitoPart::negate(void )
{
  for (int i = 0; i < GetSize(); i++){
    agitoComponent* pLump = (agitoComponent*) GetAt(i);
    pLump->negate();
  }
  return S_OK;
}

agitoAssembly::agitoAssembly() 
{

}

agitoAssembly::~agitoAssembly()
{
//for (int iA = 0; iA< this->GetSize(); iA++) {
//  agitoPart* pPart = (agitoPart* )this->GetAt(iA);
  //SetAt(iA, NULL);
//  try{
//    delete pPart ;
//  } 
//  catch (...){
//  }
//}
}

HRESULT agitoAssembly::negate(void )
{
  for (int i = 0; i < GetSize(); i++){
    agitoPart* pPart = (agitoPart*) GetAt(i);
    pPart->negate();
  }
  return S_OK;
}



int agitoComponent::Add(void* pFeature)
{
  CObject* pO = (CObject* )pFeature;
  pFeature = dynamic_cast<agitoFeature*>(pO);
  ASSERT(NULL != pFeature);
  // make sure that it is not added twice
  for (int i=0; i <GetSize() ;i++) {
    if (GetAt(i) == pFeature){
      return i;
    }
  }
  return CPtrArray::Add( (void*) pFeature);
}

void* agitoComponent::GetAt(int i) const
{
  void* pV = CPtrArray::GetAt( i);
  CObject* pO = (CObject* )pV;
  ASSERT(NULL != dynamic_cast<agitoFeature*>(pO));
  return pV;
}

void* agitoAssembly::GetAt(int i) const
{
  void* pV = CPtrArray::GetAt( i);
  CObject* pO = (CObject* )pV;
  ASSERT(NULL != dynamic_cast<agitoPart*>(pO));
  return pV;
}

int agitoAssembly::Add(void* pLump)
{
  CObject* pO = (CObject* )pLump;
  ASSERT(NULL != dynamic_cast<agitoPart*>(pO));
  return CPtrArray::Add( (void*) pLump);
}

void* agitoPart::GetAt(int i) const
{
  void* pV = CPtrArray::GetAt( i);
  CObject* pO = (CObject* )pV;
  ASSERT(NULL != dynamic_cast<agitoComponent*>(pO));         //  stl
//ASSERT( pO->IsKindOf( RUNTIME_CLASS( agitoComponent ) ) ); //  mfc
  return pV;
}

int agitoPart::Add(void* pLump)
{
  CObject* pO = (CObject* )pLump;
  ASSERT(NULL !=  dynamic_cast<agitoComponent*>(pO));
  return CPtrArray::Add( (void*) pLump);
}
