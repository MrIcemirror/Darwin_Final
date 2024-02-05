#include "DarwinActivationShieldingSensitiveLXe.hh"
#include <iostream>

DarwinActivationShieldingSensitiveLXe::
    DarwinActivationShieldingSensitiveLXe(const G4String& name, DarwinActivationShieldingAnalyzeManager* analyze_cc):
    G4VSensitiveDetector(name)
    {
        analyze = analyze_cc;
    }

DarwinActivationShieldingSensitiveLXe::~DarwinActivationShieldingSensitiveLXe(){}

G4bool DarwinActivationShieldingSensitiveLXe::ProcessHit(G4Step* aStep, G4TouchableHistory* ROHist)
{
    return true;

}