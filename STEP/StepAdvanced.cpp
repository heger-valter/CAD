// StepAdvanced.cpp: implementation of the advanced_brep Step class.
//
#include <LIMITS.H>//UINT_MAX
#include <FLOAT.H>// DBL_MAX, FLT_MAX
#include "math.h"// fabs
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
#include "CircleStep.h"
#include "Poly_loopStep.h"
#include "SurfaceStep.h"
#include "Axis2_Placement_3dStep.h"
#include "Elementary_surfaceStep.h"
#include "Connected_face_setStep.h"
#include "Faceted_brepStep.h"
#include "Next_assembly_usage_occuranceStep.h"
#include "Assembly_component_usageStep.h"
#include "Face_boundStep.h"
#include "FaceStep.h"
#include "Advanced_faceStep.h"
#include "Face_surfaceStep.h"
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
#include "CircleStepPtrArray.h"
#include "Advanced_brep_shape_representationStep.h"
#include "Cylindrical_surfaceStep.h"
#include "PlaneStep.h"
#include "agito.h"
//#include "VersionNo.h"// Micro$lop's file used from incrementing the version number

#include "Shape_definition_representationStep.h"
#include "Product_definition_shapeStep.h"
#include "Product_definitionStep.h"
#include "ProductStep.h"
#include "Mechanical_contextStep.h"
#include "Application_context.h"
#include "Design_contextStep.h"
#include "Product_definition_formation_with_specified_sourceStep.h"
#include "AddressStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern int iRepresentationStepNum ;//= 0;// for advanced

#if 0
HANDLE  myHinstDLL;
void dllEntryPoint(HANDLE  hinstDLL){
  myHinstDLL = hinstDLL;
}
BOOL WINAPI DllMain(
  HINSTANCE hinstDLL,  // handle to the DLL module
  DWORD fdwReason,     // reason for calling function
  LPVOID lpvReserved   // reserved
);

void versionNo() 
{
  // TBD
  // extract the version info VS_VERSION_INFO from the properties rather than copying it from versionNum.h
  struct my_VS_VERSION_INFO {
    WORD  wLength; 
    WORD  wValueLength; 
    WORD  wType; 
    WCHAR szKey[1]; 
    WORD  Padding1[1]; 
    VS_FIXEDFILEINFO Value; 
    WORD  Padding2[1]; 
    WORD  Children[1]; 
  } ;

  //DllEntryPoint
  
  LPTSTR lptstrFilename;
  DWORD nSize = _MAX_PATH + _MAX_FNAME + 1;
  lptstrFilename = new CHAR[nSize ];
  DWORD dm = GetModuleFileName( (HMODULE) myHinstDLL, lptstrFilename, nSize ); 
  if (dm) {
    DWORD zero;
    LPDWORD lpdwHandle = &zero;
    DWORD rv = GetFileVersionInfoSize( lptstrFilename,    
                                       lpdwHandle); 
    if (rv) {
      LPVOID lpData = new char[rv];
      int i =GetFileVersionInfo( lptstrFilename, (DWORD)myHinstDLL, rv, lpData) ;
      if (i) {
        my_VS_VERSION_INFO* pV = (my_VS_VERSION_INFO*)lpData;
        // really should use VS_VERSION_INFO
        WORD   wLength      = pV->wLength;
        WORD   wValueLength = pV->wValueLength;
        WORD   wType        = pV->wType;
        WCHAR* pKy          = pV->szKey;
      }
      else {
        DWORD dw = GetLastError();
      }
    }
    else {
      DWORD dw = GetLastError();
    }
  }
  else {
    DWORD dw = GetLastError();
  }
}
#endif 


#define Id CObject*;
#if 0
// see Braid, Hillyard, Stroud "Stepwise construction of polyhedra in geomeric modeling"  
//  Mathematical methods in computer graphics and design, p123-141 AP, london, 1980

// basis Low level Euler ops

 // make edge vertex
HRESULT  mev_EulerOp( Id s, CFaceStep* pF1, CFaceStep* pF2, Id v1, Id v2, Id v3, Id v4, double x, double y, double z)
{
  Solid *oldsolid;

  return E_FAIL;
}
 // kill edge vertex
// inverse of mev
HRESULT  kev_EulerOp(s, CFaceStep* pF, v1, v2)
{
  return S_OK;
}
 // make edge face
HRESULT  mef_EulerOp(s, f1, v1, v2, v3, v4, CFaceStep* pF2)
{
  return S_OK;
}
 // kill edge face
HRESULT  kef_EulerOp(s, CFaceStep* pF, v1, v2)
{
  return S_OK;
}

// make vertex face solid
HRESULT  mvfs_EulerOp(s, CFaceStep* pF, v, double x, double y, double z)
{
  return S_OK;
}
 // kill vertex face solid
HRESULT  kvfs_EulerOp(s)
{
  return S_OK;
}
 // kill edge make ring
HRESULT  kemr_EulerOp(s, CFaceStep* pF, v1, v2)
{
  return S_OK;
}
 // kill edge kill ring
HRESULT  kekr_EulerOp()
{
  return S_OK;
}

//  make face, kill ring hole
// aka
HRESULT mfkrh_EulerOp( s, CFaceStep* pF1, v1, v2, CFaceStep* pF2)
{
  return S_OK;
}
#endif 

#if 0
// non basis low level Euler ops
HRESULT lmev_EulerOp( he1, he2, v, double x, double y, double z)
{
  return S_OK;
}

HRESULT lmef_EulerOp( he1, he2, CFaceStep* pF)
{
  return S_OK;
}
// spitting a lowwp into two components
HRESULT lkemr_EulerOp( he1, he2)
{
  return S_OK;
}
// high level Euler ops
fhe_EulerOp

#endif 


/*
I decided that the more efficient way 
was to overload the agitoPtrArray.Add() method, 
which would try to add entries in the middle 
of the list at unoccupied entries.  
This is far more efficient than trying to fix 
the problem after the damage has been done.  
However, there might be a time when I retreat 
to that solution 
once again if things don't play out.
*/
// condense the array, remove zero entries
HRESULT step::condenseArray()
{ 
  // there are errors in here
  //static // why
	int k ; 
	k = m_ptrArrayAgito.GetSize()-1; 
	for (int i=1; i< m_ptrArrayAgito.GetSize()/2 -1 ;i++){
		if (NULL == m_ptrArrayAgito.GetAt(i)){

      for ( ; k > m_ptrArrayAgito.GetSize()/2 + 1; k--){
        if (i >= k) return S_OK;
				CBaseStep* pBaseStep = (CBaseStep* )m_ptrArrayAgito.GetAt(k);
				if (NULL!=pBaseStep) {
  				ASSERT( k == pBaseStep->m_g_ptrArrayIndex ); 
          if (k != pBaseStep->m_g_ptrArrayIndex ) {
            return E_FAIL;
          }
				  pBaseStep->m_g_ptrArrayIndex = i;
  				m_ptrArrayAgito.SetAt(i, pBaseStep);
          
          //pBaseStep->Rehash( i);

          m_ptrArrayAgito.RemoveAt(k);
//        decCount();
          // once you remove it, all the other indicies are out of synch
          for (int l=k; l < m_ptrArrayAgito.GetSize(); l++) { 
            pBaseStep = (CBaseStep* )m_ptrArrayAgito.GetAt(l); 
            pBaseStep->m_g_ptrArrayIndex = l;
          }
          k--;
				  break;
        }else {
          ASSERT( k == m_ptrArrayAgito.GetSize()-1 );
          m_ptrArrayAgito.RemoveAt(k);
//        decCount();
        }
			}// next k
			if((m_ptrArrayAgito.GetSize()/2)>k){
        return S_OK;
			}
		}// fi NULL
	}// next i
  return S_OK;
}


#if 0
// calculate the polygon polygon intersections
// Currently commented out, but needed for further enhancements
HRESULT step::polyXpolyFaceted( CFace_surfaceStep *pFace_surfaceStepOnPosFeature, 
                                CFace_surfaceStep *pFace_surfaceStepOnNegFeature,
                                CPtrArray* pPolyIntersectionPoints )// insersection point on polyon of 
{
  CPlaneStep* pPlaneStepOnPosFeature = dynamic_cast<CPlaneStep*>
    (pFace_surfaceStepOnPosFeature->m_pFace_geometry);
  if (NULL != pPlaneStepOnPosFeature ){
    CPlaneStep* pPlaneStepOnNegFeature  = dynamic_cast<CPlaneStep*>
      (pFace_surfaceStepOnNegFeature->m_pFace_geometry);
    if (NULL != pPlaneStepOnNegFeature ){

      CDirectionStep* pIntersection= NULL; 
      // calculate the direction of the intersection edge
      pIntersection=crossProduct( *pPlaneStepOnPosFeature->m_rPosition.m_pAxis, 
                                  *pPlaneStepOnNegFeature->m_rPosition.m_pAxis);

      if (!pIntersection->withinTol()){
        //calculate a point on the direction
        // project the plane origin to the direction
        CVectorStep* pp1mp0 = new 
          CVectorStep ( pPlaneStepOnPosFeature->m_rPosition.m_rLocation, //po
                        pPlaneStepOnNegFeature->m_rPosition.m_rLocation);//ipp
        CCartesian_pointStep *pPointOnLine= new 
          CCartesian_pointStep ( pPlaneStepOnPosFeature->m_rPosition.m_rLocation);

        // project q1mq0 into plane P0, project left1 and up1 into plane p0, and add all to pointOnLine
        if ( restol2 < pp1mp0->getLength2()){
          // n1 -= (dotProd (n1, noLeft) * Left + dotProd(n1, noUp) * up);
          // grahamSchmidt();
          // grahamSchmidt()
          {
            CVectorStep* pUp = new CVectorStep(* pPlaneStepOnPosFeature->m_rPosition.m_pRef_direction);
            pUp->normalize(); 

            double dp = dotProduct( *pp1mp0, *pUp);
            *pUp *= dp;
            *pPointOnLine += *pn1 ;

            CVectorStep* pAxis = new CVectorStep(* pPlaneStepOnPosFeature->m_rPosition.m_pAxis);
            pAxis->normalize();
            CVectorStep* pLeft = crossProduct( *pAxis, *pUp);
            pLeft ->normalize();

            dp = dotProduct( *pp1mp0, *pLeft);
            *pLeft *= dp;
            *pPointOnLine += *pLeft;
          }
        }

        CVectorStep *pVectorStep = new CVectorStep (*pIntersection); 
        CLineStep* pLineStep = new CLineStep(*pPointOnLine, *pVectorStep, NULL );// wh 7/24/01
        double dStartParam =  DBL_MAX;
        double dEndParam   = -DBL_MAX;
        // trim the infinite edge to within the bounds
        // there is only one bound right now, enclosing a convex region because CPolygon is convex
        for ( int ib = 0; ib < pFace_surfaceStepOnNegFeature->bounds->GetSize(); ib++){
          CFace_boundStep* pFace_boundStep= (CFace_boundStep*)
            pFace_surfaceStepOnNegFeature->bounds->GetAt(ib);
          CEdge_loopStep* pELoop = dynamic_cast<CEdge_loopStep*>(pFace_boundStep->m_bound);
          int ivm1 = pELoop->paPolygonVertices->GetSize()-1; 
          for (int iv = 0; iv < pELoop->paPolygonVertices->GetSize(); iv++){
            edgeXedgeFaceted( ivm1, iv, pELoop, dStartParam, dEndParam, pLineStep, pPolyIntersectionPoints);
            ivm1 = iv;
          }// next iv
        }// next ib

      }//fi
    }//fi
  }//fi

  return S_OK;
}
#endif

// build the features 
HRESULT step::buildFeaturesFaceted(void){
/*
    CPtrArray* pManifold_solid_brepStepPtrArray = new CPtrArray( );
    pManifold_solid_brepStepPtrArray->SetSize( GetScribView()->m_modelarray.GetSize());
    for ( int im =0; im < GetScribView()->m_modelarray.GetSize();im++ ) {
      CModel* pModel = (CModel*)GetScribView()->m_modelarray.GetAt(im);
      CManifold_solid_brepStep *pManifold_solid_brepStep = 
        new CManifold_solid_brepStep( (CBaseStep*)pModel, NULL );
    }
    CPtrArray* pFaceted_solid_brepStepPtrArray = new CPtrArray( );
    pFaceted_solid_brepStepPtrArray->SetSize( GetScribView()->m_modelarray.GetSize());
    for ( int im =0; im < GetScribView()->m_modelarray.GetSize();im++ ) {
      CModel* pModel = (CModel*)GetScribView()->m_modelarray.GetAt(im);
      CFaceted_brepStep*pFaceted_solid_brepStep = 
        new CFaceted_brepStep( (CBaseStep*)pModel, NULL );
      if ( 1 ) {
        pFaceted_brepStep->Serialize(ar);
      }
    }
*/
  return S_OK;
}


// we still need this for advanced BREPs when we do a glue operation
// maybe might do a glue operation for FACETED_BREP as well
HRESULT step::findCoincidentSurfacesFaceted( int is, // index of surface on positive feature Cthing 
                                                   //which we are intersecting for coincidence
                                             int it, // index of thing containing negative feature
                                             CPtrArray* p_FaceStepPtrArray
                                           )
{
#ifdef FINDCOINCIDENTSURFACESFACETED
  for (int js = 0; js < GetScribView()->m_surfacearray.GetSize(); js++){
    if (js != is){
      CSurface* pSurface_js = (CSurface*)GetScribView()->m_surfacearray.GetAt( js);
      if ( pSurface_js->MemberOfObject != it){
        for ( int ik = pSurface_js->FirstPolygon;
                  ik < pSurface_js->FirstPolygon + pSurface_js->polysinsurface; 
                  ik++){                
          CAdvanced_faceSte* pAdvanced_faceSte_ik = (CAdvanced_faceStep* )
            pAdvanced_faceStepPtrArray->GetAt(ik);
          CPlaneStep* pPlaneStep_ik= dynamic_cast<CPlaneStep* >( pAdvanced_faceSte_ik);
          //pAdvanced_faceSte_ik->bounds->GetSize()
          if (NULL != pPlaneStep_ik){
            CAdvanced_faceStep* pAdvanced_faceStep = (CAdvanced_faceStep* )
              pAdvanced_faceStepPtrArray->GetAt(is);
            CPlaneStep* pPlaneStep= dynamic_cast<CPlaneStep* >( pAdvanced_faceStep);
            // determine if the surfaces are parallel
            CDirectionStep parallel( pPlaneStep_ik->m_rPosition.m_pAxis); 
              parallel.crossProd( *pPlaneStep_ik->m_rPosition.m_pAxis, 
                                  *pPlaneStep->m_rPosition.m_pAxis);

            if (parallel.withinTol()){
              // now check if they are indeed coincident
              //calculate distance between plane and point
              bool bOnSurface = pPlaneStep_ik->onSurface( pPlaneStep->m_rPosition.m_rLocation);
              if ( bOnSurface ){
                // check for loop containment!
                bool bLoopContainment = false;
                int iNumberVertices = 1;
                for (int k=0; k< iNumberVertices; k++){
                  // calculate vector on outer bound
                  CVectorStep 
                    loopVector( pPlaneStep_ik->m_rPosition.m_rLocation ,  
                                pPlaneStep_ik->m_rPosition.m_rLocation);
                  // calc vector from outer_bound to [inner]bound
                  //CPolygon* pPoly= (CPolygon* )GetScribView()->m_polygonarray.GetAt(ik);
                  CFace_boundStep* pFace_boundStep = (CFace_boundStep* ) pAdvanced_faceStep_ik->bounds->GetAt(0);
                  CVertex_pointStep* pVertex_pointStep  =  NULL
                    //pVertex_pointStepPtrArray->GetAt(pPoly->VertexHead)
                    ;
                  CVectorStep 
                    vectorEndpointToCenter(  pPlaneStep_ik->m_rPosition.m_rLocation,//pVertex_pointStep->m_r_vertex_geometry,  
                                             pPlaneStep_ik->m_rPosition.m_rLocation);
                  CVectorStep cp(loopVector);
                  cp.crossProd( loopVector, vectorEndpointToCenter);
                  //CVectorStep vdp;
                  double dp = dotProduct( cp, pPlaneStep_ik.m_rPosition.m_rLocation);
                  bLoopContainment = (dp > -restol)? true: false;
                  // assumption here that there is no crossing over
                  // to really be safe you should do this for all the perimeter points
                  if (!bLoopContainment){
                    break;
                  }
                }
                if (bLoopContainment) {
//                  pPlaneStep_ik->aCoincidentCollection.Add( (void*)pPlaneStep);
                }
              }//bOnSurface 
            }//parallel.withinTol
          }//NULL != pPlaneStep_ik
          else {
            assert(false);
          }
        }//ik
      }//fi
    }//fi
  }
#endif
  return S_OK;
}

// calculate the face-edge intersection
// each edge is oriended ccw, henc wh just have to make sure that they are properly inserted into the list
HRESULT step::faceXedgeAdvanced( CAdvanced_faceStep *pAdvanced_faceStepOnPosFeature,
                                 CEdge_loopStep*    pELoopN,      // loop corresponding to neg feature
                                 double&            dStartParam,  // start parameter on line0
                                 double&            dEndParam,    // end parameter on line0
                                 CrcPtrArray*       pLoopIntersectionPoints,  // collection of intersection 
                                                                              //points on polygon
                                 unsigned int &     riStartIndex, // index of startpoint
                                 unsigned int &     riEndIndex    // index of endpoint
                               , CCartesian_pointStepPtrArray*& pCartesian_pointStepPtrArray
                               )
{ 
  HRESULT hr = S_OK;

  int iInsertionIndex = 0;
  int iAdditionIndex = 0;// how far from the end do you insert these??

  for (int iv = 0; iv < pELoopN->GetSize(); iv++){
    // create an edge on neg features bounded , that edge is oriented ccw, 
    //  hence the intersections are also oriented ccw as well, 
    //  provided that the last one was not encountered first!
    CPlaneStep* pPlaneStepOnPosFeature = dynamic_cast<CPlaneStep*>
      (pAdvanced_faceStepOnPosFeature->m_pFace_geometry);
   // int iNumIntersection=0;
    // create an edge on neg features bounded 

    COriented_edgeStep* pOriented_edgeStep = pELoopN->GetAt(iv  );

    // intersect this edge with the plane
    if( (NULL != pOriented_edgeStep)  
      ){

      CVertex_pointStep* pVertex_pointStep0 = dynamic_cast<CVertex_pointStep*>
        (pOriented_edgeStep->GetEdge_start()) ;
      CCartesian_pointStep* pPointStep0 = dynamic_cast<CCartesian_pointStep*>
        (pVertex_pointStep0->m_p_vertex_geometry);
      
      CVertex_pointStep* pVertex_pointStep1 = dynamic_cast<CVertex_pointStep*>
        (pOriented_edgeStep->GetEdge_end()) ;
      CCartesian_pointStep* pPointStep1 = dynamic_cast<CCartesian_pointStep*>
        (pVertex_pointStep1->m_p_vertex_geometry);

      intersectionType intersection = noIntersection;//unknownSegmentIntersection 
      double paramU, paramV,
             paramT[2];

      CrcPtrArray* pEdgeIntersectionPoints = NULL;
      try{
        pEdgeIntersectionPoints = new CrcPtrArray();
      } catch (...){
        return E_OUTOFMEMORY;
      }
    
      CEdge_curveStep *pEdge_curveStep = dynamic_cast<CEdge_curveStep*>
        (pOriented_edgeStep->m_pEdge_element);
      CLineStep *pLineStep = dynamic_cast<CLineStep*>
        (&(pEdge_curveStep->m_rEdge_geometry));

      hr = 
        pPlaneStepOnPosFeature->intersect( pLineStep , 
                                           intersection, 
                                           pEdgeIntersectionPoints, 
                                           paramU, 
                                           paramV,
                                           paramT );
      if (FAILED( hr)){

//      delete pEdge;

        return hr;
      }
      if ( noIntersection != intersection){
/*
  //    CDirectionStep faceLeft(NULL, pEdge->m_dMagnitude );
        containment            bContains=unknownContainment;
        double dParam;
        // wait, not so fast, we have to make sure that intersection point is inside FOB
        pELoopN->contains( (CCartesian_pointStep*)pEdgeIntersectionPoints->GetAt(0), bContains, (pEdge->m_pOrientation), dParam);
        if (out==bContains){
          intersection = noIntersection ;
        }
*/
#if 1
        if ( startpointIntersection == intersection) {
          // find out where the surface is to the left of the traversal direction
          // if edge vector is antiparellel to surface normal, start point
          // if edge vector is parallel to surface Normal, endpoint
          double dp = 
            dotProduct( *(pPlaneStepOnPosFeature->m_pPosition->m_pAxis)
            , *(pLineStep->m_pDir->m_pOrientation)
            );
          if (dp>0){
//          if (pLoopIntersectionPoints->GetAt( pLoopIntersectionPoints->GetSize()-1) != (void*)pCartesian_pointStep0){
              riStartIndex = pLoopIntersectionPoints->Add((void*)pLineStep->m_pPos);
//          }
//          else {
//            riStartIndex = pLoopIntersectionPoints->GetSize()-1;
//          }
          } else if (dp<0){
            riStartIndex = 0;
//          if (pLoopIntersectionPoints->GetAt( iInsertionIndex) != (void*)pCartesian_pointStep0){
              pLoopIntersectionPoints->InsertAt( iInsertionIndex, (void*)pLineStep->m_pPos);
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
                      , *(pLineStep->m_pDir->m_pOrientation)
                      );
          if (dp>0){
            riEndIndex = pLoopIntersectionPoints->Add((void*)pLineStep->m_pPos1);
          } else if (dp<0){
            riEndIndex = 0;
            pLoopIntersectionPoints->InsertAt(iInsertionIndex , (void*)pLineStep->m_pPos1);
            iInsertionIndex++;
          } else{
            TRACE0("coincidence??\n");
          }
        }  
        else if ( interiorIntersection == intersection) {

          // small problem in that intersection is sometimes unnecssary 
          //  because the loop goes outside the outer_bound and 
          //  has not been contained as in MERGE_BOUNDS_INTERSECTION_ADV ! // wh 02/25/02

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
                      , *(pLineStep->m_pDir->m_pOrientation)
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
            pAdvanced_faceStepOnPosFeature->contains( 
                  (CCartesian_pointStep*) pEdgeIntersectionPoints->GetAt(0)
                , bContains
                //, pFaceNormal 
                , rdParam                    
                ); 

            if ( out != bContains )// really should be    (on == bContains)
            {
#if 0
              if (0 != iv){ 
                if ((pELoopN->GetAt(iv  ) != pCartesian_pointNew ) && 
                    (pELoopN->GetAt(ivm1) != pCartesian_pointNew ) ){
                  // also double check that this isn't an endpoint

                  pELoopN->InsertAt( iv,(void*)pCartesian_pointNew );
                  iv++;
                }
              }
              else {
                if ((pELoopN->GetAt(iv  ) != pCartesian_pointNew ) && 
                    (pELoopN->GetAt(ivm1) != pCartesian_pointNew ) ){
                  // do as above

                  pELoopN->Add( (void*)pCartesian_pointNew );
                }
              }
              // also need to add them to the pos surface's loops
#endif
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
/*
          if (-1) {
            faceXedgeAdvancedCoincident( pPlaneStepOnPosFeature
                                      , pELoopN                     // loop corresponding to neg feature
                                      , pLoopIntersectionPoints     // collection of intersection 
                                                                    //     points on polygon
                                      , riStartIndex                // index of startpoint
                                      , riEndIndex                  // index of endpoint
                                      , pCartesian_pointStep0 
                                      , pCartesian_pointStep1
                                      , iInsertionIndex
                                      );

          }
*/
        }
        else {
          for (int i = 0; i< pEdgeIntersectionPoints->GetSize();i++){
             delete pEdgeIntersectionPoints->GetAt(i);
          }
        }
#endif
      }
      else {
  //        for (int i = 0; i< pEdgeIntersectionPoints->GetSize();i++){
  //           delete pEdgeIntersectionPoints->GetAt(i);// wh 10/19/01
  //        }
      }
      delete pEdgeIntersectionPoints;

//    delete pEdgeN;
//      delete pEdge;

    }
    // if you modified the neg feature, you should split the face into two as well
//    ivm1 = iv;
  }// next iv

  return S_OK;
}

#if 0

// build the product structure
HRESULT step::buildProductStructureAdvanced( FILE*                  stream, 
                                             stepArchive&           ar,
                                             agitoAssembly*         pAssembly,
                                             CRepresentationStep*&  pRepresentationStep , 
                                             surfaceModelSelect     lSurfaceModelSelect,
                                             CPtrArray*&            pAdvanced_faceStepPtrArray)
{
  CShape_definition_representationStep* pShape_definition_representationStep = new 
    CShape_definition_representationStep();
  CProduct_definition_shapeStep *pProduct_definition_shapeStep = new
    CProduct_definition_shapeStep();
  pShape_definition_representationStep->m_pDefinition = pProduct_definition_shapeStep;
  pShape_definition_representationStep->m_pUsed_representation = pRepresentationStep;

  CProduct_definitionStep *pProduct_definitionStep = new
    CProduct_definitionStep();
  pProduct_definition_shapeStep->m_pDefinition = pProduct_definitionStep;
  CProduct_definition_formation_with_specified_sourceStep *pProduct_definition_formation_with_specified_sourceStep = new 
    CProduct_definition_formation_with_specified_sourceStep();
  CProductStep *pProductStep = new 
    CProductStep();
  CMechanical_contextStep *pMechanical_contextStep = new 
    CMechanical_contextStep();
  CApplication_context *pApplication_context = new 
    CApplication_context();

  pShape_definition_representationStep->Serialize( ar);

  CAddressStep *pAddressStep = new 
    CAddressStep;
  pAddressStep->Serialize( ar);

  return S_OK;
}
#endif


// build the assembly 
HRESULT step::buildAssembliesAdvanced( FILE*                  stream, 
                                       stepArchive&           ar,
                                       agitoAssembly*         pAssembly,
                                       CRepresentationStep*&  pRepresentationStep , 
                                       surfaceModelSelect     lSurfaceModelSelect,
                                       CPtrArray*&            pAdvanced_faceStepPtrArray)
{
  int iNumModels = GetScribView()->m_modelarray.GetSize();

  t_aManifold_solid_brepStep aManifold_solid_brepStep;
  for ( int im =0; im < pAssembly->GetSize(); im++ ) {
    agitoPart* pPart= (agitoPart*)pAssembly->GetAt( im);
    agitoComponent* pLump = (agitoComponent*)pPart->GetAt(0);

    agitoFeature* pFeature = (agitoFeature*)pLump->GetAt(0);// 2 of them
    int numShells = pFeature->GetSize();
    CClosed_shellStep*       pShellStep= NULL;
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
    
    pShellStep->m_pConnected_face_setStep->m_pRepresentation_itemStep =
      pTopological_representation_itemStep;
    CManifold_solid_brepStep * pManifold_solid_brepStep = new  
      CManifold_solid_brepStep(NULL, pShellStep);
    aManifold_solid_brepStep.Add( pManifold_solid_brepStep);

    CModel* pModel= (CModel*) GetScribView()->m_modelarray.GetAt( im);
    pModel->m_pAdvancedPool->AddStep( pManifold_solid_brepStep);
    pManifold_solid_brepStep->m_pTechnadrawEntitites->AddTech( pModel);
  }//im

  CRepresentation_contextStep *pGeometric_representation_contextStep = new 
    CGeometric_representation_contextStep(NULL);

  pRepresentationStep = new 
    CAdvanced_brep_shape_representationStep( aManifold_solid_brepStep
                                           , pGeometric_representation_contextStep
                                           , this
                                           );

  pRepresentationStep->aSurfaceModelSelect = lSurfaceModelSelect ;

#if 0
  if (im > 1) {
    step::buildProductStructure();
  }
#endif

  if (m_bWriteFile) 
  {
    pRepresentationStep->Serialize(ar); 
  }
//pGeometric_representation_contextStep->release();

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
/*
// build the shells 
HRESULT step::intersectFaces( FILE*                  stream, 
                              stepArchive&           ar,
                              CRepresentationStep*&  pRepresentationStep , 
                              surfaceModelSelect     lSurfaceModelSelect,
                              CPtrArray*&            pAdvanced_faceStepPtrArray)
{

  CShellStep *pShellStep0 = NULL;
  CShellStep *pShellStep1 = NULL;
  for (int i=0; i<pShellStep->m_pCFS_faces->GetSize(); i++ ){
    CAdvanced_faceStep *pAdvanced_faceStep = pShellStep->m_pCFS_faces->GetAt(i) ;
    CPlaneStep*         pPlaneStep0       = dynamic_cast<CPlaneStep*>        
      (pAdvanced_faceStep->m_pFace_geometry);
    pPlaneStep0->intersect(pPlaneStep1);
  }
  return S_OK;
}
*/
// build the shells 
HRESULT step::buildShellsAdvanced( FILE*                  stream, 
                                   stepArchive&           ar,
                                   CRepresentationStep*&  pRepresentationStep , 
                                   surfaceModelSelect     lSurfaceModelSelect,
                                   CPtrArray*&            pAdvanced_faceStepPtrArray
                                 , CCartesian_pointStepPtrArray*& pCartesian_pointStepPtrArray
                                 )
{
  #if     NOTIFICATION 
  if (m_bWriteFile){
    GetScribView()->Notify("(40%) step::buildShellsAdvanced");
  }
  #else //NOTIFICATION 
  #endif//NOTIFICATION 
  agitoAssembly assembly;// a part (model) has features (things)
  HRESULT hr  = 
  connectFacesAdvanced( &assembly
                      , pAdvanced_faceStepPtrArray
                      );
  if (FAILED( hr)){
    return hr;
  }
/*
  CRepresentation_itemStep *pRepresentation_itemStep = 
    new CRepresentation_itemStep();
  CTopological_representation_itemStep* pTopological_representation_itemStep = 
    new CTopological_representation_itemStep( pRepresentation_itemStep);
  // created because we are outputting both cfs & shell
  CConnected_face_setStep *pConnected_face_setStep = 
    new CConnected_face_setStep( NULL
                               , pTopological_representation_itemStep 
                               );
  CClosed_shellStep *pShellStep = 
    new CClosed_shellStep( pConnected_face_setStep
                         , pAdvanced_faceStepPtrArray 
                         );

  CThing* pThing = (CThing*) GetScribView()->m_thingarray.GetAt(0);
  pThing->m_pAdvancedPool->AddStep( pShellStep);
  pShellStep->m_pTechnadrawEntitites->AddTech( pThing);

  #if    1  
  pShellStep->demote();// treat all shells as open until everything works // wh 6/28/01
  #endif
*/

  // works but not really up to advanced_brep spec

  #ifdef  SHOWPROGRESS
  if (m_bWriteFile){
    GetScribView()->progressBarUpdate( 40);
  }
  #endif//SHOWPROGRESS
 

  #if     NOTIFICATION 
  if (m_bWriteFile){
    GetScribView()->Notify("(49%) Advanced CRepresentationStep::Serialize");
  }
  #else //NOTIFICATION 
  #endif//NOTIFICATION 



  agitoComponent aNegativeFeatures ;
  // go thru the list of features, and classify them, and add em to the correct list

  // turned off until the polyloops of neg feature are oriented CW & 
  //each edge if facing the correct way as well!
  findNegFeatureAdvanced( &assembly
                        , aNegativeFeatures
                        , pAdvanced_faceStepPtrArray
                        , pCartesian_pointStepPtrArray
                        );

  #ifdef  SHOWPROGRESS
  if (m_bWriteFile){
      GetScribView()->progressBarUpdate( 49);
  }
  #endif//SHOWPROGRESS
  addEulerFaceted( &assembly, aNegativeFeatures);

// intersect all faces of A vs B
// intersectFaces();
// calculate intersection loops
// calcXLoops();
// trim the faces down to (A-B) & (B-A)
// trimFaces();
// merge the intersections
// mergeThings();

   buildAssembliesAdvanced( stream 
                          , ar 
                          , &assembly 
                          , pRepresentationStep 
                          , lSurfaceModelSelect
                          , pAdvanced_faceStepPtrArray
                          ); 
  
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
#ifdef _DEBUG
      if (m_bWriteFile) {
        iraroArchive* p_ir = (iraroArchive*) ar.m_archives.GetAt(0);
        iraroArchive& ir = *p_ir ;
        ir << "/* mem leak detected while cleaning up */\n";
      }
#endif
    }
  #if     NOTIFICATION 
  if (m_bWriteFile){
    GetScribView()->Notify("(99%) returned from Advanced CRepresentationStep::Serialize");
  }
  #else //NOTIFICATION 
  #endif//NOTIFICATION
  #ifdef  SHOWPROGRESS
  if (m_bWriteFile){
    GetScribView()->progressBarUpdate( 99);
  }
  #endif//SHOWPROGRESS
    
  return S_OK;
}
// calculate the face-face intersections
HRESULT step::faceXfaceAdvanced( CAdvanced_faceStep *             pAdvanced_faceStepOnPosFeature, // positive features's face
                                 CAdvanced_faceStep *             pAdvanced_faceSteOnNegFeature, // neg features face
                                 CEdge_loopStepEx&               polyIntersectionPoints ,   // intersection point on polyon 
                                                                                              //  of pAdvanced_faceStepOnPosFeature
                                 bool &                          bGapsEncountered, 
                                 CPtrArray*&                     pAdvanced_faceStepPtrArray
                               , CCartesian_pointStepPtrArray*&  pCartesian_pointStepPtrArray
                               )
{

  CPlaneStep* pPlaneStepOnPosFeature = dynamic_cast<CPlaneStep*>
    (pAdvanced_faceStepOnPosFeature->m_pFace_geometry);

  if (NULL != pPlaneStepOnPosFeature ){
  
    CPlaneStep* pPlaneStepOnNegFeature  = dynamic_cast<CPlaneStep*>
      (pAdvanced_faceSteOnNegFeature->m_pFace_geometry);
    if (NULL != pPlaneStepOnNegFeature ){

      CDirectionStep* pIntersection= NULL; 
      // calculate the direction of the intersection edge
      pIntersection=crossProduct( *pPlaneStepOnPosFeature->m_pPosition->m_pAxis 
                                , *pPlaneStepOnNegFeature->m_pPosition->m_pAxis
                                );
      bool bPlanesIntersect = !pIntersection->withinTol();  
      if (!bPlanesIntersect ) { 
        if (
             pPlaneStepOnPosFeature->onSurface( 
               *(pPlaneStepOnNegFeature->m_pPosition->m_pLocation))
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
        //for(;ib<pAdvanced_faceSteOnNegFeature->GetSize(); ib++)
#pragma message("change this back!\n")
        if   (  0<pAdvanced_faceSteOnNegFeature->GetSize()      )
        {
          
          CFace_boundStep* pFace_boundStepN = (CFace_boundStep*)
            pAdvanced_faceSteOnNegFeature->GetFace_outer_bound();
          CEdge_loopStep* pELoopN = dynamic_cast<CEdge_loopStep*>
            (pFace_boundStepN->m_bound);
          CrcPtrArray loopIntersectionPoints;
          loopIntersectionPoints.SetSize( 0 
            , pELoopN->GetSize() 
            );
          unsigned int iStartIndex = UINT_MAX;// holds onto the index of the start point 
          unsigned int iEndIndex   = UINT_MAX;// holds onto the index of the end   point 

          faceXedgeAdvanced( pAdvanced_faceStepOnPosFeature
                          , pELoopN 
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
                  pAdvanced_faceStepOnPosFeature->contains( 
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
                  pAdvanced_faceStepOnPosFeature->trimEdge
                    ( &loopIntersectionPoints
                    , intersectionEdge
                    , bContains
                    );
#if 0
                  // point on neg surface are not added to its loops
                  containment bContainsN = unknownContainment;
                  // if it is outside, need to move point to boundary along intersection edge
                  pAdvanced_faceSteOnNegFeature->trimEdge // wh 02/10/02
                    ( &loopIntersectionPoints
                    , intersectionEdge
                    , bContainsN
                    );
#endif
                }
              }
            
              // we have to cut away both surfaces of the intersection

              #ifdef SPLIT_NEG_FEATURE_ADV
              {

                CDirectionStep* pDirInc = pIntersection;
//              if (((!pAdvanced_faceStepOnPosFeature->m_bSame_sense)  &&
//                   ( pAdvanced_faceSteOnNegFeature->m_bSame_sense))  ||
//                  (( pAdvanced_faceStepOnPosFeature->m_bSame_sense)  &&
//                   (!pAdvanced_faceSteOnNegFeature->m_bSame_sense)
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
                  pAdvanced_faceStepOnPosFeature->splitAdd( // new way adds in the intersection pts
                                                           &intersectionEdge 
                                                         );
#else
                  pAdvanced_faceStepOnPosFeature->split( // old way
                                                        &intersectionEdge 
                                                      );
#endif


                // trim the negative feature down to size for incorporation into resultant
                // If this is done, then the part which lies outside must be deleted!
                // N. B. intersectionEdge must be inside & oriented w/ matter on LHS
                  pAdvanced_faceSteOnNegFeature->split( 
                                                        &intersectionEdge
                                                      );

                }
              }//fi 
              #endif//SPLIT_NEG_FEATURE_ADV
            }
            iStartIndex = 0;
          
//        ASSERT( UINT_MAX != iEndIndex  );
          // did not start at the vertex of an edge
          if ( UINT_MAX == iEndIndex  ){
            iEndIndex  = 0;
          }

          // unfortunately some loops [formed by leaving the solid] 
          //  are [incorrectly] added CCW, fix that
          polyIntersectionPoints.sortIntersectionsCCW(   &loopIntersectionPoints
                                                     , pPlaneStepOnNegFeature
                                                     , pPlaneStepOnPosFeature 
                                                     , bGapsEncountered
                                                   //, true // because we are creating a hole      
                                                     );
//        }// fi NULL == pLoopXPts

        }// next ib

        
      }//fi
    delete pIntersection;
    }//fi
  }//fi

  condenseArray();// wh 01/20/02

  return S_OK;
}

// culling algorithm to reduce the number of calculations
// code to calculate if the bounding boxes intersect
// if they do, pass the calculations to do the actual intersections
HRESULT step::polyXpolyBBAdvanced( int ipp, // index of positive polygon
                                  int ipn, // index of negative polygon                                
                                  CEdge_loopStepEx* pPolyIntersectionPoints , // insersection point on polyon of 
                                                                            //  pAdvanced_faceStepOnPosFeature
                                  bool & bGapsEncountered, // is the loop gaps_in
                                  CPtrArray*&     pAdvanced_faceStepPtrArray,// collection of all face_surfaces             
                                  bool& bIntersect,
                                  CClosed_shellStep* pShell
                                , CCartesian_pointStepPtrArray*& pCartesian_pointStepPtrArray
                                )// do the bb intersect
{
  if((((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipp))->px[1]<=
      ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipn))->px[1]&&

      ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipp))->px[1]>=
      ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipn))->px[0])  ||

     (((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipp))->px[0]<=
      ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipn))->px[1]&&

      ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipp))->px[0]>=
      ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipn))->px[0])  ||

     (((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipn))->px[1]<=
      ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipp))->px[1]&&

      ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipn))->px[1]>=
      ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipp))->px[0])  ||

     (((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipn))->px[0]<=
      ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipp))->px[1]&&

      ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipn))->px[0]>=
      ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipp))->px[0])){


    if((((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipp))->py[1]<=
        ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipn))->py[1]&&
        
        ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipp))->py[1]>=
        ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipn))->py[0])  ||

       (((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipp))->py[0]<=
        ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipn))->py[1]&&

        ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipp))->py[0]>=
        ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipn))->py[0])  ||

       (((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipn))->py[1]<=
        ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipp))->py[1]&&

        ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipn))->py[1]>=
        ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipp))->py[0])  ||

       (((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipn))->py[0]<=
        ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipp))->py[1]&&

        ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipn))->py[0]>=
        ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipp))->py[0])){


          if((((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipp))->pz[1]<=
              ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipn))->pz[1]&&

              ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipp))->pz[1]>=
              ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipn))->pz[0])  ||

             (((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipp))->pz[0]<=
              ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipn))->pz[1]&&

              ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipp))->pz[0]>=
              ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipn))->pz[0])  ||

             (((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipn))->pz[1]<=
              ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipp))->pz[1]&&

              ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipn))->pz[1]>=
              ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipp))->pz[0])  ||

             (((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipn))->pz[0]<=
              ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipp))->pz[1]&&

              ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipn))->pz[0]>=
              ((CPolygon*) GetScribView()->m_polygonarray.GetAt(ipp))->pz[0])){

//they intersect
                  bIntersect = true;
                  faceXfaceAdvanced( (CAdvanced_faceStep *)pAdvanced_faceStepPtrArray->GetAt( ipp), 
                                     (CAdvanced_faceStep *)pAdvanced_faceStepPtrArray->GetAt( ipn),
                                     *pPolyIntersectionPoints , 
                                     bGapsEncountered,
                                     pAdvanced_faceStepPtrArray
                                   , pCartesian_pointStepPtrArray
                                 //, rNegThingsList
                                   );
                 }
          }
      }
  
  return S_OK;
}

// check the bb of the two things to see if they intersect!
HRESULT step::thingXthingBBAdvanced( agitoAssembly*                  pAssembly,// collection of all parts
                                    int                             itn,       // index of negative CThing
                                    CThing*                         pNegThing ,// the negative features whose faces will be 
                                    // intersected against all faces in the assembly
                                    CPtrArray*&                     pAdvanced_faceStepPtrArray,
                                    CClosed_shellStep*              pShell
                                  , CCartesian_pointStepPtrArray*&  pCartesian_pointStepPtrArray
                                  //, thingList&          rNegThingsList
                                  )
{
  for ( int ipp = 0; ipp < GetScribView()->m_polygonarray.GetSize(); ipp++){
    CPolygon *pPolygonOnPosFeature = (CPolygon *) GetScribView()->m_polygonarray.GetAt(ipp);
    int itp = pPolygonOnPosFeature->MemberOfObject ;
    if ( itp != itn ){
//    bool bThingFound = false;
//    for (int i=0; i< rNegThingsList.GetSize(); i++){
//      if ((int) rNegThingsList.GetAt(i) == itn ){
//        bThingFound=  true;
//        break;
//      }
//    }
//    if ( !bThingFound  )// dont subtract from neg features // wh 10/30/01 
      if((((CThing*) GetScribView()->m_thingarray.GetAt(itp))->px[1]<=
          ((CThing*) GetScribView()->m_thingarray.GetAt(itn))->px[1]&&

          ((CThing*) GetScribView()->m_thingarray.GetAt(itp))->px[1]>=
          ((CThing*) GetScribView()->m_thingarray.GetAt(itn))->px[0])||

         (((CThing*) GetScribView()->m_thingarray.GetAt(itp))->px[0]<=
          ((CThing*) GetScribView()->m_thingarray.GetAt(itn))->px[1]&&

          ((CThing*) GetScribView()->m_thingarray.GetAt(itp))->px[0]>=
          ((CThing*) GetScribView()->m_thingarray.GetAt(itn))->px[0])||

         (((CThing*) GetScribView()->m_thingarray.GetAt(itn))->px[1]<=
          ((CThing*) GetScribView()->m_thingarray.GetAt(itp))->px[1]&&

          ((CThing*) GetScribView()->m_thingarray.GetAt(itn))->px[1]>=
          ((CThing*) GetScribView()->m_thingarray.GetAt(itp))->px[0])||

         (((CThing*) GetScribView()->m_thingarray.GetAt(itn))->px[0]<=
          ((CThing*) GetScribView()->m_thingarray.GetAt(itp))->px[1]&&

          ((CThing*) GetScribView()->m_thingarray.GetAt(itn))->px[0]>=
          ((CThing*) GetScribView()->m_thingarray.GetAt(itp))->px[0])){


        if((((CThing*) GetScribView()->m_thingarray.GetAt(itp))->py[1]<=
            ((CThing*) GetScribView()->m_thingarray.GetAt(itn))->py[1]&&
        
            ((CThing*) GetScribView()->m_thingarray.GetAt(itp))->py[1]>=
            ((CThing*) GetScribView()->m_thingarray.GetAt(itn))->py[0])||

           (((CThing*) GetScribView()->m_thingarray.GetAt(itp))->py[0]<=
            ((CThing*) GetScribView()->m_thingarray.GetAt(itn))->py[1]&&

            ((CThing*) GetScribView()->m_thingarray.GetAt(itp))->py[0]>=
            ((CThing*) GetScribView()->m_thingarray.GetAt(itn))->py[0])||

           (((CThing*) GetScribView()->m_thingarray.GetAt(itn))->py[1]<=
            ((CThing*) GetScribView()->m_thingarray.GetAt(itp))->py[1]&&

            ((CThing*) GetScribView()->m_thingarray.GetAt(itn))->py[1]>=
            ((CThing*) GetScribView()->m_thingarray.GetAt(itp))->py[0])||

           (((CThing*) GetScribView()->m_thingarray.GetAt(itn))->py[0]<=
            ((CThing*) GetScribView()->m_thingarray.GetAt(itp))->py[1]&&

            ((CThing*) GetScribView()->m_thingarray.GetAt(itn))->py[0]>=
            ((CThing*) GetScribView()->m_thingarray.GetAt(itp))->py[0])){


              if((((CThing*) GetScribView()->m_thingarray.GetAt(itp))->pz[1]<=
                  ((CThing*) GetScribView()->m_thingarray.GetAt(itn))->pz[1]&&

                  ((CThing*) GetScribView()->m_thingarray.GetAt(itp))->pz[1]>=
                  ((CThing*) GetScribView()->m_thingarray.GetAt(itn))->pz[0])||

                 (((CThing*) GetScribView()->m_thingarray.GetAt(itp))->pz[0]<=
                  ((CThing*) GetScribView()->m_thingarray.GetAt(itn))->pz[1]&&

                  ((CThing*) GetScribView()->m_thingarray.GetAt(itp))->pz[0]>=
                  ((CThing*) GetScribView()->m_thingarray.GetAt(itn))->pz[0])||

                 (((CThing*) GetScribView()->m_thingarray.GetAt(itn))->pz[1]<=
                  ((CThing*) GetScribView()->m_thingarray.GetAt(itp))->pz[1]&&

                  ((CThing*) GetScribView()->m_thingarray.GetAt(itn))->pz[1]>=
                  ((CThing*) GetScribView()->m_thingarray.GetAt(itp))->pz[0])||

                 (((CThing*) GetScribView()->m_thingarray.GetAt(itn))->pz[0]<=
                  ((CThing*) GetScribView()->m_thingarray.GetAt(itp))->pz[1]&&

                  ((CThing*) GetScribView()->m_thingarray.GetAt(itn))->pz[0]>=
                  ((CThing*) GetScribView()->m_thingarray.GetAt(itp))->pz[0])){

                      surfXsurfAdvanced(  pAssembly, 
                                         itn, 
                                         pNegThing,
                                         pAdvanced_faceStepPtrArray, 
                                         pPolygonOnPosFeature
                                         , ipp
                                        ,  pShell
                                       , pCartesian_pointStepPtrArray
                                         //,       rNegThingsList
                                         );

                     }
              }
          }
    }// fi
  // now comes the fun part, those bounds which intersected the outer_bounds need to be stitched together

    //  stitchIntersectionsFromAllSurfaces();
  }//next ip
  
  return S_OK;
}

HRESULT step::boundsXboundsAdvanced( CAdvanced_faceStep*      pAdvanced_faceStepOnPosFeature, // positive features's face
                                    boundsIntersectBounds&  rBoundsXbounds,
                                    CrcPtrArray*            pPolyIntersectionPoints )// intersection point on 
                                                                          //  polygon of pAdvanced_faceStepOnPosFeature
{  
#if 1

  double dStartParam =  DBL_MAX;
  double dEndParam   = -DBL_MAX;

  CFace_outer_boundStep* pFace_outer_boundStep= (CFace_outer_boundStep*)
    pAdvanced_faceStepOnPosFeature->GetFace_outer_bound();
  CEdge_loopStep* pELoop = dynamic_cast<CEdge_loopStep*>(pFace_outer_boundStep->m_bound);

  CPlaneStep* pPlaneStepOnPosFeature = dynamic_cast<CPlaneStep*>
    (pAdvanced_faceStepOnPosFeature->m_pFace_geometry);
  CDirectionStep* pFaceNormal = pPlaneStepOnPosFeature->m_pPosition->m_pAxis;

  CCartesian_pointStep* pLast_point = (CCartesian_pointStep* )
    pPolyIntersectionPoints->GetAt( 
      pPolyIntersectionPoints->GetSize()-1);
  containment cPreviousContains= unknownContainment;
  double rdParam0;
  pFace_outer_boundStep->contains( 
    pLast_point, 
    cPreviousContains, 
    pFaceNormal 
    , rdParam0
    );

  for (int jv = 0; jv < pPolyIntersectionPoints->GetSize(); ){

    containment cContains;
    double rdParam;
    pFace_outer_boundStep->contains( 
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
        CDWordArray   pIntersectionParam ;//= new double[pELoop->m_aPolygonVertices.GetSize()] ;
        pIntersectionParam.SetSize(pELoop->GetSize(), 0);
        int id = 0;
        int ivm1 = pELoop->GetSize()-1; 
        for (int iv = 0; iv < pELoop->GetSize(); iv++){
          
          CrcPtrArray outerboundIntersectionPoints ;
          intersectionType intersection0 = unknownSegmentIntersection; 
          intersectionType intersection1 = unknownSegmentIntersection;

          int iBefore = outerboundIntersectionPoints.GetSize();
          lineEdgeGlanceAdvanced( ivm1, iv, pELoop, dStartParam, dEndParam, 
            pLineStep, &outerboundIntersectionPoints , intersection1, 
                                     intersection0);

          //watch it, we only care about interior intersection pts
          if (interiorIntersection == intersection1 ){
            pELoop->InsertAtPoint( iv++, (CCartesian_pointStep*) outerboundIntersectionPoints.GetAt(0) );
          }
          if (interiorIntersection == intersection0){
            pIntersectionParam.SetAt(id++, (DWORD)dStartParam);
            outerboundInteriorPoints.Add( (CCartesian_pointStep*) outerboundIntersectionPoints.GetAt(0));
          }
          ivm1 = iv;
        }// next iv

        for   (int j = 0; j < outerboundInteriorPoints.GetSize(); j++) {
          int     iCurMin=0;
          double  dMinParam = (double  )pIntersectionParam.GetAt(0);
          for (int i = 1; i < outerboundInteriorPoints.GetSize(); i++){
            if (dMinParam > (double  )pIntersectionParam.GetAt(i)) {
              iCurMin = i;
              dMinParam = (double  )pIntersectionParam.GetAt(i);
            }// fi
          }// next i
          // once all the intersections are found, they have to be inserted into the list CW
          if ((double)pIntersectionParam.GetAt(iCurMin) > restol) {
            if ((double)pIntersectionParam.GetAt(iCurMin) < (1.0e0 - 
                                                                     restol// tolrel
                                                                            )) {
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
#endif
  return S_OK;
}


HRESULT step::surfXsurfAdvanced( agitoAssembly*                 pAssembly// collection of all parts
                               , int                            itNeg       // index of negative CThing
                               , CThing*                        pNegThing // the negative features whose faces will be 
                                 // intersected against all faces in the assembly
                               , CPtrArray*&                    pAdvanced_faceStepPtrArray 
                               , CPolygon*                      pPolygonOnPosFeature  // The collection of all the 
                                                                                      //  face_surfaces in the assembly
                               , int                            ipp    
                               , CClosed_shellStep*             pShell
                               , CCartesian_pointStepPtrArray*& pCartesian_pointStepPtrArray
                               )
{
#if 1
  int ISO = pPolygonOnPosFeature->MemberOfSurface;
  if (-1 != ISO){
    CSurface* pSurfOnPosFeature= (CSurface*) GetScribView()->m_surfacearray.GetAt( ISO);
    // only for surf which exist
    if (0 != pSurfOnPosFeature->exists){

        // carve out the inside polygons
      if (-1 != pNegThing->firstpolyno) {

        bool bGapsEncountered = false;
        // hold onto the set of intersection points

        CEdge_loopStepEx polyIntersectionPoints;
        polyIntersectionPoints.SetSize( 0, 1 + pNegThing->lastpolyno - pNegThing->firstpolyno);

        // Implicit (could be false) assumption here in that the polygons are a part of the edge loop,
        //  and that neighbooring ones touch!!!!!
        for ( int ipn = pNegThing->firstpolyno; ipn <= pNegThing->lastpolyno; ipn++){
          bool bIntersect = false;// used to weed out spurious intersections
          CPolygon* pPolygonInside = (CPolygon*) GetScribView()->m_polygonarray.GetAt(ipn);
          int isi = pPolygonInside->MemberOfSurface;
          if (-1 != isi){
            CSurface* pSurfInside    = (CSurface*) GetScribView()->m_surfacearray.GetAt( isi);

            // only for surf which exist
            if (0 != pSurfInside->exists){         

              CAdvanced_faceStep *pAdvanced_faceStep = (CAdvanced_faceStep*) 
                pAdvanced_faceStepPtrArray->GetAt(ipn);// wh 02/18/02
              ASSERT_VALID( pAdvanced_faceStep);
              
              polyXpolyBBAdvanced( ipp, 
                                   ipn,
                                   &polyIntersectionPoints, 
                                   bGapsEncountered, 
                                   pAdvanced_faceStepPtrArray, 
                                   bIntersect ,
                                   pShell
                                 , pCartesian_pointStepPtrArray
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
            polyIntersectionPoints.RemoveAt( polyIntersectionPoints.GetSize()-1);
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
              polyIntersectionPoints.RemoveAt( polyIntersectionPoints.GetSize()-1);
            } 
            ASSERT_VALID(pDirNeg);
            delete pDirNeg;// wh 10/06/01
          }
        }

        try {
          CAdvanced_faceStep *pAdvanced_faceStepOnPosFeature = (CAdvanced_faceStep *)
            pAdvanced_faceStepPtrArray->GetAt(ipp);
          // create a poly loop which describes the intersection
          if ( 
              2 // was 0  // wh 5/25/01
                < polyIntersectionPoints.GetSize()){
            CEdge_loopStep *pEdge_loopStepIntersection = new 
              CEdge_loopStep;

            pEdge_loopStepIntersection->SetSize( polyIntersectionPoints.GetSize() );

            pEdge_loopStepIntersection->SetAt( 0, polyIntersectionPoints.GetAt(0) );
            pEdge_loopStepIntersection->SetAt( 1, polyIntersectionPoints.GetAt(1) );
            pEdge_loopStepIntersection->SetAt( 2, polyIntersectionPoints.GetAt(2) );

            if (NULL==pEdge_loopStepIntersection) {
              return E_OUTOFMEMORY;
            }// wh 10/17/01
            if (bGapsEncountered) {
  #ifdef _DEBUG
              pEdge_loopStepIntersection->m_szLabelName += " gaps_in ";
  #endif 
              pEdge_loopStepIntersection->m_bGap = true;
            }
            for (int i = 3; i < polyIntersectionPoints.GetSize(); i++){
              COriented_edgeStep* pIn = ( polyIntersectionPoints.GetAt(i));
              pEdge_loopStepIntersection->SetAt( i, pIn);
            }

            //need to make sure that [inner]bound is inside outer_bound
            // TBD
            boundsIntersectBounds boundsXbounds = unknownBoundsIntersection;

            boundsContainBoundsAdvanced( pAdvanced_faceStepOnPosFeature
                                       , boundsXbounds
                                       , &polyIntersectionPoints
                                       );

            // need to make sure that [inner]bounds does not intersect with outer_bound, 
            //   if it does , then need to stitch them together!
            if (intersectionBounds == boundsXbounds)
            {
              // merge together the two bounds
              //pAdvanced_faceStepOnPosFeature->bounds->GetAt(0);

              // wh 11/01/01
              // gives good results, 
              // but memory problems in that some dependent entities are prematurely deleted, 
              // while still referenced!

              #ifdef MERGE_BOUNDS_INTERSECTION_ADV 
              {
                boundsXboundsAdvanced( pAdvanced_faceStepOnPosFeature ,
                                      boundsXbounds,
                                      &(pEdge_loopStepIntersection->m_aPolygonVertices));
                if (NULL != pEdge_loopStepIntersection){
                  pAdvanced_faceStepOnPosFeature->makeIslands( pEdge_loopStepIntersection);
                }
              }
              #endif//MERGE_BOUNDS_INTERSECTION_ADV 
            }
            else if (disjointBounds == boundsXbounds)            {          
              //make sure bound is thrown away  
            }
            else if (insideBounds   == boundsXbounds)            {   
//            TRACE0("inside bound\n");
            }
            else if (outsideBounds  == boundsXbounds)            {
              #ifdef  MERGE_BOUNDS_INTERSECTION_ADV 
              {

              //replace outside bounds by inside bounds   
              if (1 < pAdvanced_faceStepOnPosFeature->GetSize() ) {
                CFace_boundStep* pFace_boundStep = 
                  pAdvanced_faceStepOnPosFeature->GetAt(1);
                CLoopStep* pLoopStep = pFace_boundStep->m_bound;
                CEdge_loopStep *pEdge_loopStep = dynamic_cast<CEdge_loopStep*>( pLoopStep);
                if (NULL != pEdge_loopStep ){
                  pEdge_loopStep->replace( pEdge_loopStepIntersection);
                }
              } else {
                CFace_boundStep* pFace_boundStep =  
                    new CFace_boundStep(  NULL, 
                                          pEdge_loopStepIntersection, 
                                          true, 
                                          NULL);
                pAdvanced_faceStepOnPosFeature->Add( pFace_boundStep);
                pEdge_loopStepIntersection->addRef(); // wh 01/27/02
              }
            }
            #endif//MERGE_BOUNDS_INTERSECTION_ADV 
           }
#if 0
            if ( (commonVertexInside == boundsXbounds)    ) 
            {
              CFace_boundStep* pFace_boundStep = (CFace_boundStep* )
                pAdvanced_faceStepOnPosFeature->GetFace_outer_bound();                

              pAdvanced_faceStepOnPosFeature->makeIslands(pEdge_loopStepIntersection);
            } 
            else 
            if ( (edgeScrapesInside  == boundsXbounds)    ) 
            {
              CFace_boundStep* pFace_boundStep = (CFace_boundStep* )
                pAdvanced_faceStepOnPosFeature->GetFace_outer_bound();                
              // more sophisticated in that it also removes an edge
              pAdvanced_faceStepOnPosFeature->makeIslands(pEdge_loopStepIntersection);
            }
#endif            
            // be careful and throw out [inner]bound outside the outer bounds!
            if ( (insideBounds       == boundsXbounds) || 
                 (commonVertexInside == boundsXbounds) || 
                 (edgeScrapesInside  == boundsXbounds)    ) 
            {
              CFace_boundStep* pFace_boundStep =  
                  new CFace_boundStep(  NULL, 
                                        pEdge_loopStepIntersection, 
                                        true //wh 05/21/01 since edges are oriented CW
                                        );
              if (NULL==pEdge_loopStepIntersection) {
                return E_OUTOFMEMORY;
              }// wh 10/17/01
              int ifb = 0;
              pAdvanced_faceStepOnPosFeature->AddFB( pFace_boundStep, ifb);
            } 
            else 
            { 
              pEdge_loopStepIntersection->release(); // wh 10/09/01
              pEdge_loopStepIntersection=NULL;   // wh 10/09/01
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
      }//fi
    }//fi
  }// isp    
#endif
  return S_OK;
}

// tbd should be a method of bounds
// check to see if the outer_bound contain the [inner]bounds
HRESULT step::boundsContainBoundsAdvanced( CAdvanced_faceStep*      pAdvanced_faceStepOnPosFeature, // positive features's face
                                          boundsIntersectBounds&  rBoundsXbounds,
                                          CEdge_loopStep*         pInner_boundPoints )// tested for [inner]bounds
                                                                                           // insersection point on 
                                                                                           //  polyon of pAdvanced_faceStepOnPosFeature
{
  CFace_outer_boundStep* pFace_outer_boundStep= (CFace_outer_boundStep*)
    pAdvanced_faceStepOnPosFeature->GetFace_outer_bound();
  CEdge_loopStep* pELoop = dynamic_cast<CEdge_loopStep*>(pFace_outer_boundStep->m_bound);

  int ivm1 = pELoop->GetSize()-1;     
  CPlaneStep* pPlaneStepOnPosFeature = dynamic_cast<CPlaneStep*>
    (pAdvanced_faceStepOnPosFeature->m_pFace_geometry);

  if (NULL != pPlaneStepOnPosFeature ){
    CDirectionStep* pFaceNormal = pPlaneStepOnPosFeature->m_pPosition->m_pAxis;

    pELoop->outerloopContainment( 
                                         pFaceNormal , 
                                         (pInner_boundPoints), 
                                         rBoundsXbounds);
  }//fi
  
  return S_OK;
}


// find the negative features based on the exists param
HRESULT step::findNegFeatureAdvanced( agitoAssembly*                  pAssembly,// 
                                      agitoComponent&                 aNegativeComponents,
                                      CPtrArray*&                     pAdvanced_faceStepPtrArray
                                    , CCartesian_pointStepPtrArray*&  pCartesian_pointStepPtrArray 
                                    )
{
#if     NOTIFICATION 
  if (m_bWriteFile){
    this->GetScribView()->Notify("Finding Negative Features");}
#endif//NOTIFICATION 
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
            //rNegThingsList.Add((void*)it);
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
          CAdvanced_faceStep *pAdvanced_faceStep = (CAdvanced_faceStep *)
            pShell->m_pCFS_faces->GetAt( jp); // wh 10/02/01            
          pShell->m_pCFS_faces->SetAt( jp, NULL);
          ASSERT_VALID( pAdvanced_faceStep);
          pAdvanced_faceStep->release();//wh   10/02/01
        }// fi
      }// fi
    }// next ip
    // 
  }// next it

  intersectNegFeatureAdvanced( pAssembly
                            , pAdvanced_faceStepPtrArray
                            , pCartesian_pointStepPtrArray   
                            );
  return S_OK;
}
    // now find the intersections of this CThing's surfaces with surfaces of other CThings
HRESULT step::intersectNegFeatureAdvanced( agitoAssembly*                 pAssembly
                                        , CPtrArray*&                    pAdvanced_faceStepPtrArray
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
    // wh 03/26/03
    {
      thingXthingBBAdvanced( pAssembly
                          , it
                          , pThing
                          , pAdvanced_faceStepPtrArray 
                          , pShell
                          , pCartesian_pointStepPtrArray 
                          );
    }
  }
  return S_OK;
}

// connnect the faces and shells together
HRESULT step::connectFacesAdvanced( agitoAssembly* pAssembly, 
                                   CPtrArray*& pAdvanced_faceStepPtrArray )
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
      new CClosed_shellStep( pConnected_face_setStep, pAdvanced_faceStepPtrArray );
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

      CPtrArray*      pAdvanced_faceStePtrArrayOnfeature = new CPtrArray;
      if (NULL==pAdvanced_faceStePtrArrayOnfeature ){
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
        new CClosed_shellStep( pConnected_face_setStep, pAdvanced_faceStePtrArrayOnfeature);
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

        if (-1 != pThing->firstpolyno) {          
          if (-1 != pThing->lastpolyno) {
            for (int j = pThing->firstpolyno; 
                      j 
                        <= 
                        pThing->lastpolyno; j++) {

#if _DEBUG
// Ralph, look here, why is j out of range?? wh 10/22/01
              // this was added when trying to debug ree89!
              ASSERT((GetScribView()->m_polygonarray.GetSize()) > j);

                if ( (GetScribView()->m_polygonarray.GetSize()) <= j) {
                  #ifdef  EXPOSE      
                    fprintf( g_errorLog, "\n something is wrong with the TasDraw m_polygonarray internal data structures \n m_polygonarray [%d]", j);
                    fprintf( g_errorLog, " is out of bound. m_polygonarray.GetSize() = %d */\n", GetScribView()->m_polygonarray.GetSize());
                  #endif//EXPOSE
                }

              ASSERT((pAdvanced_faceStepPtrArray->GetSize()) > j);
                if ((pAdvanced_faceStepPtrArray->GetSize()) <= j) {
                  #ifdef  EXPOSE      
                    fprintf( g_errorLog, "something is wrong with the pAdvanced_faceStepPtrArray[%d] > %d internal data structures ", j, (pAdvanced_faceStepPtrArray->GetSize()) );
                  #endif//EXPOSE
                }
#endif //_DEBUG

              if ( ((GetScribView()->m_polygonarray.GetSize()) <= j) ||
                   (    (pAdvanced_faceStepPtrArray->GetSize()) <= j)
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
              CAdvanced_faceStep*  pAdvanced_faceStep = (CAdvanced_faceStep*)
                (pAdvanced_faceStepPtrArray->GetAt( j));
              ASSERT(NULL!=pAdvanced_faceStep);
              if (NULL!=pAdvanced_faceStep)
              {
                ASSERT_VALID( pAdvanced_faceStep);
              
                ASSERT( it == pPolygon->MemberOfObject);
  //            pConnected_face_setStep->m_pCFS_faces = pAdvanced_faceStePtrArrayOnfeature;// not needed anymore
                int i = pAdvanced_faceStePtrArrayOnfeature->Add( pAdvanced_faceStep );
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

#if 0
// build the shells 
HRESULT step::buildShellsCSG( FILE*                 stream, 
                              stepArchive &         ar,
                              CClosed_shellStep *   pShellStep, 
                              CRepresentationStep*& pRepresentationStep , 
                              surfaceModelSelect    lSurfaceModelSelect,
                              CPtrArray*&           pAdvanced_faceStepPtrArray)
{
#if     NOTIFICATION 
  if (m_bWriteFile)
    GetScribView()->Notify("(40%) step::buildShellsAdvanced");
#else //NOTIFICATION 
#endif//NOTIFICATION 
#ifdef  SHOWPROGRESS
  if (m_bWriteFile)
      GetScribView()->progressBarUpdate( 40);
#endif//SHOWPROGRESS

    for ( int it =0; it < GetScribView()->m_thingarray.GetSize();it++ ) {
      CThing* pThing = (CThing*)GetScribView()->m_thingarray.GetAt(it);

      CModel* pModel = (CModel*)GetScribView()->m_modelarray.GetAt(pThing->BelongsToModelNo);
      if (!pModel->on){
      // since it might be possible to have surfaces without CThings, we have to do it this way
        if (-1 != pThing->firstpolyno) {
          
          if (-1 != pThing->lastpolyno) {
           for (int j = pThing->firstpolyno; j<=pThing->lastpolyno; j++) {
            // remove thing's poly
            for (int i = 0; i<pShellStep->m_pCFS_faces->GetSize(); i++){
              if (pShellStep->m_pCFS_faces->GetAt(i) == pAdvanced_faceStepPtrArray->GetAt(j)) {
                pShellStep->m_pCFS_faces->SetAt(i, NULL);
              }
            }//next i
  //          pEdge_loopPtrArray->SetAt(j, NULL);
            CPolygon *pPolygon=(CPolygon *)GetScribView()->m_polygonarray.GetAt(j);
            pAdvanced_faceStepPtrArray->SetAt(pPolygon->MemberOfSurface, NULL);
          }// next j
        }
       }
      }
      else {
        if (-1 != pThing->firstpolyno)           
        for (int j = pThing->firstpolyno; j<=pThing->lastpolyno; j++) {
          CAdvanced_faceStep*  pAdvanced_faceStep = (CAdvanced_faceStep*)(pAdvanced_faceStepPtrArray->GetAt(j));
          CPlaneStep*         pPlaneStep        = dynamic_cast<CPlaneStep*>        (pAdvanced_faceStep->m_pFace_geometry);
          if (pPlaneStep){
//            pPlaneStep->m_rLocation += pCartesian_tranformation_operator_3dStep ;
          }
        }
      }
//    CClosed_shellStep* pOriented_faceBasedSurfaceModel = 
//      new COriented_faceBasedSurfaceModel();

      
#if 0
      if ( 0 == stricmp( pThing->type,  "SURFACE") ) {
        //CSurfaceStep* pSurfaceStep = new CConical_surfaceStep();
      }
      CPresentable_textStep CPresentable_textStep CPresentable_textStep;
      else
      if (  0 == stricmp( pThing->type,  "POLYGON") ) {
        //CSurfaceStep* pSurfaceStep = new CConical_surfaceStep();
      }
      else
      if (  0 == stricmp( pThing->type,  "OBJECT") ) {
        //CSurfaceStep* pSurfaceStep = new CConical_surfaceStep();
      }
      else
#endif
      if (  0 == stricmp( pThing->type,  "CONIC") ) {
#if 1
        // we have to replace closed shell with this entry
        CPolygon *pPolygon = (CPolygon *)GetScribView()->m_polygonarray.GetAt(pThing->firstpolyno);
#else
        if ( faceBasedSurfaceModel == pRepresentationStep->aSurfaceModelSelect )
//      if (0 == strcmp(type, "Type 1")){
         CCartesian_pointStep* pLocation = new CCartesian_pointStep( NULL, 0.e0, 0.e0, 0.e0);
        CAxis2_placement_3dStep *pPos= new CAxis2_placement_3dStep( *pLocation);
        CSurfaceStep* pSurfaceStep = new 
          CConical_surfaceStep( *pPos, 0., 0.);
//          CGeometric_representation_itemStep* pGeometric_representation_itemStep= new 
//            CRight_circular_cylinderStep( *pCartesian_pointStep );
        //pThing->firstpolyno
        pSurfaceStep->Serialize(ar);
//      }
        // else {
        CSurface_of_linear_extrusionStep *pSurface_of_linear_extrusionStep = new 
          CSurface_of_linear_extrusionStep;
        //}
#endif
      }
      else
        if (  0 == stricmp( pThing->type,  "BLOCK") ) {
/*
          CSurfaceStep* pSurfaceStepTo= new CPlaneStep(NULL);
          CSurfaceStep* pSurfaceStepBo= new CPlaneStep(NULL);
          CSurfaceStep* pSurfaceStepLe= new CPlaneStep(NULL);
          CSurfaceStep* pSurfaceStepRi= new CPlaneStep(NULL);
          CSurfaceStep* pSurfaceStepFr= new CPlaneStep(NULL);
          CSurfaceStep* pSurfaceStepBa= new CPlaneStep(NULL);
*/
      }
      else {
      }
    }

//delete pCartesian_tranformation_operator_3dStepPtrArray ;

#if 0
  for (int jvm1 = 0; jvm1 < MAXTEXTITEMS; jvm1 ++){
    if (0 != txtable[jvm1].layer){
      CModel* pModel = GetScribView()->m_modelarray.GetAt(txtable[jvm1].tomodel];      
      CPresentable_textStep* pPresentable_textStep= 
        new CPresentable_textStep( txtable[jvm1].txt);
    }
  }
#endif
/*
  // find the negative feature
      for (int is = 0; is < GetScribView()->m_surfacearray.GetSize(); is++){
        CSurface* pSurface= (CSurface*)GetScribView()->m_surfacearray.GetAt(is);
        if ((it == pSurface->MemberOfObject)){
          CPolygon *pPolygon = (CPolygon *)GetScribView()->m_polygonarray.GetAt(pThing->firstpolyno);
          if (pPolygon->MemberOfSurface==is){
  //        if (0 == stricmp(GetScribView()->att[pSurface->attindex].name, pThing->parameter[16]))
            {
              if (0.0 == pSurface->exists){
//                pThingNegative = pThing;
                for (int ik=0;ik<it;ik++){// no, need to do the following ones as well, ask Ralph?
//                  pThingPositive = (CThing*)GetScribView()->m_thingarray.GetAt( ik);;
                  //subtractBraid( pThingPositive, pThingNegative );
                }
                break;
              }
        //    else{
        //      pThingPositive = pThing;
        //    }
            }
          }
        }
      }//next is  
*/

  if ( 1 ) {

#if     NOTIFICATION 
    GetScribView()->Notify("(49%) Advanced CRepresentationStep::Serialize");
#else //NOTIFICATION 
#endif//NOTIFICATION 
#ifdef  SHOWPROGRESS
  if (m_bWriteFile)
      GetScribView()->progressBarUpdate( 49);
#endif//SHOWPROGRESS

    pRepresentationStep->Serialize(ar);
    
#if     NOTIFICATION 
  if (m_bWriteFile)
    GetScribView()->Notify("(99%) returned from Advanced CRepresentationStep::Serialize");
#else //NOTIFICATION 
#endif//NOTIFICATION
#ifdef  SHOWPROGRESS
  if (m_bWriteFile)
      GetScribView()->progressBarUpdate( 99);
#endif//SHOWPROGRESS
    
  }

  return S_OK;
}
#endif

// parse CThing parameter for cylinder
float  grepThing( CThing *pThing){
  float fP3 = 0.0;
  for (int j=0;j<3;j++){
    char* pC0 = strchr( &(pThing->parameter[3+j][0]),'(');
    if (NULL == pC0) {
      continue;
    }
    char* pC1 = strchr( ++pC0,')');
    if (NULL == pC1) {
      continue;
    }
    if (pC1 > pC0){
      fP3 = atof( pC0);
      if (fP3 > 0.0) {
        break;
      }
    }
  }
  return fP3 ;
}

// extract parameters describing cone
double grepThing( double     pfP3[] 
                , CThing*   pThing
                , surfType& _surfType
                ){
  for ( int j=0;
            j< sizeof(pfP3)/sizeof(double);
            j++){
    pfP3[j] = 0.0;
    char* pC0 = strchr( &(pThing->parameter[3+j][0]),'(');
    if (NULL == pC0) {
      continue;
    }
    char* pC1 = strchr( ++pC0,')');
    if (NULL == pC1) {
      continue;
    }
    if (pC1 > pC0){
      pfP3[j] = atof( pC0);
    }
  }
/*
  if ( fabs(pfP3[4]-pfP3[5]) < restol){
    _surfType = cylinder;
  } else 
  {
    _surfType = cone;
  } 
*/
  return pfP3[0] ;
}

HRESULT step::findCylinderPositionFromCircle(  CPtrArray*&              pEdge_loopStepPtrArray
                                             , CElementary_surfaceStep* pElementary_surfaceStep
                                             , CAxis2_placement_3dStep* pAxis2_Placement_3dStep
                                             )
{

  for ( int kk = 0;
        kk < pEdge_loopStepPtrArray->GetSize();
        kk++)
  {
    CEdge_loopStep *pEdge_loopStep = (CEdge_loopStep *)
      pEdge_loopStepPtrArray->GetAt(kk);
    if (NULL == pEdge_loopStep) continue;

    // the cylinder has 2 edge
    if (2 < pEdge_loopStep->GetSize() )
    {
      
      COriented_edgeStep* pOriented_edgeStep0 = (COriented_edgeStep* )
        pEdge_loopStep->GetAt(0);
      COriented_edgeStep* pOriented_edgeStep1 = (COriented_edgeStep* )
        pEdge_loopStep->GetAt(1);
      CEdge_curveStep* pEdge_curveStep0 = (CEdge_curveStep*)
        pOriented_edgeStep0->m_pEdge_element;
      CEdge_curveStep* pEdge_curveStep1 = (CEdge_curveStep*)
        pOriented_edgeStep1->m_pEdge_element;

      CCircleStep *pCircleStep0 =NULL;
      pCircleStep0 = dynamic_cast<CCircleStep*>
        (&(pEdge_curveStep0->m_rEdge_geometry));

      CCircleStep *pCircleStep1 =NULL;
      pCircleStep1 = dynamic_cast<CCircleStep*>
        (&(pEdge_curveStep1->m_rEdge_geometry));
      
      if (NULL != pCircleStep0){
        CAxis2_placement_3dStep* pAxis2_placement_3dCircle = 
          dynamic_cast<CAxis2_placement_3dStep*>
            (&(pCircleStep0->m_rPosition));

        pElementary_surfaceStep->m_pPosition->m_pAxis =
          pAxis2_placement_3dCircle->m_pAxis;// wh 12/15/01 ??
      }            
      if (NULL != pCircleStep0){
          pAxis2_Placement_3dStep->m_pLocation = 
            pCircleStep0->m_rPosition.m_pLocation;
          break;
      } 
    }

  }
  return S_OK;
}

HRESULT step::findCirclesAxisRef_dirFromEndcapPlane(
                                          CPtrArray*& pEdge_loopStepPtrArray
                                        , CElementary_surfaceStep* pElementary_surfaceStep
                                        , CAxis2_placement_3dStep *pAxis2_Placement_3dStep
                                                   )
            {

            for ( int kk = 0;
                  kk < pEdge_loopStepPtrArray->GetSize();
                  kk++)
            {
              CEdge_loopStep *pEdge_loopStep = (CEdge_loopStep *)
                pEdge_loopStepPtrArray->GetAt(kk);
              if (NULL == pEdge_loopStep) continue;

              // the end caps have an edge which is a circle
              /*
              bool bCircle = false;
              for (int i=0
                    ; i<pEdge_loopStep->m_aEdge_list.GetSize()
                    ; i++){
               COrientedEdgeStep* pOE = (COrientedEdgeStep* ) pEdge_loopStep->m_aEdge_list.GetAt(i);
              }
              */
              if (2 >= pEdge_loopStep->GetSize() )
              {
              //for ( 
                  int jvm0 = 0;
                  //jvm0 < 1;
                  //jvm0++)
                 {
                    COriented_edgeStep* pOriented_edgeStep = (COriented_edgeStep* )
                      pEdge_loopStep->GetAt(jvm0);
                    CEdge_curveStep* pEdge_curveStep = (CEdge_curveStep*)
                      pOriented_edgeStep->m_pEdge_element;

                    // copy the circle's axis & ref_dir from the end cap plane
                    CCircleStep *pCircleStep = dynamic_cast<CCircleStep*>
                      (&(pEdge_curveStep->m_rEdge_geometry));
                    if (NULL != pCircleStep){
                      CPlaneStep* pPlaneStep = dynamic_cast<CPlaneStep*>(pElementary_surfaceStep);
                      if (NULL != pPlaneStep) {
                        if (pPlaneStep->onSurface( *(pCircleStep->m_rPosition.m_pLocation)))
                        {
                          CAxis2_placement_3dStep *pAxis2_placement_3dStep = (CAxis2_placement_3dStep *)
                            &(pCircleStep->m_rPosition);
                          pAxis2_placement_3dStep->m_pAxis =
                            pElementary_surfaceStep->m_pPosition->m_pAxis;
                          pAxis2_placement_3dStep->m_pRef_direction =
                            pElementary_surfaceStep->m_pPosition->m_pRef_direction;
                        //jvm0 = pEdge_loopStep->m_aEdge_list.GetSize();
                        //break;
                      }
                    }
                  }// fi 
                }// next jvm0
              }// fi 
            }// next kk
  return S_OK;
}
          


// build the faces 
HRESULT step::buildFacesAdvanced( FILE *stream, 
                                  stepArchive &ar, 
                                  CRepresentationStep*& pRepresentationStep,
                                  CCartesian_pointStepPtrArray*& pCartesian_pointStepPtrArray  
                                , surfaceModelSelect       lSurfaceModelSelect
                                , CPtrArray*& pEdge_loopStepPtrArray)
{
#if     NOTIFICATION 
  if (m_bWriteFile)
    GetScribView()->Notify("(38%) step::buildFacesAdvanced");
#else //NOTIFICATION 
#endif//NOTIFICATION 
#ifdef  SHOWPROGRESS
  if (m_bWriteFile)
      GetScribView()->progressBarUpdate( 38);
#endif//SHOWPROGRESS

    CPtrArray* pSurfaceStepPtrArray = new CPtrArray( );
    pSurfaceStepPtrArray->SetSize( GetScribView()->m_surfacearray.GetSize());
    CPtrArray* pAdvanced_faceStepPtrArray = new CPtrArray( );

    for ( int is =0; is < GetScribView()->m_surfacearray.GetSize();is++ ) 
    {
     CSurface* pSurface= (CSurface*)GetScribView()->m_surfacearray.GetAt(is);
//   if (0 != pSurface->layer) // test me
     {
      int iO = pSurface->MemberOfObject;
      int ip = pSurface->FirstPolygon;
      for (int jp = 0; jp < 1//pSurface->polysinsurface
        ; jp++) 
      {
        CPolygon* pPolygon= (CPolygon*)GetScribView()->m_polygonarray.GetAt( ip + jp );// wrong
        int iv = pPolygon->VertexHead; 
        int iNumV = pPolygon->NumberOfVertices; 
        if (pPolygon->SameLastFirstVertex){ 
          iNumV--;
        }
        int nv = iv + iNumV;
        CCartesian_pointStep* pCartesian_pointStep = 
          (CCartesian_pointStep*)pCartesian_pointStepPtrArray->GetAt(iv);
        pCartesian_pointStep->m_szLabelName = "poly pt";

        CPolygon* pPolygonZ= (CPolygon*)GetScribView()->m_polygonarray.GetAt(pSurface->FirstPolygon);

        CCartesian_pointStep* pCartesian_pointStep1 = NULL;
        CDirectionStep*  pRef_dir = NULL;
        for ( int jv= 1; 
                  jv < iNumV; 
                  jv++)
                  {
          iv++; 
          pCartesian_pointStep1 = (CCartesian_pointStep*)pCartesian_pointStepPtrArray->GetAt(iv);
          pRef_dir = new CDirectionStep( NULL, 
                                        *pCartesian_pointStep,
                                        *pCartesian_pointStep1);
          if (!pRef_dir->isGood()){
            if (jv < iNumV-1) {          
              pRef_dir =NULL;
            }
            continue;
          }
          if (!pRef_dir->withinTol()) {
            break;
          }
          pRef_dir =NULL;
        } 

        pRef_dir->m_szLabelName = "ref dir";
        CDirectionStep*  pAxis = NULL;
        do {
          iv++; 
          CCartesian_pointStep* 
            pCartesian_pointStep2 = (CCartesian_pointStep*)pCartesian_pointStepPtrArray->GetAt(iv);
          CDirectionStep*  pLeft_dir = new CDirectionStep( NULL, 
                                                           *pCartesian_pointStep1,
                                                           *pCartesian_pointStep2);      
          if (!pLeft_dir->isGood()){
            if (iv < nv-1) {          
              pLeft_dir=NULL;
            }
            continue;
          }
          pLeft_dir->m_szLabelName = "left";

          // problem here is that the polygon is in logical, not physical space!
          pAxis = new CDirectionStep(  NULL, 
                                        pPolygonZ->NormalX, 
                                       -pPolygonZ->NormalY, // rv 03/28/01
                                        pPolygonZ->NormalZ);

          try {
          if (!pAxis->isGood()){
            if (iv < nv) {          
              pAxis=NULL;
            }
            continue;
          }
            pAxis=crossProduct(*pRef_dir,*pLeft_dir) ;//wh 03/29/01
            if (!pAxis->withinTol()){
              break;
            }
            ASSERT( false);
            if (iv<nv){
              pAxis=NULL;
            } 
          }
          catch(...){
#ifdef _DEBUG
            char buf[255] = "Errors in file ";
            strcat(buf, __FILE__);
            strcat(buf, " on line ");
            itoa(__LINE__, &buf[strlen(buf)], 10);

#if     NOTIFICATION 
            GetScribView()->Notify(buf);
#endif//NOTIFICATION 

            iraroArchive* p_ir = (iraroArchive*) ar.m_archives.GetAt(0);
            iraroArchive& ir = * p_ir ; 
            ir <<  "\n/*" << buf << "*/\n"; //moved here rv 20010412
#endif 
			    //iraroArchive* p_ir = (iraroArchive*) ar.m_archives.GetAt(0);iraroArchive& ir ; ir <<  "\n/*" << buf << "*/\n"; remmed out rv 20010412
            
          }
        } while (iv<nv);
        pAxis->m_szLabelName= "axis";
        CAxis2_placement_3dStep *pAxis2_Placement_3dStep = 
          new CAxis2_placement_3dStep( pCartesian_pointStep, pAxis , pRef_dir ); 

        CThing* pThing= (CThing*)GetScribView()->m_thingarray.GetAt(pSurface->MemberOfObject);    
    
        bool bLine = true;
        if (  0 == stricmp( pThing->type,  "CONIC") ) {
          bLine = false;
        }

        CElementary_surfaceStep* pElementary_surfaceStep = NULL; 
        if (bLine) {
          pElementary_surfaceStep = 
            new CPlaneStep( pAxis2_Placement_3dStep );
        } else {

          if (1==pSurface->polysinsurface){

            pElementary_surfaceStep = new
              CPlaneStep( pAxis2_Placement_3dStep );

             findCirclesAxisRef_dirFromEndcapPlane( pEdge_loopStepPtrArray
                                                  , pElementary_surfaceStep
                                                  , pAxis2_Placement_3dStep
                                                  );
          } else {
  
//          surfType _surfType;
            float fP3 = grepThing( pThing);//, _surfType
            // now decide if we want a cylinder or a cone or an extruded ellipse or surface of 2 lofted ellipses

            pElementary_surfaceStep = new
               CCylindrical_surfaceStep( fP3, 
                                         *pAxis2_Placement_3dStep );

//          copy the cylinder's position from the circle's center
            findCylinderPositionFromCircle( pEdge_loopStepPtrArray
                                          , pElementary_surfaceStep
                                          , pAxis2_Placement_3dStep
                                          );

          }
        }
        CFace_boundStep* pFace_boundStep =  
          new CFace_outer_boundStep( NULL, 
                                     (CEdge_loopStep*) pEdge_loopStepPtrArray->GetAt(ip + jp ), 
                                     true
                                 //, NULL
                                   );
 
          // advanced_brep
          CFaceStep * pFaceStep = new
             CAdvanced_faceStep( pElementary_surfaceStep 
                                , pFace_boundStep
                                , true
                                );

        pAdvanced_faceStepPtrArray->Add( pFaceStep);
      
     }//jp 
    }//0 != pSurface->layer
  
  }//is


  HRESULT hr = buildShellsAdvanced( stream, 
                                    ar, 
                                    pRepresentationStep 
                                  , lSurfaceModelSelect
                                  , pAdvanced_faceStepPtrArray
                                  , pCartesian_pointStepPtrArray 
                                  );
  delete pSurfaceStepPtrArray;
  delete pAdvanced_faceStepPtrArray;
  return hr;
}

// build the loops
HRESULT step::buildLoopsAdvanced( FILE *stream, 
                                  stepArchive &ar, 
                                  CRepresentationStep*& pRepresentationStep
                                , surfaceModelSelect       lSurfaceModelSelect
                                , CCartesian_pointStepPtrArray*& pCartesian_pointStepPtrArray 
                                , CPtrArray*& pEdge_loopStepPtrArray)
{
#if     NOTIFICATION 
  if (m_bWriteFile)
      GetScribView()->Notify("(35%) step::buildLoopsAdvanced");
#else //NOTIFICATION 
#endif//NOTIFICATION 
#ifdef  SHOWPROGRESS
  if (m_bWriteFile)
      GetScribView()->progressBarUpdate( 35);
#endif//SHOWPROGRESS
  HRESULT hr = 
  buildFacesAdvanced( stream, 
                      ar, 
                      pRepresentationStep 
                    , pCartesian_pointStepPtrArray
                    , lSurfaceModelSelect
                    , pEdge_loopStepPtrArray);
  return hr;
}

HRESULT step::buildPathAdvanced( FILE *                         stream, 
                                 stepArchive &                  ar, 
                                 CRepresentationStep*&          pRepresentationStep,
                                 CVertex_pointStepPtrArray*&    pVertex_pointStepPtrArray,
                                 CCartesian_pointStepPtrArray*& pCartesian_pointStepPtrArray,
                                 surfaceModelSelect             lSurfaceModelSelect 
                               , CPtrArray*&pPathStepPtrArray )
{
#if     NOTIFICATION 
  if (m_bWriteFile)
    GetScribView()->Notify("(33%) step::buildPathAdvanced");
#else //NOTIFICATION 
#endif//NOTIFICATION 
#ifdef  SHOWPROGRESS
  if (m_bWriteFile)
      GetScribView()->progressBarUpdate( 33);
#endif//SHOWPROGRESS

  HRESULT hr = buildLoopsAdvanced( stream, 
                                   ar, 
                                   pRepresentationStep 
                                 ,lSurfaceModelSelect 
                                 ,pCartesian_pointStepPtrArray 
                                 ,pPathStepPtrArray);

  return hr;
}

// build the edges from the verticies as found in TasDraw polygon entities
HRESULT step::buildLineAdvanced( FILE*                          stream, 
                                stepArchive&                   ar, 
                                CRepresentationStep*&          pRepresentationStep,
                                CVertex_pointStepPtrArray*&    pVertex_pointStepPtrArray ,
                                surfaceModelSelect             lSurfaceModelSelect
                              , CEdge_loopStep *               pEdge_loopStep
                              , CLineStepPtrArray *            pLineStepPtrArray
                              , CPtrArray*                     pEdge_curveArray
                              , CSurface*                      pSurface)
{
  HRESULT hr = S_OK;
    CVertex_pointStep* pVertex_pointStep0=NULL;
    CVertex_pointStep* pVertex_pointStep1=NULL;

    CPolygon* pPolygon= (CPolygon*)GetScribView()->m_polygonarray.GetAt(pSurface->FirstPolygon);
    int iNumV = pPolygon->NumberOfVertices;
    if (pPolygon->SameLastFirstVertex){
      iNumV--;
    }
    ASSERT( iNumV>2 );
    pEdge_loopStep->SetSize( iNumV );

    int ivm1 = pPolygon->VertexHead + iNumV -1;

    int jvm1 = (int) pVertex_pointStepPtrArray->
        m_rCartesian_pointStepPtrArray.m_hash.GetAt(ivm1);

    for ( int vh = 0;
              vh < iNumV; 
              vh++ ) {

      int iv = vh + pPolygon->VertexHead ;
      
      pVertex_pointStep0 = (CVertex_pointStep*) 
        (pVertex_pointStepPtrArray->GetAt( ivm1));
      pVertex_pointStep1 = (CVertex_pointStep*) 
        (pVertex_pointStepPtrArray->GetAt( iv));

      int jvm0 = (int) pVertex_pointStepPtrArray->
        m_rCartesian_pointStepPtrArray.m_hash.GetAt(iv);

      if (jvm0==jvm1) {
        continue;
      }
      jvm1 = jvm0;

      CCartesian_pointStep* pCartesian_pointStep0= 
        (CCartesian_pointStep*)((pVertex_pointStepPtrArray->m_rCartesian_pointStepPtrArray.GetAt( ivm1)));
      CCartesian_pointStep* pCartesian_pointStep1= 
        (CCartesian_pointStep*)((pVertex_pointStepPtrArray->m_rCartesian_pointStepPtrArray.GetAt( iv)));
      CVectorStep* pVectorStep = new 
        CVectorStep( *pCartesian_pointStep0, 
                     *pCartesian_pointStep1);

      CCurveStep* pCurveStep2= 
        new CLineStep( *pCartesian_pointStep0, 
                       *pVectorStep, 
                       pCartesian_pointStep1 );
      bool bSame_sense;
      int kv = pLineStepPtrArray->SetAt( iv, (CLineStep*)pCurveStep2, bSame_sense);
      pCurveStep2 = (CCurveStep*) pLineStepPtrArray->GetAt( kv );
      CEdge_curveStep*pEdge_curveStep3=NULL;
      if (kv==iv){
        pEdge_curveStep3 = new
          CEdge_curveStep( *pVertex_pointStep0, 
                           *pVertex_pointStep1 , 
                           *pCurveStep2, 
                           true);
        ASSERT(NULL == pEdge_curveArray->GetAt(kv));
        pEdge_curveArray->SetAt(kv, pEdge_curveStep3);
      }
      else{
        pEdge_curveStep3 = (CEdge_curveStep*) pEdge_curveArray->GetAt(kv);
      }
      
      bool bOrientation=true;
      if ( (pVertex_pointStep0) == (pEdge_curveStep3->m_pEdge_start)
         )
      {
        bOrientation=true;
      }
      else {
        bOrientation=false;
      }
//    if (!bSame_sense){
//      bOrientation=!bOrientation;
//    }

      COriented_edgeStep* pOriented_edgeStep= new 
        COriented_edgeStep(
        pEdge_curveStep3, bOrientation );
      pEdge_loopStep->SetAt( vh, pOriented_edgeStep);
      pVertex_pointStep0 = pVertex_pointStep1;

//    pVertex_pointStepLast= pVertex_pointStep1;
      ivm1 = iv;
    }//next vh
  return hr;
}

HRESULT step::buildArcOnCylinderAdvanced( FILE*                          stream, 
                                          stepArchive&                   ar, 
                                          CRepresentationStep*&          pRepresentationStep,
                                          CVertex_pointStepPtrArray*&    pVertex_pointStepPtrArray ,
                                          surfaceModelSelect             lSurfaceModelSelect
                                        , CEdge_loopStep *               pEdge_loopStep
                                        , CCircleStepPtrArray*           pEllipseStepPtrArray
                                        , CPtrArray*                     pEdge_curveArray
                                        , CSurface*                      pSurface)
{
  HRESULT hr = S_OK;

//CCurveStep* pCurveStep2 =
//  pEllipseStepPtrArray->GetAt(0);

  CEdge_curveStep*pEdge_curveStep3=NULL;
  pEdge_curveStep3 = (CEdge_curveStep*)
    pEdge_curveArray->GetAt(0);

  CCircleStep *pCircleStep = dynamic_cast<CCircleStep *>
    (&(pEdge_curveStep3->m_rEdge_geometry));
  ASSERT(NULL != pCircleStep );

  COriented_edgeStep* pOriented_edgeStep0 = new 
    COriented_edgeStep(
      pEdge_curveStep3, 
      false);
  pOriented_edgeStep0->m_szLabelName="0 on cylinder";
  pEdge_loopStep->Add( pOriented_edgeStep0);

  pEdge_curveStep3 = (CEdge_curveStep*)
  pEdge_curveArray->GetAt(1);

  pCircleStep = dynamic_cast<CCircleStep *>
    (&(pEdge_curveStep3->m_rEdge_geometry));
  ASSERT(NULL != pCircleStep );

  COriented_edgeStep* pOriented_edgeStep1 = new 
    COriented_edgeStep(
      pEdge_curveStep3, 
      false);
  pOriented_edgeStep1->m_szLabelName="1 on cylinder";
  pEdge_loopStep->Add( pOriented_edgeStep1);

  return hr;
}

// make edge face
HRESULT step::buildSeam(
                        CVertex_pointStepPtrArray*&    pVertex_pointStepPtrArray 
                      , const int ivm1 
                      , const int iv 
                      , CLineStepPtrArray *            pLineStepPtrArray
                      , CEdge_loopStep *               pEdge_loopStepCylinder
                      , CPtrArray*                     pEdge_curveArray
                      )
{
#if 0
  CVertex_pointStep*     pVertex_pointStep0 = (CVertex_pointStep*) 
        (pVertex_pointStepPtrArray->GetAt( ivm1));      
  CVertex_pointStep*     pVertex_pointStep1 = (CVertex_pointStep*) 
        (pVertex_pointStepPtrArray->GetAt( iv));

  CCartesian_pointStep* pCartesian_pointStep0= 
   (CCartesian_pointStep*)
    (pVertex_pointStepPtrArray->m_rCartesian_pointStepPtrArray.GetAt( ivm1));
  CCartesian_pointStep* pCartesian_pointStep1= 
   (CCartesian_pointStep*)
    (pVertex_pointStepPtrArray->m_rCartesian_pointStepPtrArray.GetAt( iv  ));

  CVectorStep* pVectorStep = new 
    CVectorStep( *pCartesian_pointStep0, 
                 *pCartesian_pointStep1);

  CCurveStep* pCurveStep2= 
    new CLineStep( *pCartesian_pointStep0, 
                   *pVectorStep, 
                   pCartesian_pointStep1 );
  bool bSame_sense = true;
  int kv = pLineStepPtrArray->Add( (CLineStep*)pCurveStep2);
  pCurveStep2 = (CCurveStep*) pLineStepPtrArray->GetAt( kv );
  CEdge_curveStep*pEdge_curveStep3=NULL;
    pEdge_curveStep3 = new
      CEdge_curveStep( *pVertex_pointStep0, 
                       *pVertex_pointStep1 , 
                       *pCurveStep2, 
                       true);
    pEdge_curveArray->Add( pEdge_curveStep3);

    
  bool bOrientation=true;
  if ( (pVertex_pointStep0) == (pEdge_curveStep3->m_pEdge_start)
     )
  {
    bOrientation=true;
  }
  else {
    bOrientation=false;
  }

  // be careful about the ordering of the oriented edges

  COriented_edgeStep* pOriented_edgeStep= new 
    COriented_edgeStep
      ( pEdge_curveStep3
      , bOrientation );
  pEdge_loopStepCylinder->m_aEdge_list.InsertAt( 1, pOriented_edgeStep);

  pOriented_edgeStep= new 
    COriented_edgeStep
      ( pEdge_curveStep3
      , !bOrientation );
  pEdge_loopStepCylinder->m_aEdge_list.Add( pOriented_edgeStep);
#endif
  return S_OK;
}

  // Build a seam edge connecting the two endcaps 
  //  along the cylinderical surface.
  //  because STEP spec surface.IP2 specifies that the bounds are arcwise connected!
HRESULT step::buildSeamEdgeOnCylinderAdvanced(  FILE*                          stream 
                                              , stepArchive&                   ar 
                                              , CRepresentationStep*&          pRepresentationStep
                                              , CVertex_pointStepPtrArray*&    pVertex_pointStepPtrArray 
                                              , surfaceModelSelect             lSurfaceModelSelect
                                              , CEdge_loopStep *               pEdge_loopStepCylinder
                                              , CLineStepPtrArray *            pLineStepPtrArray
                                              , CPtrArray*                     pEdge_curveArray
                                              , CSurface*                      pCylinder
                                              , CEdge_loopStep*                pEdge_loopStep1 // on endcap 1
                                              , CEdge_loopStep*                pEdge_loopStep0 // on endcap 0
                                              )                                    
{
  HRESULT hr = S_OK;

  CEdge_curveStep* pEdge_curveStep0 = (CEdge_curveStep*)
    pEdge_curveArray->GetAt(0);

  // extract the circle for the endcap 0
  CCircleStep *pCircleStep = dynamic_cast<CCircleStep *>
    (&(pEdge_curveStep0->m_rEdge_geometry));
  ASSERT( NULL != pCircleStep );
  
  CVertex_pointStep* pVertex_pointStep0=NULL;
  CVertex_pointStep* pVertex_pointStep1=NULL;
  // go through all the polygons on the surface
  for ( int ip=0;
            ip<pCylinder->polysinsurface;
            ip++) 
  {
    CPolygon* pPolygonOnCylinder = (CPolygon*)
      GetScribView()->m_polygonarray.GetAt( 
      pCylinder->FirstPolygon + ip);
    int iNumV = pPolygonOnCylinder->NumberOfVertices;
    if (pPolygonOnCylinder->SameLastFirstVertex){
      iNumV--;
    }
    ASSERT( iNumV>2 );

    int ivm1 = pPolygonOnCylinder->VertexHead + iNumV -1;

    int jvm1 = (int) pVertex_pointStepPtrArray->
        m_rCartesian_pointStepPtrArray.m_hash.GetAt(ivm1);

    int jvm0 = (int) pVertex_pointStepPtrArray->
      m_rCartesian_pointStepPtrArray.m_hash.GetAt(0);
    if (jvm0 == jvm1){
      jvm1 = (int) pVertex_pointStepPtrArray->
          m_rCartesian_pointStepPtrArray.m_hash.GetAt(ivm1-1);
    }
    // go through all of the verticies for the point on the poly of the cylinder
    for ( int vh = 0;
              vh < iNumV; 
              vh++ ) {

      int iv = vh + pPolygonOnCylinder->VertexHead ;
      
      pVertex_pointStep0 = (CVertex_pointStep*) 
        (pVertex_pointStepPtrArray->GetAt( ivm1));
      
      pVertex_pointStep1 = (CVertex_pointStep*) 
        (pVertex_pointStepPtrArray->GetAt( iv));

      jvm0 = (int) pVertex_pointStepPtrArray->
        m_rCartesian_pointStepPtrArray.m_hash.GetAt(iv);
      // make sure that this is not a zero length edge!
      if (jvm0!=jvm1) {
        jvm1 = jvm0;
        // find the vertex on the cylinder which is also on the near endcap (0) circle 
        if ( pVertex_pointStep0 == (pEdge_curveStep0->m_pEdge_start)) {

          // either it was on the next endcap or it is still on this one
          // if it is still on this endcap, we need to try again
          // if it is on the next endcap, then we build the line
          // we have to make sure that the point on the far circle is on 
          // if not, add it
          CEdge_curveStep* pEdge_curveStep1 = (CEdge_curveStep*)
              pEdge_curveArray->GetAt(1);
          
              //add it
              // check to see if it in the far endcap's polygon's list of verticies
              CSurface* pSurfaceFarCap = (CSurface*)GetScribView()->m_surfacearray.GetAt(1);
              for (int ip1=0;
                       ip1<pSurfaceFarCap->polysinsurface; 
                       ip1++){
                CPolygon* pPolygonFarCap = (CPolygon*)GetScribView()->m_polygonarray.GetAt(
                  pSurfaceFarCap->FirstPolygon + ip1);
                for (int iv1 = 0; 
                         iv1 < pPolygonFarCap->NumberOfVertices; 
                         iv1++){

                  // make sure that the points aren't repeated
                  CVertex_pointStep* pVertex_pointStepOnFarCap = 
                    pVertex_pointStepPtrArray->GetAt(pPolygonFarCap->VertexHead + iv1);
                  if ( pVertex_pointStep1 == pVertex_pointStepOnFarCap){

                    pEdge_curveStep1->m_pEdge_curveArray = pEdge_curveArray;
                    // split the edge on far endcap into 2
                    pEdge_curveStep1->split( *pVertex_pointStep1
                                           , pEdge_loopStepCylinder
                                           , pEdge_loopStep1);


                    buildSeam( pVertex_pointStepPtrArray 
                             , ivm1
                             , iv
                             , pLineStepPtrArray
                             , pEdge_loopStepCylinder              
                             , pEdge_curveArray
                             );

                    if ( pVertex_pointStep1 == (pEdge_curveStep1->m_pEdge_start)){

                    } else {
/*
                      // build seam on opposite side of endcap
                      splitEndcap0( pVertex_pointStepPtrArray 
                                  , lSurfaceModelSelect
                                  , pEdge_loopStep1
                                  , pLineStepPtrArray
                                  , pEdge_curveArray
                                  , pCylinder
                                  , pVertex_pointStep1
                                  , pEdge_loopStep0 // on endcap 0
                                  , pEdge_loopStepCylinder
                                  );
*/
                  }
                    return hr;
                  }
                }
              }
                      
        }// edge_start
      }// jvm0
      pVertex_pointStep0 = pVertex_pointStep1;

      ivm1 = iv;
    }//next vh
  } 
  ASSERT(false);
  return E_FAIL;
}

// split the other endcap
// some step readers chock if this is not done!
HRESULT step::splitEndcap0( CVertex_pointStepPtrArray*&    pVertex_pointStepPtrArray 
                          , surfaceModelSelect             lSurfaceModelSelect
                          , CEdge_loopStep *               pEdge_loopStep
                          , CLineStepPtrArray *            pLineStepPtrArray
                          , CPtrArray*                     pEdge_curveArray
                          , CSurface*                      pCylinder
                          , CVertex_pointStep*             pVertex_pointStepStart
                          , CEdge_loopStep*                pEdge_loopStep0 // on endcap 0
                          , CEdge_loopStep*                pEdge_loopStepCylinder
                          )
{
  HRESULT hr = S_OK;

  CEdge_curveStep* pEdge_curveStep1 = (CEdge_curveStep*)
    pEdge_curveArray->GetAt(1);

  // extract the circle for the endcap 0
  CCircleStep *pCircleStep = dynamic_cast<CCircleStep *>
    (&(pEdge_curveStep1->m_rEdge_geometry));
  ASSERT( NULL != pCircleStep );
  
  CVertex_pointStep* pVertex_pointStep0=NULL;
  CVertex_pointStep* pVertex_pointStep1=NULL;
  // go through all the polygons on the surface
  for ( int ip=0;
            ip<pCylinder->polysinsurface;
            ip++) 
  {
    CPolygon* pPolygonOnCylinder = (CPolygon*)GetScribView()->m_polygonarray.GetAt( pCylinder->FirstPolygon + ip);
    int iNumV = pPolygonOnCylinder->NumberOfVertices;
    if (pPolygonOnCylinder->SameLastFirstVertex){
      iNumV--;
    }
    ASSERT( iNumV>2 );

    int ivm1 = pPolygonOnCylinder->VertexHead + iNumV -1;

    int jvm1 = (int) pVertex_pointStepPtrArray->
        m_rCartesian_pointStepPtrArray.m_hash.GetAt(ivm1);

    int jvm0 = (int) pVertex_pointStepPtrArray->
      m_rCartesian_pointStepPtrArray.m_hash.GetAt(0);
    if (jvm0 == jvm1){
      jvm1 = (int) pVertex_pointStepPtrArray->
          m_rCartesian_pointStepPtrArray.m_hash.GetAt(ivm1-1);
    }
    // go through all of the verticies for the point on the poly of the cylinder
    for ( int vh = 0;
              vh < iNumV; 
              vh++ ) {

      int iv = vh + pPolygonOnCylinder->VertexHead ;
      
      pVertex_pointStep0 = (CVertex_pointStep*) 
        (pVertex_pointStepPtrArray->GetAt( ivm1));
      
      pVertex_pointStep1 = (CVertex_pointStep*) 
        (pVertex_pointStepPtrArray->GetAt( iv));

      jvm0 = (int) pVertex_pointStepPtrArray->
        m_rCartesian_pointStepPtrArray.m_hash.GetAt(iv);
      // make sure that this is not a zero length edge!
      if (jvm0!=jvm1) {
        jvm1 = jvm0;
        // find the vertex on the cylinder which is also on the near endcap (0) circle 

        if  ( pVertex_pointStepStart == pVertex_pointStep0 ) 
         if ( pVertex_pointStepStart == (pEdge_curveStep1->m_pEdge_end  )) {

          // either it was on the next endcap or it is still on this one
          // if it is still on this endcap, we need to try again
          // if it is on the next endcap, then we build the line
          // we have to make sure that the point on the far circle is on 
          // if not, add it
          CEdge_curveStep* pEdge_curveStep0 = (CEdge_curveStep*)
              pEdge_curveArray->GetAt(0);
          
              //add it
              // check to see if it in the far endcap's polygon's list of verticies
              CSurface* pSurfaceFarCap = (CSurface*)GetScribView()->m_surfacearray.GetAt(0);
              for (int ip1=0;
                       ip1<pSurfaceFarCap->polysinsurface; 
                       ip1++){
                CPolygon* pPolygonFarCap = (CPolygon*)GetScribView()->m_polygonarray.GetAt(
                  pSurfaceFarCap->FirstPolygon + ip1);
                for (int iv1 = 0; 
                         iv1 < pPolygonFarCap->NumberOfVertices; 
                         iv1++){

                  // make sure that the points aren't repeated
                  CVertex_pointStep* pVertex_pointStepOnFarCap = 
                    pVertex_pointStepPtrArray->GetAt(pPolygonFarCap->VertexHead + iv1);
                  if ( pVertex_pointStep1 == pVertex_pointStepOnFarCap){

                    pEdge_curveStep1->m_pEdge_curveArray = pEdge_curveArray;
                    // split the edge on far endcap into 2
                    pEdge_curveStep1->split( *pVertex_pointStep1
                                           , pEdge_loopStepCylinder
                                           , pEdge_loopStep0);

                    // dont create another seam because then have another loop to keep track of!

                    return hr;
                  }
                }
              }
                      
        }// edge_start
      }// jvm0
      pVertex_pointStep0 = pVertex_pointStep1;

      ivm1 = iv;
    }//next vh
  } 
  ASSERT(false);
  return E_FAIL;
}

HRESULT step::buildArcOnFlatAdvanced( FILE*                          stream, 
                                      stepArchive&                   ar, 
                                      CRepresentationStep*&          pRepresentationStep,
                                      CVertex_pointStepPtrArray*&    pVertex_pointStepPtrArray ,
                                      surfaceModelSelect             lSurfaceModelSelect
                                    , CEdge_loopStep *               pEdge_loopStep
                                    , CCircleStepPtrArray*           pEllipseStepPtrArray
                                    , CPtrArray*                     pEdge_curveArray
                                    , CSurface*                      pSurface)
{
  HRESULT hr = S_OK;
#if 0
  CVertex_pointStep* pVertex_pointStep0=NULL;
  CVertex_pointStep* pVertex_pointStep1=NULL;

  CPolygon* pPolygon= (CPolygon*)GetScribView()->m_polygonarray.GetAt(pSurface->FirstPolygon);
  int iNumV = pPolygon->NumberOfVertices;
  if (pPolygon->SameLastFirstVertex){
    iNumV--;
  }
  ASSERT( iNumV>2 );
  pEdge_loopStep->m_aEdge_list.SetSize( 0 );

  int ivm1 = pPolygon->VertexHead + iNumV -1;

  pVertex_pointStep0 = (CVertex_pointStep*) 
    (pVertex_pointStepPtrArray->GetAt( ivm1));

  CCartesian_pointStep* pCartesian_pointStep0 = new 
    CCartesian_pointStep( NULL, *(CCartesian_pointStep*)
    ((pVertex_pointStepPtrArray->m_rCartesian_pointStepPtrArray.GetAt( ivm1))));
  pCartesian_pointStep0->m_szLabelName="circle center";
  CCartesian_pointStep* pCartesian_pointStep1 = NULL;

  CDirectionStep* pAxisDir = NULL ;
  int jvm1 = (int) pVertex_pointStepPtrArray->
      m_rCartesian_pointStepPtrArray.m_hash.GetAt(ivm1);
  int iNumVerticies =1;
  for ( int vh = 0;
            vh < iNumV-1; 
            vh++ ) {

    int iv = vh + pPolygon->VertexHead ;
    
    pVertex_pointStep1 = (CVertex_pointStep*) 
      (pVertex_pointStepPtrArray->GetAt( iv));

    pCartesian_pointStep1= 
      (CCartesian_pointStep*)
      ((pVertex_pointStepPtrArray->m_rCartesian_pointStepPtrArray.GetAt( iv)));

    int jvm0 = (int) pVertex_pointStepPtrArray->
      m_rCartesian_pointStepPtrArray.m_hash.GetAt(iv);

    if (jvm0==jvm1) {
      continue;
    }
    jvm1 = jvm0;
    iNumVerticies++;
    *pCartesian_pointStep0 += *pCartesian_pointStep1;
//  if (NULL == pAxisDir ){
//  }
  }//next vh
  //the center of the circle should be calculated by bisecting two segments and finding the intersection
  *pCartesian_pointStep0 /= float(iNumVerticies);

  CDirectionStep* pRefDir = new 
    CDirectionStep( NULL, 
                    *pCartesian_pointStep0, 
                    *pCartesian_pointStep1);
  pRefDir->m_szLabelName = "ref dir";
  CAxis2_placement_3dStep *pAxis2_placement_3dStep = new 
    CAxis2_placement_3dStep(  pCartesian_pointStep0, 
                              NULL, 
                              pRefDir);

  pAxis2_placement_3dStep->m_szLabelName="on endcap";
  CThing* pThing= (CThing*)GetScribView()->m_thingarray.GetAt(pSurface->MemberOfObject);
  float fP3 = grepThing(pThing);
  // decide between circle vs ellipse
  CCurveStep* pCurveStep2 = new  
    CCircleStep( *pAxis2_placement_3dStep, 
                 fP3);

  bool bSame_sense = true;
  int kv = pEllipseStepPtrArray->Add( (CCircleStep*)pCurveStep2);
  pCurveStep2 = (CCurveStep*) pEllipseStepPtrArray->GetAt( kv );
  CEdge_curveStep*pEdge_curveStep3=NULL;
  if (true){
    pEdge_curveStep3 = new
      CEdge_curveStep( *pVertex_pointStep1, 
                       *pVertex_pointStep1 , 
                       *pCurveStep2, 
                       true);
    ASSERT(NULL == pEdge_curveArray->GetAt(kv));
    pEdge_curveArray->SetAt(kv, pEdge_curveStep3);
  }
  else{
    pEdge_curveStep3 = (CEdge_curveStep*) pEdge_curveArray->GetAt(kv);
  }
  
  bool bOrientation=true;
  if ( (pVertex_pointStep1) == (pEdge_curveStep3->m_pEdge_start)
     )
  {
    bOrientation=true;
  }
  else {
    bOrientation=false;
  }

  COriented_edgeStep* pOriented_edgeStep0= new 
    COriented_edgeStep(
    pEdge_curveStep3, true);
  pOriented_edgeStep0->m_szLabelName="on endcap";
  pEdge_loopStep->m_aEdge_list.Add( pOriented_edgeStep0);
#endif
  return hr;
}

// build the edges from the verticies as found in TasDraw polygon entities
HRESULT step::buildEdgeAdvanced( FILE*                          stream, 
                                 stepArchive&                   ar, 
                                 CRepresentationStep*&          pRepresentationStep,
                                 CVertex_pointStepPtrArray*&    pVertex_pointStepPtrArray ,
                                 CCartesian_pointStepPtrArray*& pCartesian_pointStepPtrArray,
                                 surfaceModelSelect             lSurfaceModelSelect)
{
#if     NOTIFICATION 
  if (m_bWriteFile)
  GetScribView()->Notify("(32%) step::buildEdgeAdvanced");
#else //NOTIFICATION 
#endif//NOTIFICATION 
#ifdef  SHOWPROGRESS
  if (m_bWriteFile)
  GetScribView()->progressBarUpdate( 32);
#endif//SHOWPROGRESS

  CPtrArray* pEdge_loopStepPtrArray = new CPtrArray( );
  pEdge_loopStepPtrArray->SetSize( GetScribView()->m_surfacearray.GetSize());

  CLineStepPtrArray *pLineStepPtrArray = new 
    CLineStepPtrArray( GetScribView()->m_vertexarray.GetSize());
  CCircleStepPtrArray *pEllipseStepPtrArray = new 
    CCircleStepPtrArray( );
  
  CPtrArray*pEdge_curveArray= new 
    CPtrArray( );
  pEdge_curveArray->SetSize(GetScribView()->m_vertexarray.GetSize());
  for (int jvm1 = 0; jvm1 < GetScribView()->m_vertexarray.GetSize(); jvm1++) {
    pEdge_curveArray->SetAt(jvm1, NULL);
  }

  for ( int is = 0; is < GetScribView()->m_surfacearray.GetSize();is++ ) 
  {// is in the index on the surface

    CEdge_loopStep *pEdge_loopStep = new CEdge_loopStep; //()//wh 4/17/01
    pEdge_loopStepPtrArray->SetAt( is, pEdge_loopStep );    

    CSurface* pSurface= (CSurface*)GetScribView()->m_surfacearray.GetAt(is);

    CThing* pThing= (CThing*)GetScribView()->m_thingarray.GetAt(pSurface->MemberOfObject);    
    
    bool bLine = true;
    if (  0 == stricmp( pThing->type,  "CONIC") ) {
      bLine = false;
    }

    if ( bLine ){
        
      buildLineAdvanced(
                         stream, 
                         ar, 
                         pRepresentationStep,
                         pVertex_pointStepPtrArray,
                         lSurfaceModelSelect
                       , pEdge_loopStep
                       , pLineStepPtrArray
                       , pEdge_curveArray
                       , pSurface);      
    }
    else {
      if (1==pSurface->polysinsurface){
        // on the endcaps
        buildArcOnFlatAdvanced( stream, 
                          ar, 
                          pRepresentationStep,
                          pVertex_pointStepPtrArray,
                          lSurfaceModelSelect
                        , pEdge_loopStep
                        , pEllipseStepPtrArray
                        , pEdge_curveArray
                        , pSurface);      
      }else{

        buildArcOnCylinderAdvanced( stream, 
                          ar, 
                          pRepresentationStep,
                          pVertex_pointStepPtrArray,
                          lSurfaceModelSelect
                        , pEdge_loopStep
                        , pEllipseStepPtrArray
                        , pEdge_curveArray
                        , pSurface);   

        buildSeamEdgeOnCylinderAdvanced( stream, 
                         ar, 
                         pRepresentationStep,
                         pVertex_pointStepPtrArray,
                         lSurfaceModelSelect
                       , pEdge_loopStep
                       , pLineStepPtrArray
                       , pEdge_curveArray
                       , pSurface
                       , (CEdge_loopStep *) pEdge_loopStepPtrArray->GetAt(1)
                       , (CEdge_loopStep *) pEdge_loopStepPtrArray->GetAt(0)
                       );      

      }
    }
  }//next ip

  HRESULT hr = buildPathAdvanced( stream, 
                          ar, 
                          pRepresentationStep,
                          pVertex_pointStepPtrArray,
                          pCartesian_pointStepPtrArray,
                          lSurfaceModelSelect,
                          pEdge_loopStepPtrArray );


  delete pLineStepPtrArray ;
  delete pEdge_loopStepPtrArray;
  return hr;
}

// build the verticies
HRESULT step::buildVerticesAdvanced( FILE *                stream, 
                                     stepArchive &         ar, 
                                     surfaceModelSelect    lSurfaceModelSelect, 
                                     CRepresentationStep*& pRepresentationStep 
                                   )
{
  HRESULT hr = S_OK;
#if     NOTIFICATION 
  if (m_bWriteFile)
  GetScribView()->Notify("(10%) step::buildVerticesAdvanced");
#endif//NOTIFICATION 
#ifdef  SHOWPROGRESS
  if (m_bWriteFile)
      GetScribView()->progressBarUpdate( 10);
#endif//SHOWPROGRESS

  // there is one for each model, not one for each asssembly
  CCartesian_pointStepPtrArray* pCartesian_pointStepPtrArray = new 
    CCartesian_pointStepPtrArray( GetScribView()->m_vertexarray.GetSize());
  CVertex_pointStepPtrArray* pVertex_pointStepPtrArray = new 
    CVertex_pointStepPtrArray( *pCartesian_pointStepPtrArray);

  pCartesian_pointStepPtrArray->SetSize( GetScribView()->m_vertexarray.GetSize());
  pVertex_pointStepPtrArray->SetSize( GetScribView()->m_vertexarray.GetSize());

  for ( int iv =0; iv < GetScribView()->m_vertexarray.GetSize();iv++ ) {
    CVertex* pVertex= (CVertex*)GetScribView()->m_vertexarray.GetAt(iv);
      
    CCartesian_pointStep* pCartesian_pointStep = 
      new CCartesian_pointStep( NULL, 
                                pVertex->px - GetScribView()->XRotationAxis, 
                              -(pVertex->py - GetScribView()->YRotationAxis), 
                                pVertex->pz - GetScribView()->ZRotationAxis);
    if (NULL==pCartesian_pointStep) {
      return E_OUTOFMEMORY;
    }// wh 10/17/01
    int ivSet = pCartesian_pointStepPtrArray->SetAt( iv, pCartesian_pointStep );
    if (ivSet == iv) 
    {
      CVertex_pointStep* pVertex_pointStep = 
        new CVertex_pointStep( *pCartesian_pointStep);
      if (-1 == pVertex_pointStepPtrArray->SetAt( iv, pVertex_pointStep)){
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
        "incrementing CVertex_pointStepPtrarray.GetAt(%d) =(#%d ) \n", 
        iv, pVertex_pointStep->getNum());
#endif//EXPOSE   
      pVertex_pointStep->addRef();// wh 09/20/01
    }
  }

    
  hr = buildEdgeAdvanced( stream, 
                          ar, 
                          pRepresentationStep,
                          pVertex_pointStepPtrArray ,
                          pCartesian_pointStepPtrArray,
                          lSurfaceModelSelect);

  try{

#ifdef  _DEBUG
    for ( iv = pVertex_pointStepPtrArray->GetSize()-1;iv >= 0;iv--){
      CVertex_pointStep* pVertex_point = (CVertex_pointStep* )
        pVertex_pointStepPtrArray->GetAt(iv);
      try{
        CBaseStep* pBS = dynamic_cast<CBaseStep*>(pVertex_point);
        if (NULL == pBS){
          throw 0;
        }
      } 
      catch (...){
#ifdef  EXPOSE      
        int ipf = 
        fprintf( g_errorLog, "CVertex_pointStepPtrarray.GetAt( %d ) released too often.\n", iv);
#endif//EXPOSE   
      }
    }
#endif//_DEBUG

    delete pVertex_pointStepPtrArray;

    delete pCartesian_pointStepPtrArray;

  } catch(...){
#ifdef  EXPOSE      
		TRACE0("error deleting CCartesian_pointStepPtrArray.\n");
    fprintf( g_errorLog, "error deleting CCartesian_pointStepPtrArray.\n", __FILE__);
    ASSERT(false);
#endif//EXPOSE   
  }
  return hr;
}

// for crying out loud, the complexity of the calculations is number_of_polygons ^ 2 flops operation!
// once it all works, speed things up using boundingBoxes
HRESULT step::sortFeaturesFaceted( agitoAssembly*  pAssembly,// assembly containing all the pars
                                   agitoComponent& aNegativeComponents, // the negative features
                                   CPtrArray*&     pAdvanced_faceStepPtrArray)// collection of surfaces in models
                                   
{
  for ( int it =0; it < GetScribView()->m_thingarray.GetSize();it++ ) {
    CThing* pThing = (CThing*)GetScribView()->m_thingarray.GetAt(it);
    agitoPart* pPart = (agitoPart* )pAssembly->GetAt( pThing->BelongsToModelNo);
    ASSERT( 0 == pThing->BelongsToModelNo);
    agitoComponent* pLump = (agitoComponent* )pPart->GetAt( 0);
    agitoFeature* pFeature = (agitoFeature* )pLump->GetAt( it);// fails for multi-parts
    bool bFeatureAdded=false;
    // find the negative feature
    for (int is = 0; is < GetScribView()->m_surfacearray.GetSize(); is++){
      CSurface* pSurface= (CSurface*)GetScribView()->m_surfacearray.GetAt(is);
      if ((it == pSurface->MemberOfObject)){
        CPolygon *pPolygon = (CPolygon *)GetScribView()->m_polygonarray.GetAt(pThing->firstpolyno);
        if (pPolygon->MemberOfSurface==is){
//        if (0 == stricmp(GetScribView()->att[pSurface->attindex].name, pThing->parameter[16]))
          {
            if (0.0 == pSurface->exists){
              if (!bFeatureAdded){
                aNegativeComponents.Add( pFeature);
                bFeatureAdded= true;
              }
              // now find the intersections of this CThing's surfaces with surfaces of other CThings
              // 
              findCoincidentSurfacesFaceted( is, it, pAdvanced_faceStepPtrArray//, pVertex_pointStepPtrArray
                );
//            break;// cant break because there might be other surfaces!
              // but you don't want the feature to be in the list twice, so fix that
            }
          }
        }
      }
    }//next is

//  if ( GetScribView()->m_surfacearray.GetSize() == is){
//    aPositiveFeatures.Add( pFeature);
//  }
  }// next it
  return S_OK;
}
// suppress the entities which have been turned off using the layers
HRESULT step::supressLayersFaceted( CPtrArray*&           pPoly_loopPtrArray,
                                    CRepresentationStep*& pRepresentationStep ,
                                    surfaceModelSelect    lSurfaceModelSelect, 
                                    CPtrArray*&           pAdvanced_faceStepPtrArray, 
                                    agitoAssembly*        pAssembly )
{
  try {
    bool bLayerSuppressed = false;
    // use open shells if you delete or turn off a layer
    for ( int it =0; it < GetScribView()->m_thingarray.GetSize();it++ ) {
        CThing* pThing = (CThing*)GetScribView()->m_thingarray.GetAt(it);

        CModel* pModel = (CModel*)GetScribView()->m_modelarray.GetAt(pThing->BelongsToModelNo);
        if (!pModel->on){
        // since it might be possible to have surfaces without CThings, we have to do it this way
          if (-1 != pThing->firstpolyno) {
            if (-1 != pThing->lastpolyno) {
              for (int j = pThing->firstpolyno; j<=pThing->lastpolyno; j++) {
                pPoly_loopPtrArray->SetAt(j, NULL);

                agitoPart* pPart = (agitoPart*)pAssembly->GetAt(0);
                agitoComponent* pLump = (agitoComponent*)pPart->GetAt(0);
                agitoFeature* pFeature = (agitoFeature *)pLump->GetAt(0);
                CClosed_shellStep* pShellStep = (CClosed_shellStep*) pFeature->GetAt(0);

                for (int i = 0; i<pShellStep->m_pCFS_faces->GetSize(); i++){
                  if (pShellStep->m_pCFS_faces->GetAt(i) == pAdvanced_faceStepPtrArray->GetAt( j)) {
                    pShellStep->m_pCFS_faces->SetAt(i, NULL);
                  }
                }

                pAdvanced_faceStepPtrArray->SetAt(j, NULL);
                bLayerSuppressed =true;
                pAssembly->SetAt( it, NULL);
              }
            }
          }
        }
    }
  
  #if 1
      // now turn off those parts in layers
      for (int is =0; is < GetScribView()->m_surfacearray.GetSize();is++ ){
        CSurface* pSurface= (CSurface*)GetScribView()->m_surfacearray.GetAt(is);
        if (0 == GetScribView()->layers[pSurface->layer]){

          agitoPart* pPart = (agitoPart*)pAssembly->GetAt(0);
          agitoComponent* pLump = (agitoComponent*)pPart->GetAt(0);
          agitoFeature* pFeature = (agitoFeature *)pLump->GetAt(0);
          int jF = (int) CConnected_face_setStep::map_feature.GetAt( is);// wh 07/16/01
          pFeature = (agitoFeature*) pLump->GetAt(jF);// wh 07/16/01
          CClosed_shellStep* pShellStep = (CClosed_shellStep*) pFeature->GetAt(0);
//        int js = (int) CConnected_face_setStep::map_shell.GetAt( is);
//        pShellStep = (CClosed_shellStep*) pFeature->GetAt(js);

          for (int i = 0; i<pShellStep->m_pCFS_faces->GetSize(); i++){
            if (pShellStep->m_pCFS_faces->GetAt(i) == pAdvanced_faceStepPtrArray->GetAt(is )) {
              pShellStep->m_pCFS_faces->SetAt(i, NULL);
            }
          }
          for ( int ip = 0; ip< pSurface->polysinsurface;ip++){        
            pPoly_loopPtrArray->SetAt( pSurface->FirstPolygon + ip, NULL);
  //        int js = (int) CConnected_face_setStep::map_shell.GetAt( pSurface->FirstPolygon + ip);
  //        pShellStep = (CClosed_shellStep*) pFeature->GetAt(js);
//          int jp = (int) pShellStep->map_face.GetAt( pSurface->FirstPolygon + ip);
            int jp = (int) CConnected_face_setStep::map_face.GetAt( pSurface->FirstPolygon + ip);// wh 02/19/02
            // remove face from the shell
            pShellStep->m_pCFS_faces->SetAt( jp, NULL);// wh this is not the correct shell
          }
          pAdvanced_faceStepPtrArray->SetAt(is , NULL);

          bLayerSuppressed =true;
          pShellStep->demote();
        }
      }

  #endif // is

  #if 1
    for ( int ip = 0; ip < GetScribView()->m_polygonarray.GetSize(); ip ++){
      CPolygon *pPoly = (CPolygon*)GetScribView()->m_polygonarray.GetAt( ip);
      CSurface *pSurface = (CSurface*)GetScribView()->m_surfacearray.GetAt( pPoly->MemberOfSurface);
    
      if (0 == GetScribView()->layers[ pSurface->layer] ){// not pPoly
        agitoPart* pPart = (agitoPart*)pAssembly->GetAt(0);
        agitoComponent* pLump = (agitoComponent *)pPart->GetAt(0);
        int jF = (int) CConnected_face_setStep::map_feature.GetAt( ip);// wh 07/16/01
        agitoFeature* pFeature = (agitoFeature*) pLump->GetAt(jF);// wh 07/16/01
        CClosed_shellStep* pShellStep = (CClosed_shellStep*) pFeature->GetAt(0);
  //    int js = (int) CConnected_face_setStep::map_shell.GetAt( pSurface->FirstPolygon + ip);
  //    pShellStep = (CClosed_shellStep*) pFeature->GetAt(js);
        for (int i = 0; i<pShellStep->m_pCFS_faces->GetSize(); i++){
          if ( pShellStep->m_pCFS_faces->GetAt(i) == 
               pAdvanced_faceStepPtrArray->GetAt( pPoly->MemberOfSurface )) {
            pShellStep->m_pCFS_faces->SetAt(i, NULL);
          }
        }
        pPoly_loopPtrArray->SetAt(ip , NULL);
        pAdvanced_faceStepPtrArray->SetAt(ip , NULL);
        bLayerSuppressed =true;    
        pShellStep->demote();
      }
    }
  #endif // ip
  } 
  catch (...){
    ASSERT(false);
  }  
  return S_OK;
}

HRESULT step::lineEdgeGlanceAdvanced( int              ivm1,         // start vertex on neg feature's poly
                                     int              iv,           // end vertex on neg feature's poly
                                     CEdge_loopStep*  pELoop,       // loop corresponding to neg feature
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
    (pELoop->GetAt(ivm1)));
  CCartesian_pointStep* pPointStep1 = dynamic_cast<CCartesian_pointStep*>((CObject*)
    (pELoop->GetAt(iv  )));

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


//////////////////////////////////////////////////////////
// who  date      history
//-----------------------
// wh   11/14/01  activated advanced_brep section
// wh   11/18/01  able to correctly write tetra123 & monolith
// wh   11/25/01  able to write cylinder
// wh   11/27/01  simultanously support faceted_brep & advanced_brep
// wh   12/05/01  add seam edge to cylinder
