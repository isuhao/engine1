/**************************************************************************************
Copyright 2015 Applied Research Associates, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License. You may obtain a copy of the License
at:
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
**************************************************************************************/

#pragma once
#include "patient/actions/SEPatientAction.h"
#include "bind/TensionPneumothoraxData.hxx"
#include "bind/enumPneumothoraxType.hxx"
#include "bind/enumSide.hxx"
#include "bind/enumOnOff.hxx"

class DLL_DECL SETensionPneumothorax : public SEPatientAction
{
public:

  SETensionPneumothorax();
  virtual ~SETensionPneumothorax();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  virtual bool Load(const CDM::TensionPneumothoraxData& in);
  virtual CDM::TensionPneumothoraxData* Unload() const;
protected:
  virtual void Unload(CDM::TensionPneumothoraxData& data) const;
public:

  virtual CDM::enumPneumothoraxType::value GetType() const;
  virtual void SetType(CDM::enumPneumothoraxType::value name);
  virtual bool HasType() const;
  virtual void InvalidateType();
  
  virtual CDM::enumSide::value GetSide() const;
  virtual void SetSide(CDM::enumSide::value name);
  virtual bool HasSide() const;
  virtual void InvalidateSide();

  virtual bool HasSeverity() const;
  virtual SEScalar0To1& GetSeverity();

  virtual void ToString(std::ostream &str) const;

protected:
  CDM::enumPneumothoraxType::value m_Type;
  CDM::enumSide::value m_Side;
  SEScalar0To1*    m_Severity;
  CDM::enumOnOff::value m_State;
  
};    