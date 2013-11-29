// sequenceNumberIges.h: interface for the sequenceNumberIges class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEQUENCENUMBERIGES_H__2D853F42_941C_11D5_8CB5_00D00908C1A5__INCLUDED_)
#define AFX_SEQUENCENUMBERIGES_H__2D853F42_941C_11D5_8CB5_00D00908C1A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class sequenceNumberIges  
{
public:
	sequenceNumberIges();
	virtual ~sequenceNumberIges();

	int m_iSequenceStartNum;
	int m_iSequenceGlobalNum;
	int m_iSequenceDirectoryNum;
	int m_iSequenceParameterNum;
	int m_iSequenceTerminateNum;
};

#endif // !defined(AFX_SEQUENCENUMBERIGES_H__2D853F42_941C_11D5_8CB5_00D00908C1A5__INCLUDED_)
