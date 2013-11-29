// Representation_itemStep.h: interface for the CRepresentation_item class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REPRESENTATION_ITEM_H__9B2019DB_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_)
#define AFX_REPRESENTATION_ITEM_H__9B2019DB_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "baseStep.h"

// use CCDOC here!
/**
 * <brief description>
 *
 * Class from which all geometric and topological step classes are derived!
 * <directive>
 * <directive>
 * .
 * .
 * <directive>
 */

// this is really the first definitive step class and should have most of CBaseStep functionality
class CRepresentation_itemStep : 
  public CBaseStep  
{
public:
	CString name;
/**
 * write step data
 *
 * Serialize method writes out step data
 * <directive>
 * <directive>
 * .
 * .
 * <directive>
 */
	void Serialize(stepArchive& ar);
/**
 * default constuctor
 *
 * default constuctor
 * <directive>
 * <directive>
 * .
 * .
 * <directive>
 */
	CRepresentation_itemStep();
/**
 * default destuctor
 *
 * <full description>
 * <directive>
 * <directive>
 * .
 * .
 * <directive>
 */
	virtual ~CRepresentation_itemStep();
  HRESULT backPtr( CBaseStep*& prBrep);
};

//////////////////////////////////////////////////////////
// who  date      history
// wh   11/15/01  added notes

#endif // !defined(AFX_REPRESENTATION_ITEM_H__9B2019DB_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_)
