#include <PhysicsList.hh>


PhysicsList::PhysicsList()
{
 
 
    
   // EM Physics
    RegisterPhysics( new G4EmStandardPhysics() );

   // Synchroton Radiation & GN Physics
    //RegisterPhysics( new G4EmExtraPhysics() );

   // Decays
    RegisterPhysics( new G4DecayPhysics() ); //ex) mu->e, nu_mu, nu_e

   // Hadron Elastic scattering
    //RegisterPhysics( new G4HadronElasticPhysics() );

  // Hadron Physics
    //RegisterPhysics( new G4HadronPhysicsQGSP_BERT());
    //RegisterPhysics( new G4HadronPhysicsFTFP_BERT());

  // Stopping Physics
    //RegisterPhysics( new G4StoppingPhysics() );

  // Ion Physics
    //RegisterPhysics( new G4IonPhysics());
  
  // Optical Physics
    RegisterPhysics (new G4OpticalPhysics());

  // Neutron tracking cut
    //RegisterPhysics( new G4NeutronTrackingCut());

}


PhysicsList::~PhysicsList()
{}