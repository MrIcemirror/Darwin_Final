#ifndef DarwinActivationShieldingSensitiveLXe_HH
#define DarwinActivationShieldingSensitiveLXe_HH

#include <iostream>
#include "G4VSensitiveDetector.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "DarwinActivationShieldingAnalyzeManager.hh"

class DarwinActivationShieldingSensitiveLXe: public G4VSensitiveDetector
{
    public:
        DarwinActivationShieldingSensitiveLXe(const G4String& name, DarwinActivationShieldingAnalyzeManager* analyze_cc);
        ~DarwinActivationShieldingSensitiveLXe();
        G4bool ProcessHit(G4Step*, G4TouchableHistory*);
    
    private:
        DarwinActivationShieldingAnalyzeManager* analyze;
};

#endif