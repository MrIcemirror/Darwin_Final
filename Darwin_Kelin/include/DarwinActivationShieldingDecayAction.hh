#ifndef DarwinActivationShieldingDecayAction_HH
#define DarwinActivationShieldingDecayAction_HH

#include <iostream>
#include "DarwinActivationShieldingAnalyzeManager.hh"

#include "G4UserSteppingAction.hh"
#include "G4Event.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4StepPoint.hh"

class G4Step;

class DarwinActivationShieldingDecayAction: public G4UserSteppingAction
{
    public:
        DarwinActivationShieldingDecayAction(DarwinActivationShieldingAnalyzeManager *analyze_cc, G4String file_output_cc);
        ~DarwinActivationShieldingDecayAction();    
        void UserSteppingAction(const G4Step* aStep);

    private:
        DarwinActivationShieldingAnalyzeManager* analysis;
        const G4TrackVector* fSecondary;
        G4String file_output;
};

#endif