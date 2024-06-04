// whichsur.cpp : implementation file
//

#ifdef _WINDOWS
#ifdef _WINDOWS
#include "stdafx.h"
#endif

#endif
#ifdef _WINDOWS 
#include "scribble.h"
#endif

#include "whichsur.h"
#include "resource.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// WhichSurf dialog


WhichSurf::WhichSurf(CWnd* pParent /*=NULL*/)
: CDialog(WhichSurf::IDD, pParent)
{
//{{AFX_DATA_INIT(WhichSurf)
	m_radio = -1;
	m_tex = -1;
	m_attstring = "";
	m_layer = _T("");
	//}}AFX_DATA_INIT
}

void WhichSurf::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
//{{AFX_DATA_MAP(WhichSurf)
	DDX_Radio(pDX, IDC_RADIO1, m_radio);
	DDX_Radio(pDX, IDC_RADIO4, m_tex);
	DDX_Text(pDX, IDC_EDIT2, m_attstring);
	DDV_MaxChars(pDX, m_attstring, 120);
	DDX_Text(pDX, IDC_EDIT27, m_reflect);
	DDV_MaxChars(pDX, m_reflect, 20);
	DDX_Text(pDX, IDC_EDIT28, m_refract);
	DDV_MaxChars(pDX, m_refract, 20);
	DDX_Text(pDX, IDC_EDIT8, m_exists);
	DDV_MaxChars(pDX, m_exists, 20);
	DDX_Text(pDX, IDC_STATICOBJECT2, m_layer);
	DDV_MaxChars(pDX, m_layer, 80);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(WhichSurf, CDialog)
//{{AFX_MSG_MAP(WhichSurf)
	ON_BN_CLICKED(IDC_ATTHELP, OnAtthelp)
	ON_EN_UPDATE(IDC_EDIT27, OnUpdateEdit27)
	ON_EN_UPDATE(IDC_EDIT8, OnUpdateEdit8)
	ON_EN_UPDATE(IDC_EDIT28, OnUpdateEdit28)	
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_RADIO6, OnRadio6)
	ON_BN_CLICKED(IDC_RADIO7, OnRadio7)	
	ON_BN_CLICKED(IDC_RADIO9, OnRadio9)
	ON_BN_CLICKED(IDC_RADIO10, OnRadio10)
	ON_BN_CLICKED(IDC_RADIO11, OnRadio11)
	ON_BN_CLICKED(IDC_RADIO12, OnRadio12)
	ON_BN_CLICKED(IDC_RADIO13, OnRadio13)	
	ON_BN_CLICKED(IDC_RADIO20, OnRadio20)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// WhichSurf message handlers

BOOL WhichSurf::OnInitDialog()
{
	CDialog::OnInitDialog();	
	strcpy (n[0], "When you specify a texture for a surface, depending on the texture selected, you must also assign parameters about that texture. You put these parameters in the attribute string box. Each parameter is separated by a space in the string. For example, if I need 3 parameters, of .5, 2 and 1.2, I would put these into the attribute string box as:\
\r\n\r\n.5 2 1.2 ");
	strcpy (n[1], "This texture does not require any attribute string.");
	strcpy (n[2], "SANDBLASTED SURFACE. There is one  parameter with this surface type, and it represents the coarseness of the sandblast. This parameter should have values in the range 0 to .5. ");
	strcpy (n[3], "GRANITE. There is one parameter with this surface type, and it represents the coarseness of the granite. This parameter should have values in the range 0 to .5.");
	strcpy (n[4], "WOOD GRAIN. There are four parameters in this texture type. The first is the scale parameter. This is any positive value. The standard value is 1. Using a number smaller than this will increase the scale, a larger number than 1 decreases the scale. The second parameter is what the clockwise degrees of rotation you want for the grain (which resides along the axis specified in the third parameter). Grain along the x axis rotates about y, grain along the y axis rotates about z, and grain along the z axis rotates about x. A gentle rotation (typically 5 degrees) makes for a nicer look. You can also rotate counterclockwise by specifying a negative value for this parameter. The third parameter is what axis you want the grain to run along (1=x, 2=y, 3=z). You can only use a 1, 2 or 3. The fourth and final parameter is the distortion level of the grain. A value of  0 means no distortion, and you have perfectly conical grain. Values of 1 and 2 have a nice look. This parameter must be a positive number. Usually you will want to use a value of 255 255 0 for the RGB values, which gives a nice oaken look.");
	strcpy (n[5], "MARBLE. There are two parameters with this surface type. The first is the scale factor. This is a very small, positive number, typically something like .05. The greater the scale, with the marble surface, the more activity is going on in a smaller space and vice versa. The second parameter is the resolution contrast, which is a number between 0 and 1. If 0, the marbling effect does not appear, and if 1 it appears very extremely.");
	strcpy (n[6], "BUMP MAP. This is a sophisticated technique which perturbs the surface normal to create the illusions of bumps, typically used in games. There are six parameters to a bump map: \
\r\nparameter 1 - enter a -1 to have the bump be an indent. Enter 0 for an out-dent.\r\nparameter 2 - The width of the bump. Enter a positive number (typically 3 to 7).");
	strcat(n[6],"\r\nparameter 3 - The height of the bump. Enter a positive number (typically 3 to 7). \
\r\nparameter 4 - The width of the space between bumps. Enter any positive number. \
\r\nparameter 5 - The height of the space between bumps. Enter any positive number. \
\r\nparameter 6 - The offset of the bumps. Enter a number between 0 and 1. 0 means do not offset. A value 0f .5, for instance, will align the bumps as they come down the surface in the spaces of the higher row of bumps.");
	strcat(n[6],"\r\n\r\nThree D graphics appear most realistic in gray, therefore, bumpmaps show up best when the RGB values used for the surface are 128 128 128.");
	strcat(n[7], "METALLIC. This is used primarily for colored metals (i.e. non grey colored metals) whereby the specular highlight is the color of the object itself, thus eliminating much of the plasticy look so often encountered in computer graphics. With this texture, the specular component is turned up and the diffuse component attenuated. There is no attribute string with this texture.");


  ((CEdit*) GetDlgItem(IDC_EDIT1))->SetWindowText(n[0]);  
  ((CEdit*) GetDlgItem(IDC_STATICOBJECT))->SetWindowText(object);
	switch (m_tex){
		case 0:
		  ((CEdit*) GetDlgItem(IDC_EDIT29))->SetWindowText(n[1]); break;
		case 1:
		  ((CEdit*) GetDlgItem(IDC_EDIT29))->SetWindowText(n[1]); break;
		case 2:
		  ((CEdit*) GetDlgItem(IDC_EDIT29))->SetWindowText(n[1]); break;
		case 3:
		  ((CEdit*) GetDlgItem(IDC_EDIT29))->SetWindowText(n[1]); break;
		case 4:
		  ((CEdit*) GetDlgItem(IDC_EDIT29))->SetWindowText(n[2]); break;
		case 5:
		  ((CEdit*) GetDlgItem(IDC_EDIT29))->SetWindowText(n[3]); break;
		case 6:
		  ((CEdit*) GetDlgItem(IDC_EDIT29))->SetWindowText(n[4]); break;
		case 7:
		  ((CEdit*) GetDlgItem(IDC_EDIT29))->SetWindowText(n[5]); break;
		case 8:
		  ((CEdit*) GetDlgItem(IDC_EDIT29))->SetWindowText(n[6]); break;
		case 9:
		  ((CEdit*) GetDlgItem(IDC_EDIT29))->SetWindowText(n[7]); break;
	}
	CenterWindow((AfxGetMainWnd())); 
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void WhichSurf::OnAtthelp()
{
	AfxGetApp()->WinHelp(IDC_ATTHELP); //context sensitive help 
}

void WhichSurf::OnUpdateEdit27()
{
	char s[50];
	float f;	
	CEdit* reflect=(CEdit*) GetDlgItem(IDC_EDIT27);
	if(reflect->GetWindowText(s,49)){
		f=(float)atof(s);
		if(f<0.0 || f>1.0){
			reflect->MessageBox("Reflection Percentage must be >=0.0 and <=1.0", "Input Error",  MB_OK );
		}
	}
}



void WhichSurf::OnUpdateEdit8()
{
	char s[50];	
	float f;	
	CEdit* exists=(CEdit*) GetDlgItem(IDC_EDIT8);
	if(exists->GetWindowText(s,49)){
		f=(float)atof(s);
		if(f<0.0 || f>1.0){
			exists->MessageBox("Exists parameter must be >=0.0 and <=1.0", "Input Error",  MB_OK );
		}
	}
}

void WhichSurf::OnUpdateEdit28()
{
	char s[50];	
	float f;	
	CEdit* refract=(CEdit*) GetDlgItem(IDC_EDIT28);
	if(refract->GetWindowText(s,49)){
		f=(float)atof(s);
		if(f<1.0){
			refract->MessageBox("Refraction must be >=1.0", "Input Error",  MB_OK );
		}
	}
}

void WhichSurf::OnRadio4()
{   
	 ((CEdit*) GetDlgItem(IDC_EDIT29))->SetWindowText(n[1]); 
	 CleanAttString(0);
}

void WhichSurf::OnRadio5()
{   
	 ((CEdit*) GetDlgItem(IDC_EDIT29))->SetWindowText(n[1]);
	 CleanAttString(1);
}

void WhichSurf::OnRadio6()
{   
	 ((CEdit*) GetDlgItem(IDC_EDIT29))->SetWindowText(n[1]);  
	 CleanAttString(2);
}

void WhichSurf::OnRadio7()
{   
	 ((CEdit*) GetDlgItem(IDC_EDIT29))->SetWindowText(n[1]);  
	 CleanAttString(3);
}

void WhichSurf::OnRadio9()
{   
	 ((CEdit*) GetDlgItem(IDC_EDIT29))->SetWindowText(n[2]);  
	 CleanAttString(4);
}

void WhichSurf::OnRadio10()
{   
	 ((CEdit*) GetDlgItem(IDC_EDIT29))->SetWindowText(n[3]);  
	 CleanAttString(5);
}

void WhichSurf::OnRadio11()
{   
	 ((CEdit*) GetDlgItem(IDC_EDIT29))->SetWindowText(n[4]);  
	CleanAttString(6);
}

void WhichSurf::OnRadio12()
{   
	 ((CEdit*) GetDlgItem(IDC_EDIT29))->SetWindowText(n[5]);  
	 CleanAttString(7);
}

void WhichSurf::OnRadio13()
{   
	 ((CEdit*) GetDlgItem(IDC_EDIT29))->SetWindowText(n[6]);  
	 CleanAttString(8);
}

void WhichSurf::OnRadio20()
{   
	 ((CEdit*) GetDlgItem(IDC_EDIT29))->SetWindowText(n[7]);  
	 CleanAttString(9);
}

void WhichSurf::CleanAttString(int w)
{
	if(m_tex==w){
	 ((CEdit*) GetDlgItem(IDC_EDIT2))->SetWindowText(m_attstring);
	}else{
	 ((CEdit*) GetDlgItem(IDC_EDIT2))->SetWindowText("");
	}
}
