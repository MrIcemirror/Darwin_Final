#ifndef Darwin_PS_DecayActivation_HH
#define Darwin_PS_DecayActivation_HH

#include <iostream>

#include "G4UserSteppingAction.hh"
#include "G4Event.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4StepPoint.hh"

class G4Step;

class Darwin_PS_DecayActivation: public G4UserSteppingAction
{
    public:
        Darwin_PS_DecayActivation(G4int &counts_cc);
        ~Darwin_PS_DecayActivation();

        void UserSteppingAction(const G4Step* aStep);
    
    private:
        const G4TrackVector* fSecondary;
        G4int &counts;
};

#endif