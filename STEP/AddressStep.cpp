// AddressStep.cpp: implementation of the CAddressStep class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _WINDOWS
#include "stdafx.h"
#endif

#ifdef _WINDOWS 
#include "scribble.h"
#endif

#include "AddressStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAddressStep::CAddressStep()
: m_szInternal_location       ("www.github.com/heger-valter/CAD/STEP")
, m_szStreet_number           ("318 ")
, m_szStreet                  ("W. Randolph Street")
, m_szPostal_box              ("Suite 201")
, m_szTown                    ("Chicago")
, m_szRegion                  ("IL")
, m_szPostal_code             ("60606")
, m_szCountry                 ("USA")
//, m_szFacsimile_number        ("")
, m_szTelephone_number        ("1-901-492-1038")
, m_szElectronic_mail_address ("heger.valter@gmail.com")
//, m_szTelex_number            ("")
{
  nameClass("ADDRESS");
}

CAddressStep::~CAddressStep()
{

}

HRESULT CAddressStep::backPtr(CBaseStep *&prBrep)
{
  if (NULL!=m_pBack){
    m_pBack->backPtr( prBrep );  
    return S_OK;
  }
  else {
    return E_FAIL;
  }
}

void CAddressStep::Serialize(stepArchive &ar)
{
  if (!isSerialized()){
    setSerialized();
    try{
      writePre( ar);
      if (!m_szInternal_location.IsEmpty()) {
        ar << "'" <<       m_szInternal_location       << "'";
      }  else {
        ar << "$";
      }
      ar << ",";

      if (! m_szStreet_number.IsEmpty()) {
      ar << "'" <<       m_szStreet_number           << "'";
      }  else {
        ar << "$";
      }
      ar << ",";
      if (! m_szStreet.IsEmpty()) {
      ar << "'" <<       m_szStreet                  << "'";
      }  else {
        ar << "$";
      }
      ar << ",";
      if (! m_szPostal_box.IsEmpty()) {
      ar << "'" <<       m_szPostal_box              << "'";
      }  else {
        ar << "$";
      }
      ar << ",";
      if (! m_szTown.IsEmpty()) {
      ar << "'" <<       m_szTown                    << "'";
      }  else {
        ar << "$";
      }
      ar << ",";
      if (! m_szRegion.IsEmpty()) {
      ar << "'" <<       m_szRegion                  << "'";
      }  else {
        ar << "$";
      }
      ar << ",";
      if (! m_szPostal_code.IsEmpty()) {
      ar << "'" <<       m_szPostal_code             << "'";
      }  else {
        ar << "$";
      }
      ar << ",";
      if (! m_szCountry.IsEmpty()) {
      ar << "'" <<       m_szCountry                 << "'";
      }  else {
        ar << "$";
      }
      ar << ",";
      if (! m_szFacsimile_number.IsEmpty()) {
      ar << "'" <<       m_szFacsimile_number        << "'";
      }  else {
        ar << "$";
      }
      ar << ",";
      if (! m_szTelephone_number.IsEmpty()) {
      ar << "'" <<       m_szTelephone_number        << "'";
      }  else {
        ar << "$";
      }
      ar << ",";
      if (! m_szElectronic_mail_address .IsEmpty()) {
      ar << "'" <<       m_szElectronic_mail_address << "'";
      }  else {
        ar << "$";
      }
      ar << ",";
      if (! m_szTelex_number.IsEmpty()) {
      ar << "'" <<       m_szTelex_number            << "'";
      }  else {
        ar << "$";
      }
      ar << ", #";
      ar << "1083";// hard coded ref

      writePost( ar);
    }
    catch(...){
      ar << "\nError caught in ::Serialize!\n";
    }
  }
}
