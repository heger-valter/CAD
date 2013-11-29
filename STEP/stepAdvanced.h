// stepAdvanced.h: interface for the stepAdvanced class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STEPADVANCED1_H__9D153571_93D8_48D9_A217_914B66FBB454__INCLUDED_)
#define AFX_STEPADVANCED1_H__9D153571_93D8_48D9_A217_914B66FBB454__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StepSer.h"

class stepAdvanced : public step  
{
public:
	stepAdvanced();
	virtual ~stepAdvanced();

	HRESULT buildShellsAdvanced( FILE*                              stream, 
                               stepArchive&                       ar, 
                               CClosed_shellStep *                pClosed_shellStep , 
                               CRepresentationStep*&              pRepresentationStep, 
                               surfaceModelSelect                 lSurfaceModelSelect,
                               CPtrArray*&                        pFace_surfaceStepPtrArray);

	HRESULT buildFacesAdvanced( FILE *                              stream, 
                              stepArchive &                       ar, 
                              CRepresentationStep*&               pRepresentationStep, 
                              CCartesian_pointStepPtrArray*&      pCartesian_pointStepPtrArray  
                            , surfaceModelSelect                lSurfaceModelSelect
                            , CPtrArray*&                       pEdge_loopStepPtrArray);

	HRESULT buildLoopsAdvanced( FILE *                          stream, 
                              stepArchive &                   ar, 
                              CRepresentationStep*&           pRepresentationStep
                             , surfaceModelSelect             lSurfaceModelSelect 
                             , CCartesian_pointStepPtrArray*& pCartesian_pointStepPtrArray  
                             , CPtrArray*&                    pEdge_loopStepPtrArray);

	HRESULT buildPathAdvanced( FILE *                         stream, 
                             stepArchive &                  ar, 
                             CRepresentationStep*&          pRepresentationStep,
                             CVertex_pointStepPtrArray*&    pVertex_pointStepPtrArray,
                             CCartesian_pointStepPtrArray* &pCartesian_pointStepPtrArray,
                             surfaceModelSelect             lSurfaceModelSelect,
                             CPtrArray*&                    pPathStepPtrArray );

	HRESULT buildEdgeAdvanced( FILE *                           stream, 
                             stepArchive &                    ar, 
                             CRepresentationStep*&            pRepresentationStep,
                             CVertex_pointStepPtrArray*&      pVertex_pointStepPtrArray,
                             CCartesian_pointStepPtrArray*& pCartesian_pointStepPtrArray,
                             surfaceModelSelect             lSurfaceModelSelect  );
  HRESULT buildArcAdvanced( FILE*                          stream, 
                                stepArchive&                   ar, 
                                CRepresentationStep*&          pRepresentationStep,
                                CVertex_pointStepPtrArray*&    pVertex_pointStepPtrArray ,
                                surfaceModelSelect             lSurfaceModelSelect
                              , CEdge_loopStep *               pEdge_loopStep
                              , CCircleStepPtrArray*           pCircleStepPtrArray
                              , CPtrArray*                     pEdge_curveArray
                              , CSurface*                      pSurface);

  HRESULT buildLineAdvanced( FILE*                          stream, 
                                 stepArchive&                   ar, 
                                 CRepresentationStep*&          pRepresentationStep,
                                 CVertex_pointStepPtrArray*&    pVertex_pointStepPtrArray ,
                                 surfaceModelSelect             lSurfaceModelSelect
                               ,  CEdge_loopStep * pEdge_loopStep
                               ,  CLineStepPtrArray *pLineStepPtrArray
                               ,  CPtrArray*pEdge_curveArray
                               , CSurface* pSurface);

  HRESULT buildVerticesAdvanced( FILE*                 stream, 
                                 stepArchive &         ar, 
                                 surfaceModelSelect    lSurfaceModelSelect , 
                                 CRepresentationStep*& pRepresentationStep);

};

#endif // !defined(AFX_STEPADVANCED1_H__9D153571_93D8_48D9_A217_914B66FBB454__INCLUDED_)
