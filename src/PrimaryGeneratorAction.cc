#include "PrimaryGeneratorAction.hh"
#include "math.h"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction()
{
  
  
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called at the begining of each event
  G4int n_particle = 1;
  fParticleGun = new G4ParticleGun(n_particle);
  G4double beamE = 1.0 * anEvent -> GetEventID();
  
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable -> FindParticle(particleName = "e-");

  fParticleGun -> SetParticlePosition(G4ThreeVector(0.,0.000000001,0.));
  fParticleGun -> SetParticleDefinition(particle);
  fParticleGun -> SetParticleMomentumDirection(G4ThreeVector(0.,-1.,0.)); //z-axis
  //fParticleGun -> SetParticleMomentumDirection(G4ThreeVector(0.,-1.,0.)); //0도
  //fParticleGun -> SetParticleMomentumDirection(G4ThreeVector(0.,-1.,sqrt(3))); //60도
  //fParticleGun -> SetParticleMomentumDirection(G4ThreeVector(0.,-sqrt(3),1.));//30도
  fParticleGun -> SetParticleEnergy((500)*MeV);
  //fParticleGun -> SetParticleEnergy((beamE*0.01)*MeV);
  fParticleGun -> GeneratePrimaryVertex(anEvent);
  }


