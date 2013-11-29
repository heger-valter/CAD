// agito.h: interface for the agito class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AGITO_H__5655E242_B231_41E0_995D_96419A879732__INCLUDED_)
#define AFX_AGITO_H__5655E242_B231_41E0_995D_96419A879732__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/**
 * <brief description>
 * A feature is the BREP transcription of a CSG part in the intersected part.
 *
 * A feature is a collection of connected face sets, 
 *   which is used to describe an indentation or protrusion on a model.  
 * The granularity is at the descretion of the mechanical engineer building the model.
 *
 * <directive>
 * <directive>
 * .
 * .
 * <directive>
 */

// deprecate it
class agitoFeature: public CPtrArray
{
public:
           agitoFeature();  // create an empty collection
  virtual ~agitoFeature();  // destructor for an empty collection
	HRESULT negate(void);     // method to perform the actual negation
	void* GetAt(int i) const; // method to return the i-th entry
	int Add( void *pConnected_face_setStep);
	HRESULT validate(void);
  bool m_bFeatureAdded ;    // flag to indicate if feature has already been added to the negative component collection

  // merge the CFS for a facetted collection
  HRESULT mergeCFSFacetted( int                       is, 
                            CConnected_face_setStep*  pShellStep);
  // remove the i-th CFS from a facetted collection
  HRESULT removeCFSFacetted( int                      is, // index of current shell being manuipulated
                             CConnected_face_setStep* pShellStep); // shell
private:
	bool m_bNegated;// flag to indicated if this has already been negated, to prevent recursion
};


/**
 * <brief description>
 *
 * A component [by Wilson] (or lump by Acis) is a collection of the 
 *  minimum number of features which would form a shell.
 *  for example, a block which has been split into two is described as one part consisting of two lumps
 * We need Components because a part can have components 
 *  which need to be on different [outer ]positive oriented shells.
 *  a Component is a piece of a part, geometrically disconnected from other Components on the same part.
 * A Components is a collection of one or more shells [which cannnot be separated physically 
 *   (obviously without cutting the surfaces)] describing a manifold.  
 * Components are necessary because sometimes a mechanical designer does not want to make them 
 *  as separte parts of an assembly.
 *
 * <directive>
 * <directive>
 * .
 * .
 * <directive>
 */

// deprecate it
class agitoComponent: public CPtrArray  
{
public:
	void* GetAt(int i) const;
           agitoComponent();
  virtual ~agitoComponent();
	HRESULT negate(void);
	int Add( void* pF);
};

//  a part is a collection of components
//  really should be called a solid_ModelStep, except that solid models are thought to not contain open shells!
class agitoPart: public CPtrArray
{
public:
	int Add( void* pF);
	void* GetAt(int i) const;
           agitoPart();
  virtual ~agitoPart();
	HRESULT negate(void);
  CCartesian_tranformation_operator_3dStep *m_pCartesian_tranformation_operator_3dStep;// in assemblies, parts can be positioned elsewhere in space!
  CCartesian_pointStepPtrArray* m_pCartesian_pointStepPtrArray ;// necessary to prevent the colesing of points from 2 different bodies
  CVertex_pointStepPtrArray* m_pVertex_pointStepPtrArray ;// necessary to prevent the colesing of points from 2 different bodies
};

// an assembly is a collection of parts
// deprecate it, and use STEP's CAssembly_component_usageStep
class agitoAssembly: public CPtrArray
{
public:
	int Add( void* pF);
	void* GetAt(int i) const;
           agitoAssembly();
  virtual ~agitoAssembly();
	HRESULT negate();
};

// wh 03/26/02  Several months ago, I was considering removing these collections, 
//                because they do not appear in the STEP specification explicitly.
//                The caveot is that they might be useful for ACIS-like representations, 
//                and when calulating oriented shells.


#endif // !defined(AFX_AGITO_H__5655E242_B231_41E0_995D_96419A879732__INCLUDED_)
