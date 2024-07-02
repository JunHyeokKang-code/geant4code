#ifndef EVENTACTION_HH
#define EVENTACTION_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "globals.hh"
#include "g4root.hh"

class EventAction : public G4UserEventAction
{
  public:
    EventAction();
    virtual ~EventAction();

    // method from the base class
    virtual void BeginOfEventAction(const G4Event *);
    virtual void EndOfEventAction(const G4Event *);


  private:
 
};

#endif