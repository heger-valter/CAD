// sequenceNumberIges.cpp: implementation of the sequenceNumberIges class.
//
//////////////////////////////////////////////////////////////////////

//nclude "stdafx.h"
//nclude "scribble.h"
#include "sequenceNumberIges.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

sequenceNumberIges::sequenceNumberIges()
: m_iSequenceStartNum(     0 )
, m_iSequenceGlobalNum(    0 )
, m_iSequenceDirectoryNum( 0 )
, m_iSequenceParameterNum( 0 )
, m_iSequenceTerminateNum( 0 )
{

}

sequenceNumberIges::~sequenceNumberIges()
{

}
