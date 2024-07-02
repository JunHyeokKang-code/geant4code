#ifndef STEPPINGACTION_HH
#define STEPPINGACTION_HH

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "globals.hh"
#include "g4root.hh"

class SteppingAction : public G4UserSteppingAction
{
  public:
    SteppingAction(); //생성자 : 클래스 인스턴스가 생성될때 호출
    virtual ~SteppingAction(); //가상 소멸자 : 클래스 인스턴스가 소멸될 때 호출
    // 가상으로 선언하면 이 클래스를 상속 받는 클래스에서 적절하게 소멸자가 호출 되도록 함
    virtual void UserSteppingAction(const G4Step*); //가상 메서드로, G4Step 객체를 인수받음
                                                    // Geant4가 스텝을 진행할 때마다 호출되며, 사용자가 정의한 행동을 구현
};
#endif