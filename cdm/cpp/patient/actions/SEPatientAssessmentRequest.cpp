/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "patient/actions/SEPatientAssessmentRequest.h"
PROTO_PUSH
#include "bind/cdm/PatientActions.pb.h"
PROTO_POP

SEPatientAssessmentRequest::SEPatientAssessmentRequest() : SEPatientAction()
{
  m_Type=cdm::PatientAssessmentData_eType_CompleteBloodCount;
}

SEPatientAssessmentRequest::~SEPatientAssessmentRequest()
{
  Clear();
}

void SEPatientAssessmentRequest::Clear()
{
  SEPatientAction::Clear();
  m_Type=cdm::PatientAssessmentData_eType_CompleteBloodCount;
}

bool SEPatientAssessmentRequest::IsValid() const
{
  return SEPatientAction::IsValid();
}

bool SEPatientAssessmentRequest::IsActive() const
{
  return IsValid();
}

void SEPatientAssessmentRequest::Load(const cdm::PatientAssessmentRequestData& src, SEPatientAssessmentRequest& dst)
{
  SEPatientAssessmentRequest::Serialize(src, dst);
}
void SEPatientAssessmentRequest::Serialize(const cdm::PatientAssessmentRequestData& src, SEPatientAssessmentRequest& dst)
{
  SEPatientAction::Serialize(src.patientaction(), dst);
  dst.SetType(src.type());
}

cdm::PatientAssessmentRequestData* SEPatientAssessmentRequest::Unload(const SEPatientAssessmentRequest& src)
{
  cdm::PatientAssessmentRequestData* dst = new cdm::PatientAssessmentRequestData();
  SEPatientAssessmentRequest::Serialize(src, *dst);
  return dst;
}
void SEPatientAssessmentRequest::Serialize(const SEPatientAssessmentRequest& src, cdm::PatientAssessmentRequestData& dst)
{
  SEPatientAction::Serialize(src, *dst.mutable_patientaction());
  dst.set_type(src.m_Type);
}

cdm::PatientAssessmentData_eType SEPatientAssessmentRequest::GetType() const
{
  return m_Type;
}
void SEPatientAssessmentRequest::SetType(cdm::PatientAssessmentData_eType Type)
{
  m_Type = Type;
}
void SEPatientAssessmentRequest::ToString(std::ostream &str) const
{
  str << "Patient Action : Assessment Request"; 
  if(HasComment())
    str<<"\n\tComment: "<<m_Comment;
  str  << "\n\tType: "<< cdm::PatientAssessmentData_eType_Name(GetType());
  str  << std::flush;
}