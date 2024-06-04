// StepPick.cpp : implementation file
//

#ifdef _WINDOWS
#include "stdafx.h"
#endif

#ifdef _WINDOWS 
#include "scribble.h"
#endif

#include "StepPick.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStepPick dialog


CStepPick::CStepPick(CWnd* pParent /*=NULL*/)
	: CDialog(CStepPick::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStepPick)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStepPick::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStepPick)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStepPick, CDialog)
	//{{AFX_MSG_MAP(CStepPick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStepPick message handlers

BOOL CStepPick::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CenterWindow((AfxGetMainWnd()));
	CScribView* ptView=(CScribView::GetView());  
	CButton* x1=(CButton*) GetDlgItem(IDC_RADIO1);	//FACETED
	x1->SetCheck(0);
	CButton* x2=(CButton*) GetDlgItem(IDC_RADIO2);	//ADVANCED
	x2->SetCheck(0);
	if(ptView->Step_Type==0){		
		x1->SetCheck(1);
	}
	if(ptView->Step_Type==1){		
		x2->SetCheck(1);
	}

//#ifndef   _DEBUG
//x1->SetCheck(1);
//x2->SetCheck(0);
//x2->EnableWindow(0);
//#endif

	CEdit* First=(CEdit*) GetDlgItem(IDC_FIRST_NAME);
	CEdit* Middle=(CEdit*) GetDlgItem(IDC_MIDDLE_NAME);
	CEdit* Last=(CEdit*) GetDlgItem(IDC_LAST_NAME);
	CEdit* Organization=(CEdit*) GetDlgItem(IDC_ORGANIZATION);
	CEdit* tol=(CEdit*) GetDlgItem(IDC_TOL);	
	First->SetWindowText(ptView->Step_FirstName); 
	Middle->SetWindowText(ptView->Step_MiddleName); 
	Last->SetWindowText(ptView->Step_LastName); 
	Organization->SetWindowText(ptView->Step_Organization);
	char t[30];
  if (ptView->Step_Tolerance < 1.0e-6){// hardcoded because the code only works to single precision
    ptView->Step_Tolerance = 1.0e-6;
  }

  sprintf(t,"%f",ptView->Step_Tolerance);
	tol->SetWindowText(t); 

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CStepPick::OnOK() 
{
	CScribView* ptView=(CScribView::GetView());  
	CButton* x1=(CButton*) GetDlgItem(IDC_RADIO1);	//FACETED
	if(x1->GetCheck()) 
		ptView->Step_Type=0;
	CButton* x2=(CButton*) GetDlgItem(IDC_RADIO2);	//ADVANCED
	if(x2->GetCheck()) 
		ptView->Step_Type=1;
	
	CEdit* First=(CEdit*) GetDlgItem(IDC_FIRST_NAME);
	CEdit* Middle=(CEdit*) GetDlgItem(IDC_MIDDLE_NAME);
	CEdit* Last=(CEdit*) GetDlgItem(IDC_LAST_NAME);
	CEdit* Organization=(CEdit*) GetDlgItem(IDC_ORGANIZATION);
	CEdit* tol=(CEdit*) GetDlgItem(IDC_TOL);
	
	First->GetWindowText(ptView->Step_FirstName,79); 
	Middle->GetWindowText(ptView->Step_MiddleName,79); 
	Last->GetWindowText(ptView->Step_LastName,79); 
	Organization->GetWindowText(ptView->Step_Organization,79);
	char t[30];	
	tol->GetWindowText(t,29); 
	ptView->Step_Tolerance=atof(t);

  if (ptView->Step_Tolerance < 1.0e-6){// hardcoded because the code only works to single precision
    ptView->Step_Tolerance = 1.0e-6;
  }

	CDialog::OnOK();
}
