// Geometric_Representation_contextStep.h: interface for the CGeometricRepresentation_contextStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GEOMETRICREPRESENTATION_CONTEXTSTEP_H__D02DC4C3_0C3B_11D5_BFEF_0004AC6EEF35__INCLUDED_)
#define AFX_GEOMETRICREPRESENTATION_CONTEXTSTEP_H__D02DC4C3_0C3B_11D5_BFEF_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Representation_contextStep.h"

class CGeometric_representation_contextStep : public CRepresentation_contextStep  
{
public:
	int m_iDim;
	bool writePre( stepArchive& ar);
	void Serialize( stepArchive &ar);
	CGeometric_representation_contextStep(CBaseStep*pIn);
	virtual ~CGeometric_representation_contextStep();
	bool writeDim(stepArchive &ar);
  HRESULT backPtr( CBaseStep*& prBrep);
};
//////////////////////////////////////////////////////////
// who  date      history

#endif // !defined(AFX_GEOMETRICREPRESENTATION_CONTEXTSTEP_H__D02DC4C3_0C3B_11D5_BFEF_0004AC6EEF35__INCLUDED_)
