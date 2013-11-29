// whichsur.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// WhichSurf dialog

class WhichSurf : public CDialog
{
// Construction
public:
	WhichSurf(CWnd* pParent = NULL); // standard constructor
	CString object;
	char n[8][1024];
// Dialog Data
//{{AFX_DATA(WhichSurf)
	enum { IDD = IDD_DIALOG7 };
	int  m_radio;
	int  m_tex;
	CString m_attstring;
	CString m_reflect;
	CString m_refract;
	CString m_exists;
	CString	m_layer;
	//}}AFX_DATA
	
// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
	void CleanAttString(int);
// Generated message map functions
//{{AFX_MSG(WhichSurf)
	virtual BOOL OnInitDialog();
	afx_msg void OnAtthelp();
	afx_msg void OnUpdateEdit27();
	afx_msg void OnUpdateEdit8();
	afx_msg void OnUpdateEdit28();
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	afx_msg void OnRadio6();
	afx_msg void OnRadio7();
	afx_msg void OnRadio9();
	afx_msg void OnRadio10();
	afx_msg void OnRadio11();
	afx_msg void OnRadio12();
	afx_msg void OnRadio13();
	afx_msg void OnRadio20();
//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
