#include "g4root.hh"
#include "G4PrimaryParticle.hh"
#include "G4Track.hh"
#include "G4Trajectory.hh"
#include "EventAction.hh"
#include "G4EventManager.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4UnitsTable.hh"
#include "G4Step.hh"
#include "SteppingAction.hh"
#include "G4ProcessType.hh"
#include "g4root_defs.hh"
EventAction::EventAction()
: G4UserEventAction()
{
}

EventAction::~EventAction()
{
}

void EventAction::BeginOfEventAction(const G4Event*)
{ 
  
}

void EventAction::EndOfEventAction(const G4Event* event)
{

}
