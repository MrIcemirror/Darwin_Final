#include "DarwinActivationShieldingAction.hh"
#include "DarwinActivationShieldingAnalyzeManager.hh"
#include "DarwinActivationShieldingDecayAction.hh"
#include "DarwinActivationShieldingGenerator.hh"

using namespace std;

DarwinActivationShieldingAction_init::
DarwinActivationShieldingAction_init(G4double world_length_cc,
                                     G4double gen_radius_cc,
                                     std::vector<G4double> upper_cc,
                                     std::vector<G4double> lower_cc,
                                     std::vector<G4double> flux_prob_cc,
                                     DarwinActivationShieldingAnalyzeManager* analysis_cc,
                                     G4String file_output_cc,
                                     G4String sphere_cc,
                                     G4double gen_z_cc):
world_length(world_length_cc),upper(upper_cc),lower(lower_cc),flux_prob(flux_prob_cc)
{
    gen_z = gen_z_cc;
    sphere = sphere_cc;
    analysis = analysis_cc;
    file_output = file_output_cc;
    Build(world_length,gen_radius,upper,lower,flux_prob);
}

DarwinActivationShieldingAction_init::
~DarwinActivationShieldingAction_init(){}

void DarwinActivationShieldingAction_init::
Build(G4double world_length,G4double gen_radius, std::vector<G4double> upper,
      std::vector<G4double> lower,std::vector<G4double> flux_prob) const
{
    DarwinActivationShieldingGenerator *Generator = 
        new DarwinActivationShieldingGenerator(world_length,gen_radius,upper,lower,flux_prob,sphere,file_output,gen_z);
    SetUserAction(Generator);

    //Set stepping manager
    DarwinActivationShieldingDecayAction* stepping = new DarwinActivationShieldingDecayAction(analysis,file_output);
    SetUserAction(stepping);
    
}