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
  G4int n_particle = 1; //동시 발사 단위 설정
  fParticleGun = new G4ParticleGun(n_particle); //gun 생성
  G4double beamE = 1.0 * anEvent -> GetEventID(); // event 당 에너지 증가시 사용
  
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable -> FindParticle(particleName = "e-"); //입자 종류 정의

  fParticleGun -> SetParticlePosition(G4ThreeVector(0.,0.000000001,0.)); // 생성위치 설정
  fParticleGun -> SetParticleDefinition(particle); //위에서 설정한 입자 종류 설정
  fParticleGun -> SetParticleMomentumDirection(G4ThreeVector(0.,-1.,0.)); //운동량 설정 ( 운동 방향 )
  //fParticleGun -> SetParticleMomentumDirection(G4ThreeVector(0.,-1.,0.)); //0도
  //fParticleGun -> SetParticleMomentumDirection(G4ThreeVector(0.,-1.,sqrt(3))); //60도
  //fParticleGun -> SetParticleMomentumDirection(G4ThreeVector(0.,-sqrt(3),1.));//30도
  fParticleGun -> SetParticleEnergy((500)*MeV); // 에너지 설정
  //fParticleGun -> SetParticleEnergy((beamE*0.01)*MeV);
  fParticleGun -> GeneratePrimaryVertex(anEvent); // 발사
  }


