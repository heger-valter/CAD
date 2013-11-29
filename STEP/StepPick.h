#if !defined(AFX_STEPPICK_H__C5670A7D_58F1_4CE9_A4BA_596ED6135A3E__INCLUDED_)
#define AFX_STEPPICK_H__C5670A7D_58F1_4CE9_A4BA_596ED6135A3E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StepPick.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CStepPick dialog

class CStepPick : public CDialog
{
// Construction
public:
	CStepPick(CWnd* pParent = NULL);   // standard constructor
  void OnOK() ;
// Dialog Data
	//{{AFX_DATA(CStepPick)
	enum { IDD = IDD_DIALOG18 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStepPick)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStepPick)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STEPPICK_H__C5670A7D_58F1_4CE9_A4BA_596ED6135A3E__INCLUDED_)
