// Solid_modelStep.h: interface for the CSolid_model class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOLID_MODEL_H__9B2019DA_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_)
#define AFX_SOLID_MODEL_H__9B2019DA_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Geometric_representation_itemStep.h"
class CSolid_modelStep : public CGeometric_representation_itemStep  
{
public:
	bool CountReset(void );
	void Serialize( stepArchive &ar);
	CSolid_modelStep(CBaseStep*pIn);
	virtual ~CSolid_modelStep();
  HRESULT backPtr( CBaseStep*& prBrep);

};
//////////////////////////////////////////////////////////
// who  date      history

#endif // !defined(AFX_SOLID_MODEL_H__9B2019DA_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_)
