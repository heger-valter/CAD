// baseStep.cpp: implementation of the CBaseStep class.
//
//////////////////////////////////////////////////////////////////////

//#include <string>
//CString.h"

#include "assert.h"
#include "afx.h"
#ifdef _WINDOWS
#include "stdafx.h"
#endif

#include <float.h>// isnan

#include "baseStep.h"
#include "stepArchive.h"
#include "Faceted_brepStep.h"
#include "ScribVw.h"//step
#include "StepSer.h"
#include "RepresentationStep.h"
#include "ExtentsStep.h"
#include "agitoPtrArray.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


const char* szEndl = "\n";

const int iOUT_OF_BOUNDS = -1;
#define GARBAGE_COLLECTION true


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// leave some space for pdm & tm because some fool at NIST said so, 
//  what every happend to minimal information, 
//  what do I care about product design management or config management

//static 
const	unsigned int iFirstCount=2000;


unsigned int CBaseStep::m_iCount = iFirstCount;
class step;
//step& CBaseStep::rStep;


surfaceModelSelect  CBaseStep::aSurfaceModelSelect = faceBasedSurfaceModel;// remove me // wh 10/19/01

CBaseStep ::CBaseStep (CBaseStep * pParent) 
  : m_pParent( pParent)
//  , m_iRef(1L)
  , m_g_ptrArrayIndex(0)
  , m_pTechnadrawEntitites(NULL)
  , m_pBack(NULL)
{
  init();
}

CBaseStep::CBaseStep( )
  : m_pParent( NULL)// wh 10/19/01
//  , m_iRef(1L)
  , m_g_ptrArrayIndex(0)
  , m_pTechnadrawEntitites(NULL)
  , m_pBack(NULL)
{
  init();
}

CBaseStep ::~CBaseStep()
{
  ASSERT_VALID(this);
  ASSERT( 0 <= m_g_ptrArrayIndex);// someone is still referencing me!

  // make sure that no one took your spot
  ASSERT( CRepresentationStep::m_pStep->m_ptrArrayAgito.GetAt( m_g_ptrArrayIndex) == this );// wh 10/19/01
  if (0 <= m_g_ptrArrayIndex){
    // call office and tell them you are checking out
    CRepresentationStep::m_pStep->m_ptrArrayAgito.SetAt( m_g_ptrArrayIndex, NULL);
  }
#ifdef  EXPOSE      
  fprintf( g_errorLog, "\t\t m_ptrArrayAgito[%d] ~CBaseStep this=%p\n", m_g_ptrArrayIndex), this;
#endif//EXPOSE   

  zeroTechnadrawPtr();
}

void CBaseStep::init()
{
  iLhs = 0;
  m_bSerialized = false;
  getNum();
  ASSERT( NULL != CRepresentationStep::m_pStep);
//ASSERT_VALID( NULL != CRepresentationStep::m_pStep->m_ptrArrayAgito);
//#ifdef CREATESTEP  
  // add this class to the collection for garbage collection later
  m_g_ptrArrayIndex = CRepresentationStep::m_pStep->m_ptrArrayAgito.Add(this);
//#endif

//((CObject*)this)->
//nameClass("");
#ifdef  EXPOSE      
  fprintf( g_errorLog, "\t\t m_ptrArrayAgito[%d] CBaseStep this=%p, (#%d ), m_iRef=%u \n"
                             , m_g_ptrArrayIndex,         this, getNum(), getRefCnt());
#endif//EXPOSE   
}

// remove all references to other external objects 
// (only used on REFERENCES, but it does not seem to do the trick)
void CRefObj::fin()// finish up
{
// each parent needs to force children to clean up after the job is done
//remove all references!
  // if noone is referencing me, I am free to be deleted
#ifdef GARBAGE_COLLECTION
	if (0==m_iRef) {
    // release all children first
    delete this;
	}
#endif
}

// indicate that class has been serialized, prevents infinite loops
// return value indicates if setSerialized has been set!

// Question, should it be set after info about this is written, 
// or after all of its children are written (maybe might be a circular reference)
bool CBaseStep::setSerialized()
{
  if ( !isSerialized() ) {
#if 0
      char out[128] = "(";
      int size = CRepresentationStep::m_pStep->m_ptrArrayAgito.GetSize() + iFirstCount;
      size = (size + m_g_ptrArrayIndex) / (size*2);
      itoa( size, &(out[strlen(out)]), 10);
      strcat(out, "%) ");
      strcat(out, m_szTheClass);
#endif
    m_bSerialized = true;
    return true;
  }
  return false;
}

void CBaseStep::writeChild( stepArchive &ar, int i)
{
  writePre(ar);
  writeLabel( ar); 
  ar << "#" ;
  ar << i;
  writePost(ar);
}

bool CBaseStep::nameClass(char *pszName)
{
  // if using shortnames, need to translate long name to short name
  m_szTheClass=pszName;
  m_szTheClass.MakeUpper();
//((CObject*)this)->
//nameClass("");
  return false;
}

bool CBaseStep::writeChild(stepArchive &ar, int i, char *pszC)
{
  writePre(ar);
  writeLabel( ar); 
  ar <<   "#";
  ar << i;
//ar <<   " ";// wasting space for unnecessay blank!
  ar <<   pszC;
  writePost(ar);
  return false;
}

bool CBaseStep::writeChild(stepArchive &ar, int i, bool b    )
{
  writePre(ar);
  ar <<  "'" << m_szLabelName << "',*,*,"; 
  ar <<   "#";
  ar << i;
  ar <<   ",";
  ar <<   b   ;
  writePost(ar);
  return false;
}

bool CBaseStep::writeChild(stepArchive &ar)
{
  writePre(ar);
  writePost(ar);
  return false;
}

bool CBaseStep::writeChild(stepArchive &ar, int i, int j)
{
  writePre(ar);
  writeLabel( ar); 
  ar <<   "#";
  ar << i;
  ar <<   ",#";
  ar << j;
  writePost(ar);
  return false;
}

//inline
void CBaseStep::write1tuple( stepArchive &ar
                           , int &iLen
                           , char* szNext 
                           )
{
  if (NULL != this){
    int iNum = this->getNum();
    // int iLenNum = alog10(iNum);
    // really should do the check here // wh 02/13/02
    ar << szNext;
    ar <<   "#";// step files are limited to 80 chars
    ar << iNum ;
    int iLen2 = ar.GetLength();
    if ((iLen2-iLen+7) > STEP_LINE_LENGTH){
      ar << "\n";
      iLen = iLen2;
    }
    szNext[0] = ',';
  }
}



bool CBaseStep::writeNtuple(stepArchive &ar, CPtrArray*pList, int iSize )
{
  try{
    int iLen = ar.GetLength()+26;

    ar << "(";
    char szNext[2] = {NULL, NULL};
    if ( iSize > 0 ) {
      for ( int i = 0; i<iSize ; i++ ) {
        CBaseStep* pBS = (CBaseStep* ) pList->GetAt(i);
        if (NULL != pBS){
          pBS->write1tuple(ar, iLen, szNext);
        }
      }
      
      ASSERT(NULL != szNext[0]);
      if (NULL == szNext[0]){
//      ar << "$";
      }
    }
    else{
      ar << "$";    // wh 03/26/03
    }
    ar << ")";
  }
  catch(...){
    ar << "\n/*Errors detected in CBaseStep::writeNtuple #\n";
    ar << "$";    
    ar <<   ", but continuing*/\n" ;   
    ar << ")";
  }
  return false;
}

bool CBaseStep::writePre(stepArchive &ar)
{
  ar.setEntry( getNum());
//CString& na= CFaceted_brepStep::m_pStringArray->ElementAt( getNum());
  ar << "#" ;
  ar << getNum();
  ar <<   "=";
  ar << m_szTheClass;
  ar <<  "(";
  return false;
}

bool CBaseStep::writePost(stepArchive &ar)
{
  ar <<   ");";
  ar << szEndl;
  setSerialized();
  return false;
}

bool CBaseStep::writeChild(stepArchive &ar, float* coordinates, int d)
{
  writeLabel( ar); 
  ASSERT(d>0);
  ar <<   "(" ;
//ASSERT(!_isnan(coordinates[0]));
  ar << coordinates[0];
  for (int i = 1; i<  d ; i++){
    ar <<   "," ;
//  ASSERT(!_isnan(coordinates[i]));
    ar << coordinates[i];
  }
  ar <<   ")" ;
  return false;
}

bool CBaseStep::writeDouble(stepArchive &ar, double *coordinates, int d)
{
  ASSERT(d>0);
  
  ar <<   "(" ;
//ASSERT(!_isnan(coordinates[0]));
  ar << coordinates[0];
  for (int i = 1; i<  d ; i++){
    ar <<   "," ;
//  ASSERT(!_isnan(coordinates[i]));
    ar << coordinates[i];
  }
  ar <<   ")" ;
  return false;
}

bool CBaseStep::CountReset()
{
  m_iCount = iFirstCount;

  return false;
}

#if 1
int CBaseStep::getNum()
{
  if (0==iLhs){
    iLhs = m_iCount++;
  }
  return iLhs;
}

#else 
int CBaseStep::getNum()
{
  try {
    if (0==iLhs){
      iLhs = m_iCount++;
    }
  }
  catch (...){
    return iOUT_OF_BOUNDS;
  }
  return iLhs;
}
#endif

bool CBaseStep::writeLabel(stepArchive &ar)
{
  m_szLabelName.Replace( "'", "''" );// replace all single quotes by two single quotes
  // but do this only if there aren't two quotes already
  ar <<  "'" << m_szLabelName << "',";// config_control_design writes some descriptive info here!
  return false;
}

#if 0
template <class T> 
CDerivedBaseStep<T>::CDerivedBaseStep (void) 
: CBaseStep( )
{
//nameClass(T.getName());
}

template <class T> 
CDerivedBaseStep<T>::~CDerivedBaseStep (void) 
{
}

template <class T> 
void 
CDerivedBaseStep<T>::Serialize( stepArchive &ar) 
{
  try{
    if (!isSerialized()){
      setSerialized();
      writePre (ar);
      writeLabel(ar);
      writePost(ar);
      aPtrArray->Serialize( stepArchive &ar) 
    }
  }
  catch(...){
    ar << "\n/*Errors detected in CDerivedBaseStep::Serialize #\n";
    ar << getNum();
    ar <<   ", but continuing*/\n" ;      
  }

}
#endif

//DEL ULONG CBaseStep::addRef()
//DEL {
//DEL   ASSERT( m_iRef > 0);
//DEL   m_iRef++;
//DEL 
//DEL #ifdef  EXPOSE      
//DEL   TRACE3("\tC%sStep::addRef(), (#%d ), m_iRef=%u\n", m_szTheClass.GetBuffer(m_szTheClass.GetLength()), getNum(), m_iRef);
//DEL   m_szTheClass.ReleaseBuffer();
//DEL 
//DEL   fprintf( g_errorLog, "\tC%sStep::addRef(), (#%d ), m_iRef=%u\n", m_szTheClass.GetBuffer(m_szTheClass.GetLength()), getNum(), m_iRef);
//DEL   m_szTheClass.ReleaseBuffer();
//DEL #endif//EXPOSE   
//DEL 
//DEL   return m_iRef;
//DEL }

//DEL ULONG CBaseStep::release()
//DEL { 
//DEL   ASSERT_VALID( this );
//DEL   ASSERT( 0 != m_iRef);
//DEL   m_iRef--;
//DEL #ifdef  EXPOSE      
//DEL   TRACE3("\tC%sStep::release(), (#%d ), m_iRef=%u\n", m_szTheClass.GetBuffer(m_szTheClass.GetLength()), getNum(), m_iRef);
//DEL   m_szTheClass.ReleaseBuffer();
//DEL 
//DEL   fprintf( g_errorLog, "\tC%sStep::release(), (#%d ), m_iRef=%u\n", m_szTheClass.GetBuffer(m_szTheClass.GetLength()), getNum(), m_iRef);
//DEL   m_szTheClass.ReleaseBuffer();
//DEL #endif//EXPOSE   
//DEL 
//DEL #ifdef GARBAGE_COLLECTION
//DEL   if (0 == m_iRef){ 
//DEL     delete this;
//DEL     return 0;
//DEL   }
//DEL   else if (0xFFFFFFFF == m_iRef){
//DEL     return 0xFFFFFFFF;// since this->m_iRef has been returned to the heap
//DEL   }
//DEL #endif //GARBAGE_COLLECTION
//DEL 
//DEL   return m_iRef;
//DEL }

//HRESULT CBaseStep::calc_boundingBox()
//{
//  return S_OK;
//}

// negate the topology
HRESULT CBaseStep::negate()
{
  return S_OK;
}

// make the entity topogically valid
/*
It look as if the only correct solution is to use the validate method.   
This will traverse the poly-loop of each face and each partner face 
(a parter face is one which share a common edge).
If the poly loop on one face has an traversal from vertex 1 to vertex 2, 
then its partner must have the traversal from vertex 2 to vertex 1.
*/
HRESULT CBaseStep::validate()
{
  return S_OK;
}

// useful for changing an [inner] face_bound into a face_outer_bound!
HRESULT CBaseStep::promote()
{
  return S_OK;
}


HRESULT CBaseStep::Rehash(int i)
{
  return S_OK;
}

bool CBaseStep::isSerialized( stepArchive &ar)
{
  if (!m_bSerialized){
    ar.setEntry( getNum());
  }
  return m_bSerialized;
}

//DEL ULONG CBaseStep::getRefCnt()
//DEL {    
//DEL   return m_iRef;  
//DEL }

bool CBaseStep::isSerialized(    )
{
  return m_bSerialized;
};
/*
HRESULT CBaseStep::backPtr(CBaseStep *&prBrep)
{
  prBrep = m_pBack;  
  return S_OK;
}
*/
//CBaseStep& CBaseStep::operator=(CBaseStep &rRhs)
//{
//  memcpy(this ,&rRhs, sizeof(this));
//  return *this;
//}


HRESULT CBaseStep::zeroTechnadrawPtr()
{
  if (NULL != m_pTechnadrawEntitites){
    ASSERT_VALID(m_pTechnadrawEntitites);
    CPtrPool* pPtrPool = dynamic_cast<CPtrPool*>(m_pTechnadrawEntitites);
    if (NULL!= pPtrPool) {
      for (int j=0; j< pPtrPool->m_aTechnadrawEntities.GetSize(); j++){
        CStepPtr* pThing = (CStepPtr* ) pPtrPool->m_aTechnadrawEntities.GetAt(j);
  /*
        if (pThing->m_aAdvancedStep.GetAt(i) == this){
          m_pTechnadrawEntitites->m_aAdvancedStep.RemoveAt(i);
        }
  */
        for (int i = 0 ; i < pThing->m_pFacetedPool->m_aStepEntities.GetSize(); i++) {
          if (pThing->m_pFacetedPool->m_aStepEntities.GetAt(i) == this){
            m_pTechnadrawEntitites->m_aStepEntities.RemoveAt(i);            
            return S_OK;
          }
          else {
    		    TRACE1("Disassociated Technadraw Entity %p.\n", m_pTechnadrawEntitites);
          }
        }
      }
    }
    else{
  		TRACE1("Invalid Technadraw Entity %p.\n", m_pTechnadrawEntitites);
    }
  }
  return E_FAIL;
}

CString& CBaseStep::getClassName()
{
  return m_szTheClass;
}

/*
// need to release buffer
char* CBaseStep::getClassNameBuffer()
{
  return this->m_szTheClass.GetBufferSetLength(m_szTheClass.GetLength()+1);
}
*/

HRESULT CBaseStep::decCount()
{
  m_iCount--;
  return S_OK;
}

// useful for changing the closed_shell into a open_shell 
HRESULT CBaseStep::demote()
{
  return S_OK;
}

//////////////////////////////////////////////////////////
// who  date      history
// wh   03/09/01  init
// wh   10/18/01  CrcPtrArray added
// wh   10/29/01  what to do about NULL entries in CBaseStep::writeNtuple's CPtrArray
// wh   12/01/01  remove unnecessary blanks to reduce file size
// wh   12/06/01  CBaseStep::operator=
// wh   12/07/01  CBaseStep::zeroTechnadrawPtr
//////////////////////////////////////////////////////////


