/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once

#include "properties/SEScalar.h"
#include "compartment/fluid/SEGasCompartment.h"
#include "compartment/fluid/SEGasCompartmentLink.h"
#include "compartment/fluid/SELiquidCompartment.h"
#include "compartment/fluid/SELiquidCompartmentLink.h"
#include "compartment/tissue/SETissueCompartment.h"
#include "scenario/SEDataRequestManager.h"
#include "utils/DataTrack.h"
class SESystem; 
class SEPatient;
class SEEnvironment;
class PhysiologyEngine;
class SESubstanceManager;
class SECompartmentManager;

enum class CompartmentUpdate {None,
                              InFlow, OutFlow,
                              HeatTransferRateIn, HeatTransferRateOut,
                              Volume,Pressure,
                              Heat, Temperature,
                              VolumeFraction,
                              Mass, Concentration, 
                              pH, Molarity,
                              PartialPressure, Saturation};
class SEDataRequestScalar : public SEGenericScalar
{
public:
  SEDataRequestScalar(Logger* logger) : SEGenericScalar(logger)
  {
    Heading.clear();

    UpdateProperty = CompartmentUpdate::None;
    GasCmpt = nullptr;
    GasSubstance = nullptr;
    LiquidCmpt = nullptr;
    LiquidSubstance = nullptr;
    ThermalCmpt = nullptr;
  }
  
  void UpdateScalar();
  void SetScalar(const SEScalar* s, SEDataRequest& dr);// SEScalar* in order to internnally throw error if the Track cannot find the requested property, it will pass in nullptr if it cannot find it

  std::string     Heading;

  // Compartment related variables
  CompartmentUpdate             UpdateProperty;
  SEGasCompartment*             GasCmpt;
  SEGasSubstanceQuantity*       GasSubstance;
  SELiquidCompartment*          LiquidCmpt;
  SELiquidSubstanceQuantity*    LiquidSubstance;
  SEThermalCompartment*         ThermalCmpt;
  // Tissue cmpts don't have children and they don't have computed data that changes on call (like flow)
};

class CDM_DECL SEEngineTracker : public Loggable
{
public:
  SEEngineTracker(PhysiologyEngine& engine);
  virtual ~SEEngineTracker();

  void Clear();// Remove all requests and close the results file
    
  DataTrack& GetDataTrack();
  SEDataRequestManager& GetDataRequestManager() { return m_DataRequestMgr; }

  void ResetFile();// Close file, so next Track Data will re hook up everything and make a new file

  bool ConnectRequest(SEDataRequest& dr, SEDataRequestScalar& ds);

  const SEDataRequestScalar* GetScalar(const SEDataRequest& dr) const;

  virtual void SetupRequests();
  virtual void TrackData(double currentTime_s);
  virtual void PullData();
  virtual bool TrackRequest(SEDataRequest& dr);
  virtual void ForceConnection() { m_ForceConnection = true; }
  
protected:
  bool                         m_ForceConnection;
  DataTrack                    m_DataTrack;

  std::stringstream            m_ss;
  std::ofstream                m_ResultsStream;
  SEDataRequestManager         m_DataRequestMgr;
  
  SEPatient&                   m_Patient;
  SESubstanceManager&          m_SubMgr;
  SECompartmentManager&        m_CmptMgr;

  SEEnvironment*               m_Environment;
  std::vector<SESystem*>       m_PhysiologySystems;
  SESystem*                    m_AnesthesiaMachine;
  SESystem*                    m_ECG;
  SESystem*                    m_Inhaler;
  std::map<const SEDataRequest*, SEDataRequestScalar*> m_Request2Scalar;
};