// Connected_face_setStep.h: interface for the CConnected_face_setStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONNECTED_FACE_SETSTEP_H__9F9D4C75_0C2F_11D5_BFEF_0004AC6EEF35__INCLUDED_)
#define AFX_CONNECTED_FACE_SETSTEP_H__9F9D4C75_0C2F_11D5_BFEF_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCartesian_pointStepPtrArray;
class CVertex_pointStepPtrArray;
class CCartesian_tranformation_operator_3dStep;
#include "Topological_representation_itemStep.h"
#include "stepArchive.h"


class CConnected_face_setStep : public CTopological_representation_itemStep  
{
public:
	CConnected_face_setStep( 
                           CPtrArray *pFaceStepPtrArray, 
                           CRepresentation_itemStep *pRepresentation_itemStep =NULL);
	virtual ~CConnected_face_setStep();
	void Serialize( stepArchive &ar);

	CPtrArray* m_pCFS_faces;
protected:
  friend class step;
  friend class CClosed_shellStep;
  CRepresentation_itemStep *m_pRepresentation_itemStep;
public:
	HRESULT validate(void);
	HRESULT negate(void);
//bool calc_boundingBox(void);// remove this method, as it is being done in scribView.px
  // problem, move this to CRepresention_itemStep because there will be one for each model!

  // these variables define the mapping between agito and step, 
  // j= map_agito(i); the ith agito entry tells you where the j-th step entry exists
  // should not be a static // wh 6/7/01
  static CPtrArray map_part;// map the Tasdraw polygon (input) to the model
  static CPtrArray map_lump;// map the Tasdraw polygon (input) to the lump// not used
  static CPtrArray map_feature;// map the Tasdraw polygon (input) to the thing
  static CPtrArray map_shell;// map the Tasdraw polygon (input) to the shell
  static  // tbd remove the static 
         CPtrArray map_face;// map the Tasdraw polygon (input) to the surface on the shell
  // note that we don't know which shell this corresponds to 

  static CPtrArray map_surface;// map the Tasdraw polygon (input) to the surface on the shell
private:
  // indicate whether this entity has been negated!  If so, do not negate it twice
	bool m_bNegated;
public:
  HRESULT backPtr( CBaseStep*& prBrep);
	bool m_bOpen;
};

class CClosed_shellStep: public CConnected_face_setStep
{
  friend class step;
  CConnected_face_setStep* m_pConnected_face_setStep;
public:
  CClosed_shellStep( CConnected_face_setStep *pConnected_face_setStep, 
                     CPtrArray *pFace_surfaceStepPtrArray );
	virtual ~CClosed_shellStep();
public:   
	HRESULT demote(void);
	void fin();
  void Serialize( stepArchive &ar);
//private:
  HRESULT backPtr( CBaseStep*& prBrep);
private:
static	bool m_bProgressed;
};

// deprecate it
template <class T> 
class CShellStep: public CConnected_face_setStep
{
  friend class step;
  CConnected_face_setStep* m_pConnected_face_setStep;
public:
  CShellStep( CConnected_face_setStep *pConnected_face_setStep, 
                     CPtrArray *pFace_surfaceStepPtrArray );
	virtual ~CShellStep();
public:   
	void fin();
  void Serialize( stepArchive &ar);
};
/*
class Open{
public:
            Open(){};
	virtual  ~Open(){};
};

class Closed{
public:
            Closed(){};
	virtual  ~Closed(){};
};

class CShellStep<Open>
{
  friend class step;
  CConnected_face_setStep* m_pConnected_face_setStep;
public:
  CShellStep<Open>( CConnected_face_setStep *pConnected_face_setStep, 
                     CPtrArray *pFace_surfaceStepPtrArray );
	virtual ~CShellStep<Open>();
public:   
	void fin();
  void Serialize( stepArchive &ar);
};
*/
/*
class COpen_shellStep: public CConnected_face_setStep
{
  friend class step;
  CConnected_face_setStep* m_pConnected_face_setStep;
public:
  COpen_shellStep( CConnected_face_setStep *pConnected_face_setStep, 
                     CPtrArray *pFace_surfaceStepPtrArray );
	virtual ~COpen_shellStep();
public:   
	void fin();
  void Serialize( stepArchive &ar);
};
*/

//////////////////////////////////////////////////////////
// who  date      history
// wh   5/16/01   moved agitoFeature, part, assembly data structure here
// wh   6/19/01   should the hiarchy be assembly, part, lump, feature, shell [currently implementation]
//                                or    assembly, part, feature, lump, shell [my opionion after I change my mind]
//                Need to look this up in Jain's documentation.

#endif // !defined(AFX_CONNECTED_FACE_SETSTEP_H__9F9D4C75_0C2F_11D5_BFEF_0004AC6EEF35__INCLUDED_)
