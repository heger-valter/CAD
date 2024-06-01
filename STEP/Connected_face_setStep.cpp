// Connected_face_setStep.cpp: implementation of the CConnected_face_setStep class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#ifdef _WINDOWS 
#include "scribble.h"
#endif

#include "Connected_face_setStep.h"
#include "stepArchive.h"
#include "faceStep.h"
#include "StepSer.h"
#include "ScribVw.h"
#include "RepresentationStep.h"
#include "Cartesian_tranformation_operator_3dStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CConnected_face_setStep::CConnected_face_setStep(
                                                  CPtrArray*               pFaceStepPtrArray, 
                                                  CRepresentation_itemStep *pRepresentation_itemStep )
: CTopological_representation_itemStep( this)
, m_pCFS_faces( pFaceStepPtrArray)
, m_pRepresentation_itemStep( pRepresentation_itemStep)
, m_bOpen(false)
{
  nameClass("CONNECTED_FACE_SET");
//m_pRepresentation_itemStep->addRef();//not set yet wh 8/26/01
}

CConnected_face_setStep::~CConnected_face_setStep()
{ 
#if 1// repair me wh 8/26/01
  if( NULL != m_pCFS_faces){
     int is = m_pCFS_faces->GetSize();
     for ( int i = 0; i< is; i++){
        CFaceStep* pF = (CFaceStep*)m_pCFS_faces->GetAt(i);
        if (NULL != pF){
          pF->release();
        }
     }
  }
#endif
  if (NULL != m_pCFS_faces){
    delete  m_pCFS_faces;  
  }
  m_pCFS_faces=NULL;
  zeroTechnadrawPtr();
}

void CConnected_face_setStep::Serialize( stepArchive &ar)
{
  char out[128] = "(55%) ";
  strcat(out, this->m_szTheClass);

#if     NOTIFICATION 
  if (CRepresentationStep::m_pStep->m_bWriteFile){
    CRepresentationStep::m_pStep->m_pScribView->Notify( out);}
#else //NOTIFICATION 
#endif//NOTIFICATION 

#ifdef  SHOWPROGRESS
  if (CRepresentationStep::m_pStep->m_bWriteFile){
    CRepresentationStep::m_pStep->m_pScribView->progressBarUpdate( 55);}
#endif//SHOWPROGRESS

  try{
    if (!isSerialized()){
      setSerialized();
      if (NULL != m_pCFS_faces){
       writeNtuple( ar, m_pCFS_faces);
       int is = m_pCFS_faces->GetSize();
       for ( int i = 0; i< is; i++){
          CFaceStep* pS = (CFaceStep*)m_pCFS_faces->GetAt(i);
          pS->Serialize(ar);
       }
      }
      else {
        writeChild(ar, m_pRepresentation_itemStep->getNum());
        m_pRepresentation_itemStep->Serialize(ar);
      }
    }
  }
  catch(...){
    ar << "\n/*Errors detected in CConnected_face_setStep::Serialize #\n";
    ar << getNum();
    ar <<   ", but continuing*/\n" ;    
  }
}

CPtrArray CConnected_face_setStep::map_part;// map the Tasdraw polygon (input) to the shell
CPtrArray CConnected_face_setStep::map_lump;// map the Tasdraw polygon (input) to the shell
CPtrArray CConnected_face_setStep::map_feature;// map the Tasdraw polygon (input) to the shell
CPtrArray CConnected_face_setStep::map_shell;// map the Tasdraw polygon (input) to the shell
// tells you which poly maps to which face
CPtrArray CConnected_face_setStep::map_face;// map the Tasdraw polygon (input) to the face on the shell
CPtrArray CConnected_face_setStep::map_surface;// 
CClosed_shellStep::CClosed_shellStep( CConnected_face_setStep* pConnected_face_setStep, 
                                      CPtrArray *pFace_surfaceStepPtrArray)
  :  CConnected_face_setStep( pFace_surfaceStepPtrArray)
{
  nameClass("CLOSED_SHELL");
  m_pConnected_face_setStep = pConnected_face_setStep;
  m_pConnected_face_setStep->addRef();
}

CClosed_shellStep::~CClosed_shellStep()
{
  CTopological_representation_itemStep* pTRI= 
    dynamic_cast<CTopological_representation_itemStep*>
      (m_pConnected_face_setStep->m_pRepresentation_itemStep);
      
  if (NULL != pTRI){
    pTRI->m_pParent->release();
    pTRI->release();
  }
  m_pConnected_face_setStep->release();
  m_pConnected_face_setStep->release();
  m_pConnected_face_setStep=NULL;
}

bool CClosed_shellStep::m_bProgressed;

HRESULT CClosed_shellStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  else {
    return E_FAIL;
  }
}

void CClosed_shellStep::Serialize( stepArchive &ar)
{
  try{
    if (!isSerialized()){
      setSerialized();
      
      char out[128] = "(53%) ";
      strcat(out, this->m_szTheClass);
#if     NOTIFICATION 
      if (CRepresentationStep::m_pStep->m_bWriteFile)
          CRepresentationStep::m_pStep->m_pScribView->Notify( out);
#else //NOTIFICATION 
#endif//NOTIFICATION 

#ifdef  SHOWPROGRESS
      if ( !m_bProgressed ){
        if (CRepresentationStep::m_pStep->m_bWriteFile)
              CRepresentationStep::m_pStep->m_pScribView->progressBarUpdate( 53);
              this->m_bProgressed = true;
            }
#endif//SHOWPROGRESS

      writePre(ar);

      ar << "'', " ;
      // this is too long
      writeNtuple(ar, m_pCFS_faces, m_pCFS_faces->GetSize());
      writePost(ar);

#ifdef   WRITEEULER
      CBaseStep* pBaseStep=NULL;
      backPtr( pBaseStep);
      
      if (NULL!=pBaseStep){
        CManifold_solid_brepStep* pManifold_solid_brepStep=(CManifold_solid_brepStep*) pBaseStep;
        pManifold_solid_brepStep->eulerCnt.m_numClosedShells++;
      }
#endif//WRITEEULER

      int is = m_pCFS_faces->GetSize();
      for ( int i = 0; i< is; i++){
        CFaceStep* pS = (CFaceStep*)m_pCFS_faces->GetAt(i);
        if (NULL != pS){
          pS->m_pBack = this;
          pS->Serialize(ar);
        }
      }
    }
  }
  catch(...){
    ar << "\n/*Errors detected in CClosed_shellStep::Serialize #\n";
//  ar << getNum();
    ar <<   ", but continuing*/\n" ;    
  }
#if     NOTIFICATION 
  CRepresentationStep::m_pStep->m_pScribView->Notify("(65%) CClosed_shellStep::Serialize");
#else //NOTIFICATION 
#endif//NOTIFICATION 

#ifdef  SHOWPROGRESS
//      CRepresentationStep::m_pStep->m_pScribView->progressBarUpdate( 65);
#endif//SHOWPROGRESS
}

// wh   03/15/01  try/catch in serialize

void CClosed_shellStep::fin()
{
  m_pConnected_face_setStep->release();
  m_pConnected_face_setStep=NULL;
  CConnected_face_setStep::release();
  release();
}

template <class T> 
CShellStep<T>::CShellStep( CConnected_face_setStep* pConnected_face_setStep, 
                           CPtrArray*               pFace_surfaceStepPtrArray)
  :  CConnected_face_setStep( pFace_surfaceStepPtrArray)
{
//nameClass( T.getName());
  m_pConnected_face_setStep = pConnected_face_setStep;
}

template <class T> 
CShellStep<T>::~CShellStep()
{
  fin();
}
#if 0
template <class T> 
void CShellStep<T>::Serialize( stepArchive &ar)
{
  try{
    if (!isSerialized()){
      setSerialized();
      
      char out[128] = "(53%) ";
      strcat(out, this->name);
#if     NOTIFICATION 
  if (CRepresentationStep::m_pStep->m_bWriteFile)
      CRepresentationStep::m_pStep->m_pScribView->Notify( out);
#else //NOTIFICATION 
#endif//NOTIFICATION 

#ifdef  SHOWPROGRESS
  if (CRepresentationStep::m_pStep->m_bWriteFile)
      CRepresentationStep::m_pStep->m_pScribView->progressBarUpdate( 53);
#endif//SHOWPROGRESS

      writePre(ar);
      ar << "'', " ;
      writeNtuple(ar, m_pCFS_faces, m_pCFS_faces->GetSize());
      writePost(ar);

#ifdef   WRITEEULER
      CBaseStep* pBaseStep=NULL;
      backPtr( pBaseStep);
      if (NULL!=pBaseStep){
        CManifold_solid_brepStep* pManifold_solid_brepStep=(CManifold_solid_brepStep*) pBaseStep;
        pManifold_solid_brepStep->eulerCnt.m_numOpenShells++;
      }
#endif//WRITEEULER

      int is = m_pCFS_faces->GetSize();
      for ( int i = 0; i< is; i++){
        CFaceStep* pS = (CFaceStep*)m_pCFS_faces->GetAt(i);
        if (NULL != pS){
          pS->m_pBack = this;
          pS->Serialize(ar);
        }
      }
    }

  }
  catch(...){
    ar << "\n/*Errors detected in CShellStep::Serialize #\n";
//  ar << getNum();
    ar <<   ", but continuing*/\n" ;    
  }
#if     NOTIFICATION 
  if (CRepresentationStep::m_pStep->m_bWriteFile)
  CRepresentationStep::m_pStep->m_pScribView->Notify("(65%) CShellStep::Serialize");
#else //NOTIFICATION 
#endif//NOTIFICATION 

#ifdef  SHOWPROGRESS
  if (CRepresentationStep::m_pStep->m_bWriteFile)
  CRepresentationStep::m_pStep->m_pScribView->progressBarUpdate( 65);
#endif//SHOWPROGRESS
}
#endif
// wh   03/15/01  try/catch in serialize

template <class T> 
void CShellStep<T>::fin()
{
  m_pConnected_face_setStep->release();
  m_pConnected_face_setStep=NULL;
  CConnected_face_setStep::release();
  release();
}


#if 0

COpen_shellStep::COpen_shellStep( CConnected_face_setStep* pConnected_face_setStep, 
                                      CPtrArray *pFace_surfaceStepPtrArray)
  :  CConnected_face_setStep( //pConnected_face_setStep, 
                              pFace_surfaceStepPtrArray)
  {
    nameClass("OPEN_SHELL");
    m_pConnected_face_setStep = pConnected_face_setStep;
  }

COpen_shellStep::~COpen_shellStep()
{
  fin();
/*
  delete m_pConnected_face_setStep;
  m_pConnected_face_setStep=NULL;
*/
}

void COpen_shellStep::Serialize( stepArchive &ar)
{
  try{
    if (!isSerialized()){
      setSerialized();
      
      char out[128] = "(53%) ";
      strcat(out, this->name);
#if     NOTIFICATION 
  if (CRepresentationStep::m_pStep->m_bWriteFile)
      CRepresentationStep::m_pStep->m_pScribView->Notify( out);
#else //NOTIFICATION 
#endif//NOTIFICATION 

#ifdef  SHOWPROGRESS
  if (CRepresentationStep::m_pStep->m_bWriteFile)
      CRepresentationStep::m_pStep->m_pScribView->progressBarUpdate( 53);
#endif//SHOWPROGRESS

      writePre(ar);
      ar << "'', " ;
      writeNtuple(ar, m_pCFS_faces, m_pCFS_faces->GetSize());
      writePost(ar);
  
#ifdef   WRITEEULER
      CBaseStep* pBaseStep=NULL;
      backPtr( pBaseStep);
      if (NULL!=pBaseStep){
        CManifold_solid_brepStep* pManifold_solid_brepStep=(CManifold_solid_brepStep*) pBaseStep;
        pManifold_solid_brepStep->eulerCnt.m_numOpenShells++;
      }
#endif//WRITEEULER

      int is = m_pCFS_faces->GetSize();
      for ( int i = 0; i< is; i++){
        CFaceStep* pS = (CFaceStep*)m_pCFS_faces->GetAt(i);
        if (NULL != pS){
          pS->m_pBack = this;
          pS->Serialize(ar);
        }
      }
    }


  }
  catch(...){
    if (CRepresentationStep::m_pStep->m_bWriteFile){
    ar << "\n/*Errors detected in COpen_shellStep::Serialize #\n";
//  ar << getNum();
    ar <<   ", but continuing*/\n" ;    
    }
  }
#if     NOTIFICATION 
  if (CRepresentationStep::m_pStep->m_bWriteFile)
  CRepresentationStep::m_pStep->m_pScribView->Notify("(65%) COpen_shellStep::Serialize");
#else //NOTIFICATION 
#endif//NOTIFICATION 

#ifdef  SHOWPROGRESS
  if (CRepresentationStep::m_pStep->m_bWriteFile)
      CRepresentationStep::m_pStep->m_pScribView->progressBarUpdate( 65);
#endif//SHOWPROGRESS
}
#endif

// wh   03/15/01  try/catch in serialize
/*
void COpen_shellStep::fin()
{
  m_pConnected_face_setStep->release();
  m_pConnected_face_setStep=NULL;
  CConnected_face_setStep::release();
  release();
}
*/

HRESULT CConnected_face_setStep::negate(void)
{
  int is = m_pCFS_faces->GetSize();
  for ( int i = 0; i< is; i++){
    CFaceStep* pF = (CFaceStep*)m_pCFS_faces->GetAt(i);
    if (NULL != pF){
      pF->negate();
    }
  }
  return S_OK;
}

HRESULT CConnected_face_setStep::validate()
{
  int is = m_pCFS_faces->GetSize();
  for ( int i = 0; i< is; i++){
    CFaceStep* pS = (CFaceStep*)m_pCFS_faces->GetAt(i);
    if (NULL != pS){
      pS->validate();
    }
  }
  return S_OK;
}

HRESULT CConnected_face_setStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  else {
    return E_FAIL;
  }
}


// we sometimes have to demote a closed shell if 
// 1)  layer turns off that 
// 2)  it fails Euler's rule
HRESULT CClosed_shellStep::demote()
{ 
  m_bOpen = true;
  nameClass("OPEN_SHELL");
  // NB. open shells are not supported by advanced_brep but most vendors accept them!
  return S_OK;
}

//////////////////////////////////////////////////////////
// who  date      history
// wh   5/16/01   moved agitoFeature, part, assembly data structure here
// tbd
