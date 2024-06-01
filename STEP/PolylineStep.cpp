// PolylineStep.cpp: implementation of the CPolylineStep class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#ifdef _WINDOWS 
#include "scribble.h"
#endif

#include "PolylineStep.h"
#include "stepArchive.h"
#include "pointStep.h"
#include "Cartesian_pointStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPolylineStep::CPolylineStep()
{
 nameClass("Polyline");
}

CPolylineStep::~CPolylineStep()
{

}

void CPolylineStep::Serialize(stepArchive &ar)
{
  try{
    if (!isSerialized()){
      setSerialized();
      writePre( ar);
      ar << "'',";

      CCartesian_pointStep* pCartesian_pointStep=NULL;
      ar << "(";
      for (int i = 0;i<points.GetSize()-2;i++){
        ar << "#";
        pCartesian_pointStep= (CCartesian_pointStep*)points.GetAt(i);
        ar<<pCartesian_pointStep->getNum();
        ar << ",";
      }
      ar << "#";
      pCartesian_pointStep= (CCartesian_pointStep*)points.GetAt(points.GetSize()-1);
      ar<<pCartesian_pointStep->getNum();
      ar << ")";
      writePost( ar);
      for (  i = 0;i<points.GetSize()-1;i++){
        pCartesian_pointStep= (CCartesian_pointStep*)points.GetAt(i);
        pCartesian_pointStep->Serialize( ar);
      }
    }
  }
  catch(...){
    ar << "\n/*Errors detected in CPolylineStep::Serialize #\n";
//  ar << getNum();
    ar <<   ", but continuing*/\n" ;    
    setSerialized();
  }
}

bool CPolylineStep::Add(CPoint p)
{
  CCartesian_pointStep* pCartesian_pointStep = new CCartesian_pointStep(NULL, p.x, p.y, 0.0e0, 2 );
  points.Add( pCartesian_pointStep);
  return false;
}

HRESULT CPolylineStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  return E_FAIL;
}
