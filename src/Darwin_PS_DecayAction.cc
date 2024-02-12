#include <iostream>
#include "Darwin_PS_DecayAction.hh"

#include "G4SystemOfUnits.hh"
#include "G4StepPoint.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4SteppingManager.hh"

Darwin_PS_DecayActivation::Darwin_PS_DecayActivation(G4int &counts_cc): counts(counts_cc){}

Darwin_PS_DecayActivation::~Darwin_PS_DecayActivation(){}

void Darwin_PS_DecayActivation::UserSteppingAction(const G4Step* aStep)
{
    G4SteppingManager *steppingmanager = fpSteppingManager;
    G4Track* track = aStep->GetTrack();

    //get parent particle name
    const G4DynamicParticle* particle = track->GetDynamicParticle();
    const G4ParticleDefinition* particle_def = particle->GetParticleDefinition();
    const G4String & particle_name = particle_def->GetParticleName();

    // exclude leptons and photons for process
    if(particle_name == "e-" or
       particle_name == "gamma" or
       particle_name == "e+"){}
    else
    {
        G4VProcess* process = steppingmanager->GetfCurrentProcess();
        const G4String &process_name = process->GetProcessName();

        if(process_name == "neutronInelastic" or
            process_name == "RadioactiveDecay" or
            process_name == "nCapture")
        {
            fSecondary = steppingmanager->GetSecondary();
            for (size_t lp1=0; lp1<(*fSecondary).size();lp1++)
            {
                const G4String &volume_name = (*fSecondary)[lp1]->GetVolume()->GetName();

                //only care actions inside the LXe cube
                if(volume_name!="phys_Center_LXe"){}
                else
                {
                    const G4DynamicParticle* second_particle = (*fSecondary)[lp1]->GetDynamicParticle();
                    const G4ParticleDefinition* second_particle_def = second_particle->GetDefinition();
                    const G4String & second_particle_name = second_particle_def->GetParticleName();

                    if(second_particle_name == "Xe137"){counts = counts+1;}
                    //if(second_particle_name.find("Xe")!= second_particle_name.npos){counts = counts+1;}
                }
            }
        }
   // G4cout << counts << G4endl;
    }
}