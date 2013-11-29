// VertexStep.cpp: implementation of the CVertexStep class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "scribble.h"
#include "VertexStep.h"
#include "Cartesian_pointStep.h"
#include "Cartesian_pointStepPtrArray.h"
#include "igesArchive.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//extern char gParameterDelimiterCharacter;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVertexStep::CVertexStep(CBaseStep * pFrom)
: CTopological_representation_itemStep(pFrom)
{
  nameClass("Vertex");
}

CVertexStep::~CVertexStep()
{

}

void CVertexStep::Serialize(stepArchive &ar)
{
  if (!isSerialized()){
    setSerialized();
    writeChild( ar );// no op here
    // all the work is done by CVertex_pointStep::Serialize();
  }
}

HRESULT CVertexStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  return E_FAIL;
}

CVertex_pointStep::CVertex_pointStep( CPointStep& r_vertex_geometry)
    : CVertexStep(this)
    , m_p_vertex_geometry ( &r_vertex_geometry)
{
  nameClass("VERTEX_POINT");    
#ifdef  EXPOSE      
  fprintf( g_errorLog, "CVertex_pointStep (#%d ), m_iRef=%u\n", getNum(), getRefCnt());
#endif//EXPOSE   
  r_vertex_geometry.addRef();
}

CVertex_pointStep::~CVertex_pointStep()
{
#ifdef  EXPOSE      
  fprintf( g_errorLog, "~CVertex_pointStep (#%d ), m_iRef=%u\n", getNum(), getRefCnt());
#endif//EXPOSE   
  m_p_vertex_geometry->release();
}

HRESULT CVertex_pointStep::backPtr(CBaseStep *&prBrep)
{ 
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  return E_FAIL;
}

void CVertex_pointStep::Serialize(stepArchive &ar)
{
  try{
    if (!isSerialized()){
      setSerialized();
      writePre(ar);
      ar << "'',#";
      ar << m_p_vertex_geometry->getNum();
      writePost(ar);
      m_p_vertex_geometry->m_pBack = this;
      m_p_vertex_geometry->Serialize( ar);
    }
  }
  catch(...){
      setSerialized();
      ar << "\nError caught in CVertex_pointStep::Serialize!\n";
  }
}


CVertex_pointStepPtrArray::CVertex_pointStepPtrArray(CCartesian_pointStepPtrArray& rCartesian_pointStepPtrArray)
  : CPtrArray()
,  m_rCartesian_pointStepPtrArray(rCartesian_pointStepPtrArray)
{
}

CVertex_pointStepPtrArray::~CVertex_pointStepPtrArray()
{
  bool bVertex_point = false;
  for (int iv = GetSize()-1;iv >= 0;iv--){
    CVertex_pointStep* pVertex_point = (CVertex_pointStep* )GetAt(iv);
    try{
      if (!bVertex_point){
        ASSERT_VALID( pVertex_point);
      }
#ifdef  EXPOSE      
      TRACE1("releasing CVertex_pointStepPtrArray[ %d ].\n", iv);
      fprintf( g_errorLog, "releasing CVertex_pointStepPtrArray[ %d ].\n", iv);
#endif//EXPOSE   
      pVertex_point->release();// some are being released too many times
    } catch (...) {
        bVertex_point = true;
#ifdef  EXPOSE      
  		char outbuf[512];
  		char inbuf[]  = "CVertex_pointStepPtrArray[ %d ] released too often.\n";
      sprintf( outbuf, inbuf, iv);
  		TRACE0( outbuf);
      fprintf( g_errorLog, outbuf);
#endif//EXPOSE   
    }
  }
}

int CVertex_pointStepPtrArray::SetAt(int nIndex, CVertex_pointStep* pNewElement)
{
  CVertex_pointStep* pPointElement = (CVertex_pointStep*) pNewElement;
  //int nNewIndex = nIndex;
  int nNewIndex = (int) m_rCartesian_pointStepPtrArray.m_hash.GetAt( nIndex);
  if (nNewIndex == nIndex) {
    CPtrArray::SetAt( nNewIndex, pNewElement);
    TRACE2("set CVertex_pointStepPtrArray[ %d ] is #%d.\n", nNewIndex, pNewElement->getNum());
#ifdef  EXPOSE      
    fprintf( g_errorLog, "set CVertex_pointStepPtrArray[ %d ] is #%d.\n", nNewIndex, pNewElement->getNum());
#endif//EXPOSE   
    pPointElement->addRef();//wh 9/7/01
//  pPointElement->addRef();// first timers need one extra //wh 9/8/01
  }
  else {
    ASSERT( 1 == pNewElement->getRefCnt() );
    delete pNewElement;//??
    pPointElement=(CVertex_pointStep* )CPtrArray::GetAt( nNewIndex );//wh 9/20/01
#ifdef  EXPOSE      
    fprintf( g_errorLog, "set CVertex_pointStepPtrArray[ %d ] is #%d.\n", nNewIndex, pPointElement->getNum());
#endif//EXPOSE   
    pPointElement->addRef();//wh 9/20/01
  }
  return nNewIndex;// wh 9/6/01
}

CVertex_pointStep* CVertex_pointStepPtrArray::GetAt(int nIndex)
{ 
  ASSERT( nIndex < m_rCartesian_pointStepPtrArray.m_hash.GetSize() );
  int nNewIndex = (int) m_rCartesian_pointStepPtrArray.m_hash.GetAt( nIndex);
  return (CVertex_pointStep*) CPtrArray::GetAt( nNewIndex);
}

CCartesian_pointStep* CVertex_pointStepPtrArray::find( CPointStep* pPoint)
{
  CCartesian_pointStep* pCartesian_pointStep = NULL;
  for (int i=0; i<GetSize();i++){
    CVertex_pointStep* pVp = (CVertex_pointStep*)GetAt(i);
    if (pPoint == pVp->m_p_vertex_geometry){
      int nNewIndex = (int) m_rCartesian_pointStepPtrArray.m_hash.GetAt( i);
      pCartesian_pointStep = m_rCartesian_pointStepPtrArray.GetAt( i);
      return pCartesian_pointStep;    
    }
  }
  return NULL;
}
  
//////////////////////////////////////////////////////////
// who  date      history
// wh   09/17/01  assert only once
// wh   10/12/01  find
// wh   12/05/01  CVertexStep::operator= is not allowed because of too many problems

