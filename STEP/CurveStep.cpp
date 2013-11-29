// CurveStep.cpp: implementation of the CCurveStep class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "scribble.h"
#include "CurveStep.h"
#include "stepArchive.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCurveStep::CCurveStep()
:CGeometric_representation_itemStep(this)
{
 nameClass( "Curve");
}

CCurveStep::~CCurveStep()
{

}

HRESULT CCurveStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  else {
    return E_FAIL;
  }
}
void CCurveStep::Serialize(stepArchive &ar)
{
  try{
    if (!isSerialized()){
      setSerialized();
      writePre(ar);
      ar << "'',#";
//    ar << m_rPos.getNum();
      ar << ",#";
//    ar << m_rDir.getNum();
      writePost(ar);

//    m_rPos.Serialize( ar);
//    m_rDir.Serialize( ar);
    }
  }
  catch(...){
      setSerialized();
      ar << "\n/*Error caught in CCurveStep::Serialize!*/\n";
  }

}
