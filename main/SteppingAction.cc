#include "SteppingAction.hh"
#include "EventAction.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4UnitsTable.hh"
#include "G4EventManager.hh"
#include "G4ProcessType.hh"
#include "G4Trajectory.hh"  
#include "G4VProcess.hh"
SteppingAction::SteppingAction()
: G4UserSteppingAction()
{
  // G4AnalysisManager 인스턴스 생성
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // 압축 수준 설정 (예: 1로 설정)
  analysisManager->SetCompressionLevel(9);
}
SteppingAction::~SteppingAction()
{
}
void SteppingAction::UserSteppingAction(const G4Step* step)
{ 
  G4RunManager* rumManager = G4RunManager::GetRunManager();

  const G4Track* track = step->GetTrack();
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4double flagParticle=0.;
  G4double flagProcess=0.;
  G4double x,y,z,xp,yp,zp,track_delta_e,total_track_dist,track_kin_e,prepx,prepy,prepz;
  G4int pdgcode,eventID;


        eventID = G4RunManager::GetRunManager() -> GetCurrentEvent() -> GetEventID(); //현재 event가 몇번째 event인지 numbering
        xp=step->GetPreStepPoint()->GetPosition().x()/nanometer; // 이전 strp에서의 x값
        yp=step->GetPreStepPoint()->GetPosition().y()/nanometer; // 이전 strp에서의 y값
        zp=step->GetPreStepPoint()->GetPosition().z()/nanometer; // 이전 strp에서의 z값
        /*xp=step->GetPostStepPoint()->GetPosition().x()/nanometer;
        yp=step->GetPostStepPoint()->GetPosition().y()/nanometer;
        zp=step->GetPostStepPoint()->GetPosition().z()/nanometer; */
        x=step->GetTrack()->GetPosition().x()/nanometer; //현재 step에서의 x값
        y=step->GetTrack()->GetPosition().y()/nanometer; //현재 step에서의 y값
        z=step->GetTrack()->GetPosition().z()/nanometer; //현재 step에서의 z값
        total_track_dist = step->GetTrack()->GetTrackLength()/mm; //현재 track의 총 이동거리
        track_kin_e = step->GetPreStepPoint()->GetKineticEnergy()/keV; //현재 track에서의 운동에너지
        track_delta_e = step->GetDeltaEnergy()/keV; //현 step에서 잃어버린 에너지
        G4int parentID = step->GetTrack()->GetParentID(); //현재 track을 생성시킨 모입자의 trackID
        pdgcode = step->GetTrack()->GetDynamicParticle()->GetPDGcode(); //현재 track입자의 pdg코드
        // 스텝의 시작 지점에서의 운동량 (PreStepPoint)
        // 스텝의 끝 지점에서의 운동량 (PostStepPoint)
        prepx = step->GetPreStepPoint()->GetMomentum().x()/c_light/keV; //x방향 presteppoint에서의 운동량
        prepy = step->GetPreStepPoint()->GetMomentum().y()/c_light/keV; //y방향 ``
        prepz = step->GetPreStepPoint()->GetMomentum().z()/c_light/keV; //z방향 ``
        G4double energyLoss = step->GetTotalEnergyDeposit()/keV; // 주변 공간으로의 에너지 방사량
        G4double stepLength = step->GetStepLength()/cm; //이전 step에서 현step 까지의 거리
        G4double stoppingPower = energyLoss / stepLength; //이동거리별 에너지 손실량
        const G4VProcess* process = track->GetStep()->GetPostStepPoint()->GetProcessDefinedStep(); //process  
        G4ProcessType processType = process->GetProcessType(); //해당 process의 type을 가져옴
        G4double globaltime = step->GetTrack()->GetGlobalTime()/ns; //시뮬레이션 시작부터 현재 시점까지의 전체 경과 시간
        G4double localTime = step->GetPreStepPoint()->GetLocalTime(); //입자가 특정 볼륨에 들어온 이후부터 현재 시점까지의 경과 시간
        G4int stepnum = step ->GetTrack() -> GetCurrentStepNumber(); //몇번째 step인지 표시, 하지만 verbose 할때와 달리 initialize 되지 않음
        G4int trackID = step->GetTrack()->GetTrackID();
        //G4ProcessType CreatorProcess = step -> GetTrack() -> GetCreatorProcess() ->GetProcessType(); //모입자에서 생성될때 어떤 process에서 생성되었는지 출력
        
        
        if(track->GetCreatorProcess()){
          //G4cout<<step -> GetTrack() -> GetCreatorProcess() ->GetProcessName()<<G4endl;
          if(step -> GetTrack() -> GetCreatorProcess() ->GetProcessName() == "Decay"){ //모입자 프로세스 한정

         //if(processType == fDecay)//step들중 decayprocess를 가진 step만 기록
         //{
          if(pdgcode = 11){
          analysisManager -> FillNtupleIColumn(0, eventID);//Ntuplecolumn에 데이터 저장 , I는 정수, D는 실수
          analysisManager->FillNtupleDColumn(1, x);//
          analysisManager->FillNtupleDColumn(2, y);
          analysisManager->FillNtupleDColumn(3, z);
          analysisManager->FillNtupleDColumn(4, std::sqrt((x-xp)*(x-xp)+(y-yp)*(y-yp)+(z-zp)*(z-zp)) );
          analysisManager->FillNtupleIColumn(5, trackID ); //현재 track의 ID 
          analysisManager->FillNtupleIColumn(6, step->GetTrack()->GetParentID() ); //모입자의 TrackID
          analysisManager->FillNtupleIColumn(7, step->GetTrack()->GetDynamicParticle()->GetPDGcode() ); //현재 track입자의 pdg코드
          analysisManager->FillNtupleDColumn(8, track_kin_e );
          analysisManager->FillNtupleDColumn(9, total_track_dist );
          analysisManager->FillNtupleDColumn(10, track_delta_e);
          analysisManager->FillNtupleIColumn(11, step->GetTrack()->GetCurrentStepNumber() ); //몇번째 step인지 표시, 하지만 verbose 할때와 달리 initialize 되지 않음
          analysisManager->FillNtupleDColumn(12, step->GetPreStepPoint()->GetMomentum().x()/c_light/keV  );
          analysisManager->FillNtupleDColumn(13, step->GetPreStepPoint()->GetMomentum().y()/c_light/keV  );
          analysisManager->FillNtupleDColumn(14, step->GetPreStepPoint()->GetMomentum().z()/c_light/keV  );
          analysisManager->FillNtupleDColumn(15, energyLoss);
          analysisManager->FillNtupleDColumn(16, globaltime);
          analysisManager->FillNtupleDColumn(17,step->GetPreStepPoint()->GetLocalTime()/ns); //presteppoint에서의 localtime
          analysisManager->FillNtupleDColumn(18,step->GetTrack()->GetLocalTime()/ns);
          analysisManager->FillNtupleDColumn(19,stoppingPower);
          analysisManager -> AddNtupleRow();
          }
          
          
        
        
        else{}}}


     if(eventID % 100 == 0){
  std::cout<<eventID/500.000<<"%"<<"\r";
  std::cout.flush();
  }


   
}
  

 
