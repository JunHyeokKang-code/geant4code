#include "globals.hh"

#include "G4RunManager.hh"
#include "G4VisExecutive.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"

#include "QGSP_BERT.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "PhysicsList.hh"

int main(int argc, char** argv)
{
  G4RunManager* runManager = new G4RunManager;
  
  G4VModularPhysicsList* physicsList = new QGSP_BERT; //physics 모델 , 원하는 시뮬레이션에 따라 변경 가능 , QSP + BERT 모델 
  //runManager -> SetUserInitialization(physicsList);
  runManager -> SetUserInitialization(new PhysicsList()); // 각각 코드들을 실행
  runManager -> SetUserInitialization(new DetectorConstruction());
  runManager -> SetUserAction(new PrimaryGeneratorAction());
  runManager -> SetUserAction(new RunAction());
  //runManager -> SetUserAction(new EventAction());
  runManager -> SetUserAction(new SteppingAction());
  runManager -> Initialize(); //코드 실행을 위한 초기화
  
  G4VisManager* visManager = new G4VisExecutive;
  visManager -> Initialize(); //코드 실행을 위한 초기화
  
//다음은 ui 실행 옵션
  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  if (argc != 1) 
  {
    G4String command = "/control/execute "; 
    G4String fileName = argv[1];
    UImanager -> ApplyCommand(command+fileName);
  }
  else 
  {
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
    UImanager -> ApplyCommand("/control/execute vis.mac"); //매크로 파일 실행
    ui -> SessionStart();
    delete ui;
  }

  delete visManager;
  delete runManager;

  return 0;
}
