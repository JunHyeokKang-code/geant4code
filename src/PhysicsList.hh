#ifndef PHYSICSLIST_HH
#define PHYSICSLIST_HH
#include "G4VModularPhysicsList.hh"
#include "G4EmExtraPhysics.hh"
#include "G4HadronPhysicsQGSP_BERT.hh"
#include "G4StoppingPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4NeutronTrackingCut.hh"
#include "G4HadronPhysicsFTFP_BERT.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"
#include "G4DecayPhysics.hh"
class PhysicsList : public G4VModularPhysicsList
{ 
  public:
    PhysicsList();
    ~PhysicsList();

};

#endif