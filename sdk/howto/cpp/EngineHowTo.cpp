/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

// The following how-to functions demonstrate various ways of interacting with the Pulse engine
#include "EngineHowTo.h"
#include "engine/SEEngineTracker.h"
#include "scenario/SEDataRequest.h"
#include "properties/SEScalarTime.h"

int main()
{
  // Uncomment a method to execute fuctionality!

  //HowToSandbox();

  //HowToEngineUse();
  //HowToCreateAPatient();

  //HowToAirwayObstruction();
  //HowToAnesthesiaMachine();
  //HowToAsthmaAttack();
  //HowToBrainInjury();
  //HowToBolusDrug();
  //HowToConsumeNutrients();
  //HowToCOPD();
  //HowToCPR(); 
  //HowToEnvironmentChange();
  //HowToExercise();
  //HowToHemorrhage();
  //HowToLobarPneumonia();
  //HowToMechanicalVentilation();
  //HowToPulmonaryFunctionTest();
  //HowToSmoke();
  //HowToTensionPneumothorax();

  // This one does not really run, is a pure example
  //HowToRunScenario();

  // More complicated examples that do run
  //HowToConcurrentEngines();
    HowToDynamicHemorrhage();
}

HowToTracker::HowToTracker(PhysiologyEngine& engine) : m_Engine(engine)
{
  m_dT_s = m_Engine.GetTimeStep(TimeUnit::s);
}

HowToTracker::~HowToTracker()
{
}

void HowToTracker::AdvanceModelTime(double time_s)
{  
  // This samples the engine at each time step
  int count = static_cast<int>(time_s / m_dT_s);
  for (int i = 0; i <= count; i++)
  {    
    m_Engine.AdvanceModelTime();  // Compute 1 time step

    // Pull Track will pull data from the engine and append it to the file
    m_Engine.GetEngineTracker()->TrackData(m_Engine.GetSimulationTime(TimeUnit::s));
  }
}
