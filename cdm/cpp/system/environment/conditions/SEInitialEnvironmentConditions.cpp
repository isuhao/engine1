/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
#include "stdafx.h"
#include "system/environment/conditions/SEInitialEnvironmentConditions.h"

#include "properties/SEScalar0To1.h"
#include "properties/SEScalarHeatConductancePerArea.h"
#include "properties/SEScalarLengthPerTime.h"
#include "properties/SEScalarMassPerVolume.h"
#include "properties/SEScalarPower.h"
#include "properties/SEScalarPressure.h"
#include "properties/SEScalarTemperature.h"
#include "properties/SEScalarHeatResistanceArea.h"

SEInitialEnvironmentConditions::SEInitialEnvironmentConditions(SESubstanceManager& substances) : SEEnvironmentCondition(), m_Substances(substances)
{
  m_Conditions = nullptr;
  InvalidateConditionsFile();  
}

SEInitialEnvironmentConditions::~SEInitialEnvironmentConditions()
{
  Clear();
}

void SEInitialEnvironmentConditions::Clear()
{
  SEEnvironmentCondition::Clear();
  InvalidateConditionsFile();
  SAFE_DELETE(m_Conditions);
}

bool SEInitialEnvironmentConditions::IsValid() const
{
  return SEEnvironmentCondition::IsValid() && (HasConditions() || HasConditionsFile());
}

void SEInitialEnvironmentConditions::Load(const cdm::InitialEnvironmentConditionsData& src, SEInitialEnvironmentConditions& dst)
{
  SEInitialEnvironmentConditions::Serialize(src, dst);
}
void SEInitialEnvironmentConditions::Serialize(const cdm::InitialEnvironmentConditionsData& src, SEInitialEnvironmentConditions& dst)
{
  SEEnvironmentCondition::Serialize(src.environmentcondition(), dst);
  if (src.has_conditions())
    SEEnvironmentalConditions::Load(src.conditions(), dst.GetConditions());
  else
    dst.SetConditionsFile(src.conditionsfile());
}

cdm::InitialEnvironmentConditionsData* SEInitialEnvironmentConditions::Unload(const SEInitialEnvironmentConditions& src)
{
  cdm::InitialEnvironmentConditionsData* dst = new cdm::InitialEnvironmentConditionsData();
  SEInitialEnvironmentConditions::Serialize(src, *dst);
  return dst;
}
void SEInitialEnvironmentConditions::Serialize(const SEInitialEnvironmentConditions& src, cdm::InitialEnvironmentConditionsData& dst)
{
  SEEnvironmentCondition::Serialize(src, *dst.mutable_environmentcondition());
  if (src.HasConditions())
    dst.set_allocated_conditions(SEEnvironmentalConditions::Unload(*src.m_Conditions));
  else if (src.HasConditionsFile())
    dst.set_conditionsfile(src.m_ConditionsFile);
}

bool SEInitialEnvironmentConditions::HasConditions() const
{
  return m_Conditions != nullptr;
}
SEEnvironmentalConditions& SEInitialEnvironmentConditions::GetConditions()
{
  m_ConditionsFile = "";
  if (m_Conditions == nullptr)
    m_Conditions = new SEEnvironmentalConditions(m_Substances);
  return *m_Conditions;
}
const SEEnvironmentalConditions* SEInitialEnvironmentConditions::GetConditions() const
{
  return m_Conditions;
}

std::string SEInitialEnvironmentConditions::GetConditionsFile() const
{
  return m_ConditionsFile;
}
void SEInitialEnvironmentConditions::SetConditionsFile(const std::string& fileName)
{
  if (m_Conditions != nullptr)
    SAFE_DELETE(m_Conditions);
  m_ConditionsFile = fileName;
}
bool SEInitialEnvironmentConditions::HasConditionsFile() const
{
  return m_ConditionsFile.empty() ? false : true;
}
void SEInitialEnvironmentConditions::InvalidateConditionsFile()
{
  m_ConditionsFile = "";
}


void SEInitialEnvironmentConditions::ToString(std::ostream &str) const
{
  str << "Environment Initial"; 
  if(HasComment())
    str<<"\n\tComment: "<<m_Comment;
  if (HasConditionsFile())
    str << "\n\tConditions File: "; str << m_ConditionsFile;
  if (HasConditions())
  {
    str << "\n\tSurroundingType: " << m_Conditions->GetSurroundingType();
    str << "\n\tAir Velocity: ";  m_Conditions->HasAirVelocity() ? str << m_Conditions->GetAirVelocity() : str << "Not Set";
    str << "\n\tAmbient Temperature: ";  m_Conditions->HasAmbientTemperature() ? str << m_Conditions->GetAmbientTemperature() : str << "Not Set";
    str << "\n\tAtmospheric Pressure: ";  m_Conditions->HasAtmosphericPressure() ? str << m_Conditions->GetAtmosphericPressure() : str << "Not Set";
    str << "\n\tClothing Resistance: ";  m_Conditions->HasClothingResistance() ? str << m_Conditions->GetClothingResistance() : str << "Not Set";
    str << "\n\tEmissivity: ";  m_Conditions->HasEmissivity() ? str << m_Conditions->GetEmissivity() : str << "Not Set";
    str << "\n\tMean Radiant Temperature: ";  m_Conditions->HasMeanRadiantTemperature() ? str << m_Conditions->GetMeanRadiantTemperature() : str << "Not Set";
    str << "\n\tRelative Humidity: ";  m_Conditions->HasRelativeHumidity() ? str << m_Conditions->GetRelativeHumidity() : str << "Not Set";
    str << "\n\tRespiration Ambient Temperature: ";  m_Conditions->HasRespirationAmbientTemperature() ? str << m_Conditions->GetRespirationAmbientTemperature() : str << "Not Set";
    if (m_Conditions->HasAmbientGas())
    {
      for (SESubstanceFraction* sf : m_Conditions->GetAmbientGases())
      {
        str << "\n\tSubstance : " << sf->GetSubstance().GetName() << " Fraction Amount " << sf->GetFractionAmount();
      }
    }
    if (m_Conditions->HasAmbientAerosol())
    {
      for (SESubstanceConcentration* sc : m_Conditions->GetAmbientAerosols())
      {
        str << "\n\tSubstance : " << sc->GetSubstance().GetName() << " Concentration " << sc->GetConcentration();
      }
    }
  }
  str << std::flush;
}

