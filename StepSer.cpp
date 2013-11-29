
// StepSer.cpp (maybe rename to step.cpp): implementation of the step class.
//
//////////////////////////////////////////////////////////////////////
//
//  class: step is responsible for creating step ISO-10303-21 output from Technadraw.  
//   I)    Geometric/topological entities are built bottom up from Technadraw classes in 
//         build[Entity][type]
//         where Entity is one of vertex, edge, face, surface, and shell, and
//               type is Advanced or Faceted.
//   II)   [Inner]bounds (holes in faces) are calculated by intersection of the 
//          negative features in step::findNegFeatureFaceted
//          with the positive features surfaces.
//   III)  Once the resultant step model is created, it is output by using the 
//          serialization method Serialize().
//          step::buildAssembliesFaceted is the last class called which does the 
//          actual serialization in CRepresentationStep::Serialize().
//         CBaseStep is a class containing methods and functionality common to all classes, 
//         but not explicitly specified in the spec.  
//         Representation_itemStep is derived from CBaseStep and is the first class in the spec.
//         All step classes are concatenated with the prefix using the letter C for class, 
//          and a postfix with the word Step.  
//          Instead of spaces as delimiters in the names, the underscore is used "_".
//          
//   IV)   Final touchup is performed on the stepArchive memory file, 
//                which is then output to the hard drive.
//          If the Euler equation is not satisfied, 
//           the closed shell is demoted to an open shell.
//          If layering is used, open_shells are used.
//          If the line is longer than 72 chars, it is split, 
//           being careful not to split a comment contained by ''
//
//          Currently there are two categories of classes, those that work on 
//           faceted_brep & advanced_brep (incomplete).
//          NB. faceted_brep is akin to CATIA output, 
//          while advanced_brep is akin to Spatial's ACIS sat, 
//           Unigraphics's Parasolids, PTC's Pro/E
//
//          Some older systems use CSG, which will recreate breps on regeneration 
//          (for example when features are moved).  Unfortunately, the problem is that 
//          sometimes the regen might fail, or produce different results based on the 
//          tolerance specified
//          Pro/E was the first to use the feature history for regen.
//
//  References:
//         www.PDES.org
//         part 42 geometric and topological representation, 
//          provided defn of entities used in this project.
//         pdes, provided specs on faceted_representation
//          NIST, express Engine (http://sourceforge.net/projects/exp-engine/ ) which reads the file CONFIG_CONTROL_DESIGN and 
//            creates a diagram of the class hierarchy which is explicitly encoded.
//            The *.stp files were verified using expresso for proper syntax.
//         CONFIG_CONTROL_DESIGN (http://www.mel.nist.gov/step/parts/) is the file which describes the classes and 
//           their interactions in a language called Express.
//         Mantyla, "An Introduction to Solid Modeling"
//         Mortenson, Michael E, "Geometric Modeling"
//         Shaw & Mantyla, "Parametric and Feature based Modeling" used in specify iraroEntities
//         Foley & VanDam, "Computer Graphics, Practices and Principles"
//         WiseView32.exe was used to validate the data
//         IBM - Catia step website provided example step files.
//         CATIA-STEP -AP203 Interface Version 4 Reference Manual UNIX Workstation, 
//          program number 5626-STP
//         www.steptools.com provided example files
//         NIST provided many example files and specs, as well as express engine.
//         http://www.uspro.org
//         Product Data Exchange using STEP (PDES) 
//                           Part 42 - Integrated Generic Resources: Geometric and 
//                           Topological Representations 
//                           Company Name: US Product Data Association
//                           Publication Date: 1995 
//                           Contributor 1: American National Standards Institute Inc 
//
//            A reasonable book, except most of the 
//            people writing it shuned some mathematical definitions (genera), and copied down a formula 
//            from another book which they did not comprehend.  Whenever I find something like that, it 
//            makes me think that there might be other problem areas, which they swept under the rug.  
//            For my own sanity, I tried to pull myself out of the same pitfall (not sweeping issues under 
//            the carpet), and introduced entitites like lump, and feature, but to be honest, I remember 
//            them from the ACIS documentation. 
              
//            
//         USPro STEP manuals: ANS US PRO/IPO-200-21 Express Reference Manual
//         USPro STEP manuals: ANS US PRO/IPO-200-046-1994 Representation Context
//         USPro STEP manuals: ANS US PRO/IPO-200-101-1994 Draugthing
//         USPro STEP manuals: ANS US PRO/IPO-200-201-1994 Assoc Draugthing
//         USPro STEP manuals: ANS US PRO/IPO-200-203-1994 configuration controlled design
//         USPro STEP manuals: step aic 513 Faceted Boundary Representation
//         USPro STEP manuals: step aic 514 Advanced Boundary Representation
//         USPro STEP manuals: step aic 515 Constructive Solid Geometry,
//         https://www.uspro.org/new_catalog/approved_step.html
//         
//         Fowler, Julien, "Step, An introduction to Product Exchange"
//         Owen, Jon, "An introduction to STEP", 
//          Unfortunately his example use syntax which is out of date with config_controlled_design.  
//          Wastes valuable time with stupid examples of the Royal family express representation 
//            instead of something pertinent like geometry.
//          Has good UML diagrams in the back of the book of implementation details,
//          however it is unclear if the branches mean anything.
//          Unclear whether "is-a" or "has-a" relationships are implied.
//         http://WWW.PDM-IF.ORG/test_case_archive/
//         http://WWW.boeing.com 
//         http://www.scra.org/step/HTMLS/b37.htm
//         http://www.mel.nist.gov/step/parts/
//         "Inside OLE", Craig Brockschmidt.  addRef, release







//#include <Lmcons.h> //UNLEN 
#include <LIMITS.H>   //UINT_MAX,NAME_MAX
#include <FLOAT.H>    // DBL_MAX, FLT_MAX
#include <stdio.h>    //FILENAME_MAX
#include <stdlib.h>   // _MAX_PATH

#include "afxwin.h" 
#include "stdafx.h" 
#include "scribble.h"
#include "stepArchive.h"
#include "ScribVw.h"
#include "VertexStep.h"
#include "PointStep.h"
#include "VertexStep.h"
#include "Faceted_brepStep.h"
#include "EdgeStep.h"
#include "PathStep.h"
#include "Vertex_loopStep.h"
#include "CurveStep.h"
#include "Oriented_EdgeStep.h"
#include "LineStep.h"
#include "Poly_loopStep.h"
#include "SurfaceStep.h"
#include "Axis2_Placement_3dStep.h"
#include "Elementary_surfaceStep.h"
#include "FaceStep.h"
#include "Face_surfaceStep.h"
//#include "Advanced_faceStep.h"
#include "Connected_face_setStep.h"
#include "Faceted_brepStep.h"
#include "Next_assembly_usage_occuranceStep.h"
#include "Assembly_component_usageStep.h"
#include "Face_boundStep.h"
#include "Cartesian_tranformation_operator_3dStep.h"
#include "Faceted_brepStep.h"
#include "Conical_surfaceStep.h"
#include "Presentable_textStep.h"
#include "Edge_loopStep.h"
#include "Edge_curveStep.h"
#include "Elementary_surfaceStep.h"
#include "PolylineStep.h"
#include "StepSer.h"
#include "PointStep.h"
#include "Cartesian_pointStep.h"
#include "Cartesian_pointStepPtrArray.h"
#include "agitoPtrArray.h"
#include "Faceted_brep_shape_representationStep.h"
#include "PlaneStep.h"
#include "agito.h"
//#include "VersionNo.h"// Micro$lop's file used from incrementing the version number
#include "OrganizationStep.h"


agitoPtrArray step::m_ptrArrayAdvAgito;  // holds onto all of the Step classes for garbage collection later
agitoPtrArray step::m_ptrArrayFacAgito;  // holds onto all of the Step classes for garbage collection later
CFaceted_brep_shape_representationStep * step::m_pFaceted_brep_shape_representationStep  = NULL; // wh 11/21/01
CAdvanced_brep_shape_representationStep* step::m_pAdvanced_brep_shape_representationStep = NULL;

CTime startTime;

// set "true" to turn on functionality which generates negative features 
#define CSG_MERGE true
// negate the entire csg using exists==0 instead of looking at the surface.flip ()
#define CSG_NEGATE true
/*
    surfaceModelSelect aSurfaceModelSelect 
= 
#if 0
      shellBasedSurfaceModel
#else 
      faceBasedSurfaceModel 
#endif
;
*/



const char* szAPPLICATION_CONTEXT = "config_control_design";// using part 203, i.e. 10303-203
//const char* szAPPLICATION_CONTEXT = "core_data_for_automotive_mechanical_design";// using part 214, i.e. 10303-214

#ifdef  EXPOSE      
FILE * g_errorLog = NULL;
#endif//EXPOSE      
int iRepresentationStepNum = 0;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
step::step( CScribView *pOuter)
: m_pScribView( pOuter)
, m_bWriteFile( true)
, m_ptrArrayAgito( m_ptrArrayFacAgito)
, m_pSelectRepresentationStep( NULL)
{ 
  init();
}

step::step( CScribView *pOuter
          , surfaceModelSelect lSurfaceModelSelect)
: m_pScribView( pOuter)
, m_bWriteFile( true)
, m_ptrArrayAgito( m_ptrArrayAdvAgito)
, m_pSelectRepresentationStep( NULL)
{ 
  init();
}
 
step::~step(){
  if   (NULL != m_pSelectRepresentationStep ){
    ASSERT_VALID(m_pSelectRepresentationStep);
    if (m_pSelectRepresentationStep == m_pAdvanced_brep_shape_representationStep)  
    {
      m_pSelectRepresentationStep->m_pStep->finAdv();
    
      // set it back
      m_pSelectRepresentationStep = 
        dynamic_cast<CRepresentationStep*>(m_pFaceted_brep_shape_representationStep);
    } else {
      m_pSelectRepresentationStep->m_pStep->finFac();
    }
  }
}

// write the step data from stepArchive(CString) into a file

HRESULT step::writeStepData(FILE *stream, surfaceModelSelect lSurfaceModelSelect )
{
  HRESULT hr = S_OK;
  try {
    stepArchive ar;// how do you do a setSize on a CString?
    long int iSize = STEP_LINE_LENGTH *
      ( 1024 + 
        this->GetScribView()->m_polygonarray.GetSize()  + 
        this->GetScribView()->m_surfacearray.GetSize()  + 
        this->GetScribView()->m_vertexarray.GetSize()   + 
        this->GetScribView()->m_trianglearray.GetSize() + 
        this->GetScribView()->m_thingarray.GetSize()    );

    // need to preallocate the CString buffer to prevent fragmentation of memory
//  ar.GetBufferSetLength( iSize); // wh 6/5/01    
    hr = TechDraw2Step( stream, ar, lSurfaceModelSelect );
    if ( SUCCEEDED( hr) ) {
      bool fin = false;
      // need to trim line length to < 72
      int iStart=0;
      int iCurr =0;// current start of buffer used to find the line
#if 0 // low priority because most viewers will read it anyway!
      // force lines to be shorter than 72 chars as per spec
      do {
        int iPos = ar.Find("\n");
        ar.GetBuffer(iPos);
        if ((iPos-iStart) > STEP_LINE_LENGTH){
        }
        ar.ReleaseBuffer();
      // last chance to demote closed_shells [to open_shells] or 
        // promote face_bound [to face_outer_bound]
      }
      while (!fin);
#else
      ar.write( stream);
#endif 
    }
    else {
#if 1
      *( (iraroArchive*)(ar.m_archives.GetAt(0) )) << "\n/*Errors detected*/\n";
      ar.write( stream);
      
#endif
    }
  }
  catch ( ... ) {
    bool bStepGood = false;
    ASSERT( bStepGood );
    return E_FAIL;  
  }

  return hr;
}

//#ifndef UNLEN // hack, hack, hack, but I could not get it to compile in release mode without this
//#define UNLEN            255
//#endif

char szUserName[FILENAME_MAX +1];
DWORD nSize = (FILENAME_MAX );

int g_iFACETED_BREP_SHAPE_REPRESENTATION = CBaseStep::m_iCount;
// write out the part design managment section
// just adds the CFS face set to the base feature
// when it works, then we will worry about Braid/Greyer add
HRESULT step::addEulerFaceted( agitoAssembly* pAssembly, 
                               agitoComponent& raNegativeFeatures)
{
  for (int im =0; im<pAssembly->GetSize();im++){

    agitoPart* pPart = (agitoPart*)pAssembly->GetAt(im);
    agitoComponent* pLump = (agitoComponent*)pPart->GetAt( 0);
    agitoFeature* pFeature = (agitoFeature*)pLump->GetAt( 0);
    CClosed_shellStep* pShellStep = (CClosed_shellStep* )    pFeature->GetAt( 0);
    for (int iF = 0; iF < pLump->GetSize(); iF++) {
      agitoFeature* pAntiFeature = NULL;
      if (iF>0){
        pFeature = (agitoFeature*)pLump->GetAt( iF);
        for (int iAnti=0; iAnti < raNegativeFeatures.GetSize(); iAnti++){
          agitoFeature* pAntiFeature = (agitoFeature* )raNegativeFeatures.GetAt(iAnti);
          if ( pAntiFeature == pFeature ){
            break;
          }
        }//iAnti
        if (NULL ==pAntiFeature ){
          pFeature->mergeCFSFacetted( 0, pShellStep);
        }
        else {
          pFeature->removeCFSFacetted( 0, pShellStep);
        }

      }//fi iF>0
        
      if (NULL ==pAntiFeature ){
        int numShells = pFeature->GetSize();
        for (int is=1;is< numShells ; is++){
           pFeature->mergeCFSFacetted(is, pShellStep);
        }//next is
      }
    }//next iF
  }// next im
  return S_OK;
}
// bug above, make it work when the base feature is not the first one
// hint create a binary tree


HRESULT step::faceXedgeFacetedCoincident( CPlaneStep*        pPlaneStepOnPosFeature,
                                          CPoly_loopStep*    pPLoopN,       // loop corresponding to neg feature
                                          CrcPtrArray*       pLoopIntersectionPoints,     // collection of intersection 
                                                                                          //  points on polygon
                                          unsigned int &     riStartIndex, // index of startpoint
                                          unsigned int &     riEndIndex   // index of endpoint
                                        , CCartesian_pointStep* pCartesian_pointStep0 
                                        , CCartesian_pointStep* pCartesian_pointStep1 
                                        , int &iInsertionIndex
                                        )
{
  int k0 = pPLoopN->Find(pCartesian_pointStep0);
  int k1 = pPLoopN->Find(pCartesian_pointStep1);
  if (0 == pLoopIntersectionPoints->GetSize()){
    if (((k0+1) == k1) || ( (0 == k1) && ((pPLoopN->GetSize()-1) == k0))){
      pLoopIntersectionPoints->Add( pCartesian_pointStep1);
      pLoopIntersectionPoints->Add( pCartesian_pointStep0);
    } else if 
       (((k0-1) == k1) ||( ((pPLoopN->GetSize()-1) == k1) && (0 == k0))){
      pLoopIntersectionPoints->Add( pCartesian_pointStep0);
      pLoopIntersectionPoints->Add( pCartesian_pointStep1);
    } else {
      ASSERT(0);
      pLoopIntersectionPoints->Add( pCartesian_pointStep0);
      pLoopIntersectionPoints->Add( pCartesian_pointStep1);
    }
  }
  else if (pCartesian_pointStep0 == pLoopIntersectionPoints->GetAt(0)) {

    if (((k0+1) == k1) || ( (0 == k1) && ((pPLoopN->GetSize()-1)==k0))){
      pLoopIntersectionPoints->InsertAt( iInsertionIndex, pCartesian_pointStep1);
//    iInsertionIndex++;
    } else if 
       (((k0-1) == k1) ||( ((pPLoopN->GetSize()-1) == k1) && (0==k0))){
      pLoopIntersectionPoints->InsertAt( iInsertionIndex+1, pCartesian_pointStep1);
//    iInsertionIndex++;
    } else {
      ASSERT(0);
      pLoopIntersectionPoints->InsertAt(iInsertionIndex+1, pCartesian_pointStep1);
//    iInsertionIndex++;
    }

//          pLoopIntersectionPoints->InsertAt(0, pCartesian_pointStep1);
  }
  else if (pCartesian_pointStep1 == pLoopIntersectionPoints->GetAt(0)){
    if (((k0+1) == k1) || ( (0 == k1) && ((pPLoopN->GetSize()-1)==k0))){
      pLoopIntersectionPoints->InsertAt(iInsertionIndex+1, pCartesian_pointStep0);
//    iInsertionIndex++;
    } else if 
       (((k0-1) == k1) ||( ((pPLoopN->GetSize()-1) == k1) && (0==k0))){
      pLoopIntersectionPoints->InsertAt(iInsertionIndex, pCartesian_pointStep0);
//    iInsertionIndex++;
    } else {
      ASSERT(0);
      pLoopIntersectionPoints->InsertAt(iInsertionIndex, pCartesian_pointStep0);
//    iInsertionIndex++;
    }
//  pLoopIntersectionPoints->InsertAt(0, pCartesian_pointStep0);
  }
  else if (pCartesian_pointStep0 == pLoopIntersectionPoints->GetAt(pLoopIntersectionPoints->GetSize()-1)){
    if (((k0+1) == k1) || ( (0 == k1) && ((pPLoopN->GetSize()-1)==k0))){
      pLoopIntersectionPoints->InsertAt(pLoopIntersectionPoints->GetSize()-1, pCartesian_pointStep1);
    } else if 
       (((k0-1) == k1) ||( ((pPLoopN->GetSize()-1) == k1) && (0==k0))){
      pLoopIntersectionPoints->Add( pCartesian_pointStep1);
    } else {
      ASSERT(0);
      pLoopIntersectionPoints->Add( pCartesian_pointStep1);
    }
//  pLoopIntersectionPoints->Add( pCartesian_pointStep1);
  }
  else if (pCartesian_pointStep1 == pLoopIntersectionPoints->GetAt(pLoopIntersectionPoints->GetSize()-1)){
    if (((k0+1) == k1) || ( (0 == k1) && ((pPLoopN->GetSize()-1)==k0))){
      pLoopIntersectionPoints->Add( pCartesian_pointStep0);
    } else if 
       (((k0-1) == k1) ||( ((pPLoopN->GetSize()-1) == k1) && (0==k0))){
      pLoopIntersectionPoints->InsertAt(pLoopIntersectionPoints->GetSize()-1, pCartesian_pointStep0);
    } else {
      ASSERT(0);
      pLoopIntersectionPoints->InsertAt(pLoopIntersectionPoints->GetSize()-1, pCartesian_pointStep0);
    }
//  pLoopIntersectionPoints->Add( pCartesian_pointStep0);
  } else {
    ASSERT(0);
  }

  return S_OK;
}
/*
          if (pCartesian_pointStep0 == pLoopIntersectionPoints->GetAt(0)) {
            double dp = 
              dotProduct( *(pPlaneStepOnPosFeature->m_pPosition->m_pAxis)
                        , *(pEdge->m_pOrientation)
                        );
            if (dp>restol2){
              pLoopIntersectionPoints->Add((void*)pCartesian_pointStep1);
            } else if (dp<-restol2){
              pLoopIntersectionPoints->InsertAt( iInsertionIndex 
                , (void*)pCartesian_pointStep1);
              iInsertionIndex++;
            } else {
              TRACE0("coincidence??\n");
              ASSERT(0);
            }
          }
          else if (pCartesian_pointStep1 == pLoopIntersectionPoints->GetAt(0)){
          double dp = 
            dotProduct( *(pPlaneStepOnPosFeature->m_pPosition->m_pAxis)
                      , *(pEdge->m_pOrientation)
                      );
          if (dp>restol2){
            pLoopIntersectionPoints->Add((void*)pCartesian_pointStep0);
          } else if (dp<-restol2){
            pLoopIntersectionPoints->InsertAt( iInsertionIndex 
              , (void*)pCartesian_pointStep0);
            iInsertionIndex++;
          } else {
            TRACE0("coincidence??\n");
            ASSERT(0);
          }
          }
          else if (pCartesian_pointStep0 == pLoopIntersectionPoints->GetAt(pLoopIntersectionPoints->GetSize()-1)){
          double dp = 
            dotProduct( *(pPlaneStepOnPosFeature->m_pPosition->m_pAxis)
                      , *(pEdge->m_pOrientation)
                      );
          if (dp>restol2){
            pLoopIntersectionPoints->Add((void*)pCartesian_pointStep1);
          } else if (dp<-restol2){
            pLoopIntersectionPoints->InsertAt( iInsertionIndex 
              , (void*)pCartesian_pointStep1);
            iInsertionIndex++;
          } else {
            TRACE0("coincidence??\n");
            ASSERT(0);
          }
          }
          else if (pCartesian_pointStep1 == pLoopIntersectionPoints->GetAt(pLoopIntersectionPoints->GetSize()-1)){
          double dp = 
            dotProduct( *(pPlaneStepOnPosFeature->m_pPosition->m_pAxis)
                      , *(pEdge->m_pOrientation)
                      );
          if (dp>restol2){
            pLoopIntersectionPoints->Add((void*)pCartesian_pointStep1);
          } else if (dp<-restol2){
            pLoopIntersectionPoints->InsertAt( iInsertionIndex 
              , (void*)pCartesian_pointStep1);
            iInsertionIndex++;
          } else {
            TRACE0("coincidence??\n");
            ASSERT(0);
          }
          } else {
            ASSERT(0);
          double dp = 
            dotProduct( *(pPlaneStepOnPosFeature->m_pPosition->m_pAxis)
                      , *(pEdge->m_pOrientation)
                      );
          if (dp>restol2){
            pLoopIntersectionPoints->Add((void*)pCartesian_pointStep0);
            pLoopIntersectionPoints->Add((void*)pCartesian_pointStep1);
          } else if (dp<-restol2){
            pLoopIntersectionPoints->InsertAt( iInsertionIndex 
              , (void*)pCartesian_pointStep0);
            iInsertionIndex++;
            pLoopIntersectionPoints->InsertAt( iInsertionIndex 
              , (void*)pCartesian_pointStep1);
            iInsertionIndex++;
          } else {
            TRACE0("coincidence??\n");
            ASSERT(0);
          }
          }
  */


// calculate the face-edge intersection
// each edge is oriended ccw, henc wh just have to make sure that they are properly inserted into the list
HRESULT step::faceXedgeFaceted( CFace_surfaceStep *pFace_surfaceStepOnPosFeature,
                                CPoly_loopStep*    pPLoopN,       // loop corresponding to neg feature
                                double&            dStartParam,  // start parameter on line0
                                double&            dEndParam,    // end parameter on line0
                                CrcPtrArray*       pLoopIntersectionPoints,     // collection of intersection 
                                //points on polygon
                                unsigned int &     riStartIndex, // index of startpoint
                                unsigned int &     riEndIndex   // index of endpoint
                              , CCartesian_pointStepPtrArray*& pCartesian_pointStepPtrArray
                              )
{ 
  HRESULT hr = S_OK;
  int iInsertionIndex = 0;
  int iAdditionIndex = 0;// how far from the end do you insert these??
  int ivm1 = pPLoopN->m_aPolygonVertices.GetSize()-1; 
  for (int iv = 0; iv < pPLoopN->m_aPolygonVertices.GetSize(); iv++){
    // create an edge on neg features bounded , that edge is oriented ccw, 
    //  hence the intersections are also oriented ccw as well, 
    //  provided that the last one was not encountered first!
    CPlaneStep* pPlaneStepOnPosFeature = dynamic_cast<CPlaneStep*>
      (pFace_surfaceStepOnPosFeature->m_pFace_geometry);
   // int iNumIntersection=0;
    // create an edge on neg features bounded 

    CCartesian_pointStep* pCartesian_pointStep0 = 
      dynamic_cast<CCartesian_pointStep*>((CBaseStep*)
      (pPLoopN->m_aPolygonVertices.GetAt(ivm1)));

    CCartesian_pointStep* pCartesian_pointStep1 = 
      dynamic_cast<CCartesian_pointStep*>((CBaseStep*)
      (pPLoopN->m_aPolygonVertices.GetAt(iv  )));

    // intersect this edge with the plane
    if( (NULL != pCartesian_pointStep0) && 
        (NULL != pCartesian_pointStep1)
      ){

      CVectorStep* pEdge = new 
        CVectorStep ( *pCartesian_pointStep0, *pCartesian_pointStep1);   
      if (NULL==pEdge) {
        return E_OUTOFMEMORY;
      }// wh 10/17/01
      CLineStep *pEdgeN = new 
        CLineStep (*pCartesian_pointStep0, *pEdge , pCartesian_pointStep1);
      if (NULL==pEdgeN) {
        return E_OUTOFMEMORY;
      }// wh 10/17/01
      intersectionType intersection = noIntersection;//unknownSegmentIntersection 
      double paramU, paramV,
             paramT[2];

      CrcPtrArray* pEdgeIntersectionPoints = new CrcPtrArray();
      if ( NULL == pEdgeIntersectionPoints ) {
        delete pEdge;
        delete pEdgeN;
        return E_OUTOFMEMORY;
      }
    
      hr = 
        pPlaneStepOnPosFeature->intersect( pEdgeN, 
                                           intersection, 
                                           pEdgeIntersectionPoints, 
                                           paramU, 
                                           paramV,
                                           paramT );
      if (FAILED( hr)){
        delete pEdgeIntersectionPoints;
        delete pEdge;
        delete pEdgeN;
        return hr;
      }

      if ( noIntersection != intersection){
/*
  //    CDirectionStep faceLeft(NULL, pEdge->m_dMagnitude );
        containment            bContains=unknownContainment;
        double dParam;
        // wait, not so fast, we have to make sure that intersection point is inside FOB
        pPLoopN->contains( (CCartesian_pointStep*)pEdgeIntersectionPoints->GetAt(0), bContains, (pEdge->m_pOrientation), dParam);
        if (out==bContains){
          intersection = noIntersection ;
        }
*/
        if ( startpointIntersection == intersection) {
          // find out where the surface is to the left of the traversal direction
          // if edge vector is antiparellel to surface normal, start point
          // if edge vector is parallel to surface Normal, endpoint
          double dp = 
            dotProduct( *(pPlaneStepOnPosFeature->m_pPosition->m_pAxis)
            , *(pEdge->m_pOrientation));
          if (dp>0){
//          if (pLoopIntersectionPoints->GetAt( pLoopIntersectionPoints->GetSize()-1) != (void*)pCartesian_pointStep0){
              riStartIndex = pLoopIntersectionPoints->Add((void*)pCartesian_pointStep0);
//          }
//          else {
//            riStartIndex = pLoopIntersectionPoints->GetSize()-1;
//          }
          } else if (dp<0){
            riStartIndex = 0;
//          if (pLoopIntersectionPoints->GetAt( iInsertionIndex) != (void*)pCartesian_pointStep0){
              pLoopIntersectionPoints->InsertAt( iInsertionIndex, (void*)pCartesian_pointStep0);
              iInsertionIndex++;          
//          }
          } else {
            TRACE0("coincidence??\n");
          }
        }  
        else if ( endpointIntersection == intersection) {
          // find out where the surface is to the left of the traversal direction
          // if edge vector is antiparellel to surface normal, start point
          // if edge vector is parallel to surface Normal, endpoint
          double dp = 
            dotProduct( *(pPlaneStepOnPosFeature->m_pPosition->m_pAxis)
                      , *(pEdge->m_pOrientation)
                      );
          if (dp>0){
            riEndIndex = pLoopIntersectionPoints->Add((void*)pCartesian_pointStep1);
          } else if (dp<0){
            riEndIndex = 0;
            pLoopIntersectionPoints->InsertAt(iInsertionIndex , (void*)pCartesian_pointStep1);
            iInsertionIndex++;
          } else{
            TRACE0("coincidence??\n");
          }
        }  
        else if ( interiorIntersection == intersection) {

          // small problem in that intersection is sometimes unnecssary 
          //  because the loop goes outside the outer_bound and 
          //  has not been contained as in MERGE_BOUNDS_INTERSECTION ! // wh 02/25/02

          // accept only intersections between the start_point and end_point.of Edge1.
          // Not only do we have to find the params, 
          //   but we also have to split the loop on face of the neg feature and truncate it
          CCartesian_pointStep *pCartesian_pointOld = (CCartesian_pointStep *)pEdgeIntersectionPoints->GetAt(0);
          CCartesian_pointStep *pCartesian_pointNew = pCartesian_pointOld;
  /*
          // need to search against the list of known points, and if found use the other one!  //wh 11/13/01   
          pCartesian_pointStepPtrArray->Find( pCartesian_pointOld, pCartesian_pointNew);// wh 11/13/01
          if (NULL != pCartesian_pointOld){
            pCartesian_pointStepPtrArray->Add( pCartesian_pointNew);// wh 11/13/01
          }
  */
          // we need to make sure the intersection points are ordered CCW
          // if edge vector is antiparellel to surface normal, start point
          // if edge vector is parallel to surface Normal, endpoint
          double dp = 
            dotProduct( *(pPlaneStepOnPosFeature->m_pPosition->m_pAxis)
                      , *(pEdge->m_pOrientation)
                      );
          if (dp>restol2){
            pLoopIntersectionPoints->Add((void*) pCartesian_pointNew);
          } else if (dp<-restol2){
            pLoopIntersectionPoints->InsertAt( iInsertionIndex 
              , (void*)pCartesian_pointNew);
            iInsertionIndex++;
          } else {
            TRACE0("coincidence??\n");
            ASSERT(0);
          }

          // we should also add this intersection to the posFeature's face?

  // wh 10/22/01 true

          // wh 10/15/01  setting true gives better results, but gaps_in loops
          // modify the negative feature by adding the vertex at the intersection
  // seem to miss one due to tolerance issues!// wh 11/06/01
            // check if the point is within the [outer]bound
            CDirectionStep* pFaceNormal = pPlaneStepOnPosFeature->m_pPosition->m_pAxis;
            containment bContains = unknownContainment; 
            double rdParam;
            pFace_surfaceStepOnPosFeature->convexContains( 
              (CCartesian_pointStep*) pEdgeIntersectionPoints->GetAt(0), 
              bContains, 
              pFaceNormal 
            , rdParam                    
            ); 

            if ( out != bContains )// really should be    (on == bContains)
            {
              if (0 != iv){ 
                if ((pPLoopN->m_aPolygonVertices.GetAt(iv  ) != pCartesian_pointNew ) && 
                    (pPLoopN->m_aPolygonVertices.GetAt(ivm1) != pCartesian_pointNew ) ){
                  // also double check that this isn't an endpoint

                  pPLoopN->m_aPolygonVertices.InsertAt( iv,(void*)pCartesian_pointNew );
                  iv++;
                }
              }
              else {
                if ((pPLoopN->m_aPolygonVertices.GetAt(iv  ) != pCartesian_pointNew ) && 
                    (pPLoopN->m_aPolygonVertices.GetAt(ivm1) != pCartesian_pointNew ) ){
                  // do as above

                  pPLoopN->m_aPolygonVertices.Add( (void*)pCartesian_pointNew );
                }
              }
              // also need to add them to the pos surface's loops

            }// fi contain
          // fi MOD_NEG_FEATURE

          // can there be more intersections here??, 
            //probably not on a plane, what about with numerical noise?
        }// fi interiorIntersection == intersection
        else if ( coincidentIntersection == intersection) {
          // should not reveal more info than we already have, but could be used to simplify
          dStartParam = min( dStartParam, paramT[0]);
          dEndParam   = max( dEndParam  , paramT[1]);

// need this to prevent gaps
// wh 3/13/02
          if (-1) {
            faceXedgeFacetedCoincident( pPlaneStepOnPosFeature
                                      , pPLoopN                     // loop corresponding to neg feature
                                      , pLoopIntersectionPoints     // collection of intersection 
                                                                    //     points on polygon
                                      , riStartIndex                // index of startpoint
                                      , riEndIndex                  // index of endpoint
                                      , pCartesian_pointStep0 
                                      , pCartesian_pointStep1
                                      , iInsertionIndex
                                      );

          }
        }
        else {
          for (int i = 0; i< pEdgeIntersectionPoints->GetSize();i++){
             delete pEdgeIntersectionPoints->GetAt(i);
          }
        }
      }
      else {
  //        for (int i = 0; i< pEdgeIntersectionPoints->GetSize();i++){
  //           delete pEdgeIntersectionPoints->GetAt(i);// wh 10/19/01
  //        }
      }

      delete pEdgeIntersectionPoints;

      delete pEdgeN;
      delete pEdge;

    }
    // if you modified the neg feature, you should split the face into two as well
    ivm1 = iv;
  }// next iv
  return S_OK;
}

// calculate the edge-edge intersection 
HRESULT step::edgeXedgeFaceted( int              ivm1,         // start vertex on neg feature's poly
                                int              iv,           // end vertex on neg feature's poly
                                CPoly_loopStep*  pPLoop,       // loop corresponding to neg feature
                                double&          dStartParam,  // start parameter on line0
                                double&          dEndParam,    // end parameter on line0
                                CLineStep*       pLine0,       // line of intersection between the two polys
                                CrcPtrArray*     pLoopIntersectionPoints     // collection of intersection 
                                                                //points on polygon
                                , CCartesian_pointStepPtrArray*pCartesian_pointStepPtrArray
                                )
{
 // int iNumIntersection=0;
  // create an edge on neg features bounded 
  int jvm1 = (int )pCartesian_pointStepPtrArray->m_hash.GetAt(ivm1);
  CCartesian_pointStep* pPointStep0 = dynamic_cast<CCartesian_pointStep*>((CPointStep* )
    (pPLoop->m_aPolygonVertices.GetAt(jvm1)));
  int jv = (int )pCartesian_pointStepPtrArray->m_hash.GetAt(iv);// wh 09/07/01
  CCartesian_pointStep* pPointStep1 = dynamic_cast<CCartesian_pointStep*>((CPointStep* )
    (pPLoop->m_aPolygonVertices.GetAt(jv  )));

  // intersect this edge with the line
  if( (NULL != pPointStep0) && (NULL != pPointStep1)){
    CVectorStep* pEdge = new 
      CVectorStep ( *pPointStep0, *pPointStep1);   
    if (NULL==pEdge) {
      return E_OUTOFMEMORY;
    }// wh 10/17/01
    CLineStep *pEdge1 = new 
      CLineStep (*pPointStep0, *pEdge, pPointStep1 );
    if (NULL==pEdge1) {
      return E_OUTOFMEMORY;
    }// wh 10/17/01
    intersectionType intersection, intersection0;
    double param0, 
           param1;
    CrcPtrArray* pEdgeIntersectionPoints = new CrcPtrArray();
    if (NULL==pEdgeIntersectionPoints) {
      return E_OUTOFMEMORY;
    }// wh 10/17/01
    HRESULT hr =
    pLine0->intersect( *pEdge1, intersection, pEdgeIntersectionPoints, 
        param0, param1 , intersection0);
    if (FAILED(hr)){
      delete pEdgeIntersectionPoints;
      return hr;
    }
    if ( noIntersection != intersection){
      if ( startpointIntersection == intersection) {
        // find out where the surface is to the left of the traversal direction
        dStartParam = min( dStartParam, param0);
        pLoopIntersectionPoints->Add((void*)pEdgeIntersectionPoints->GetAt(0));
      }  
      else if ( endpointIntersection == intersection) {
        // find out where the surface is to the left of the traversal direction
        dEndParam   = max( dEndParam  , param0);
        pLoopIntersectionPoints->Add((void*)pEdgeIntersectionPoints->GetAt(0));
      }  
      else if ( interiorIntersection == intersection) {
        // accept only intersections between the start_point and end_point.of Edge1
//      pEdge1->
        // not only do we have to find the params, 
        // but we also have to split the loop on face of the neg feature and truncate it
        dStartParam = min( dStartParam, param0);
        dEndParam   = max( dEndParam  , param0);
        pLoopIntersectionPoints->Add((void*)pEdgeIntersectionPoints->GetAt(0));
      }
      else if ( coincidentIntersection == intersection) {
        // should not reveal more info than we already have, but could be used to simplify
        dStartParam = min( dStartParam, param0);
        dEndParam   = max( dEndParam  , param0);
//      pLoopIntersectionPoints->Add((void*)pEdgeIntersectionPoints->GetAt(0));
//      pLoopIntersectionPoints->Add((void*)pEdgeIntersectionPoints->GetAt(1));
      }  
    }
    delete pEdgeIntersectionPoints;
  }//fi
  return S_OK;
}

// make a method of CPoly_loopStep  wh 7/23/01
// calculate the edge-line intersections (or almost intersection)
HRESULT step::lineEdgeGlanceFaceted( int              ivm1,         // start vertex on neg feature's poly
                                     int              iv,           // end vertex on neg feature's poly
                                     CPoly_loopStep*  pPLoop,       // loop corresponding to neg feature
                                     double&          dStartParam,  // start parameter on line0
                                     double&          dEndParam,    // end parameter on line0
                                     CLineStep*       pLine0,       // line of intersection between the two polys
                                     CrcPtrArray*       pLoopIntersectionPoints,     // collection of intersection points on polygon
                                     intersectionType& intersection1, 
                                     intersectionType& intersection0)

{
 // int iNumIntersection=0;
  // create an edge on neg features bounded 
  CCartesian_pointStep* pPointStep0 = dynamic_cast<CCartesian_pointStep*>((CObject*)
    (pPLoop->m_aPolygonVertices.GetAt(ivm1)));
  CCartesian_pointStep* pPointStep1 = dynamic_cast<CCartesian_pointStep*>((CObject*)
    (pPLoop->m_aPolygonVertices.GetAt(iv  )));

  // intersect this edge with the line
  if( (NULL != pPointStep0) && (NULL != pPointStep1)){
    CVectorStep* pEdge = new 
      CVectorStep ( *pPointStep0, *pPointStep1);   
    if (NULL==pEdge) {
      return E_OUTOFMEMORY;
    }// wh 10/17/01
    bool bWithinTol ;
    pEdge->withinTol( bWithinTol );
    if (!bWithinTol ){
      CLineStep *pEdge1 = new 
        CLineStep (*pPointStep0, *pEdge , pPointStep1);
      if (NULL==pEdge1) {
        return E_OUTOFMEMORY;
      }// wh 10/17/01
      double param0, 
             param1;
      CrcPtrArray* pEdgeIntersectionPoints = new CrcPtrArray();
      if (NULL==pEdgeIntersectionPoints) {
        return E_OUTOFMEMORY;
      }// wh 10/17/01

      pLine0->intersect( *pEdge1, intersection1, pEdgeIntersectionPoints, 
        param0, param1 , intersection0);

      if ( ( noIntersection != intersection1) && 
           (pEdgeIntersectionPoints->GetSize()>0)  // wh 10/09/01
         )
      {
        if ( startpointIntersection == intersection1) {
          // find out where the surface is to the left of the traversal direction
          dStartParam = min( dStartParam, param0);
          pLoopIntersectionPoints->Add((void*)pEdgeIntersectionPoints->GetAt(0));
        }  
        else if ( endpointIntersection == intersection1) {
          // find out where the surface is to the left of the traversal direction
          dEndParam   = max( dEndParam  , param0);
          pLoopIntersectionPoints->Add((void*)pEdgeIntersectionPoints->GetAt(0));
        }  
        else if ( interiorIntersection == intersection1) {
          // accept only intersections between the start_point and end_point.of Edge1
  //      pEdge1->
          // not only do we have to find the params, 
          //  but we also have to split the loop on face of the neg feature and truncate it
          dStartParam = min( dStartParam, param0);
          dEndParam   = max( dEndParam  , param0);
          pLoopIntersectionPoints->Add((void*)pEdgeIntersectionPoints->GetAt(0));
        }
        else if ( coincidentIntersection == intersection1) {
          // should not reveal more info than we already have, but could be used to simplify
          dStartParam = min( dStartParam, param0);
          dEndParam   = max( dEndParam  , param0);
  //      pLoopIntersectionPoints->Add((void*)pEdgeIntersectionPoints->GetAt(0));
  //      pLoopIntersectionPoints->Add((void*)pEdgeIntersectionPoints->GetAt(1));
        }  
      }
      delete pEdgeIntersectionPoints;
      delete pEdge1;//wh 10/04/01
    }
    delete pEdge;
  }//fi
  return S_OK;
}


// calculate the face-face intersections
HRESULT step::faceXfaceFaceted( CFace_surfaceStep *             pFace_surfaceStepOnPosFeature, // positive features's face
                                CFace_surfaceStep *             pFace_surfaceStepOnNegFeature, // neg features face
                                CPoly_loopStepEx*               pPolyIntersectionPoints ,   // intersection point on polyon 
                                                                                            //  of pFace_surfaceStepOnPosFeature
                                bool &                          bGapsEncountered, 
                                CPtrArray*&                     pFace_surfaceStepPtrArray
                              , CCartesian_pointStepPtrArray*&  pCartesian_pointStepPtrArray
                            //, thingList&                      rNegThingsList 
                              )
{

  CPlaneStep* pPlaneStepOnPosFeature = dynamic_cast<CPlaneStep*>
    (pFace_surfaceStepOnPosFeature->m_pFace_geometry);

  if (NULL != pPlaneStepOnPosFeature ){
  
    CPlaneStep* pPlaneStepOnNegFeature  = dynamic_cast<CPlaneStep*>
      (pFace_surfaceStepOnNegFeature->m_pFace_geometry);
    if (NULL != pPlaneStepOnNegFeature ){

      CDirectionStep* pIntersection= NULL; 
      // calculate the direction of the intersection edge
      pIntersection=crossProduct( *pPlaneStepOnPosFeature->m_pPosition->m_pAxis 
                                , *pPlaneStepOnNegFeature->m_pPosition->m_pAxis
                                );
      bool bPlanesIntersect = !pIntersection->withinTol();  
      if (!bPlanesIntersect ) { 
        if (
             pPlaneStepOnPosFeature->onSurface( *(pPlaneStepOnNegFeature->m_pPosition->m_pLocation))
           ){
          bPlanesIntersect = true;
        }
      }

      // make sure that the faces are not parallel
      if (bPlanesIntersect ){
      
        double dStartParam =  DBL_MAX;//???
        double dEndParam   = -DBL_MAX;//???
        // trim the infinite edge to within the bounds
        // there is only one bound right now, 
        //  enclosing a convex region because CPolygon is convex
        int ib = 0;
        //for(;ib<pFace_surfaceStepOnNegFeature->GetSize(); ib++)
#pragma message("change this back!\n")
        if   (  0<pFace_surfaceStepOnNegFeature->GetSize()      )
        {
          
          CFace_boundStep* pFace_boundStepN = (CFace_boundStep*)
            pFace_surfaceStepOnNegFeature->GetFace_outer_bound();
          CPoly_loopStep* pPLoopN = dynamic_cast<CPoly_loopStep*>
            (pFace_boundStepN->m_bound);
//          loopXPts *pLoopXPts = NULL;
//          for (int ix = 0; ix < aLoopXPointArray.GetSize(); ix++){
//            pLoopXPts = aLoopXPointArray.GetAt( ix);
//            if ((NULL != pLoopXPts) && 
//                (pLoopXPts->m_pPlaneStepOnNegFeature == pPlaneStepOnNegFeature)
//               ){
//              break;
//            }
//            else {
//              pLoopXPts = NULL;
//            }
//          }// next ix
//          ASSERT(NULL != pLoopXPts);
//          if (NULL != pLoopXPts){
          CrcPtrArray loopIntersectionPoints ;//= (pLoopXPts->loopIntersectionPoints);
          loopIntersectionPoints.SetSize( 0 
            , pPLoopN->m_aPolygonVertices.GetSize() //wh 10/18/01
            );
          unsigned int iStartIndex = UINT_MAX;// holds onto the index of the start point 
          unsigned int iEndIndex   = UINT_MAX;// holds onto the index of the end   point 

          faceXedgeFaceted( pFace_surfaceStepOnPosFeature
                          , pPLoopN 
                          , dStartParam 
                          , dEndParam 
                          , &loopIntersectionPoints 
                          , iStartIndex 
                          , iEndIndex 
                          , pCartesian_pointStepPtrArray
                          );

          // ensure that all intersection point come in pairs, if not, replicate last one

          // now need to weed out duplicate points and 
          //make sure that the negative features polyloop is oriented CW!

          // did not end at the vertex of an edge
          if ( true //UINT_MAX == iStartIndex // wh 02/05/02
                    ){  paramPtrArray intersectionEdge(2 * loopIntersectionPoints.GetSize());
            intersectionEdge.SetSize(0, loopIntersectionPoints.GetSize());
            if (0 < loopIntersectionPoints.GetSize()){
              intersectionEdge.SetSize(0, 2);
                CDirectionStep& faceNormal = *(pPlaneStepOnPosFeature->m_pPosition->m_pAxis);

                containment bContainsP = unknownContainment;
                for (int k = 0 ; k< loopIntersectionPoints.GetSize(); k++){
                  double dParam;
                  containment bContainsI = unknownContainment;
                  // if it is outside, need to move point to boundary along intersection edge
                  pFace_surfaceStepOnPosFeature->contains( 
                      (CCartesian_pointStep*)loopIntersectionPoints.GetAt(k)
                    , bContainsI
                    , dParam
                    );
//                  ASSERT( unknownContainment != bContainsI);// wh 2/10/01

                  if ( in == bContainsI){
                    int iw = intersectionEdge.Add( loopIntersectionPoints.GetAt(k));
                    double dnkm1 = -k-1;
                    intersectionEdge.aParam.SetAt(iw, (DWORD) dnkm1 );
                  } else if ( on == bContainsI){
                    int iw = intersectionEdge.Add( loopIntersectionPoints.GetAt(k));
                    double dnkm1 = -k-1;
                    intersectionEdge.aParam.SetAt(iw, (DWORD) dnkm1 );
                  }
                  else{
//                  intersectionEdge.SetAt(k, NULL);
                  }
                  if (unknownContainment == bContainsP){
                    bContainsP = bContainsI;
                  }

                  if (out == bContainsI){
                    bContainsP = bContainsI;
                  }
                }// next k

                if (out == bContainsP ){
                  containment bContains = unknownContainment;
                  // if it is outside, need to move point to boundary along intersection edge
                  pFace_surfaceStepOnPosFeature->trimEdge
                    ( &loopIntersectionPoints
                    , intersectionEdge
                    , bContains
                    );
#if 0
                  // point on neg surface are not added to its loops
                  containment bContainsN = unknownContainment;
                  // if it is outside, need to move point to boundary along intersection edge
                  pFace_surfaceStepOnNegFeature->trimEdge // wh 02/10/02
                    ( &loopIntersectionPoints
                    , intersectionEdge
                    , bContainsN
                    );
#endif
                }
              }
            
              // we have to cut away both surfaces of the intersection
//            #define SPLIT_NEG_FEATURE false
              // wh 02/08/02
              #ifdef SPLIT_NEG_FEATURE
              {

                CDirectionStep* pDirInc = pIntersection;
//              if (((!pFace_surfaceStepOnPosFeature->m_bSame_sense)  &&
//                   ( pFace_surfaceStepOnNegFeature->m_bSame_sense))  ||
//                  (( pFace_surfaceStepOnPosFeature->m_bSame_sense)  &&
//                   (!pFace_surfaceStepOnNegFeature->m_bSame_sense)
//                 )){
//                pDirInc->negate();
//              }

                intersectionEdge.simplify( );
//              ASSERT( ((intersectionEdge.GetSize())%2) == 0);
                if (1 < intersectionEdge.GetSize()){
                  // problem, the intersection edge has to be oriented where the cutting side has matter to the left
                  intersectionEdge.orderByParam( pDirInc);
                // and positive one as well

                  // first process the pos features because it has the missing pts wh 2/13/02
                  // problem in that intersection points haven't been added this FB's loop yet!   // wh 02/08/02
#if 0
                  pFace_surfaceStepOnPosFeature->splitAdd( // new way adds in the intersection pts
                                                           &intersectionEdge 
                                                         );
#else
                  pFace_surfaceStepOnPosFeature->split( // old way
                                                        &intersectionEdge 
                                                      );
#endif


                // trim the negative feature down to size for incorporation into resultant
                // If this is done, then the part which lies outside must be deleted!
                // N. B. intersectionEdge must be inside & oriented w/ matter on LHS
                  pFace_surfaceStepOnNegFeature->split( 
                                                        &intersectionEdge
                                                      );

                }
              }//fi 
              #endif//SPLIT_NEG_FEATURE
            }
            iStartIndex = 0;
          
//        ASSERT( UINT_MAX != iEndIndex  );
          // did not start at the vertex of an edge
          if ( UINT_MAX == iEndIndex  ){
            iEndIndex  = 0;
          }

          // unfortunately some loops [formed by leaving the solid] 
          //  are [incorrectly] added CCW, fix that
          pPolyIntersectionPoints->sortIntersectionsCCW(
                                                         &loopIntersectionPoints
                                                       , pPlaneStepOnNegFeature
                                                       , pPlaneStepOnPosFeature 
                                                       , bGapsEncountered
                                                     //, true // because we are creating a hole      
                                                       );
//        }// fi NULL == pLoopXPts
//        else {
//          TRACE0("pPlaneStepOnNegFeature not found\n");
//        }
        }// next ib

        
      }//fi
    delete pIntersection;
    }//fi
  }//fi

  condenseArray();// wh 01/20/02

  return S_OK;
}

// here we intersect the outside bounds with the candidate inside bound
// Doing this is a two step process.  
// First, the intersection-points must be trimmed down to exist only 
//   within the face_outer_bound.
// Once that is finished, if the two bounds have common edges, the edges must be removed and the 
//  two face bounds are combined into one common FOB.  
// Sometimes, this will result in a face being split into two disjoint FOB s.
// should do the math in uv space instead of xyz
HRESULT step::boundsXboundsFaceted( CFace_surfaceStep*      pFace_surfaceStepOnPosFeature, // positive features's face
                                    boundsIntersectBounds&  rBoundsXbounds,
                                    CrcPtrArray*            pPolyIntersectionPoints )// intersection point on 
                                                                          //  polygon of pFace_surfaceStepOnPosFeature
{  
  double dStartParam =  DBL_MAX;
  double dEndParam   = -DBL_MAX;

  CFace_outer_boundStep* pFace_outer_boundStep= (CFace_outer_boundStep*)
    pFace_surfaceStepOnPosFeature->GetFace_outer_bound();
  CPoly_loopStep* pPLoop = dynamic_cast<CPoly_loopStep*>(pFace_outer_boundStep->m_bound);

  CPlaneStep* pPlaneStepOnPosFeature = dynamic_cast<CPlaneStep*>
    (pFace_surfaceStepOnPosFeature->m_pFace_geometry);
  CDirectionStep* pFaceNormal = pPlaneStepOnPosFeature->m_pPosition->m_pAxis;

  CCartesian_pointStep* pLast_point =  (CCartesian_pointStep* )
    pPolyIntersectionPoints->GetAt( 
      pPolyIntersectionPoints->GetSize()-1);
  containment cPreviousContains= unknownContainment;
  double rdParam0;
  pFace_outer_boundStep->convexContains( 
    pLast_point, 
    cPreviousContains, 
    pFaceNormal 
    , rdParam0
    );

  for (int jv = 0; jv < pPolyIntersectionPoints->GetSize(); ){

    containment cContains;
    double rdParam;
    pFace_outer_boundStep->convexContains( 
      (CCartesian_pointStep* )pPolyIntersectionPoints->GetAt(jv), 
      cContains, 
      pFaceNormal 
      , rdParam                    
      );

    bool bTransition = 
      (out == cPreviousContains) && ( out != cContains);
    bTransition = bTransition  || 
      (out != cPreviousContains) && ( out == cContains);

    if (bTransition) {
      CVectorStep* pVectorStep= new 
        CVectorStep( *(CCartesian_pointStep* )pPolyIntersectionPoints->GetAt(jv), 
                     *pLast_point );
      if (NULL == pVectorStep) {
        return E_OUTOFMEMORY;
      }
      bool bWithin = false;
      pVectorStep->withinTol(bWithin);
      if (!bWithin ){
        CLineStep * pLineStep =  new 
          CLineStep( *(CCartesian_pointStep* )pPolyIntersectionPoints->GetAt(jv), 
                      *pVectorStep, pLast_point);
        if (NULL == pLineStep) {
          delete pVectorStep;
          return E_OUTOFMEMORY;
        }

        CrcPtrArray outerboundInteriorPoints ;
        CDWordArray   pIntersectionParam ;//= new double[pPLoop->m_aPolygonVertices.GetSize()] ;
        pIntersectionParam.SetSize(pPLoop->m_aPolygonVertices.GetSize(), 0);
        int id = 0;
        int ivm1 = pPLoop->m_aPolygonVertices.GetSize()-1; 
        for (int iv = 0; iv < pPLoop->m_aPolygonVertices.GetSize(); iv++){
          
          CrcPtrArray outerboundIntersectionPoints ;
          intersectionType intersection0 = unknownSegmentIntersection; 
          intersectionType intersection1 = unknownSegmentIntersection;

          int iBefore = outerboundIntersectionPoints.GetSize();
          lineEdgeGlanceFaceted( ivm1, iv, pPLoop, dStartParam, dEndParam, 
            pLineStep, &outerboundIntersectionPoints , intersection1, 
                                     intersection0);

          //watch it, we only care about interior intersection pts
          if (interiorIntersection == intersection1 ){
            pPLoop->m_aPolygonVertices.InsertAt( iv++, outerboundIntersectionPoints.GetAt(0) );
          }
          if (interiorIntersection == intersection0){
            pIntersectionParam.SetAt(id++, (DWORD)dStartParam);
            outerboundInteriorPoints.Add( outerboundIntersectionPoints.GetAt(0));
          }
          ivm1 = iv;
        }// next iv

        for   (int j=0; j < outerboundInteriorPoints.GetSize(); j++) {
          int     iCurMin=0;
          double  dMinParam = (double  )pIntersectionParam.GetAt(0);
          for (int i = 1; i < outerboundInteriorPoints.GetSize(); i++){
            if (dMinParam > (double  )pIntersectionParam.GetAt(i)) {
              iCurMin = i;
              dMinParam = (double  )pIntersectionParam.GetAt(i);
            }// fi
          }// next i
          // once all the intersections are found, they have to be inserted into the list CW
          if ((double  )pIntersectionParam.GetAt(iCurMin) > restol) {
            if ((double  )pIntersectionParam.GetAt(iCurMin) < (1.0e0 - restol)) {
              pPolyIntersectionPoints->InsertAt( jv++, outerboundInteriorPoints.GetAt(iCurMin) );
            }
            else {
            //  also a pain
              pPolyIntersectionPoints->InsertAt( jv++, outerboundInteriorPoints.GetAt(iCurMin) );
            }
          } else {
            // pain because it intersects at the corner, 
            //  hence you have to decide whether to insert at jv-1 or jv 
            pPolyIntersectionPoints->InsertAt( jv++, outerboundInteriorPoints.GetAt(iCurMin) );
          }
          outerboundInteriorPoints.SetAt( iCurMin, (void*)0) ;
          pIntersectionParam.SetAt(iCurMin, DWORD((double)pIntersectionParam.GetAt(iCurMin) + 2.));
        }// next j

        pIntersectionParam.SetSize(0);
      
        delete pLineStep;// wh 10/04/01
      } else {
    
        // remove the point??
        if (0<jv){  
          pPolyIntersectionPoints->RemoveAt( jv);
          jv--;
        } else { 
          pPolyIntersectionPoints->RemoveAt( 
            pPolyIntersectionPoints->GetSize()-1);
        }
      }
      delete pVectorStep;
    }//bTransition
    pLast_point = (CCartesian_pointStep*)
      pPolyIntersectionPoints->GetAt(jv);
    if (out == cContains) {  
      pPolyIntersectionPoints->RemoveAt(jv);
//    ASSERT( pPolyIntersectionPoints->GetSize()>0);
    } else {
      jv++;
    }
    cPreviousContains = cContains;
  }// next iv
  if (pPolyIntersectionPoints->GetSize() > 2) {
    rBoundsXbounds = commonVertexInside;
  } 
  //else { 
  //rBoundsXbounds = commonVertexOutside;// wh 10/07/01
  //}
  return S_OK;
}


// Perform the surface-surface intersection.
// We do not intersect two nonexistant surfaces, 
//  this is a good thing I hope, can you think of cases where its not?
// Several cases can occur
//  1.  Negative Feature exists completely inside a positive feature, 
          //  hence we get an inside void on a new shell, 
          //  in advanced_brep we get two oriented_closed_shell, 
          //  outside one is positive, inside one is negative.
//  2.  Negative feature intersects just one face and becomes attached to the shell.
//  2b. Negative feature intersects two disjoint faces on the same shell, creates a hole.
//  3.  Negative feature intersects two adjoining faces [on the same shell], eats away a chunk.
//  3b. Negative feature divides a face, creates multiple lumps.
//  4.  Negative feature intersects two disjoint faces [on different shell], 
          //joins two shells, no hole, rather a tunnel between the shells.

HRESULT step::surfXsurfFaceted( agitoAssembly*                 pAssembly// collection of all parts
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
                              )
{
  int ISO = pPolygonOnPosFeature->MemberOfSurface;
  if (-1 != ISO){
    CSurface* pSurfOnPosFeature= (CSurface*) GetScribView()->m_surfacearray.GetAt( ISO);
    // only for surf which exist
    if (0 != pSurfOnPosFeature->exists){

        // carve out the inside polygons
      if (-1 != pNegThing->firstpolyno) {

        bool bGapsEncountered = false;
        // hold onto the set of intersection points

        CPoly_loopStepEx polyIntersectionPoints;
        polyIntersectionPoints.m_aPolygonVertices.SetSize( 0, GetScribView()->m_polygonarray.GetSize());//wh 06/04/01

        int iLastSurfaceNo = -1;
        // false assumption here in that the polygons are a part of the poly loop, and that neighbooring ones touch!!!!!
        for ( int ipn = pNegThing->firstpolyno; ipn <= pNegThing->lastpolyno; ipn++){
          bool bIntersect = false;// used to weed out spurious intersections
          CPolygon* pPolygonInside = (CPolygon*) GetScribView()->m_polygonarray.GetAt(ipn);
          int isi = pPolygonInside->MemberOfSurface;
          if (-1 != isi){
            CSurface* pSurfInside    = (CSurface*) GetScribView()->m_surfacearray.GetAt( isi);

            // only for surf which exist
            if (0 != pSurfInside->exists){         

//              loopXPts* ploopXPts = new loopXPts;
//              aLoopXPointArray.Add( ploopXPts );
//              int ifac = (int) CConnected_face_setStep::map_face.GetAt(ipn);
              CFace_surfaceStep *pFace_surfaceStep = (CFace_surfaceStep*) 
                pFace_surfaceStepPtrArray->GetAt(ipn);// wh 02/18/02
              ASSERT_VALID( pFace_surfaceStep);
//              ploopXPts->m_pPlaneStepOnNegFeature = dynamic_cast<CPlaneStep*> 
//                (pFace_surfaceStep->m_pFace_geometry);

//            ASSERT( isi == ifac );// each owning surface should be different!
              iLastSurfaceNo = isi;
              
              polyXpolyBBFaceted( ipp, 
                                  ipn,
                                  &polyIntersectionPoints , 
                                  bGapsEncountered, 
                                  pFace_surfaceStepPtrArray, 
                                  bIntersect ,
                                  pShell
                                , pCartesian_pointStepPtrArray
                              //, rNegThingsList
                                );
            }//fi
          }//fi

          if (!bIntersect){
            //polyIntersectionPoints.RemoveAll();
          }
        }//next ipn
 
        polyIntersectionPoints.move( NULL);  // wh 03/05/02
        polyIntersectionPoints.simplify();
        // worry about wrap around
        if (1 // wh 7/09/01
              < polyIntersectionPoints.GetSize()) {
          if ( polyIntersectionPoints.GetAt(0) == 
               polyIntersectionPoints.GetAt(polyIntersectionPoints.GetSize()-1) )
          {
            polyIntersectionPoints.m_aPolygonVertices.RemoveAt( polyIntersectionPoints.GetSize()-1);
          }
          else {
            CDirectionStep* pDirNeg = new 
             CDirectionStep( NULL, 
               *(CCartesian_pointStep*)polyIntersectionPoints.GetAt( polyIntersectionPoints.GetSize()-1),
               *(CCartesian_pointStep*)polyIntersectionPoints.GetAt( 0));
            if (NULL==pDirNeg) {
              return E_OUTOFMEMORY;
            }//wh 10/17/01
            if (pDirNeg->getLength2() < restol2) {
              polyIntersectionPoints.m_aPolygonVertices.RemoveAt( polyIntersectionPoints.GetSize()-1);
            } 
            ASSERT_VALID(pDirNeg);
            delete pDirNeg;// wh 10/06/01
          }
        }

        try {
          CFace_surfaceStep *pFace_surfaceStepOnPosFeature = (CFace_surfaceStep *)
            pFace_surfaceStepPtrArray->GetAt(ipp);
          // create a poly loop which describes the intersection
          if ( 
              2 // was 0  // wh 5/25/01
                < polyIntersectionPoints.GetSize()){
            CPoly_loopStep *pPoly_loopStepIntersection = new 
              CPoly_loopStep( (CPointStep*)polyIntersectionPoints.GetAt(0), 
                              (CPointStep*)polyIntersectionPoints.GetAt(1), 
                              (CPointStep*)polyIntersectionPoints.GetAt(2)
                            , polyIntersectionPoints.GetSize());
            if (NULL==pPoly_loopStepIntersection) {
              return E_OUTOFMEMORY;
            }// wh 10/17/01
            if (bGapsEncountered) {
              pPoly_loopStepIntersection->m_bGap = true;
            }
            for (int i = 3; i < polyIntersectionPoints.GetSize(); i++){
              CPointStep*pIn = ( (CPointStep*) polyIntersectionPoints.GetAt(i));
              pPoly_loopStepIntersection->SetAt( i, pIn);
            }

            //need to make sure that [inner]bound is inside outer_bound
            // TBD
            boundsIntersectBounds boundsXbounds = unknownBoundsIntersection;

            boundsContainBoundsFaceted(  pFace_surfaceStepOnPosFeature
                                      , boundsXbounds
                                      , &polyIntersectionPoints 
                                      );

            // need to make sure that [inner]bounds does not intersect with outer_bound, 
            //   if it does , then need to stitch them together!
            if (intersectionBounds == boundsXbounds)
            {
              // merge together the two bounds
              //pFace_surfaceStepOnPosFeature->bounds->GetAt(0);

              // wh 11/01/01
//            #define MERGE_BOUNDS_INTERSECTION false
              // gives good results, 
              // but memory problems in that some dependent entities are prematurely deleted, 
              // while still referenced!

              #ifdef MERGE_BOUNDS_INTERSECTION 
              {
                boundsXboundsFaceted( pFace_surfaceStepOnPosFeature ,
                                      boundsXbounds,
                                      &(pPoly_loopStepIntersection->m_aPolygonVertices));
                if (NULL != pPoly_loopStepIntersection){
                  pFace_surfaceStepOnPosFeature->makeIslands( pPoly_loopStepIntersection);
                }
              }
              #endif//MERGE_BOUNDS_INTERSECTION 
            }
            else if (disjointBounds == boundsXbounds)            {          
              //make sure bound is thrown away  
            }
            else if (insideBounds   == boundsXbounds)            {   
//            TRACE0("inside bound\n");
            }
            else if (outsideBounds  == boundsXbounds)            {
              #ifdef  MERGE_BOUNDS_INTERSECTION 
              {

              //replace outside bounds by inside bounds   
              if (1 < pFace_surfaceStepOnPosFeature->GetSize() ) {
                CFace_boundStep* pFace_boundStep = 
                  pFace_surfaceStepOnPosFeature->GetAt(1);
                CLoopStep* pLoopStep = pFace_boundStep->m_bound;
                CPoly_loopStep *pPoly_loopStep = dynamic_cast<CPoly_loopStep*>( pLoopStep);
                if (NULL != pPoly_loopStep ){
                  pPoly_loopStep->replace( pPoly_loopStepIntersection);
                }
              } else {
                CFace_boundStep* pFace_boundStep =  
                    new CFace_boundStep(  NULL, 
                                          pPoly_loopStepIntersection, 
                                          true, 
                                          NULL);
                pFace_surfaceStepOnPosFeature->Add( pFace_boundStep);
                pPoly_loopStepIntersection->addRef(); // wh 01/27/02
              }
            }
            #endif//MERGE_BOUNDS_INTERSECTION 
           }
#if 0
            if ( (commonVertexInside == boundsXbounds)    ) 
            {
              CFace_boundStep* pFace_boundStep = (CFace_boundStep* )
                pFace_surfaceStepOnPosFeature->GetFace_outer_bound();                

              pFace_surfaceStepOnPosFeature->makeIslands(pPoly_loopStepIntersection);
            } 
            else 
            if ( (edgeScrapesInside  == boundsXbounds)    ) 
            {
              CFace_boundStep* pFace_boundStep = (CFace_boundStep* )
                pFace_surfaceStepOnPosFeature->GetFace_outer_bound();                
              // more sophisticated in that it also removes an edge
              pFace_surfaceStepOnPosFeature->makeIslands(pPoly_loopStepIntersection);
            }
#endif            
            // be careful and throw out [inner]bound outside the outer bounds!
            if ( (insideBounds       == boundsXbounds) || 
                 (commonVertexInside == boundsXbounds) || 
                 (edgeScrapesInside  == boundsXbounds)    ) 
            {
              CFace_boundStep* pFace_boundStep =  
                  new CFace_boundStep(  NULL, 
                                        pPoly_loopStepIntersection, 
                                        true //wh 05/21/01 since edges are oriented CW
                                        //,NULL
                                        );
              if (NULL==pPoly_loopStepIntersection) {
                return E_OUTOFMEMORY;
              }// wh 10/17/01
              int ifb = 0;
              pFace_surfaceStepOnPosFeature->AddFB( pFace_boundStep, ifb);
//            pFace_surfaceStepOnPosFeature->Add( pFace_boundStep);
            } 
            else 
            { 
              pPoly_loopStepIntersection->release(); // wh 10/09/01
              pPoly_loopStepIntersection=NULL;   // wh 10/09/01
            }
          }          // Xpoints  
          else { 
//          ASSERT( 0 == polyIntersectionPoints.GetSize() );// wh 10/09/01
          }
        }
        catch(...){
          ASSERT(false);
#ifdef  EXPOSE      
          fprintf( g_errorLog, "error while computing m_polygonarray[ %d]\n", ipn );
#endif//EXPOSE   

        }
//        for ( int ik=0; ik < aLoopXPointArray.GetSize(); ik++){
//          loopXPts * pLoopXPts = aLoopXPointArray.GetAt(ik);
//        delete pLoopXPts->loopIntersectionPoints;
//          delete pLoopXPts;
//        }// next ik
//        aLoopXPointArray.SetSize(0);
      }//fi
    }//fi
  }// isp    
  return S_OK;
}

////
//1.For each CThing in m_thingarray
//2.    If the CThing has at least one CSurface
//3.        If one or more CSurface.exists==0.0
//4.            For each CPolygon in m_polygonarray
//5.                If the Cpolygon.MemberOfObject != CThing from (1.)
//6.                    For each CPolygon in CThing from (1.)
//7.                        Create a temporary polygon comprised of the
//                          intersection of the Cpolygon from (6.) with the plane from the Cpoly in (4.)
//8.                            The temporary polygon from (7.) is removed
//from the CPolygon in(4.) //the hard part!
//
//Creating the temproary polygon may not be too difficult as the m_*arrays are
//all in order of their creation, so they should therefore either align
//sequentially in either CCW or CW order, can end up either way. Removing the
//temporary polygon is easy if it is incribed (it is therefore simply the
//inner loop) , and if not, the resultant polygon needs to be tessalated so as
//to always be convex.
////

// find the negative features based on the exists param
HRESULT step::findNegFeatureFaceted( agitoAssembly* pAssembly,// 
                                     agitoComponent&     aNegativeComponents,
                                     CPtrArray*&    pFace_surfaceStepPtrArray
                                    ,CCartesian_pointStepPtrArray*& pCartesian_pointStepPtrArray 
                                   )
{
#if     NOTIFICATION 
  if (m_bWriteFile){
    this->GetScribView()->Notify("Finding Negative Features");}
#endif//NOTIFICATION 
  //thingList rNegThingsList;
  for ( int it = 0; it < GetScribView()->m_thingarray.GetSize(); it++ ) {
    CThing* pThing = (CThing*) GetScribView()->m_thingarray.GetAt(it);
    agitoPart* pPart = (agitoPart* )pAssembly->GetAt( pThing->BelongsToModelNo);
    ASSERT( 0 == pThing->BelongsToModelNo);
    agitoComponent* pLump = (agitoComponent* )pPart->GetAt( 0);
    agitoFeature* pFeature = (agitoFeature* )pLump->GetAt( it);// fails for multi-parts
     
    pFeature->m_bFeatureAdded = false;
    // find the negative feature
    if (-1 != pThing->firstpolyno) 
    for ( int ip = pThing->firstpolyno; ip <= pThing->lastpolyno; ip++){
      CPolygon *pPolygon= (CPolygon *)GetScribView()->m_polygonarray.GetAt(ip);
      if (-1 != pPolygon->MemberOfSurface){
        CSurface* pSurface= (CSurface*) GetScribView()->m_surfacearray.GetAt(pPolygon->MemberOfSurface);
        if (0.0 == pSurface->exists){

          if (!pFeature->m_bFeatureAdded){
            aNegativeComponents.Add( pFeature);
            pFeature->negate();
            pFeature->m_bFeatureAdded= true;
          }

          // need to delete the nonexistant surface from the shell!
          CClosed_shellStep* pShell = (CClosed_shellStep* ) pFeature->GetAt(0);

          pThing->m_pFacetedPool->AddStep(  pShell);
          pShell->m_pTechnadrawEntitites->AddTech( pThing);

          int jp = ip;

          jp = (int) pShell->map_face.GetAt(ip);
          // remove face from the shell
          CFace_surfaceStep *pFace_surfaceStep = (CFace_surfaceStep *)
            pShell->m_pCFS_faces->GetAt( jp); // wh 10/02/01            
          pShell->m_pCFS_faces->SetAt( jp, NULL);
          ASSERT_VALID( pFace_surfaceStep);
          pFace_surfaceStep->release();//wh   10/02/01
        }//
      }
    }
    // 
  }

  intersectNegFeatureFaceted( pAssembly
                            , pFace_surfaceStepPtrArray
                            , pCartesian_pointStepPtrArray   
                            );
  return S_OK;
}

    // now find the intersections of this CThing's surfaces with surfaces of other CThings
HRESULT step::intersectNegFeatureFaceted( agitoAssembly*                 pAssembly
                                        , CPtrArray*&                    pFace_surfaceStepPtrArray
                                        , CCartesian_pointStepPtrArray*& pCartesian_pointStepPtrArray 
                                        )
{
  for ( int it = 0; it < GetScribView()->m_thingarray.GetSize(); it++ ) {
    CThing* pThing = (CThing*) GetScribView()->m_thingarray.GetAt(it);
    agitoPart* pPart = (agitoPart* )pAssembly->GetAt( pThing->BelongsToModelNo);
    ASSERT( 0 == pThing->BelongsToModelNo);
    agitoComponent* pLump = (agitoComponent* )pPart->GetAt( 0);
    agitoFeature* pFeature = (agitoFeature* )pLump->GetAt( it);// fails for multi-parts
    CClosed_shellStep* pShell=NULL;// for the time being// wh 7/15/01
    if (pFeature->m_bFeatureAdded){
      thingXthingBBFaceted( pAssembly, it, pThing,
                            pFace_surfaceStepPtrArray ,
                            pShell
                          , pCartesian_pointStepPtrArray 
                          );
    }
  }
  return S_OK;
}


// build the shells from the faces in the assembly
HRESULT step::buildShellsFaceted( FILE*                 stream, 
                                  stepArchive &         ar,
                                  CPtrArray*&           pPoly_loopPtrArray, 
                                  CRepresentationStep*& pRepresentationStep , 
                                  surfaceModelSelect    lSurfaceModelSelect,
                                  CPtrArray*&           pFace_surfaceStepPtrArray
                                , CCartesian_pointStepPtrArray*& pCartesian_pointStepPtrArray
                                )
{ 
#if     NOTIFICATION 
  if (m_bWriteFile){
    GetScribView()->Notify("(40%) step::buildShellsFaceted");
  }
#endif//NOTIFICATION 

#ifdef  SHOWPROGRESS
  if (m_bWriteFile){
    GetScribView()->progressBarUpdate( 40);
  }
#endif//SHOWPROGRESS

  agitoAssembly assembly;// a part (model) has features (things)
  HRESULT hr  = 
  connectFacesFaceted( &assembly, 
                       pFace_surfaceStepPtrArray);
  if (FAILED( hr)){
    return hr;
  }
// commented out until it works // wh 7/17/01
#ifdef  _LAYER
  // suppress those features & parts that are not to be output!
  supressLayersFaceted( pPoly_loopPtrArray        ,       
                        pRepresentationStep       ,
                        lSurfaceModelSelect       ,
                        pFace_surfaceStepPtrArray , 
                        &assembly 
                      );
#endif//_LAYER

//m_ptrArrayAgito.SearchFromTheTop(); // wh 7/11/01
  //then remove features and add positive features
  agitoComponent aNegativeFeatures ;
  // go thru the list of features, and classify them, and add em to the correct list

  // turned off until the polyloops of neg feature are oriented CW & 
  //each edge if facing the correct way as well!
  findNegFeatureFaceted( &assembly
                       , aNegativeFeatures
                       , pFace_surfaceStepPtrArray
                       , pCartesian_pointStepPtrArray
                       );

  CTime theTime;
  theTime = CTime::GetCurrentTime(); 
  iraroArchive* p_ir = (iraroArchive*) ar.m_archives.GetAt(0);
  iraroArchive& ir = *p_ir;
  ir << "\n/* time when findNegFeature ";
  ir << theTime.Format(" %Y-%m-%d T%H:%M:%S*/\n");       
  
  addEulerFaceted( &assembly, aNegativeFeatures);
#if     NOTIFICATION 
  if (m_bWriteFile){
    GetScribView()->Notify("(49%) Faceted CRepresentationStep::Serialize ");}
#endif//NOTIFICATION 

#ifdef  SHOWPROGRESS
  if (m_bWriteFile){
    GetScribView()->progressBarUpdate( 49);}
#endif//SHOWPROGRESS

  buildAssembliesFaceted( ar, &assembly, pRepresentationStep );

  try {
    for ( int im =0; im < assembly.GetSize(); im++ ) {
      agitoPart* pPart= (agitoPart*)assembly.GetAt( im);
      for ( int ip =0; ip < pPart->GetSize(); ip++ ) {
        agitoComponent* pLump = (agitoComponent*)pPart->GetAt(ip);
        for ( int il =0; il < pLump->GetSize(); il++ ) {
          agitoFeature* pFeature = (agitoFeature*)pLump->GetAt( il);
          delete pFeature ;
        }
        delete pLump;
      }
      delete pPart;
    }
  }
  catch(...){
  }
#if     NOTIFICATION 
  if (m_bWriteFile){
    GetScribView()->Notify("(99%) returned with Faceted CRepresentationStep::Serialize ");}
#endif//NOTIFICATION 

#ifdef  SHOWPROGRESS
  if (m_bWriteFile){
    GetScribView()->progressBarUpdate( 99);}
#endif//SHOWPROGRESS
  return S_OK;
}

HRESULT step::preShellsFaceted( FILE*                 stream, 
                                  stepArchive &         ar,
                                  CPtrArray*&           pPoly_loopPtrArray, 
                                  CRepresentationStep*& pRepresentationStep , 
                                  surfaceModelSelect    lSurfaceModelSelect,
                                  CPtrArray*&           pFace_surfaceStepPtrArray
                              , CCartesian_pointStepPtrArray*& pCartesian_pointStepPtrArray
                              )
{ 
#if     NOTIFICATION 
  if (m_bWriteFile){
    GetScribView()->Notify("(40%) step::buildShellsFaceted");}
#endif//NOTIFICATION 

#ifdef  SHOWPROGRESS
  if (m_bWriteFile){
    GetScribView()->progressBarUpdate( 40);}
#endif//SHOWPROGRESS

  agitoAssembly assembly;// a part (model) has features (things)
  HRESULT hr  = 
  connectFacesFaceted( &assembly, 
                       pFace_surfaceStepPtrArray);
  if (FAILED( hr)){
    return hr;
  }
// commented out until it works // wh 7/17/01
#ifdef  _LAYER
    // suppress those features & parts that are not to be output!
    supressLayersFaceted( pPoly_loopPtrArray        ,       
                          pRepresentationStep       ,
                          lSurfaceModelSelect       ,
                          pFace_surfaceStepPtrArray , 
                          &assembly );
#endif//_LAYER

//m_ptrArrayAgito.SearchFromTheTop(); // wh 7/11/01
  //then remove features and add positive features
  agitoComponent aNegativeComponents ;
  // go thru the list of features, and classify them, and add em to the correct list
    
    
      // turned off until the polyloops of neg feature are oriented CW & 
      //each edge if facing the correct way as well!
      findNegFeatureFaceted( &assembly, aNegativeComponents, pFace_surfaceStepPtrArray
        ,  pCartesian_pointStepPtrArray
        );
      if (m_bWriteFile) 
      {
        CTime theTime;
        theTime = CTime::GetCurrentTime(); 
        iraroArchive* p_ir = (iraroArchive*) ar.m_archives.GetAt(0);
        iraroArchive& ir = *p_ir;
        ir << "\n/* time when findNegFeature ";
        ir << theTime.Format(" %Y-%m-%d T%H:%M:%S*/\n");       
      }
    
    addEulerFaceted( &assembly, aNegativeComponents);
#if     NOTIFICATION 
  if (m_bWriteFile)
    GetScribView()->Notify("(49%) Faceted CRepresentationStep::Serialize ");
#endif//NOTIFICATION 

#ifdef  SHOWPROGRESS
  if (m_bWriteFile)
      GetScribView()->progressBarUpdate( 49);
#endif//SHOWPROGRESS

    preAssembliesFaceted( ar, &assembly, pRepresentationStep );

    try {
      for ( int im =0; im < assembly.GetSize(); im++ ) {
        agitoPart* pPart= (agitoPart*)assembly.GetAt( im);
        for ( int ip =0; ip < pPart->GetSize(); ip++ ) {
          agitoComponent* pLump = (agitoComponent*)pPart->GetAt(ip);
          for ( int il =0; il < pLump->GetSize(); il++ ) {
            agitoFeature* pFeature = (agitoFeature*)pLump->GetAt( il);
            delete pFeature ;
          }
          delete pLump;
        }
        delete pPart;
      }
    }
    catch(...){

    }
#if     NOTIFICATION 
  if (m_bWriteFile)
    GetScribView()->Notify("(99%) returned with Faceted CRepresentationStep::Serialize ");
#endif//NOTIFICATION 

#ifdef  SHOWPROGRESS
  if (m_bWriteFile)
  GetScribView()->progressBarUpdate( 99);
#endif//SHOWPROGRESS
  return S_OK;
}

// connnect the faces and shells together
HRESULT step::connectFacesFaceted( agitoAssembly* pAssembly, 
                                   CPtrArray*& pFace_surfaceStepPtrArray )
{
  for ( int im =0; im <  GetScribView()->m_modelarray.GetSize();im++ ) {
    CModel* pModel= (CModel* )GetScribView()->m_modelarray.GetAt(im);
    if (pModel->on){
      agitoComponent* pLump= new agitoComponent;// a lump has features (things)
      if (NULL==pLump){
        return E_OUTOFMEMORY;
      }
      agitoPart* pPart= new agitoPart;// a part (model) has lumps
      if (NULL==pPart){
        return E_OUTOFMEMORY;
      }
      pPart->Add(pLump);
      pAssembly->Add( (LPVOID) pPart);
    }
  }// next im

  CConnected_face_setStep::map_part.SetSize(    GetScribView()->m_polygonarray.GetSize());
  CConnected_face_setStep::map_lump.SetSize(    GetScribView()->m_polygonarray.GetSize());
  CConnected_face_setStep::map_feature.SetSize( GetScribView()->m_polygonarray.GetSize());
  CConnected_face_setStep::map_shell.SetSize(   GetScribView()->m_polygonarray.GetSize());
  CConnected_face_setStep::map_face.SetSize(    GetScribView()->m_polygonarray.GetSize());
//CConnected_face_setStep::map_surface.SetSize( GetScribView()->m_polygonarray.GetSize());// wh 02/19/02

// connectFaces, extract transform for CThing
  //prepThing
// maybe we should set up a dummy thing which holds all unaccounted for things living in space
  if (0 == GetScribView()->m_thingarray.GetSize()) {
    // created because we are outputting both cfs & shell
    CConnected_face_setStep *pConnected_face_setStep = 
      new CConnected_face_setStep( NULL, NULL);
    if (NULL==pConnected_face_setStep ){
      return E_OUTOFMEMORY;
    }

    // be careful, there can be many shells
    CClosed_shellStep *pShellStep = 
      new CClosed_shellStep( pConnected_face_setStep, pFace_surfaceStepPtrArray );
    if (NULL==pShellStep) {
      return E_OUTOFMEMORY;
    }// wh 10/17/01

    pShellStep->m_bProgressed = false;
//  pShellStep->demote();// treat all shells as open until everything works // wh 6/28/01
    agitoFeature* pFeature= new agitoFeature;
    if (NULL==pFeature){
      return E_OUTOFMEMORY;
    }
    pFeature->Add(pShellStep);
    agitoPart* pPart = (agitoPart* )pAssembly->GetAt(0);
    agitoComponent* pLump = (agitoComponent* )pPart->GetAt(0);
    pLump->Add((LPVOID)pFeature);

    for (int i = 0; i<GetScribView()->m_polygonarray.GetSize(); i++){
      pShellStep->map_face.SetAt(i, (void*)i);
      CConnected_face_setStep::map_shell.SetAt( i, (void*)0);
//    CConnected_face_setStep::map_surface.SetAt( i, (void*)i);
    }

  }
  else{
  // first set up the transforms, 
    for ( int it =0; it < GetScribView()->m_thingarray.GetSize();it++ ) {

      CPtrArray*      pFace_surfaceStepPtrArrayOnfeature = new CPtrArray;
      if (NULL==pFace_surfaceStepPtrArrayOnfeature ){
        return E_OUTOFMEMORY;
      }
      CThing* pThing = (CThing*)GetScribView()->m_thingarray.GetAt(it);

      agitoFeature* pFeature = new agitoFeature;// the features have shells 
      if (NULL==pFeature) {
        return E_OUTOFMEMORY;
      }// wh 10/17/01

      // created because we are outputting both cfs & shell
      CConnected_face_setStep *pConnected_face_setStep = 
        new CConnected_face_setStep( NULL, NULL);// wait until you find out where the surfaces go
      if (NULL==pConnected_face_setStep ){
        return E_OUTOFMEMORY;
      }

      pThing->m_pFacetedPool->AddStep(  pConnected_face_setStep);
      pConnected_face_setStep->m_pTechnadrawEntitites->AddTech(pThing);

      // be careful, there can be many shells
      CClosed_shellStep *pShellStep = NULL;
      // use Euler-Poincare formula to determine if its open or closed
//    bLayerSuppressed =? v-e+f-r==2*(s-h): ;
      // see CRepresentation_itemStep::writeEulerNum

      {
        pShellStep =
        new CClosed_shellStep( pConnected_face_setStep, pFace_surfaceStepPtrArrayOnfeature);
      // leaking wh 7/9/01
//      pShellStep->demote();// treat all shells as open until everything works // wh 6/28/01
        if (NULL==pShellStep ){
          return E_OUTOFMEMORY;
        }

        pThing->m_pFacetedPool->AddStep(  pShellStep);
        pShellStep->m_pTechnadrawEntitites->AddTech( pThing);

        pShellStep->m_bProgressed = false;

      }

      int iModel = pThing->BelongsToModelNo;
      ASSERT( -1 != iModel );// nested things??
      CModel* pModel = (CModel*)GetScribView()->m_modelarray.GetAt(iModel);
      if ( pModel->on)
      {
        pFeature->Add( pShellStep);

        agitoPart* pPart = (agitoPart* ) pAssembly->GetAt( pThing->BelongsToModelNo);
        agitoComponent *pLump = (agitoComponent*) pPart->GetAt(0);
        int iFeature = pLump->Add( (LPVOID) pFeature); 

        bool bTrans = false;
        if (false){
          bTrans =   bTrans &&       ((pThing->Xmove)>restol);
          bTrans =   bTrans &&       ((pThing->Ymove)>restol);
          bTrans =   bTrans &&       ((pThing->Zmove)>restol);
          bTrans =   bTrans &&       ((pThing->Xrot )>restol);
          bTrans =   bTrans &&       ((pThing->Yrot )>restol);
          bTrans =   bTrans &&       ((pThing->Zrot )>restol);
        }

        if (false){
          CCartesian_tranformation_operator_3dStep *pCartesian_tranformation_operator_3dStep = new 
            CCartesian_tranformation_operator_3dStep( 
              pThing->Xmove, 
              pThing->Ymove, 
              pThing->Zmove);
          if (NULL==pCartesian_tranformation_operator_3dStep ){
            return E_OUTOFMEMORY;
          }
          pCartesian_tranformation_operator_3dStep->rotate(
                  pThing->Xrot,  
                  pThing->Yrot,  
                  pThing->Zrot);
// this applies to the Technadraw view
//  #pragma message("\nHow do you know whether to rotate first and then move or vis versa.  MSG FROM(" __FILE__ ")\n")
          if (NULL != pPart->m_pCartesian_tranformation_operator_3dStep ){
            pPart->m_pCartesian_tranformation_operator_3dStep->release();
          }
          pPart->m_pCartesian_tranformation_operator_3dStep = pCartesian_tranformation_operator_3dStep;
//        pCartesian_tranformation_operator_3dStep->addRef();
        }

        if (-1 != pThing->firstpolyno) {          
          if (-1 != pThing->lastpolyno) {
            for (int j = pThing->firstpolyno; 
                      j 
                        <= 
                        pThing->lastpolyno; j++) {



              if ( ((GetScribView()->m_polygonarray.GetSize()) <= j) ||
                   (    (pFace_surfaceStepPtrArray->GetSize()) <= j)
                ) {
                  return E_FAIL;
              }
              
              CPolygon *pPolygon=(CPolygon *) (GetScribView()->m_polygonarray.GetAt(j));
              ASSERT( NULL!=pPolygon);
              if (NULL==pPolygon){
                  return E_FAIL;
              }
              else {
                ASSERT_VALID( pPolygon);
              }
              CFace_surfaceStep*  pFace_surfaceStep = (CFace_surfaceStep*)
                (pFace_surfaceStepPtrArray->GetAt( j));
              ASSERT(NULL!=pFace_surfaceStep);
              if (NULL!=pFace_surfaceStep)
              {
                ASSERT_VALID( pFace_surfaceStep);
              
                ASSERT( it == pPolygon->MemberOfObject);
  //            pConnected_face_setStep->m_pCFS_faces = pFace_surfaceStepPtrArrayOnfeature;// not needed anymore
                int i = pFace_surfaceStepPtrArrayOnfeature->Add( pFace_surfaceStep );
                pShellStep->map_face.SetAt( j, (void*)i);
                CConnected_face_setStep::map_shell.SetAt( j, (void*)it);
                CConnected_face_setStep::map_feature.SetAt( j, (void*) iFeature);// wh 7/16/01
  //            CConnected_face_setStep::map_surface.SetAt( j, (void*)i);
              } else {
//                pShellStep->map_face.SetAt( j, (void*)-1);
//                CConnected_face_setStep::map_shell.SetAt( j, (void*)-1);
//                CConnected_face_setStep::map_feature.SetAt( j, (void*)-1);// wh 7/16/01
//              return E_FAIL;
              } 
            }// next j
          }// fi
        }// fi
      }// fi

    }// next it
  }
  return S_OK;
}

HRESULT step::preAssembliesFaceted(   stepArchive&          ar, 
                                      agitoAssembly*        pAssembly,
                                      CRepresentationStep *&pRepresentationStep )
{

#if     NOTIFICATION 
  if (m_bWriteFile)
  this->GetScribView()->Notify("Building assembly");
#endif//NOTIFICATION 

  int iNumModels = GetScribView()->m_modelarray.GetSize();
  //CNext_assembly_usage_occuranceStep
//  CAssembly_component_usageStep *pAssemblyStep = new 
//    CNext_assembly_usage_occuranceStep( (CModel*)GetScribView()->m_modelarray.GetAt(0), iNumModels);


  CPtrArray* pFaceted_brepStepArray = new CPtrArray;
  
  for ( int im =0; im < pAssembly->GetSize(); im++ ) {
    CClosed_shellStep*       pShellStep= NULL;
    agitoPart* pPart= (agitoPart*)pAssembly->GetAt( im);
    agitoComponent* pLump = (agitoComponent*)pPart->GetAt(0);
    agitoFeature* pFeature = (agitoFeature*)pLump->GetAt(0);
    int numShells = pFeature->GetSize();
    pShellStep = (CClosed_shellStep* )
      pFeature->GetAt( 0);

    CRepresentation_itemStep *pRepresentation_itemStep = new 
      CRepresentation_itemStep();
    if (NULL==pRepresentation_itemStep ){
      return E_OUTOFMEMORY;
    }
    CRepresentation_itemStep *pTopological_representation_itemStep = new 
      CTopological_representation_itemStep( pRepresentation_itemStep);
    if (NULL==pTopological_representation_itemStep ){
      return E_OUTOFMEMORY;
    }

#ifdef  EXPOSE      
    fprintf( g_errorLog, "CTopological_representation_itemStep::m_iLhs = %d\n"
      , 0// , pTopological_representation_itemStep->getNum()
      );
#endif//EXPOSE   
    
    pShellStep->m_pConnected_face_setStep->m_pRepresentation_itemStep =
      pTopological_representation_itemStep;
    CFaceted_brepStep*pFaceted_brepStep = new CFaceted_brepStep( pShellStep);
    if (NULL==pFaceted_brepStep ){
      return E_OUTOFMEMORY;
    }
    CModel* pModel = (CModel*) GetScribView()->m_modelarray.GetAt(im);
    pModel->m_pFacetedPool->AddStep(  pFaceted_brepStep);
    pFaceted_brepStep->m_pTechnadrawEntitites->AddTech( (CStepPtr *)
      GetScribView()->m_modelarray.GetAt(im));


    pFaceted_brepStepArray->Add( pFaceted_brepStep);
  }//im

  CRepresentation_contextStep *pGeometric_representation_contextStep = new 
    CGeometric_representation_contextStep(NULL);
  if (NULL==pGeometric_representation_contextStep ){
    return E_OUTOFMEMORY;
  }
  pRepresentationStep = new 
    CFaceted_brep_shape_representationStep( *pFaceted_brepStepArray, 
                                            pGeometric_representation_contextStep, 
                                            this );          
  if (NULL==pRepresentationStep) {
    return E_OUTOFMEMORY;
  }// wh 10/17/01
  
  g_iFACETED_BREP_SHAPE_REPRESENTATION = pRepresentationStep->getNum();

  if (m_bWriteFile) 
  {
    CTime theTime;
    theTime = CTime::GetCurrentTime();      
    iraroArchive* p_ir = (iraroArchive*) ar.m_archives.GetAt(0);
    iraroArchive& ir = *p_ir ;
    ir << "\n/* time when buildAssemblies ";
    ir << theTime.Format(" %Y-%m-%d T%H:%M:%S*/\n");

    ir << "\n/* from STEP topology/geometry schema, (part 42) */\n";
  }

  if (m_bWriteFile) 
  {
    pRepresentationStep->Serialize(ar); 
  }
#ifdef PRESENTATION
  // wh 7/15/01 presentation error
  presentation( ar);
#endif

  pGeometric_representation_contextStep->release();

  try{
    ASSERT( 1 == pRepresentationStep->getRefCnt());

#ifndef CREATESTEP 
    if ( m_bWriteFile){
      iRepresentationStepNum = pRepresentationStep->getNum();
      pRepresentationStep->release();
      pRepresentationStep=NULL;
    }
#endif

  }
  catch ( ... ) {
    // so what
    return S_OK;
  }
  delete pFaceted_brepStepArray;
  return S_OK;
}

// build the assembly
HRESULT step::buildAssembliesFaceted( stepArchive&          ar, 
                                      agitoAssembly*        pAssembly,
                                      CRepresentationStep *&pRepresentationStep )
{

#if     NOTIFICATION 
  if (m_bWriteFile)
  this->GetScribView()->Notify("Building assembly");
#endif//NOTIFICATION 

  int iNumModels = GetScribView()->m_modelarray.GetSize();
  //CNext_assembly_usage_occuranceStep
//  CAssembly_component_usageStep *pAssemblyStep = new 
//    CNext_assembly_usage_occuranceStep( (CModel*)GetScribView()->m_modelarray.GetAt(0), iNumModels);

//CPtrArray* pFaceted_brepStep = new CPtrArray;
  CPtrArray aFaceted_brepStep;
  
  for ( int im =0; im < pAssembly->GetSize(); im++ ) {
    CClosed_shellStep*       pShellStep= NULL;
    agitoPart* pPart= (agitoPart*)pAssembly->GetAt( im);
    agitoComponent* pLump = (agitoComponent*)pPart->GetAt(0);
    agitoFeature* pFeature = (agitoFeature*)pLump->GetAt(0);
    int numShells = pFeature->GetSize();
    pShellStep = (CClosed_shellStep* )
      pFeature->GetAt( 0);

    CRepresentation_itemStep *pRepresentation_itemStep = new 
      CRepresentation_itemStep();
    if (NULL==pRepresentation_itemStep ){
      return E_OUTOFMEMORY;
    }
    CRepresentation_itemStep *pTopological_representation_itemStep = new 
      CTopological_representation_itemStep( pRepresentation_itemStep);
    if (NULL==pTopological_representation_itemStep ){
      return E_OUTOFMEMORY;
    }

#ifdef  EXPOSE      
    fprintf( g_errorLog, "CTopological_representation_itemStep::m_iLhs = %d\n"
      , 0// , pTopological_representation_itemStep->getNum()
      );
#endif//EXPOSE   
    
    pShellStep->m_pConnected_face_setStep->m_pRepresentation_itemStep =
      pTopological_representation_itemStep;
    CFaceted_brepStep*pFaceted_brepStep = new CFaceted_brepStep( pShellStep);
    if (NULL==pFaceted_brepStep ){
      return E_OUTOFMEMORY;
    }
#if 0
    if (0){
      CCartesian_pointStep* pLocation = new CCartesian_pointStep( NULL, 0.0e0);
      if (NULL==pFaceted_brepStep ){
        return E_OUTOFMEMORY;
      }
      pLocation *=
      pPart->m_pCartesian_tranformation_operator_3dStep;
      CAxis2_placement_3dStep *pAxis2_placement_3dStep = new 
        CAxis2_placement_3dStep( *pLocation );
      if (NULL==pAxis2_placement_3dStep ){
        return E_OUTOFMEMORY;
      }
      aFaceted_brepStep.Add( pAxis2_placement_3dStep );
      pAxis2_placement_3dStep ->addRef();
    }
#endif
    aFaceted_brepStep.Add( pFaceted_brepStep);
  }//im

  CRepresentation_contextStep *pGeometric_representation_contextStep = new 
    CGeometric_representation_contextStep(NULL);
  if (NULL==pGeometric_representation_contextStep ){
    return E_OUTOFMEMORY;
  }
  pRepresentationStep = new 
    CFaceted_brep_shape_representationStep( aFaceted_brepStep, 
                                            pGeometric_representation_contextStep, 
                                            this );          
  if (NULL==pRepresentationStep) {
    return E_OUTOFMEMORY;
  }// wh 10/17/01
  
  g_iFACETED_BREP_SHAPE_REPRESENTATION = pRepresentationStep->getNum();

  if (m_bWriteFile) 
  {
    CTime theTime;
    theTime = CTime::GetCurrentTime();      
    iraroArchive* p_ir = (iraroArchive*) ar.m_archives.GetAt(0);
    iraroArchive& ir = *p_ir ;
    ir << "\n/* time when buildAssemblies ";
    ir << theTime.Format(" %Y-%m-%d T%H:%M:%S*/\n");

    ir << "\n/* from STEP topology/geometry schema, (part 42) */\n";
  }

  if (m_bWriteFile) 
  {
    pRepresentationStep->Serialize(ar); 
  }
#ifdef PRESENTATION
  // wh 7/15/01 presentation error
  presentation( ar);
#endif

  if ( m_bWriteFile)
  {
    pGeometric_representation_contextStep->release();
  }

  try{
    ASSERT( 1 == pRepresentationStep->getRefCnt());

    iRepresentationStepNum = pRepresentationStep->getNum();
    pRepresentationStep->release();

    pRepresentationStep=NULL;
  }
  catch ( ... ) {
    // so what
    return S_OK;
  }
  return S_OK;
}

//inline
HRESULT step::buildLeftFaceted( 
                                int&                          iv, 
                                CPolygon*&                    pPolygon, 
                                CCartesian_pointStepPtrArray* pCartesian_pointStepPtrArray, 
                                CCartesian_pointStep*&        pCartesian_pointStep1, 
                                stepArchive&                  ar,
                                CPolygon*&                    pPolygonZ, 
                                CDirectionStep*&              pRef_dir, 
                                int                           nv, // pPolygon->VertexHead + pPolygon->NumberOfVertices - pPolygon->SameLastFirstVertex
                                CDirectionStep*&              pAxis)
{

  if ( iv <= nv) // wh 04/09/01
  {
    do {
      iv++; 
      CCartesian_pointStep*  pCartesian_pointStep2 = NULL;
      if (iv <  nv){
        pCartesian_pointStep2 = 
        (CCartesian_pointStep*)pCartesian_pointStepPtrArray->GetAt( iv);
      } else {
        pCartesian_pointStep2 = 
        (CCartesian_pointStep*)pCartesian_pointStepPtrArray->GetAt( iv + pPolygon->VertexHead - nv );
      }
      ASSERT_VALID(pCartesian_pointStep2);
      CDirectionStep left_dir ( NULL 
                              , *pCartesian_pointStep1
                              , *pCartesian_pointStep2
                              );  
      if (left_dir.withinTol()) {
        continue;
      }
      CDirectionStep*  pLeft_dir = &left_dir ;

      if (NULL != pLeft_dir) {// wh 04/09/01
#ifdef _DEBUG
        pLeft_dir->m_szLabelName = "left";
#endif
      }
      else {// wh 04/09/01
        iraroArchive* p_ir = ar.GetAt( pLeft_dir->getNum());
        iraroArchive& ir = * p_ir ; 
        ir << "/*can't determine left direction because all the vertices are colinear.*/\n";
      }

      // flip is already taken into account!
      CSurface *pSurface = (CSurface *)
        GetScribView()->m_surfacearray.GetAt(pPolygonZ->MemberOfSurface);

      try {
        if (NULL ==pRef_dir)  {
          continue;
        }//wh 4/09/01
        pAxis = crossProduct( *pRef_dir, *pLeft_dir) ;//wh 03/29/01
        // take flip into account?
        if (!pAxis->withinTol()){
          break;
        }

        delete pAxis;// wh 3/06/02
        pAxis = NULL; // wh 9/28/01
      }
      catch(...){
        iraroArchive* p_ir = (iraroArchive*) ar.m_archives.GetAt(0);
        iraroArchive& ir = * p_ir ; 
        ir <<  "\n/*Errors for polygon "<< iv <<" */\n";
        TRACE1("Errors for polygon %n\n", iv);
      }
    } 
    while (iv <=
                nv // WH 03/07/02
          );

    if (iv >
             nv// wh 03/07/02
       ){
      ASSERT( false);
      iraroArchive* p_ir = (iraroArchive*) ar.m_archives.GetAt(0);//pAxis->getNum()
      iraroArchive& ir = * p_ir ; 
      ir << "/* cross prod is zero for polygon "<< iv <<" (#"<< -1 << ") */\n";
    }
  }
  else {
    TRACE1("iv (%d) >= pPolygon->VertexHead + nv\n", iv);
  }

  // problem here is that the polygon is in logical, not physical space!
  if (NULL == pAxis) {
    ASSERT_VALID( pPolygonZ);
    pAxis = new CDirectionStep(  NULL, 
                                 pPolygonZ->NormalX, 
                                -pPolygonZ->NormalY, // rv 03/28/01
                                 pPolygonZ->NormalZ);


//    ASSERT(!_isnan(pPolygonZ->NormalX));
    if (_isnan(pPolygonZ->NormalX)){
      TRACE0("pPolygonZ->NormalX NAN\n");
      pAxis->m_direction_ratios[0]=1.e0;
    }
//    ASSERT(!_isnan(pPolygonZ->NormalY));
    if (_isnan(pPolygonZ->NormalY)){
      TRACE0("pPolygonZ->NormalY NAN\n");
      pAxis->m_direction_ratios[1]=1.e0;
    }
//    ASSERT(!_isnan(pPolygonZ->NormalZ));
    if (_isnan(pPolygonZ->NormalZ)){
      TRACE0("pPolygonZ->NormalZ NAN\n");
      pAxis->m_direction_ratios[2]=1.e0;
    }
  }

  return S_OK;
}

HRESULT step::preFacesFaceted( FILE*                          stream, 
                               stepArchive&                   ar, 
                               CPtrArray*&                    pPoly_loopPtrArray, 
                               CRepresentationStep*&          pRepresentationStep,
                               CCartesian_pointStepPtrArray*& pCartesian_pointStepPtrArray  
                             , surfaceModelSelect             lSurfaceModelSelect  
//                           . (*f)
                             )
{
  HRESULT hr = S_OK;
#if     NOTIFICATION 
  if (m_bWriteFile)
  GetScribView()->Notify("(38%) step::buildFacesFaceted");
#endif//NOTIFICATION

#ifdef  SHOWPROGRESS
  if (m_bWriteFile)
  GetScribView()->progressBarUpdate( 38);
#endif//SHOWPROGRESS
  
  try{
    
    CPtrArray surfaceStepPtrArray ;
    CPtrArray* pSurfaceStepPtrArray = &surfaceStepPtrArray ;// allocate this off the stack instead

    pSurfaceStepPtrArray->SetSize( GetScribView()->m_surfacearray.GetSize());
    for (int i0 = 0; i0< surfaceStepPtrArray.GetSize();i0++){
      surfaceStepPtrArray.SetAt( i0, NULL);
    }
    CPtrArray face_surfaceStepPtrArray ;// allocate this off the stack instead
    CPtrArray* pFace_surfaceStepPtrArray = &face_surfaceStepPtrArray ;// allocate this off the stack instead
    
    pFace_surfaceStepPtrArray->SetSize( GetScribView()->m_polygonarray.GetSize() );
    for (i0 = 0; i0< face_surfaceStepPtrArray .GetSize();i0++){
      face_surfaceStepPtrArray .SetAt( i0, NULL);
    }

    for ( int is =0; is < GetScribView()->m_surfacearray.GetSize();is++ ) {
     CSurface* pSurface= (CSurface*)GetScribView()->m_surfacearray.GetAt(is);
//   if (0 != pSurface->layer) // test me
     {  
      int iT = pSurface->MemberOfObject;
      int ip = pSurface->FirstPolygon;
      for (int jp = 0; jp < pSurface->polysinsurface; jp++) 
      {
        CPolygon* pPolygon= (CPolygon*)GetScribView()->m_polygonarray.GetAt( ip + jp );
        int iv = pPolygon->VertexHead;
        int vn = pPolygon->NumberOfVertices;
        if (pPolygon->SameLastFirstVertex) {
          vn--;
        }
        int nv = iv + vn;
  #ifdef   EXPOSE
        if (iv >= GetScribView()->m_vertexarray.GetSize()){
          fprintf( g_errorLog, 
            "GetScribView()->m_vertexarray[ %d ] out of range.\n", iv);
        } 
  #endif //EXPOSE

        CVertex* pVertex= (CVertex*)
          GetScribView()->m_vertexarray.GetAt(iv); 
        CCartesian_pointStep* pCartesian_pointStep = 
          (CCartesian_pointStep*)pCartesian_pointStepPtrArray->GetAt(iv);


        CPolygon* pPolygonZ= (CPolygon*) // the poly which will provide the z coordinate
          GetScribView()->m_polygonarray.GetAt(pSurface->FirstPolygon);

        CCartesian_pointStep* pCartesian_pointStep1 = NULL;
        CDirectionStep*  pRef_dir = NULL;
        for ( int jv= 1; 
                  jv <= vn; 
                  jv++)
        {
          iv++; 
          if(iv < nv) {
            pCartesian_pointStep1 = (CCartesian_pointStep*)pCartesian_pointStepPtrArray->GetAt( iv);
          } else {
            pCartesian_pointStep1 = (CCartesian_pointStep*)pCartesian_pointStepPtrArray->GetAt( iv - vn );// wrap
          }
          pRef_dir = new CDirectionStep( NULL, 
                                         *pCartesian_pointStep,
                                         *pCartesian_pointStep1);
          if (NULL==pRef_dir ){
            return E_OUTOFMEMORY;
          }
          if (!pRef_dir->isGood()){
            if (iv <= nv) {    
              delete pRef_dir;// wh 09/20/01
              pRef_dir =NULL;
            }
            pCartesian_pointStep = pCartesian_pointStep1;// wh 3/07/02
            continue;
          }
          
          break;
        } 
        if (NULL !=pRef_dir){ // wh 04/09/01

        }
        else {// wh 04/09/01
          iraroArchive* p_ir = (iraroArchive*) ar.m_archives.GetAt( 0);//pCartesian_pointStep1->getNum());
          iraroArchive& ir = * p_ir ; 
          ar <<  "/*can't detemine up direction because all the point are colinear*/\n" ;
        }

        ASSERT_VALID(pCartesian_pointStep1);

        CDirectionStep*  pAxis = NULL;
        buildLeftFaceted( iv, 
                          pPolygon, 
                          pCartesian_pointStepPtrArray, 
                          pCartesian_pointStep1, 
                          ar,
                          pPolygonZ, 
                          pRef_dir, 
                          nv, 
                          pAxis);
            
	      // I dont trust this , use old way of negating the entire feature instead wh 5/28/01
        if (!CSG_NEGATE){
          if (pSurface->flip){// wh 5/12/00
            pAxis->negate();
          }
        }// !CSG_NEGATE

        CAxis2_placement_3dStep *pAxis2_Placement_3dStep = 
          new CAxis2_placement_3dStep( pCartesian_pointStep, pAxis , pRef_dir ); 
        if (NULL==pAxis2_Placement_3dStep) {
          return E_OUTOFMEMORY;
        }// wh 10/17/01
        // leaking wh 7/9/01
        CPlaneStep* pPlaneStep= 
          new CPlaneStep(  pAxis2_Placement_3dStep );
        if (NULL==pPlaneStep) {
          return E_OUTOFMEMORY;
        }// wh 10/17/01
        // leaking wh 7/9/01

        CPoly_loopStep* pPoly_loopStep = (CPoly_loopStep*) 
          pPoly_loopPtrArray->GetAt( ip + jp);// wh 04/03/01

	    // I dont trust this , use old way of negating the entire feature instead wh 5/28/01
        if (!CSG_NEGATE){
          if (pSurface->flip){// wh 5/12/00
            pPoly_loopStep->negate();
          }
        }// !CSG_NEGATE

        CFace_boundStep* pFace_boundStep = NULL;
        // at this stage all we know is that it is an outer bound, when we find out differently, we then demote it
        pFace_boundStep=  
        new CFace_outer_boundStep(  NULL, 
                                    pPoly_loopStep, 
                                    true
                                    //, NULL
                                    );
        if (NULL==pFace_boundStep) {
          return E_OUTOFMEMORY;
        }// wh 10/17/01
        pPolygon->m_pFacetedPool->AddStep(  pFace_boundStep);
        pFace_boundStep->m_pTechnadrawEntitites->AddTech( pPolygon);
      
        CFaceStep * pFaceStep = NULL;
        pFaceStep = 
          new CFace_surfaceStep( pPlaneStep
                               , pFace_boundStep// here is where there is one face outer_bound and several [inner]bound s
                               , true);
        if (NULL==pFaceStep) {
          return E_OUTOFMEMORY;
        }// wh 10/17/01
        pPolygon->m_pFacetedPool->AddStep(  pFaceStep );
        pFaceStep->m_pTechnadrawEntitites->AddTech( pPolygon);

        ASSERT( NULL == pFace_surfaceStepPtrArray->GetAt( ip + jp));
        pFace_surfaceStepPtrArray->SetAt( ip + jp, pFaceStep);

      }// next jp
     }// fi
    }// next is

    // build the shells
    // build the shells
    hr = preShellsFaceted( stream, 
                             ar, 
                             pPoly_loopPtrArray, 
                             pRepresentationStep 
                           , lSurfaceModelSelect
                           , pFace_surfaceStepPtrArray
                           , pCartesian_pointStepPtrArray
                           );
    } 
    catch (...){
#ifdef EXPOSE
      fprintf( g_errorLog, "Error deleting CSurfaceStepPtrArray \n");//big deal, the show is over
#endif//EXPOSE
      hr = E_FAIL;
    }
  return hr;
}

// build the faces from the surfaces
HRESULT step::buildFacesFaceted( FILE*                          stream, 
                                 stepArchive&                   ar, 
                                 CPtrArray*&                    pPoly_loopPtrArray, 
                                 CRepresentationStep*&          pRepresentationStep,
                                 CCartesian_pointStepPtrArray*& pCartesian_pointStepPtrArray  
                               , surfaceModelSelect             lSurfaceModelSelect                                 
                               )
{
  HRESULT hr = S_OK;
#if     NOTIFICATION 
  if (m_bWriteFile)
  GetScribView()->Notify("(38%) step::buildFacesFaceted");
#endif//NOTIFICATION

#ifdef  SHOWPROGRESS
  if (m_bWriteFile)
  GetScribView()->progressBarUpdate( 38);
#endif//SHOWPROGRESS
  
  try{
    
    CPtrArray surfaceStepPtrArray ;
    CPtrArray* pSurfaceStepPtrArray = &surfaceStepPtrArray ;// allocate this off the stack instead

    pSurfaceStepPtrArray->SetSize( GetScribView()->m_surfacearray.GetSize());
    for (int i0 = 0; i0< surfaceStepPtrArray.GetSize();i0++){
      surfaceStepPtrArray.SetAt( i0, NULL);
    }
    CPtrArray face_surfaceStepPtrArray ;// allocate this off the stack instead
    CPtrArray* pFace_surfaceStepPtrArray = &face_surfaceStepPtrArray ;// allocate this off the stack instead
    
    pFace_surfaceStepPtrArray->SetSize( GetScribView()->m_polygonarray.GetSize() );
    for (i0 = 0; i0< face_surfaceStepPtrArray .GetSize();i0++){
      face_surfaceStepPtrArray .SetAt( i0, NULL);
    }

    for ( int is =0; is < GetScribView()->m_surfacearray.GetSize();is++ ) {
     CSurface* pSurface= (CSurface*)GetScribView()->m_surfacearray.GetAt(is);
//   if (0 != pSurface->layer) // test me
     {  
      int iT = pSurface->MemberOfObject;
      int ip = pSurface->FirstPolygon;
      for (int jp = 0; jp < pSurface->polysinsurface; jp++) 
      {
        CPolygon* pPolygon= (CPolygon*)GetScribView()->m_polygonarray.GetAt( ip + jp );
        int iv = pPolygon->VertexHead;
        int vn = pPolygon->NumberOfVertices;
        if (pPolygon->SameLastFirstVertex) {
          vn--;
        }
        int nv = iv + vn;
  #ifdef   EXPOSE
        if (iv >= GetScribView()->m_vertexarray.GetSize()){
          fprintf( g_errorLog, 
            "GetScribView()->m_vertexarray[ %d ] out of range.\n", iv);
        } 
  #endif //EXPOSE

        CVertex* pVertex= (CVertex*)
          GetScribView()->m_vertexarray.GetAt(iv); 
        CCartesian_pointStep* pCartesian_pointStep = 
          (CCartesian_pointStep*)pCartesian_pointStepPtrArray->GetAt(iv);


        CPolygon* pPolygonZ= (CPolygon*) // the poly which will provide the z coordinate
          GetScribView()->m_polygonarray.GetAt(pSurface->FirstPolygon);

        CCartesian_pointStep* pCartesian_pointStep1 = NULL;
        CDirectionStep*  pRef_dir = NULL;
        for ( int jv= 1; 
                  jv <= vn; 
                  jv++)
        {
          iv++; 
          if(iv < nv) {
            pCartesian_pointStep1 = (CCartesian_pointStep*)pCartesian_pointStepPtrArray->GetAt( iv);
          } else {
            pCartesian_pointStep1 = (CCartesian_pointStep*)pCartesian_pointStepPtrArray->GetAt( iv - vn );// wrap
          }
          pRef_dir = new CDirectionStep( NULL, 
                                         *pCartesian_pointStep,
                                         *pCartesian_pointStep1);
          if (NULL==pRef_dir ){
            return E_OUTOFMEMORY;
          }
          if (!pRef_dir->isGood()){
            if (iv <= nv) {    
              delete pRef_dir;// wh 09/20/01
              pRef_dir =NULL;
            }
            pCartesian_pointStep = pCartesian_pointStep1;// wh 3/07/02
            continue;
          }
          
          break;
        } 
        if (NULL !=pRef_dir){ // wh 04/09/01
        }
        else {// wh 04/09/01
          iraroArchive* p_ir = (iraroArchive*) ar.m_archives.GetAt( 0);//pCartesian_pointStep1->getNum());
          iraroArchive& ir = * p_ir ; 
          ar <<  "/*can't detemine up direction because all the point are colinear*/\n" ;
        }

        ASSERT_VALID(pCartesian_pointStep1);

        CDirectionStep*  pAxis = NULL;
        buildLeftFaceted( iv, 
                          pPolygon, 
                          pCartesian_pointStepPtrArray, 
                          pCartesian_pointStep1, 
                          ar,
                          pPolygonZ, 
                          pRef_dir, 
                          nv, 
                          pAxis);
            
	      // I dont trust this , use old way of negating the entire feature instead wh 5/28/01
        if (!CSG_NEGATE){
          if (pSurface->flip){// wh 5/12/00
            pAxis->negate();
          }
        }// !CSG_NEGATE

        CAxis2_placement_3dStep *pAxis2_Placement_3dStep = 
          new CAxis2_placement_3dStep( pCartesian_pointStep, pAxis , pRef_dir ); 
        if (NULL==pAxis2_Placement_3dStep) {
          return E_OUTOFMEMORY;
        }// wh 10/17/01
        // leaking wh 7/9/01
        CPlaneStep* pPlaneStep= 
          new CPlaneStep(  pAxis2_Placement_3dStep );
        if (NULL==pPlaneStep) {
          return E_OUTOFMEMORY;
        }// wh 10/17/01
        // leaking wh 7/9/01

        CPoly_loopStep* pPoly_loopStep = (CPoly_loopStep*) 
          pPoly_loopPtrArray->GetAt( ip + jp);// wh 04/03/01
        if (NULL != pPoly_loopStep){// wh 03/12/02
	    // I dont trust this , use old way of negating the entire feature instead wh 5/28/01
        if (!CSG_NEGATE){
          if (pSurface->flip){// wh 5/12/00
            pPoly_loopStep->negate();
          }
        }// !CSG_NEGATE

        CFace_boundStep* pFace_boundStep = NULL;
        // at this stage all we know is that it is an outer bound, when we find out differently, we then demote it
        pFace_boundStep=  
        new CFace_outer_boundStep(  NULL, 
                                    pPoly_loopStep, 
                                    true
                                    //, NULL
                                    );
        if (NULL==pFace_boundStep) {
          return E_OUTOFMEMORY;
        }// wh 10/17/01
        pPolygon->m_pFacetedPool->AddStep(  pFace_boundStep);
        pFace_boundStep->m_pTechnadrawEntitites->AddTech( pPolygon);
      
        CFaceStep * pFaceStep = NULL;
        pFaceStep = 
          new CFace_surfaceStep( pPlaneStep
                               , pFace_boundStep// here is where there is one face outer_bound and several [inner]bound s
                               , true);
        if (NULL==pFaceStep) {
          return E_OUTOFMEMORY;
        }// wh 10/17/01
        pPolygon->m_pFacetedPool->AddStep(  pFaceStep );
        pFaceStep->m_pTechnadrawEntitites->AddTech( pPolygon);

        ASSERT( NULL == pFace_surfaceStepPtrArray->GetAt( ip + jp));
        pFace_surfaceStepPtrArray->SetAt( ip + jp, pFaceStep);
        }// fi pPoly_loopStep
        else {
          pFace_surfaceStepPtrArray->SetAt( ip + jp, NULL);// wh 03/12/02
        }
      }// next jp
     }// fi
    }// next is

    // build the shells
    hr = buildShellsFaceted( stream, 
                             ar, 
                             pPoly_loopPtrArray, 
                             pRepresentationStep 
                           , lSurfaceModelSelect
                           , pFace_surfaceStepPtrArray
                           , pCartesian_pointStepPtrArray
                           );
    } 
    catch (...){
#ifdef EXPOSE
      fprintf( g_errorLog, "Error deleting CSurfaceStepPtrArray \n");//big deal, the show is over
#endif//EXPOSE
      hr = E_FAIL;
    }
  return hr;
}


// build the loops
HRESULT step::buildLoopsFaceted( FILE *                           stream, 
                                 stepArchive &                    ar, 
                                 CPtrArray*&                      pPoly_loopPtrArray, 
                                 CRepresentationStep*&            pRepresentationStep
                               , surfaceModelSelect              lSurfaceModelSelect
                               , CCartesian_pointStepPtrArray*&  pCartesian_pointStepPtrArray  
                               )
{
#if     NOTIFICATION 
  if (m_bWriteFile)
  GetScribView()->Notify("(35%) step::buildLoopsFaceted");
#endif//NOTIFICATION 

#ifdef  SHOWPROGRESS
  if (m_bWriteFile)
      GetScribView()->progressBarUpdate( 35);
#endif//SHOWPROGRESS

  HRESULT hr = buildFacesFaceted( stream, 
                  ar, 
                  pPoly_loopPtrArray, 
                  pRepresentationStep 
                  , pCartesian_pointStepPtrArray
                  , lSurfaceModelSelect
                  );
  return hr;
}

//inline
HRESULT step::buildPoly_loopFaceted(
                                    int&                          iv,
                                    CVertex_pointStepPtrArray*&   pVertex_pointStepPtrArray,
                                    CPolygon*&                    pPolygon,
                                    CCartesian_pointStepPtrArray* pCartesian_pointStepPtrArray,
                                    int&                          ip,
                                    CPtrArray*&                   pPoly_loopPtrArray,
                                    CVertex_pointStep*&           pVertex_pointStep0 ,
                                    CVertex_pointStep*&           pVertex_pointStep1,
                                    CPoly_loopStep*&              pPoly_loopStep)
{
  pVertex_pointStep0 = (CVertex_pointStep*) 
    (pVertex_pointStepPtrArray->GetAt( pPolygon->VertexHead+0));
  ASSERT(NULL != pVertex_pointStep0);
  pVertex_pointStep1 = (CVertex_pointStep*) 
    (pVertex_pointStepPtrArray->GetAt( pPolygon->VertexHead+1));
  ASSERT(NULL != pVertex_pointStep1);
  CVertex_pointStep* 
  pVertex_pointStep2 = (CVertex_pointStep*) 
    (pVertex_pointStepPtrArray->GetAt( pPolygon->VertexHead+2));
  ASSERT(NULL != pVertex_pointStep2);
  
  int iNumV = pPolygon->NumberOfVertices;
  if (pPolygon->SameLastFirstVertex){
    iNumV--;
  }
  pPoly_loopStep = 
    new CPoly_loopStep( 
       (pVertex_pointStep0->m_p_vertex_geometry), 
       (pVertex_pointStep1->m_p_vertex_geometry), 
       (pVertex_pointStep2->m_p_vertex_geometry),
      iNumV );
  if (NULL==pPoly_loopStep) {
    return E_OUTOFMEMORY;
  }// wh 10/17/01
  pPolygon->m_pFacetedPool->AddStep(  pPoly_loopStep);
  pPoly_loopStep->m_pTechnadrawEntitites->AddTech( pPolygon);
   
//make pPoly_loopPtrArray a CrtPtrArray// wh 10/19/01
  pPoly_loopPtrArray->SetAt(ip, pPoly_loopStep );

  iv = pPolygon->VertexHead;
  CVertex* pVertex1= (CVertex*)GetScribView()->m_vertexarray.GetAt(iv ); 
//if (-1 != pVertex1->dupe) {iv1 = pVertex1->dupe;} else {iv1 = iv;} 
  CCartesian_pointStep* pCartesian_pointStep0= 
    (CCartesian_pointStep*)((pCartesian_pointStepPtrArray->GetAt( iv  )));
  CCartesian_pointStep* pCartesian_pointStep1= 
    (CCartesian_pointStep*)((pCartesian_pointStepPtrArray->GetAt( iv+1)));

  iv++;
  CVertex* pVertex2= (CVertex*)GetScribView()->m_vertexarray.GetAt(iv ); 
  pCartesian_pointStep0= (CCartesian_pointStep*)
    ((pCartesian_pointStepPtrArray->GetAt( iv  )));
  pCartesian_pointStep1= (CCartesian_pointStep*)
    ((pCartesian_pointStepPtrArray->GetAt( iv+1)));

  return S_OK;
}

// build the path
HRESULT step::prePathFaceted( FILE *                        stream,           
                              stepArchive &                 ar, 
                              CRepresentationStep*&         pRepresentationStep,
                              CVertex_pointStepPtrArray*&   pVertex_pointStepPtrArray,
                              CCartesian_pointStepPtrArray* &pCartesian_pointStepPtrArray,
                              surfaceModelSelect            lSurfaceModelSelect
                           
                            )
{
  HRESULT hr = S_OK;
#if     NOTIFICATION 
  if (m_bWriteFile)
  GetScribView()->Notify("(33%) step::buildPathFaceted");
#endif//NOTIFICATION 

#ifdef  SHOWPROGRESS
  if (m_bWriteFile)
  GetScribView()->progressBarUpdate( 33);
#endif//SHOWPROGRESS
    
  CPtrArray* pPoly_loopPtrArray = new CPtrArray( );
    if (NULL==pPoly_loopPtrArray) {
      return E_OUTOFMEMORY;
    }// wh 10/17/01
    pPoly_loopPtrArray->SetSize( GetScribView()->m_polygonarray.GetSize());

    for ( int ip =0; ip < GetScribView()->m_polygonarray.GetSize();ip++ ) {
      CPolygon* pPolygon= (CPolygon*)GetScribView()->m_polygonarray.GetAt(ip);
      CVertex_pointStep* pVertex_pointStep0=NULL;
      CVertex_pointStep* pVertex_pointStep1=NULL;
      CPoly_loopStep* pPoly_loopStep = NULL;
      int iNumV = pPolygon->NumberOfVertices;
      if (pPolygon->SameLastFirstVertex){// wh 3/12/02
        iNumV--;
      }
      ASSERT( iNumV>2);
      int iv=0;
      
      if ( iNumV>2 ) {
        buildPoly_loopFaceted(        
                              iv,
                              pVertex_pointStepPtrArray,
                              pPolygon,
                              pCartesian_pointStepPtrArray,
                              ip,
                              pPoly_loopPtrArray,
                              pVertex_pointStep0,
                              pVertex_pointStep1, 
                              pPoly_loopStep );          
      }
      else {
        TRACE2("for CPolygon %d, iNumV = %d\n", ip, iNumV);
        pVertex_pointStep0 = (CVertex_pointStep*) 
        (pVertex_pointStepPtrArray->GetAt( pPolygon->VertexHead+0));
        char buf [16];
          itoa( ip, buf, 10);

        iraroArchive* p_ir = (iraroArchive*) ar.m_archives.GetAt( 0); //pVertex_pointStep0->getNum());
        iraroArchive& ir = * p_ir ; 
        ir <<  "\n/* CPolygon " << buf << " has too few verticies ( " << iNumV << " )*/\n";
        // wh   09/28/01  Encountered polygons with 2 verticies, what should I do?
        // either ignore the entity
        // or build a degenerate 3-sided polygon where the first and last vertex agree

        // remove the face bound for this poly_loop  03/12/02
        pPoly_loopPtrArray->SetAt( ip, // 3/12/02
                              NULL);
      }

      pVertex_pointStep0 = (CVertex_pointStep*) 
        (pVertex_pointStepPtrArray->GetAt( pPolygon->VertexHead+1));
      pVertex_pointStep1 = (CVertex_pointStep*) 
        (pVertex_pointStepPtrArray->GetAt( pPolygon->VertexHead+2));

      for ( int vh = // 2
                     3 // wh 9/14/01
            ; vh < 
              iNumV-1; //wh 5/15/01// first and last vertex are in twice
                              // I had a problem when tring to use the last one!
              vh++ ) {
        int iv = vh + pPolygon->VertexHead ;
        CVertex* pVertex1= (CVertex*)GetScribView()->m_vertexarray.GetAt(iv ); 
        CCartesian_pointStep* pCartesian_pointStep0= 
          (CCartesian_pointStep*)((pCartesian_pointStepPtrArray->GetAt( iv)));
        CCartesian_pointStep* pCartesian_pointStep1= 
          (CCartesian_pointStep*)((pCartesian_pointStepPtrArray->GetAt( iv+1)));

        CVertex_pointStep* pVertex_pointStep1  = (CVertex_pointStep*) 
          (pVertex_pointStepPtrArray->GetAt(  iv));
        pVertex_pointStep0 = pVertex_pointStep1;
        pPoly_loopStep->SetAt( vh, (pVertex_pointStep0->m_p_vertex_geometry));
      }// vh

      // rearranged code wh 9/19/01
      if (iNumV>2// 11/15/01
        ) {
        int iv = iNumV-1 + pPolygon->VertexHead ;
        CVertex* pVertex1= (CVertex*)GetScribView()->m_vertexarray.GetAt(iv ); 
        CCartesian_pointStep* pCartesian_pointStep0= 
          (CCartesian_pointStep*)((pCartesian_pointStepPtrArray->GetAt( iv)));
        CCartesian_pointStep* pCartesian_pointStep1= 
          (CCartesian_pointStep*)((pCartesian_pointStepPtrArray->GetAt( pPolygon->VertexHead )));

        CVertex_pointStep* pVertex_pointStep1  = (CVertex_pointStep*) 
          (pVertex_pointStepPtrArray->GetAt( iv));
        pVertex_pointStep0 = pVertex_pointStep1;
        pPoly_loopStep->SetAt( iNumV-1, 
                              (pVertex_pointStep0->m_p_vertex_geometry));
      } else {
      }
//    pPoly_loopStep->simplify();// wh 10/24/01
    }//next ip 

  hr = preFacesFaceted( stream, 
                        ar, 
                        pPoly_loopPtrArray, 
                        pRepresentationStep,
                        pCartesian_pointStepPtrArray                      
                      , lSurfaceModelSelect 
//                    , &preShellsFaceted
                      );
  delete pPoly_loopPtrArray;// wh 02/02/02
  return hr;
}

// build the path, and along each of the paths, call to build the loops
HRESULT step::buildPathFaceted( FILE *                        stream,           
                                stepArchive &                 ar, 
                                CRepresentationStep*&         pRepresentationStep,
                                CVertex_pointStepPtrArray*&   pVertex_pointStepPtrArray,
                                CCartesian_pointStepPtrArray* &pCartesian_pointStepPtrArray,
                                surfaceModelSelect            lSurfaceModelSelect 
                                
                              )
{
#if     NOTIFICATION 
  if (m_bWriteFile)
    GetScribView()->Notify("(33%) step::buildPathFaceted");
#endif//NOTIFICATION 

#ifdef  SHOWPROGRESS
  if (m_bWriteFile)
      GetScribView()->progressBarUpdate( 33);
#endif//SHOWPROGRESS

    // move to buildpath
//  CPtrArray* pPathStepPtrArray = new CPtrArray( );
//  pPathStepPtrArray->SetSize( GetScribView()->m_polygonarray.GetSize());
    
    CPtrArray* pPoly_loopPtrArray = new CPtrArray( );
    if (NULL==pPoly_loopPtrArray) {
      return E_OUTOFMEMORY;
    }// wh 10/17/01
    pPoly_loopPtrArray->SetSize( GetScribView()->m_polygonarray.GetSize());

    for ( int ip =0; ip < GetScribView()->m_polygonarray.GetSize();ip++ ) {
      CPolygon* pPolygon= (CPolygon*)GetScribView()->m_polygonarray.GetAt(ip);
      CVertex_pointStep* pVertex_pointStep0=NULL;
      CVertex_pointStep* pVertex_pointStep1=NULL;
      CPoly_loopStep* pPoly_loopStep = NULL;
//    ASSERTMSG("polygon has too few vertices", pPolygon->NumberOfVertices>2);
      int iNumV = pPolygon->NumberOfVertices;
      if (pPolygon->SameLastFirstVertex){// wh 3/12/02
        iNumV--;
      }
      ASSERT( iNumV>2);
      int iv=0;
      
      if ( iNumV>2 ) {
        buildPoly_loopFaceted(        
                              iv,
                              pVertex_pointStepPtrArray,
                              pPolygon,
                              pCartesian_pointStepPtrArray,
                              ip,
                              pPoly_loopPtrArray,
                              pVertex_pointStep0,
                              pVertex_pointStep1, 
                              pPoly_loopStep );          
      }
      else {
        TRACE2("for CPolygon %d, iNumV = %d\n", ip, iNumV);
        pVertex_pointStep0 = (CVertex_pointStep*) 
        (pVertex_pointStepPtrArray->GetAt( pPolygon->VertexHead+0));
        char buf [16];
          itoa( ip, buf, 10);

        iraroArchive* p_ir = (iraroArchive*) ar.m_archives.GetAt( 0); //pVertex_pointStep0->getNum());
        iraroArchive& ir = * p_ir ; 
        ir <<  "\n/* CPolygon " << buf << " has too few verticies ( " << iNumV << " )*/\n";
        // wh   09/28/01  Encountered polygons with 2 verticies, what should I do?
        // either ignore the entity
        // or build a degenerate 3-sided polygon where the first and last vertex agree

        // remove the face bound for this poly_loop  03/12/02
        pPoly_loopPtrArray->SetAt( ip, // 3/12/02
                              NULL);
      }

      pVertex_pointStep0 = (CVertex_pointStep*) 
        (pVertex_pointStepPtrArray->GetAt( pPolygon->VertexHead+1));
      pVertex_pointStep1 = (CVertex_pointStep*) 
        (pVertex_pointStepPtrArray->GetAt( pPolygon->VertexHead+2));

//    int iNumberOfVertices= iNumV;// wh 9/19/01
//    if (!pPolygon->SameLastFirstVertex){// wh 9/19/01
//      iNumberOfVertices= pPolygon->NumberOfVertices;// wh 9/19/01
//    }
      for ( int vh = // 2
                     3 // wh 9/14/01
            ; vh < 
              iNumV-1; //wh 5/15/01// first and last vertex are in twice
                              // I had a problem when tring to use the last one!
              vh++ ) {
        int iv = vh + pPolygon->VertexHead ;
        CVertex* pVertex1= (CVertex*)GetScribView()->m_vertexarray.GetAt(iv ); 
        CCartesian_pointStep* pCartesian_pointStep0= 
          (CCartesian_pointStep*)((pCartesian_pointStepPtrArray->GetAt( iv)));
        CCartesian_pointStep* pCartesian_pointStep1= 
          (CCartesian_pointStep*)((pCartesian_pointStepPtrArray->GetAt( iv+1)));

        CVertex_pointStep* pVertex_pointStep1  = (CVertex_pointStep*) 
          (pVertex_pointStepPtrArray->GetAt(  iv));
        pVertex_pointStep0 = pVertex_pointStep1;
        pPoly_loopStep->SetAt( vh, (pVertex_pointStep0->m_p_vertex_geometry));
      }// vh

      // rearranged code wh 9/19/01
      if (iNumV>2// 11/15/01
        ) {
        int iv = iNumV-1 + pPolygon->VertexHead ;
        CVertex* pVertex1= (CVertex*)GetScribView()->m_vertexarray.GetAt(iv ); 
        CCartesian_pointStep* pCartesian_pointStep0= 
          (CCartesian_pointStep*)((pCartesian_pointStepPtrArray->GetAt( iv)));
        CCartesian_pointStep* pCartesian_pointStep1= 
          (CCartesian_pointStep*)((pCartesian_pointStepPtrArray->GetAt( pPolygon->VertexHead )));

        CVertex_pointStep* pVertex_pointStep1  = (CVertex_pointStep*) 
          (pVertex_pointStepPtrArray->GetAt( iv));
        pVertex_pointStep0 = pVertex_pointStep1;
        pPoly_loopStep->SetAt( iNumV-1, 
                              (pVertex_pointStep0->m_p_vertex_geometry));
      } else {
      }
//    pPoly_loopStep->simplify();// wh 10/24/01
    }//next ip 

  HRESULT hr = buildLoopsFaceted( stream, 
                                  ar, 
                                  pPoly_loopPtrArray, 
                                  pRepresentationStep,
                                  lSurfaceModelSelect, 
                                  pCartesian_pointStepPtrArray
                                  //,*pVertex_pointStepPtrArray
                                  );

  delete pPoly_loopPtrArray;

  return hr;
}

// build the edge, and for each edge, build the path
HRESULT step::buildEdgeFaceted( FILE *stream, 
                                stepArchive &ar, 
                                CRepresentationStep*& pRepresentationStep,
                                CVertex_pointStepPtrArray*& pVertex_pointStepPtrArray ,
                                CCartesian_pointStepPtrArray* &pCartesian_pointStepPtrArray,
                                surfaceModelSelect       lSurfaceModelSelect               
                               )
{
#if     NOTIFICATION 
  if (m_bWriteFile)
  GetScribView()->Notify("(32%) step::buildEdgeFaceted");
#endif//NOTIFICATION 

#ifdef  SHOWPROGRESS
  if (m_bWriteFile)
      GetScribView()->progressBarUpdate( 32);
#endif//SHOWPROGRESS

  HRESULT hr = buildPathFaceted( stream, 
                                  ar, 
                                  pRepresentationStep,
                                  pVertex_pointStepPtrArray,
                                  pCartesian_pointStepPtrArray,
                                  lSurfaceModelSelect           
                                  );
  return hr;
}

// build the vertices of the model
HRESULT step::preVerticesFaceted( FILE *                stream, 
                                  stepArchive &         ar, 
                                  surfaceModelSelect    lSurfaceModelSelect, 
                                  CRepresentationStep*& pFaceted_brep_shape_representationStep
                                 )
{

#if     NOTIFICATION 
  if (m_bWriteFile)
  GetScribView()->Notify("(10%) step::buildVerticesFaceted");
#endif//NOTIFICATION 
#ifdef  SHOWPROGRESS
  if (m_bWriteFile){
      GetScribView()->progressBarUpdate( 10);
  }
#endif//SHOWPROGRESS

  // there is one for each model, not one for each asssembly
  CCartesian_pointStepPtrArray* pCartesian_pointStepPtrArray = new 
    CCartesian_pointStepPtrArray( GetScribView()->m_vertexarray.GetSize());
  if (NULL==pCartesian_pointStepPtrArray) {
    return E_OUTOFMEMORY;
  }// wh 10/17/01
  CVertex_pointStepPtrArray* pVertex_pointStepPtrArray = new 
    CVertex_pointStepPtrArray( *pCartesian_pointStepPtrArray);
  if (NULL==pVertex_pointStepPtrArray) {
    return E_OUTOFMEMORY;
  }// wh 10/17/01

  pCartesian_pointStepPtrArray->SetSize( GetScribView()->m_vertexarray.GetSize());
  pVertex_pointStepPtrArray->SetSize( GetScribView()->m_vertexarray.GetSize());

  for ( int iv =0; iv < GetScribView()->m_vertexarray.GetSize();iv++ ) {
    CVertex* pVertex= (CVertex*)GetScribView()->m_vertexarray.GetAt(iv);
//  if (-1 == pVertex->dupe){
      
      CCartesian_pointStep* pCartesian_pointStep = 
        new CCartesian_pointStep( NULL, 
                                  pVertex->px - GetScribView()->XRotationAxis, 
                                -(pVertex->py - GetScribView()->YRotationAxis), 
                                  pVertex->pz - GetScribView()->ZRotationAxis);
      if (NULL==pCartesian_pointStep) {
        return E_OUTOFMEMORY;
      }// wh 10/17/01
      pVertex->m_pFacetedPool->AddStep(  pCartesian_pointStep);
      pCartesian_pointStep->m_pTechnadrawEntitites->AddTech( pVertex);
//    pCartesian_pointStep->m_szLabelName = "CCartesian_pointStep ";
      int ivSet = pCartesian_pointStepPtrArray->SetAt( iv, pCartesian_pointStep);
      if (ivSet == iv) 
      {
        CVertex_pointStep* pVertex_pointStep = 
          new CVertex_pointStep( *pCartesian_pointStep);
        if (NULL==pVertex_pointStep) {
          return E_OUTOFMEMORY;
        }// wh 10/17/01
//      pVertex->m_pFacetedPool->AddStep(pVertex_pointStep);
//      pVertex_pointStep->m_pTechnadrawEntitites->AddTech( pVertex);
        if (-1 == pVertex_pointStepPtrArray->SetAt( iv, pVertex_pointStep)){
  //          break;
        }
        pVertex_pointStep->release();
        // since it is copied in the array 
        pCartesian_pointStep->release();// wh 8/30/01 //??
      }       
      else {
        CVertex_pointStep* pVertex_pointStep = 
          pVertex_pointStepPtrArray->GetAt( iv);
#ifdef  EXPOSE      
        fprintf( g_errorLog, 
          "incrementing CVertex_pointStepPtrArray[%d] =(#%d ) \n", 
          iv, pVertex_pointStep->getNum());
#endif//EXPOSE   
//      pVertex_pointStep->addRef();// wh 09/20/01
//      pVertex_pointStep->m_p_vertex_geometry->pCartesian_pointStep->m_pTechnadrawEntitites->AddTech( pVertex);
//      pVertex->m_pFacetedPool->AddStep(  pVertex_pointStep->m_p_vertex_geometry);
      }
//  }
  }
  HRESULT hr = S_OK;

  // move to buildface

  hr = 
    prePathFaceted( stream, 
                    ar, 
                    pFaceted_brep_shape_representationStep,
                    pVertex_pointStepPtrArray ,
                    pCartesian_pointStepPtrArray,
                    lSurfaceModelSelect
                  );
//  delete pVertex_pointStepPtrArray;// wh 2/08/02

//  delete pCartesian_pointStepPtrArray;// wh 2/08/02
  return hr;
}

// build the vertices of the model
HRESULT step::buildVerticesFaceted( FILE *                stream, 
                                    stepArchive &         ar, 
                                    surfaceModelSelect    lSurfaceModelSelect, 
                                    CRepresentationStep*& pRepresentationStep 
                                  )
{
#if     NOTIFICATION 
  if (m_bWriteFile)
  GetScribView()->Notify("(10%) step::buildVerticesFaceted");
#endif//NOTIFICATION 
#ifdef  SHOWPROGRESS
  if (m_bWriteFile)
      GetScribView()->progressBarUpdate( 10);
#endif//SHOWPROGRESS

  // there is one for each model, not one for each asssembly
  CCartesian_pointStepPtrArray* pCartesian_pointStepPtrArray = new 
    CCartesian_pointStepPtrArray( GetScribView()->m_vertexarray.GetSize());
  if (NULL==pCartesian_pointStepPtrArray) {
    return E_OUTOFMEMORY;
  }// wh 10/17/01
  CVertex_pointStepPtrArray* pVertex_pointStepPtrArray = new 
    CVertex_pointStepPtrArray( *pCartesian_pointStepPtrArray);
  if (NULL==pVertex_pointStepPtrArray) {
    return E_OUTOFMEMORY;
  }// wh 10/17/01

  pCartesian_pointStepPtrArray->SetSize( GetScribView()->m_vertexarray.GetSize());
  pVertex_pointStepPtrArray->SetSize( GetScribView()->m_vertexarray.GetSize());

  for ( int iv =0; iv < GetScribView()->m_vertexarray.GetSize();iv++ ) {
    CVertex* pVertex= (CVertex*)GetScribView()->m_vertexarray.GetAt(iv);
//  if (-1 == pVertex->dupe){
      
      CCartesian_pointStep* pCartesian_pointStep = 
        new CCartesian_pointStep( NULL, 
                                  pVertex->px - GetScribView()->XRotationAxis, 
                                -(pVertex->py - GetScribView()->YRotationAxis), 
                                  pVertex->pz - GetScribView()->ZRotationAxis);
      if (NULL==pCartesian_pointStep) {
        return E_OUTOFMEMORY;
      }// wh 10/17/01

      pVertex->m_pFacetedPool->AddStep(pCartesian_pointStep);
      pCartesian_pointStep->m_pTechnadrawEntitites->AddTech( pVertex);
//    pCartesian_pointStep->m_szLabelName = "CCartesian_pointStep ";
      int ivSet = pCartesian_pointStepPtrArray->SetAt( iv, pCartesian_pointStep);
      if (ivSet == iv) 
      {
        CVertex_pointStep* pVertex_pointStep = 
          new CVertex_pointStep( *pCartesian_pointStep);
        if (NULL==pVertex_pointStep) {
          return E_OUTOFMEMORY;
        }// wh 10/17/01

//      pVertex->m_pFacetedPool->AddStep(pVertex_pointStep);
//      pVertex_pointStep->m_pTechnadrawEntitites->AddTech( pVertex);
        if (-1 == pVertex_pointStepPtrArray->SetAt( iv, pVertex_pointStep)){
  //          break;
        }
        pVertex_pointStep->release();
        // since it is copied in the array 
        pCartesian_pointStep->release();// wh 8/30/01 //??
//      pCartesian_pointStep->Dump();
      }       
      else {
        CVertex_pointStep* pVertex_pointStep = 
          pVertex_pointStepPtrArray->GetAt( iv);
#ifdef  EXPOSE      
        fprintf( g_errorLog, 
          "incrementing CVertex_pointStepPtrArray[%d] =(#%d ) \n", 
          iv, pVertex_pointStep->getNum());
#endif//EXPOSE   
        pVertex_pointStep->addRef();// wh 09/20/01
      }
//  }
  }
  HRESULT hr = S_OK;

    // move to buildface
  hr = 
    buildEdgeFaceted( stream, 
                          ar, 
                          pRepresentationStep,
                          pVertex_pointStepPtrArray ,
                          pCartesian_pointStepPtrArray,
                          lSurfaceModelSelect);

  try{



    delete pVertex_pointStepPtrArray;

    delete pCartesian_pointStepPtrArray;

  } catch(...){
#ifdef  EXPOSE      
		TRACE0("error deleting CCartesian_pointStepPtrArray.\n");
    fprintf( g_errorLog, "error deleting CCartesian_pointStepPtrArray.\n");
    ASSERT(false);
#endif//EXPOSE   
  }
//ar.FreeExtra();// wh 8/29/01
  return hr;
}



 
// translate from technadraw entities to STEP entities.
// There are different API functionality for faceted_brep vs. advanced_brep 
//  because each Application Interpreted Construct make different assumptions 
//  on how the lower level entities look like
HRESULT step::TechDraw2Step( FILE*              stream, 
                             stepArchive&       ar, 
                             surfaceModelSelect lSurfaceModelSelect
                           )
{
  HRESULT hr = S_OK;
  // bulletin board mechanism as seen in Mantlya's GWB
  try {

    // we build the model from lower level entities to higher level entities.
    // build vertices  10%
    // build edges    32
    // build path     33
    // build loops,   35
    // build faces    38
    // build shells   40

    CRepresentationStep *pRepresentationStep= NULL;
    if (shellBasedSurfaceModel != lSurfaceModelSelect )
    { 
      if ( //m_bWriteFile &&
          (NULL!=m_pFaceted_brep_shape_representationStep)
         )
      { 
        ASSERT_VALID( m_pFaceted_brep_shape_representationStep);

        // need to reset isSerialized or save the CStringArray
        for (int i = 0; i<m_pFaceted_brep_shape_representationStep->m_pStep->m_ptrArrayAgito.GetSize(); i++){
          CBaseStep* pBaseStep = ( CBaseStep*) m_pFaceted_brep_shape_representationStep->m_pStep->m_ptrArrayAgito.GetAt(i);
          if(NULL != pBaseStep){
            ASSERT_VALID(pBaseStep);
            pBaseStep->m_bSerialized = false;
          }
        }
        
        m_pFaceted_brep_shape_representationStep->Serialize(ar);// wh 11/21/01
      }
      else {
        hr = 
          buildVerticesFaceted( stream, 
                                ar, 
                                lSurfaceModelSelect ,
                                pRepresentationStep);
      }
      if (FAILED( hr)){
        return hr;
      }
    }
    else
    {
      if ( //m_bWriteFile &&
          (NULL!=m_pAdvanced_brep_shape_representationStep)
         )
      { 
        ASSERT_VALID( m_pAdvanced_brep_shape_representationStep);

        // need to reset isSerialized or save the CStringArray
        for (int i = 0; i<m_pAdvanced_brep_shape_representationStep->m_pStep->m_ptrArrayAgito.GetSize(); i++){
          CBaseStep* pBaseStep = ( CBaseStep*) m_pAdvanced_brep_shape_representationStep->m_pStep->m_ptrArrayAgito.GetAt(i);
          if(NULL != pBaseStep){
            ASSERT_VALID(pBaseStep);
            pBaseStep->m_bSerialized = false;
          }
        }
        
        m_pAdvanced_brep_shape_representationStep->Serialize(ar);// wh 11/21/01
      }
      else {
        hr = 
        buildVerticesAdvanced( stream, 
                               ar, 
                               lSurfaceModelSelect ,
                               pRepresentationStep);    
  //    m_pSelectRepresentationStep = pRepresentationStep;
        if (FAILED( hr)){
          return hr;
        }
      }
    }
  }
  catch ( ... ) {
    hr = E_FAIL;
    ASSERT( SUCCEEDED( hr));
    return E_FAIL;  
  }

  return S_OK;
}


// After much deliberation, the correct way to do garbage collection is to first delete all 
//   classes which reference other classes, 
//   and then delete all classes which are referenced by those classes.
// fat chance sucker, easier said than done!
// Need to check ref_counting.  anytime a pointer is copied or an object referenced, 
//                  increment reference count.  
//                  Whenever a pointer/reference is removed, dec ref cnt.

// Find out why bounds checker complains about variable being 
//   allocated off the stack as opposed to the heap.  
//  Is that an MFC restriction?

void 
//step::
garbage_collection( CPtrArray& m_ptrArrayAgito)
{
#ifdef  EXPOSE      
  fprintf( g_errorLog, "\n garbage_collection\n");
#endif//EXPOSE   
  try{
    if (0) {
      // remove ref to all classes
      for (int i = m_ptrArrayAgito.GetSize()-1; 
               i >= 0 ; 
               i--)
      {
        try{
          // problem with the fact that I have references to objects
          CBaseStep* pBS = (CBaseStep*)
            m_ptrArrayAgito.GetAt(i);
          if (NULL != pBS){
            pBS->fin();
          }
        }
        catch(...){
          // just accept it
//        int numwrite=fputs("\n/* Errors encountered while cleaning up */\n", stream); 
        }
      }// next i
    }


    // Loop while there are some classes being released.
    // If no more classes are being release, 
    //   then either we are done, or 
    //   (there is a circular reference) need to be more forceful

    if (true)// house of cards approach!
    {
      bool bLetGo = false;
      {
        bool bOneFound = false;
        bLetGo = false;
        // go through the entire list and 
        //  find those entities which are only referenced once and 
        //  release them!
        for (int i = m_ptrArrayAgito.GetSize()-1; 
                 i >= 0 ; 
                 i--)
        {
          try{
            // problem with the fact that I have references to objects
            CBaseStep* pV= (CBaseStep*)m_ptrArrayAgito.GetAt(i);
            if (NULL != pV){
              ASSERT_VALID( pV);
              if (1 <= pV->getRefCnt()){
                bLetGo = true;
#ifdef  EXPOSE      
                fprintf( g_errorLog, 
                  "unfreed object encountered in step::garbage_collection, m_ptrArrayAgito[ %d ] (#%d ) is a %s.\n", 
                  i, 
                  pV->getNum(), 
                  pV->m_szTheClass.GetBuffer( pV->m_szTheClass.GetLength()));
                pV->m_szTheClass.ReleaseBuffer();
#endif//EXPOSE   
                pV->release();
              }
            }
          }
          catch(...){
            // write something to the bottom
            TRACE1(" m_ptrArrayAgito[ %d ] already deleted. \n", i);
#ifdef  EXPOSE      
            fprintf( g_errorLog, " m_ptrArrayAgito[ %d ] already deleted. \n", i);
#endif//EXPOSE   
          }
        }// next i
      }// while ( bLetGo );
    }// fi
#ifdef  EXPOSE      
  fprintf( g_errorLog, "\n Deleting remaining objects.\n");
#endif//EXPOSE   
    if (true) {
      // now since there are no references to worry about, delete the classes
      for (int i = m_ptrArrayAgito.GetSize()-1; 
               i >= 0 ; 
               i--)
      {
        try{
          // problem with the fact that I have references to objects
            CBaseStep* pV= (CBaseStep*)m_ptrArrayAgito.GetAt(i);
            if (NULL != pV){
#ifdef  EXPOSE      
                fprintf( g_errorLog, "\n Deleting m_ptrArrayAgito[ %d ]\n", i);
#endif//EXPOSE   
                delete pV;
            }
        }
        catch(...){
          // just accept it, 
          // There is a reference to your object which you are deleting, 
          //  so what,  its the end of the show
          //E:\Program Files\Microsoft Visual Studio\VC98\CRT\SRC\DBGHEAP.C         
          // Error if freeing incorrect memory type 
          //        _ASSERTE(pHead->nBlockUse == nBlockUse);
          //_free_dbg_lk(void * 0x03d89900, int 1) line 1084 + 43 bytes

          TRACE1("m_ptrArrayAgito[ %d ] has been deleted but entry remains.\n", i); 
#ifdef  EXPOSE      
          fprintf( g_errorLog 
            ,"m_ptrArrayAgito[ %d ] has been deleted but entry remains.\n"
            , i);
#endif//EXPOSE   
        }
      }// next i
    }// fi


    // delete all classes
    m_ptrArrayAgito.RemoveAll();
  }
  catch(...){
    // just accept it
//  int numwrite=fputs("\n/* Errors encountered while cleaning up */\n", stream); 
#ifdef  EXPOSE      
    fprintf( g_errorLog, "Errors encountered while cleaning up.\n");
#endif//EXPOSE   
  }
  return ;
}

