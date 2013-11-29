// TransformationMatrixIges.h: interface for the TransformationMatrixIges class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSFORMATIONMATRIXIGES_H__361AE502_9567_11D5_8CB5_00D00908C1A5__INCLUDED_)
#define AFX_TRANSFORMATIONMATRIXIGES_H__361AE502_9567_11D5_8CB5_00D00908C1A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseIges.h"
#include "transformationMatrix.h"

class CTransformationMatrixIges : public CBaseIges  
{
  transformationMatrix3d mat;
public:
	CTransformationMatrixIges();
	virtual ~CTransformationMatrixIges();

};

#endif // !defined(AFX_TRANSFORMATIONMATRIXIGES_H__361AE502_9567_11D5_8CB5_00D00908C1A5__INCLUDED_)
