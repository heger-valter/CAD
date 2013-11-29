// Application_context.cpp: implementation of the CApplication_context class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "scribble.h"
#include "Application_context.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CApplication_context::CApplication_context()
{
  nameClass("APPLICATION_CONTEXT");
//Configuration controlled 3D designs of mechanical parts and assemblies
}

CApplication_context::~CApplication_context()
{

}

void CApplication_context::Serialize(stepArchive &ar)
{

}

HRESULT CApplication_context::backPtr(CBaseStep *&prBrep)
{
    return S_OK;
}
