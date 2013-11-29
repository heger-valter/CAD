#if !defined(AFX_STEPSER_H__F3ABC471_0EA0_11D5_BFF1_0004AC6EEF35__INCLUDED_)
#define AFX_STEPSER_H__F3ABC471_0EA0_11D5_BFF1_0004AC6EEF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CScribView ;
class stepArchive;//wh 02/21/01
class CRepresentationStep;
class CFaceted_brep_shape_representationStep;
class CAdvanced_brep_shape_representationStep;
class CClosed_shellStep ;
class CCartesian_pointStepPtrArray;
class CPtrArray;
class CrcPtrArray;
class CClosed_shellStep;
class CRepresentationStep;
class CVertex_pointStepPtrArray;
class COriented_edgeStepPtrArray;
class CConnected_face_setStep;
class CFace_surfaceStep;
class CAdvanced_faceStep;
class CPoly_loopStep;
class CLineStep;
class CPlaneStep;
class agitoFeature;
class agitoPart;
class agitoComponent;
class agitoAssembly;
class CVectorStep;
class CDirectionStep;
class agitoPtrArray;
class CVertex_pointStep;
class CLineStepPtrArray;
class CEdge_loopStep;
class CCircleStepPtrArray;
class CElementary_surfaceStep;
class CAxis2_placement_3dStep;

class CPoly_loopStepEx;
class CEdge_loopStep;
class CEdge_loopStepEx;

enum boundsIntersectBounds;
enum intersectionType ;

// as specified in ISO-10303-21
const unsigned int STEP_LINE_LENGTH = 72;


#include "transformationMatrix.h"
#include "agitoPtrArray.h"

//template< class CThingInts, class int > class CArray : public CObject;
#define thingList CPtrArray

//#include "agitoPtrArray.h"

const int step_zero = 0;
// class which handles all the conversion from Technadraw to STEP
class step
{
static  CFaceted_brep_shape_representationStep  *m_pFaceted_brep_shape_representationStep;// really the faceted representation
static  CAdvanced_brep_shape_representationStep *m_pAdvanced_brep_shape_representationStep;
  agitoPtrArray& m_ptrArrayAgito;
  CRepresentationStep  *m_pSelectRepresentationStep;
public:
	HRESULT ncreatestep();
  step(CScribView *pOuter);
	step( CScribView *pOuter
      , surfaceModelSelect lSurfaceModelSelect);
  virtual ~step();
  HRESULT stepClasses( bool bWriteFile);
  CScribView *m_pScribView;

  friend class CScribView;
//inline	
  CScribView* GetScribView(){
            return m_pScribView;
          };
	bool m_bWriteFile;
private:
	void init();
	void finFac();
	void finAdv();
	HRESULT boundsContainBoundsFaceted( CFace_surfaceStep*      pFace_surfaceStepOnPosFeature, // positive features's face
                                      boundsIntersectBounds&  rBoundsXbounds,
                                      CPoly_loopStep*         pPolyIntersectionPoints );// insersection point on 
                                                                          //  polyon of pFace_surfaceStepOnPosFeature

	HRESULT thingXthingBBFaceted( agitoAssembly*  pAssembly,// collection of all parts
                                    int             itNeg,       // index of negative CThing
                                    CThing*         pNegThing ,// the negative features whose faces will be 
                                    // intersected against all faces in the assembly
                                    CPtrArray*&     pFace_surfaceStepPtrArray, 
                                    CClosed_shellStep* pShell
                                  , CCartesian_pointStepPtrArray*& pCartesian_pointStepPtrArray
                                //, thingList&          rNegThingsList
                                );
//inline 
	HRESULT connectFacesFaceted( agitoAssembly* pAssembly, 
                               CPtrArray*& pFace_surfaceStepPtrArray );

	HRESULT buildShellsFaceted( FILE*           stream, 
                               stepArchive&ar, 
                               CPtrArray*& pPoly_loopPtrArray, 
                               CRepresentationStep*& pRepresentationStep, 
                               surfaceModelSelect       lSurfaceModelSelect,
                               CPtrArray*& pFace_surfaceStepPtrArray
                             , CCartesian_pointStepPtrArray*& pCartesian_pointStepPtrArray
                                //, thingList&          rNegThingsList
                                );

	HRESULT buildFacesFaceted( FILE *stream, 
                              stepArchive &ar, 
                              CPtrArray*& pPoly_loopPtrArray, 
                              CRepresentationStep*& pRepresentationStep, 
                              CCartesian_pointStepPtrArray*& pCartesian_pointStepPtrArray  
                              , surfaceModelSelect       lSurfaceModelSelect
                              //, CVertex_pointStepPtrArray&rVertex_pointStepPtrArray
                             //, thingList&          rNegThingsList 
                             );

	HRESULT buildLoopsFaceted( FILE *stream, 
                              stepArchive &ar, 
                              CPtrArray*& pPoly_loopPtrArray, 
                              CRepresentationStep*& pRepresentationStep
                             , surfaceModelSelect       lSurfaceModelSelect 
                             ,CCartesian_pointStepPtrArray*& pCartesian_pointStepPtrArray
                            //,CVertex_pointStepPtrArray&rVertex_pointStepPtrArray
                            //, thingList&          rNegThingsList
                            );
	HRESULT buildPathFaceted( FILE *stream, 
                     stepArchive &ar, 
                     CRepresentationStep*& pRepresentationStep,
                     CVertex_pointStepPtrArray*& pVertex_pointStepPtrArray,
                     CCartesian_pointStepPtrArray* &pCartesian_pointStepPtrArray,
                     surfaceModelSelect       lSurfaceModelSelect );

	HRESULT prePathFaceted( FILE *stream, 
                     stepArchive &ar, 
                     CRepresentationStep*& pRepresentationStep,
                     CVertex_pointStepPtrArray*& pVertex_pointStepPtrArray,
                     CCartesian_pointStepPtrArray* &pCartesian_pointStepPtrArray,
                     surfaceModelSelect       lSurfaceModelSelect 
                     
                            );

  HRESULT buildEdgeFaceted(  FILE *stream, 
                             stepArchive &ar, 
                             CRepresentationStep*& pRepresentationStep,
                             CVertex_pointStepPtrArray*& pVertex_pointStepPtrArray,
                             CCartesian_pointStepPtrArray* &pCartesian_pointStepPtrArray,
                             surfaceModelSelect       lSurfaceModelSelect  );

	HRESULT buildVerticesFaceted( FILE*                 stream, 
                                stepArchive &         ar, 
                                surfaceModelSelect    lSurfaceModelSelect , 
                                CRepresentationStep*& pRepresentationStep);

	HRESULT preVerticesFaceted( FILE*                 stream, 
                              stepArchive &         ar, 
                              surfaceModelSelect    lSurfaceModelSelect , 
                              CRepresentationStep*& pRepresentationStep                            
                            );

	HRESULT buildShellsAdvanced( FILE*                              stream, 
                               stepArchive&                       ar, 
                               CRepresentationStep*&              pRepresentationStep, 
                               surfaceModelSelect                 lSurfaceModelSelect,
                               CPtrArray*&                        pFace_surfaceStepPtrArray
                             , CCartesian_pointStepPtrArray*&     pCartesian_pointStepPtrArray 
                             );

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
  HRESULT buildArcOnFlatAdvanced( FILE*                          stream, 
                                stepArchive&                   ar, 
                                CRepresentationStep*&          pRepresentationStep,
                                CVertex_pointStepPtrArray*&    pVertex_pointStepPtrArray ,
                                surfaceModelSelect             lSurfaceModelSelect
                              , CEdge_loopStep *               pEdge_loopStep
                              , CCircleStepPtrArray*           pCircleStepPtrArray
                              , CPtrArray*                     pEdge_curveArray
                              , CSurface*                      pSurface);

  HRESULT buildArcOnCylinderAdvanced( FILE*                          stream, 
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

  HRESULT TechDraw2Step( FILE *stream, 
                         stepArchive &ar, 
                         surfaceModelSelect lSurfaceModelSelect 
                        );

	HRESULT writeStepData( FILE* pStream, 
                         surfaceModelSelect lSurfaceModelSelect );

	HRESULT onFileSaveStep( char* dlgpathname, 
                          surfaceModelSelect lSurfaceModelSelect                         
                          );

  friend class CBaseStep;
  static agitoPtrArray m_ptrArrayFacAgito;  // holds onto all of the Step classes for garbage collection later, entry 0 holds the header!
  static agitoPtrArray m_ptrArrayAdvAgito;  // holds onto all of the Step classes for garbage collection later, entry 0 holds the header!

  HRESULT condenseArray(void);

  //Notify(char*pC){m_pScribView->Notify(char* pC)};// pass on to outer // aggragation

  HRESULT presentation(stepArchive &                    ar);

  HRESULT supressLayersFaceted( CPtrArray*&               pPoly_loopPtrArray,                             
                                CRepresentationStep*&     pRepresentationStep ,                             
                                surfaceModelSelect        lSurfaceModelSelect,                            
                                CPtrArray*&               pFace_surfaceStepPtrArray, 
                                agitoAssembly*            pAssembly  );

  HRESULT buildFeaturesFaceted(void);

  HRESULT buildPartsFaceted(void);

  HRESULT buildAssembliesFaceted( stepArchive&          ar, 
                                  agitoAssembly*        pAssembly,
                                  CRepresentationStep *&pRepresentationStep );
  HRESULT preAssembliesFaceted(   stepArchive&          ar, 
                                      agitoAssembly*        pAssembly,
                                      CRepresentationStep *&pRepresentationStep );

  HRESULT addEulerFaceted(  agitoAssembly* pAssembly, 
                            agitoComponent& raNegativeComponents);

  // worries about coincidence of edges
  HRESULT subtractBraidFaceted(  agitoAssembly* pAssembly, 
                                agitoComponent& raNegativeComponents);

  HRESULT sortFeaturesFaceted( agitoAssembly* pAssembly,
                               agitoComponent& raNegativeComponents,
                               CPtrArray*& pFace_surfaceStepPtrArray
                               //,CVertex_pointStepPtrArray*    pVertex_pointStepPtrArray
                               );

//inline 
  HRESULT findCoincidentSurfacesFaceted( int is, 
                                         int it, 
                                         CPtrArray* pFace_surfaceStepPtrArray
                                     //, CVertex_pointStepPtrArray*    pVertex_pointStepPtrArray
                                       );

//inline 
  HRESULT surfXsurfFaceted( agitoAssembly* pAssembly,// collection of all parts
                            int        it,       // index of negative CThing
                            CThing* pNegThing,
                            CPtrArray*& pFace_surfaceStepPtrArray  , 
                            CPolygon *pPolygonOnPosFeature, 
                            int ipp , 
                            CClosed_shellStep* pShell
                          , CCartesian_pointStepPtrArray*& pCartesian_pointStepPtrArray
                        //, thingList&          rNegThingsList
                          );

//inline 
  HRESULT findNegFeatureFaceted( agitoAssembly* pAssembly,
                                 agitoComponent& aNegativeComponents,
                                 CPtrArray*& pFace_surfaceStepPtrArray
                               , CCartesian_pointStepPtrArray*& pCartesian_pointStepPtrArray
                               );

//inline 
  HRESULT polyXpolyFaceted( CFace_surfaceStep *pFace_surfaceStepOutside, 
                            CFace_surfaceStep *pFace_surfaceStepInside,
                            CrcPtrArray* pXPoints 
                          );

//inline 
  HRESULT edgeXedgeFaceted( int              ivm1, 
                            int              iv, 
                            CPoly_loopStep*  pPLoop, 
                            double&          dStartParam,
                            double&          dEndParam    ,
                            CLineStep*       pLine0 , 
                            CrcPtrArray*       pXPoints, CCartesian_pointStepPtrArray*pCartesian_pointStepPtrArray
                          );

//inline 
  HRESULT lineEdgeGlanceFaceted( int         ivm1, 
                                 int              iv, 
                                 CPoly_loopStep*  pPLoop, 
                                 double&          dStartParam,
                                 double&          dEndParam    ,
                                 CLineStep*       pLine0 , 
                                 CrcPtrArray*       pXPoints,     // collection of intersection points on polygon
                                 intersectionType& intersection0, 
                                 intersectionType& intersection1);

//inline 
  HRESULT faceXedgeFaceted( CFace_surfaceStep *pFace_surfaceStepOnPosFeature,
                            CPoly_loopStep*  pPLoop,       // loop corresponding to neg feature
                            double&          dStartParam,  // start parameter on line0
                            double&          dEndParam,    // end parameter on line0
                            CrcPtrArray*       pPolyIntersectionPoints,     // collection of intersection points on polygon
                            unsigned int &   startIndex, 
                            unsigned int &   endIndex
                          , CCartesian_pointStepPtrArray*& pCartesian_pointStepPtrArray
                          );     // collection of intersection points on polygon

//inline 
  HRESULT faceXfaceFaceted( CFace_surfaceStep *pFace_surfaceStepOnPosFeature, 
                            CFace_surfaceStep *pFace_surfaceStepOnNegFeature,
                            CPoly_loopStepEx*    pPolyIntersectionPoints , 
                            bool &             bBackward, 
                            CPtrArray*&         pFace_surfaceStepPtrArray
                          , CCartesian_pointStepPtrArray*& pCartesian_pointStepPtrArray
                        //, thingList&          rNegThingsList
                          );// intersection point on polyon of 

//inline 
  HRESULT boundsXboundsFaceted( CFace_surfaceStep *     pFace_surfaceStepOnPosFeature, // positive features's face
                                boundsIntersectBounds&  rBoundsXbounds,
                                CrcPtrArray*            pPolyIntersectionPoints );// insersection point on polyon of pFace_surfaceStepOnPosFeature

//inline 
  HRESULT polyXpolyBBFaceted( int               p1, 
                              int               p2,                                 
                              CPoly_loopStepEx*   pPolyIntersectionPoints , // insersection point on polyon of pFace_surfaceStepOnPosFeature
                              bool &            bBackward, 
                              CPtrArray*&       pFace_surfaceStepPtrArray ,             
                              bool&             bIntersect
                            , CClosed_shellStep* pShell
                            , CCartesian_pointStepPtrArray*& pCartesian_pointStepPtrArray
                          //, thingList&          rNegThingsList
                            );
//inline 
  HRESULT buildLeftFaceted(     int&                          iv, 
                                CPolygon*&                    pPolygon, 
                                CCartesian_pointStepPtrArray* pCartesian_pointStepPtrArray, 
                                CCartesian_pointStep*&        pCartesian_pointStep1, 
                                stepArchive&                  ar,
                                CPolygon*&                    pPolygonZ, 
                                CDirectionStep*&              pRef_dir, 
                                int                           nv, 
                                CDirectionStep*&              pAxis);
//inline 
  HRESULT buildPoly_loopFaceted(
                                   int&                          iv,
                                    CVertex_pointStepPtrArray*&   pVertex_pointStepPtrArray,
                                    CPolygon*&                    pPolygon,
                                    CCartesian_pointStepPtrArray* pCartesian_pointStepPtrArray,
                                    int&                          ip,
                                    CPtrArray*&                   pPoly_loopPtrArray,
                                    CVertex_pointStep*&           pVertex_pointStep0 ,
                                    CVertex_pointStep*&           pVertex_pointStep1,
                                    CPoly_loopStep*&              pPoly_loopStep);

  HRESULT preShellsFaceted( FILE*                 stream, 
                            stepArchive &         ar,
                            CPtrArray*&           pPoly_loopPtrArray, 
                            CRepresentationStep*& pRepresentationStep , 
                            surfaceModelSelect    lSurfaceModelSelect,
                            CPtrArray*&           pFace_surfaceStepPtrArray
                          , CCartesian_pointStepPtrArray*& pCartesian_pointStepPtrArray
                          );

  HRESULT preFacesFaceted( FILE*                          stream, 
                           stepArchive&                   ar, 
                           CPtrArray*&                    pPoly_loopPtrArray, 
                           CRepresentationStep*&          pRepresentationStep,
                           CCartesian_pointStepPtrArray*& pCartesian_pointStepPtrArray  
                         , surfaceModelSelect             lSurfaceModelSelect                                 
                         );

  HRESULT buildSeamEdgeOnCylinderAdvanced(
                                FILE*                          stream, 
                                stepArchive&                   ar, 
                                CRepresentationStep*&          pRepresentationStep,
                                CVertex_pointStepPtrArray*&    pVertex_pointStepPtrArray ,
                                surfaceModelSelect             lSurfaceModelSelect
                              , CEdge_loopStep *               pEdge_loopStep
                              , CLineStepPtrArray *            pLineStepPtrArray
                              , CPtrArray*                     pEdge_curveArray
                              , CSurface*                      pSurface
                              , CEdge_loopStep*                pEdge_loopStep1 
                              , CEdge_loopStep*                pEdge_loopStep0 // on endcap 0
                              );

  HRESULT buildSeam( CVertex_pointStepPtrArray*&    pVertex_pointStepPtrArray 
                   , const int ivm1 
                   , const int iv 
                   , CLineStepPtrArray *            pLineStepPtrArray
                   , CEdge_loopStep *               pEdge_loopStep    
                   , CPtrArray*                     pEdge_curveArray
                   );

  HRESULT splitEndcap0( CVertex_pointStepPtrArray*&    pVertex_pointStepPtrArray 
                      , surfaceModelSelect             lSurfaceModelSelect
                      , CEdge_loopStep *               pEdge_loopStep1
                      , CLineStepPtrArray *            pLineStepPtrArray
                      , CPtrArray*                     pEdge_curveArray
                      , CSurface*                      pCylinder
                      , CVertex_pointStep*             pVertex_pointStep0
                      , CEdge_loopStep*                pEdge_loopStep0 // on endcap 0
                      , CEdge_loopStep*                pEdge_loopStepCylinder
                      );

  HRESULT findCylinderPositionFromCircle(
                                          CPtrArray*& pEdge_loopStepPtrArray
                                        , CElementary_surfaceStep* pElementary_surfaceStep
                                        , CAxis2_placement_3dStep *pAxis2_Placement_3dStep
                                        );

  HRESULT findCirclesAxisRef_dirFromEndcapPlane(
                                          CPtrArray*& pEdge_loopStepPtrArray
                                        , CElementary_surfaceStep* pElementary_surfaceStep
                                        , CAxis2_placement_3dStep *pAxis2_Placement_3dStep
                                        );

  HRESULT intersectNegFeatureFaceted(     agitoAssembly*                 pAssembly
                                         , CPtrArray*&                    pFace_surfaceStepPtrArray
                                         , CCartesian_pointStepPtrArray*& pCartesian_pointStepPtrArray 
                                         );

  HRESULT intersectionEdgePartner_Add(   CCartesian_pointStep* pPoint );

  HRESULT faceXedgeFacetedCoincident( CPlaneStep*           pPlaneStepOnPosFeature,
                                      CPoly_loopStep*       pPLoopN,       // loop corresponding to neg feature
                                      CrcPtrArray*          pLoopIntersectionPoints,     // collection of intersection 
                                                                                      //  points on polygon
                                      unsigned int &        riStartIndex, // index of startpoint
                                      unsigned int &        riEndIndex   // index of endpoint
                                    , CCartesian_pointStep* pCartesian_pointStep0 
                                    , CCartesian_pointStep* pCartesian_pointStep1 
                                    , int&                  iInsertionIndex 
                                    );

  HRESULT *pShellsFaceted( FILE*                 stream, 
                           stepArchive &         ar,
                           CPtrArray*&           pPoly_loopPtrArray, 
                           CRepresentationStep*& pRepresentationStep , 
                           surfaceModelSelect    lSurfaceModelSelect,
                           CPtrArray*&           pFace_surfaceStepPtrArray
                         , CCartesian_pointStepPtrArray*& pCartesian_pointStepPtrArray
                         );


	HRESULT buildAssembliesAdvanced( 
                                   FILE*                  stream, 
                                   stepArchive&           ar,
                                   agitoAssembly*         pAssembly,
                                   CRepresentationStep*&  pRepresentationStep , 
                                   surfaceModelSelect     lSurfaceModelSelect,
                                   CPtrArray*&            pAdvanced_faceStepPtrArray
                                 );

  HRESULT findNegFeatureAdvanced( agitoAssembly* pAssembly// 
                                , agitoComponent&     aNegativeComponents
                                , CPtrArray*&    pFace_surfaceStepPtrArray
                                , CCartesian_pointStepPtrArray*& pCartesian_pointStepPtrArray 
                                );

  HRESULT connectFacesAdvanced( agitoAssembly* pAssembly
                              , CPtrArray*& pFace_surfaceStepPtrArray 
                              );

  HRESULT intersectNegFeatureAdvanced( agitoAssembly*                 pAssembly
                                     , CPtrArray*&                    pFace_surfaceStepPtrArray
                                     , CCartesian_pointStepPtrArray*& pCartesian_pointStepPtrArray 
                                     );

  HRESULT polyXpolyBBAdvanced( int ipp, // index of positive polygon
                               int ipn, // index of negative polygon                                
                               CEdge_loopStepEx* pPolyIntersectionPoints , // insersection point on polyon of 
                                                                          //  pFace_surfaceStepOnPosFeature
                               bool & bGapsEncountered, // is the loop gaps_in
                               CPtrArray*&     pFace_surfaceStepPtrArray,// collection of all face_surfaces             
                               bool& bIntersect,
                               CClosed_shellStep* pShell
                             , CCartesian_pointStepPtrArray*& pCartesian_pointStepPtrArray
                            //, thingList&          rNegThingsList
                             );// do the bb intersect

  HRESULT faceXedgeAdvanced( CAdvanced_faceStep *pFace_surfaceStepOnPosFeature,
                                CEdge_loopStep*    pPLoopN,       // loop corresponding to neg feature
                                double&            dStartParam,  // start parameter on line0
                                double&            dEndParam,    // end parameter on line0
                                CrcPtrArray*       pLoopIntersectionPoints,     // collection of intersection 
                                //points on polygon
                                unsigned int &     riStartIndex, // index of startpoint
                                unsigned int &     riEndIndex   // index of endpoint
                              , CCartesian_pointStepPtrArray*& pCartesian_pointStepPtrArray
                              );

  HRESULT faceXfaceAdvanced( CAdvanced_faceStep *             pFace_surfaceStepOnPosFeature, // positive features's face
                                CAdvanced_faceStep *             pFace_surfaceStepOnNegFeature, // neg features face
                                CEdge_loopStepEx&               polyIntersectionPoints ,   // intersection point on polyon 
                                                                                            //  of pFace_surfaceStepOnPosFeature
                                bool &                          bGapsEncountered, 
                                CPtrArray*&                     pFace_surfaceStepPtrArray
                              , CCartesian_pointStepPtrArray*&  pCartesian_pointStepPtrArray
                            //, thingList&                      rNegThingsList 
                              );

  HRESULT thingXthingBBAdvanced( agitoAssembly*                  pAssembly,// collection of all parts
                                    int                             itn,       // index of negative CThing
                                    CThing*                         pNegThing ,// the negative features whose faces will be 
                                    // intersected against all faces in the assembly
                                    CPtrArray*&                     pFace_surfaceStepPtrArray,
                                    CClosed_shellStep*              pShell
                                  , CCartesian_pointStepPtrArray*&  pCartesian_pointStepPtrArray
                                  //, thingList&          rNegThingsList
                                  );

  HRESULT boundsContainBoundsAdvanced( CAdvanced_faceStep*      pFace_surfaceStepOnPosFeature, // positive features's face
                                          boundsIntersectBounds&  rBoundsXbounds,
                                          CEdge_loopStep*         pInner_boundPoints );// tested for [inner]bounds

  HRESULT surfXsurfAdvanced( agitoAssembly*                 pAssembly// collection of all parts
                              , int                            itNeg       // index of negative CThing
                              , CThing*                        pNegThing // the negative features whose faces will be 
                                // intersected against all faces in the assembly
                              ,  CPtrArray*&                   pFace_surfaceStepPtrArray 
                              ,  CPolygon*                     pPolygonOnPosFeature// the collection of all the 
                                //face_surfaces in the assembly
                              , int                            ipp    
                              , CClosed_shellStep*             pShell
                              , CCartesian_pointStepPtrArray*& pCartesian_pointStepPtrArray
                            //, thingList&                     rNegThingsList
                              );

  HRESULT boundsXboundsAdvanced( CAdvanced_faceStep*      pFace_surfaceStepOnPosFeature, // positive features's face
                                 boundsIntersectBounds&  rBoundsXbounds,
                                 CrcPtrArray*            pPolyIntersectionPoints // intersection point on 
                                                                                 //  polygon of pFace_surfaceStepOnPosFeature
                               );

  HRESULT lineEdgeGlanceAdvanced( int               ivm1, 
                                  int               iv, 
                                  CEdge_loopStep*   pPLoop, 
                                  double&           dStartParam,
                                  double&           dEndParam    ,
                                  CLineStep*        pLine0 , 
                                  CrcPtrArray*      pXPoints,     // collection of intersection points on polygon
                                  intersectionType& intersection0, 
                                  intersectionType& intersection1);

  HRESULT buildProductStructureAdvanced( 
                                 FILE*                  stream, 
                                 stepArchive&           ar,
                                 agitoAssembly*         pAssembly,
                                 CRepresentationStep*&  pRepresentationStep , 
                                 surfaceModelSelect     lSurfaceModelSelect,
                                 CPtrArray*&            pAdvanced_faceStepPtrArray);

};//class step


#endif // !defined(AFX_STEPSER_H__F3ABC471_0EA0_11D5_BFF1_0004AC6EEF35__INCLUDED_)
