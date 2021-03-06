/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "Controller/System.h"
PROTO_PUSH
#include "bind/engine/EngineEnvironment.pb.h"
PROTO_POP
#include "system/environment/SEEnvironment.h"

/**
 * @brief The %Environment class characterizes the environment and manages interactions between the body its surroundings.
 */  
class PULSE_DECL Environment : public SEEnvironment, public PulseSystem
{
  friend PulseController;
  friend class PulseEngineTest;
protected:
  Environment(PulseController& data);
  PulseController& m_data;

public:
  virtual ~Environment();

  void Clear();

  // Set members to a stable homeostatic state
  void Initialize();

  static void Load(const pulse::EnvironmentData& src, Environment& dst);
  static pulse::EnvironmentData* Unload(const Environment& src);
protected:
  static void Serialize(const pulse::EnvironmentData& src, Environment& dst);
  static void Serialize(const Environment& src, pulse::EnvironmentData& dst);

  // Set pointers and other member varialbes common to both homeostatic initialization and loading a state
  void SetUp();

public:
  void AtSteadyState();
  void PreProcess();
  void Process();
  void PostProcess();

  void StateChange();
protected:
  
  void ProcessActions();
  void CalculateSupplementalValues();
  /**/double AntoineEquation(double dTemperature_C);
  void CalculateRadiation();
  void CalculateConvection();
  void CalculateEvaporation();
  void CalculateRespiration();

  // Serializable member variables (Set in Initialize and in schema)
  

  // Stateless member variable (Calculated in Supplemental Method and used in other methods)
  double m_dLewisRelation;
  double m_dHeatOfVaporizationOfWater_J_Per_kg;
  double m_dWaterVaporPressureInAmbientAir_Pa;
  double m_dWaterVaporPressureAtSkin_Pa;
  //Prandtl number calculation
  double m_WaterSpecificHeat_J_Per_kg_K;
  double m_WaterViscosity_N_s_Per_m2;
  double m_WaterThermalConductivity_W_Per_m_K;
  //Grashof number calculation
  double m_ThermalExpansion_Per_K;
  // For Convection calculations
  double m_PatientEquivalentDiameter_m;

  // Stateless member variable (Set in SetUp())
  // Patient and Actions
  SEPatient*                     m_Patient;  
  SEPatientActionCollection*     m_PatientActions;
  SEEnvironmentActionCollection* m_EnvironmentActions;
  // Compartments
  SEGasCompartment*              m_AmbientGases;
  SELiquidCompartment*           m_AmbientAerosols;
  //Circuits                     
  SEThermalCircuit*              m_EnvironmentCircuit;
  //Nodes                        
  SEThermalCircuitNode*          m_ThermalEnvironment;
  SEThermalCircuitNode*          m_SkinNode;
  SEThermalCircuitNode*          m_ClothingNode;
  SEThermalCircuitNode*          m_EnclosureNode;
  //Paths                        
  SEThermalCircuitPath*          m_SkinToClothing;
  SEThermalCircuitPath*          m_ActiveHeatTransferRatePath;
  SEThermalCircuitPath*          m_ActiveTemperaturePath;
  SEThermalCircuitPath*          m_ActiveSwitchPath;
  SEThermalCircuitPath*          m_ClothingToEnclosurePath;
  SEThermalCircuitPath*          m_GroundToEnclosurePath;
  SEThermalCircuitPath*          m_ClothingToEnvironmentPath;
  SEThermalCircuitPath*          m_GroundToEnvironmentPath;
  SEThermalCircuitPath*          m_EnvironmentSkinToGroundPath;
  SEThermalCircuitPath*          m_EnvironmentCoreToGroundPath;
};
