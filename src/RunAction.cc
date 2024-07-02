#include "RunAction.hh"

RunAction::RunAction()
: G4UserRunAction()
{
}

RunAction::~RunAction()
{
  delete G4AnalysisManager::Instance();
}

void RunAction::BeginOfRunAction(const G4Run*) //생성자 :각각의 event가 시작할때 적용되는 코드. 
{


  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance(); 
  analysisManager -> OpenFile("data"); // 파일 생성
  analysisManager -> CreateNtuple("step","step"); // Ntuple생성
	analysisManager->CreateNtupleIColumn("eventID"); //각각 NtupleColumn 생성 I는 정수값 D는 실수값
	analysisManager->CreateNtupleDColumn("x");
	analysisManager->CreateNtupleDColumn("y");
	analysisManager->CreateNtupleDColumn("z");
	analysisManager->CreateNtupleDColumn("stepLength");
  analysisManager->CreateNtupleIColumn("trackid");
  analysisManager->CreateNtupleIColumn("parentid");
  analysisManager->CreateNtupleIColumn("pdgcode");
  analysisManager->CreateNtupleDColumn("kin_E");
  analysisManager->CreateNtupleDColumn("track_total");
  analysisManager->CreateNtupleDColumn("delta_E");
  analysisManager->CreateNtupleIColumn("stepnumber");
  analysisManager->CreateNtupleDColumn("prepx");
  analysisManager->CreateNtupleDColumn("prepy");
  analysisManager->CreateNtupleDColumn("prepz");
  analysisManager->CreateNtupleDColumn("energyLoss");
  analysisManager->CreateNtupleDColumn("Globaltime");
  analysisManager->CreateNtupleDColumn("prelocaltime");
  analysisManager->CreateNtupleDColumn("localtime");
  analysisManager->CreateNtupleDColumn("stoppingPower");


  analysisManager -> FinishNtuple(); //Ntuple 생성 종료
}

void RunAction::EndOfRunAction(const G4Run*) //소멸자 : 코드 구동이 종료될때 작동하는 코드
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager -> Write(); //파일에 Ntuple 기록
  analysisManager -> CloseFile(); // 파일 닫기. 저장 종료
}