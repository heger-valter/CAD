// Design_contextStep.h: interface for the CDesign_ContextStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CDesign_contextStep_H__9B2019DB_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_)
#define AFX_CDesign_contextStep_H__9B2019DB_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Product_definition_contextStep.h"

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

class CDesign_contextStep : 
  public CProduct_definition_contextStep  
{
public:
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
	CDesign_contextStep();
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
	virtual ~CDesign_contextStep();
  HRESULT backPtr( CBaseStep*& prBrep);
};

//////////////////////////////////////////////////////////
// who  date      history
// wh   11/15/01  added notes

#endif // !defined(AFX_CDesign_contextStep_H__9B2019DB_0C17_11D5_BFEF_0004AC6EEF35__INCLUDED_)
