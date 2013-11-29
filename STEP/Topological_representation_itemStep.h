// Topological_representation_itemStep.h: interface for the CTopological_representation_item class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOPOLOGICAL_REPRESENTATION_ITEM_H__9B2019D7_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_)
#define AFX_TOPOLOGICAL_REPRESENTATION_ITEM_H__9B2019D7_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Representation_itemStep.h"
class CStepArchive;

// These entities are used for defining any information where connectivity is fundamental.
class CTopological_representation_itemStep : public CRepresentation_itemStep
{
public:
	CTopological_representation_itemStep(CBaseStep*pIn);
	virtual ~CTopological_representation_itemStep();
	void Serialize( stepArchive &ar);
//CRepresentation_itemStep *pRepresentation_itemStep
  HRESULT backPtr( CBaseStep*& prBrep);
};


// deprecate it
template <int topologicalType> 
  class CDerivedTopological_representation_itemStep//( CBaseStep*pIn)
//      : public CTopological_representation_itemStep( NULL)
  {
  public:
    CDerivedTopological_representation_itemStep( CBaseStep*pIn);
  	virtual ~CDerivedTopological_representation_itemStep();
  	void Serialize( stepArchive &ar);
  };

//////////////////////////////////////////////////////////
// who  date      history

#endif // !defined(AFX_TOPOLOGICAL_REPRESENTATION_ITEM_H__9B2019D7_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_)
