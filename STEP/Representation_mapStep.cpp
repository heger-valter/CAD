// Representation_mapStep.cpp: implementation of the CRepresentation_mapStep class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _WINDOWS
#include "stdafx.h"
#endif

#ifdef _WINDOWS 
#include "scribble.h"
#endif

#include "Representation_mapStep.h"
#include "Mapped_itemStep.h"
#include "Representation_itemStep.h"
#include "RepresentationStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRepresentation_mapStep::CRepresentation_mapStep()
{
  nameClass("Representation_map");
}

CRepresentation_mapStep::~CRepresentation_mapStep()
{

}

void CRepresentation_mapStep::Serialize(stepArchive &ar)
{
  try{
    if (!isSerialized()){
      setSerialized();
      writePre(ar);
      ar << "'',";
      if (NULL != m_pMapping_origin) {
        ar << "#";
        ar << m_pMapping_origin->getNum();
      } else {
        ar << "$";
      }
      ar << ",";
      if (NULL != m_pMapped_representation) {
        ar << "#";
        ar << m_pMapped_representation->getNum();
      } else {
        ar << "$";
      }
      ar << ",";
      if ( 0 < aMap_usage.GetSize() ) {
        if (NULL != aMap_usage.GetAt(0)) {
          ar << "(#";
          ar << this->aMap_usage.GetAt(0)->getNum();
        } else {
          ar << "$";
        }
        for (int i = 1; i < aMap_usage.GetSize(); i++) { 
          if (NULL != aMap_usage.GetAt(i)) {
            ar << ",#";
            ar << this->aMap_usage.GetAt(i)->getNum();
          }
        }
        ar << ")";
      } else {
        ar << "$";
      }
      writePost(ar);

      m_pMapped_representation->Serialize( ar);
      m_pMapping_origin->Serialize( ar);
      for (int i = 0; i < aMap_usage.GetSize(); i++) { 
        aMap_usage.GetAt(i)->Serialize( ar);
      }
    }
  }
  catch(...){
    ar << "\n/*Errors detected in ::Serialize #\n";
//  ar << getNum();
    ar <<   ", but continuing*/\n" ;    
  }
}

