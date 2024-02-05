#include <iostream>
#include "DarwinActivationShieldingDecayAction.hh"
#include "DarwinActivationShieldingAnalyzeManager.hh"


#include "G4SystemOfUnits.hh"
#include "G4StepPoint.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4SteppingManager.hh"

DarwinActivationShieldingDecayAction::
    DarwinActivationShieldingDecayAction(DarwinActivationShieldingAnalyzeManager* analysis_cc, G4String file_output_cc)
    {
        file_output = file_output_cc;
        analysis = analysis_cc;
        fSecondary = 0;
    }

DarwinActivationShieldingDecayAction::~DarwinActivationShieldingDecayAction(){}

void DarwinActivationShieldingDecayAction::UserSteppingAction(const G4Step *aStep)
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

            //only analyze radioactive process
            if(process_name == "neutronInelastic" or
               process_name == "RadioactiveDecay" or
               process_name == "nCapture")
            //  if(true)
            {
                std::fstream file(file_output, std::ios::app); 
                fSecondary = steppingmanager->GetSecondary();
                for (size_t lp1=0; lp1<(*fSecondary).size();lp1++)
                {
                    const G4String &volume_name = (*fSecondary)[lp1]->GetVolume()->GetName();

                    //only care actions inside the LXe cube
                    if(volume_name!="phys_LXe_pipe"){}
                    else
                    {
                        //track and step information
                        G4int track_id = track->GetTrackID();
                        G4int step_id = track->GetCurrentStepNumber();
                        //G4cout << "Decay_cout "<<step_id << std::endl;
                        //analysis->track_information(track_id,step_id);

                        //current particle information
                        G4int charge = particle_def->GetPDGCharge();
                        G4double mass = particle->GetMass();
                        G4double Ek = track->GetKineticEnergy();
                        
                        //analysis->particle_information(particle_name,mass,charge,Ek);

                        //secondary decay table
                        const G4DynamicParticle* second_particle = (*fSecondary)[lp1]->GetDynamicParticle();
                        const G4ParticleDefinition* second_particle_def = second_particle->GetDefinition();
                        const G4String & second_particle_name = second_particle_def->GetParticleName();
                        if(second_particle_name.find("Xe")== second_particle_name.npos){continue;}
                      //     second_particle_name.find("Cs")== second_particle_name.npos){continue;}
                        G4int second_particle_charge = second_particle_def->GetPDGCharge();
                        G4double second_Ek = (*fSecondary)[lp1]->GetKineticEnergy();
                        G4int second_atomic_number = second_particle_def->GetAtomicNumber();
                        G4int second_atomic_mass = second_particle_def->GetAtomicMass();
                        //G4cout << particle_name << std::endl;
                        file << ""
                             << track_id << " "
                             << step_id << " "
                             << particle_name << " "
                             << charge << " "
                             << mass << " "
                             << Ek << " "
                             << process_name << " "
                             << second_particle_name << " "
                             << second_atomic_number << " "
                             << second_atomic_mass << " "
                             << second_particle_charge << " "
                             << second_Ek << std::endl;
                        //analysis->product_information(particle_name,process_name,second_particle_name,
                         //                           second_atomic_number,second_atomic_mass,second_particle_charge,second_Ek);
                    }
                }
                file.close();
            }
        }
}
